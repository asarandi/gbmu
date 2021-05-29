#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// 0, 1, 2, 3, 4, 5,    6, 7
// b, c, d, e, h, l, (hl), a
// opcode 0x76 => halt

struct gameboy {
    uint8_t memory[0x10000];
    uint8_t r8[8];
    uint16_t pc;
    uint16_t sp;
    uint8_t opcode;
};

uint8_t read_u8(struct gameboy *gb, uint16_t addr) {
    return gb->memory[addr];
}

void write_u8(struct gameboy *gb, uint16_t addr, uint8_t val) {
    gb->memory[addr] = val;
}

#define r16bc ((gb->r8[0] << 8) | (gb->r8[1]))
#define r16de ((gb->r8[2] << 8) | (gb->r8[3]))
#define r16hl ((gb->r8[4] << 8) | (gb->r8[5]))
#define r16af ((gb->r8[7] << 8) | (gb->r8[6] & 240))

#define r8dst ((gb->opcode >> 3) & 7)   // bits 5-3
#define r8src (gb->opcode & 7)          // bits 2-0

static inline void r16hl_dec(struct gameboy *gb) {
    uint16_t r = ((gb->r8[4] << 8) | (gb->r8[5])) - 1;
    gb->r8[4] = r >> 8, gb->r8[5] = r & 255;
}

static inline void r16hl_inc(struct gameboy *gb) {
    uint16_t r = ((gb->r8[4] << 8) | (gb->r8[5])) + 1;
    gb->r8[4] = r >> 8, gb->r8[5] = r & 255;
}

/*
** 8-bit load instructions
*/

// 0b01xxxyyy except 110yyy and xxx110
// 1 byte, 1 cycle
void ld_r_r(struct gameboy *gb) {
    gb->r8[r8dst] = gb->r8[r8src];
    gb->pc++;
}

// 0b00xxx110 except 0x36 (0v X6, XE)
// 2 bytes, 2 cycles
void ld_r_n(struct gameboy *gb) {
    gb->pc++;
    gb->r8[r8dst] = read_u8(gb, gb->pc);
    gb->pc++;
}

// 0b01xxx110 except 0x76 (4v X6, XE)
// 1 byte, 2 cycles
void ld_r_hl(struct gameboy *gb) {
    gb->r8[r8dst] = read_u8(gb, r16hl);
    gb->pc++;
}

// 0b01110xxx except 0x76 (h 70-77)
// 1 byte, 2 cycles
void ld_hl_r(struct gameboy *gb) {
    write_u8(gb, r16hl, gb->r8[r8src]);
    gb->pc++;
}

// 0x36
// 2 bytes, 3 cycles
void ld_hl_n(struct gameboy *gb) {
    gb->pc++;
    write_u8(gb, r16hl, read_u8(gb, gb->pc));
    gb->pc++;
}

// 0x0a
// 1 byte, 2 cycles
void ld_a_bc(struct gameboy *gb) {
    gb->r8[7] = read_u8(gb, r16bc);
    gb->pc++;
}

// 0x1a, 1 byte, 2 cycles
void ld_a_de(struct gameboy *gb) {
    gb->r8[7] = read_u8(gb, r16de);
    gb->pc++;
}

// 0x02, 1 byte, 2 cycles
void ld_bc_a(struct gameboy *gb) {
    write_u8(gb, r16bc, gb->r8[7]);
    gb->pc++;
}

// 0x12, 1 byte, 2 cycles
void ld_de_a(struct gameboy *gb) {
    write_u8(gb, r16de, gb->r8[7]);
    gb->pc++;
}

// 0xfa, 3 bytes, 4 cycles
void ld_a_nn(struct gameboy *gb) {
    uint16_t nn;
    gb->pc++;
    nn = read_u8(gb, gb->pc);
    gb->pc++;
    nn |= (read_u8(gb, gb->pc) << 8);
    gb->r8[7] = read_u8(gb, nn);
    gb->pc++;
}

// 0xea, 3 bytes, 4 cycles
void ld_nn_a(struct gameboy *gb) {
    uint16_t nn;
    gb->pc++;
    nn = read_u8(gb, gb->pc);
    gb->pc++;
    nn |= (read_u8(gb, gb->pc) << 8);
    write_u8(gb, nn, gb->r8[7]);
    gb->pc++;
}

// 0xf2, 1 byte, 2 cycles
void ldh_a_c(struct gameboy *gb) {
    gb->r8[7] = read_u8(gb, (0xff00 + gb->r8[1]));
    gb->pc++;
}

// 0xe2, 1 byte, 2 cycles
void ldh_c_a(struct gameboy *gb) {
    write_u8(gb, (0xff00 + gb->r8[1]), gb->r8[7]);
    gb->pc++;
}

// 0xf0, 2 bytes, 3 cycles
void ldh_a_n(struct gameboy *gb) {
    uint8_t n;
    gb->pc++;
    n = read_u8(gb, gb->pc);
    gb->r8[7] = read_u8(gb, (0xff00 + n));
    gb->pc++;
}

// 0xe0, 2 bytes, 3 cycles
void ldh_n_a(struct gameboy *gb) {
    uint8_t n;
    gb->pc++;
    n = read_u8(gb, gb->pc);
    write_u8(gb, (0xff00 + n), gb->r8[7]);
    gb->pc++;
}

// 0x3a, 1 byte, 2 cycles
void ld_a_hl_dec(struct gameboy *gb) {
    gb->r8[7] = read_u8(gb, r16hl);
    r16hl_dec(gb);
    gb->pc++;
}

// 0x32, 1 byte, 2 cycles
void ld_hl_dec_a(struct gameboy *gb) {
    write_u8(gb, r16hl, gb->r8[7]);
    r16hl_dec(gb);
    gb->pc++;
}

// 0x2a, 1 byte, 2 cycles
void ld_a_hl_inc(struct gameboy *gb) {
    gb->r8[7] = read_u8(gb, r16hl);
    r16hl_inc(gb);
    gb->pc++;
}

// 0x22, 1 byte, 2 cycles
void ld_hl_inc_a(struct gameboy *gb) {
    write_u8(gb, r16hl, gb->r8[7]);
    r16hl_inc(gb);
    gb->pc++;
}

/*
** 16-bit load instructions
*/

// 0x01, 0x11, 0x21, 0x31
// 3 bytes, 3 cycles
void ld_rr_nn(struct gameboy *gb) {
    uint16_t nn, r16idx;
    gb->pc++;
    nn = read_u8(gb, gb->pc);
    gb->pc++;
    nn |= (read_u8(gb, gb->pc) << 8);
    r16idx = (gb->opcode >> 4) & 3;

    if (r16idx == 3) {
        gb->sp = nn;
    } else {
        gb->r8[r16idx * 2] = nn >> 8;
        gb->r8[r16idx * 2 + 1] = nn & 255;
    }

    gb->pc++;
}

// 0x08, 3 bytes, 5 cycles
void ld_nn_sp(struct gameboy *gb) {
    uint16_t nn;
    gb->pc++;
    nn = read_u8(gb, gb->pc);
    gb->pc++;
    nn |= (read_u8(gb, gb->pc) << 8);
    write_u8(gb, nn, gb->sp & 255);
    write_u8(gb, nn + 1, gb->sp >> 8);
    gb->pc++;
}

// 0xf9, 1 byte, 2 cycles
void ld_sp_hl(struct gameboy *gb) {
    gb->sp = r16hl;
    gb->pc++;
}

// 0b11xx0101: 0xc5, 0xd5, 0xe5, 0xf5; bc,de,hl,af
// 1 byte, 4 cycles
void push_rr(struct gameboy *gb) {
    uint8_t r16idx;
    r16idx = (gb->opcode >> 4) & 3;
    gb->sp--;

    if (r16idx == 3) {
        write_u8(gb, gb->sp, gb->r8[7]);    // a
    } else {
        write_u8(gb, gb->sp, gb->r8[r16idx * 2]);
    }

    gb->sp--;

    if (r16idx == 3) {
        write_u8(gb, gb->sp, gb->r8[6] & 240); // f
    } else {
        write_u8(gb, gb->sp, gb->r8[r16idx * 2 + 1]);
    }

    gb->pc++;
}


// 0b11xx0001: 0xc1, 0xd1, 0xe1, 0xf1; bc,de,hl,af
// 1 byte, 3 cycles
void pop_rr(struct gameboy *gb) {
    uint16_t r16idx;
    r16idx = (gb->opcode >> 4) & 3;

    if (r16idx == 3) {
        gb->r8[6] = read_u8(gb, gb->sp) & 240; // f
    } else {
        gb->r8[r16idx * 2 + 1] = read_u8(gb, gb->sp);
    }

    gb->sp++;

    if (r16idx == 3) {
        gb->r8[7] = read_u8(gb, gb->sp); // a
    } else {
        gb->r8[r16idx * 2] = read_u8(gb, gb->sp);
    }

    gb->sp++;
    gb->pc++;
}



int main(void) {
    struct gameboy *gb = calloc(sizeof(struct gameboy), 1);
    (void)ld_r_r(gb);
    (void)ld_r_n(gb);
    (void)ld_r_hl(gb);
    (void)ld_hl_r(gb);
    (void)ld_hl_n(gb);
    (void)ld_a_bc(gb);
    (void)ld_a_de(gb);
    (void)ld_bc_a(gb);
    (void)ld_de_a(gb);
    (void)ld_a_nn(gb);
    (void)ld_nn_a(gb);
    (void)ldh_a_c(gb);
    (void)ldh_c_a(gb);
    (void)ldh_a_n(gb);
    (void)ldh_n_a(gb);
    (void)ld_a_hl_dec(gb);
    (void)ld_hl_dec_a(gb);
    (void)ld_a_hl_inc(gb);
    (void)ld_hl_inc_a(gb);
    (void)ld_rr_nn(gb);
    (void)ld_nn_sp(gb);
    (void)ld_sp_hl(gb);
    (void)push_rr(gb);
    (void)pop_rr(gb);
    return 0;
}
