#include "gb.h"
#include "timer.h"
#include "hardware.h"

static const int timer_freq[] = {9, 3, 5, 7};

// updates div, returns true if tac enabled and appropriate bit goes 1 => 0
static int is_timer_tick(struct gameboy *gb, uint16_t new_div) {
    int tick = (gb->timer.tac & TACF_START) &&
               (_IS_FALLING_EDGE(timer_freq[gb->timer.tac & 3], gb->timer.div, new_div));
    gb->timer.div = new_div;
    return tick;
}

uint8_t timer_read_u8(struct gameboy *gb, uint16_t addr) {
    switch (addr) {
    case rDIV:
        return gb->timer.div >> 8;

    case rTIMA:
        return gb->timer.tima;

    case rTMA:
        return gb->timer.tma;

    case rTAC:
        return 0b11111000 | (gb->timer.tac & 7);
    }

    return 0xff;
}

void timer_write_u8(struct gameboy *gb, uint16_t addr, uint8_t data) {
    switch (addr) {
    case rDIV:
        if (is_timer_tick(gb, 0)) {
            if (!(++gb->timer.tima)) {
                gb->timer.tima = gb->timer.tma;
                gb->memory[rIF] |= IEF_TIMER;
            }
        }

        break ;

    case rTIMA:
        if (gb->timer.is_overflow) {
            gb->timer.is_overflow = 0;
        }

        if (!gb->timer.was_overflow) {
            gb->timer.tima = data;
        }

        break ;

    case rTMA:
        gb->timer.tma = data;

        if (gb->timer.was_overflow) {
            gb->timer.tima = data;
        }

        break ;

    case rTAC:
        if ((gb->timer.tac & TACF_START) && (!(data & TACF_START)) &&
                (gb->timer.div & (1 << (timer_freq[gb->timer.tac & 3])))) {
            if (!(++gb->timer.tima)) {
                gb->timer.tima = gb->timer.tma;
                gb->memory[rIF] |= IEF_TIMER;
            }
        }

        gb->timer.tac = data & 7;
        break ;
    }
}

int timer_update(struct gameboy *gb) {
    const int cycles = 4;
    int bitflip;

    if (gb->timer.is_overflow) {
        gb->timer.tima = gb->timer.tma;
        gb->memory[rIF] |= IEF_TIMER;
    }

    gb->timer.was_overflow = gb->timer.is_overflow;
    gb->timer.is_overflow = 0;
    bitflip = _IS_BITFLIP(13, gb->timer.div, gb->timer.div + cycles);

    if (is_timer_tick(gb, gb->timer.div + cycles)) {
        gb->timer.is_overflow = !(++gb->timer.tima);
    }

    return bitflip;
}
