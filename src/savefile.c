#include "gb.h"
#include "hardware.h"
#include <errno.h>

static bool has_battery() {
    switch (gb_mem[0x147]) {
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

int savefile_read() {
    int len, offset, ret, fd;
    struct stat st;

    if (!has_battery()) {
        return 1;
    }

    len = strlen(state->rom_file);
    state->ram_file = calloc(len + 6, 1);
    (void)strncpy(state->ram_file, state->rom_file, len + 1);
    (void)memset(&state->ram_file[len], 0, 5);
    offset = 0;

    if (!strcmp(&state->ram_file[len - 3], ".gb")) {
        offset = 3;
    }

    if (!strcmp(&state->ram_file[len - 4], ".gbc")) {
        offset = 4;
    }

    strncpy(&state->ram_file[len - offset], ".sav", 5);

    if (stat(state->ram_file, &st) != 0) {
        return errno == ENOENT;
    }

    if ((fd = open(state->ram_file, O_RDONLY)) == -1) {
        return 0;
    }

    ret = read(fd, state->ram_banks, RAM_SIZE * 16);
    (void)close(fd);
    return ret != -1;
}

int savefile_write() {
    int fd, ret, size;

    if (!has_battery()) {
        return 1;
    }

    size = (RAM_SIZE * 16) - 1;

    while ((size >= 0) && (!state->ram_banks[size])) {
        size--;
    }

    size++;

    /* no ram data ? */
    if (!size) {
        return 1;
    }

    fd = open(state->ram_file, O_CREAT | O_TRUNC | O_WRONLY, 0644);

    if (fd == -1) {
        return 0;
    }

    ret = write(fd, state->ram_banks, size);
    (void)close(fd);
    return ret != -1;
}
