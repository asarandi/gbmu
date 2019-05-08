#include "gb.h"
#include <SDL.h>

void gb_delay()
{
    static struct timespec tp, tp0, tp1, last_tp;
    static uint64_t clock_cycles, cc0, current_ms, last_ms;


    if (clock_gettime(CLOCK_REALTIME, &tp))
        return ;

    if (tp.tv_sec != tp0.tv_sec)
    {
        printf("clock cycles per second = %u, sec = %u, nsec = %u\n", state->cycles - cc0, tp.tv_sec, tp.tv_nsec);
        cc0 = state->cycles;
        tp0.tv_sec = tp.tv_sec;
    }

    if (tp.tv_sec > last_tp.tv_sec)
        last_ms = 0;

    current_ms = tp.tv_nsec / 1000000;
    if (current_ms <= last_ms)
        return ;

    uint64_t time_units = current_ms - last_ms;
    uint64_t clk = state->cycles - clock_cycles;

    if (clk <= time_units * 4194)
        return ;
/*
    if (state->cycles < clock_cycles + 4194 + 2500)
        return ;
*/
    last_ms = current_ms;
    memcpy(&last_tp, &tp, sizeof(struct timespec));
    clock_cycles = state->cycles;
//    tp1.tv_sec = 0;
//    tp1.tv_nsec = 1000000;
//    nanosleep(&tp1, NULL);
    SDL_Delay(1);
}


void    timers_update(uint8_t *gb_mem, t_state *state, int current_cycles)
{
    static  uint16_t    div;
    static  uint64_t    cycles;
    static  uint64_t    freq = 1024;

    (void)state;

    gb_delay();

    div = (gb_mem[0xff04] << 8) | gb_mem[0xff03];
    div += current_cycles;
    gb_mem[0xff04] = div >> 8;
    gb_mem[0xff03] = div & 0xff;

    if ((gb_mem[0xff07] & 0x04) == 0) { //timer disabled
        cycles = 0;
        return ;
    }

    switch (gb_mem[0xff07] & 0x03) {
        case 0: {
            if (freq != 1024) cycles = 0;
            freq = 1024;
            break ;
        }
        case 1: {
            if (freq != 16) cycles = 0;
            freq = 16;
            break ;
        }
        case 2: {
            if (freq != 64) cycles = 0;
            freq = 64;
            break ;
        }
        case 3: {
            if (freq != 256) cycles = 0;
            freq = 256;
            break ;
        }
    }

    cycles += current_cycles;
    if (cycles > freq) {
        cycles %= freq;
        gb_mem[0xff05]++;
        
        if (gb_mem[0xff05] == 0) {
            gb_mem[0xff05] = gb_mem[0xff06];
            gb_mem[0xff0f] |= 4; 
        }
    }
}
