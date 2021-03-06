#include <SDL2/SDL.h>
#include "gb.h"
#include "hardware.h"

/*
* video
*/

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *texture = NULL;
static int scale_factor = 3;

int video_open(struct gameboy *gb) {
    (void)gb;
    int f = scale_factor;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        printf("failed to initialise SDL\n");
        return 0;
    }

    window = SDL_CreateWindow("gbmu",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCRN_X * f, SCRN_Y * f, 0);

    if (!window) {
        SDL_Log("could not create window: %s", SDL_GetError());
        return 0;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        SDL_Log("could not create renderer: %s", SDL_GetError());
        return 0;
    }

    SDL_RenderClear(renderer);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                                SDL_TEXTUREACCESS_STREAMING, SCRN_X, SCRN_Y);

    if (!texture) {
        SDL_Log("could not create texture: %s", SDL_GetError());
    }

    return 1;
}

int video_close(struct gameboy *gb) {
    (void)gb;

    if (texture) {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }

    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }

    if (window) {
        SDL_DestroyWindow(window);
        window = NULL;
    }

    SDL_Quit();
    return 1;
}

int video_write(struct gameboy *gb, uint8_t *data, uint32_t size) {
    (void)gb;
    uint32_t palette[] = {0xffffff, 0xaaaaaa, 0x555555, 0x000000};
    uint32_t *pixels, px;
    int pitch, y, x;
    (void)size;

    if (SDL_LockTexture(texture, NULL, (void *)&pixels, &pitch) < 0) {
        SDL_Log("couldn't lock texture: %s\n", SDL_GetError());
        return 0;
    }

    for (y = 0; y < SCRN_Y; y++) {
        for (x = 0; x < SCRN_X; x++) {
            px = data[y * SCRN_X + x];
            pixels[y * SCRN_X + x] = palette[px];
        }
    }

    SDL_UnlockTexture(texture);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    return 1;
}

/*
* inputs
*/

static void set_button_states(struct gameboy *gb, uint32_t key, uint8_t value) {
    uint32_t i, controls[] = {
        SDLK_DOWN, SDLK_UP, SDLK_LEFT, SDLK_RIGHT,
        SDLK_RETURN, SDLK_RSHIFT, SDLK_z, SDLK_x,
    };

    for (i = 0; i < 8; i++) {
        if (key == controls[i]) {
            gb->buttons[i] = value;
            joypad_request_interrupt(gb); //TODO: fix bad design
        }
    }
}

int input_open(struct gameboy *gb) {
    (void)gb;
    return 1;
}

int input_close(struct gameboy *gb) {
    (void)gb;
    return 1;
}

int input_read(struct gameboy *gb) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            gb->done = true;
            break;

        case SDL_KEYDOWN:
            set_button_states(gb, event.key.keysym.sym, 1);

            if (event.key.keysym.sym == SDLK_ESCAPE) {
                gb->done = true;
            }

            if (event.key.keysym.sym == SDLK_d) {
                gb->debug = !gb->debug;
            }

            if (event.key.keysym.sym == SDLK_s) {
                gb->screenshot = true;
            }

            if (event.key.keysym.sym == SDLK_i) {
                gb->log_io = true;
            }

            break;

        case SDL_KEYUP:
            set_button_states(gb, event.key.keysym.sym, 0);
            break;
        }
    }

    return 1;
}

/*
* sync
*/

int av_sync(struct gameboy *gb) {
    (void)gb;
    return 1;
}

/*
* audio
*/

static SDL_AudioDeviceID audio_device;
static uint8_t sdl_sound_buffer[SOUND_BUF_SIZE];
static volatile int audio_done;

int audio_write(struct gameboy *gb, uint8_t *data, uint32_t size) {
    (void)gb;
    memcpy(sdl_sound_buffer, data, size);
    audio_done = 0;

    while (!audio_done) {
        SDL_Delay(1);    /* wait */
    }

    return 1;
}

static void audio_callback(void *userdata, Uint8 *stream, int len) {
    (void)userdata;
    memcpy(stream, sdl_sound_buffer, len);
    audio_done = 1; /* signal */
}

/* to be called after SDL_Init() */
int audio_open(struct gameboy *gb) {
    (void)gb;
    SDL_AudioSpec want, have;
    int ret;
    SDL_memset(&have, 0, sizeof(SDL_AudioSpec));
    SDL_memset(&want, 0, sizeof(SDL_AudioSpec));
    want.freq = SAMPLING_FREQUENCY;
    want.format = AUDIO_S16;
    want.channels = NUM_CHANNELS;
    want.samples = NUM_FRAMES;
    want.callback = audio_callback;
    audio_device = SDL_OpenAudioDevice(NULL, 0, &want, &have, 0);
    ret = (audio_device != 0);

    if (!audio_device) {
        return ret;
    }

    if (want.freq != have.freq) {
        printf("  freq want: %d, have: %d\n", want.freq, have.freq);
        ret = 0;
    }

    if (want.format != have.format) {
        printf("format want: %d, have: %d\n", want.format, have.format);
        ret = 0;
    }

    if (want.channels != have.channels) {
        printf("  chan want: %d, have: %d\n", want.channels, have.channels);
        ret = 0;
    }

    if (want.samples != have.samples) {
        printf("sample want: %d, have: %d\n", want.samples,have.samples);
        ret = 0;
    }

    SDL_PauseAudioDevice(audio_device, 0);
    return ret;
}

int audio_close(struct gameboy *gb) {
    (void)gb;

    if (!audio_device) {
        return 1;
    }

    SDL_PauseAudioDevice(audio_device, 1);
    SDL_CloseAudioDevice(audio_device);
    audio_device = 0;
    return 1;
}
