#include "gb.h"
#include "hardware.h"

void joypad_request_interrupt() {
    gb_mem[rIF] |= IEF_HILO;
}

uint8_t joypad_read() {
    uint8_t i, res;
    res = (gb_mem[rP1] & 0x30) | (~0x30);

    if ((res & 0x30) == P1F_GET_DPAD) {
        for (i = 0; i < 4; i++) {
            res ^= ((state->buttons[i] & 1) << (3 - i));
        }
    } else if ((res & 0x30) == P1F_GET_BTN) {
        for (i = 0; i < 4; i++) {
            res ^= ((state->buttons[i + 4] & 1) << (3 - i));
        }
    }

    return res;
}

void joypad_write(uint8_t data) {
    gb_mem[rP1] = data & 0b00110000;
}
