#include "gb.h"
#include "hardware.h"

static inline uint8_t normalize(uint8_t value) {
    value &= (value & PADF_DOWN) ? ~PADF_UP : 255;
    value &= (value & PADF_LEFT) ? ~PADF_RIGHT : 255;
    return value;
}

uint8_t joypad_get_buttons(struct gameboy *gb) {
    return gb->buttons;
}

void joypad_set_buttons(struct gameboy *gb, uint8_t new_value) {
    if (normalize(gb->buttons) != normalize(new_value)) {
        gb->memory[rIF] |= IEF_HILO;
    }

    gb->buttons = new_value;
}

uint8_t joypad_read_u8(struct gameboy *gb, uint16_t addr) {
    (void)addr;
    uint8_t value, res;
    value = normalize(gb->buttons);
    res = (gb->memory[rP1] & 0x30) | (~0x30);

    if ((res & 0x30) == P1F_GET_DPAD) {
        res = (res & 0xf0) | (~((value >> 4) & 0xf));
    } else if ((res & 0x30) == P1F_GET_BTN) {
        res = (res & 0xf0) | (~(value & 0xf));
    }

    return res;
}

void joypad_write_u8(struct gameboy *gb, uint16_t addr, uint8_t data) {
    (void)addr;
    gb->memory[rP1] = data & 0b00110000;
}
