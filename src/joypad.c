#include "gb.h"
#include "hardware.h"

void joypad_request_interrupt() {
    gb_mem[rIF] |= IEF_HILO;
}

uint8_t joypad_read() {
    uint8_t i, offset, bit, res;
    res = gb_mem[rP1];
    offset = (res & P1F_GET_BTN) == 0 ? 0 : 4;

    for (i = 0; i < 4; i++) {
        bit = (state->buttons[i + offset] & 1) ^ 1;
        res &= ~(1 << (3 - i));
        res |= bit << (3 - i);
    }

    gb_mem[rP1] = res;
    return res;
}

void joypad_write(uint8_t data) {
    gb_mem[rP1] = (gb_mem[rP1] & 15) | (data & 48);
}
