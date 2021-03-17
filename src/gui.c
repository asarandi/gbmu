#include <SDL.h>
#include "gb.h"

#define WND_WIDTH   160
#define WND_HEIGHT  144

static int gui_scale_factor = 3;

static SDL_Window      *gui_window;
static SDL_Renderer    *gui_renderer;
static SDL_Texture     *gui_buffer;

uint32_t        game_controls[]     = {SDLK_DOWN, SDLK_UP, SDLK_LEFT, SDLK_RIGHT, SDLK_RETURN, SDLK_RSHIFT, SDLK_z, SDLK_x};
uint32_t        num_game_controls   = sizeof(game_controls) / sizeof(uint32_t);

struct s_render_palette {
    uint32_t colors[4];
    char *name;
};

struct s_render_palette render_palettes[] = {
    {{0xffffff, 0xaaaaaa, 0x555555, 0x000000}, "classic"},
    {{0xe6e6e6, 0xb3b3b3, 0x737373, 0x333333}, "greys"},
    {{0xebdd77, 0xa1bc00, 0x0d8833, 0x004333}, "pea-soup"},
    {{0x9bbc0f, 0x8bac0f, 0x306230, 0x0f380f}, "wikipedia"},
    {{0xf8e3c4, 0xcc3495, 0x6b1fb1, 0x0b0630}, "spacehaze"},
    {{0xeefded, 0x9a7bbc, 0x2d757e, 0x001b2e}, "purpledawn"},
    {{0xe0f0e8, 0xa8c0b0, 0x507868, 0x183030}, "platinum"},
    {{0xd0d058, 0xa0a840, 0x708028, 0x405010}, "nostalgia"},
    {{0xf4fbd0, 0x68cf68, 0x1e9178, 0x05241f}, "lightgreen"},
    {{0xbeeb71, 0x6ab417, 0x376d03, 0x172808}, "harshgreens"},
    {{0xc4cfa1, 0x8b956d, 0x4d533c, 0x1f1f1f}, "dirtyboy"},
    {{0xeff9d6, 0xba5044, 0x7a1c4b, 0x1b0326}, "crimson"},
    {{0xd0f4f8, 0x70b0c0, 0x3c3468, 0x1c0820}, "blue-seni"},
    {{0xffffb5, 0x7bc67b, 0x6b8c42, 0x5a3921}, "links-awakening-sgb-2"},
    {{0xffe4c2, 0xdca456, 0xa9604c, 0x422936}, "gb-chocolate"},
    {{0xf7bef7, 0xe78686, 0x7733e7, 0x2c2c96}, "kirby-sgb-2"},
    {{0xe7e8f3, 0x8c83c3, 0x634d8f, 0x120b19}, "darkboy4"},
    {{0xaedf1e, 0xb62558, 0x2c1700, 0x047e60}, "metroid-ii-sgb-2"},
    {{0xcef7f7, 0xf78e50, 0x9e0000, 0x1e0000}, "kid-icarus-sgb-2"},
    {{0xeff7b6, 0xdfa677, 0x11c600, 0x000000}, "super-mario-land-2-sgb-2"},
    {{0xffffff, 0xb6b6b6, 0x676767, 0x000000}, "2-bit-grayscale"},
    {{0xe2f3e4, 0x94e344, 0x46878f, 0x332c50}, "kirokaze-gameboy"},
    {{0xf7e7c6, 0xd68e49, 0xa63725, 0x331e50}, "nintendo-super-gameboy"},
    {{0xe0f8d0, 0x88c070, 0x346856, 0x081820}, "nintendo-gameboy-bgb"},
    {{0xffefff, 0xf7b58c, 0x84739c, 0x181010}, "pokemon-sgb"},
    {{0xe0dbcd, 0xa89f94, 0x706b66, 0x2b2b26}, "grafxkid-gameboy-pocket-gray"},
    {{0xcecece, 0x6f9edf, 0x42678e, 0x102533}, "megaman-v-sgb"},
    {{0xfff6d3, 0xf9a875, 0xeb6b6f, 0x7c3f58}, "ice-cream-gb"},
    {{0xc4f0c2, 0x5ab9a8, 0x1e606e, 0x2d1b00}, "mist-gb"},
    {{0xedb4a1, 0xa96868, 0x764462, 0x2c2137}, "rustic-gb"},
    {{0xacb56b, 0x768448, 0x3f503f, 0x243137}, "nintendo-gameboy-arne"},
    {{0xfff5dd, 0xf4b26b, 0xb76591, 0x65296c}, "grapefruit"},
    {{0x7e8416, 0x577b46, 0x385d49, 0x2e463d}, "nintendo-gameboy-black-zero"},
    {{0xe3eec0, 0xaeba89, 0x5e6745, 0x202020}, "andrade-gameboy"},
    {{0xc4cfa1, 0x8b956d, 0x4d533c, 0x1f1f1f}, "pj-gameboy"},
    {{0xdbf4b4, 0xabc396, 0x7b9278, 0x4c625a}, "grafxkid-gameboy-pocket-green"},
    {{0xa1ef8c, 0x3fac95, 0x446176, 0x2c2137}, "nymph-gb"},
    {{0xebdd77, 0xa1bc00, 0x0d8833, 0x004333}, "gb-easy-greens"},
    {{0x8be5ff, 0x608fcf, 0x7550e8, 0x622e4c}, "wish-gb"}
};

#define num_render_palettes (sizeof(render_palettes) / sizeof(struct s_render_palette))

static unsigned int render_palette_idx = num_render_palettes * 0x10000 + 6;

void set_window_title()
{
    char *t, *s = render_palettes[render_palette_idx % num_render_palettes].name;
    char *title1 = "gbmu";
    char *title2 = "gbmu: ";
    if ((!s) || (!strlen(s))) {
        (void)SDL_SetWindowTitle(gui_window, title1);
        return ;
    }
    t = malloc(strlen(title2) + strlen(s) + 1);
    (void)strcpy(t, title2);
    (void)strcat(t, s);
    SDL_SetWindowTitle(gui_window, t);
    free(t);
}

void set_window_size()
{
    int width = WND_WIDTH * gui_scale_factor;
    int height = WND_HEIGHT * gui_scale_factor;

    if (gui_buffer)
        SDL_DestroyTexture(gui_buffer);
    SDL_SetWindowSize(gui_window, width, height);
    SDL_SetWindowPosition(gui_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    if ((gui_buffer = SDL_CreateTexture(gui_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height)) == NULL)
        SDL_Log("%s: could not create a texture: %s", "set_window_size()",  SDL_GetError());
}

bool gui_init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        printf("Failed to initialise SDL\n");
        return false;
    }
    if ((gui_window = SDL_CreateWindow("gbmu", 0, 0, WND_WIDTH, WND_HEIGHT, 0)) == NULL) {
        SDL_Log("Could not create a window: %s", SDL_GetError());
        return false;
    }
    if ((gui_renderer = SDL_CreateRenderer(gui_window, -1, SDL_RENDERER_ACCELERATED)) == NULL) {
        SDL_Log("Could not create a renderer: %s", SDL_GetError());
        return false;
    }

    set_window_title();
    set_window_size();
    SDL_RenderClear(gui_renderer);
    return true;
}

void gui_cleanup()
{
    SDL_DestroyTexture(gui_buffer);
    SDL_DestroyRenderer(gui_renderer);
    SDL_DestroyWindow(gui_window);
    SDL_Quit();
}

void gui_render()
{
    uint32_t    *pixels;
    int         pitch, idx, buf_y, buf_x, gui_y, gui_x;

    if (SDL_LockTexture(gui_buffer, NULL, (void *)&pixels, &pitch) < 0) {
        SDL_Log("Couldn't lock texture: %s\n", SDL_GetError());
        state->done = true;
    }
    for (buf_y = 0; buf_y < 144; buf_y++) {
        for (buf_x = 0; buf_x < 160; buf_x++) {
            idx = state->screen_buf[buf_y * 160 + buf_x];
            for (gui_y = buf_y * gui_scale_factor; gui_y < (buf_y + 1) * gui_scale_factor; gui_y++) {
                for (gui_x = buf_x * gui_scale_factor; gui_x < (buf_x + 1) * gui_scale_factor; gui_x++) {
                    pixels[gui_y * gui_scale_factor * WND_WIDTH + gui_x] =
                        render_palettes[render_palette_idx % num_render_palettes].colors[idx];
                }
            }
        }
    }
    SDL_UnlockTexture(gui_buffer);
    SDL_RenderClear(gui_renderer);
    SDL_RenderCopy(gui_renderer, gui_buffer, NULL, NULL);
    SDL_RenderPresent(gui_renderer);
}

void gui_set_button_states(uint32_t key, uint8_t value)
{
    uint32_t i;

    for (i=0; i < num_game_controls; i++) {
        if (game_controls[i] == key) {
            state->buttons[i] = value;
            joypad_request_interrupt();
        }
    }
}

void gui_update()
{
    int         i, tmp;
    SDL_Event   event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            state->done = true;
            break ;
        case SDL_KEYDOWN:
            gui_set_button_states(event.key.keysym.sym, 1);
            if (event.key.keysym.sym == SDLK_ESCAPE)
                state->done = true;

            tmp = gui_scale_factor;
            if (event.key.keysym.sym == SDLK_1)
                gui_scale_factor = 1;
            if (event.key.keysym.sym == SDLK_2)
                gui_scale_factor = 2;
            if (event.key.keysym.sym == SDLK_3)
                gui_scale_factor = 3;
            if (event.key.keysym.sym == SDLK_4)
                gui_scale_factor = 4;
            if (event.key.keysym.sym == SDLK_5)
                gui_scale_factor = 5;
            if (tmp != gui_scale_factor)
                set_window_size();

            if ((event.key.keysym.sym == SDLK_EQUALS) && (state->volume > 0))
                state->volume--;
            if ((event.key.keysym.sym == SDLK_MINUS) && (state->volume < 16))
                state->volume++;

            for (i=tmp=0; i<4; i++) {
                if (event.key.keysym.sym == (int[]) {
                SDLK_u, SDLK_i, SDLK_o, SDLK_p
            }[i]) {
                    state->sound_channels[i] ^= 1;
                    tmp = 1;
                }
            }

            for (i=0; tmp && i<4; i++) {
                printf("nr%d [%s]%s", i + 1,
                       state->sound_channels[i] ? "on" : "off",
                       i + 1 < 4 ? ", " : "\n");
            }

            if (event.key.keysym.sym == SDLK_q)
                render_palette_idx--;
            if (event.key.keysym.sym == SDLK_w)
                render_palette_idx++;
            if ((event.key.keysym.sym == SDLK_q) || (event.key.keysym.sym == SDLK_w))
                set_window_title();
            break ;
        case SDL_KEYUP:
            gui_set_button_states(event.key.keysym.sym, 0);
            break ;
        }
    }
}

void gb_throttle()
{
    static struct timespec tp, last_tp;
    static unsigned int clock_cycles, current_ms, last_ms;

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
    SDL_Delay(1);
}
