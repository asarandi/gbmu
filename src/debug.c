#include "gb.h"

void dump_background(uint8_t *gb_mem) {
    const char s[] = "0123";
    uint8_t *background, lcdc, *tile_data, tile_byte0, tile_byte1;
    int bg_tile_map_idx, bg_tile_data_idx, y, x, i, j, bit, tile_idx, dst_idx, color_idx, fd;

    background = malloc(0x10000);
    (void)memset(background, 0, 0x10000);
    lcdc = gb_mem[0xff40];

    bg_tile_map_idx = (lcdc & 0x8) ? 0x9c00 : 0x9800;
    bg_tile_data_idx = (lcdc & 0x10) ? 0x8000 : 0x8800;

    for (y = 0; y < 32; y++) {
        for (x = 0; x < 32; x++) {
            tile_idx = gb_mem[bg_tile_map_idx + ((y * 32) + x)];
            tile_data = &gb_mem[bg_tile_data_idx + (tile_idx * 16)];    /*16 bytes of tile data*/
            for (j = 0; j < 8; j++) {
                tile_byte0 = tile_data[j * 2];
                tile_byte1 = tile_data[j * 2 + 1];
                for (bit = 0; bit < 8; bit++) {
                    color_idx = (tile_byte0 >> (7 - bit)) & 1;
                    color_idx |= ((tile_byte1 >> (7 - bit)) & 1) << 1;
                    dst_idx = (y * 8 * 256) + (x * 8) + (j * 256) + bit;
                    background[dst_idx] = s[color_idx];
                }
            }
        }
    }

    fd = open("background.dump", O_WRONLY | O_CREAT, 0644);
    for (i = 0; i < 0x100; i++) {
        (void)write(fd, &background[i * 0x100], 0x100);
        (void)write(fd, "\n", 1);
    }
    close(fd);
}

void dump_ram(void *ram) {
    int fd;

    fd = open("mem.dump", O_CREAT | O_WRONLY, 0644);
    (void)write(fd, ram, 0x10000);
    close(fd);
}

void dump_registers(void *registers, void *gb_state, uint8_t *gb_mem) {
    int byte_len, idx, i;
    char *op_name, z, n, h, c;
    t_r16 *r16 = registers;
    t_r8 *r8 = registers;
    uint8_t u8;
    uint16_t u16;

    z = IS_Z_FLAG ? 'Z' : '-';
    n = IS_N_FLAG ? 'N' : '-';
    h = IS_H_FLAG ? 'H' : '-';
    c = IS_C_FLAG ? 'C' : '-';

    (void)gb_state;
    (void)gb_mem;

    printf("A: %02X  F: %02X  (AF: %04X)\n", r8->A, r8->F, r16->AF);
    printf("B: %02X  C: %02X  (BC: %04X)\n", r8->B, r8->C, r16->BC);
    printf("D: %02X  E: %02X  (DE: %04X)\n", r8->D, r8->E, r16->DE);
    printf("H: %02X  L: %02X  (HL: %04X)\n", r8->H, r8->L, r16->HL);
    printf("PC: %04X  SP: %04X\n", r16->PC, r16->SP);
    printf("ROM: %02X  RAM: %02X  WRAM: %02X  VRAM: %02X\n", 1, 0, 1, 0);
    printf("F: [%c%c%c%c]\n", z, n, h, c);

    printf("%02X:%04X:  ", 0, r16->PC);

    idx = read_u8(r16->PC);
    byte_len = byte_lens0[idx];
    op_name = op_names0[idx];

    if (idx == 0xcb) {
        idx = read_u8(r16->PC + 1);
        byte_len = byte_lens1[idx];
        op_name = op_names1[idx];
    }
    for (i = 0; i < byte_len; i++) {
        printf("%02X", read_u8(r16->PC + i));
    }

    printf("\t");

    u8 = read_u8(r16->PC + 1);
    u16 = read_u16(r16->PC + 1);

    if (strstr(op_name, "%02"))
        printf(op_name, u8);
    else if (strstr(op_name, "%04"))
        printf(op_name, u16);
    else
        printf("%s", op_name);

    printf("\n>\n");
}

