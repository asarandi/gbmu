#include "gb.h"
#include "hardware.h"
#include <time.h>

#define TIMEOUT 10

// test exit codes
//   10: success/pass
//   11: failure
//   12: timeout
//   13: error

void testing_run_hook() {
    if (!state->testing) {
        return ;
    }

    static struct timespec start;
    static int f;

    if (!f++) {
        if ((clock_gettime(CLOCK_REALTIME, &start)) != 0) {
            perror(__func__);
            state->done = 1;
            state->exit_code = 13;
        }
    } else {
        struct timespec ts;

        if ((clock_gettime(CLOCK_REALTIME, &ts)) != 0) {
            perror(__func__);
            state->done = 1;
            state->exit_code = 13;
        } else {
            if (ts.tv_sec > start.tv_sec + TIMEOUT) {
                state->exit_code = 12;
                state->done = 1;
            }
        }
    }
}

void testing_write_hook(uint16_t addr, uint8_t data) {
    if (!state->testing) {
        return;
    }

    static uint8_t ct, s, success[] = {3, 5, 8, 13, 21, 34};
    static uint8_t f, failure[] = {0x42, 0x42, 0x42, 0x42, 0x42, 0x42};

    if ((addr == rSC) && ((data & 0x81) == 0x81)) {
        // mooneye passing
        if ((s == ct) && (gb_mem[rSB] == success[s])) {
            if (++s == 6) {
                state->exit_code = 10;
                state->done = 1;
            }

            // mooneye failing
        } else if ((f == ct) && (gb_mem[rSB] == failure[f])) {
            if (++f == 6) {
                state->exit_code = 11;
                state->done = 1;
            }

            // blargg
        } else {
            (void)fprintf(stderr, "%c", gb_mem[rSB]);
            (void)fflush(stderr);
        }

        ++ct;
        return;
    }

    // some blargg tests write to 0xa004
    if ((addr >= _SRAM) && (addr < _RAM)) {
        gb_mem[addr] = data;
    }

    const uint8_t sig[] = {0xde, 0xb0, 0x61};
    static uint16_t b, i = _SRAM + 4;
    b |= !memcmp((const void *)&gb_mem[_SRAM + 1], sig, 3);

    while ((b) && (gb_mem[i])) {
        (void)fprintf(stderr, "%c", gb_mem[i++]);
        (void)fflush(stderr);
    }
}
