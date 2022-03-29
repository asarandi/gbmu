#include <SDL2/SDL.h>
#include "gb.h"
#include "hardware.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *texture = NULL;

int video_open(struct gameboy *gb) {
    (void)gb;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK) != 0) {
        SDL_Log("SDL_Init(): %s", SDL_GetError());
        return 0;
    }

    window = SDL_CreateWindow("gbmu", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, SCRN_X * 3, SCRN_Y * 3, 0);

    if (!window) {
        SDL_Log("SDL_CreateWindow(): %s", SDL_GetError());
        return 0;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);

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
    uint32_t palette[] = {0xffffff, 0xaaaaaa, 0x555555, 0x000000};
    uint32_t *pixels, px;
    int pitch, y, x;
    (void)size;

    if (gb->screenshot) {
        screenshot(gb, "screenshot.png");
        gb->screenshot = false;
    }

    if (gb->testing) {
        return 1;
    }

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
