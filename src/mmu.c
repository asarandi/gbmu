#include "gb.h"
#include "hardware.h"

uint8_t read_u8(uint16_t addr) {
    /* mbc/rom */
    if (addr < _VRAM) {
        return state->rom_read_u8(addr);
    }

    /* mbc/ram */
    if ((addr >= _SRAM) && (addr < _SRAM + 0x2000)) {
        return state->ram_read_u8(addr);
    }

    if (state->is_dma) {
        if (addr >= _RAM + 0x2000) {
            addr = _RAM | (addr & 0x1fff);
        }

        return gb_mem[addr];
    }

    /* ignore reads from vram in lcd-mode-3 */
    if ((addr >= _VRAM) && (addr < _VRAM + 0x2000)) {
        if ((gb_mem[rSTAT] & STATF_LCD) == 3) {
            return 0xff;
        }
    }

    /* ignore reads from oam in lcd mode 2 and 3 */
    if ((addr >= _OAMRAM) && (addr < _OAMRAM + 0xa0)) {
        if ((gb_mem[rSTAT] & STATF_LCD) >= 2) {
            return 0xff;
        }
    }

    if (addr >= _IO) {
        return io_read_u8(addr);
    }

    return gb_mem[addr];
}

uint16_t read_u16(uint16_t addr) {
    return ((read_u8(addr + 1) << 8) | read_u8(addr));
}

void write_u8(uint16_t addr, uint8_t data) {
    if (state->testing) {
        (void)state->testing_write_hook(addr, data);
    }

    /* mbc/rom */
    if (addr < _VRAM) {
        return state->rom_write_u8(addr, data);
    }

    /* mbc/ram */
    if ((addr >= _SRAM) && (addr < _SRAM + 0x2000)) {
        return state->ram_write_u8(addr, data);
    }

    /* ignore writes to vram in lcd-mode-3 */
    if ((addr >= _VRAM) && (addr < _VRAM + 0x2000)) {
        if ((gb_mem[rSTAT] & STATF_LCD) == 3) {
            return;
        }
    }

    /* ignore writes to oam in lcd mode 2 and 3 */
    if ((addr >= _OAMRAM) && (addr < _OAMRAM + 0xa0)) {
        if ((gb_mem[rSTAT] & STATF_LCD) >= 2) {
            return;
        }
    }

    if ((addr >= _OAMRAM + 0xa0) && (addr < _IO)) {
        return;
    }

    /* echo */
    if ((addr >= 0xc000) && (addr <= 0xddff)) {
        gb_mem[addr + 0x2000] = data;
    }

    if (addr == rP1) {
        return joypad_write(data);
    }

    if ((addr == rSB) || (addr == rSC)) {
        return serial_write_u8(addr, data);
    }

    /* reset DIV if written to */
    if (addr == rDIV) {
        state->div_cycles = 0;
        data = 0;
    }

    /* TAC bottom 3 bits only */
    if (addr == rTAC) {
        data = 0xf8 | (data & 7);
    }

    if ((addr >= rNR10) && (addr < rNR10 + 0x30)) {
        return sound_write_u8(addr, data);
    }

    if (addr == rSTAT) {
        // dmg specific:
        // any write while lcd is `on` and - in mode `0` - or - mode `1`
        // will set bit 1 in IF register
        if (gb_mem[rLCDC] & LCDCF_ON) {
            if ((gb_mem[rSTAT] & STATF_LCD) < 2) {
                gb_mem[rIF] |= IEF_LCDC;
            }
        }

        // bottom 3 bits are read-only
        gb_mem[rSTAT] = (data & 0xf8) | (gb_mem[rSTAT] & 7);
        return;
    }

    if (addr == rDMA) {
        return dma_write_u8(addr, data);
    }

    /* read only as per pandocs */
    if (addr == rPCM12) {
        return;
    }

    /* read only as per pandocs */
    if (addr == rPCM34) {
        return;
    }

    /* finally */
    gb_mem[addr] = data;
}

void write_u16(uint16_t addr, uint16_t data) {
    (void) write_u8(addr, (uint8_t) data & 0xff);
    (void) write_u8(addr + 1, (uint8_t)(data >> 8));
}
