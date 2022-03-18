#include "gb.h"
#include "hardware.h"
#include "endian.h"

void default_ram_write_u8(struct gameboy *gb, uint16_t addr, uint8_t data) {
    (void)gb;
    (void)addr;
    (void)data;
}

uint8_t default_ram_read_u8(struct gameboy *gb, uint16_t addr) {
    (void)gb;
    (void)addr;
    return 0xff;
}

uint8_t default_rom_read_u8(struct gameboy *gb, uint16_t addr) {
    return gb->cartridge.data[addr & 0x7fff];
}

void default_rom_write_u8(struct gameboy *gb, uint16_t addr, uint8_t data) {
    (void)gb;
    (void)addr;
    (void)data;
}

void mbc1_ram_write_u8(struct gameboy *gb, uint16_t addr, uint8_t data) {
    uint8_t *f = gb->cartridge.data;

    if (gb->cartridge.ramg != 0x0a) {
        return;
    }

    if ((gb->cartridge.mode == 1) && (f[0x149] > 2)) {
        gb->ram_banks[(gb->cartridge.romb1 << 13) + (addr & 0x1fff)] = data;
        return;
    }

    gb->ram_banks[addr & 0x1fff] = data;
}

uint8_t mbc1_ram_read_u8(struct gameboy *gb, uint16_t addr) {
    uint8_t *f = gb->cartridge.data;

    if (gb->cartridge.ramg != 0x0a) {
        return 0xff;
    }

    if ((gb->cartridge.mode == 1) && (f[0x149] > 2)) {
        return gb->ram_banks[(gb->cartridge.romb1 << 13) + (addr & 0x1fff)];
    }

    return gb->ram_banks[addr & 0x1fff];
}

uint8_t mbc1_rom_read_u8(struct gameboy *gb, uint16_t addr) {
    uint8_t *f = gb->cartridge.data;
    uint32_t idx;

    if (addr <= 0x3fff) {
        if (gb->cartridge.mode == 0) {
            return f[addr];
        }

        if (gb->cartridge.mode == 1) {
            idx = (gb->cartridge.romb1 << 19) + addr;
            idx &= gb->cartridge.size - 1;
            return f[idx];
        }
    }

    if ((addr >= 0x4000) && (addr <= 0x7fff)) {
        idx = (((gb->cartridge.romb1 << 5) | gb->cartridge.romb0) << 14) |
              (addr & 0x3fff);
        idx &= gb->cartridge.size - 1;
        return f[idx];
    }

    return 0xff;
}

void mbc1_rom_write_u8(struct gameboy *gb, uint16_t addr, uint8_t data) {
    if (addr <= 0x1fff) {
        gb->cartridge.ramg = data & 0x0f;
    }

    if ((addr >= 0x2000) && (addr <= 0x3fff)) {
        gb->cartridge.romb0 = data & 31 ? data & 31 : 1;
    }

    if ((addr >= 0x4000) && (addr <= 0x5fff)) {
        gb->cartridge.romb1 = data & 3;
    }

    if ((addr >= 0x6000) && (addr <= 0x7fff)) {
        gb->cartridge.mode = data & 1;
    }
}

void mbc2_ram_write_u8(struct gameboy *gb, uint16_t addr, uint8_t data) {
    if (gb->cartridge.ramg != 0x0a) {
        return;
    }

    gb->ram_banks[addr & 0x1ff] = (data & 0x0f) | 0xf0;
}

uint8_t mbc2_ram_read_u8(struct gameboy *gb, uint16_t addr) {
    if (gb->cartridge.ramg != 0x0a) {
        return 0xff;
    }

    return (gb->ram_banks[addr & 0x1ff] & 0x0f) | 0xf0;
}

uint8_t mbc2_rom_read_u8(struct gameboy *gb, uint16_t addr) {
    uint8_t *f = gb->cartridge.data;
    uint32_t idx;

    if (addr <= 0x3fff) {
        return f[addr];
    }

    if ((addr >= 0x4000) && (addr <= 0x7fff)) {
        idx = (gb->cartridge.romb0 << 14) | (addr & 0x3fff);
        idx &= gb->cartridge.size - 1;
        return f[idx];
    }

    return 0xff;
}

void mbc2_rom_write_u8(struct gameboy *gb, uint16_t addr, uint8_t data) {
    if (addr <= 0x3fff) {
        if (addr & 0x100) {
            gb->cartridge.romb0 = data & 15 ? data & 15 : 1;
        } else {
            gb->cartridge.ramg = data & 15;
        }
    }
}

void mbc3_ram_write_u8(struct gameboy *gb, uint16_t addr, uint8_t data) {
    const uint8_t rtc_masks[5] = {63, 63, 31, 255, 193};
    int i;

    if (gb->cartridge.ramg != 0x0a) {
        return;
    }

    if (gb->cartridge.ramb <= 3) {
        gb->ram_banks[(gb->cartridge.ramb << 13) + (addr & 0x1fff)] = data;
        return ;
    }

    i = gb->cartridge.ramb - 8;
    gb->cartridge.rtc.hidden[i] = data & rtc_masks[i];
}

uint8_t mbc3_ram_read_u8(struct gameboy *gb, uint16_t addr) {
    int i;

    if (gb->cartridge.ramg != 0x0a) {
        return 0xff;
    }

    if (gb->cartridge.ramb <= 3) {
        return gb->ram_banks[(gb->cartridge.ramb << 13) + (addr & 0x1fff)];
    }

    i = gb->cartridge.ramb - 8;
    return gb->cartridge.rtc.latched[i];
}

uint8_t mbc3_rom_read_u8(struct gameboy *gb, uint16_t addr) {
    uint8_t *f = gb->cartridge.data;
    uint32_t idx;

    if (addr <= 0x3fff) {
        return f[addr];
    }

    if ((addr >= 0x4000) && (addr <= 0x7fff)) {
        idx = (gb->cartridge.romb0 << 14) | (addr & 0x3fff);
        idx &= gb->cartridge.size - 1;
        return f[idx];
    }

    return 0xff;
}

void mbc3_rom_write_u8(struct gameboy *gb, uint16_t addr, uint8_t data) {
    if (addr <= 0x1fff) {
        gb->cartridge.ramg = data & 15;
    }

    if ((addr >= 0x2000) && (addr <= 0x3fff)) {
        // FIXME: MBC30 (Pokemon Crystal JP) has 256 rom banks, 8 ram banks
        gb->cartridge.romb0 = data & 127 ? data & 127 : 1;
    }

    if ((addr >= 0x4000) && (addr <= 0x5fff)) {
        if ((data <= 3) || ((8 <= data) && (data <= 12))) {
            gb->cartridge.ramb = data;
        }
    }

    if ((addr >= 0x6000) && (addr <= 0x7fff)) {
        if ((gb->cartridge.last_write == 0) && (data == 1)) {
            (void)memcpy(gb->cartridge.rtc.latched,
                         gb->cartridge.rtc.hidden, 20);
        }

        gb->cartridge.last_write = data;
    }
}

void mbc5_ram_write_u8(struct gameboy *gb, uint16_t addr, uint8_t data) {
    if (gb->cartridge.ramg != 0x0a) {
        return;
    }

    gb->ram_banks[(gb->cartridge.ramb << 13) + (addr & 0x1fff)] = data;
}

uint8_t mbc5_ram_read_u8(struct gameboy *gb, uint16_t addr) {
    if (gb->cartridge.ramg != 0x0a) {
        return 0xff;
    }

    return gb->ram_banks[(gb->cartridge.ramb << 13) + (addr & 0x1fff)];
}

uint8_t mbc5_rom_read_u8(struct gameboy *gb, uint16_t addr) {
    uint8_t *f = gb->cartridge.data;
    uint32_t idx;

    if (addr <= 0x3fff) {
        return f[addr];
    }

    if ((addr >= 0x4000) && (addr <= 0x7fff)) {
        idx = (((gb->cartridge.romb1 << 8) | gb->cartridge.romb0) << 14) |
              (addr & 0x3fff);
        idx &= gb->cartridge.size - 1;
        return f[idx];
    }

    return 0xff;
}

void mbc5_rom_write_u8(struct gameboy *gb, uint16_t addr, uint8_t data) {
    if (addr <= 0x1fff) {
        gb->cartridge.ramg = data;
    }

    if ((addr >= 0x2000) && (addr <= 0x2fff)) {
        gb->cartridge.romb0 = data;
    }

    if ((addr >= 0x3000) && (addr <= 0x3fff)) {
        gb->cartridge.romb1 = data & 1;
    }

    if ((addr >= 0x4000) && (addr <= 0x5fff)) {
        gb->cartridge.ramb = data & 15;
    }
}

int mbc_init(struct gameboy *gb) {
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

    case CART_ROM_MBC3_BAT_RTC:         // 0x0F
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

// FIXME: remove strings, printf
    default:
        fprintf(stderr, "unsupported cartridge type %02x\n", gb->memory[0x147]);
        fflush(stderr);
        return 0;
    }

    return 1;
}
