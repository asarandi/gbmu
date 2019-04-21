#include <SDL2/SDL.h>
#include "gb.h"

#define WND_WIDTH   160
#define WND_HEIGHT  144
#define SCALE_FACTOR 3

/*
 * delay in milliseconds
*/
#define GUI_DELAY_DURATION	15

SDL_Window      *gui_window;
SDL_Renderer    *gui_renderer;
SDL_Texture     *gui_buffer;

/*
 Bit 3 - P13 Input Down  or Start    (0=Pressed) (Read Only)
 Bit 2 - P12 Input Up    or Select   (0=Pressed) (Read Only)
 Bit 1 - P11 Input Left  or Button B (0=Pressed) (Read Only)
 Bit 0 - P10 Input Right or Button A (0=Pressed) (Read Only)
*/

uint32_t        game_controls[]     = {SDLK_DOWN, SDLK_UP, SDLK_LEFT, SDLK_RIGHT, SDLK_RETURN, SDLK_RSHIFT, SDLK_x, SDLK_z};
uint32_t        num_game_controls   = sizeof(game_controls) / sizeof(uint32_t);
uint32_t        gui_colors[]        = {0xffffffff, 0xaaaaaaff, 0x555555ff, 0x000000ff};        /*classic*/
//uint32_t        gui_colors[] = {0xe6e6e6ff, 0xb3b3b3ff, 0x737373ff, 0x333333ff};        /*shades of grey*/
//uint32_t        gui_colors[] = {0x9bbc0fff, 0x8bac0fff, 0x306230ff, 0x0f380fff};        /*shades of green*/
//uint32_t        gui_colors[] = {0xebdd77ff, 0xa1bc00ff, 0x0d8833ff, 0x004333ff};        /*green-beige*/


bool
gui_init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Failed to initialise SDL\n");
        return false;
    }
    if ((gui_window = SDL_CreateWindow("gbmu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WND_WIDTH * SCALE_FACTOR, WND_HEIGHT * SCALE_FACTOR, 0)) == NULL) {
        SDL_Log("Could not create a window: %s", SDL_GetError());
        return false;
    }
    if ((gui_renderer = SDL_CreateRenderer(gui_window, -1, SDL_RENDERER_ACCELERATED)) == NULL) {
        SDL_Log("Could not create a renderer: %s", SDL_GetError());
        return false;
    }
    if ((gui_buffer = SDL_CreateTexture(gui_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WND_WIDTH * SCALE_FACTOR, WND_HEIGHT * SCALE_FACTOR)) == NULL) {
        SDL_Log("Could not create a texture: %s", SDL_GetError());
        return false;
    }

    SDL_RenderClear(gui_renderer);
    return true;
}

void
gui_cleanup() {
    SDL_DestroyTexture(gui_buffer);
    SDL_DestroyRenderer(gui_renderer);
    SDL_DestroyWindow(gui_window);
    SDL_Quit();
}

void
gui_render() {
    uint32_t    *pixels;
    int         pitch, idx;

    if (SDL_LockTexture(gui_buffer, NULL, (void *)&pixels, &pitch) < 0) {
        SDL_Log("Couldn't lock texture: %s\n", SDL_GetError());
        state->done = true;
    }
    for (int buf_y = 0; buf_y < 144; buf_y++) {
        for (int buf_x = 0; buf_x < 160; buf_x++) {
            idx = state->screen_buf[buf_y * 160 + buf_x];
            for (int gui_y = buf_y * SCALE_FACTOR; gui_y < (buf_y + 1) * SCALE_FACTOR; gui_y++) {
                for (int gui_x = buf_x * SCALE_FACTOR; gui_x < (buf_x + 1) * SCALE_FACTOR; gui_x++) {
                    pixels[gui_y * SCALE_FACTOR * WND_WIDTH + gui_x] = gui_colors[idx];
                }
            }
        }
    }
    SDL_UnlockTexture(gui_buffer);
}

void
gui_set_button_states(uint32_t key, uint8_t value) {
    for (int i=0; i < num_game_controls; i++) {
        if (game_controls[i] == key) {
            state->buttons[i] = value;
            joypad_request_interrupt();
        }
    }
}

void
gui_update() {
    SDL_Event   event;

    gui_render();
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                state->done = true;
                break ;
            case SDL_KEYDOWN:
                gui_set_button_states(event.key.keysym.sym, 1);
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    state->done = true;
                break ;
            case SDL_KEYUP:
                gui_set_button_states(event.key.keysym.sym, 0);
                break ;
        }
    }
    SDL_RenderClear(gui_renderer);
    SDL_RenderCopy(gui_renderer, gui_buffer, NULL, NULL);
    SDL_RenderPresent(gui_renderer);
    SDL_Delay(GUI_DELAY_DURATION);
}
