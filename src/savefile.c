#include "gb.h"
#include "hardware.h"
#include <errno.h>
#include <ctype.h>
#include <inttypes.h>

static bool has_rtc(struct gameboy *gb) {
    switch (gb->cartridge.data[0x147]) {
    case CART_ROM_MBC3_BAT_RTC:
    case CART_ROM_MBC3_RAM_BAT_RTC:
        return true;
    }

    return false;
}

static bool has_battery(struct gameboy *gb) {
    switch (gb->cartridge.data[0x147]) {
    case CART_ROM_MBC1_RAM_BAT:
    case CART_ROM_MBC2_BAT:
    case CART_ROM_RAM_BAT:
    case CART_ROM_MMM01_RAM_BAT:
    case CART_ROM_MBC3_BAT_RTC:
    case CART_ROM_MBC3_RAM_BAT_RTC:
    case CART_ROM_MBC3_RAM_BAT:
    case CART_ROM_MBC5_BAT:
    case CART_ROM_MBC5_RAM_BAT:
    case CART_ROM_MBC5_RAM_BAT_RUMBLE:
    case CART_ROM_MBC7_RAM_BAT_GYRO:
        return true;
    }

    return false;
}

static uint64_t get_ram_size(struct gameboy *gb) {
    if (!has_battery(gb)) {
        return 0;
    }

    if (gb->memory[0x147] == CART_ROM_MBC2_BAT) {
        return 512;
    }

    switch (gb->memory[0x149]) {
    case CART_SRAM_8KB:
        return 8192;

    case CART_SRAM_32KB:
        return 32768;

    case CART_SRAM_128KB:
        return 131072;

    case 5: // missing hardware.inc def
        return 65536;
    }

    return 0;
}


// f("myfile.gb", ".sav") => "myfile.sav"
char *replace_exten(char *fn, char *ext) {
    size_t fnlen, extlen, i;
    char *res;
    fnlen = strlen(fn);
    extlen = strlen(ext);
    res = calloc(fnlen + extlen + 1, 1);
    (void)memcpy(res, fn, fnlen);

    for (i = fnlen - 1; i > 0; i--) {
        if (!isalnum(res[i])) {
            break ;
        }
    }

    i = (i > 0) ? i : fnlen;
    (void)memcpy(res + i, ext, extlen + 1);
    return res;
}

int savefile_read(struct gameboy *gb) {
    int fd, ok;
    struct stat st;
    bool a, b, c;
    gb->ram_size = get_ram_size(gb);

    if (!gb->ram_size) {
        return 1;
    }

    // freed in `savefile_write()' below
    gb->ram_file = replace_exten(gb->rom_file, ".sav");

    if (stat(gb->ram_file, &st) != 0) {
        if (errno == ENOENT) {
            return 1;
        } else {
            (void)perror("stat()");
            return 0;
        }
    }

    a = (uint64_t)st.st_size == gb->ram_size;
    b = has_rtc(gb) && (uint64_t)st.st_size == gb->ram_size + 48;
    c = has_rtc(gb) && (uint64_t)st.st_size == gb->ram_size + 44;

    if (!(a || b || c)) {
        (void)fprintf(stderr, "expecting %" PRIu64 " bytes, but file is %" PRIu64
                      " bytes\n", gb->ram_size, (uint64_t)st.st_size);
        return 0;
    }

    if ((fd = open(gb->ram_file, O_RDONLY | O_BINARY)) == -1) {
        (void)perror("open()");
        return 0;
    }

    ok = read(fd, gb->ram_banks, gb->ram_size) == (ssize_t)gb->ram_size;

    if (ok && b) {
        ok = read(fd, gb->cartridge.rtc.buf, 48) == 48;
    }

    if (ok && c) {
        ok = read(fd, gb->cartridge.rtc.buf, 44) == 44;
    }

    if (ok && (b || c)) {
        ok = rtc_deserialize(gb) == 1;
    }

    if (b || c) {
        fprintf(stderr, "rtc load %s\n", ok ? "ok" : "failed");
    }

    (void)close(fd);
    return ok;
}

int savefile_write(struct gameboy *gb) {
    int fd, ok;

    if (!gb->ram_size) {
        return 1;
    }

    fd = open(gb->ram_file, O_CREAT | O_TRUNC | O_WRONLY | O_BINARY, 0644);

    if (fd == -1) {
        return 0;
    }

    ok = write(fd, gb->ram_banks, gb->ram_size) == (ssize_t)gb->ram_size;

    if (ok && has_rtc(gb)) {
        ok = rtc_serialize(gb) && write(fd, gb->cartridge.rtc.buf, 48) == 48;
        fprintf(stderr, "rtc save %s\n", ok ? "ok":"failed");
    }

    (void)close(fd);
    // free allocated mem
    (void)free(gb->ram_file);
    gb->ram_file = NULL;
    return ok;
}
