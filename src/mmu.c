#include "gb.h"
#include "hardware.h"

extern struct io_register io_registers[];

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
        if (((gb->memory[rSTAT] & STATF_LCD) >= 2) || (gb->is_dma)) {
            return 0xff;
        }
    }

    if (addr >= _IO) {
        return io_read_u8(gb, addr);
    }

    return gb->memory[addr];
}

uint16_t read_u16(struct gameboy *gb, uint16_t addr) {
    return ((read_u8(gb, addr + 1) << 8) | read_u8(gb, addr));
}

void write_u8(struct gameboy *gb, uint16_t addr, uint8_t data) {
    if (gb->testing) {
        (void)gb->testing_write_hook(gb, addr, data);
    }

    if ((gb->log_io) && (addr >= _IO)) {
        char *io_reg_name = io_registers[addr - _IO].name;

        if (addr >= _HRAM) {
            io_reg_name = "HRAM";
        }

        (void)printf("IO: addr = %04x data = %02x register = %s\n",
                     addr, data, io_reg_name);
        (void)fflush(stdout);
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

    if (addr == rP1) {
        return joypad_write(gb, data);
    }

    if ((addr == rSB) || (addr == rSC)) {
        return serial_write_u8(gb, addr, data);
    }

    /* reset DIV if written to */
    if (addr == rDIV) {
        gb->div_cycles = 0;
        data = 0;
    }

    /* TAC bottom 3 bits only */
    if (addr == rTAC) {
        data = 0xf8 | (data & 7);
    }

    if ((addr >= rNR10) && (addr < rNR10 + 0x30)) {
        return sound_write_u8(gb, addr, data);
    }

    if (addr == rSTAT) {
        // dmg specific:
        // any write while lcd is `on` and - in mode `0` - or - mode `1`
        // will set bit 1 in IF register
        if (gb->memory[rLCDC] & LCDCF_ON) {
            if ((gb->memory[rSTAT] & STATF_LCD) < 2) {
                gb->stat_irq = true;
            }
        }

        // bottom 3 bits are read-only
        gb->memory[rSTAT] = (data & 0xf8) | (gb->memory[rSTAT] & 7);
        return;
    }

    if (addr == rDMA) {
        gb->dma_clocks = 12;
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
    gb->memory[addr] = data;
}

void write_u16(struct gameboy *gb, uint16_t addr, uint16_t data) {
    (void) write_u8(gb, addr, (uint8_t) data & 0xff);
    (void) write_u8(gb, addr + 1, (uint8_t)(data >> 8));
}
