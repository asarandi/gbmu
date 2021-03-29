#include "gb.h"

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
static ma_device device;

static uint8_t sb[2][SOUND_BUF_SIZE];
static volatile int is_full[2];

#include <caca.h>
static caca_display_t *display = NULL;
static caca_canvas_t *canvas = NULL;
static caca_dither_t *dither = NULL;
static int canvas_width, canvas_height;

int video_open() {
    canvas = caca_create_canvas(0, 0);
//    display = caca_create_display_with_driver(canvas, "ncurses");
    display = caca_create_display(canvas);
    if (display == NULL)
        return 0;
    canvas_width = caca_get_canvas_width(canvas),
    canvas_height = caca_get_canvas_height(canvas),
    dither = caca_create_dither(32, 160, 144, 4 * 160, 255<<16, 255<<8, 255, 0);
//    caca_set_dither_algorithm(dither, "none");
//    caca_set_dither_antialias(dither, "default");
//    caca_set_dither_charset(dither, "default");
//    caca_set_dither_color(dither, "default");
    return 1;
}

int video_close() {
    if (dither) {
        caca_free_dither(dither);
        dither = NULL;
    }
    if (display) {
        caca_free_display(display);
        display = NULL;
    }
    return 1;
}

int video_write(uint8_t *data, uint32_t size) {
//    uint32_t palette[] = {0xffffff, 0xaaaaaa, 0x555555, 0x000000};
    uint32_t palette[] = {0xffe4c2, 0xdca456, 0xa9604c, 0x422936};
    uint32_t bitmap[160*144];
    uint32_t y, x, p;

    (void)size;

    for (y = 0; y < 144; y++) {
        for (x = 0; x < 160; x++) {
            p = data[y * 160 + x];
            bitmap[y * 160 + x] = palette[p];
        }
    }
    caca_dither_bitmap(canvas, 0, 0, canvas_width, canvas_height, dither, bitmap);
    caca_refresh_display(display);
    return 1;
}

int audio_write(uint8_t *data, uint32_t size) {
    int i;

    while (is_full[0] && is_full[1])
        ; /* wait */
    i = is_full[0];
    (void)memcpy(sb[i], data, size);
    is_full[i] = 1;
    return 1;
}

void callback(ma_device* dev, void* out, const void* in, ma_uint32 ct) {
    static int i, p;
    int want, have;

    (void)dev;
    (void)in;

    want = ct * NUM_CHANNELS * SAMPLE_SIZE;
    have = SOUND_BUF_SIZE - p;

    if ((p + want) < SOUND_BUF_SIZE) {
        memcpy(out, sb[i] + p, want);
        p += want;
    } else {
        memcpy(out, sb[i] + p, have);
        is_full[i] = 0;
        i ^= 1;
        p = want - have;
        memcpy(out + have, sb[i], p);
    }
}

int audio_open() {
    ma_device_config config  = ma_device_config_init(ma_device_type_playback);
    config.playback.format   = ma_format_s16;
    config.playback.channels = NUM_CHANNELS;
    config.sampleRate        = SAMPLING_FREQUENCY;
    config.dataCallback      = callback;

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
    caca_event_t event;
    int event_type, mask, key, i;

    int controls[] = {
        CACA_KEY_DOWN,
        CACA_KEY_UP,
        CACA_KEY_LEFT,
        CACA_KEY_RIGHT,
        CACA_KEY_RETURN,
        CACA_KEY_BACKSPACE,
        'z',
        'x',
    };

    int quit[] = {
        CACA_KEY_ESCAPE,
        CACA_KEY_CTRL_C,
        CACA_KEY_CTRL_D,
        CACA_KEY_CTRL_Z,
        'q',
    };

    mask = CACA_EVENT_QUIT | CACA_EVENT_RESIZE |
           CACA_EVENT_KEY_PRESS | CACA_EVENT_KEY_RELEASE;
    while (caca_get_event(display, mask, &event, 0)) {
        event_type = caca_get_event_type(&event);
        /*
            issue: when holding down a key - caca continuously generates `KEY_PRESS` events
            this introduces a significant lag in games like mario - simply "walking"
        */
        if (event_type == CACA_EVENT_QUIT) {
            state->done = 1;
        } else if (event_type == CACA_EVENT_RESIZE) {
            /*
                issue: not receiving this event, driver specific?
            */
            canvas_width = caca_get_event_resize_width(&event);
            canvas_height = caca_get_event_resize_height(&event);
            caca_set_canvas_size(canvas, canvas_width, canvas_height);
            caca_clear_canvas(canvas);
        } else {
            key = caca_get_event_key_ch(&event);
            key = (key >= 'A' && key <= 'Z') ? key | 32 : key;
            for (i = 0; i < 8; i++) {
                if (key == controls[i]) {
                    state->buttons[i] = event_type == CACA_EVENT_KEY_PRESS;
                }
            }
            for (i = 0; i < 5; i++) {
                if (key == quit[i]) {
                    state->done = 1;
                }
            }
        }
    }
    return 1;
}

int av_sync() {
    return 1;
}
