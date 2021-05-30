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

static inline void r16hld(struct gameboy *gb) {
    uint16_t r = ((gb->r8[4] << 8) | (gb->r8[5])) - 1;
    gb->r8[4] = r >> 8, gb->r8[5] = r & 255;
}

static inline void r16hli(struct gameboy *gb) {
    uint16_t r = ((gb->r8[4] << 8) | (gb->r8[5])) + 1;
    gb->r8[4] = r >> 8, gb->r8[5] = r & 255;
}


//            0,        1,        2,       3,          4,       5,       6,       7,          8,         9,        a,      b,          c,       d,       e,      f,
// 0        nop, ld_rr_nn,  ld_bc_a,  inc_rr,      inc_r,   dec_r,  ld_r_n,   rlc_r,   ld_nn_sp, add_hl_rr,  ld_a_bc, dec_rr,      inc_r,   dec_r,  ld_r_n,  rrc_r,
// 1       stop, ld_rr_nn,  ld_de_a,  inc_rr,      inc_r,   dec_r,  ld_r_n,    rl_r,       jr_e, add_hl_rr,  ld_a_de, dec_rr,      inc_r,   dec_r,  ld_r_n,   rr_r,
// 2    jr_cc_e, ld_rr_nn, ld_hli_a,  inc_rr,      inc_r,   dec_r,  ld_r_n,     daa,    jr_cc_e, add_hl_rr, ld_a_hli, dec_rr,      inc_r,   dec_r,  ld_r_n,    cpl,
// 3    jr_cc_e, ld_rr_nn, ld_hld_a,  inc_rr,     inc_hl,  dec_hl, ld_hl_n,     scf,    jr_cc_e, add_hl_rr, ld_a_hld, dec_rr,      inc_r,   dec_r,  ld_r_n,    ccf,
// 4     ld_r_r,   ld_r_r,   ld_r_r,  ld_r_r,     ld_r_r,  ld_r_r, ld_r_hl,  ld_r_r,     ld_r_r,    ld_r_r,   ld_r_r, ld_r_r,     ld_r_r,  ld_r_r, ld_r_hl, ld_r_r,
// 5     ld_r_r,   ld_r_r,   ld_r_r,  ld_r_r,     ld_r_r,  ld_r_r, ld_r_hl,  ld_r_r,     ld_r_r,    ld_r_r,   ld_r_r, ld_r_r,     ld_r_r,  ld_r_r, ld_r_hl, ld_r_r,
// 6     ld_r_r,   ld_r_r,   ld_r_r,  ld_r_r,     ld_r_r,  ld_r_r, ld_r_hl,  ld_r_r,     ld_r_r,    ld_r_r,   ld_r_r, ld_r_r,     ld_r_r,  ld_r_r, ld_r_hl, ld_r_r,
// 7    ld_hl_r,  ld_hl_r,  ld_hl_r, ld_hl_r,    ld_hl_r, ld_hl_r,    halt, ld_hl_r,     ld_r_r,    ld_r_r,   ld_r_r, ld_r_r,     ld_r_r,  ld_r_r, ld_r_hl, ld_r_r,
// 8      add_r,    add_r,    add_r,   add_r,      add_r,   add_r,  add_hl,   add_r,      adc_r,     adc_r,    adc_r,  adc_r,      adc_r,   adc_r,  adc_hl,  adc_r,
// 9      sub_r,    sub_r,    sub_r,   sub_r,      sub_r,   sub_r,  sub_hl,   sub_r,      sbc_r,     sbc_r,    sbc_r,  sbc_r,      sbc_r,   sbc_r,  sbc_hl,  sbc_r,
// a      and_r,    and_r,    and_r,   and_r,      and_r,   and_r,  and_hl,   and_r,      xor_r,     xor_r,    xor_r,  xor_r,      xor_r,   xor_r,  xor_hl,  xor_r,
// b       or_r,     or_r,     or_r,    or_r,       or_r,    or_r,   or_hl,    or_r,       cp_r,      cp_r,     cp_r,   cp_r,       cp_r,    cp_r,   cp_hl,   cp_r,
// c     ret_cc,   pop_rr, jp_cc_nn,   jp_nn, call_cc_nn, push_rr,   add_n,   rst_n,     ret_cc,       ret, jp_cc_nn,      -, call_cc_nn, call_nn,   adc_n,  rst_n,
// d     ret_cc,   pop_rr, jp_cc_nn,       -, call_cc_nn, push_rr,   sub_n,   rst_n,     ret_cc,      reti, jp_cc_nn,      -, call_cc_nn,       -,   sbc_n,  rst_n,
// e    ldh_n_a,   pop_rr,  ldh_c_a,       -,          -, push_rr,   and_n,   rst_n,   add_sp_e,     jp_hl,  ld_nn_a,      -,          -,       -,   xor_n,  rst_n,
// f    ldh_a_n,   pop_rr,  ldh_a_c,      di,          -, push_rr,    or_n,   rst_n, ld_hl_sp_e,  ld_sp_hl,  ld_a_nn,     ei,          -,       -,    cp_n,  rst_n,


//            0,        1,        2,       3,          4,       5,       6,       7,          8,         9,        a,      b,          c,       d,       e,      f,
// 0      rlc_r,    rlc_r,     rlc_r,    rlc_r,    rlc_r,   rlc_r,  rlc_hl,   rlc_r,      rrc_r,     rrc_r,    rrc_r,  rrc_r,      rrc_r,   rrc_r,  rrc_hl,  rrc_r,
// 1       rl_r,     rl_r,      rl_r,     rl_r,     rl_r,    rl_r,   rl_hl,    rl_r,       rr_r,      rr_r,     rr_r,   rr_r,       rr_r,    rr_r,   rr_hl,   rr_r,
// 2      sla_r,    sla_r,     sla_r,    sla_r,    sla_r,   sla_r,  sla_hl,   sla_r,      sra_r,     sra_r,    sra_r,  sra_r,      sra_r,   sra_r,  sra_hl,  sra_r,
// 3     swap_r,   swap_r,    swap_r,   swap_r,   swap_r,  swap_r, swap_hl,  swap_r,      srl_r,     srl_r,    srl_r,  srl_r,      srl_r,   srl_r,  srl_hl,  srl_r,
// 4      bit_r,    bit_r,     bit_r,    bit_r,    bit_r,   bit_r,  bit_hl,   bit_r,      bit_r,     bit_r,    bit_r,  bit_r,      bit_r,   bit_r,  bit_hl,  bit_r,
// 5      bit_r,    bit_r,     bit_r,    bit_r,    bit_r,   bit_r,  bit_hl,   bit_r,      bit_r,     bit_r,    bit_r,  bit_r,      bit_r,   bit_r,  bit_hl,  bit_r,
// 6      bit_r,    bit_r,     bit_r,    bit_r,    bit_r,   bit_r,  bit_hl,   bit_r,      bit_r,     bit_r,    bit_r,  bit_r,      bit_r,   bit_r,  bit_hl,  bit_r,
// 7      bit_r,    bit_r,     bit_r,    bit_r,    bit_r,   bit_r,  bit_hl,   bit_r,      bit_r,     bit_r,    bit_r,  bit_r,      bit_r,   bit_r,  bit_hl,  bit_r,
// 8      res_r,    res_r,     res_r,    res_r,    res_r,   res_r,  res_hl,   res_r,      res_r,     res_r,    res_r,  res_r,      res_r,   res_r,  res_hl,  res_r,
// 9      res_r,    res_r,     res_r,    res_r,    res_r,   res_r,  res_hl,   res_r,      res_r,     res_r,    res_r,  res_r,      res_r,   res_r,  res_hl,  res_r,
// a      res_r,    res_r,     res_r,    res_r,    res_r,   res_r,  res_hl,   res_r,      res_r,     res_r,    res_r,  res_r,      res_r,   res_r,  res_hl,  res_r,
// b      res_r,    res_r,     res_r,    res_r,    res_r,   res_r,  res_hl,   res_r,      res_r,     res_r,    res_r,  res_r,      res_r,   res_r,  res_hl,  res_r,
// c      set_r,    set_r,     set_r,    set_r,    set_r,   set_r,  set_hl,   set_r,      set_r,     set_r,    set_r,  set_r,      set_r,   set_r,  set_hl,  set_r,
// d      set_r,    set_r,     set_r,    set_r,    set_r,   set_r,  set_hl,   set_r,      set_r,     set_r,    set_r,  set_r,      set_r,   set_r,  set_hl,  set_r,
// e      set_r,    set_r,     set_r,    set_r,    set_r,   set_r,  set_hl,   set_r,      set_r,     set_r,    set_r,  set_r,      set_r,   set_r,  set_hl,  set_r,
// f      set_r,    set_r,     set_r,    set_r,    set_r,   set_r,  set_hl,   set_r,      set_r,     set_r,    set_r,  set_r,      set_r,   set_r,  set_hl,  set_r,


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
void ld_a_hld(struct gameboy *gb) {
    gb->r8[7] = read_u8(gb, R16HL);
    r16hld(gb);
    gb->pc++;
}

// 0x32, 1 byte, 2 cycles
void ld_hld_a(struct gameboy *gb) {
    write_u8(gb, R16HL, gb->r8[7]);
    r16hld(gb);
    gb->pc++;
}

// 0x2a, 1 byte, 2 cycles
void ld_a_hli(struct gameboy *gb) {
    gb->r8[7] = read_u8(gb, R16HL);
    r16hli(gb);
    gb->pc++;
}

// 0x22, 1 byte, 2 cycles
void ld_hli_a(struct gameboy *gb) {
    write_u8(gb, R16HL, gb->r8[7]);
    r16hli(gb);
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

// 0xf8, 2 bytes, 3 cycles
void ld_hl_sp_e(struct gameboy *gb) {
    int8_t e;
    gb->pc++;
    e = (int8_t)read_u8(gb, gb->pc);
    gb->pc++;
    gb->r8[4] = (gb->sp + e) >> 8;
    gb->r8[5] = (gb->sp + e) & 255;
    CLEAR_Z_FLAG;
    CLEAR_N_FLAG;
    (e & 0xf) + (gb->sp & 0xf) > 0xf ? SET_H_FLAG : CLEAR_H_FLAG;
    (e & 0xff) + (gb->sp & 0xff) > 0xff ? SET_C_FLAG : CLEAR_C_FLAG;
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

// 0x04, 0x0c, 0x14, 0x1c, 0x24, 0x2c, 0x3c
// 1 byte, 1 cycle
void inc_r(struct gameboy *gb) {}
// 0x34: 1 byte, 3 cycles
void inc_hl(struct gameboy *gb) {}


// 0x05, 0x0d, 0x15, 0x1d, 0x25, 0x2d, 0x3d
// 1 byte, 1 cycle
void dec_r(struct gameboy *gb) {}
// 0x35: 1 byte, 3 cycles
void dec_hl(struct gameboy *gb) {}


// 0x80-0x87, except 0x86: 1 byte, 1 cycle
void add_r(struct gameboy *gb) {}
// 0x86: 1 byte, 2 cycles
void add_hl(struct gameboy *gb) {}
// 0xc6: 2 bytes, 2 cycles
void add_n(struct gameboy *gb) {}

// 0x88-0x8f, except 0x8e: 1 byte, 1 cycle
void adc_r(struct gameboy *gb) {}
// 0x8e: 1 byte, 2 cycles
void adc_hl(struct gameboy *gb) {}
// 0xce: 2 bytes, 2 cycles
void adc_n(struct gameboy *gb) {}

// 0x90-97, except 0x96: 1 byte, 1 cycle
void sub_r(struct gameboy *gb) {}
// 0x96: 1 byte, 2 cycles
void sub_hl(struct gameboy *gb) {}
// 0xd6: 2 bytes, 2 cycles
void sub_n(struct gameboy *gb) {}

// 0x98-0x9f, except 0x9e: 1 byte, 1 cycle
void sbc_r(struct gameboy *gb) {}
// 0x9e: 1 byte, 2 cycles
void sbc_hl(struct gameboy *gb) {}
// 0xde: 2 bytes, 2 cycles
void sbc_n(struct gameboy *gb) {}

// 0xa0-a7, except 0xa6: 1 byte, 1 cycle
void and_r(struct gameboy *gb) {}
// 0xa6: 1 byte, 2 cycles
void and_hl(struct gameboy *gb) {}
// 0xe6: 2 bytes, 2 cycles
void and_n(struct gameboy *gb) {}

// 0xa8-0xaf, except 0xae: 1 byte, 1 cycle
void xor_r(struct gameboy *gb) {}
// 0xae: 1 byte, 2 cycles
void xor_hl(struct gameboy *gb) {}
// 0xee: 2 bytes, 2 cycles
void xor_n(struct gameboy *gb) {}

// 0xb0-b7, except 0xb6: 1 byte, 1 cycle
void or_r(struct gameboy *gb) {}
// 0xb6: 1 byte, 2 cycles
void or_hl(struct gameboy *gb) {}
// 0xf6: 2 bytes, 2 cycles
void or_n(struct gameboy *gb) {}

// 0xb8-0xbf, except 0xbe: 1 byte, 1 cycle
void cp_r(struct gameboy *gb) {}
// 0xbe: 1 byte, 2 cycles
void cp_hl(struct gameboy *gb) {}
// 0xfe: 2 bytes, 2 cycles
void cp_n(struct gameboy *gb) {}

/*
** 16-bit arithmetic instructions
*/

// 0x03, 0x13, 0x23, 0x33: 1 byte, 2 cycles
void inc_rr(struct gameboy *gb) {}

// 0x0b, 0x1b, 0x2b, 0x3b: 1 byte, 2 cycles
void dec_rr(struct gameboy *gb) {}

// 0x09, 0x19, 0x29, 0x39
// 1 byte, 2 cycles
void add_hl_rr(struct gameboy *gb) {}

// 0xe8, 2 bytes, 4 cycles
void add_sp_e(struct gameboy *gb) {}

/*
** rotate, shift, and bit operation instructions
*/

void rlc_r(struct gameboy *gb) {}
void rrc_r(struct gameboy *gb) {}
void rl_r(struct gameboy *gb) {}
void rr_r(struct gameboy *gb) {}
void sla_r(struct gameboy *gb) {}
void sra_r(struct gameboy *gb) {}
void swap_r(struct gameboy *gb) {}
void srl_r(struct gameboy *gb) {}
void bit_r(struct gameboy *gb) {}
void res_r(struct gameboy *gb) {}
void set_r(struct gameboy *gb) {}

void rlc_hl(struct gameboy *gb) {}
void rrc_hl(struct gameboy *gb) {}
void rl_hl(struct gameboy *gb) {}
void rr_hl(struct gameboy *gb) {}
void sla_hl(struct gameboy *gb) {}
void sra_hl(struct gameboy *gb) {}
void swap_hl(struct gameboy *gb) {}
void srl_hl(struct gameboy *gb) {}
void bit_hl(struct gameboy *gb) {}
void res_hl(struct gameboy *gb) {}
void set_hl(struct gameboy *gb) {}

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
    (void)ld_a_hld(gb);
    (void)ld_hld_a(gb);
    (void)ld_a_hli(gb);
    (void)ld_hli_a(gb);
    (void)ld_rr_nn(gb);
    (void)ld_nn_sp(gb);
    (void)ld_sp_hl(gb);
    (void)push_rr(gb);
    (void)pop_rr(gb);
    return 0;
}
