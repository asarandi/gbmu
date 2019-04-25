#include "gb.h"

void    timers_update(uint8_t *gb_mem, t_state *state, int current_cycles)
{
    static  uint16_t    div;
    static  uint64_t    cycles;
    static  uint64_t    freq = 1024;

    (void)state;

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

void delay()
{
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = 1000000000L / 30;

    struct timespec tz;
    tz.tv_sec = 0;
    tz.tv_nsec = 1000000000L / 30;
    (void)nanosleep(&ts, &tz);
}
