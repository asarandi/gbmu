#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "gb.h"


extern void (*ops0[])(void *, t_state *, uint8_t *);
extern void (*ops1[])(void *, t_state *, uint8_t *);
extern int byte_lens0[];
extern int byte_lens1[];
extern char* op_names0[];
extern char* op_names1[];
extern unsigned char DMG_ROM_bin[];
extern int get_num_cycles(void *gb_reg, void *gb_mem);


void    dump_background(uint8_t *gb_mem)
{
    char *s = "0123";

    uint8_t *background = malloc(0x10000);
//    (void)memset(background,0,0x10000);
    uint8_t lcdc = gb_mem[0xff40];
    int bg_tile_map_idx;
    int bg_tile_data_idx;
    int tile_idx;
    uint8_t* tile_data;

    bg_tile_map_idx = (lcdc & 0xf) ? 0x9800 : 0x9c00;
    bg_tile_data_idx = (lcdc & 0x1f) ? 0x8000 : 0x8800;

    for (int y=0; y<32; y++) {
        for (int x=0; x<32; x++) {

            tile_idx = gb_mem[bg_tile_map_idx + ((y*32)+x)];
            tile_data = &gb_mem[bg_tile_data_idx + (tile_idx * 16)];    //16 bytes of tile data
            for (int j=0; j<8; j++) {
                uint8_t tile_byte0 = tile_data[j*2];
                uint8_t tile_byte1 = tile_data[j*2+1];
                for (int bit=0; bit<8; bit++) {
                    int color_idx = (tile_byte0 >> (7-bit)) & 1;
                    color_idx |= ((tile_byte1 >> (7-bit)) & 1) << 1;
                    int dst_idx = (y*8*256)+(x*8)+(j*256)+bit;
                    background[dst_idx] = s[color_idx];
                }
            }
        }
    }

    int fd = open("background.dump", O_WRONLY | O_CREAT, 0644);
    for (int i=0;i<0x100;i++) {
        write(fd, &background[i*0x100], 0x100);
        write(fd, "\n", 1);
    }
    close(fd);

}




void dump_ram(void *ram)
{
    int fd = open("mem.dump", O_CREAT | O_WRONLY, 0644);
    write(fd, ram, 0x10000);
    close(fd);
}

void dump_registers(void *registers, void *gb_state, uint8_t *gb_mem)
{
    int         byte_len;
    int         idx;
    char        *op_name;
    t_r16       *r16 = registers;
    t_r8        *r8 = registers;
    uint8_t     u8;
    uint16_t    u16;
    char z = is_z_flag ? 'Z' : '-';
    char n = is_n_flag ? 'N' : '-';
    char h = is_h_flag ? 'H' : '-';
    char c = is_c_flag ? 'C' : '-';

    printf("A: %02X  F: %02X  (AF: %04X)\n", r8->A, r8->F, r16->AF);
    printf("B: %02X  C: %02X  (BC: %04X)\n", r8->B, r8->C, r16->BC);
    printf("D: %02X  E: %02X  (DE: %04X)\n", r8->D, r8->E, r16->DE);
    printf("H: %02X  L: %02X  (HL: %04X)\n", r8->H, r8->L, r16->HL);
    printf("PC: %04X  SP: %04X\n", r16->PC, r16->SP);
    printf("ROM: %02X  RAM: %02X  WRAM: %02X  VRAM: %02X\n", 1, 0, 1, 0);
    printf("F: [%c%c%c%c]\n", z,n,h,c);

    printf("%02X:%04X:  ", 0, r16->PC);

    idx = gb_mem[r16->PC];
    byte_len = byte_lens0[idx];
    op_name = op_names0[idx];

    if (idx == 0xcb) {
        idx = gb_mem[r16->PC + 1];
        byte_len = byte_lens1[idx];
        op_name = op_names1[idx];
    }
    for (int i = 0; i < byte_len; i++) {
        printf("%02X", gb_mem[r16->PC + i]);
    }

    printf("\t");

    u8 = gb_mem[r16->PC + 1];
    u16 = *(uint16_t *)&gb_mem[r16->PC + 1];

    if (strstr(op_name, "%02"))
        printf(op_name, u8);
    else if (strstr(op_name, "%04"))
        printf(op_name, u16);
    else        
        printf("%s", op_name);

    printf("\n>\n");
}

int main(int ac, char **av)
{

    int         fd;
    void        *registers;
    t_r16       *r16;
    t_r8        *r8;
    void        *gb_state;
    t_state     *state;
    void        *gb_mem;    
    uint8_t     *mem;
    uint8_t     op0;
    uint8_t     op1;
    struct stat stat_buf;
    void (*f)(void *, t_state *, uint8_t *);
    int         op_cycles;





    if (ac != 2)
        return 1;

    if ((fd = open(av[1], O_RDONLY)) == -1) {
        printf("failed to open file\n");
        return 1;
    }

    if (fstat(fd, &stat_buf) != 0) {
        close(fd);
        printf("fstat() failed\n");
        return 1;
    }

    
    if (stat_buf.st_size != 0x8000) {
        close(fd);
        printf("unsupported file format\n");
        return 1;
    }

    registers = malloc(sizeof(t_r8));
    (void)memset(registers, 0, sizeof(t_r8));
    r16 = registers;
    r8 = registers;

    gb_state = malloc(sizeof(t_state));
    (void)memset(gb_state, 0, sizeof(t_state));    
    state = gb_state;

    gb_mem = malloc(0x10000);
    (void)memset(gb_mem, 0, 0x10000);
    mem = gb_mem;


    if (read(fd, gb_mem, 0x8000) != 0x8000) {
        printf("read() failed\n");
    }
    close(fd);

    /* default register values as per mgba debugger */

    r16->AF = 0x0000;
    r16->BC = 0x0000;
    r16->DE = 0x0000;
    r16->HL = 0x0000;
    r16->SP = 0x0000;
    r16->PC = 0x0000;

    (void)memcpy(mem, DMG_ROM_bin, 0x100);
    int zum = 0;
    while (true)
    {
        op0 = mem[r16->PC];
        op1 = mem[r16->PC + 1];
        f = ops0[op0];
        if (op0 == 0xcb)
            f = ops1[op1];
        dump_registers(registers, gb_state, gb_mem);
        op_cycles = get_num_cycles(registers, gb_mem);
        printf("total cycles: %08lu, this op cycles: %02d\n", state->cycles, op_cycles);

        f(registers, gb_state, gb_mem);

        state->cycles += op_cycles;

        if (r16->PC == 0x68){
            dump_ram(mem);
             break ; }
    }

    dump_background(gb_mem);

    free(gb_mem);
    free(gb_state);
    free(registers);

    return 0;
}
