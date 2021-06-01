#include "gb.h"
#include "hardware.h"

void joypad_request_interrupt(struct gameboy *gb) {
    gb->memory[rIF] |= IEF_HILO;
}

uint8_t joypad_read(struct gameboy *gb) {
    uint8_t i, res;
    res = (gb->memory[rP1] & 0x30) | (~0x30);

    if ((res & 0x30) == P1F_GET_DPAD) {
        for (i = 0; i < 4; i++) {
            res ^= ((gb->buttons[i] & 1) << (3 - i));
        }
    } else if ((res & 0x30) == P1F_GET_BTN) {
        for (i = 0; i < 4; i++) {
            res ^= ((gb->buttons[i + 4] & 1) << (3 - i));
        }
    }

    return res;
}

void joypad_write(struct gameboy *gb, uint8_t data) {
    gb->memory[rP1] = data & 0b00110000;
}
