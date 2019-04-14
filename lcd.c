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

#define frame_duration          70224    //10 vblank scanlines
#define is_lcd_enabled          (gb_mem[0xff40] & 0x80 ? 1:0)
#define is_window_enabled       (gb_mem[0xff40] & 0x20 ? 1:0)
#define is_bg_wnd_enabled       (gb_mem[0xff40] & 0x01 ? 1:0)           //DMG specific XXX

int get_wnd_screen_pixel_yx(uint8_t *gb_mem, int y, int x)
{
    int tile_map_addr = (gb_mem[0xff40] & 0x40) ? 0x9c00 : 0x9800;      //bit 6
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

bool    is_window_pixel(uint8_t *gb_mem, int y, int x)
{
    uint8_t wy, wx;

    wy = gb_mem[0xff4a];
    wx = gb_mem[0xff4b] - 7;
    if (!is_lcd_enabled)
        return false ;
    if (!is_window_enabled)
        return false ;
    if (!is_bg_wnd_enabled)
        return false ;
    if ((y >= 144) || (x >= 160))                               //current pixel drawn yx on screen
        return false ;
    if ((wy >= 144) || (wx >= 160))
        return false ;
    if ((y >= wy) && (x >= wx))                                 // current pixel is in window region
        return true ;
    return false ;
}

void    screen_update(uint8_t *gb_mem, t_state *state)
{
    uint8_t y, x, pixel;

    y = gb_mem[0xff44];
    pixel = 0;
    for (x = 0; x < 160; x++) {
        if (is_lcd_enabled) { // && is_bg_wnd_enabled) {
            pixel = get_bg_screen_pixel_yx(gb_mem, y, x);
        }
        if (is_window_pixel(gb_mem, y, x)) {
            pixel = get_wnd_screen_pixel_yx(gb_mem, y, x);
        }
        state->screen_buf[y * 160 + x] = pixel;
    }
}

void    lcd_update(uint8_t *gb_mem, t_state *state, int current_cycles)
{

    uint64_t        lcd_cycle;
    static bool     is_screen_update;

    if (!is_lcd_enabled) {
        gb_mem[0xff41] = (gb_mem[0xff41] & 0xfc) | 2;           //lcd disabled, mode 2
//        (void)memset(state->screen_buf, 0, 144*160);
        return ;
    }

    lcd_cycle = state->cycles % 70224;
    gb_mem[0xff44] = lcd_cycle / 456;                           //current scanline range(0,153)
    gb_mem[0xff41] &= 0xfb;                                     //clear coincidence bit
    if (gb_mem[0xff44] == gb_mem[0xff45]) {                     //ly == lyc ?
        gb_mem[0xff41] |= 4;                                    //set coincidence bit
        if (gb_mem[0xff41] & 0x40)
            gb_mem[0xff0f] |= 2;                                //request lcd interrupt if coincidence bit enabled
    }

    if (gb_mem[0xff44] < 144) {
        if (lcd_cycle % 456 < 80) {            
            gb_mem[0xff41] &= 0xfc;
            gb_mem[0xff41] |= 2;                                //mode 2
        }
        else if (lcd_cycle % 456 < 252) {
            gb_mem[0xff41] &= 0xfc;
            gb_mem[0xff41] |= 3;                                //mode 3
            is_screen_update = true;
        }
        else {
            gb_mem[0xff41] &= 0xfc;                             //mode 0
            if (is_screen_update) {
                is_screen_update = false ;
                screen_update(gb_mem, state);
            }
        }
    }
    else {
        gb_mem[0xff41] &= 0xfc;
        gb_mem[0xff41] |= 1;                                    //mode 1
    }
}
