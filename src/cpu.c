#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/*
** https://gekkio.fi/files/gb-docs/gbctr.pdf
** https://rgbds.gbdev.io/docs/master/gbz80.7
** https://gbdev.io/gb-opcodes/optables/
*/

// 0, 1, 2, 3, 4, 5,    6, 7
// b, c, d, e, h, l, (hl), a
// opcode 0x76 => halt

enum CPU_STATE { RUNNING, HALTED, STOPPED };

struct gameboy {
    uint8_t memory[0x10000];
    uint8_t r8[8];
    uint16_t pc;
    uint16_t sp;
    uint8_t opcode;
    int cpu_state;
    int ime;
    int ime_scheduled;
};

uint8_t read_u8(struct gameboy *gb, uint16_t addr) {
    return gb->memory[addr];
}

void write_u8(struct gameboy *gb, uint16_t addr, uint8_t val) {
    gb->memory[addr] = val;
}

#define R16BC        ((gb->r8[0] << 8) | (gb->r8[1]))
#define R16DE        ((gb->r8[2] << 8) | (gb->r8[3]))
#define R16HL        ((gb->r8[4] << 8) | (gb->r8[5]))
#define R16AF        ((gb->r8[7] << 8) | (gb->r8[6] & 240))

#define R8DST        ((gb->opcode >> 3) & 7)   // bits 5-3
#define R8SRC        (gb->opcode & 7)          // bits 2-0

#define IS_Z_FLAG    ((gb->r8[6] & 0b10000000) != 0)
#define IS_N_FLAG    ((gb->r8[6] & 0b01000000) != 0)
#define IS_H_FLAG    ((gb->r8[6] & 0b00100000) != 0)
#define IS_C_FLAG    ((gb->r8[6] & 0b00010000) != 0)

#define SET_Z_FLAG   (gb->r8[6] |= 0b10000000)
#define SET_N_FLAG   (gb->r8[6] |= 0b01000000)
#define SET_H_FLAG   (gb->r8[6] |= 0b00100000)
#define SET_C_FLAG   (gb->r8[6] |= 0b00010000)

#define CLEAR_Z_FLAG (gb->r8[6] &= ~0b10000000)
#define CLEAR_N_FLAG (gb->r8[6] &= ~0b01000000)
#define CLEAR_H_FLAG (gb->r8[6] &= ~0b00100000)
#define CLEAR_C_FLAG (gb->r8[6] &= ~0b00010000)

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
    gb->r8[R8DST] = gb->r8[R8SRC];
    gb->pc++;
}

// 0b00xxx110 except 0x36 (0v X6, XE)
// 2 bytes, 2 cycles
void ld_r_n(struct gameboy *gb) {
    gb->pc++;
    gb->r8[R8DST] = read_u8(gb, gb->pc);
    gb->pc++;
}

// 0b01xxx110 except 0x76 (4v X6, XE)
// 1 byte, 2 cycles
void ld_r_hl(struct gameboy *gb) {
    gb->r8[R8DST] = read_u8(gb, R16HL);
    gb->pc++;
}

// 0b01110xxx except 0x76 (h 70-77)
// 1 byte, 2 cycles
void ld_hl_r(struct gameboy *gb) {
    write_u8(gb, R16HL, gb->r8[R8SRC]);
    gb->pc++;
}

// 0x36
// 2 bytes, 3 cycles
void ld_hl_n(struct gameboy *gb) {
    gb->pc++;
    write_u8(gb, R16HL, read_u8(gb, gb->pc));
    gb->pc++;
}

// 0x0a
// 1 byte, 2 cycles
void ld_a_bc(struct gameboy *gb) {
    gb->r8[7] = read_u8(gb, R16BC);
    gb->pc++;
}

// 0x1a, 1 byte, 2 cycles
void ld_a_de(struct gameboy *gb) {
    gb->r8[7] = read_u8(gb, R16DE);
    gb->pc++;
}

// 0x02, 1 byte, 2 cycles
void ld_bc_a(struct gameboy *gb) {
    write_u8(gb, R16BC, gb->r8[7]);
    gb->pc++;
}

// 0x12, 1 byte, 2 cycles
void ld_de_a(struct gameboy *gb) {
    write_u8(gb, R16DE, gb->r8[7]);
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
    gb->r8[7] = read_u8(gb, R16HL);
    r16hl_dec(gb);
    gb->pc++;
}

// 0x32, 1 byte, 2 cycles
void ld_hl_dec_a(struct gameboy *gb) {
    write_u8(gb, R16HL, gb->r8[7]);
    r16hl_dec(gb);
    gb->pc++;
}

// 0x2a, 1 byte, 2 cycles
void ld_a_hl_inc(struct gameboy *gb) {
    gb->r8[7] = read_u8(gb, R16HL);
    r16hl_inc(gb);
    gb->pc++;
}

// 0x22, 1 byte, 2 cycles
void ld_hl_inc_a(struct gameboy *gb) {
    write_u8(gb, R16HL, gb->r8[7]);
    r16hl_inc(gb);
    gb->pc++;
}

/*
** 16-bit load instructions
*/

// 0x01, 0x11, 0x21, 0x31
// 3 bytes, 3 cycles
void ld_rr_nn(struct gameboy *gb) {
    uint16_t nn;
    int r16idx;
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
    gb->sp = R16HL;
    gb->pc++;
}

// 0b11xx0101: 0xc5, 0xd5, 0xe5, 0xf5; bc,de,hl,af
// 1 byte, 4 cycles
void push_rr(struct gameboy *gb) {
    int r16idx;
    r16idx = (gb->opcode >> 4) & 3;
    gb->sp--;

    if (r16idx == 3) {
        write_u8(gb, gb->sp, gb->r8[7]);    // a
    } else {
        write_u8(gb, gb->sp, gb->r8[r16idx * 2]);
    }

    gb->sp--;

    if (r16idx == 3) {
        write_u8(gb, gb->sp, gb->r8[6] & 0b11110000); // f
    } else {
        write_u8(gb, gb->sp, gb->r8[r16idx * 2 + 1]);
    }

    gb->pc++;
}


// 0b11xx0001: 0xc1, 0xd1, 0xe1, 0xf1; bc,de,hl,af
// 1 byte, 3 cycles
void pop_rr(struct gameboy *gb) {
    int r16idx;
    r16idx = (gb->opcode >> 4) & 3;

    if (r16idx == 3) {
        gb->r8[6] = read_u8(gb, gb->sp) & 0b11110000; // f
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

/*
** 8-bit arithmetic instructions
*/

/*
** 16-bit arithmetic instructions
*/

/*
** rotate, shift, and bit operation instructions
*/

/*
** control flow instructions
*/


// 0xc3, 3 bytes, 4 cycles
void jp_nn(struct gameboy *gb) {
    uint16_t nn;
    gb->pc++;
    nn = read_u8(gb, gb->pc);
    gb->pc++;
    nn |= (read_u8(gb, gb->pc) << 8);
    gb->pc = nn;
}

// 0xe9, 1 byte, 1 cycle
void jp_hl(struct gameboy *gb) {
    gb->pc = R16HL;
}

// 0b110cc010: 0xc2 (NZ), 0xca (Z), 0xd2 (NC), 0xda (C)
// 3 bytes, 3 cycles (cc false) - or - 4 cycles (cc true)
void jp_cc_nn(struct gameboy *gb) {
    int cc;
    uint16_t nn;
    cc = (gb->opcode >> 3) & 3;
    gb->pc++;
    nn = read_u8(gb, gb->pc);
    gb->pc++;
    nn |= (read_u8(gb, gb->pc) << 8);
    gb->pc++;

    if (((cc == 0) && (!IS_Z_FLAG)) ||
            ((cc == 1) && (IS_Z_FLAG))  ||
            ((cc == 2) && (!IS_C_FLAG)) ||
            ((cc == 3) && (IS_C_FLAG))) {
        gb->pc = nn;
    }
}

// 0x18, 2 bytes, 3 cycles
void jr_e(struct gameboy *gb) {
    int8_t e;
    gb->pc++;
    e = (int8_t)read_u8(gb, gb->pc);
    gb->pc++;
    gb->pc += e;
}

// 0b001cc000: 0x20 (NZ), 0x28 (Z), 0x30 (NC), 0x38 (C)
// 2 bytes, 2 cycles (cc false) - or - 3 cycles (cc true)
void jr_cc_e(struct gameboy *gb) {
    int cc;
    int8_t e;
    cc = (gb->opcode >> 3) & 3;
    gb->pc++;
    e = (int8_t)read_u8(gb, gb->pc);
    gb->pc++;

    if (((cc == 0) && (!IS_Z_FLAG)) ||
            ((cc == 1) && (IS_Z_FLAG))  ||
            ((cc == 2) && (!IS_C_FLAG)) ||
            ((cc == 3) && (IS_C_FLAG))) {
        gb->pc += e;
    }
}

// 0xcd, 3 bytes, 6 cycles
void call_nn(struct gameboy *gb) {
    uint16_t nn;
    gb->pc++;
    nn = read_u8(gb, gb->pc);
    gb->pc++;
    nn |= (read_u8(gb, gb->pc) << 8);
    gb->pc++;
    gb->sp--;
    write_u8(gb, gb->sp, gb->pc >> 8);
    gb->sp--;
    write_u8(gb, gb->sp, gb->pc & 255);
    gb->pc = nn;
}

// 0b110cc100: 0xc4 (NZ) 0xcc (Z), 0xd4 (NC), 0xdc (C)
// 3 bytes, 3 cycles (cc false) - or - 6 cycles (cc true)
void call_cc_nn(struct gameboy *gb) {
    int cc;
    uint16_t nn;
    cc = (gb->opcode >> 3) & 3;
    gb->pc++;
    nn = read_u8(gb, gb->pc);
    gb->pc++;
    nn |= (read_u8(gb, gb->pc) << 8);
    gb->pc++;

    if (((cc == 0) && (!IS_Z_FLAG)) ||
            ((cc == 1) && (IS_Z_FLAG))  ||
            ((cc == 2) && (!IS_C_FLAG)) ||
            ((cc == 3) && (IS_C_FLAG))) {
        gb->sp--;
        write_u8(gb, gb->sp, gb->pc >> 8);
        gb->sp--;
        write_u8(gb, gb->sp, gb->pc & 255);
        gb->pc = nn;
    }
}

// 0xc9, 1 byte, 4 cycles
void ret(struct gameboy *gb) {
    uint16_t addr;
    gb->pc++;
    addr = read_u8(gb, gb->sp);
    gb->sp++;
    addr |= (read_u8(gb, gb->sp) << 8);
    gb->sp++;
    gb->pc = addr;
}

// 0b110cc000: 0xc0 (NZ), 0xc8 (Z), 0xd0 (NC), 0xd8 (C)
// 2 cycles (cc false) - or - 5 cycles (cc true)
void ret_cc(struct gameboy *gb) {
    int cc;
    uint16_t addr;
    cc = (gb->opcode >> 3) & 3;
    gb->pc++;

    if (((cc == 0) && (!IS_Z_FLAG)) ||
            ((cc == 1) && (IS_Z_FLAG))  ||
            ((cc == 2) && (!IS_C_FLAG)) ||
            ((cc == 3) && (IS_C_FLAG))) {
        addr = read_u8(gb, gb->sp);
        gb->sp++;
        addr |= (read_u8(gb, gb->sp) << 8);
        gb->sp++;
        gb->pc = addr;
    }
}

// 0xd9, 1 byte, 4 cycles
void reti(struct gameboy *gb) {
    uint16_t addr;
    gb->pc++;
    addr = read_u8(gb, gb->sp);
    gb->sp++;
    addr |= (read_u8(gb, gb->sp) << 8);
    gb->sp++;
    gb->pc = addr;
    gb->ime = 1;
}

// 0b11xxx111: c7,cf,d7,df,e7,ef,f7,ff
// 1 byte, 4 cycles;
void rst_n(struct gameboy *gb) {
    gb->pc++;
    gb->sp--;
    write_u8(gb, gb->sp, gb->pc >> 8);
    gb->sp--;
    write_u8(gb, gb->sp, gb->pc & 255);
    gb->pc = gb->opcode & 0b00111000;
}

/*
** miscellaneous instructions
*/

// 0x76 XXX 1 byte, 1 cycle
void halt(struct gameboy *gb) {
    gb->pc++;
    gb->cpu_state = HALTED;
}

// 0x10 XXX
void stop(struct gameboy *gb) {
    gb->pc++;
    gb->cpu_state = STOPPED;
}

// 0xf3, 1 byte, 1 cycle
void di(struct gameboy *gb) {
    gb->pc++;
    gb->ime = gb->ime_scheduled = 0;
}

// 0xfb, 1 byte, 1 cycle
void ei(struct gameboy *gb) {
    gb->pc++;
    gb->ime_scheduled = 1;
}

// 0x3f, 1 byte, 1 cycle
void ccf(struct gameboy *gb) {
    gb->pc++;
    CLEAR_N_FLAG;
    CLEAR_H_FLAG;
    IS_C_FLAG ? CLEAR_C_FLAG : SET_C_FLAG;
}

// 0x37, 1 byte, 1 cycle
void scf(struct gameboy *gb) {
    gb->pc++;
    CLEAR_N_FLAG;
    CLEAR_H_FLAG;
    SET_C_FLAG;
}

// 0x00, 1 byte, 1 cycle
void nop(struct gameboy *gb) {
    gb->pc++;
}

// 0x27, 1 byte, 1 cycle
// https://forums.nesdev.com/viewtopic.php?f=20&t=15944
void daa(struct gameboy *gb) {
    gb->pc++;

    if (!IS_N_FLAG) {
        if ((IS_C_FLAG) || (gb->r8[7] > 0x99)) {
            gb->r8[7] += 0x60;
            SET_C_FLAG;
        }

        if ((IS_H_FLAG) || ((gb->r8[7] & 0x0f) > 0x09)) {
            gb->r8[7] += 0x6;
        }
    } else {
        if (IS_C_FLAG) {
            gb->r8[7] -= 0x60;
        }

        if (IS_H_FLAG) {
            gb->r8[7] -= 0x6;
        }
    }

    gb->r8[7] == 0 ? SET_Z_FLAG : CLEAR_Z_FLAG;
    CLEAR_H_FLAG;
}

// 0x2f, 1 byte, 1 cycle
void cpl(struct gameboy *gb) {
    gb->pc++;
    gb->r8[7] = ~(gb->r8[7]);
    SET_N_FLAG;
    SET_H_FLAG;
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
