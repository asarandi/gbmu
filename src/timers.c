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
    static  uint64_t    div_cycles;
    static  uint64_t    tac_cycles;
    static  uint64_t    f;
    uint8_t shifts[] = {10, 4, 6, 8};


    (void)state;

    if (state->cycles >> 8 != div_cycles)
    {
        div_cycles = state->cycles >> 8;
        gb_mem[0xff04]++;
    }

    if (!(gb_mem[0xff07] & 4))
        return ;
    if (f != (gb_mem[0xff07] & 3))
        f = gb_mem[0xff07] & 3;
    if (state->cycles >> shifts[f] == tac_cycles)
        return ;
    tac_cycles = state->cycles >> shifts[f];
    gb_mem[0xff05]++;
    if (gb_mem[0xff05])
        return ;
    gb_mem[0xff05] = gb_mem[0xff06];
    gb_mem[0xff0f] |= 4;
}
