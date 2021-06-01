#include "gb.h"
#include "hardware.h"

void timers_update(struct gameboy *gb) {
    const uint32_t current_cycles = 4;
    static uint8_t tima, counter;
    static bool current, prev, overflow;
    uint8_t shifts[] = {9, 3, 5, 7};
    int f;
    gb->div_cycles += current_cycles;
    gb->div_cycles &= 0xffff;
    gb->memory[rDIV] = gb->div_cycles >> 8;
    f = gb->memory[rTAC] & 3;
    current = (gb->div_cycles >> shifts[f]) & 1;
    current &= (gb->memory[rTAC] >> 2) & 1;

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
}
