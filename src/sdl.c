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

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK) != 0) {
        SDL_Log("SDL_Init(): %s", SDL_GetError());
        return 0;
    }

    window = SDL_CreateWindow("gbmu",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCRN_X * f, SCRN_Y * f, 0);

    if (!window) {
        SDL_Log("SDL_CreateWindow(): %s", SDL_GetError());
        return 0;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        SDL_Log("SDL_CreateRenderer(): %s", SDL_GetError());
        return 0;
    }

    SDL_RenderClear(renderer);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                                SDL_TEXTUREACCESS_STREAMING, SCRN_X, SCRN_Y);

    if (!texture) {
        SDL_Log("SDL_CreateTexture(): %s", SDL_GetError());
        return 0;
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
        SDL_Log("SDL_LockTexture(): %s", SDL_GetError());
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

static SDL_Joystick *joystick = NULL;

static void set_button_states(struct gameboy *gb, uint32_t key, uint8_t value) {
    uint32_t i, prev_val, controls[] = {
        SDLK_DOWN, SDLK_UP, SDLK_LEFT, SDLK_RIGHT,
        SDLK_RETURN, SDLK_RSHIFT, SDLK_z, SDLK_x,
    };

    for (i = 0; i < 8; i++) {
        if (key == controls[i]) {
            prev_val = gb->buttons[i];
            gb->buttons[i] = value;

            if (prev_val != value) {
                joypad_request_interrupt(gb); //TODO: fix bad design
            }
        }
    }
}

int input_open(struct gameboy *gb) {
    (void)gb;
    return 1;
}

int input_close(struct gameboy *gb) {
    (void)gb;

    if (joystick) {
        SDL_JoystickClose(joystick);
        joystick = NULL;
    }

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

        case SDL_JOYAXISMOTION: {
            int axis = event.jaxis.axis;
            int value = event.jaxis.value;
            struct {
                int axis, value, k1, v1, k2, v2;
            } tab[] = {
                {0,  32767, SDLK_RIGHT, 1, SDLK_LEFT, 0},
                {0, -32768, SDLK_RIGHT, 0, SDLK_LEFT, 1},
                {0,      0, SDLK_RIGHT, 0, SDLK_LEFT, 0},
                {1,  32767, SDLK_DOWN, 1, SDLK_UP, 0},
                {1, -32768, SDLK_DOWN, 0, SDLK_UP, 1},
                {1,      0, SDLK_DOWN, 0, SDLK_UP, 0},
            };

            for (int i=0; i<6; i++) {
                if ((tab[i].axis == axis) && (tab[i].value == value)) {
                    set_button_states(gb, tab[i].k1, tab[i].v1);
                    set_button_states(gb, tab[i].k2, tab[i].v2);
                    break ;
                }
            }
        }
        break;

        case SDL_JOYBUTTONDOWN:
        case SDL_JOYBUTTONUP: {
            int button = event.jbutton.button;
            int value = event.jbutton.state;

            for (int i=0; i<6; i++) {
                struct {
                    int button, key;
                } tab[] = {
                    {9, SDLK_RETURN},
                    {8, SDLK_RSHIFT},
                    {2, SDLK_z},
                    {1, SDLK_x},
                    {3, SDLK_z},
                    {0, SDLK_x},
                };

                if (tab[i].button == button) {
                    set_button_states(gb, tab[i].key, value);
                    break ;
                }
            }
        }
        break;

        case SDL_JOYDEVICEADDED:
            if (!joystick) {
                joystick = SDL_JoystickOpen(event.jdevice.which);

                if (!joystick) {
                    SDL_Log("SDL_JoystickOpen(): %s", SDL_GetError());
                } else {
                    SDL_Log("joystick added");
                }
            }

            break;

        case SDL_JOYDEVICEREMOVED:
            if ((joystick) && (SDL_JoystickInstanceID(joystick) == event.jdevice.which)) {
                SDL_JoystickClose(joystick);
                joystick = NULL;
                SDL_Log("joystick removed");
            }

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
    int retval;
    SDL_AudioSpec want, have;
    SDL_memset(&have, 0, sizeof(SDL_AudioSpec));
    SDL_memset(&want, 0, sizeof(SDL_AudioSpec));
    want.freq = SAMPLING_FREQUENCY;
    want.format = AUDIO_S16;
    want.channels = NUM_CHANNELS;
    want.samples = NUM_FRAMES;
    want.callback = audio_callback;
    audio_device = SDL_OpenAudioDevice(NULL, 0, &want, &have, 0);
    retval = audio_device != 0;

    if (!audio_device) {
        SDL_Log("SDL_OpenAudioDevice(): %s", SDL_GetError());
        retval = 0;
    }

    if (want.freq != have.freq) {
        SDL_Log("frequency want: %d, have: %d", want.freq, have.freq);
        retval = 0;
    }

    if (want.format != have.format) {
        SDL_Log("   format want: %d, have: %d", want.format, have.format);
        retval = 0;
    }

    if (want.channels != have.channels) {
        SDL_Log(" channels want: %d, have: %d", want.channels, have.channels);
        retval = 0;
    }

    if (want.samples != have.samples) {
        SDL_Log("  samples want: %d, have: %d", want.samples, have.samples);
        retval = 0;
    }

    if (retval) {
        SDL_PauseAudioDevice(audio_device, 0);
    }

    return retval;
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
