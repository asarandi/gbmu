#include "gb.h"

void    joypad_request_interrupt()
{
    uint8_t *gb_mem = state->gameboy_memory;
    gb_mem[0xff0f] |= 0x10;
}

uint8_t    joypad_read()
{
    uint8_t *gb_mem = state->gameboy_memory;
    uint8_t joypad = gb_mem[0xff00];

    if ((joypad & 0x10) == 0) {
        for (int i = 0; i < 4; i++) {
            int val = (state->buttons[i] & 1) ^ 1;
            joypad &=  ~(1 << (3 - i));
            joypad |= val << (3 - i);
        }
    }

    if ((joypad & 0x20) == 0) {
        for (int i = 0; i < 4; i++) {
            int val = (state->buttons[i + 4] & 1) ^ 1;
            joypad &=  ~(1 << (3 - i));
            joypad |= val << (3 - i);
        }
    }
    gb_mem[0xff00] = joypad;
    return joypad;
}
