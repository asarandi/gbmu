#include <SDL2/SDL.h>
#include <stdbool.h>
#include "gb.h"

#define WND_WIDTH   160
#define WND_HEIGHT  144
#define SCALE_FACTOR 3

void *gui(void *arg)
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    SDL_Texture *buffer;
    uint32_t *pixels;
    uint8_t *screen_buf;
    int pitch;
    int idx;
    uint32_t    colors[] = {0xffffffff, 0xaaaaaaff, 0x555555ff, 0x000000ff};
//    uint32_t colors[] = {0xe6e6e6ff, 0xb3b3b3ff, 0x737373ff, 0x333333ff};         /*shades of grey*/
//    uint32_t colors[] = {0x9bbc0fff, 0x8bac0fff, 0x306230ff, 0x0f380fff};         /*shades of green*/
//    uint32_t colors[] = {0xebdd77ff, 0xa1bc00ff, 0x0d8833ff, 0x004333ff};         /*green-beige*/

    struct s_state *state = arg;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Failed to initialise SDL\n");
        return NULL;
    }

    window = SDL_CreateWindow("gbmu",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          WND_WIDTH * SCALE_FACTOR,
                                          WND_HEIGHT * SCALE_FACTOR,
                                          0);
    if (window == NULL)
    {
        SDL_Log("Could not create a window: %s", SDL_GetError());
        return NULL;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        SDL_Log("Could not create a renderer: %s", SDL_GetError());
        return NULL;
    }
    buffer = SDL_CreateTexture(renderer,
                           SDL_PIXELFORMAT_RGBA8888,
                           SDL_TEXTUREACCESS_STREAMING, 
                           WND_WIDTH * SCALE_FACTOR,
                           WND_HEIGHT * SCALE_FACTOR);
    while (true)
    {
        
#ifdef __linux__        
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                break;
        }
#endif

        SDL_LockTexture(buffer, NULL, (void *)&pixels, &pitch);
        for (int y0=0;y0<144;y0++){
            for (int x0=0;x0<160;x0++){
                idx = (int)state->screen_buf[y0*160+x0];
                for (int y1=y0*SCALE_FACTOR; y1<(y0+1)*SCALE_FACTOR;y1++) {
                    for (int x1=x0*SCALE_FACTOR; x1<(x0+1)*SCALE_FACTOR;x1++) {
                        pixels[y1*SCALE_FACTOR*WND_WIDTH+x1] = colors[idx];
                    }
                }
            }
        }

        SDL_UnlockTexture(buffer);
        SDL_RenderCopy(renderer, buffer, NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_Delay(100);        
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return NULL;
}
