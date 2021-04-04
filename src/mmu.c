#include "gb.h"
#include "hardware.h"

/*
    the purpose of read_memory() and write_memory()
    is to control reads/writes to restricted memory areas;
    tetris is stuck at copyright screen because it tries to write to 0xff80
*/

#define IS_LCD_MODE_2   ((gb_mem[rSTAT] & 3) == 2)
#define IS_LCD_MODE_3   ((gb_mem[rSTAT] & 3) == 3)

uint8_t read_u8(uint16_t addr) {
    /* ROM */
    if (addr < _VRAM) {
        return state->rom_read_u8(addr);
    }

    /* ignore reads from vram in lcd-mode-3 */
    if ((addr >= _VRAM) && (addr < _SRAM)) {
        if (IS_LCD_MODE_3) {
            return 0xff;
        }
    }

    if ((addr >= _SRAM) && (addr < _RAM)) {
        return state->ram_read_u8(addr);
    }

    if ((addr == rSB) || (addr == rSC)) {
        return serial_read_u8(addr);
    }

    if ((addr >= rNR10) && (addr < rNR10 + 0x30)) {
        return sound_read_u8(addr);
    }

    /* ignore reads from oam in lcd-mode-2 and lcd-mode-3 */
    if ((addr >= _OAMRAM) && (addr < _OAMRAM + 0xa0)) {
        if ((IS_LCD_MODE_2) || (IS_LCD_MODE_3)) {
            return 0xff;
        }
    }

    /* if (addr >= 0xfea0 && addr < 0xff00) return 0; */
    /* joypad no buttons pressed */
    if (addr == rP1) {
        return joypad_read();
    }

    /* upper 3 bits of IF register always 1 */
    if (addr == rIF) {
        return ((gb_mem[rIF] & 0x1f) | 0xe0);
    }

    return gb_mem[addr];
}

uint16_t read_u16(uint16_t addr) {
    return ((read_u8(addr + 1) << 8) | read_u8(addr));
}

void write_u8(uint16_t addr, uint8_t data) {
    /* ROM */
    if (addr < _VRAM) {
        return state->rom_write_u8(addr, data);
    }

    if ((addr >= _VRAM) && (addr < _SRAM)) {
        if (IS_LCD_MODE_3) {
            return;
        }
    }

    if ((addr >= _SRAM) && (addr < _RAM)) {
        return state->ram_write_u8(addr, data);
    }

    /* ECHO */
    if ((addr >= 0xc000) && (addr <= 0xddff)) {
        gb_mem[addr + 0x2000] = data;
    }

    /* ignore writes to oam in lcd-mode-2 and lcd-mode-3 */
    if ((addr >= _OAMRAM) && (addr < _OAMRAM + 0xa0)) {
        if ((IS_LCD_MODE_2) || (IS_LCD_MODE_3)) {
            return;
        }
    }

    if ((addr >= _OAMRAM + 0xa0) && (addr < _IO)) {
        return;
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

    /* LCD STAT */
    /*
            t_r16   *r16 = state->gameboy_registers;
            printf("writing to STAT 0xff41, data: %02x, r16->PC = %04x\n", data, r16->PC);
            printf("current LY 0xff44: %02x, current LYC 0xff45: %02x\n", gb_mem[0xff44], gb_mem[0xff45]);
    */
    /* lcd stat bottom 3 bits read only */
    if (addr == rSTAT) {
        data &= 0xf8;
        data |= (gb_mem[rSTAT] & 7);
    }

    if (addr == rDMA) {
        state->dma_update = true;
    }

    /* read only as per pandocs */
    if (addr ==  rPCM12) {
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
