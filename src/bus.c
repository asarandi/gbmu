#include "gb.h"
#include "hardware.h"

uint8_t read_u8(struct gameboy *gb, uint16_t addr) {
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

    return gb->memory[addr];
}

void write_u8(struct gameboy *gb, uint16_t addr, uint8_t data) {
    if (gb->testing) {
        (void)gb->testing_write_hook(gb, addr, data);
    }

    if ((gb->dma.active) && (addr < _IO)) {
        return;
    }

    /* mbc/rom */
    if (addr < _VRAM) {
        return gb->rom_write_u8(gb, addr, data);
    }

    /* mbc/ram */
    if ((addr >= _SRAM) && (addr < _SRAM + 0x2000)) {
        return gb->ram_write_u8(gb, addr, data);
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

    /* echo */
    if ((addr >= 0xc000) && (addr <= 0xddff)) {
        gb->memory[addr + 0x2000] = data;
    }

    if (addr >= _IO) {
        return io_write_u8(gb, addr, data);
    }

    /* finally */
    gb->memory[addr] = data;
}
