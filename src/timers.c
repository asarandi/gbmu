#include "gb.h"
#include "hardware.h"

void timers_update(uint8_t *gb_mem, t_state *state, int current_cycles) {
    static uint8_t tima, counter;
    static bool current, prev, overflow;
    uint8_t shifts[] = {9, 3, 5, 7};
    int f;
    state->div_cycles += current_cycles;
    state->div_cycles &= 0xffff;
    gb_mem[rDIV] = state->div_cycles >> 8;
    f = gb_mem[rTAC] & 3;
    current = (state->div_cycles >> shifts[f]) & 1;
    current &= (gb_mem[rTAC] >> 2) & 1;

    if (overflow) {
        counter++;

        if ((tima != gb_mem[rTIMA]) && (counter == 1)) {
            overflow = false;
        }
    }

    if (overflow) {
        gb_mem[rTIMA] = gb_mem[rTMA];

        if (counter == 1) {
            gb_mem[rIF] |= IEF_TIMER;
        }

        if (counter > 1) {
            overflow = false;
        }
    }

    if (!current && prev) {
        gb_mem[rTIMA]++;

        if (!gb_mem[rTIMA]) {
            overflow = true;
            counter = 0;
        }
    }

    prev = current;
    tima = gb_mem[rTIMA];
}
