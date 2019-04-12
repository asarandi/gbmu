#include "gb.h"

/*
    mode 2:   80 cycles
    mode 3:  172 cycles
    mode 0:  204 cycles (h-blank)
    mode 1: 4560 cycles (v-blank)

*/

static int  lcd_mode = 2;


int get_bg_screen_pixel_yx(uint8_t *gb_mem, int y, int x)
{
    y = (y + gb_mem[0xff42]) % 256;     //scroll_y
    x = (x + gb_mem[0xff43]) % 256;   //scroll_x

    int tile_map_addr = (gb_mem[0xff40] & 8) ? 0x9c00 : 0x9800;      //lcdc bit 3
    int tile_data_addr = (gb_mem[0xff40] & 0x10) ? 0x8000 : 0x8800;    //lcdc bit 4
    int tile_idx_addr = ((y/8)*32)+(x/8);

    int tile_idx = (uint8_t)gb_mem[tile_map_addr + tile_idx_addr];
    if ((tile_data_addr == 0x8800) && (tile_idx > 127))
        tile_idx = (int8_t)gb_mem[tile_map_addr + tile_idx_addr];
    uint8_t *tile_data = &gb_mem[tile_data_addr + (tile_idx * 16)];
    uint8_t tile_byte0 = tile_data[(y % 8) * 2];
    uint8_t tile_byte1 = tile_data[(y % 8) * 2 + 1];
    int pixel = ((tile_byte0 >> (7-(x%8))) & 1) | (((tile_byte1 >> (7-(x%8))) << 1) & 3);

    return (gb_mem[0xff47] >> (pixel * 2)) & 3; //bg palette data
}

void    dump_background2(uint8_t *gb_mem, t_state *state)
{
    for (int y=0; y<144; y++) {
        for (int x=0;x<160; x++) {
            state->screen_buf[y*160+x] = (uint8_t)get_bg_screen_pixel_yx(gb_mem, y, x);
        }
    }
}

#define frame_duration  70224    //10 vblank scanlines

void    lcd_update(uint8_t *gb_mem, t_state *state, int current_cycles)
{
    int flag;
    if (state->lcd_cycle >= 456) {
        state->lcd_cycle %= 456;        
        state->lcd_scanline++;
    }
    state->lcd_scanline %= 154;
    gb_mem[0xff44] = state->lcd_scanline;

    gb_mem[0xff41] &= 0xfb; //clear coincidence bit
    if (gb_mem[0xff44] == gb_mem[0xff45]) { //ly==lyc
        gb_mem[0xff41] |= 4; //set coincidence bit
    }

    if (state->lcd_scanline < 144) {
        if (state->lcd_cycle < 80) {            
            gb_mem[0xff41] = (gb_mem[0xff41] & 0xfc) | 2;   //mode 2        
        }
        else if (state->lcd_cycle < 252) {
            gb_mem[0xff41] = (gb_mem[0xff41] & 0xfc) | 3;   //mode 3
            //update screen_buf
            flag = 0;

        }
        else {
            if (!flag) {
                int y = state->lcd_scanline;
                for (int x = 0; x < 160; x++) {
                    state->screen_buf[y*160+x] = 
                    (uint8_t)get_bg_screen_pixel_yx(gb_mem, y, x);
                 }
                 flag = 1;
            }

            gb_mem[0xff41] &= 0xfc;   //mode 0    h-blank
        }
    }
    else {
        gb_mem[0xff41] = (gb_mem[0xff41] & 0xfc) | 1;   //v-blank
    }

    state->lcd_cycle += current_cycles;

}







