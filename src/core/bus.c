#include "gb.h"
#include "hardware.h"

static int is_video_ram_bus(uint16_t addr) {
    return ((addr >= _VRAM) && (addr < _VRAM + 0x2000));
}

static int is_same_bus(uint16_t a1, uint16_t a2) {
    return is_video_ram_bus(a1) == is_video_ram_bus(a2);
}

static int is_dma_conflict(struct gameboy *gb, uint16_t addr) {
    uint16_t dma_addr = gb->dma.source + gb->dma.index;
    return (gb->dma.active) && (addr < _OAMRAM) && (is_same_bus(dma_addr, addr));
}

uint8_t read_u8(struct gameboy *gb, uint16_t addr) {
    (void)gb->testing_read_hook(gb, addr);

    if (is_dma_conflict(gb, addr)) {
        return gb->dma.byte;
    }

    /* mbc/rom */
    if (addr < _VRAM) {
        return gb->rom_read_u8(gb, addr);
    }

    /* mbc/ram */
    if ((addr >= _SRAM) && (addr < _SRAM + 0x2000)) {
        return gb->ram_read_u8(gb, addr);
    }

    /* ignore reads from vram in lcd-mode-3 */
    if ((addr >= _VRAM) && (addr < _VRAM + 0x2000)) {
        if ((gb->memory[rSTAT] & STATF_LCD) == 3) {
            return 0xff;
        }
    }

    /* ignore reads from oam in lcd mode 2 and 3 */
    if ((addr >= _OAMRAM) && (addr < _OAMRAM + 0xa0)) {
        if (gb->dma.active) {
            return 0xff;
        }

        if ((gb->memory[rSTAT] & STATF_LCD) >= 2) {
            return 0xff;
        }
    }

    if (addr >= _IO) {
        return io_read_u8(gb, addr);
    }

    /* echo ram */
    if ((addr >= 0xe000) && (addr < 0xfe00)) {
        addr -= 0x2000;
    }

    return gb->memory[addr];
}

void write_u8(struct gameboy *gb, uint16_t addr, uint8_t data) {
    (void)gb->testing_write_hook(gb, addr, data);

    if ((gb->dma.active) && (addr < _IO)) {
        return;
    }

    /* mbc/rom */
    if (addr < _VRAM) {
        (void)gb->rom_write_u8(gb, addr, data);
        return;
    }

    /* mbc/ram */
    if ((addr >= _SRAM) && (addr < _SRAM + 0x2000)) {
        (void)gb->ram_write_u8(gb, addr, data);
        return;
    }

    /* ignore writes to vram in lcd-mode-3 */
    if ((addr >= _VRAM) && (addr < _VRAM + 0x2000)) {
        if ((gb->memory[rSTAT] & STATF_LCD) == 3) {
            return;
        }
    }

    /* ignore writes to oam in lcd mode 2 and 3 */
    if ((addr >= _OAMRAM) && (addr < _OAMRAM + 0xa0)) {
        if ((gb->memory[rSTAT] & STATF_LCD) >= 2) {
            return;
        }
    }

    if ((addr >= _OAMRAM + 0xa0) && (addr < _IO)) {
        return;
    }

    if (addr >= _IO) {
        (void)io_write_u8(gb, addr, data);
        return;
    }

    /* echo ram */
    if ((addr >= 0xe000) && (addr < 0xfe00)) {
        addr -= 0x2000;
    }

    /* finally */
    gb->memory[addr] = data;
}
