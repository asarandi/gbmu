#ifndef TIMER_H
# define TIMER_H

#include <stdbool.h>
#include <stdint.h>

struct timer {
    uint16_t div;
    uint8_t tima, tma, tac;
    bool is_overflow, was_overflow;
};

#define _IS_BITFLIP(B,M,N) (((M) & (1 << (B))) != ((N) & (1 << (B))))
#define _IS_RISING_EDGE(B,M,N) ((!((M) & (1 << (B)))) && ((N) & (1 << (B))))
#define _IS_FALLING_EDGE(B,M,N) (((M) & (1 << (B))) && (!((N) & (1 << (B)))))

#endif
