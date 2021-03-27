#include "gb.h"

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#define SCALE 3
#define WIDTH (SCALE * 160)
#define HEIGHT (SCALE * 144)

static ma_device device;

int video_open() {
    return 1;
}

int video_close() {
    return 1;
}

int video_write(uint8_t *data, uint32_t size) {
    (void)data;
    (void)size;
//    uint32_t palette[] = {0xffc2e4ff, 0xff56a4dc, 0xff4c60a9, 0xff362942};
//    uint32_t idx, y, x, i, j, f = SCALE;
//    uint32_t *pixels = (uint32_t*)video_buffer;
//
//    (void)size;
//
//    for (y = 0; y < 144; y++) {
//        for (x = 0; x < 160; x++) {
//            idx = data[y * 160 + x];
//            for (i = y * f; i < (y + 1) * f; i++) {
//                for (j = x * f; j < (x + 1) * f; j++) {
//                    pixels[i * f * 160 + j] = palette[idx];
//                }
//            }
//        }
//    }
//
//    sfTexture_updateFromPixels(texture, video_buffer, WIDTH, HEIGHT, 0, 0);
//    sfRenderWindow_drawSprite(window, sprite, NULL);
//    sfRenderWindow_display(window);
    return 1;
}

static uint8_t sb[2][SOUND_BUF_SIZE];
static volatile int is_full[2];

int audio_write(uint8_t *data, uint32_t size) {
    int i;

    while (is_full[0] && is_full[1])
        ; /* wait */
    i = is_full[0];
    (void)memcpy(sb[i], data, size);
    is_full[i] = 1;
    return 1;
}

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount) {
    static int i, p;
    int want, have;

    (void)pDevice;
    (void)pInput;

    want = frameCount * NUM_CHANNELS * SAMPLE_SIZE;
    have = SOUND_BUF_SIZE - p;

    if ((p + want) <= SOUND_BUF_SIZE) {
        memcpy(pOutput, sb[i] + p, want);
        p += want;
    } else {
        memcpy(pOutput, sb[i] + p, have);
        is_full[i] = 0;
        i ^= 1;
        p = want - have;
        memcpy(pOutput + have, sb[i], p);
    }
}

int audio_open() {
    ma_device_config config  = ma_device_config_init(ma_device_type_playback);
    config.playback.format   = ma_format_s16;
    config.playback.channels = NUM_CHANNELS;
    config.sampleRate        = SAMPLING_FREQUENCY;
    config.dataCallback      = data_callback;

    if (ma_device_init(NULL, &config, &device) != MA_SUCCESS) {
        return 0;
    }
    (void)ma_device_start(&device);
    return 1;
}

int audio_close() {
    (void)ma_device_stop(&device);
    (void)ma_device_uninit(&device);
    return 1;
}

int input_open() {
    return 1;
}

int input_close() {
    return 1;
}

int input_read() {
    return 1;
}

int av_sync() {
    return 1;
}
