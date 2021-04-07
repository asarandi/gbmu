#include "gb.h"
#include "hardware.h"

#define FRAME_DURATION  70224
#define IS_LCD_ENABLED  (gb_mem[rLCDC] & 0x80 ? 1:0)
#define IS_WND_ENABLED  (gb_mem[rLCDC] & 0x20 ? 1:0)
#define IS_BG_ENABLED   (gb_mem[rLCDC] & 0x01 ? 1:0) /* DMG specific */
#define IS_OBJ_ENABLED  (gb_mem[rLCDC] & 0x02 ? 1:0)
#define IS_OBJ_Y_FLIP   (obj_attr & 0x40 ? 1:0)
#define IS_OBJ_X_FLIP   (obj_attr & 0x20 ? 1:0)

uint8_t bg_pixel(uint8_t *gb_mem, uint8_t y, uint8_t x, int win) {
    uint16_t addr;
    uint8_t *data, a, b;

    if (win) {
        y -= gb_mem[rWY];
        x = x - gb_mem[rWX] + 7;
        b = LCDCF_WIN9C00;
    } else {
        y += gb_mem[rSCY];
        x += gb_mem[rSCX];
        b = LCDCF_BG9C00;
    }

    addr = (gb_mem[rLCDC] & b) ? 0x9c00 : 0x9800;
    addr += ((y >> 3) << 5) + (x >> 3);

    if (gb_mem[rLCDC] & LCDCF_BG8000) {
        data = &gb_mem[0x8000 + ((uint8_t)gb_mem[addr] << 4)];
    } else {
        data = &gb_mem[0x9000 + ((int8_t)gb_mem[addr] << 4)];
    }

    data += (y & 7) << 1;
    a = *data, b = *(++data);
    return ((a >> (7 - (x & 7))) & 1) | (((b >> (7 - (x & 7))) << 1) & 3);
}

bool is_window_pixel(uint8_t *gb_mem, uint8_t y, uint8_t x) {
    if (!(gb_mem[rLCDC] & LCDCF_WINON)) {
        return false;
    }

    if ((gb_mem[rWY] > 143) || (gb_mem[rWX] > 166)) {
        return false;
    }

    return (y >= gb_mem[rWY]) && ((x + 7) >= gb_mem[rWX]);
}

uint8_t get_sprite_pixel(uint8_t *gb_mem, uint8_t idx, uint8_t y, uint8_t x) {
    uint8_t *oam, obj_height, coord_y, coord_x, obj_num, obj_attr;
    uint8_t *tile_data, tile0, tile1, pixel;

    if ((idx == 0xff) || (!IS_OBJ_ENABLED)) {
        return 0;
    }

    oam = &gb_mem[0xfe00];
    obj_height = (gb_mem[rLCDC] & 4) ? 16 : 8;
    coord_y = (y + 16 - oam[idx]) % obj_height;
    coord_x = (x + 8 - oam[idx + 1]) % 8;
    obj_num = oam[idx + 2];
    obj_attr = oam[idx + 3];

    if (obj_height == 16) {
        obj_num &= 0xfe;
    }

    if (IS_OBJ_Y_FLIP) {
        coord_y = (obj_height - 1) - coord_y;
    }

    if (IS_OBJ_X_FLIP) {
        coord_x = 7 - coord_x;
    }

    tile_data = &gb_mem[0x8000 + (obj_num * 16)];
    tile0 = tile_data[coord_y * 2];
    tile1 = tile_data[coord_y * 2 + 1];
    pixel = ((tile0 >> (7 - (coord_x))) & 1) |
            (((tile1 >> (7 - (coord_x))) << 1) & 3);

    if (!pixel) {
        return 0;
    }

    return (pixel | (obj_attr & 0xf0));
}

static int sprites_compare_dmg(const void *a, const void *b) {
    /* dmg priority */
    int m = gb_mem[_OAMRAM + *(uint8_t *)a + 1];
    int n = gb_mem[_OAMRAM + *(uint8_t *)b + 1];
    return m - n;
}

//static int sprites_compare_cgb(const void *a, const void *b) {
//    /* cgb priority */
//    return (int)(*(uint8_t *)a - *(uint8_t *)b);
//}

/* fills `uint8_t *sprites' with indexes to oam */
void get_sprites(uint8_t *gb_mem, uint8_t lcd_y, uint8_t *sprites) {
    uint8_t *oam = &gb_mem[0xfe00];
    uint8_t idx, sprites_idx, obj_y;
    uint8_t obj_height = (gb_mem[rLCDC] & 4) ? 16 : 8;
    (void)memset(sprites, 0xff, 10);

    if (!IS_OBJ_ENABLED) {
        return;
    }

    idx = 0;
    sprites_idx = 0;

    for (idx = 0; idx < 160; idx += 4) {
        obj_y = oam[idx];

        if ((obj_y == 0) || (obj_y > 160)) {
            continue;
        }

        if ((obj_y <= 8) && (obj_height == 8)) {
            continue;
        }

        if ((lcd_y + 16 >= obj_y) && (lcd_y + 16 < obj_y + obj_height)) {
            sprites[sprites_idx++] = idx;
        }

        if (sprites_idx >= 10) {
            break;
        }
    }

    (void)qsort(sprites, sprites_idx, 1, &sprites_compare_dmg);
}

void screen_mask() {
    /* freeze */
    if (!state->screen_mask) {
        return;
    }

    (void)memset(state->screen_buf, 0, sizeof(state->screen_buf));
}

void draw_bg(uint8_t *out, uint8_t *bg_data, uint8_t y) {
    uint8_t pal = gb_mem[rBGP], p, x;

    for (x = 0; x < 160; x++) {
        if (is_window_pixel(gb_mem, y, x)) {
            p = bg_pixel(gb_mem, y, x, 1);
        } else {
            p = bg_pixel(gb_mem, y, x, 0);
        }

        out[x] = (pal >> ((p & 3) << 1)) & 3;
        bg_data[x]= p;
    }
}


void screen_update(uint8_t *gb_mem, t_state *state, uint8_t *sprites) {
    uint8_t y = gb_mem[rLY], x, i, p, pal;
    uint8_t obj_data[160] = {0}, bg_data[160] = {0};
    uint8_t oam_idx;
    uint8_t *oam = &gb_mem[_OAMRAM];
    uint8_t *out = &state->screen_buf[y * 160];

    if (y > 143) {
        return;
    }

    if (state->screen_mask) {
        (void)screen_mask();
        return;
    }

    (void)memset(obj_data, 0, 160);
    (void)memset(bg_data, 0, 160);
    (void)memset(out, 0, 160);

    if (gb_mem[rLCDC] & LCDCF_BGON) {
        draw_bg(out, bg_data, y);
    }

    for (i = 0; i < 10; i++) {
        oam_idx = sprites[i];

        if (oam_idx == 0xff) {
            break;
        }

        for (x = 0; x < 160; x++) {
            if (obj_data[x]) {
                continue;
            }

            if (x + 8 < oam[oam_idx + 1]) {
                continue;
            }

            if (x >= oam[oam_idx + 1]) {
                break;
            }

            p = get_sprite_pixel(gb_mem, oam_idx, y, x);

            if (!p) {
                continue;
            }

            if (((p & 0x80) == 0) || (bg_data[x] == 0)) {
                pal = (p & 0x10) ? gb_mem[rOBP1] : gb_mem[rOBP0];
                out[x] = (pal >> ((p & 3) << 1)) & 3;
            }

            obj_data[x] = p;
        }
    }
}

int lcd_update(uint8_t *gb_mem, t_state *state, int current_cycles) {
    static bool is_vblank, is_hblank, is_oam, is_lyc, is_get_sprites;
    static int lcd_cycle;
    static uint8_t sprites[10];
    uint8_t i;
    uint16_t dma_source;
    int render;
    render = 0;

    if (!IS_LCD_ENABLED) {
        (void)memset(state->screen_buf, 0, sizeof(state->screen_buf));
        gb_mem[rSTAT] &= 0xfc;
        gb_mem[rLY] = 0;
        lcd_cycle = 0;
        return render;
    }

    lcd_cycle += current_cycles;
    lcd_cycle %= FRAME_DURATION;
    gb_mem[rLY] = lcd_cycle / 456;

    /* set coincidence bit */
    if (gb_mem[rLY] == gb_mem[rLYC]) {
        gb_mem[rSTAT] |= 4;

        if (is_lyc) {
            is_lyc = false;

            if (gb_mem[rSTAT] & 0x40) {
                gb_mem[rIF] |= 2;
            }
        }
    } else {
        /* clear coincidence bit */
        gb_mem[rSTAT] &= 0xfb;
        is_lyc = true;
    }

    if (gb_mem[rLY] < 144) {
        if ((lcd_cycle % 456) < 80) {
            /* mode 2 */
            gb_mem[rSTAT] = (gb_mem[rSTAT] & 0xfc) | 2;

            if (is_oam) {
                is_oam = false;

                /* irq */
                if (gb_mem[rSTAT] & 0x20) {
                    gb_mem[rIF] |= 2;
                }
            }

            is_get_sprites = true;
        } else if ((lcd_cycle % 456) < 252) {
            if (is_get_sprites) {
                is_get_sprites = false;
                get_sprites(gb_mem, gb_mem[rLY], sprites);
            }

            /* mode 3 */
            gb_mem[rSTAT] = (gb_mem[rSTAT] & 0xfc) | 3;
            is_hblank = true;
        } else {
            /* mode 0 */
            gb_mem[rSTAT] &= 0xfc;

            if (is_hblank) {
                is_hblank = false;
                screen_update(gb_mem, state, sprites);

                /* irq */
                if (gb_mem[rSTAT] & 0x08) {
                    gb_mem[rIF] |= 2;
                }
            }

            is_vblank = true;
        }
    } else {
        /* mode 1 */
        gb_mem[rSTAT] = (gb_mem[rSTAT] & 0xfc) | 1;

        /* request vblank */
        if (is_vblank) {
            is_vblank = false;
            render = 1;
            gb_mem[rIF] |= 1;

            /* irq */
            if (gb_mem[rSTAT] & 0x10) {
                gb_mem[rIF] |= 2;
            }
        }

        is_oam = true;
    }

    if (state->dma_update) {
        state->dma_update = false;
        dma_source = gb_mem[rDMA] << 8;

        for (i = 0; i < 0xa0; i++) {
            gb_mem[_OAMRAM + i] = read_u8(dma_source + i);
        }
    }

    return render;
}
