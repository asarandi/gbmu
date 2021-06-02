#include "gb.h"
#include "hardware.h"

uint8_t serial_read_u8(struct gameboy *gb, uint16_t addr) {
    uint8_t res = 0xff;

    if (addr == rSB) {
        res = gb->memory[rSB];
    } else if (addr == rSC) {
        res = ((gb->memory[rSC] & 0x81) | 0x7e);
    }

    return res;
}

void serial_write_u8(struct gameboy *gb, uint16_t addr, uint8_t data) {
    if (addr == rSB) {
        gb->memory[rSB] = data;
    } else if (addr == rSC) {
        gb->memory[rSC] = data & 0x81;

        if ((gb->memory[rSC] & 0x81) == 0x81) {
            gb->memory[rSC] &= 1;
            gb->memory[rIF] |= IEF_SERIAL;
            gb->memory[rSB] = 0xff;
        }
    }
}
