#include "gb.h"

#define FRAME_DURATION          70224
#define IS_LCD_ENABLED          (gb_mem[0xff40] & 0x80 ? 1:0)
#define IS_WND_ENABLED          (gb_mem[0xff40] & 0x20 ? 1:0)
#define IS_BG_ENABLED           (gb_mem[0xff40] & 0x01 ? 1:0)                   /* DMG specific XXX */
#define IS_OBJ_ENABLED          (gb_mem[0xff40] & 0x02 ? 1:0)
#define IS_OBJ_Y_FLIP           (obj_attr & 0x40 ? 1:0)
#define IS_OBJ_X_FLIP           (obj_attr & 0x20 ? 1:0)

uint8_t    get_bg_pixel_yx(uint8_t *gb_mem, uint8_t y, uint8_t x)
{
    uint16_t    tile_map_addr, tile_data_addr, tile_idx_addr;
    uint8_t     tile_byte0, tile_byte1, tile_idx, pixel, *tile_data;
    int8_t      idxi;

    y += gb_mem[0xff42];
    x += gb_mem[0xff43];
    tile_map_addr = (gb_mem[0xff40] & 0x08) ? 0x9c00 : 0x9800;              /* lcdc bit 3 */
    tile_data_addr = (gb_mem[0xff40] & 0x10) ? 0x8000 : 0x8800;             /* lcdc bit 4 */
    tile_idx_addr = ((y>>3)<<5)+(x>>3);
    tile_idx = gb_mem[tile_map_addr + tile_idx_addr];
    tile_data = &gb_mem[tile_data_addr + (tile_idx << 4)];
    if (tile_data_addr == 0x8800) {
        idxi = (int8_t)gb_mem[tile_map_addr + tile_idx_addr];
        tile_data = &gb_mem[0x9000 + (idxi * 16)];
    }
    tile_byte0 = tile_data[(y % 8) * 2];
    tile_byte1 = tile_data[(y % 8) * 2 + 1];
    pixel = ((tile_byte0 >> (7-(x%8))) & 1) | (((tile_byte1 >> (7-(x%8))) << 1) & 3);
    return pixel;
}

uint8_t get_wnd_pixel_yx(uint8_t *gb_mem, uint8_t y, uint8_t x)
{
    int tile_map_addr, tile_data_addr;
    uint16_t tile_idx_addr;
    uint8_t tile_idx, *tile_data, tile_byte0, tile_byte1, pixel;
    int8_t idxi;

    y -= gb_mem[0xff4a];
    x -= gb_mem[0xff4b];
    x += 7;
    tile_map_addr = (gb_mem[0xff40] & 0x40) ? 0x9c00 : 0x9800;              /* bit 6     */
    tile_data_addr = (gb_mem[0xff40] & 0x10) ? 0x8000 : 0x8800;             /* lcdc bit 4 */
    tile_idx_addr = ((y>>3)<<5)+(x>>3);
    tile_idx = gb_mem[tile_map_addr + tile_idx_addr];
    tile_data = &gb_mem[tile_data_addr + (tile_idx << 4)];
    if (tile_data_addr == 0x8800) {
        idxi = (int8_t)gb_mem[tile_map_addr + tile_idx_addr];
        tile_data = &gb_mem[0x9000 + (idxi * 16)];
    }
    tile_byte0 = tile_data[(y % 8) * 2];
    tile_byte1 = tile_data[(y % 8) * 2 + 1];
    pixel = ((tile_byte0 >> (7-(x%8))) & 1) | (((tile_byte1 >> (7-(x%8))) << 1) & 3);
    return pixel;
}

bool    is_window_pixel(uint8_t *gb_mem, uint8_t y, uint8_t x)
{
    uint8_t wy, wx;

    wy = gb_mem[0xff4a];
    wx = gb_mem[0xff4b];
    if (!IS_WND_ENABLED)
        return false ;
    if ((wy > 143) || (wx > 166))
        return false ;
    if ((y >= wy) && (x + 7 >= wx))                 /* current pixel is in window region */
        return true ;
    return false ;
}

uint8_t     get_sprite_pixel(uint8_t *gb_mem, uint8_t idx, uint8_t y, uint8_t x)
{
    uint8_t *oam, obj_height, coord_y, coord_x, obj_num, obj_attr;
    uint8_t *tile_data, tile_byte0, tile_byte1, pixel;

    if ((idx == 0xff) || (!IS_OBJ_ENABLED))
        return 0;
    oam = &gb_mem[0xfe00];
    obj_height = (gb_mem[0xff40] & 4) ? 16 : 8;
    coord_y = (y + 16 - oam[idx]) % obj_height;
    coord_x = (x + 8 - oam[idx + 1]) % 8;
    obj_num = oam[idx + 2];
    obj_attr = oam[idx + 3];
    if (obj_height == 16)
        obj_num &= 0xfe;
    if (IS_OBJ_Y_FLIP)
        coord_y = (obj_height-1) - coord_y;
    if (IS_OBJ_X_FLIP)
        coord_x = 7 - coord_x;
    tile_data = &gb_mem[0x8000 + (obj_num * 16)];
    tile_byte0 = tile_data[coord_y * 2];
    tile_byte1 = tile_data[coord_y * 2 + 1];
    pixel = ((tile_byte0 >> (7-(coord_x))) & 1) | (((tile_byte1 >> (7-(coord_x))) << 1) & 3);
    if (!pixel)
        return 0;
    return (pixel | (obj_attr & 0xf0));
}

int sprites_compare(const void *alpha, const void *beta)
{
    /* dmg priority */

    /*
     * return (gb_mem[0xfe00 + *(uint8_t*)alpha + 1] - gb_mem[0xfe00 + *(uint8_t*)beta + 1]);
     * */
    return (int)(*(uint8_t*)alpha - *(uint8_t*)beta);   /* cgb priority */
}

/* fills `uint8_t *sprites' with indexes to oam */
void    get_sprites(uint8_t *gb_mem, uint8_t lcd_y, uint8_t *sprites)
{
    uint8_t     *oam = &gb_mem[0xfe00];
    uint8_t     idx, sprites_idx, obj_y;
    uint8_t     obj_height = (gb_mem[0xff40] & 4) ? 16 : 8;

    (void)memset(sprites, 0xff, 10);
    if (!IS_OBJ_ENABLED) return ;

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
    (void)qsort(sprites, sprites_idx, 1, &sprites_compare);
}

void    screen_mask()
{
    uint8_t color_0 = gb_mem[0xff47] & 3;

    if (state->screen_mask == 0)                                /*freeze*/
        return ;
    if (state->screen_mask == 2)
        (void)memset(state->screen_buf, 3, 144*160);            /*black*/
    if (state->screen_mask == 3)
        (void)memset(state->screen_buf, color_0, 144*160);      /*color 0*/
}

void    screen_update(uint8_t *gb_mem, t_state *state, uint8_t *sprites)
{

    uint8_t     y, x, i;
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
    if (state->screen_mask) {
        (void)screen_mask();
        return ;
    }

    (void)memset(bg_data, 0, 160);
    (void)memset(obj_data, 0, 160);
    (void)memset(&state->screen_buf[y * 160], 0, 160);
    bg_pal = gb_mem[0xff47];

    for (x = 0; x < 160; x++) {
        if (IS_BG_ENABLED) {
            bg_pixel = get_bg_pixel_yx(gb_mem, y, x);
            bg_render = (bg_pal >> ((bg_pixel & 3) << 1)) & 3;
            state->screen_buf[y * 160 + x] = bg_render ;
            bg_data[x] = bg_pixel ;
        }
        if (is_window_pixel(gb_mem, y, x)) {
            wnd_pixel = get_wnd_pixel_yx(gb_mem, y, x);
            wnd_render = (bg_pal >> ((wnd_pixel & 3) << 1)) & 3;
            state->screen_buf[y * 160 + x] = wnd_render ;
            bg_data[x] = wnd_pixel ;
        }
    }

    for (i = 0; i < 10; i++) {
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

int    lcd_update(uint8_t *gb_mem, t_state *state, int current_cycles)
{
    static bool     is_vblank, is_hblank, is_oam, is_lyc, is_get_sprites;
    static int      lcd_cycle;
    static uint8_t  sprites[10];
    uint8_t         i;
    uint16_t        dma_source;
    int             render ;

    render = 0;

    if (!IS_LCD_ENABLED) {
        (void)memset(state->screen_buf, 0, 160*144);
        gb_mem[0xff41] &= 0xfc ;
        gb_mem[0xff44] = 0;
        lcd_cycle = 0;
        return render;
    }

    lcd_cycle += current_cycles;
    lcd_cycle %= FRAME_DURATION;

    gb_mem[0xff44] = lcd_cycle / 456;

    if (gb_mem[0xff44] == gb_mem[0xff45]) {                         /* ly == lyc ? */
        gb_mem[0xff41] |= 4;                                        /* set coincidence bit */
        if (is_lyc) {
            is_lyc = false ;
            if (gb_mem[0xff41] & 0x40)      gb_mem[0xff0f] |= 2;    /* irq */
        }
    }                                                               /* if coincidence bit enabled */
    else {
        gb_mem[0xff41] &= 0xfb;                                     /* clear coincidence bit */
        is_lyc = true;
    }

    if (gb_mem[0xff44] < 144) {
        if ((lcd_cycle % 456) < 80) {
            gb_mem[0xff41] = (gb_mem[0xff41] & 0xfc) | 2;           /* mode 2 */
            if (is_oam) {
                is_oam = false;
                if (gb_mem[0xff41] & 0x20)  gb_mem[0xff0f] |= 2;    /* irq */
            }
            is_get_sprites = true;
        } else if ((lcd_cycle % 456) < 252) {
            if (is_get_sprites) {
                is_get_sprites = false;
                get_sprites(gb_mem, gb_mem[0xff44], sprites);
            }
            gb_mem[0xff41] = (gb_mem[0xff41] & 0xfc) | 3;           /* mode 3 */
            is_hblank = true;
        } else {
            gb_mem[0xff41] &= 0xfc;                                 /* mode 0 */
            if (is_hblank) {
                is_hblank = false;
                screen_update(gb_mem, state, sprites);
                if (gb_mem[0xff41] & 0x08)  gb_mem[0xff0f] |= 2;    /* irq */
            }
            is_vblank = true;
        }
    } else {
        gb_mem[0xff41] = (gb_mem[0xff41] & 0xfc) | 1;               /* mode 1 */
        if (is_vblank) {
            is_vblank = false;
            render = 1;
            gb_mem[0xff0f] |= 1;                                    /* request vblank */
            if (gb_mem[0xff41] & 0x10)      gb_mem[0xff0f] |= 2;    /* irq */
        }
        is_oam = true;
    }
    if (state->dma_update) {
        state->dma_update = false ;
        dma_source = gb_mem[0xff46] << 8;
        for (i = 0; i < 0xa0; i++)
            gb_mem[0xfe00 + i] = read_u8(dma_source + i);
    }
    return render;
}
