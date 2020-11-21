#include "gb.h"

/*
    the purpose of read_memory() and write_memory()
    is to control reads/writes to restricted memory areas;
    tetris is stuck at copyright screen because it tries to write to 0xff80
*/

#define is_lcd_mode_2   ((gb_mem[0xff41] & 3) == 2 ? 1:0)
#define is_lcd_mode_3   ((gb_mem[0xff41] & 3) == 3 ? 1:0)

uint8_t read_u8(uint16_t addr)
{
    if (addr <= 0x7fff)                                 /* ROM */
        return state->rom_read_u8(addr);
    if ((addr >= 0xa000) && (addr <= 0xbfff))           /* RAM */
        return state->ram_read_u8(addr);
    if (addr == 0xff02)
        return ((gb_mem[0xff02] & 0x81) | 0x7e);

    /* ignore reads from oam in lcd-mode-2 and lcd-mode-3 */
    if ((addr >= 0xfe00) && (addr <= 0xfe9f) && ((is_lcd_mode_2) || (is_lcd_mode_3)))
        return 0xff;
    /* ignore reads from vram in lcd-mode-3 */
    if ((addr >= 0x8000) && (addr <= 0x9fff) && (is_lcd_mode_3))
        return 0xff;

    /*    if (addr >= 0xfea0 && addr < 0xff00) return 0; */

    if (addr == 0xff00) {  /* joypad no buttons pressed */
        return joypad_read();
    }
    /*
        if (addr == 0xff04) { printf("reading DIV  0xff04, value = %02x\n", gb_mem[0xff04]); }
        if (addr == 0xff05) { printf("reading TIMA 0xff05, value = %02x\n", gb_mem[0xff05]); }
        if (addr == 0xff06) { printf("reading TMA  0xff06, value = %02x\n", gb_mem[0xff06]); }
        if (addr == 0xff07) { printf("reading TAC  0xff07, value = %02x\n", gb_mem[0xff07]); }
    */
    if (addr == 0xff0f) {
        return ((gb_mem[0xff0f] & 0x1f) | 0xe0);  /* upper 3 bits of IF register always 1 */
    }
    return gb_mem[addr];
}

uint16_t read_u16(uint16_t addr)
{
    return ((read_u8(addr+1) << 8) | read_u8(addr));
}

void    write_u8(uint16_t addr, uint8_t data)
{
    if (addr <= 0x7fff) {                                /* ROM */
        (void)state->rom_write_u8(addr, data);
        return ;
    }
    if ((addr >= 0x8000) && (addr <= 0x9fff) && (is_lcd_mode_3))
        return ;
    if ((addr >= 0xa000) && (addr < 0xbfff))  {           /* RAM */
        (void)state->ram_write_u8(addr, data);
        return ;
    }
    if ((addr >= 0xc000) && (addr <= 0xddff))           /* ECHO */
        gb_mem[addr+0x2000] = data;

    /* ignore writes to oam in lcd-mode-2 and lcd-mode-3 */
    if ((addr >= 0xfe00) && (addr <= 0xfe9f) && ((is_lcd_mode_2) || (is_lcd_mode_3)))
        return ;
    if (addr >= 0xfea0 && addr < 0xff00)
        return ;
    /* ignore writes to vram in lcd-mode-3 */

    if (addr == 0xff00) {                                                    /* joypad */
        joypad_write(data);
        return ;
    }
    if (addr == 0xff01) {                                                    /* SB */
        serial_data(data);
        return ;
    }
    if (addr == 0xff02) {                                                    /* SC */
        serial_control(data);
        return ;
    }

    if (addr == 0xff04) {
        state->div_cycles = 0;    /* reset DIV if written to */
        data = 0;
    }
    if (addr == 0xff07) {
        data = 0xf8 | (data & 7);    /* TAC bottom 3 bits only */
    }

    if ((addr >= 0xff10) && (addr <= 0xff26)) {
        (void)sound_write_u8(addr, data);
        return ;
    }

    if (addr == 0xff41) {                                                   /* LCD STAT */
        /*
                t_r16   *r16 = state->gameboy_registers;
                printf("writing to STAT 0xff41, data: %02x, r16->PC = %04x\n", data, r16->PC);
                printf("current LY 0xff44: %02x, current LYC 0xff45: %02x\n", gb_mem[0xff44], gb_mem[0xff45]);
        */
        data &= 0xf8;
        data |= (gb_mem[0xff41] & 7);                            /* lcd stat bottom 3 bits read only */
    }

    if (addr == 0xff46) {
        state->dma_update = true;    /* DMA */
    }
    if (addr == 0xff76)                                                     /* read only as per pandocs */
        return ;
    if (addr == 0xff77)                                                     /* read only as per pandocs */
        return ;

    gb_mem[addr] = data;                                                    /* finally */
}

void    write_u16(uint16_t addr, uint16_t data)
{
    (void)write_u8(addr, (uint8_t) data & 0xff);
    (void)write_u8(addr + 1, (uint8_t) (data >> 8));
}
