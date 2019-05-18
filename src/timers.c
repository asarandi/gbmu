#include "gb.h"
#include <SDL.h>

void gb_throttle()
{
    static struct timespec tp, last_tp;
    static uint64_t clock_cycles, current_ms, last_ms;

    if (clock_gettime(CLOCK_REALTIME, &tp))
        return ;

    if (tp.tv_sec > last_tp.tv_sec)
        last_ms = 0;

    current_ms = tp.tv_nsec / 1000000;
    if (current_ms <= last_ms)
        return ;

    if ((state->cycles - clock_cycles) <= (current_ms - last_ms) * (4194304 / 1000))
        return ;

    last_ms = current_ms;
    memcpy(&last_tp, &tp, sizeof(struct timespec));
    clock_cycles = state->cycles;
    SDL_Delay(1);
}

void    timers_update(uint8_t *gb_mem, t_state *state, int current_cycles)
{
    static  uint8_t    tima, counter;
    static  uint64_t    f;
    static bool current, prev, overflow;
    uint8_t shifts[] = {9, 3, 5, 7};

    state->div_cycles += current_cycles;
    state->div_cycles &= 0xffff;
    gb_mem[0xff04] = state->div_cycles >> 8;

    f = gb_mem[0xff07] & 3;
    current = (state->div_cycles >> shifts[f]) & 1;
    current &= (gb_mem[0xff07] >> 2) & 1;

    if (overflow) {
        counter++;
        if ((tima != gb_mem[0xff05]) && (counter < 2))
            overflow = false ;
    }

    if (overflow) {
        gb_mem[0xff05] = gb_mem[0xff06];
        if (counter >= 2) {
            overflow = false;
            gb_mem[0xff0f] |= 4;
        }
    }

    if (!current && prev) {
        gb_mem[0xff05]++;
        if (!gb_mem[0xff05]) {
            overflow = true;
            counter = 0;
        }
    }
    prev = current;
    tima = gb_mem[0xff05];
}
