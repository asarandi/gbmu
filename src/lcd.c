#include "gb.h"
#include "hardware.h"

#define FRAME_DURATION  70224

uint8_t bg_pixel(struct gameboy *gb, uint8_t y, uint8_t x, int win) {
    uint16_t addr;
    uint8_t *data, a, b;

    if (win) {
        x = x - gb->memory[rWX] + 7;
        b = LCDCF_WIN9C00;
    } else {
        y += gb->memory[rSCY];
        x += gb->memory[rSCX];
        b = LCDCF_BG9C00;
    }

    addr = (gb->memory[rLCDC] & b) ? 0x9c00 : 0x9800;
    addr += ((y >> 3) << 5) + (x >> 3);

    if (gb->memory[rLCDC] & LCDCF_BG8000) {
        data = &gb->memory[0x8000 + ((uint8_t)gb->memory[addr] << 4)];
    } else {
        data = &gb->memory[0x9000 + ((int8_t)gb->memory[addr] << 4)];
    }

    data += (y & 7) << 1;
    a = *data, b = *(++data);
    return ((a >> (7 - (x & 7))) & 1) | (((b >> (7 - (x & 7))) << 1) & 3);
}

bool is_window_pixel(struct gameboy *gb, uint8_t y, uint8_t x) {
    if (!(gb->memory[rLCDC] & LCDCF_WINON)) {
        return false;
    }

    if ((gb->memory[rWY] > 143) || (gb->memory[rWX] > 166)) {
        return false;
    }

    return (y >= gb->memory[rWY]) && ((x + 7) >= gb->memory[rWX]);
}

uint8_t get_sprite_pixel(struct gameboy *gb, int i, uint8_t y, uint8_t x) {
    uint8_t obj_height, coord_y, coord_x, obj_num;
    uint8_t *tile_data, tile0, tile1, pixel;
    struct OAM_ATTRS *obj;

    if (!(gb->memory[rLCDC] & LCDCF_OBJON)) {
        return 0;
    }

    obj = gb->sprites[i];
    obj_height = (gb->memory[rLCDC] & LCDCF_OBJ16) ? 16 : 8;
    coord_y = (y + 16 - obj->OAMA_Y) % obj_height;
    coord_x = (x + 8 - obj->OAMA_X) % 8;
    obj_num = obj->OAMA_TILEID;

    if (obj_height == 16) {
        obj_num &= 0xfe;
    }

    if (obj->OAMA_FLAGS & OAMF_YFLIP) {
        coord_y = (obj_height - 1) - coord_y;
    }

    if (obj->OAMA_FLAGS & OAMF_XFLIP) {
        coord_x = 7 - coord_x;
    }

    tile_data = &gb->memory[_VRAM + (obj_num << 4)];
    tile0 = tile_data[coord_y << 1];
    tile1 = tile_data[(coord_y << 1) + 1];
    pixel = ((tile0 >> (7 - (coord_x))) & 1) |
            (((tile1 >> (7 - (coord_x))) << 1) & 3);

    if (!pixel) {
        return 0;
    }

    return (pixel | (obj->OAMA_FLAGS & 0xf0));
}

void get_sprites(struct gameboy *gb) {
    int i, j, ct, hgt, ly;
    struct OAM_ATTRS *obj;

    if (!(gb->memory[rLCDC] & LCDCF_OBJON)) {
        return;
    }

    (void)memset(gb->sprites, 0, sizeof(gb->sprites));
    hgt = (gb->memory[rLCDC] & 4) ? 16 : 8;
    ly = gb->memory[rLY];

    for (i = ct = 0; (i < 40) && (ct < 10); i++) {
        obj = (struct OAM_ATTRS *)&gb->memory[_OAMRAM + (i << 2)];

        if ((obj->OAMA_Y == 0) || (obj->OAMA_Y > 160)) {
            continue;
        }

        if ((obj->OAMA_Y <= 8) && (hgt == 8)) {
            continue;
        }

        if (!((ly + 16 >= obj->OAMA_Y) && (ly + 16 < obj->OAMA_Y + hgt))) {
            continue;
        }

        j = ct;

        while ((j > 0) && (gb->sprites[j - 1]->OAMA_X > obj->OAMA_X)) {
            gb->sprites[j] = gb->sprites[j - 1];
            --j;
        }

        gb->sprites[j] = obj;
        ++ct;
    }
}

void draw_bg(struct gameboy *gb, uint8_t *out, uint8_t *bg_data, uint8_t y) {
    uint8_t pal = gb->memory[rBGP], p, x;
    static uint8_t wy, wq; // window line counter

    if (y == 0) {
        wy = 0;
    }

    for (x = wq = 0; x < 160; x++) {
        if (is_window_pixel(gb, y, x)) {
            p = bg_pixel(gb, wy, x, 1);
            wq = 1;
        } else {
            p = bg_pixel(gb, y, x, 0);
        }

        out[x] = (pal >> ((p & 3) << 1)) & 3;
        bg_data[x] = p;
    }

    wy += wq;
}

void screen_update(struct gameboy *gb) {
    uint8_t y = gb->memory[rLY], x, i, p, pal;
    uint8_t obj_data[160] = {0}, bg_data[160] = {0};
    uint8_t *out = &gb->screen_buf[y * 160];

    if (y > 143) {
        return;
    }

    (void)memset(out, 0, 160);
    (void)memset(bg_data, 0, 160);

    if (gb->memory[rLCDC] & LCDCF_BGON) {
        (void)draw_bg(gb, out, bg_data, y);
    } else {
        (void)memset(out, gb->memory[rBGP] & 3, 160);
    }

    if (!(gb->memory[rLCDC] & LCDCF_OBJON)) {
        return;
    }

    (void)memset(obj_data, 0, 160);

    for (i = 0; i < 10; i++) {
        if (!gb->sprites[i]) {
            break;
        }

        for (x = 0; x < 160; x++) {
            if (obj_data[x]) {
                continue;
            }

            if (x + 8 < gb->sprites[i]->OAMA_X) {
                continue;
            }

            if (x >= gb->sprites[i]->OAMA_X) {
                break;
            }

            p = get_sprite_pixel(gb, i, y, x);

            if (!p) {
                continue;
            }

            if ((!(p & OAMF_PRI)) || (!(bg_data[x]))) {
                pal = (p & OAMF_PAL1) ? gb->memory[rOBP1] : gb->memory[rOBP0];
                out[x] = (pal >> ((p & 3) << 1)) & 3;
            }

            obj_data[x] = p;
        }
    }
}

int lcd_update(struct gameboy *gb) {
    const uint32_t nskipfram = 1; // skip first frame after lcd on
    static uint32_t on, lcd_cycle, frames;
    gb->video_render = 0;

    if (gb->memory[rLCDC] & LCDCF_ON) {
        on = 1;
    } else if (on) {
        gb->memory[rSTAT] &= ~STATF_LCD;
        gb->memory[rLY] = on = frames = 0;
        lcd_cycle = 252; // start in mode 0
        // show "blank" screen when lcd off
        (void)memset(gb->screen_buf, 0, sizeof(gb->screen_buf));
        gb->video_render = 1;
        return gb->video_render;
    } else {
        return gb->video_render;
    }

    gb->memory[rLY] = lcd_cycle / 456;

    if (gb->memory[rLY] == gb->memory[rLYC]) {
        gb->memory[rSTAT] |= STATF_LYCF;
        gb->cpu.stat_irq = (gb->memory[rSTAT] & STATF_LYC) ? true : false;
    } else {
        gb->memory[rSTAT] &= ~STATF_LYCF;
        gb->cpu.stat_irq = false;
    }

    if (gb->memory[rLY] < 144) {
        // mode 2
        if ((lcd_cycle % 456) < 80) {
            if (gb->memory[rSTAT] & STATF_MODE10) {
                gb->cpu.stat_irq |= true;
            }

            gb->memory[rSTAT] = (gb->memory[rSTAT] & ~STATF_LCD) | STATF_OAM;
        } else if ((lcd_cycle % 456) < 252) {
            // mode 3
            if ((gb->memory[rSTAT] & STATF_LCD) == STATF_OAM) { //once
                if (frames >= nskipfram) {
                    get_sprites(gb);
                }
            }

            gb->memory[rSTAT] |= STATF_LCD;
        } else {
            // mode 0
            if ((gb->memory[rSTAT] & STATF_LCD) == STATF_LCD) { //once
                if (frames >= nskipfram) {
                    screen_update(gb);
                }
            }

            if (gb->memory[rSTAT] & STATF_MODE00) {
                gb->cpu.stat_irq |= true;
            }

            gb->memory[rSTAT] &= ~STATF_LCD;
        }
    } else {
        // mode 1
        if (!(gb->memory[rSTAT] & STATF_VBL)) { //once
            if (gb->memory[rSTAT] & STATF_MODE10) {
                gb->cpu.stat_irq |= true;
            }

            gb->memory[rIF] |= IEF_VBLANK;

            if (frames >= nskipfram) {
                gb->video_render = 1;
            }

            ++frames;
        }

        if (gb->memory[rSTAT] & STATF_MODE01) {
            gb->cpu.stat_irq |= true;
        }

        gb->memory[rSTAT] = (gb->memory[rSTAT] & ~STATF_LCD) | STATF_VBL;
    }

    lcd_cycle += 4;
    lcd_cycle %= FRAME_DURATION;
    return gb->video_render;
}

uint8_t dma_read_u8(struct gameboy *gb, uint16_t addr) {
    if (addr < _VRAM) {
        return gb->rom_read_u8(gb, addr);
    }

    if ((addr >= _SRAM) && (addr < _SRAM + 0x2000)) {
        return gb->ram_read_u8(gb, addr);
    }

    return gb->memory[addr];
}

void dma_update(struct gameboy *gb) {
    if (gb->dma.clocks) {
        gb->dma.clocks -= 4;

        if (!gb->dma.clocks) {
            gb->dma.active = 1;
            gb->dma.index = 0;
            gb->dma.source = gb->memory[rDMA] << 8;

            if (gb->dma.source > 0xdfff) {
                gb->dma.source &= 0xdfff;
            }
        }
    }

    if (gb->dma.active) {
        gb->dma.byte = dma_read_u8(gb, gb->dma.source + gb->dma.index);
        gb->memory[_OAMRAM + gb->dma.index] = gb->dma.byte;
        gb->dma.active = (++gb->dma.index < 0xa0);
    }
}
