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
static uint32_t num_samples = SOUND_BUF_SIZE / SAMPLE_SIZE;
static volatile uint32_t audio_frame_count;

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

sfBool getDataCallback(sfSoundStreamChunk *chunk, void *userdata) {
    (void)userdata;
    chunk->samples = (sfInt16*)sound_buffer;
    chunk->sampleCount = num_samples;
    audio_frame_count++;
    return sfTrue;
}

void seekCallback(sfTime time, void *userdata) {
    (void)time;
    (void)userdata;
}

int audio_open() {
    sound_stream = sfSoundStream_create(&getDataCallback, seekCallback, NUM_CHANNELS, SAMPLING_FREQUENCY, NULL);
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

int audio_write(uint8_t *data, uint32_t size) {
    (void)memcpy(sound_buffer, data, size);
    num_samples = size / SAMPLE_SIZE;
    return 1;
}

int input_open() {
    return 1;
}

int input_close() {
    return 1;
}

int input_read() {
    sfKeyCode keys[] = {sfKeyDown, sfKeyUp, sfKeyLeft, sfKeyRight, sfKeyEnter, sfKeyRShift, sfKeyZ, sfKeyX};
    sfEvent event;
    int i;

    while (sfRenderWindow_pollEvent(window, &event)) {
        switch (event.type) {
        case sfEvtClosed:
            state->done = 1;
            break;
        case sfEvtKeyPressed:
        case sfEvtKeyReleased:
            state->done = (event.key.code == sfKeyEscape) || (event.key.code == sfKeyQ);
            for (i = 0; i < 8; i++) {
                if (event.key.code == keys[i]) {
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

void throttle() {
    static struct timespec tp, last_tp; //, sleep = {0, 99};
    static uint64_t clock_cycles, current_ms, last_ms;

    if (clock_gettime(CLOCK_REALTIME, &tp))
        return ;

    if (tp.tv_sec > last_tp.tv_sec)
        last_ms = 0;

    current_ms = tp.tv_nsec / 1000000;
    if (current_ms <= last_ms)
        return ;

    if ((state->cycles - clock_cycles) <= (current_ms - last_ms) * (4194304 / 1000))
        return ;

    last_ms = current_ms;
    memcpy(&last_tp, &tp, sizeof(struct timespec));
    clock_cycles = state->cycles;
    sfSleep(sfMilliseconds(1));
}

int av_sync() {
    throttle();
    return 1;
}

