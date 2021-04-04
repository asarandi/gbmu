#include "gb.h"

static uint8_t ramg, romb0 = 1, romb1, ramb;

void mbc5_ram_write_u8(uint16_t addr, uint8_t data) {
    if (ramg != 0x0a) {
        return;
    }

    state->ram_banks[(ramb << 13) + (addr & 0x1fff)] = data;
}

uint8_t mbc5_ram_read_u8(uint16_t addr) {
    if (ramg != 0x0a) {
        return 0xff;
    }

    return state->ram_banks[(ramb << 13) + (addr & 0x1fff)];
}

uint8_t mbc5_rom_read_u8(uint16_t addr) {
    uint8_t *f = state->file_contents;
    int idx;

    if (addr <= 0x3fff) {
        return f[addr];
    }

    if ((addr >= 0x4000) && (addr <= 0x7fff)) {
        idx = (((romb1 << 8) | romb0) << 14) | (addr & 0x3fff);
        idx &= state->file_size - 1;
        return f[idx];
    }

    return 0xff;
}

void mbc5_rom_write_u8(uint16_t addr, uint8_t data) {
    if (addr <= 0x1fff) {
        ramg = data;
    }

    if ((addr >= 0x2000) && (addr <= 0x2fff)) {
        romb0 = data;
    }

    if ((addr >= 0x3000) && (addr <= 0x3fff)) {
        romb1 = data & 0x01;
    }

    if ((addr >= 0x4000) && (addr <= 0x5fff)) {
        ramb = data & 0x0f;
    }
}
