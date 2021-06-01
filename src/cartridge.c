#include "gb.h"
#include "hardware.h"

static uint8_t ramg, romb0 = 1, romb1, ramb, mode;

void default_ram_write_u8(struct gameboy *gb, uint16_t addr, uint8_t data) {
    (void)gb;
    (void)addr;
    (void)data;
    return;
}

uint8_t default_ram_read_u8(struct gameboy *gb, uint16_t addr) {
    (void)gb;
    (void)addr;
    return 0xff;
}

uint8_t default_rom_read_u8(struct gameboy *gb, uint16_t addr) {
    (void)addr;
    return gb->file_contents[addr & 0x7fff];
}

void default_rom_write_u8(struct gameboy *gb, uint16_t addr, uint8_t data) {
    (void)gb;
    (void)addr;
    (void)data;
    return;
}

void mbc1_ram_write_u8(struct gameboy *gb, uint16_t addr, uint8_t data) {
    uint8_t *f = gb->file_contents;

    if (ramg != 0x0a) {
        return;
    }

    if ((mode == 1) && (f[0x149] > 2)) {
        gb->ram_banks[(romb1 << 13) + (addr & 0x1fff)] = data;
        return;
    }

    gb->ram_banks[addr & 0x1fff] = data;
}

uint8_t mbc1_ram_read_u8(struct gameboy *gb, uint16_t addr) {
    uint8_t *f = gb->file_contents;

    if (ramg != 0x0a) {
        return 0xff;
    }

    if ((mode == 1) && (f[0x149] > 2)) {
        return gb->ram_banks[(romb1 << 13) + (addr & 0x1fff)];
    }

    return gb->ram_banks[addr & 0x1fff];
}

uint8_t mbc1_rom_read_u8(struct gameboy *gb, uint16_t addr) {
    uint8_t *f = gb->file_contents;
    int idx;

    if (addr <= 0x3fff) {
        if (mode == 0) {
            return f[addr];
        }

        if (mode == 1) {
            idx = (romb1 << 19) + addr;
            idx &= gb->file_size - 1;
            return f[idx];
        }
    }

    if ((addr >= 0x4000) && (addr <= 0x7fff)) {
        idx = (((romb1 << 5) | romb0) << 14) | (addr & 0x3fff);
        idx &= gb->file_size - 1;
        return f[idx];
    }

    return 0xff;
}

void mbc1_rom_write_u8(struct gameboy *gb, uint16_t addr, uint8_t data) {
    (void)gb;

    if (addr <= 0x1fff) {
        ramg = data & 0x0f;
    }

    if ((addr >= 0x2000) && (addr <= 0x3fff)) {
        romb0 = data & 0x1f;

        if (romb0 == 0) {
            romb0 = 1;
        }
    }

    if ((addr >= 0x4000) && (addr <= 0x5fff)) {
        romb1 = data & 3;
    }

    if ((addr >= 0x6000) && (addr <= 0x7fff)) {
        mode = data & 1;
    }
}

void mbc2_ram_write_u8(struct gameboy *gb, uint16_t addr, uint8_t data) {
    if (ramg != 0x0a) {
        return;
    }

    gb->ram_banks[addr & 0x1ff] = (data & 0x0f) | 0xf0;
}

uint8_t mbc2_ram_read_u8(struct gameboy *gb, uint16_t addr) {
    if (ramg != 0x0a) {
        return 0xff;
    }

    return (gb->ram_banks[addr & 0x1ff] & 0x0f) | 0xf0;
}

uint8_t mbc2_rom_read_u8(struct gameboy *gb, uint16_t addr) {
    uint8_t *f = gb->file_contents;
    int idx;

    if (addr <= 0x3fff) {
        return f[addr];
    }

    if ((addr >= 0x4000) && (addr <= 0x7fff)) {
        idx = (romb0 << 14) | (addr & 0x3fff);
        idx &= gb->file_size - 1;
        return f[idx];
    }

    return 0xff;
}

void mbc2_rom_write_u8(struct gameboy *gb, uint16_t addr, uint8_t data) {
    (void)gb;

    if (addr <= 0x3fff) {
        if (addr & 0x100) {
            romb0 = data & 15;

            if (romb0 == 0) {
                romb0 = 1;
            }
        } else {
            ramg = data & 15;
        }
    }
}

void mbc3_ram_write_u8(struct gameboy *gb, uint16_t addr, uint8_t data) {
    if (ramg != 0x0a) {
        return;
    }

    gb->ram_banks[(ramb << 13) + (addr & 0x1fff)] = data;
}

uint8_t mbc3_ram_read_u8(struct gameboy *gb, uint16_t addr) {
    if (ramg != 0x0a) {
        return 0xff;
    }

    return gb->ram_banks[(ramb << 13) + (addr & 0x1fff)];
}

uint8_t mbc3_rom_read_u8(struct gameboy *gb, uint16_t addr) {
    uint8_t *f = gb->file_contents;
    int idx;

    if (addr <= 0x3fff) {
        return f[addr];
    }

    if ((addr >= 0x4000) && (addr <= 0x7fff)) {
        idx = (romb0 << 14) | (addr & 0x3fff);
        idx &= gb->file_size - 1;
        return f[idx];
    }

    return 0xff;
}

void mbc3_rom_write_u8(struct gameboy *gb, uint16_t addr, uint8_t data) {
    (void)gb;

    if (addr <= 0x1fff) {
        ramg = data;
    }

    if ((addr >= 0x2000) && (addr <= 0x3fff)) {
        romb0 = data;

        if (romb0 == 0) {
            romb0 = 1;
        }
    }

    if ((addr >= 0x4000) && (addr <= 0x5fff)) {
        data &= 0x0f;

        if (data <= 3) {
            ramb = data & 3;
        } else {
            printf("mbc3 rtc register select, data = %02x\n", data);    /* TODO */
        }
    }

    if ((addr >= 0x6000) && (addr <= 0x7fff)) {
        printf("mbc3 latch clock data, data = %02x\n", data);    /* TODO */
    }
}

void mbc5_ram_write_u8(struct gameboy *gb, uint16_t addr, uint8_t data) {
    if (ramg != 0x0a) {
        return;
    }

    gb->ram_banks[(ramb << 13) + (addr & 0x1fff)] = data;
}

uint8_t mbc5_ram_read_u8(struct gameboy *gb, uint16_t addr) {
    if (ramg != 0x0a) {
        return 0xff;
    }

    return gb->ram_banks[(ramb << 13) + (addr & 0x1fff)];
}

uint8_t mbc5_rom_read_u8(struct gameboy *gb, uint16_t addr) {
    uint8_t *f = gb->file_contents;
    int idx;

    if (addr <= 0x3fff) {
        return f[addr];
    }

    if ((addr >= 0x4000) && (addr <= 0x7fff)) {
        idx = (((romb1 << 8) | romb0) << 14) | (addr & 0x3fff);
        idx &= gb->file_size - 1;
        return f[idx];
    }

    return 0xff;
}

void mbc5_rom_write_u8(struct gameboy *gb, uint16_t addr, uint8_t data) {
    (void)gb;

    if (addr <= 0x1fff) {
        ramg = data;
    }

    if ((addr >= 0x2000) && (addr <= 0x2fff)) {
        romb0 = data;
    }

    if ((addr >= 0x3000) && (addr <= 0x3fff)) {
        romb1 = data & 1;
    }

    if ((addr >= 0x4000) && (addr <= 0x5fff)) {
        ramb = data & 15;
    }
}

int cartridge_init(struct gameboy *gb) {
    switch (gb->memory[0x147]) {
    case CART_ROM:                      // 0x00
        gb->ram_read_u8 = &default_ram_read_u8;
        gb->ram_write_u8 = &default_ram_write_u8;
        gb->rom_read_u8 = &default_rom_read_u8;
        gb->rom_write_u8 = &default_rom_write_u8;
        break;

    case CART_ROM_MBC1:                 // 0x01
    case CART_ROM_MBC1_RAM:             // 0x02
    case CART_ROM_MBC1_RAM_BAT:         // 0x03
        gb->ram_read_u8 = &mbc1_ram_read_u8;
        gb->ram_write_u8 = &mbc1_ram_write_u8;
        gb->rom_read_u8 = &mbc1_rom_read_u8;
        gb->rom_write_u8 = &mbc1_rom_write_u8;
        break;

    case CART_ROM_MBC2:                 // 0x05, untested
    case CART_ROM_MBC2_BAT:             // 0x06
        gb->ram_read_u8 = &mbc2_ram_read_u8;
        gb->ram_write_u8 = &mbc2_ram_write_u8;
        gb->rom_read_u8 = &mbc2_rom_read_u8;
        gb->rom_write_u8 = &mbc2_rom_write_u8;
        break;

    case CART_ROM_MBC3_RAM_BAT_RTC:     // 0x10
    case CART_ROM_MBC3:                 // 0x11
    case CART_ROM_MBC3_RAM:             // 0x12, untested
    case CART_ROM_MBC3_RAM_BAT:         // 0x13
        gb->ram_read_u8 = &mbc3_ram_read_u8;
        gb->ram_write_u8 = &mbc3_ram_write_u8;
        gb->rom_read_u8 = &mbc3_rom_read_u8;
        gb->rom_write_u8 = &mbc3_rom_write_u8;
        break;

    case CART_ROM_MBC5:                 // 0x19
    case CART_ROM_MBC5_BAT:             // 0x1A, untested
    case CART_ROM_MBC5_RAM_BAT:         // 0x1B
    case CART_ROM_MBC5_RUMBLE:          // 0x1C
    case CART_ROM_MBC5_RAM_RUMBLE:      // 0x1D, untested
    case CART_ROM_MBC5_RAM_BAT_RUMBLE:  // 0x1E
        gb->ram_read_u8 = &mbc5_ram_read_u8;
        gb->ram_write_u8 = &mbc5_ram_write_u8;
        gb->rom_read_u8 = &mbc5_rom_read_u8;
        gb->rom_write_u8 = &mbc5_rom_write_u8;
        break;

    default:
        fprintf(stderr, "unsupported cartridge type %02x\n", gb->memory[0x147]);
        return 0;
    }

    return 1;
}
