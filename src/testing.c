#include "gb.h"
#include "hardware.h"
#include <time.h>
#include <ctype.h>

#define TIMEOUT        15
#define RESULT_SUCCESS 10
#define RESULT_FAILURE 11
#define RESULT_TIMEOUT 12
#define RESULT_ERROR   13

void default_run_hook(struct gameboy *);
void blargg1_write_hook(struct gameboy *, uint16_t, uint8_t);
void blargg2_run_hook(struct gameboy *);
void blargg2_write_hook(struct gameboy *, uint16_t, uint8_t);
void mooneye_write_hook(struct gameboy *,uint16_t, uint8_t);
void screenshot_run_hook(struct gameboy *);
void mealybug_run_hook(struct gameboy *);
void screenshot_write_hook(struct gameboy *, uint16_t, uint8_t);

int testing_setup(struct gameboy *gb, char *test_name) {
    struct test {
        char *name;
        void (*run)(struct gameboy *);
        void (*write)(struct gameboy *, uint16_t, uint8_t);
    } tests[] = {
        {"blargg1", &default_run_hook, &blargg1_write_hook},
        {"blargg2", &blargg2_run_hook, &blargg2_write_hook},
        {"mooneye", &default_run_hook, &mooneye_write_hook},
        {"screenshot", &screenshot_run_hook, &screenshot_write_hook},
        {"mealybug", &mealybug_run_hook, &screenshot_write_hook},
    };

    for (int i = 0; i < 5; i++) {
        if (!strcasecmp(test_name, tests[i].name)) {
            gb->testing_run_hook = tests[i].run;
            gb->testing_write_hook = tests[i].write;
            gb->testing = 1;
            gb->exit_code = -1;
            return 1;
        }
    }

    (void)fprintf(stderr, "test not found: %s\n", test_name);
    return 0;
}

void screenshot_and_exit(struct gameboy *gb, char *exten) {
    char *fn = replace_exten(gb->rom_file, exten);
    screenshot(gb, fn);
    free(fn);
    fn = NULL;
    gb->exit_code = 0;
    gb->done = 1;
}

void screenshot_run_hook(struct gameboy *gb) {
    if (!gb->testing) {
        return ;
    }

    if ((gb->cycles >= (40 * 4194304)) && (gb->video_render)) {
        (void)screenshot_and_exit(gb, "-1.png");
    }

    if (gb->cycles >= (41 * 4194304)) {
        (void)printf("timeout: %s\n,", gb->rom_file);
        (void)fflush(stdout);
        gb->exit_code = RESULT_TIMEOUT;
        gb->done = 1;
    }
}

void mealybug_run_hook(struct gameboy *gb) {
    if (!gb->testing) {
        return ;
    }

    if (gb->cpu.opcode == 0x40) { // LD B,B
        (void)screenshot_and_exit(gb, "-gbmu.png");
    }
}

void screenshot_write_hook(struct gameboy *gb, uint16_t addr, uint8_t data) {
    (void)addr;
    (void)data;

    if (!gb->testing) {
        return ;
    }
}

void default_run_hook(struct gameboy *gb) {
    static time_t start;

    if (!gb->testing) {
        return ;
    }

    if (!start) {
        start = time(NULL);
    } else if (time(NULL) > start + TIMEOUT) {
        gb->exit_code = RESULT_TIMEOUT;
        gb->done = 1;
    }
}

void mooneye_write_hook(struct gameboy *gb, uint16_t addr, uint8_t data) {
    uint8_t success[] = {3, 5, 8, 13, 21, 34};
    uint8_t failure[] = {66, 66, 66, 66, 66, 66};
    static int i;

    if (!gb->testing) {
        return;
    }

    if (!((addr == rSC) && ((data & 0x81) == 0x81))) {
        return;
    }

    if (gb->memory[rSB] == success[i]) {
        if (++i == 6) {
            gb->exit_code = RESULT_SUCCESS;
            gb->done = 1;
        }
    } else if (gb->memory[rSB] == failure[i]) {
        if (++i == 6) {
            gb->exit_code = RESULT_FAILURE;
            gb->done = 1;
        }
    } else {
        i = 0;
    }
}

void blargg1_write_hook(struct gameboy *gb, uint16_t addr, uint8_t data) {
    static uint8_t buf[8], i;

    if (!gb->testing) {
        return;
    }

    if (!((addr == rSC) && ((data & 0x81) == 0x81))) {
        return;
    }

    (void)fprintf(stderr, "%c", gb->memory[rSB]);
    (void)fflush(stderr);
    buf[i++] = gb->memory[rSB];

    if (i < 6) {
        return;
    }

    if (!memcmp(buf, "Failed", 6)) {
        gb->exit_code = RESULT_FAILURE;
        gb->done = 1;
    } else if (!memcmp(buf, "Passed", 6)) {
        gb->exit_code = RESULT_SUCCESS;
        gb->done = 1;
    }

    for (i = 0; i < 5; i++) {
        buf[i] = buf[i + 1];
    }
}

void blargg2_run_hook(struct gameboy *gb) {
    if (!gb->testing) {
        return;
    }
}

// should work for: oam_bug, mem_timing-2, dmg_sound, cgb_sound
void blargg2_write_hook(struct gameboy *gb, uint16_t addr, uint8_t data) {
    const uint8_t sig[] = {0xde, 0xb0, 0x61};
    char *res = (char *)&gb->memory[_SRAM + 4];
    static int f;

    if (!gb->testing) {
        return;
    }

    if ((addr >= _SRAM) && (addr < _RAM)) {
        gb->memory[addr] = data;
    }

    if (memcmp((const void *)&gb->memory[_SRAM + 1], sig, 3)) {
        return;
    }

    if (gb->memory[_SRAM] == 0x80) {
        f = 1;
    } else if (f) {
        gb->done = 1;
        fprintf(stderr, "%s", res);

        if (strstr(res, "Failed")) {
            gb->exit_code = RESULT_FAILURE;
        } else if (strstr(res, "Passed")) {
            gb->exit_code = RESULT_SUCCESS;
        } else {
            gb->exit_code = RESULT_ERROR;
        }
    }
}
