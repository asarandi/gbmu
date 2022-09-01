#include "gb.h"
#include "hardware.h"
#include "hash.h"
#include "endian.h"
#include <time.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>

#define TIMEOUT        15
#define RESULT_SUCCESS 10
#define RESULT_FAILURE 11
#define RESULT_TIMEOUT 12
#define RESULT_ERROR   13

void serial_run_hook(struct gameboy *);
void serial_read_hook(struct gameboy *, uint16_t);
void serial_write_hook(struct gameboy *, uint16_t, uint8_t);
void timeout_run_hook(struct gameboy *);
void blargg1_write_hook(struct gameboy *, uint16_t, uint8_t);
void blargg2_write_hook(struct gameboy *, uint16_t, uint8_t);
void mooneye_write_hook(struct gameboy *,uint16_t, uint8_t);
void screenshot_run_hook(struct gameboy *);
void mealybug_run_hook(struct gameboy *);
void gambatte_run_hook(struct gameboy *);

void dummy_run_hook(struct gameboy *gb) {
    (void)gb;
}

void dummy_read_hook(struct gameboy *gb, uint16_t addr) {
    (void)gb;
    (void)addr;
}

void dummy_write_hook(struct gameboy *gb, uint16_t addr, uint8_t data) {
    (void)gb;
    (void)addr;
    (void)data;
}

int testing_dummy_setup(struct gameboy *gb) {
    gb->testing_run_hook = &dummy_run_hook;
    gb->testing_read_hook = &dummy_read_hook;
    gb->testing_write_hook = &dummy_write_hook;
    gb->testing = 0;
    return 1;
}

// assuming run/read/write hook funcs are populated with dummy
int testing_setup(struct gameboy *gb, char *test_name) {
    struct test {
        char *name;
        void (*run)(struct gameboy *);
        void (*read)(struct gameboy *, uint16_t);
        void (*write)(struct gameboy *, uint16_t, uint8_t);
    } tests[] = {
        // null means run dummy func, else implementation
        {"serial", &serial_run_hook, &serial_read_hook, &serial_write_hook},
        {"blargg1", &timeout_run_hook, 0, &blargg1_write_hook},
        {"blargg2", &timeout_run_hook, 0, &blargg2_write_hook},
        {"mooneye", &timeout_run_hook, 0, &mooneye_write_hook},
        {"screenshot", &screenshot_run_hook, 0, 0},
        {"mealybug", &mealybug_run_hook, 0, 0},
        {"gambatte", &gambatte_run_hook, 0, 0},
    };

    for (int i = 0; i < 7; i++) {
        if (!strcasecmp(test_name, tests[i].name)) {
            if (tests[i].run) {
                gb->testing_run_hook = tests[i].run;
            }

            if (tests[i].read) {
                gb->testing_read_hook = tests[i].read;
            }

            if (tests[i].write) {
                gb->testing_write_hook = tests[i].write;
            }

            gb->testing = 1;
            gb->exit_code = -1;
            return 1;
        }
    }

    (void)fprintf(stderr, "test not found: %s\n", test_name);
    return 0;
}

static struct serial_stats {
    int sb_read;
    int sb_write;
    int sc_read;
    int sc_write;
    int primary;
    int secondary;
} serial_stats = {};

void serial_run_hook(struct gameboy *gb) {
    if (gb->cycles < (30 * 4194304)) {
        return ;
    }

    (void)fprintf(stderr,
                  "serial: SB r=%04d w=%04d, SC r=%04d w=%04d, primary=%04d secondary=%04d - %s\n",
                  serial_stats.sb_read, serial_stats.sb_write,
                  serial_stats.sc_read, serial_stats.sc_write,
                  serial_stats.primary, serial_stats.secondary,
                  gb->rom_file);
    (void)fflush(stderr);
    gb->done = 1;
}

void serial_read_hook(struct gameboy *gb, uint16_t addr) {
    (void)gb;

    switch (addr) {
    case rSB:
        serial_stats.sb_read++;
        break ;

    case rSC:
        serial_stats.sc_read++;
        break ;
    }
}

void serial_write_hook(struct gameboy *gb, uint16_t addr, uint8_t data) {
    (void)gb;

    switch (addr) {
    case rSB:
        serial_stats.sb_write++;
        break ;

    case rSC:
        serial_stats.sc_write++;

        if ((data & 0x81) == 0x81) {
            serial_stats.primary++;
        }

        if ((data & 0x81) == 0x80) {
            serial_stats.secondary++;
        }

        break ;
    }
}

void screenshot_and_exit(struct gameboy *gb, char *exten) {
    char *fn = replace_exten(gb->rom_file, exten);
    screenshot(gb, fn);
    free(fn);
    gb->exit_code = 0;
    gb->done = 1;
}

void screenshot_run_hook(struct gameboy *gb) {
    if (!gb->testing) {
        return ;
    }

    if ((gb->cycles >= (40 * 4194304)) && (gb->lcd.render)) {
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

void timeout_run_hook(struct gameboy *gb) {
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

    if (memcmp((const void *)&gb->memory[_SRAM + 1], sig, 3) != 0) {
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

static uint32_t gambatte_get_tile_hash(struct gameboy *gb, int y, int x) {
    uint8_t data[64] = {0};
    int i, j;

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            data[i * 8 + j] = gb->lcd.buf[(y + i) * 160 + (x + j)];
        }
    }

    return my_crc32(data, 64);
}

static uint8_t gambatte_identify_tile_hash(uint32_t hash) {
    struct {
        uint32_t hash;
        uint8_t tile;
    } tab[] = {
        { 0x19dd6c31, '0' },
        { 0x1d1c638a, '1' },
        { 0xb96e834c, '2' },
        { 0xa7c98e3a, '3' },
        { 0xfe31f622, '4' },
        { 0xc84b5743, '5' },
        { 0x0337e3ee, '6' },
        { 0xd84ae335, '7' },
        { 0x19d0831a, '8' },
        { 0xdcf1b61d, '9' },
        { 0xde2a9463, 'A' },
        { 0x5d1475c4, 'B' },
        { 0xa0c1d990, 'C' },
        { 0xca4d4aff, 'D' },
        { 0x692084af, 'E' },
        { 0x0ac39f1f, 'F' },
        { 0x758d6336, ' ' }, // not checking
    };
    int i;

    for (i = 0; i < 16; i++) {
        if (tab[i].hash == hash) {
            return tab[i].tile;
        }
    }

    return 0xff;
}

static uint8_t *gambatte_get_tile_string(struct gameboy *gb, int len) {
    static uint8_t buf[32];
    uint32_t hash;
    int i;
    assert(0 < len && len <= 20); // top row only

    for (i = 0; i < len; i++) {
        hash = gambatte_get_tile_hash(gb, 0, i * 8);
        buf[i] = gambatte_identify_tile_hash(hash);

        if (buf[i] == 0xff) {
            (void)fprintf(stderr, "gambatte: unknown tile, position %d\n", i);
        }
    }

    buf[i] = 0;
    return buf;
}

void gambatte_run_hook(struct gameboy *gb) {
    char *ptr, *s, *p;
    int len;

    if (!gb->testing) {
        return;
    }

    if (!(gb->cycles > 15 * 70224)) {
        return ;
    }

    gb->exit_code = RESULT_ERROR;
    gb->done = 1;
    ptr = strdup(gb->rom_file);

    if (!(s = strstr(ptr, "_dmg08"))) {
        free(ptr);
        return ;
    }

    s = s + 6;

    if (!(s = strstr(s, "_out"))) {
        free(ptr);
        return ;
    }

    p = s = s + 4;

    while (*p && (isupper(*p) || isdigit(*p))) {
        ++p;
    }

    *p = '\0';
    len = strlen(s);
    p = (char *)gambatte_get_tile_string(gb, len);
    gb->exit_code = (!strncmp(s, p, len)) ? RESULT_SUCCESS : RESULT_FAILURE;
    free(ptr);
}

int screenshot(struct gameboy *gb, char *filename) {
    uint8_t buf[5972] = {0};
    const uint8_t png_head[] = {
        0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, // png
        0x00, 0x00, 0x00, 0x0d, 0x49, 0x48, 0x44, 0x52, // ihdr size 13
        0x00, 0x00, 0x00, 0xa0, 0x00, 0x00, 0x00, 0x90, // 160, 144
        0x02, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x6e, 0x27, // 2 bit depth, crc
        0xfd, 0x00, 0x00, 0x17, 0x1b, 0x49, 0x44, 0x41, // idat size 5915
        0x54, 0x58, 0x09, 0x01, 0x10, 0x17, 0xef, 0xe8  // zlib hdr
    };
    const uint8_t png_tail[] = {
        0xaa, 0xaa, 0xaa, 0xaa, 0xbb, 0xbb, 0xbb, 0xbb, // crc aa=zlib, bb=idat
        0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, // iend size 0
        0xae, 0x42, 0x60, 0x82                          // iend crc
    };
    (void)memcpy(buf, png_head, sizeof(png_head));
    (void)memcpy(buf + 5952, png_tail, sizeof(png_tail));
    int fd, i, o = 48;

    for (i = 0; i < 144 * 160;) {
        if (!(i % 160)) {
            buf[o++] = 0;
        }

        buf[o] = (3 - gb->lcd.buf[i++]) << 6;
        buf[o] |= (3 - gb->lcd.buf[i++]) << 4;
        buf[o] |= (3 - gb->lcd.buf[i++]) << 2;
        buf[o++] |= 3 - gb->lcd.buf[i++];
    }

    (void)write_be32(buf + o, my_adler32(buf + 48, 5904)); // zlib
    (void)write_be32(buf + o + 4, my_crc32(buf + 37, 5919)); // idat
    fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC | O_BINARY, 0644);

    if (fd < 1) {
        (void)perror(__func__);
        return 0;
    }

    assert(write(fd, buf, sizeof(buf)) == sizeof(buf));
    (void)close(fd);
    return 1;
}
