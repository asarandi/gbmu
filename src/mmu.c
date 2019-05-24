#include "gb.h"

/*
    the purpose of read_memory() and write_memory()
    is to control reads/writes to restricted memory areas;
    tetris is stuck at copyright screen because it tries to write to 0xff80
*/

#define is_lcd_mode_2   ((mem[0xff41] & 3) == 2 ? 1:0)
#define is_lcd_mode_3   ((mem[0xff41] & 3) == 3 ? 1:0)

uint8_t read_u8(uint16_t addr) {
    uint8_t *mem = state->gameboy_memory;

    if (addr <= 0x7fff)                                 //ROM
		return state->rom_read_u8(addr);
    if ((addr >= 0xa000) && (addr <= 0xbfff))           //RAM
        return state->ram_read_u8(addr);

    /* ignore reads from oam in lcd-mode-2 and lcd-mode-3 */
    if ((addr >= 0xfe00) && (addr <= 0xfe9f) && ((is_lcd_mode_2) || (is_lcd_mode_3)))   return 0xff;
    /* ignore reads from vram in lcd-mode-3 */
    if ((addr >= 0x8000) && (addr <= 0x9fff) && (is_lcd_mode_3))                        return 0xff;

//    if (addr >= 0xfea0 && addr < 0xff00) return 0;

    if (addr == 0xff00) { return joypad_read(); } /* joypad no buttons pressed */
/*
    if (addr == 0xff04) { printf("reading DIV  0xff04, value = %02x\n",mem[0xff04]); }
    if (addr == 0xff05) { printf("reading TIMA 0xff05, value = %02x\n",mem[0xff05]); }
    if (addr == 0xff06) { printf("reading TMA  0xff06, value = %02x\n",mem[0xff06]); }
    if (addr == 0xff07) { printf("reading TAC  0xff07, value = %02x\n",mem[0xff07]); }
*/
    if (addr == 0xff0f) { return ((mem[0xff0f] & 0x1f) | 0xe0); } /*upper 3 bits of IF register always 1*/
    return mem[addr];
}

uint16_t read_u16(uint16_t addr) {    
    return ((read_u8(addr+1) << 8) | read_u8(addr));
}

void    write_u8(uint16_t addr, uint8_t data) {
    uint8_t *mem = state->gameboy_memory;

    if (addr <= 0x7fff)                                 //ROM
        return state->rom_write_u8(addr, data);
    if ((addr >= 0xa000) && (addr < 0xbfff))            //RAM
        return state->ram_write_u8(addr, data);
    if ((addr >= 0xc000) && (addr <= 0xddff))           //ECHO
        mem[addr+0x2000] = data;

    if (addr == 0xff01)
        return serial_data(data);

    if (addr == 0xff02)
        return serial_control(data);
    
    if (addr == 0xff02) {
        if (data == 0x81) {
            mem[0xff01] = 0xff;
            mem[0xff02] = 1;
            mem[0xff0f] |= 8;
            return ;
        }
    }

    /* ignore writes to oam in lcd-mode-2 and lcd-mode-3 */
    if ((addr >= 0xfe00) && (addr <= 0xfe9f) && ((is_lcd_mode_2) || (is_lcd_mode_3)))   return ;

    /* ignore writes to vram in lcd-mode-3 */
    if ((addr >= 0x8000) && (addr <= 0x9fff) && (is_lcd_mode_3))                        return ;

    if (addr >= 0xfea0 && addr < 0xff00) return ;
    if (addr == 0xff46) { state->dma_update = true; }
    if (addr == 0xff04) { state->div_cycles = 0; data = 0; }    /*reset DIV if written to*/
    if (addr == 0xff07) { data = 0xf8 | (data & 7); }           /* TAC bottom 3 bits only */


    if ((addr >= 0xff10) && (addr <= 0xff26))
        return sound_write_u8(addr, data);

//    if (addr > 0xff00) { printf("writing to   0x%04x, old value = %02x, new value = %02x\n",addr,mem[addr],data); }
    if (addr == 0xff41) {
        t_r16   *r16 = state->gameboy_registers;
        printf("writing to STAT 0xff41, data: %02x, r16->PC = %04x\n", data, r16->PC);
        printf("current LY 0xff44: %02x, current LYC 0xff45: %02x\n", mem[0xff44], mem[0xff45]);

    }

    if (addr == 0xff41) { data &= 0xf8; data |= (mem[0xff41] & 7); }         /*lcd stat bottom 3 bits read only*/
    if (addr == 0xff00) { data &= 0xf0; data |= (mem[0xff00] & 15); }       /*joypad bottom 4 bits read only*/
    if (addr == 0xff76) return ; /*read only as per pandocs*/
    if (addr == 0xff77) return ; /*read only as per pandocs*/
//    if (addr == 0xff44) return ;    /* ly, ignore */

//    if (addr == 0xff80) return ;

/*
    if (addr == 0xff04) { printf("writing DIV  0xff04, old value = %02x, new value = %02x\n",mem[0xff04],data); }
    if (addr == 0xff05) { printf("writing TIMA 0xff05, old value = %02x, new value = %02x\n",mem[0xff05],data); }
    if (addr == 0xff06) { printf("writing TMA  0xff06, old value = %02x, new value = %02x\n",mem[0xff06],data); }
    if (addr == 0xff07) { printf("writing TAC  0xff07, old value = %02x, new value = %02x\n",mem[0xff07],data); data &= 7; }
*/

    mem[addr] = data;
}

void    write_u16(uint16_t addr, uint16_t data) {    
    (void)write_u8(addr, (uint8_t) data & 0xff);
    (void)write_u8(addr + 1, (uint8_t) (data >> 8));
}
