#include "gb.h"

#define frame_duration          70224                                           //10 vblank scanlines
#define is_lcd_enabled          (gb_mem[0xff40] & 0x80 ? 1:0)
#define is_wnd_enabled          (gb_mem[0xff40] & 0x20 ? 1:0)
#define is_bg_enabled           (gb_mem[0xff40] & 0x01 ? 1:0)                   //DMG specific XXX
#define is_sprites_enabled      (gb_mem[0xff40] & 0x02 ? 1:0)
#define sprite_height           (gb_mem[0xff40] & 0x04 ? 16:8)
#define is_obj_y_flip           (obj_attr & 0x40 ? 1:0)
#define is_obj_x_flip           (obj_attr & 0x20 ? 1:0)


uint8_t    get_bg_screen_pixel_yx(uint8_t *gb_mem, uint8_t y, uint8_t x)
{
    y += gb_mem[0xff42];
    x += gb_mem[0xff43];
    uint16_t tile_map_addr = (gb_mem[0xff40] & 0x08) ? 0x9c00 : 0x9800;                 //lcdc bit 3
    uint16_t tile_data_addr = (gb_mem[0xff40] & 0x10) ? 0x8000 : 0x8800;             //lcdc bit 4
    uint16_t tile_idx_addr = ((y>>3)<<5)+(x>>3);
    uint8_t tile_idx = gb_mem[tile_map_addr + tile_idx_addr];
    uint8_t *tile_data = &gb_mem[tile_data_addr + (tile_idx << 4)];
    if (tile_data_addr == 0x8800)
    {
        int8_t idxi = (int8_t)gb_mem[tile_map_addr + tile_idx_addr];
        tile_data = &gb_mem[0x9000 + (idxi * 16)];
    }
    uint8_t tile_byte0 = tile_data[(y % 8) * 2];
    uint8_t tile_byte1 = tile_data[(y % 8) * 2 + 1];
    uint8_t pixel = ((tile_byte0 >> (7-(x%8))) & 1) | (((tile_byte1 >> (7-(x%8))) << 1) & 3);
    return pixel;
}

void    dump_background2(uint8_t *gb_mem, t_state *state)
{
    for (int y=0; y<144; y++) {
        for (int x=0;x<160; x++) {
            state->screen_buf[y*160+x] = (uint8_t)get_bg_screen_pixel_yx(gb_mem, y, x);
        }
    }
}

uint8_t get_wnd_screen_pixel_yx(uint8_t *gb_mem, uint8_t y, uint8_t x)
{

    y -= gb_mem[0xff4a];
    x -= gb_mem[0xff4b];
    x += 7;

    int tile_map_addr = (gb_mem[0xff40] & 0x40) ? 0x9c00 : 0x9800;              //bit 6
    int tile_data_addr = (gb_mem[0xff40] & 0x10) ? 0x8000 : 0x8800;             //lcdc bit 4
    uint16_t tile_idx_addr = ((y>>3)<<5)+(x>>3);
    uint8_t tile_idx = gb_mem[tile_map_addr + tile_idx_addr];
    uint8_t *tile_data = &gb_mem[tile_data_addr + (tile_idx << 4)];
    if (tile_data_addr == 0x8800)
    {
        int8_t idxi = (int8_t)gb_mem[tile_map_addr + tile_idx_addr];
        tile_data = &gb_mem[0x9000 + (idxi * 16)];
    }
    uint8_t tile_byte0 = tile_data[(y % 8) * 2];
    uint8_t tile_byte1 = tile_data[(y % 8) * 2 + 1];
    uint8_t pixel = ((tile_byte0 >> (7-(x%8))) & 1) | (((tile_byte1 >> (7-(x%8))) << 1) & 3);
    return pixel;
}

bool    is_window_pixel(uint8_t *gb_mem, int y, int x)
{
    int wy, wx;

    wy = gb_mem[0xff4a];
    wx = gb_mem[0xff4b];
    if (!is_wnd_enabled)
        return false ;
    if ((wy > 143) || (wx > 166))
        return false ;
    if ((y >= wy) && ((int)x  >= (int)wx-7))                                                 // current pixel is in window region
        return true ;
    return false ;
}

bool    is_sprite_candidate(uint8_t *gb_mem, int y, int x, int obj_y, int obj_x)
{
    uint8_t obj_height = (gb_mem[0xff40] & 4) ? 16 : 8;
    if ((obj_y == 0) || (obj_y > 160))
        return false;
    if ((obj_y <= 8) && (obj_height == 8))
        return false;
    if ((y + 16 >= obj_y) && (y + 16 < obj_y + obj_height)) {
        if ((x + 8 >= obj_x) && (x < obj_x)) {
            return true ;
        }
    }
    return false ;
}

uint8_t     get_sprite_pixel(uint8_t *gb_mem, int idx, int y, int x)
{
    if (idx == 0xff)
        return 0;
    uint8_t *oam = &gb_mem[0xfe00];
    uint8_t obj_height = (gb_mem[0xff40] & 4) ? 16 : 8;
    uint8_t coord_y = (y + 16 - oam[idx]) % obj_height;
    uint8_t coord_x = (x + 8 - oam[idx + 1]) % 8;
    uint8_t obj_num = oam[idx + 2];
    uint8_t obj_attr = oam[idx + 3];
    if (obj_height == 16)
        obj_num &= 0xfe;
    if (is_obj_y_flip)
        coord_y = (obj_height-1) - coord_y;
    if (is_obj_x_flip)
        coord_x = 7 - coord_x;
    uint8_t *tile_data = &gb_mem[0x8000 + (obj_num * 16)];
    uint8_t tile_byte0 = tile_data[coord_y * 2];
    uint8_t tile_byte1 = tile_data[coord_y * 2 + 1];
    uint8_t pixel = ((tile_byte0 >> (7-(coord_x))) & 1) | (((tile_byte1 >> (7-(coord_x))) << 1) & 3);
    if (!pixel)
        return 0;
    return (pixel | (obj_attr & 0xf0));
}

int sprites_compare(const void *alpha, const void *beta)
{
//    uint8_t *gb_mem = state->gameboy_memory;
//  return (gb_mem[0xfe00 + *(uint8_t*)alpha + 1] - gb_mem[0xfe00 + *(uint8_t*)beta + 1]);  /* dmg priority */
    return (int)(*(uint8_t*)alpha - *(uint8_t*)beta);   /* cgb priority */
}

/* fills `uint8_t *sprites' with indexes to oam */
void    get_first_ten_sprites(uint8_t *gb_mem, uint8_t lcd_y, uint8_t *sprites)
{
    uint8_t     *oam = &gb_mem[0xfe00];
    uint8_t     idx, sprites_idx, obj_y;

    uint8_t     obj_height = (gb_mem[0xff40] & 4) ? 16 : 8;

    idx = 0;
    sprites_idx = 0;
    for (idx = 0; idx < 160; idx += 4) {
        obj_y = oam[idx];
        if ((obj_y == 0) || (obj_y > 160))
            continue ;
        if ((obj_y <= 8) && (obj_height == 8))
            continue ;
        if ((lcd_y + 16 >= obj_y) && (lcd_y + 16 < obj_y + obj_height))
            sprites[sprites_idx++] = idx;
        if (sprites_idx >= 10)
            break ;
    }
    qsort(sprites, sprites_idx, 1, &sprites_compare);
    while (sprites_idx < 10)
        sprites[sprites_idx++] = 0xff;
}

void    screen_update(uint8_t *gb_mem, t_state *state)
{
    uint8_t        sprites[10] = {0xff};

    uint32_t    y, x;
    uint8_t     bg_pixel, wnd_pixel, obj_pixel;
    uint8_t     bg_pal, obj_pal;
    uint8_t     bg_render, wnd_render, obj_render;
    uint8_t     oam_idx;
    uint8_t     bg_data[160] = {0};
    uint8_t     obj_data[160] = {0};


    uint8_t     *oam = &gb_mem[0xfe00];

    y = gb_mem[0xff44];

    if (y > 143)
        return;

    memset(&state->screen_buf[y * 160], 0, 160);
    bg_pal = gb_mem[0xff47];

    for (x = 0; x < 160; x++) {
        if (is_bg_enabled) {
            bg_pixel = get_bg_screen_pixel_yx(gb_mem, y, x);
            bg_render = (bg_pal >> ((bg_pixel & 3) << 1)) & 3;
            state->screen_buf[y * 160 + x] = bg_render ;
            bg_data[x] = bg_pixel ;
        }
        if (is_window_pixel(gb_mem, y, x)) {
            wnd_pixel = get_wnd_screen_pixel_yx(gb_mem, y, x);
            wnd_render = (bg_pal >> ((wnd_pixel & 3) << 1)) & 3;
            state->screen_buf[y * 160 + x] = wnd_render ;
            bg_data[x] = wnd_pixel ;
        }
    }

    get_first_ten_sprites(gb_mem, y, sprites);

    for (int i = 0; i < 10; i++) {
        oam_idx = sprites[i];
        if (oam_idx == 0xff)
            break ;

        for (x = 0; x < 160; x++) {
            if (x + 8 < oam[oam_idx + 1])
                continue ;
            if (x >= oam[oam_idx + 1])
                break ;

            obj_pixel = get_sprite_pixel(gb_mem, oam_idx, y, x);
            if ((obj_pixel) && (obj_data[x] == 0)) {
                obj_pal = (obj_pixel & 0x10) ? gb_mem[0xff49] : gb_mem[0xff48];
                obj_render = (obj_pal >> ((obj_pixel & 3) << 1)) & 3;
                if (((obj_pixel & 0x80) == 0) || (bg_data[x] == 0))
                    state->screen_buf[y * 160 + x] = obj_render;
                obj_data[x] = 1;
            }
        }
    }
}

void    lcd_update(uint8_t *gb_mem, t_state *state, int current_cycles)
{
    static uint64_t lcd_cycle;
    static bool     is_vblank;
    static bool     is_hblank;
    static bool     is_oam;
    static bool     is_lyc;

    if (!is_lcd_enabled) {
        gb_mem[0xff41] = (gb_mem[0xff41] & 0xfc) | 1;                //lcd disabled, mode 1
        gb_mem[0xff44] = 0;
        lcd_cycle = 0;
        return ;
    }

    lcd_cycle += current_cycles;
    lcd_cycle %= 70224;

    gb_mem[0xff44] = lcd_cycle / 456;

    gb_mem[0xff41] &= 0xfb;                                          //clear coincidence bit
    if (gb_mem[0xff44] == gb_mem[0xff45]) {                          //ly == lyc ?
        gb_mem[0xff41] |= 4;                                         //set coincidence bit
        if (is_lyc) {
            is_lyc = false ;
            if (gb_mem[0xff41] & 0x40)
                gb_mem[0xff0f] |= 2;                                 //request lcd interrupt
        }
    }                                                                //if coincidence bit enabled
    else {
        is_lyc = true;
    }

    if (gb_mem[0xff44] < 144) {
        if (lcd_cycle % 456 < 80) {
            gb_mem[0xff41] &= 0xfc;
            gb_mem[0xff41] |= 2;                                     //mode 2
            if (is_oam) {
                is_oam = false;
                if (gb_mem[0xff41] & 0x20)
                    gb_mem[0xff0f] |= 2;                             //request lcd
            }
        }
        else if (lcd_cycle % 456 < 252) {
            gb_mem[0xff41] &= 0xfc;
            gb_mem[0xff41] |= 3;                                     //mode 3
            is_hblank = true;
        }
        else {
            gb_mem[0xff41] &= 0xfc;                                  //mode 0
            if (is_hblank) {
                screen_update(gb_mem, state);                        //blit
                is_hblank = false;
                if (gb_mem[0xff41] & 0x08) {
                    gb_mem[0xff0f] |= 2;
                }
            }
            is_vblank = true;
        }
    }
    else {
        gb_mem[0xff41] &= 0xfc;
        gb_mem[0xff41] |= 1;                                         //mode 1
        if (is_vblank) {
            is_vblank = false;
            gb_mem[0xff0f] |= 1;                                     //request vblank
            if (gb_mem[0xff41] & 0x10)
                gb_mem[0xff0f] |= 2;                                 //request lcd
//            delay();
        }
        is_oam = true;
    }
}
