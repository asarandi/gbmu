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

// send/receive 1 bit every 512 clock cycles
int serial_update(struct gameboy *gb) {
    int bitflip = (gb->serial_cycles & (1 << 9)) !=
                  ((gb->serial_cycles + 4) & (1 << 9));
    gb->serial_cycles += 4;

    if ((bitflip) && ((gb->memory[rSC] & 0x81) == 0x81)) {
        gb->memory[rSB] <<= 1; // send
        gb->memory[rSB] |= 1; // receive
        gb->serial_ctr = (gb->serial_ctr + 1) & 7;

        if (!gb->serial_ctr) {
            gb->memory[rSC] &= 1;
            gb->memory[rIF] |= IEF_SERIAL;
        }
    }

    return (gb->memory[rSC] & 0b10000000) != 0;
}

void serial_write_u8(struct gameboy *gb, uint16_t addr, uint8_t data) {
    if (addr == rSB) {
        gb->memory[rSB] = data;
    } else if (addr == rSC) {
        gb->memory[rSC] = data & 0x81;

        if ((gb->memory[rSC] & 0x81) == 0x81) {
            gb->serial_ctr = 0;
        }
    }
}
