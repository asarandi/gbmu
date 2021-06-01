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
        break;

    default:
        return false;
    }

    return true;
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

    if (!has_battery(gb)) {
        return 1;
    }

    // TODO: free on exit
    gb->ram_file = replace_exten(gb->rom_file, ".sav");

    if (stat(gb->ram_file, &st) != 0) {
        return errno == ENOENT;
    }

    if ((fd = open(gb->ram_file, O_RDONLY | O_BINARY)) == -1) {
        return 0;
    }

    ret = read(fd, gb->ram_banks, RAM_SIZE * 16);
    (void)close(fd);
    return ret != -1;
}

int savefile_write(struct gameboy *gb) {
    int fd, ret, size;

    if (!has_battery(gb)) {
        return 1;
    }

    size = (RAM_SIZE * 16) - 1;

    while ((size >= 0) && (!gb->ram_banks[size])) {
        size--;
    }

    size++;

    /* no ram data ? */
    if (!size) {
        return 1;
    }

    fd = open(gb->ram_file, O_CREAT | O_TRUNC | O_WRONLY | O_BINARY, 0644);

    if (fd == -1) {
        return 0;
    }

    ret = write(fd, gb->ram_banks, size);
    (void)close(fd);
    return ret != -1;
}
