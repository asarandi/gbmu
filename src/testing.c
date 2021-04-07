#include "gb.h"
#include "hardware.h"
#include <time.h>
#include <ctype.h>

#define TIMEOUT        10
#define RESULT_SUCCESS 10
#define RESULT_FAILURE 11
#define RESULT_TIMEOUT 12
#define RESULT_ERROR   13

void default_run_hook();
void blargg1_write_hook(uint16_t, uint8_t);
void blargg2_run_hook();
void blargg2_write_hook(uint16_t, uint8_t);
void mooneye_write_hook(uint16_t, uint8_t);

int testing_setup(char *s) {
    struct test {
        char *name;
        void (*run)();
        void (*write)(uint16_t, uint8_t);
    } tests[] = {
        {"blargg1", &default_run_hook, &blargg1_write_hook},
        {"blargg2", &blargg2_run_hook, &blargg2_write_hook},
        {"mooneye", &default_run_hook, &mooneye_write_hook},
    };

    for (int i = 0; i < 3; i++) {
        if (!strcasecmp(s, tests[i].name)) {
            state->testing_run_hook = tests[i].run;
            state->testing_write_hook = tests[i].write;
            state->testing = 1;
            state->exit_code = -1;
            return 1;
        }
    }

    (void)fprintf(stderr, "test not found: %s\n", s);
    return 0;
}

void default_run_hook() {
    if (!state->testing) {
        return ;
    }

    static struct timespec start;
    static int f;

    if (!f++) {
        if ((clock_gettime(CLOCK_REALTIME, &start)) != 0) {
            perror(__func__);
            state->done = 1;
            state->exit_code = RESULT_ERROR;
        }
    } else {
        struct timespec ts;

        if ((clock_gettime(CLOCK_REALTIME, &ts)) != 0) {
            perror(__func__);
            state->done = 1;
            state->exit_code = RESULT_ERROR;
        } else {
            if (ts.tv_sec > start.tv_sec + TIMEOUT) {
                state->exit_code = RESULT_TIMEOUT;
                state->done = 1;
            }
        }
    }
}

void mooneye_write_hook(uint16_t addr, uint8_t data) {
    uint8_t success[] = {3, 5, 8, 13, 21, 34};
    uint8_t failure[] = {66, 66, 66, 66, 66, 66};
    static int i;

    if (!state->testing) {
        return;
    }

    if (!((addr == rSC) && ((data & 0x81) == 0x81))) {
        return;
    }

    if (gb_mem[rSB] == success[i]) {
        if (++i == 6) {
            state->exit_code = RESULT_SUCCESS;
            state->done = 1;
        }
    } else if (gb_mem[rSB] == failure[i]) {
        if (++i == 6) {
            state->exit_code = RESULT_FAILURE;
            state->done = 1;
        }
    } else {
        i = 0;
    }
}

void blargg1_write_hook(uint16_t addr, uint8_t data) {
    uint8_t passed[] = {'P', 'a', 's', 's', 'e', 'd'};
    uint8_t failed[] = {'F', 'a', 'i', 'l', 'e', 'd'};
    static int i;

    if (!state->testing) {
        return;
    }

    if (!((addr == rSC) && ((data & 0x81) == 0x81))) {
        return;
    }

    (void)fprintf(stderr, "%c", gb_mem[rSB]);
    (void)fflush(stderr);

    if (gb_mem[rSB] == passed[i]) {
        if (++i == 6) {
            state->exit_code = RESULT_SUCCESS;
            state->done = 1;
        }
    } else if (gb_mem[rSB] == failed[i]) {
        if (++i == 6) {
            state->exit_code = RESULT_FAILURE;
            state->done = 1;
        }
    } else {
        i = 0;
    }
}

void blargg2_run_hook() {
    if (!state->testing) {
        return;
    }
}

// should work for: oam_bug, mem_timing-2, dmg_sound, cgb_sound
void blargg2_write_hook(uint16_t addr, uint8_t data) {
    const uint8_t sig[] = {0xde, 0xb0, 0x61};
    char *res = (char *)&gb_mem[_SRAM + 4];
    static int f;

    if (!state->testing) {
        return;
    }

    if ((addr >= _SRAM) && (addr < _RAM)) {
        gb_mem[addr] = data;
    }

    if (memcmp((const void *)&gb_mem[_SRAM + 1], sig, 3)) {
        return;
    }

    if (gb_mem[_SRAM] == 0x80) {
        f = 1;
    } else if (f) {
        state->done = 1;
        fprintf(stderr, "%s", res);

        if (strstr(res, "Failed")) {
            state->exit_code = RESULT_FAILURE;
        } else if (strstr(res, "Passed")) {
            state->exit_code = RESULT_SUCCESS;
        } else {
            state->exit_code = RESULT_ERROR;
        }
    }
}
