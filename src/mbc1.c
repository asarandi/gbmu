#include "gb.h"

static uint8_t ramg, bank1 = 1, bank2, mode;

void mbc1_ram_write_u8(uint16_t addr, uint8_t data) {
    uint8_t *f = state->file_contents;

    if (ramg != 0x0a) {
        return;
    }

    if ((mode == 1) && (f[0x149] > 2)) {
        state->ram_banks[(bank2 << 13) + (addr & 0x1fff)] = data;
        return;
    }

    state->ram_banks[addr & 0x1fff] = data;
}

uint8_t mbc1_ram_read_u8(uint16_t addr) {
    uint8_t *f = state->file_contents;

    if (ramg != 0x0a) {
        return 0xff;
    }

    if ((mode == 1) && (f[0x149] > 2)) {
        return state->ram_banks[(bank2 << 13) + (addr & 0x1fff)];
    }

    return state->ram_banks[addr & 0x1fff];
}

uint8_t mbc1_rom_read_u8(uint16_t addr) {
    uint8_t *f = state->file_contents;
    int idx;

    if (addr <= 0x3fff) {
        if (mode == 0) {
            return f[addr];
        }

        if (mode == 1) {
            idx = (bank2 << 19) + addr;
            idx &= state->file_size - 1;
            return f[idx];
        }
    }

    if ((addr >= 0x4000) && (addr <= 0x7fff)) {
        idx = (((bank2 << 5) | bank1) << 14) | (addr & 0x3fff);
        idx &= state->file_size - 1;
        return f[idx];
    }

    return 0xff;
}

void mbc1_rom_write_u8(uint16_t addr, uint8_t data) {
    if (addr <= 0x1fff) {
        ramg = data & 0x0f;
    }

    if ((addr >= 0x2000) && (addr <= 0x3fff)) {
        bank1 = data & 0x1f;

        if (bank1 == 0) {
            bank1 = 1;
        }
    }

    if ((addr >= 0x4000) && (addr <= 0x5fff)) {
        bank2 = data & 3;
    }

    if ((addr >= 0x6000) && (addr <= 0x7fff)) {
        mode = data & 1;
    }
}
