#include "gb.h"
#include <SFML/Audio.h>
#include <SFML/Graphics.h>

#define SCALE 3
#define WIDTH (SCALE * 160)
#define HEIGHT (SCALE * 144)

static sfRenderWindow* window;
static sfSprite* sprite;
static sfTexture* texture;
static sfSoundStream* sound_stream;
static uint8_t sound_buffer[SOUND_BUF_SIZE];
static volatile int audio_done = 0;

int video_open() {
    sfVideoMode mode = {WIDTH, HEIGHT, 32};

    window = sfRenderWindow_create(mode, "gbmu", sfClose, NULL);
    if (window == NULL)
        return 0;
    texture = sfTexture_create(WIDTH, HEIGHT);
    if (texture == NULL)
        return 0;
    sprite = sfSprite_create();
    if (sprite == NULL)
        return 0;
    sfSprite_setTexture(sprite, texture, 0);
    return 1;
}

int video_close() {
    if (sprite)
        sfSprite_destroy(sprite);
    if (texture)
        sfTexture_destroy(texture);
    if (window) {
        sfRenderWindow_close(window);
        sfRenderWindow_destroy(window);
    }
    return 1;
}

int video_write(uint8_t *data, uint32_t size) {
    sfUint8 video_buffer[WIDTH * HEIGHT * 4];
    uint32_t palette[] = {0xffc2e4ff, 0xff56a4dc, 0xff4c60a9, 0xff362942};
    uint32_t idx, y, x, i, j, f = SCALE;
    uint32_t *pixels = (uint32_t*)video_buffer;

    (void)size;

    for (y = 0; y < 144; y++) {
        for (x = 0; x < 160; x++) {
            idx = data[y * 160 + x];
            for (i = y * f; i < (y + 1) * f; i++) {
                for (j = x * f; j < (x + 1) * f; j++) {
                    pixels[i * f * 160 + j] = palette[idx];
                }
            }
        }
    }

    sfTexture_updateFromPixels(texture, video_buffer, WIDTH, HEIGHT, 0, 0);
    sfRenderWindow_drawSprite(window, sprite, NULL);
    sfRenderWindow_display(window);
    return 1;
}

int audio_write(uint8_t *data, uint32_t size) {
    (void)memcpy(sound_buffer, data, size);
    audio_done = 0;
    while (!audio_done)
        ; /* wait */
    return 1;
}

sfBool callback(sfSoundStreamChunk *chunk, void *userdata) {
    (void)userdata;
    chunk->samples = (sfInt16*)sound_buffer;
    chunk->sampleCount = SOUND_BUF_SIZE / SAMPLE_SIZE;
    audio_done = 1; /* signal */
    return sfTrue;
}

int audio_open() {
    sound_stream = sfSoundStream_create(&callback, NULL,
                                        NUM_CHANNELS, SAMPLING_FREQUENCY, NULL);
    if (sound_stream == NULL)
        return 0;
    sfSoundStream_play(sound_stream);
    return 1;
}

int audio_close() {
    if (sound_stream) {
        sfSoundStream_stop(sound_stream);
        sfSoundStream_destroy(sound_stream);
    }
    return 1;
}

int input_open() {
    return 1;
}

int input_close() {
    return 1;
}

int input_read() {
    sfKeyCode keys[] = {sfKeyDown, sfKeyUp, sfKeyLeft, sfKeyRight,
                        sfKeyEnter, sfKeyRShift, sfKeyZ, sfKeyX
                       };
    sfEvent event;
    int key, i;

    while (sfRenderWindow_pollEvent(window, &event)) {
        switch (event.type) {
        case sfEvtClosed:
            state->done = 1;
            break;
        case sfEvtKeyPressed:
        case sfEvtKeyReleased:
            key = event.key.code;
            state->done = (key == sfKeyEscape) || (key == sfKeyQ);
            for (i = 0; i < 8; i++) {
                if (key == keys[i]) {
                    state->buttons[i] = (event.type == sfEvtKeyPressed);
                    joypad_request_interrupt();
                }
            }
            break;
        default:
            break;
        }
    }
    return 1;
}

int av_sync() {
    return 1;
}
