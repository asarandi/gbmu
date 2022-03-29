#include <SDL2/SDL.h>
#include "gb.h"
#include "hardware.h"

static SDL_Joystick *joystick = NULL;
const char *joystick_name = NULL;

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

    if (gb->testing) {
        return 1;
    }

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
            struct {
                int axis, value, k1, v1, k2, v2;
            } tab[] = {
                {0,  1, SDLK_RIGHT, 1, SDLK_LEFT, 0},
                {0, -1, SDLK_RIGHT, 0, SDLK_LEFT, 1},
                {0,  0, SDLK_RIGHT, 0, SDLK_LEFT, 0},
                {1,  1, SDLK_DOWN, 1, SDLK_UP, 0},
                {1, -1, SDLK_DOWN, 0, SDLK_UP, 1},
                {1,  0, SDLK_DOWN, 0, SDLK_UP, 0},
            };
            int axis, value, i;
            axis = event.jaxis.axis;
            value = event.jaxis.value;
            value = value > 0 ? 1 : value < 0 ? -1 : 0;

            for (i=0; i<6; i++) {
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
            int button, value, i;
            button = event.jbutton.button;
            value = event.jbutton.state;

            for (i=0; i<6; i++) {
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
                    break ;
                }

                joystick_name = SDL_JoystickName(joystick);

                if (SDL_JoystickNumAxes(joystick) != 2) {
                    SDL_Log("joystick does not have 2 axes, skipping: %s", joystick_name);
                    SDL_JoystickClose(joystick);
                    joystick_name = NULL;
                    joystick = NULL;
                    break ;
                }

                SDL_Log("joystick added: %s", joystick_name);
            }

            break;

        case SDL_JOYDEVICEREMOVED:
            if ((joystick) && (SDL_JoystickInstanceID(joystick) == event.jdevice.which)) {
                SDL_Log("joystick removed: %s", joystick_name);
                SDL_JoystickClose(joystick);
                joystick_name = NULL;
                joystick = NULL;
            }

            break;
        }
    }

    return 1;
}

