#include "gb.h"
#include "hardware.h"
#include <errno.h>
#include <ctype.h>

static bool has_battery(struct gameboy *gb) {
    switch (gb->memory[0x147]) {
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

static size_t get_ram_size(struct gameboy *gb) {
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
    int ret, fd;
    struct stat st;
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

    if ((size_t)st.st_size != gb->ram_size) {
        (void)fprintf(stderr, "expecting %lu bytes, but file is %lu bytes\n",
                      gb->ram_size, st.st_size);
        return 0;
    }

    if ((fd = open(gb->ram_file, O_RDONLY | O_BINARY)) == -1) {
        (void)perror("open()");
        return 0;
    }

    ret = read(fd, gb->ram_banks, gb->ram_size);
    (void)close(fd);
    return (size_t)ret == gb->ram_size;
}

int savefile_write(struct gameboy *gb) {
    int fd, ret;

    if (!gb->ram_size) {
        return 1;
    }

    fd = open(gb->ram_file, O_CREAT | O_TRUNC | O_WRONLY | O_BINARY, 0644);

    if (fd == -1) {
        return 0;
    }

    ret = write(fd, gb->ram_banks, gb->ram_size);
    (void)close(fd);
    // free allocated mem
    (void)free(gb->ram_file);
    gb->ram_file = NULL;
    return (size_t)ret == gb->ram_size;
}
