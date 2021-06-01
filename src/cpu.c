#include <gb.h>

/*
** https://gekkio.fi/files/gb-docs/gbctr.pdf
** https://rgbds.gbdev.io/docs/master/gbz80.7
** https://gbdev.io/gb-opcodes/optables/
*/

#define R16HLD \
    gb->cpu.u16 = R16HL - 1;\
    gb->cpu.r8[4] = gb->cpu.u16 >> 8;\
    gb->cpu.r8[5] = gb->cpu.u16 & 255;

#define R16HLI \
    gb->cpu.u16 = R16HL + 1;\
    gb->cpu.r8[4] = gb->cpu.u16 >> 8;\
    gb->cpu.r8[5] = gb->cpu.u16 & 255;

/*
** 8-bit load instructions
*/

// 0b01xxxyyy except 110yyy and xxx110
// 1 byte, 1 cycle
void ld_r_r(struct gameboy *gb) {
    gb->cpu.pc++;
    gb->cpu.r8[U3DST] = gb->cpu.r8[U3SRC];
}

// 0b00xxx110 except 0x36 (0v X6, XE)
// 2 bytes, 2 cycles
void ld_r_d8(struct gameboy *gb) {
    gb->cpu.pc++;
    gb->cpu.lo = read_u8(gb, gb->cpu.pc);
    gb->cpu.pc++;
    gb->cpu.r8[U3DST] = gb->cpu.lo;
}

// 0b01xxx110 except 0x76 (4v X6, XE)
// 1 byte, 2 cycles
void ld_r_hl(struct gameboy *gb) {
    gb->cpu.pc++;
    gb->cpu.r8[U3DST] = read_u8(gb, R16HL);
}

// 0b01110xxx except 0x76 (h 70-77)
// 1 byte, 2 cycles
void ld_hl_r(struct gameboy *gb) {
    gb->cpu.pc++;
    write_u8(gb, R16HL, gb->cpu.r8[U3SRC]);
}

// 0x36, 2 bytes, 3 cycles
void ld_hl_d8(struct gameboy *gb) {
    gb->cpu.pc++;
    gb->cpu.lo = read_u8(gb, gb->cpu.pc);
    gb->cpu.pc++;
    write_u8(gb, R16HL, gb->cpu.lo);
}

// 0x0a, 1 byte, 2 cycles
void ld_a_bc(struct gameboy *gb) {
    gb->cpu.pc++;
    gb->cpu.r8[7] = read_u8(gb, R16BC);
}

// 0x1a, 1 byte, 2 cycles
void ld_a_de(struct gameboy *gb) {
    gb->cpu.pc++;
    gb->cpu.r8[7] = read_u8(gb, R16DE);
}

// 0x02, 1 byte, 2 cycles
void ld_bc_a(struct gameboy *gb) {
    gb->cpu.pc++;
    write_u8(gb, R16BC, gb->cpu.r8[7]);
}

// 0x12, 1 byte, 2 cycles
void ld_de_a(struct gameboy *gb) {
    gb->cpu.pc++;
    write_u8(gb, R16DE, gb->cpu.r8[7]);
}

// 0xfa, 3 bytes, 4 cycles
void ld_a_a16(struct gameboy *gb) {
    gb->cpu.pc++;
    gb->cpu.lo = read_u8(gb, gb->cpu.pc);
    gb->cpu.pc++;
    gb->cpu.hi = read_u8(gb, gb->cpu.pc);
    gb->cpu.pc++;
    gb->cpu.r8[7] = read_u8(gb, A16);
}

// 0xea, 3 bytes, 4 cycles
void ld_a16_a(struct gameboy *gb) {
    gb->cpu.pc++;
    gb->cpu.lo = read_u8(gb, gb->cpu.pc);
    gb->cpu.pc++;
    gb->cpu.hi = read_u8(gb, gb->cpu.pc);
    gb->cpu.pc++;
    write_u8(gb, A16, gb->cpu.r8[7]);
}

// 0xf2, 1 byte, 2 cycles
void ldh_a_c(struct gameboy *gb) {
    gb->cpu.pc++;
    gb->cpu.r8[7] = read_u8(gb, (0xff00 + gb->cpu.r8[1]));
}

// 0xe2, 1 byte, 2 cycles
void ldh_c_a(struct gameboy *gb) {
    gb->cpu.pc++;
    write_u8(gb, (0xff00 + gb->cpu.r8[1]), gb->cpu.r8[7]);
}

// 0xf0, 2 bytes, 3 cycles
void ldh_a_a8(struct gameboy *gb) {
    gb->cpu.pc++;
    gb->cpu.u16 = read_u8(gb, gb->cpu.pc);
    gb->cpu.pc++;
    gb->cpu.r8[7] = read_u8(gb, 0xff00 + gb->cpu.u16);
}

// 0xe0, 2 bytes, 3 cycles
void ldh_a8_a(struct gameboy *gb) {
    gb->cpu.pc++;
    gb->cpu.u16 = read_u8(gb, gb->cpu.pc);
    gb->cpu.pc++;
    write_u8(gb, 0xff00 + gb->cpu.u16, gb->cpu.r8[7]);
}

// 0x3a, 1 byte, 2 cycles
void ld_a_hld(struct gameboy *gb) {
    gb->cpu.pc++;
    gb->cpu.r8[7] = read_u8(gb, R16HL);
    R16HLD;
}

// 0x32, 1 byte, 2 cycles
void ld_hld_a(struct gameboy *gb) {
    gb->cpu.pc++;
    write_u8(gb, R16HL, gb->cpu.r8[7]);
    R16HLD;
}

// 0x2a, 1 byte, 2 cycles
void ld_a_hli(struct gameboy *gb) {
    gb->cpu.pc++;
    gb->cpu.r8[7] = read_u8(gb, R16HL);
    R16HLI;
}

// 0x22, 1 byte, 2 cycles
void ld_hli_a(struct gameboy *gb) {
    gb->cpu.pc++;
    write_u8(gb, R16HL, gb->cpu.r8[7]);
    R16HLI;
}

/*
** 16-bit load instructions
*/

// 0x01, 0x11, 0x21, 0x31
// 3 bytes, 3 cycles
void ld_rr_d16(struct gameboy *gb) {
    gb->cpu.pc++;
    gb->cpu.lo = read_u8(gb, gb->cpu.pc);
    gb->cpu.pc++;
    gb->cpu.hi = read_u8(gb, gb->cpu.pc);
    gb->cpu.pc++;

    if (U2IDX == 3) {
        gb->cpu.sp = D16;
    } else {
        gb->cpu.r8[U2IDX * 2] = gb->cpu.hi;
        gb->cpu.r8[U2IDX * 2 + 1] = gb->cpu.lo;
    }
}

// 0x08, 3 bytes, 5 cycles
void ld_a16_sp(struct gameboy *gb) {
    gb->cpu.pc++;
    gb->cpu.lo = read_u8(gb, gb->cpu.pc);
    gb->cpu.pc++;
    gb->cpu.hi = read_u8(gb, gb->cpu.pc);
    gb->cpu.pc++;
    write_u8(gb, A16, gb->cpu.sp & 255);
    write_u8(gb, A16 + 1, gb->cpu.sp >> 8);
}

// 0xf9, 1 byte, 2 cycles
void ld_sp_hl(struct gameboy *gb) {
    gb->cpu.pc++;
    gb->cpu.sp = R16HL;
}

// 0xf8, 2 bytes, 3 cycles
void ld_hl_sp_e(struct gameboy *gb) {
    gb->cpu.pc++;
    gb->cpu.i16 = (int8_t)read_u8(gb, gb->cpu.pc); //signed XXX
    gb->cpu.pc++;
    CLEAR_Z_FLAG;
    CLEAR_N_FLAG;
    ((gb->cpu.sp & 0xf) + (gb->cpu.i16 & 0xf)) > 0xf ? SET_H_FLAG : CLEAR_H_FLAG;
    ((gb->cpu.sp & 0xff) + (gb->cpu.i16 & 0xff)) > 0xff ? SET_C_FLAG : CLEAR_C_FLAG;
    gb->cpu.r8[4] = (gb->cpu.sp + gb->cpu.i16) >> 8;
    gb->cpu.r8[5] = (gb->cpu.sp + gb->cpu.i16) & 255;
}


// 0b11xx0101: 0xc5, 0xd5, 0xe5, 0xf5; bc,de,hl,af
// 1 byte, 4 cycles
void push_rr(struct gameboy *gb) {
    gb->cpu.pc++;
    gb->cpu.sp--;
    if (U2IDX == 3) {
        write_u8(gb, gb->cpu.sp, gb->cpu.r8[7]);    // a
    } else {
        write_u8(gb, gb->cpu.sp, gb->cpu.r8[U2IDX * 2]);
    }
    gb->cpu.sp--;
    if (U2IDX == 3) {
        write_u8(gb, gb->cpu.sp, gb->cpu.r8[6] & 0b11110000); // f
    } else {
        write_u8(gb, gb->cpu.sp, gb->cpu.r8[U2IDX * 2 + 1]);
    }
}


// 0b11xx0001: 0xc1, 0xd1, 0xe1, 0xf1; bc,de,hl,af
// 1 byte, 3 cycles
void pop_rr(struct gameboy *gb) {
    gb->cpu.pc++;
    if (U2IDX == 3) {
        gb->cpu.r8[6] = read_u8(gb, gb->cpu.sp) & 0b11110000; // f
    } else {
        gb->cpu.r8[U2IDX * 2 + 1] = read_u8(gb, gb->cpu.sp);
    }
    gb->cpu.sp++;
    if (U2IDX == 3) {
        gb->cpu.r8[7] = read_u8(gb, gb->cpu.sp); // a
    } else {
        gb->cpu.r8[U2IDX * 2] = read_u8(gb, gb->cpu.sp);
    }
    gb->cpu.sp++;
}

/*
** 8-bit arithmetic instructions
*/

// 0x04, 0x0c, 0x14, 0x1c, 0x24, 0x2c, 0x3c - 1 byte, 1 cycle
void inc_r(struct gameboy *gb) {
    gb->cpu.pc++;
    gb->cpu.r8[U3DST]++;
    (gb->cpu.r8[U3DST] == 0) ? SET_Z_FLAG : CLEAR_Z_FLAG;
    CLEAR_N_FLAG;
    ((gb->cpu.r8[U3DST] & 0xf) == 0) ? SET_H_FLAG : CLEAR_H_FLAG;
}

// 0x34: 1 byte, 3 cycles
void inc_hl(struct gameboy *gb) {
    gb->cpu.pc++;
    gb->cpu.lo = read_u8(gb, R16HL);
    gb->cpu.lo++;
    (gb->cpu.lo == 0) ? SET_Z_FLAG : CLEAR_Z_FLAG;
    CLEAR_N_FLAG;
    ((gb->cpu.lo & 0xf) == 0) ? SET_H_FLAG : CLEAR_H_FLAG;
    write_u8(gb, R16HL, gb->cpu.lo);
}

// 0x05, 0x0d, 0x15, 0x1d, 0x25, 0x2d, 0x3d - 1 byte, 1 cycle
void dec_r(struct gameboy *gb) {
    gb->cpu.pc++;
    gb->cpu.r8[U3DST]--;
    (gb->cpu.r8[U3DST] == 0) ? SET_Z_FLAG : CLEAR_Z_FLAG;
    SET_N_FLAG;
    ((gb->cpu.r8[U3DST] & 0xf) == 0) ? SET_H_FLAG : CLEAR_H_FLAG;
}

// 0x35: 1 byte, 3 cycles
void dec_hl(struct gameboy *gb) {
    gb->cpu.pc++;
    gb->cpu.lo = read_u8(gb, R16HL);
    gb->cpu.lo--;
    (gb->cpu.lo == 0) ? SET_Z_FLAG : CLEAR_Z_FLAG;
    SET_N_FLAG;
    ((gb->cpu.lo & 0xf) == 0) ? SET_H_FLAG : CLEAR_H_FLAG;
    write_u8(gb, R16HL, gb->cpu.lo);
}

#define _ADD \
    (((gb->cpu.r8[7] & 15) + (gb->cpu.lo & 15)) > 15) ? SET_H_FLAG : CLEAR_H_FLAG;\
    ((gb->cpu.r8[7] + gb->cpu.lo) > 255) ? SET_C_FLAG : CLEAR_C_FLAG;\
    gb->cpu.r8[7] += gb->cpu.lo;\
    (gb->cpu.r8[7] == 0) ? SET_Z_FLAG : CLEAR_Z_FLAG;\
    CLEAR_N_FLAG;

// 0x80-0x87, except 0x86: 1 byte, 1 cycle
void add_r(struct gameboy *gb)  { gb->cpu.pc++; gb->cpu.lo = gb->cpu.r8[U3SRC]; _ADD; }
// 0x86: 1 byte, 2 cycles
void add_hl(struct gameboy *gb) { gb->cpu.pc++; gb->cpu.lo = read_u8(gb, R16HL); _ADD; }
// 0xc6: 2 bytes, 2 cycles
void add_n(struct gameboy *gb)  { gb->cpu.pc++; gb->cpu.lo = read_u8(gb, gb->cpu.pc); gb->cpu.pc++; _ADD; }

#define _ADC \
    gb->cpu.u16 = gb->cpu.r8[7] + gb->cpu.lo + IS_C_FLAG;\
    (((gb->cpu.r8[7] & 15) + (gb->cpu.lo & 15) + IS_C_FLAG) > 15) ? SET_H_FLAG : CLEAR_H_FLAG;\
    (gb->cpu.u16 > 255) ? SET_C_FLAG : CLEAR_C_FLAG;\
    gb->cpu.r8[7] = gb->cpu.u16 & 255;\
    (gb->cpu.r8[7] == 0) ? SET_Z_FLAG : CLEAR_Z_FLAG;\
    CLEAR_N_FLAG;

// 0x88-0x8f, except 0x8e: 1 byte, 1 cycle
void adc_r(struct gameboy *gb)  { gb->cpu.pc++; gb->cpu.lo = gb->cpu.r8[U3SRC]; _ADC; }
// 0x8e: 1 byte, 2 cycles
void adc_hl(struct gameboy *gb) { gb->cpu.pc++; gb->cpu.lo = read_u8(gb, R16HL); _ADC; }
// 0xce: 2 bytes, 2 cycles
void adc_n(struct gameboy *gb)  { gb->cpu.pc++; gb->cpu.lo = read_u8(gb, gb->cpu.pc); gb->cpu.pc++; _ADC; }

#define _SUB \
    ((gb->cpu.r8[7] & 15) < (gb->cpu.lo & 15)) ? SET_H_FLAG : CLEAR_H_FLAG;\
    (gb->cpu.r8[7] < gb->cpu.lo) ? SET_C_FLAG : CLEAR_C_FLAG;\
    gb->cpu.r8[7] -= gb->cpu.lo;\
    (gb->cpu.r8[7] == 0) ? SET_Z_FLAG : CLEAR_Z_FLAG;\
    SET_N_FLAG;

// 0x90-97, except 0x96: 1 byte, 1 cycle
void sub_r(struct gameboy *gb)  { gb->cpu.pc++; gb->cpu.lo = gb->cpu.r8[U3SRC]; _SUB; }
// 0x96: 1 byte, 2 cycles
void sub_hl(struct gameboy *gb) { gb->cpu.pc++; gb->cpu.lo = read_u8(gb, R16HL); _SUB; }
// 0xd6: 2 bytes, 2 cycles
void sub_n(struct gameboy *gb)  { gb->cpu.pc++; gb->cpu.lo = read_u8(gb, gb->cpu.pc); gb->cpu.pc++; _SUB; }

#define _SBC \
    gb->cpu.i16 = gb->cpu.r8[7] - gb->cpu.lo - IS_C_FLAG;\
    (((gb->cpu.r8[7] & 15) - (gb->cpu.lo & 15) - IS_C_FLAG) < 0) ? SET_H_FLAG : CLEAR_H_FLAG;\
    (gb->cpu.i16 < 0) ? SET_C_FLAG : CLEAR_C_FLAG;\
    gb->cpu.r8[7] = gb->cpu.i16 & 255;\
    (gb->cpu.r8[7] == 0) ? SET_Z_FLAG : CLEAR_Z_FLAG;\
    SET_N_FLAG;

// 0x98-0x9f, except 0x9e: 1 byte, 1 cycle
void sbc_r(struct gameboy *gb)  { gb->cpu.pc++; gb->cpu.lo = gb->cpu.r8[U3SRC]; _SBC; }
// 0x9e: 1 byte, 2 cycles
void sbc_hl(struct gameboy *gb) { gb->cpu.pc++; gb->cpu.lo = read_u8(gb, R16HL); _SBC; }
// 0xde: 2 bytes, 2 cycles
void sbc_n(struct gameboy *gb)  { gb->cpu.pc++; gb->cpu.lo = read_u8(gb, gb->cpu.pc); gb->cpu.pc++; _SBC; }

#define _AND \
    gb->cpu.r8[7] &= gb->cpu.lo;\
    (gb->cpu.r8[7] == 0) ? SET_Z_FLAG : CLEAR_Z_FLAG;\
    CLEAR_N_FLAG;\
    SET_H_FLAG;\
    CLEAR_C_FLAG;

// 0xa0-a7, except 0xa6: 1 byte, 1 cycle
void and_r(struct gameboy *gb)  { gb->cpu.pc++; gb->cpu.lo = gb->cpu.r8[U3SRC]; _AND; }
// 0xa6: 1 byte, 2 cycles
void and_hl(struct gameboy *gb) { gb->cpu.pc++; gb->cpu.lo = read_u8(gb, R16HL); _AND; }
// 0xe6: 2 bytes, 2 cycles
void and_n(struct gameboy *gb)  { gb->cpu.pc++; gb->cpu.lo = read_u8(gb, gb->cpu.pc); gb->cpu.pc++; _AND; }

#define _XOR \
    gb->cpu.r8[7] ^= gb->cpu.lo;\
    (gb->cpu.r8[7] == 0) ? SET_Z_FLAG : CLEAR_Z_FLAG;\
    CLEAR_N_FLAG;\
    CLEAR_H_FLAG;\
    CLEAR_C_FLAG;

// 0xa8-0xaf, except 0xae: 1 byte, 1 cycle
void xor_r(struct gameboy *gb)  { gb->cpu.pc++; gb->cpu.lo = gb->cpu.r8[U3SRC]; _XOR; }
// 0xae: 1 byte, 2 cycles
void xor_hl(struct gameboy *gb) { gb->cpu.pc++; gb->cpu.lo = read_u8(gb, R16HL); _XOR; }
// 0xee: 2 bytes, 2 cycles
void xor_n(struct gameboy *gb)  { gb->cpu.pc++; gb->cpu.lo = read_u8(gb, gb->cpu.pc); gb->cpu.pc++; _XOR; }

#define _OR \
    gb->cpu.r8[7] |= gb->cpu.lo;\
    (gb->cpu.r8[7] == 0) ? SET_Z_FLAG : CLEAR_Z_FLAG;\
    CLEAR_N_FLAG;\
    CLEAR_H_FLAG;\
    CLEAR_C_FLAG;

// 0xb0-b7, except 0xb6: 1 byte, 1 cycle
void or_r(struct gameboy *gb)  { gb->cpu.pc++; gb->cpu.lo = gb->cpu.r8[U3SRC]; _OR; }
// 0xb6: 1 byte, 2 cycles
void or_hl(struct gameboy *gb) { gb->cpu.pc++; gb->cpu.lo = read_u8(gb, R16HL); _OR; }
// 0xf6: 2 bytes, 2 cycles
void or_n(struct gameboy *gb)  { gb->cpu.pc++; gb->cpu.lo = read_u8(gb, gb->cpu.pc); gb->cpu.pc++; _OR; }

#define _CP \
    (gb->cpu.r8[7] == gb->cpu.lo) ? SET_Z_FLAG : CLEAR_Z_FLAG;\
    SET_N_FLAG;\
    ((gb->cpu.r8[7] & 15) < (gb->cpu.lo & 15)) ? SET_H_FLAG : CLEAR_H_FLAG;\
    (gb->cpu.r8[7] < gb->cpu.lo) ? SET_C_FLAG : CLEAR_C_FLAG;

// 0xb8-0xbf, except 0xbe: 1 byte, 1 cycle
void cp_r(struct gameboy *gb)  { gb->cpu.pc++; gb->cpu.lo = gb->cpu.r8[U3SRC]; _CP; }
// 0xbe: 1 byte, 2 cycles
void cp_hl(struct gameboy *gb) { gb->cpu.pc++; gb->cpu.lo = read_u8(gb, R16HL); _CP; }
// 0xfe: 2 bytes, 2 cycles
void cp_n(struct gameboy *gb)  { gb->cpu.pc++; gb->cpu.lo = read_u8(gb, gb->cpu.pc); gb->cpu.pc++; _CP; }

/*
** 16-bit arithmetic instructions
*/

// 0x03, 0x13, 0x23, 0x33: 1 byte, 2 cycles
void inc_rr(struct gameboy *gb) {
    gb->cpu.pc++;
    if (U2IDX == 3) {
        gb->cpu.sp++;
    } else {
        gb->cpu.u16 = (gb->cpu.r8[U2IDX * 2] << 8) + gb->cpu.r8[U2IDX * 2 + 1];
        gb->cpu.u16++;
        gb->cpu.r8[U2IDX * 2] = gb->cpu.u16 >> 8;
        gb->cpu.r8[U2IDX * 2 + 1] = gb->cpu.u16 & 255;
    }
}

// 0x0b, 0x1b, 0x2b, 0x3b: 1 byte, 2 cycles
void dec_rr(struct gameboy *gb) {
    gb->cpu.pc++;
    if (U2IDX == 3) {
        gb->cpu.sp--;
    } else {
        gb->cpu.u16 = (gb->cpu.r8[U2IDX * 2] << 8) + gb->cpu.r8[U2IDX * 2 + 1];
        gb->cpu.u16--;
        gb->cpu.r8[U2IDX * 2] = gb->cpu.u16 >> 8;
        gb->cpu.r8[U2IDX * 2 + 1] = gb->cpu.u16 & 255;
    }
}

// 0x09, 0x19, 0x29, 0x39 - 1 byte, 2 cycles
void add_hl_rr(struct gameboy *gb) {
    gb->cpu.pc++;
    if (U2IDX == 3) {
        gb->cpu.u16 = gb->cpu.sp;
    } else {
        gb->cpu.u16 = (gb->cpu.r8[U2IDX * 2] << 8) + gb->cpu.r8[U2IDX * 2 + 1];
    }
    CLEAR_N_FLAG;
    ((R16HL & 0xfff) + (gb->cpu.u16 & 0xfff) > 0xfff) ? SET_H_FLAG : CLEAR_H_FLAG;
    ((R16HL + gb->cpu.u16) > 0xffff) ? SET_C_FLAG : CLEAR_C_FLAG;
    gb->cpu.u16 += R16HL;
    gb->cpu.r8[4] = gb->cpu.u16 >> 8;
    gb->cpu.r8[5] = gb->cpu.u16 & 255;
}

// 0xe8, 2 bytes, 4 cycles
void add_sp_e(struct gameboy *gb) {
    gb->cpu.pc++;
    gb->cpu.i16 = (int8_t)read_u8(gb, gb->cpu.pc); //signed XXX
    gb->cpu.pc++;
    CLEAR_Z_FLAG;
    CLEAR_N_FLAG;
    (gb->cpu.sp & 0xf) + (gb->cpu.i16 & 0xf) > 0xf ? SET_H_FLAG : CLEAR_H_FLAG;
    (gb->cpu.sp & 0xff) + (gb->cpu.i16 & 0xff) > 0xff ? SET_C_FLAG : CLEAR_C_FLAG;
    gb->cpu.sp += gb->cpu.i16;
}

/*
** rotate, shift, and bit operation instructions
*/

#define _RLC \
    gb->cpu.lo = (gb->cpu.lo << 1) | ((gb->cpu.lo & 1) >> 7);\
    (gb->cpu.lo == 0) ? SET_Z_FLAG : CLEAR_Z_FLAG;\
    CLEAR_N_FLAG;\
    CLEAR_H_FLAG;\
    (gb->cpu.lo & 1) ? SET_C_FLAG : CLEAR_C_FLAG;

#define _RRC \
    (gb->cpu.lo & 1) ? SET_C_FLAG : CLEAR_C_FLAG;\
    gb->cpu.lo = (gb->cpu.lo >> 1) | ((gb->cpu.lo & 1) << 7);\
    (gb->cpu.lo == 0) ? SET_Z_FLAG : CLEAR_Z_FLAG;\
    CLEAR_N_FLAG;\
    CLEAR_H_FLAG;

#define _RL \
    gb->cpu.hi = IS_C_FLAG;\
    (gb->cpu.lo & 0x80) ? SET_C_FLAG : CLEAR_C_FLAG;\
    gb->cpu.lo = (gb->cpu.lo << 1) | gb->cpu.hi;\
    (gb->cpu.lo == 0) ? SET_Z_FLAG : CLEAR_Z_FLAG;\
    CLEAR_N_FLAG;\
    CLEAR_H_FLAG;

#define _RR \
    gb->cpu.hi = IS_C_FLAG;\
    (gb->cpu.lo & 1) ? SET_C_FLAG : CLEAR_C_FLAG;\
    gb->cpu.lo = (gb->cpu.lo >> 1) | (gb->cpu.hi << 7);\
    (gb->cpu.lo == 0) ? SET_Z_FLAG : CLEAR_Z_FLAG;\
    CLEAR_N_FLAG;\
    CLEAR_H_FLAG;

#define _SLA \
    (gb->cpu.lo & 0x80) ? SET_C_FLAG : CLEAR_C_FLAG;\
    gb->cpu.lo = gb->cpu.lo << 1;\
    (gb->cpu.lo == 0) ? SET_Z_FLAG : CLEAR_Z_FLAG;\
    CLEAR_N_FLAG;\
    CLEAR_H_FLAG;

#define _SRA \
    (gb->cpu.lo & 1) ? SET_C_FLAG : CLEAR_C_FLAG;\
    gb->cpu.lo = (gb->cpu.lo & 0x80) | (gb->cpu.lo >> 1);\
    (gb->cpu.lo == 0) ? SET_Z_FLAG : CLEAR_Z_FLAG;\
    CLEAR_N_FLAG;\
    CLEAR_H_FLAG;

#define _SWAP \
    gb->cpu.lo = ((gb->cpu.lo & 0xf0) >> 4) | ((gb->cpu.lo & 0x0f) << 4);\
    (gb->cpu.lo == 0) ? SET_Z_FLAG : CLEAR_Z_FLAG;\
    CLEAR_N_FLAG;\
    CLEAR_H_FLAG;\
    CLEAR_C_FLAG;

#define _SRL \
    (gb->cpu.lo & 1) ? SET_C_FLAG : CLEAR_C_FLAG;\
    gb->cpu.lo = gb->cpu.lo >> 1;\
    (gb->cpu.lo == 0) ? SET_Z_FLAG : CLEAR_Z_FLAG;\
    CLEAR_N_FLAG;\
    CLEAR_H_FLAG;

#define _BIT \
    (gb->cpu.lo & (1 << U3DST)) ? CLEAR_Z_FLAG : SET_Z_FLAG;\
    CLEAR_N_FLAG;\
    SET_H_FLAG;

#define _RES \
    gb->cpu.lo &= ~(1 << U3DST);

#define _SET \
    gb->cpu.lo |= (1 << U3DST);

// CB-prefix + 1 cycle
void rlc_r(struct gameboy *gb)   { gb->cpu.pc++; gb->cpu.lo = gb->cpu.r8[U3SRC];      _RLC;  gb->cpu.r8[U3SRC] = gb->cpu.lo; }
void rrc_r(struct gameboy *gb)   { gb->cpu.pc++; gb->cpu.lo = gb->cpu.r8[U3SRC];      _RRC;  gb->cpu.r8[U3SRC] = gb->cpu.lo; }
void rl_r(struct gameboy *gb)    { gb->cpu.pc++; gb->cpu.lo = gb->cpu.r8[U3SRC];      _RL;   gb->cpu.r8[U3SRC] = gb->cpu.lo; }
void rr_r(struct gameboy *gb)    { gb->cpu.pc++; gb->cpu.lo = gb->cpu.r8[U3SRC];      _RR;   gb->cpu.r8[U3SRC] = gb->cpu.lo; }
void sla_r(struct gameboy *gb)   { gb->cpu.pc++; gb->cpu.lo = gb->cpu.r8[U3SRC];      _SLA;  gb->cpu.r8[U3SRC] = gb->cpu.lo; }
void sra_r(struct gameboy *gb)   { gb->cpu.pc++; gb->cpu.lo = gb->cpu.r8[U3SRC];      _SRA;  gb->cpu.r8[U3SRC] = gb->cpu.lo; }
void swap_r(struct gameboy *gb)  { gb->cpu.pc++; gb->cpu.lo = gb->cpu.r8[U3SRC];      _SWAP; gb->cpu.r8[U3SRC] = gb->cpu.lo; }
void srl_r(struct gameboy *gb)   { gb->cpu.pc++; gb->cpu.lo = gb->cpu.r8[U3SRC];      _SRL;  gb->cpu.r8[U3SRC] = gb->cpu.lo; }
void bit_r(struct gameboy *gb)   { gb->cpu.pc++; gb->cpu.lo = gb->cpu.r8[U3SRC];      _BIT;  gb->cpu.r8[U3SRC] = gb->cpu.lo; }
void res_r(struct gameboy *gb)   { gb->cpu.pc++; gb->cpu.lo = gb->cpu.r8[U3SRC];      _RES;  gb->cpu.r8[U3SRC] = gb->cpu.lo; }
void set_r(struct gameboy *gb)   { gb->cpu.pc++; gb->cpu.lo = gb->cpu.r8[U3SRC];      _SET;  gb->cpu.r8[U3SRC] = gb->cpu.lo; }

// CB-prefix + 3 cycles
void rlc_hl(struct gameboy *gb)  { gb->cpu.pc++; gb->cpu.lo = read_u8(gb, R16HL); _RLC;  write_u8(gb, R16HL, gb->cpu.lo); }
void rrc_hl(struct gameboy *gb)  { gb->cpu.pc++; gb->cpu.lo = read_u8(gb, R16HL); _RRC;  write_u8(gb, R16HL, gb->cpu.lo); }
void rl_hl(struct gameboy *gb)   { gb->cpu.pc++; gb->cpu.lo = read_u8(gb, R16HL); _RL;   write_u8(gb, R16HL, gb->cpu.lo); }
void rr_hl(struct gameboy *gb)   { gb->cpu.pc++; gb->cpu.lo = read_u8(gb, R16HL); _RR;   write_u8(gb, R16HL, gb->cpu.lo); }
void sla_hl(struct gameboy *gb)  { gb->cpu.pc++; gb->cpu.lo = read_u8(gb, R16HL); _SLA;  write_u8(gb, R16HL, gb->cpu.lo); }
void sra_hl(struct gameboy *gb)  { gb->cpu.pc++; gb->cpu.lo = read_u8(gb, R16HL); _SRA;  write_u8(gb, R16HL, gb->cpu.lo); }
void swap_hl(struct gameboy *gb) { gb->cpu.pc++; gb->cpu.lo = read_u8(gb, R16HL); _SWAP; write_u8(gb, R16HL, gb->cpu.lo); }
void srl_hl(struct gameboy *gb)  { gb->cpu.pc++; gb->cpu.lo = read_u8(gb, R16HL); _SRL;  write_u8(gb, R16HL, gb->cpu.lo); }
void bit_hl(struct gameboy *gb)  { gb->cpu.pc++; gb->cpu.lo = read_u8(gb, R16HL); _BIT;  write_u8(gb, R16HL, gb->cpu.lo); }
void res_hl(struct gameboy *gb)  { gb->cpu.pc++; gb->cpu.lo = read_u8(gb, R16HL); _RES;  write_u8(gb, R16HL, gb->cpu.lo); }
void set_hl(struct gameboy *gb)  { gb->cpu.pc++; gb->cpu.lo = read_u8(gb, R16HL); _SET;  write_u8(gb, R16HL, gb->cpu.lo); }

/*
** control flow instructions
*/

// 0xc3, 3 bytes, 4 cycles
void jp_a16(struct gameboy *gb) {
    gb->cpu.pc++;
    gb->cpu.lo = read_u8(gb, gb->cpu.pc);
    gb->cpu.pc++;
    gb->cpu.hi = read_u8(gb, gb->cpu.pc);
    gb->cpu.pc++;
    gb->cpu.pc = A16;
}

// 0xe9, 1 byte, 1 cycle
void jp_hl(struct gameboy *gb) {
    gb->cpu.pc++;
    gb->cpu.pc = R16HL;
}

// 0b110cc010: 0xc2 (NZ), 0xca (Z), 0xd2 (NC), 0xda (C)
// 3 bytes, 3 cycles (cc false) - or - 4 cycles (cc true)
void jp_cc_a16(struct gameboy *gb) {
    gb->cpu.pc++;
    gb->cpu.lo = read_u8(gb, gb->cpu.pc);
    gb->cpu.pc++;
    gb->cpu.hi = read_u8(gb, gb->cpu.pc);
    gb->cpu.pc++;
    if (CONDITION) {
        gb->cpu.pc = A16;
    }
}

// 0x18, 2 bytes, 3 cycles
void jr_e(struct gameboy *gb) {
    gb->cpu.pc++;
    gb->cpu.i16 = (int8_t)read_u8(gb, gb->cpu.pc); //signed XXX
    gb->cpu.pc++;
    gb->cpu.pc += gb->cpu.i16;
}

// 0b001cc000: 0x20 (NZ), 0x28 (Z), 0x30 (NC), 0x38 (C)
// 2 bytes, 2 cycles (cc false) - or - 3 cycles (cc true)
void jr_cc_e(struct gameboy *gb) {
    gb->cpu.pc++;
    gb->cpu.i16 = (int8_t)read_u8(gb, gb->cpu.pc); //signed XXX
    gb->cpu.pc++;
    if (CONDITION) {
        gb->cpu.pc += gb->cpu.i16;
    }
}

// 0xcd, 3 bytes, 6 cycles
void call_a16(struct gameboy *gb) {
    gb->cpu.pc++;
    gb->cpu.lo = read_u8(gb, gb->cpu.pc);
    gb->cpu.pc++;
    gb->cpu.hi = read_u8(gb, gb->cpu.pc);
    gb->cpu.pc++;
    gb->cpu.sp--;
    write_u8(gb, gb->cpu.sp, gb->cpu.pc >> 8);
    gb->cpu.sp--;
    write_u8(gb, gb->cpu.sp, gb->cpu.pc & 255);
    gb->cpu.pc = A16;
}

// 0b110cc100: 0xc4 (NZ) 0xcc (Z), 0xd4 (NC), 0xdc (C)
// 3 bytes, 3 cycles (cc false) - or - 6 cycles (cc true)
void call_cc_a16(struct gameboy *gb) {
    gb->cpu.pc++;
    gb->cpu.lo = read_u8(gb, gb->cpu.pc);
    gb->cpu.pc++;
    gb->cpu.hi = read_u8(gb, gb->cpu.pc);
    gb->cpu.pc++;
    if (CONDITION) {
        gb->cpu.sp--;
        write_u8(gb, gb->cpu.sp, gb->cpu.pc >> 8);
        gb->cpu.sp--;
        write_u8(gb, gb->cpu.sp, gb->cpu.pc & 255);
        gb->cpu.pc = A16;
    }
}

// 0xc9, 1 byte, 4 cycles
void ret(struct gameboy *gb) {
    gb->cpu.pc++;
    gb->cpu.lo = read_u8(gb, gb->cpu.sp);
    gb->cpu.sp++;
    gb->cpu.hi = read_u8(gb, gb->cpu.sp);
    gb->cpu.sp++;
    gb->cpu.pc = A16;
}

// 0b110cc000: 0xc0 (NZ), 0xc8 (Z), 0xd0 (NC), 0xd8 (C)
// 1 byte, 2 cycles (cc false) - or - 5 cycles (cc true)
void ret_cc(struct gameboy *gb) {
    gb->cpu.pc++;
    if (CONDITION) {
        gb->cpu.lo = read_u8(gb, gb->cpu.sp);
        gb->cpu.sp++;
        gb->cpu.hi = read_u8(gb, gb->cpu.sp);
        gb->cpu.sp++;
        gb->cpu.pc = A16;
    }
}

// 0xd9, 1 byte, 4 cycles
void reti(struct gameboy *gb) {
    gb->cpu.pc++;
    gb->cpu.lo = read_u8(gb, gb->cpu.sp);
    gb->cpu.sp++;
    gb->cpu.hi = read_u8(gb, gb->cpu.sp);
    gb->cpu.sp++;
    gb->cpu.pc = A16;
    gb->cpu.ime = 1;
}

// 0b11xxx111: c7,cf,d7,df,e7,ef,f7,ff
// 1 byte, 4 cycles;
void rst(struct gameboy *gb) {
    gb->cpu.pc++;
    gb->cpu.sp--;
    write_u8(gb, gb->cpu.sp, gb->cpu.pc >> 8);
    gb->cpu.sp--;
    write_u8(gb, gb->cpu.sp, gb->cpu.pc & 255);
    gb->cpu.pc = gb->cpu.opcode & 0b00111000;
}

/*
** miscellaneous instructions
*/

// 0x76 XXX 1 byte, 1 cycle
void halt(struct gameboy *gb) {
    gb->cpu.pc++;
    gb->cpu.cpu_state = HALTED;
}

// 0x10 XXX
void stop(struct gameboy *gb) {
    gb->cpu.pc++;
    gb->cpu.cpu_state = STOPPED;
}

// 0xf3, 1 byte, 1 cycle
void di(struct gameboy *gb) {
    gb->cpu.pc++;
    gb->cpu.ime = gb->cpu.ime_scheduled = 0;
}

// 0xfb, 1 byte, 1 cycle
void ei(struct gameboy *gb) {
    gb->cpu.pc++;
    gb->cpu.ime_scheduled = 1;
}

// 0x3f, 1 byte, 1 cycle
void ccf(struct gameboy *gb) {
    gb->cpu.pc++;
    CLEAR_N_FLAG;
    CLEAR_H_FLAG;
    IS_C_FLAG ? CLEAR_C_FLAG : SET_C_FLAG;
}

// 0x37, 1 byte, 1 cycle
void scf(struct gameboy *gb) {
    gb->cpu.pc++;
    CLEAR_N_FLAG;
    CLEAR_H_FLAG;
    SET_C_FLAG;
}

// 0x00, 1 byte, 1 cycle
void nop(struct gameboy *gb) {
    gb->cpu.pc++;
}

// 0x27, 1 byte, 1 cycle
// https://forums.nesdev.com/viewtopic.php?f=20&t=15944
void daa(struct gameboy *gb) {
    gb->cpu.pc++;

    if (!IS_N_FLAG) {
        if ((IS_C_FLAG) || (gb->cpu.r8[7] > 0x99)) {
            gb->cpu.r8[7] += 0x60;
            SET_C_FLAG;
        }

        if ((IS_H_FLAG) || ((gb->cpu.r8[7] & 0x0f) > 0x09)) {
            gb->cpu.r8[7] += 0x6;
        }
    } else {
        if (IS_C_FLAG) {
            gb->cpu.r8[7] -= 0x60;
        }

        if (IS_H_FLAG) {
            gb->cpu.r8[7] -= 0x6;
        }
    }

    (gb->cpu.r8[7] == 0) ? SET_Z_FLAG : CLEAR_Z_FLAG;
    CLEAR_H_FLAG;
}

// 0x2f, 1 byte, 1 cycle
void cpl(struct gameboy *gb) {
    gb->cpu.pc++;
    gb->cpu.r8[7] = ~(gb->cpu.r8[7]);
    SET_N_FLAG;
    SET_H_FLAG;
}

void (*instruct[])(struct gameboy *gb) = {
     nop, ld_rr_d16,   ld_bc_a,  inc_rr,       inc_r,   dec_r,  ld_r_d8,   rlc_r,  ld_a16_sp, add_hl_rr,   ld_a_bc, dec_rr,       inc_r,    dec_r, ld_r_d8,  rrc_r,
    stop, ld_rr_d16,   ld_de_a,  inc_rr,       inc_r,   dec_r,  ld_r_d8,    rl_r,       jr_e, add_hl_rr,   ld_a_de, dec_rr,       inc_r,    dec_r, ld_r_d8,   rr_r,
 jr_cc_e, ld_rr_d16,  ld_hli_a,  inc_rr,       inc_r,   dec_r,  ld_r_d8,     daa,    jr_cc_e, add_hl_rr,  ld_a_hli, dec_rr,       inc_r,    dec_r, ld_r_d8,    cpl,
 jr_cc_e, ld_rr_d16,  ld_hld_a,  inc_rr,      inc_hl,  dec_hl, ld_hl_d8,     scf,    jr_cc_e, add_hl_rr,  ld_a_hld, dec_rr,       inc_r,    dec_r, ld_r_d8,    ccf,
  ld_r_r,    ld_r_r,    ld_r_r,  ld_r_r,      ld_r_r,  ld_r_r,  ld_r_hl,  ld_r_r,     ld_r_r,    ld_r_r,    ld_r_r, ld_r_r,      ld_r_r,   ld_r_r, ld_r_hl, ld_r_r,
  ld_r_r,    ld_r_r,    ld_r_r,  ld_r_r,      ld_r_r,  ld_r_r,  ld_r_hl,  ld_r_r,     ld_r_r,    ld_r_r,    ld_r_r, ld_r_r,      ld_r_r,   ld_r_r, ld_r_hl, ld_r_r,
  ld_r_r,    ld_r_r,    ld_r_r,  ld_r_r,      ld_r_r,  ld_r_r,  ld_r_hl,  ld_r_r,     ld_r_r,    ld_r_r,    ld_r_r, ld_r_r,      ld_r_r,   ld_r_r, ld_r_hl, ld_r_r,
 ld_hl_r,   ld_hl_r,   ld_hl_r, ld_hl_r,     ld_hl_r, ld_hl_r,     halt, ld_hl_r,     ld_r_r,    ld_r_r,    ld_r_r, ld_r_r,      ld_r_r,   ld_r_r, ld_r_hl, ld_r_r,
   add_r,     add_r,     add_r,   add_r,       add_r,   add_r,   add_hl,   add_r,      adc_r,     adc_r,     adc_r,  adc_r,       adc_r,    adc_r,  adc_hl,  adc_r,
   sub_r,     sub_r,     sub_r,   sub_r,       sub_r,   sub_r,   sub_hl,   sub_r,      sbc_r,     sbc_r,     sbc_r,  sbc_r,       sbc_r,    sbc_r,  sbc_hl,  sbc_r,
   and_r,     and_r,     and_r,   and_r,       and_r,   and_r,   and_hl,   and_r,      xor_r,     xor_r,     xor_r,  xor_r,       xor_r,    xor_r,  xor_hl,  xor_r,
    or_r,      or_r,      or_r,    or_r,        or_r,    or_r,    or_hl,    or_r,       cp_r,      cp_r,      cp_r,   cp_r,        cp_r,     cp_r,   cp_hl,   cp_r,
  ret_cc,    pop_rr, jp_cc_a16,  jp_a16, call_cc_a16, push_rr,    add_n,     rst,     ret_cc,       ret, jp_cc_a16,      0, call_cc_a16, call_a16,   adc_n,    rst,
  ret_cc,    pop_rr, jp_cc_a16,       0, call_cc_a16, push_rr,    sub_n,     rst,     ret_cc,      reti, jp_cc_a16,      0, call_cc_a16,        0,   sbc_n,    rst,
ldh_a8_a,    pop_rr,   ldh_c_a,       0,           0, push_rr,    and_n,     rst,   add_sp_e,     jp_hl,  ld_a16_a,      0,           0,        0,   xor_n,    rst,
ldh_a_a8,    pop_rr,   ldh_a_c,      di,           0, push_rr,     or_n,     rst, ld_hl_sp_e,  ld_sp_hl,  ld_a_a16,     ei,           0,        0,    cp_n,    rst,

   rlc_r,     rlc_r,     rlc_r,   rlc_r,     rlc_r,     rlc_r,   rlc_hl,   rlc_r,      rrc_r,     rrc_r,     rrc_r,  rrc_r,       rrc_r,    rrc_r,  rrc_hl,  rrc_r,
    rl_r,      rl_r,      rl_r,    rl_r,      rl_r,      rl_r,    rl_hl,    rl_r,       rr_r,      rr_r,      rr_r,   rr_r,        rr_r,     rr_r,   rr_hl,   rr_r,
   sla_r,     sla_r,     sla_r,   sla_r,     sla_r,     sla_r,   sla_hl,   sla_r,      sra_r,     sra_r,     sra_r,  sra_r,       sra_r,    sra_r,  sra_hl,  sra_r,
  swap_r,    swap_r,    swap_r,  swap_r,    swap_r,    swap_r,  swap_hl,  swap_r,      srl_r,     srl_r,     srl_r,  srl_r,       srl_r,    srl_r,  srl_hl,  srl_r,
   bit_r,     bit_r,     bit_r,   bit_r,     bit_r,     bit_r,   bit_hl,   bit_r,      bit_r,     bit_r,     bit_r,  bit_r,       bit_r,    bit_r,  bit_hl,  bit_r,
   bit_r,     bit_r,     bit_r,   bit_r,     bit_r,     bit_r,   bit_hl,   bit_r,      bit_r,     bit_r,     bit_r,  bit_r,       bit_r,    bit_r,  bit_hl,  bit_r,
   bit_r,     bit_r,     bit_r,   bit_r,     bit_r,     bit_r,   bit_hl,   bit_r,      bit_r,     bit_r,     bit_r,  bit_r,       bit_r,    bit_r,  bit_hl,  bit_r,
   bit_r,     bit_r,     bit_r,   bit_r,     bit_r,     bit_r,   bit_hl,   bit_r,      bit_r,     bit_r,     bit_r,  bit_r,       bit_r,    bit_r,  bit_hl,  bit_r,
   res_r,     res_r,     res_r,   res_r,     res_r,     res_r,   res_hl,   res_r,      res_r,     res_r,     res_r,  res_r,       res_r,    res_r,  res_hl,  res_r,
   res_r,     res_r,     res_r,   res_r,     res_r,     res_r,   res_hl,   res_r,      res_r,     res_r,     res_r,  res_r,       res_r,    res_r,  res_hl,  res_r,
   res_r,     res_r,     res_r,   res_r,     res_r,     res_r,   res_hl,   res_r,      res_r,     res_r,     res_r,  res_r,       res_r,    res_r,  res_hl,  res_r,
   res_r,     res_r,     res_r,   res_r,     res_r,     res_r,   res_hl,   res_r,      res_r,     res_r,     res_r,  res_r,       res_r,    res_r,  res_hl,  res_r,
   set_r,     set_r,     set_r,   set_r,     set_r,     set_r,   set_hl,   set_r,      set_r,     set_r,     set_r,  set_r,       set_r,    set_r,  set_hl,  set_r,
   set_r,     set_r,     set_r,   set_r,     set_r,     set_r,   set_hl,   set_r,      set_r,     set_r,     set_r,  set_r,       set_r,    set_r,  set_hl,  set_r,
   set_r,     set_r,     set_r,   set_r,     set_r,     set_r,   set_hl,   set_r,      set_r,     set_r,     set_r,  set_r,       set_r,    set_r,  set_hl,  set_r,
   set_r,     set_r,     set_r,   set_r,     set_r,     set_r,   set_hl,   set_r,      set_r,     set_r,     set_r,  set_r,       set_r,    set_r,  set_hl,  set_r,
};
