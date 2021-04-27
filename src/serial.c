#include "gb.h"
#include "hardware.h"

uint8_t serial_read_u8(uint16_t addr) {
    uint8_t res = 0xff;

    if (addr == rSB) {
        res = gb_mem[rSB];
    } else if (addr == rSC) {
        res = ((gb_mem[rSC] & 0x81) | 0x7e);
    }

    return res;
}

void serial_write_u8(uint16_t addr, uint8_t data) {
    if (addr == rSB) {
        gb_mem[rSB] = data;
    } else if (addr == rSC) {
        gb_mem[rSC] = data & 0x81;

        if ((gb_mem[rSC] & 0x81) == 0x81) {
            gb_mem[rSC] &= 1;
            gb_mem[rIF] |= IEF_SERIAL;
            gb_mem[rSB] = 0xff;
        }
    }
}
