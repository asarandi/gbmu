#include "gb.h"
#include "hardware.h"

void timer_write_u8(struct gameboy *gb, uint16_t addr, uint8_t data) {
    /* reset DIV if written to */
    if (addr == rDIV) {
        gb->div_cycles = 0;
        data = 0;
    }

    /* TAC bottom 3 bits only */
    if (addr == rTAC) {
        data = 0xf8 | (data & 7);
    }

    gb->memory[addr] = data;
}

uint8_t timer_read_u8(struct gameboy *gb, uint16_t addr) {
    return gb->memory[addr];
}

int timer_update(struct gameboy *gb) {
    const uint32_t current_cycles = 4;
    static uint8_t tima, counter;
    static bool current, prev, overflow;
    uint8_t shifts[] = {9, 3, 5, 7};
    int f, bitflip;
    bitflip = ((gb->div_cycles & (1 << 13)) !=
               ((gb->div_cycles + current_cycles) & (1 << 13)));
    gb->div_cycles += current_cycles;
    gb->div_cycles &= 0xffff;
    gb->memory[rDIV] = gb->div_cycles >> 8;
    f = gb->memory[rTAC] & 3;   // tac.freq
    current = (gb->div_cycles >> shifts[f]) & 1;
    current &= (gb->memory[rTAC] >> 2) & 1; // tac.enable

    if (overflow) {
        counter++;

        if ((tima != gb->memory[rTIMA]) && (counter == 1)) {
            overflow = false;
        }
    }

    if (overflow) {
        gb->memory[rTIMA] = gb->memory[rTMA];

        if (counter == 1) {
            gb->memory[rIF] |= IEF_TIMER;
        }

        if (counter > 1) {
            overflow = false;
        }
    }

    if (!current && prev) {
        gb->memory[rTIMA]++;

        if (!gb->memory[rTIMA]) {
            overflow = true;
            counter = 0;
        }
    }

    prev = current;
    tima = gb->memory[rTIMA];
    return bitflip;
}
