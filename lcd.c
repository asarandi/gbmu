#include "gb.h"

/*
    mode 2:   80 cycles
    mode 3:  172 cycles
    mode 0:  204 cycles (h-blank)
    mode 1: 4560 cycles (v-blank)

*/

void delay()
{
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = 1000000000L / 60;

    struct timespec tz;
    tz.tv_sec = 0;
    tz.tv_nsec = 1000000000L / 60;
    (void)nanosleep(&ts, &tz);
}

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
#define is_sprites_enabled      (gb_mem[0xff40] & 0x02 ? 1:0)
#define sprite_height           (gb_mem[0xff40] & 0x04 ? 16:8)

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

bool    is_screen_yx_in_sprite(uint8_t *gb_mem, int y, int x, int sy, int sx)
{
//    printf("is_screen_yx_in_sprite() y=%d, x=%d, sy=%d, sx=%d\n",y,x,sy,sx);
    if ((y >= sy + 16) && (y <= (sy + 16 + sprite_height))) {
        if ((x >= sx + 8) && (x <= sx + 16)) {
            return true ;
        }
    }
    return false ;
}

int     get_obj_screen_pixel_yx(uint8_t *gb_mem, int y, int x)
{
    uint8_t *oam;

    oam = &gb_mem[0xfe00];
    for (uint8_t i = 0; i < 160; i += 4) {
        printf("%02x, %02x, %02x, %02x\n", oam[i], oam[i+1], oam[i+2], oam[i+3]);
        if (!is_screen_yx_in_sprite(gb_mem, y, x, oam[i], oam[i+1]))
            continue ;
        int coord_y = oam[i] + 16 + sprite_height - y;
        int coord_x = oam[i+1] +  8 + 8 - x;
//        printf("y = %d, x = %d, sprite = %d, coord y = %d, coord x = %d\n",y,x, oam[i+2], coord_y, coord_x);
    }
    return 0;
}


void    screen_update(uint8_t *gb_mem, t_state *state)
{
    uint8_t y, x, pixel;

    for (y = 0; y < 144; y++) {
        for (x = 0; x < 160; x++) {
            if (is_lcd_enabled && is_bg_wnd_enabled) {
                pixel = get_bg_screen_pixel_yx(gb_mem, y, x);
                state->screen_buf[y * 160 + x] = pixel;
            }
            if (is_window_pixel(gb_mem, y, x)) {
                pixel = get_wnd_screen_pixel_yx(gb_mem, y, x);
                state->screen_buf[y * 160 + x] = pixel;
            }
        }
    }
}

void    lcd_update(uint8_t *gb_mem, t_state *state, int current_cycles)
{
    static uint64_t lcd_cycle;
    static uint8_t  scanline;
    static bool     is_vblank;
    static bool     is_hblank;
    static bool     is_oam;
    static bool     is_lyc;

    if (!is_lcd_enabled) {
        gb_mem[0xff41] = (gb_mem[0xff41] & 0xfc) | 1;           //lcd disabled, mode 1
        lcd_cycle = 0;
        return ;
    }

    lcd_cycle += current_cycles;
    lcd_cycle %= 70224;

    gb_mem[0xff44] = lcd_cycle / 456;

    gb_mem[0xff41] &= 0xfb;                                     //clear coincidence bit
    if (gb_mem[0xff44] == gb_mem[0xff45]) {                     //ly == lyc ?
        gb_mem[0xff41] |= 4;                                    //set coincidence bit
        if (is_lyc) {
            is_lyc = false ;
            if (gb_mem[0xff41] & 0x40)
                gb_mem[0xff0f] |= 2;                            //request lcd interrupt
        }
    }                                                           //if coincidence bit enabled
    else {
        is_lyc = true;
    }

    if (gb_mem[0xff44] < 144) {
        if (lcd_cycle % 456 < 80) {            
            gb_mem[0xff41] &= 0xfc;
            gb_mem[0xff41] |= 2;                                //mode 2
            if (is_oam) {
                is_oam = false;
                if (gb_mem[0xff41] & 0x20)
                    gb_mem[0xff0f] |= 2;                        //request lcd
            }
        }
        else if (lcd_cycle % 456 < 252) {
            gb_mem[0xff41] &= 0xfc;
            gb_mem[0xff41] |= 3;                                //mode 3
            is_hblank = true;
        }
        else {
            gb_mem[0xff41] &= 0xfc;                             //mode 0
            if (is_hblank) {
                is_hblank = false;
                if (gb_mem[0xff41] & 0x08) {
                    gb_mem[0xff0f] |= 2;
                }                                               //request lcd                
                screen_update(gb_mem, state);
            }
            is_vblank = true;
        }
    }
    else {
        gb_mem[0xff41] &= 0xfc;
        gb_mem[0xff41] |= 1;                                    //mode 1        
        if (is_vblank) { 
            is_vblank = false;
            gb_mem[0xff0f] |= 1;                                //request vblank
            if (gb_mem[0xff41] & 0x10)
                gb_mem[0xff0f] |= 2;                            //request lcd
//            delay();
        }
        is_oam = true;
    }
}
