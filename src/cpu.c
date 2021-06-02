#include "gb.h"
#include "cpu.h"
#include "hardware.h"

/*
** https://gekkio.fi/files/gb-docs/gbctr.pdf
** https://rgbds.gbdev.io/docs/master/gbz80.7
** https://gbdev.io/gb-opcodes/optables/
*/

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
    if (gb->cpu.step == 0) {
        gb->cpu.step = 1;
        gb->cpu.pc++;
    } else if (gb->cpu.step == 1) {
        gb->cpu.step = 0;
        gb->cpu.lo = read_u8(gb, gb->cpu.pc);
        gb->cpu.pc++;
        gb->cpu.r8[U3DST] = gb->cpu.lo;
    }
}

// 0b01xxx110 except 0x76 (4v X6, XE)
// 1 byte, 2 cycles
void ld_r_hl(struct gameboy *gb) {
    if (gb->cpu.step == 0) {
        gb->cpu.step = 1;
        gb->cpu.pc++;
    } else if (gb->cpu.step == 1) {
        gb->cpu.step = 0;
        gb->cpu.r8[U3DST] = read_u8(gb, R16HL);
    }
}

// 0b01110xxx except 0x76 (h 70-77)
// 1 byte, 2 cycles
void ld_hl_r(struct gameboy *gb) {
    if (gb->cpu.step == 0) {
        gb->cpu.step = 1;
        gb->cpu.pc++;
    } else if (gb->cpu.step == 1) {
        gb->cpu.step = 0;
        write_u8(gb, R16HL, gb->cpu.r8[U3SRC]);
    }
}

// 0x36, 2 bytes, 3 cycles
void ld_hl_d8(struct gameboy *gb) {
    if (gb->cpu.step == 0) {
        gb->cpu.step = 1;
        gb->cpu.pc++;
    } else if (gb->cpu.step == 1) {
        gb->cpu.step = 2;
        gb->cpu.lo = read_u8(gb, gb->cpu.pc);
        gb->cpu.pc++;
    } else if (gb->cpu.step == 2) {
        gb->cpu.step = 0;
        write_u8(gb, R16HL, gb->cpu.lo);
    }
}

// 0x0a, 1 byte, 2 cycles
void ld_a_bc(struct gameboy *gb) {
    if (gb->cpu.step == 0) {
        gb->cpu.step = 1;
        gb->cpu.pc++;
    } else if (gb->cpu.step == 1) {
        gb->cpu.step = 0;
        gb->cpu.r8[7] = read_u8(gb, R16BC);
    }
}

// 0x1a, 1 byte, 2 cycles
void ld_a_de(struct gameboy *gb) {
    if (gb->cpu.step == 0) {
        gb->cpu.step = 1;
        gb->cpu.pc++;
    } else if (gb->cpu.step == 1) {
        gb->cpu.step = 0;
        gb->cpu.r8[7] = read_u8(gb, R16DE);
    }
}

// 0x02, 1 byte, 2 cycles
void ld_bc_a(struct gameboy *gb) {
    if (gb->cpu.step == 0) {
        gb->cpu.step = 1;
        gb->cpu.pc++;
    } else if (gb->cpu.step == 1) {
        gb->cpu.step = 0;
        write_u8(gb, R16BC, gb->cpu.r8[7]);
    }
}

// 0x12, 1 byte, 2 cycles
void ld_de_a(struct gameboy *gb) {
    if (gb->cpu.step == 0) {
        gb->cpu.step = 1;
        gb->cpu.pc++;
    } else if (gb->cpu.step == 1) {
        gb->cpu.step = 0;
        write_u8(gb, R16DE, gb->cpu.r8[7]);
    }
}

// 0xfa, 3 bytes, 4 cycles
void ld_a_a16(struct gameboy *gb) {
    if (gb->cpu.step == 0) {
        gb->cpu.step = 1;
        gb->cpu.pc++;
    } else if (gb->cpu.step == 1) {
        gb->cpu.step = 2;
        gb->cpu.lo = read_u8(gb, gb->cpu.pc);
        gb->cpu.pc++;
    } else if (gb->cpu.step == 2) {
        gb->cpu.step = 3;
        gb->cpu.hi = read_u8(gb, gb->cpu.pc);
        gb->cpu.pc++;
    } else if (gb->cpu.step == 3) {
        gb->cpu.step = 0;
        gb->cpu.r8[7] = read_u8(gb, A16);
    }
}

// 0xea, 3 bytes, 4 cycles
void ld_a16_a(struct gameboy *gb) {
    if (gb->cpu.step == 0) {
        gb->cpu.step = 1;
        gb->cpu.pc++;
    } else if (gb->cpu.step == 1) {
        gb->cpu.step = 2;
        gb->cpu.lo = read_u8(gb, gb->cpu.pc);
        gb->cpu.pc++;
    } else if (gb->cpu.step == 2) {
        gb->cpu.step = 3;
        gb->cpu.hi = read_u8(gb, gb->cpu.pc);
        gb->cpu.pc++;
    } else if (gb->cpu.step == 3) {
        gb->cpu.step = 0;
        write_u8(gb, A16, gb->cpu.r8[7]);
    }
}

// 0xf2, 1 byte, 2 cycles
void ldh_a_c(struct gameboy *gb) {
    if (gb->cpu.step == 0) {
        gb->cpu.step = 1;
        gb->cpu.pc++;
    } else if (gb->cpu.step == 1) {
        gb->cpu.step = 0;
        gb->cpu.r8[7] = read_u8(gb, (0xff00 + gb->cpu.r8[1]));
    }
}

// 0xe2, 1 byte, 2 cycles
void ldh_c_a(struct gameboy *gb) {
    if (gb->cpu.step == 0) {
        gb->cpu.step = 1;
        gb->cpu.pc++;
    } else if (gb->cpu.step == 1) {
        gb->cpu.step = 0;
        write_u8(gb, (0xff00 + gb->cpu.r8[1]), gb->cpu.r8[7]);
    }
}

// 0xf0, 2 bytes, 3 cycles
void ldh_a_a8(struct gameboy *gb) {
    if (gb->cpu.step == 0) {
        gb->cpu.step = 1;
        gb->cpu.pc++;
    } else if (gb->cpu.step == 1) {
        gb->cpu.step = 2;
        gb->cpu.u16 = read_u8(gb, gb->cpu.pc);
        gb->cpu.pc++;
    } else if (gb->cpu.step == 2) {
        gb->cpu.step = 0;
        gb->cpu.r8[7] = read_u8(gb, 0xff00 + gb->cpu.u16);
    }
}

// 0xe0, 2 bytes, 3 cycles
void ldh_a8_a(struct gameboy *gb) {
    if (gb->cpu.step == 0) {
        gb->cpu.step = 1;
        gb->cpu.pc++;
    } else if (gb->cpu.step == 1) {
        gb->cpu.step = 2;
        gb->cpu.u16 = read_u8(gb, gb->cpu.pc);
        gb->cpu.pc++;
    } else if (gb->cpu.step == 2) {
        gb->cpu.step = 0;
        write_u8(gb, 0xff00 + gb->cpu.u16, gb->cpu.r8[7]);
    }
}

#define R16HLD \
    gb->cpu.u16 = R16HL - 1;\
    gb->cpu.r8[4] = gb->cpu.u16 >> 8;\
    gb->cpu.r8[5] = gb->cpu.u16 & 255;

#define R16HLI \
    gb->cpu.u16 = R16HL + 1;\
    gb->cpu.r8[4] = gb->cpu.u16 >> 8;\
    gb->cpu.r8[5] = gb->cpu.u16 & 255;

// 0x3a, 1 byte, 2 cycles
void ld_a_hld(struct gameboy *gb) {
    if (gb->cpu.step == 0) {
        gb->cpu.step = 1;
        gb->cpu.pc++;
    } else if (gb->cpu.step == 1) {
        gb->cpu.step = 0;
        gb->cpu.r8[7] = read_u8(gb, R16HL);
        R16HLD;
    }
}

// 0x32, 1 byte, 2 cycles
void ld_hld_a(struct gameboy *gb) {
    if (gb->cpu.step == 0) {
        gb->cpu.step = 1;
        gb->cpu.pc++;
    } else if (gb->cpu.step == 1) {
        gb->cpu.step = 0;
        write_u8(gb, R16HL, gb->cpu.r8[7]);
        R16HLD;
    }
}

// 0x2a, 1 byte, 2 cycles
void ld_a_hli(struct gameboy *gb) {
    if (gb->cpu.step == 0) {
        gb->cpu.step = 1;
        gb->cpu.pc++;
    } else if (gb->cpu.step == 1) {
        gb->cpu.step = 0;
        gb->cpu.r8[7] = read_u8(gb, R16HL);
        R16HLI;
    }
}

// 0x22, 1 byte, 2 cycles
void ld_hli_a(struct gameboy *gb) {
    if (gb->cpu.step == 0) {
        gb->cpu.step = 1;
        gb->cpu.pc++;
    } else if (gb->cpu.step == 1) {
        gb->cpu.step = 0;
        write_u8(gb, R16HL, gb->cpu.r8[7]);
        R16HLI;
    }
}

/*
** 16-bit load instructions
*/

// 0x01, 0x11, 0x21, 0x31
// 3 bytes, 3 cycles
void ld_rr_d16(struct gameboy *gb) {
    if (gb->cpu.step == 0) {
        gb->cpu.step = 1;
        gb->cpu.pc++;
    } else if (gb->cpu.step == 1) {
        gb->cpu.step = 2;
        gb->cpu.lo = read_u8(gb, gb->cpu.pc);
        gb->cpu.pc++;
    } else if (gb->cpu.step == 2) {
        gb->cpu.step = 0;
        gb->cpu.hi = read_u8(gb, gb->cpu.pc);
        gb->cpu.pc++;

        if (U2IDX == 3) {
            gb->cpu.sp = D16;
        } else {
            gb->cpu.r8[U2IDX * 2] = gb->cpu.hi;
            gb->cpu.r8[U2IDX * 2 + 1] = gb->cpu.lo;
        }
    }
}

// 0x08, 3 bytes, 5 cycles
void ld_a16_sp(struct gameboy *gb) {
    if (gb->cpu.step == 0) {
        gb->cpu.step = 1;
        gb->cpu.pc++;
    } else if (gb->cpu.step == 1) {
        gb->cpu.step = 2;
        gb->cpu.lo = read_u8(gb, gb->cpu.pc);
        gb->cpu.pc++;
    } else if (gb->cpu.step == 2) {
        gb->cpu.step = 3;
        gb->cpu.hi = read_u8(gb, gb->cpu.pc);
        gb->cpu.pc++;
    } else if (gb->cpu.step == 3) {
        gb->cpu.step = 4;
        write_u8(gb, A16, gb->cpu.sp & 255);
    } else if (gb->cpu.step == 4) {
        gb->cpu.step = 0;
        write_u8(gb, A16 + 1, gb->cpu.sp >> 8);
    }
}

// 0xf9, 1 byte, 2 cycles
void ld_sp_hl(struct gameboy *gb) {
    if (gb->cpu.step == 0) {
        gb->cpu.step = 1;
        gb->cpu.pc++;
    } else if (gb->cpu.step == 1) {
        gb->cpu.step = 0;
        gb->cpu.sp = R16HL;
    }
}

// 0xf8, 2 bytes, 3 cycles
void ld_hl_sp_e(struct gameboy *gb) {
    if (gb->cpu.step == 0) {
        gb->cpu.step = 1;
        gb->cpu.pc++;
    } else if (gb->cpu.step == 1) {
        gb->cpu.step = 2;
        gb->cpu.i16 = (int8_t)read_u8(gb, gb->cpu.pc); //signed XXX
        gb->cpu.pc++;
    } else if (gb->cpu.step == 2) {
        gb->cpu.step = 0;
        CLEAR_Z_FLAG;
        CLEAR_N_FLAG;
        ((gb->cpu.sp & 0xf) + (gb->cpu.i16 & 0xf)) > 0xf ? SET_H_FLAG : CLEAR_H_FLAG;
        ((gb->cpu.sp & 0xff) + (gb->cpu.i16 & 0xff)) > 0xff ? SET_C_FLAG : CLEAR_C_FLAG;
        gb->cpu.r8[4] = (gb->cpu.sp + gb->cpu.i16) >> 8;
        gb->cpu.r8[5] = (gb->cpu.sp + gb->cpu.i16) & 255;
    }
}

// 0b11xx0101: 0xc5, 0xd5, 0xe5, 0xf5; bc,de,hl,af
// 1 byte, 4 cycles
void push_rr(struct gameboy *gb) {
    if (gb->cpu.step == 0) {
        gb->cpu.step = 1;
        gb->cpu.pc++;
    } else if (gb->cpu.step == 1) {
        gb->cpu.step = 2;
    } else if (gb->cpu.step == 2) {
        gb->cpu.step = 3;
        gb->cpu.sp--;

        if (U2IDX == 3) {
            write_u8(gb, gb->cpu.sp, gb->cpu.r8[7]);    // a
        } else {
            write_u8(gb, gb->cpu.sp, gb->cpu.r8[U2IDX * 2]);
        }
    } else if (gb->cpu.step == 3) {
        gb->cpu.step = 0;
        gb->cpu.sp--;

        if (U2IDX == 3) {
            write_u8(gb, gb->cpu.sp, gb->cpu.r8[6] & 0b11110000); // f
        } else {
            write_u8(gb, gb->cpu.sp, gb->cpu.r8[U2IDX * 2 + 1]);
        }
    }
}

// 0b11xx0001: 0xc1, 0xd1, 0xe1, 0xf1; bc,de,hl,af
// 1 byte, 3 cycles
void pop_rr(struct gameboy *gb) {
    if (gb->cpu.step == 0) {
        gb->cpu.step = 1;
        gb->cpu.pc++;
    } else if (gb->cpu.step == 1) {
        gb->cpu.step = 2;

        if (U2IDX == 3) {
            gb->cpu.r8[6] = read_u8(gb, gb->cpu.sp) & 0b11110000; // f
        } else {
            gb->cpu.r8[U2IDX * 2 + 1] = read_u8(gb, gb->cpu.sp);
        }

        gb->cpu.sp++;
    } else if (gb->cpu.step == 2) {
        gb->cpu.step = 0;

        if (U2IDX == 3) {
            gb->cpu.r8[7] = read_u8(gb, gb->cpu.sp); // a
        } else {
            gb->cpu.r8[U2IDX * 2] = read_u8(gb, gb->cpu.sp);
        }

        gb->cpu.sp++;
    }
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
    if (gb->cpu.step == 0) {
        gb->cpu.step = 1;
        gb->cpu.pc++;
    } else if (gb->cpu.step == 1) {
        gb->cpu.step = 2;
        gb->cpu.lo = read_u8(gb, R16HL);
        gb->cpu.lo++;
    } else if (gb->cpu.step == 2) {
        gb->cpu.step = 0;
        (gb->cpu.lo == 0) ? SET_Z_FLAG : CLEAR_Z_FLAG;
        CLEAR_N_FLAG;
        ((gb->cpu.lo & 0xf) == 0) ? SET_H_FLAG : CLEAR_H_FLAG;
        write_u8(gb, R16HL, gb->cpu.lo);
    }
}

// 0x05, 0x0d, 0x15, 0x1d, 0x25, 0x2d, 0x3d - 1 byte, 1 cycle
void dec_r(struct gameboy *gb) {
    gb->cpu.pc++;
    gb->cpu.r8[U3DST]--;
    (gb->cpu.r8[U3DST] == 0) ? SET_Z_FLAG : CLEAR_Z_FLAG;
    SET_N_FLAG;
    ((gb->cpu.r8[U3DST] & 0xf) == 0xf) ? SET_H_FLAG : CLEAR_H_FLAG;
}

// 0x35: 1 byte, 3 cycles
void dec_hl(struct gameboy *gb) {
    if (gb->cpu.step == 0) {
        gb->cpu.step = 1;
        gb->cpu.pc++;
    } else if (gb->cpu.step == 1) {
        gb->cpu.step = 2;
        gb->cpu.lo = read_u8(gb, R16HL);
        gb->cpu.lo--;
    } else if (gb->cpu.step == 2) {
        gb->cpu.step = 0;
        (gb->cpu.lo == 0) ? SET_Z_FLAG : CLEAR_Z_FLAG;
        SET_N_FLAG;
        ((gb->cpu.lo & 0xf) == 0xf) ? SET_H_FLAG : CLEAR_H_FLAG;
        write_u8(gb, R16HL, gb->cpu.lo);
    }
}

#define _ADD \
    (((gb->cpu.r8[7] & 15) + (gb->cpu.lo & 15)) > 15) ? SET_H_FLAG : CLEAR_H_FLAG;\
    ((gb->cpu.r8[7] + gb->cpu.lo) > 255) ? SET_C_FLAG : CLEAR_C_FLAG;\
    gb->cpu.r8[7] += gb->cpu.lo;\
    (gb->cpu.r8[7] == 0) ? SET_Z_FLAG : CLEAR_Z_FLAG;\
    CLEAR_N_FLAG;

#define _ADC \
    gb->cpu.u16 = gb->cpu.r8[7] + gb->cpu.lo + IS_C_FLAG;\
    (((gb->cpu.r8[7] & 15) + (gb->cpu.lo & 15) + IS_C_FLAG) > 15) ? SET_H_FLAG : CLEAR_H_FLAG;\
    (gb->cpu.u16 > 255) ? SET_C_FLAG : CLEAR_C_FLAG;\
    gb->cpu.r8[7] = gb->cpu.u16 & 255;\
    (gb->cpu.r8[7] == 0) ? SET_Z_FLAG : CLEAR_Z_FLAG;\
    CLEAR_N_FLAG;

#define _SUB \
    ((gb->cpu.r8[7] & 15) < (gb->cpu.lo & 15)) ? SET_H_FLAG : CLEAR_H_FLAG;\
    (gb->cpu.r8[7] < gb->cpu.lo) ? SET_C_FLAG : CLEAR_C_FLAG;\
    gb->cpu.r8[7] -= gb->cpu.lo;\
    (gb->cpu.r8[7] == 0) ? SET_Z_FLAG : CLEAR_Z_FLAG;\
    SET_N_FLAG;

#define _SBC \
    gb->cpu.i16 = gb->cpu.r8[7] - gb->cpu.lo - IS_C_FLAG;\
    (((gb->cpu.r8[7] & 15) - (gb->cpu.lo & 15) - IS_C_FLAG) < 0) ? SET_H_FLAG : CLEAR_H_FLAG;\
    (gb->cpu.i16 < 0) ? SET_C_FLAG : CLEAR_C_FLAG;\
    gb->cpu.r8[7] = gb->cpu.i16 & 255;\
    (gb->cpu.r8[7] == 0) ? SET_Z_FLAG : CLEAR_Z_FLAG;\
    SET_N_FLAG;

#define _AND \
    gb->cpu.r8[7] &= gb->cpu.lo;\
    (gb->cpu.r8[7] == 0) ? SET_Z_FLAG : CLEAR_Z_FLAG;\
    CLEAR_N_FLAG;\
    SET_H_FLAG;\
    CLEAR_C_FLAG;

#define _XOR \
    gb->cpu.r8[7] ^= gb->cpu.lo;\
    (gb->cpu.r8[7] == 0) ? SET_Z_FLAG : CLEAR_Z_FLAG;\
    CLEAR_N_FLAG;\
    CLEAR_H_FLAG;\
    CLEAR_C_FLAG;

#define _OR \
    gb->cpu.r8[7] |= gb->cpu.lo;\
    (gb->cpu.r8[7] == 0) ? SET_Z_FLAG : CLEAR_Z_FLAG;\
    CLEAR_N_FLAG;\
    CLEAR_H_FLAG;\
    CLEAR_C_FLAG;

#define _CP \
    (gb->cpu.r8[7] == gb->cpu.lo) ? SET_Z_FLAG : CLEAR_Z_FLAG;\
    SET_N_FLAG;\
    ((gb->cpu.r8[7] & 15) < (gb->cpu.lo & 15)) ? SET_H_FLAG : CLEAR_H_FLAG;\
    (gb->cpu.r8[7] < gb->cpu.lo) ? SET_C_FLAG : CLEAR_C_FLAG;


#define ARITHMETIC(FUNC_R,FUNC_HL,FUNC_N,MACRO) \
                                                \
void FUNC_R(struct gameboy *gb)  {              \
    gb->cpu.pc++;                               \
    gb->cpu.lo = gb->cpu.r8[U3SRC];             \
    MACRO;                                      \
}                                               \
                                                \
void FUNC_HL(struct gameboy *gb) {              \
    if (gb->cpu.step == 0) {                    \
        gb->cpu.step = 1;                       \
        gb->cpu.pc++;                           \
    } else if (gb->cpu.step == 1) {             \
        gb->cpu.step = 0;                       \
        gb->cpu.lo = read_u8(gb, R16HL);        \
        MACRO;                                  \
    }                                           \
}                                               \
                                                \
void FUNC_N(struct gameboy *gb)  {              \
    if (gb->cpu.step == 0) {                    \
        gb->cpu.step = 1;                       \
        gb->cpu.pc++;                           \
    } else if (gb->cpu.step == 1) {             \
        gb->cpu.step = 0;                       \
        gb->cpu.lo = read_u8(gb, gb->cpu.pc);   \
        gb->cpu.pc++;                           \
        MACRO;                                  \
    }                                           \
}

ARITHMETIC(add_r, add_hl, add_n, _ADD);
ARITHMETIC(adc_r, adc_hl, adc_n, _ADC);
ARITHMETIC(sub_r, sub_hl, sub_n, _SUB);
ARITHMETIC(sbc_r, sbc_hl, sbc_n, _SBC);
ARITHMETIC(and_r, and_hl, and_n, _AND);
ARITHMETIC(xor_r, xor_hl, xor_n, _XOR);
ARITHMETIC(or_r,  or_hl,  or_n, _OR);
ARITHMETIC(cp_r,  cp_hl,  cp_n, _CP);


/*
** 16-bit arithmetic instructions
*/

// 0x03, 0x13, 0x23, 0x33: 1 byte, 2 cycles
void inc_rr(struct gameboy *gb) {
    if (gb->cpu.step == 0) {
        gb->cpu.step = 1;
        gb->cpu.pc++;
    } else if (gb->cpu.step == 1) {
        gb->cpu.step = 0;

        if (U2IDX == 3) {
            gb->cpu.sp++;
        } else {
            gb->cpu.u16 = (gb->cpu.r8[U2IDX * 2] << 8) + gb->cpu.r8[U2IDX * 2 + 1];
            gb->cpu.u16++;
            gb->cpu.r8[U2IDX * 2] = gb->cpu.u16 >> 8;
            gb->cpu.r8[U2IDX * 2 + 1] = gb->cpu.u16 & 255;
        }
    }
}

// 0x0b, 0x1b, 0x2b, 0x3b: 1 byte, 2 cycles
void dec_rr(struct gameboy *gb) {
    if (gb->cpu.step == 0) {
        gb->cpu.step = 1;
        gb->cpu.pc++;
    } else if (gb->cpu.step == 1) {
        gb->cpu.step = 0;

        if (U2IDX == 3) {
            gb->cpu.sp--;
        } else {
            gb->cpu.u16 = (gb->cpu.r8[U2IDX * 2] << 8) + gb->cpu.r8[U2IDX * 2 + 1];
            gb->cpu.u16--;
            gb->cpu.r8[U2IDX * 2] = gb->cpu.u16 >> 8;
            gb->cpu.r8[U2IDX * 2 + 1] = gb->cpu.u16 & 255;
        }
    }
}

// 0x09, 0x19, 0x29, 0x39 - 1 byte, 2 cycles
void add_hl_rr(struct gameboy *gb) {
    if (gb->cpu.step == 0) {
        gb->cpu.step = 1;
        gb->cpu.pc++;
    } else if (gb->cpu.step == 1) {
        gb->cpu.step = 0;

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
}

// 0xe8, 2 bytes, 4 cycles
void add_sp_e(struct gameboy *gb) {
    if (gb->cpu.step == 0) {
        gb->cpu.step = 1;
        gb->cpu.pc++;
    } else if (gb->cpu.step == 1) {
        gb->cpu.step = 2;
        gb->cpu.i16 = (int8_t)read_u8(gb, gb->cpu.pc); //signed XXX
        gb->cpu.pc++;
    } else if (gb->cpu.step == 2) {
        gb->cpu.step = 3;
        CLEAR_Z_FLAG;
        CLEAR_N_FLAG;
        (gb->cpu.sp & 0xf) + (gb->cpu.i16 & 0xf) > 0xf ? SET_H_FLAG : CLEAR_H_FLAG;
        (gb->cpu.sp & 0xff) + (gb->cpu.i16 & 0xff) > 0xff ? SET_C_FLAG : CLEAR_C_FLAG;
        gb->cpu.sp += gb->cpu.i16;
    } else if (gb->cpu.step == 2) {
        gb->cpu.step = 0;
    }
}

/*
** rotate, shift, and bit operation instructions
*/

#define _RLC \
    gb->cpu.lo = (gb->cpu.lo << 1) | ((gb->cpu.lo & 0x80) >> 7);\
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
#define CBR8(FUNC,MACRO)                    \
void FUNC(struct gameboy *gb)   {           \
    gb->cpu.pc++;                           \
    gb->cpu.lo = gb->cpu.r8[U3SRC];         \
    MACRO;                                  \
    gb->cpu.r8[U3SRC] = gb->cpu.lo;         \
}

CBR8(rlc_r,_RLC);
CBR8(rrc_r,_RRC);
CBR8(rl_r,_RL);
CBR8(rr_r,_RR);
CBR8(sla_r,_SLA);
CBR8(sra_r,_SRA);
CBR8(swap_r,_SWAP);
CBR8(srl_r,_SRL);
CBR8(bit_r,_BIT);
CBR8(res_r,_RES);
CBR8(set_r,_SET);

// CB-prefix + 3 cycles, except `bit' => 2 cycles
#define CBHL(FUNC,MACRO)                    \
void FUNC(struct gameboy *gb)  {            \
    if (gb->cpu.step == 0) {                \
        gb->cpu.step = 1;                   \
        gb->cpu.pc++;                       \
    } else if (gb->cpu.step == 1) {         \
        gb->cpu.step = 2;                   \
        gb->cpu.lo = read_u8(gb, R16HL);    \
    } else if (gb->cpu.step == 2) {         \
        gb->cpu.step = 0;                   \
        MACRO;                              \
        write_u8(gb, R16HL, gb->cpu.lo);    \
    }                                       \
}

CBHL(rlc_hl,_RLC);
CBHL(rrc_hl,_RRC);
CBHL(rl_hl,_RL);
CBHL(rr_hl,_RR);
CBHL(sla_hl,_SLA);
CBHL(sra_hl,_SRA);
CBHL(swap_hl,_SWAP);
CBHL(srl_hl,_SRL);
CBHL(res_hl,_RES);
CBHL(set_hl,_SET);

// CB cycle + 2 cycles
void bit_hl(struct gameboy *gb)  {
    if (gb->cpu.step == 0) {
        gb->cpu.step = 1;
        gb->cpu.pc++;
    } else if (gb->cpu.step == 1) {
        gb->cpu.step = 0;
        gb->cpu.lo = read_u8(gb, R16HL);
        _BIT;
        write_u8(gb, R16HL, gb->cpu.lo);
    }
}

void rlca(struct gameboy *gb)    {
    rlc_r(gb);
    CLEAR_Z_FLAG;
};

void rrca(struct gameboy *gb)    {
    rrc_r(gb);
    CLEAR_Z_FLAG;
};

void rla(struct gameboy *gb)     {
    rl_r(gb);
    CLEAR_Z_FLAG;
};

void rra(struct gameboy *gb)     {
    rr_r(gb);
    CLEAR_Z_FLAG;
};

/*
** control flow instructions
*/

// 0xc3, 3 bytes, 4 cycles
void jp_a16(struct gameboy *gb) {
    if (gb->cpu.step == 0) {
        gb->cpu.step = 1;
        gb->cpu.pc++;
    } else if (gb->cpu.step == 1) {
        gb->cpu.step = 2;
        gb->cpu.lo = read_u8(gb, gb->cpu.pc);
        gb->cpu.pc++;
    } else if (gb->cpu.step == 2) {
        gb->cpu.step = 3;
        gb->cpu.hi = read_u8(gb, gb->cpu.pc);
        gb->cpu.pc++;
    } else if (gb->cpu.step == 3) {
        gb->cpu.step = 0;
        gb->cpu.pc = A16;
    }
}

// 0xe9, 1 byte, 1 cycle
void jp_hl(struct gameboy *gb) {
    gb->cpu.pc++;
    gb->cpu.pc = R16HL;
}

// 0b110cc010: 0xc2 (NZ), 0xca (Z), 0xd2 (NC), 0xda (C)
// 3 bytes, 3 cycles (cc false) - or - 4 cycles (cc true)
void jp_cc_a16(struct gameboy *gb) {
    if (gb->cpu.step == 0) {
        gb->cpu.step = 1;
        gb->cpu.pc++;
    } else if (gb->cpu.step == 1) {
        gb->cpu.step = 2;
        gb->cpu.lo = read_u8(gb, gb->cpu.pc);
        gb->cpu.pc++;
    } else if (gb->cpu.step == 2) {
        gb->cpu.step = (CONDITION) ? 3 : 0;
        gb->cpu.hi = read_u8(gb, gb->cpu.pc);
        gb->cpu.pc++;
    } else if (gb->cpu.step == 3) {
        gb->cpu.step = 0;
        gb->cpu.pc = A16;
    }
}

// 0x18, 2 bytes, 3 cycles
void jr_e(struct gameboy *gb) {
    if (gb->cpu.step == 0) {
        gb->cpu.step = 1;
        gb->cpu.pc++;
    } else if (gb->cpu.step == 1) {
        gb->cpu.step = 2;
        gb->cpu.i16 = (int8_t)read_u8(gb, gb->cpu.pc); //signed XXX
        gb->cpu.pc++;
    } else if (gb->cpu.step == 2) {
        gb->cpu.step = 0;
        gb->cpu.pc += gb->cpu.i16;
    }
}

// 0b001cc000: 0x20 (NZ), 0x28 (Z), 0x30 (NC), 0x38 (C)
// 2 bytes, 2 cycles (cc false) - or - 3 cycles (cc true)
void jr_cc_e(struct gameboy *gb) {
    if (gb->cpu.step == 0) {
        gb->cpu.step = 1;
        gb->cpu.pc++;
    } else if (gb->cpu.step == 1) {
        gb->cpu.step = (CONDITION) ? 2 : 0;
        gb->cpu.i16 = (int8_t)read_u8(gb, gb->cpu.pc); //signed XXX
        gb->cpu.pc++;
    } else if (gb->cpu.step == 2) {
        gb->cpu.step = 0;
        gb->cpu.pc += gb->cpu.i16;
    }
}

// 0xcd, 3 bytes, 6 cycles
void call_a16(struct gameboy *gb) {
    if (gb->cpu.step == 0) {
        gb->cpu.step = 1;
        gb->cpu.pc++;
    } else if (gb->cpu.step == 1) {
        gb->cpu.step = 2;
        gb->cpu.lo = read_u8(gb, gb->cpu.pc);
        gb->cpu.pc++;
    } else if (gb->cpu.step == 2) {
        gb->cpu.step = 3;
        gb->cpu.hi = read_u8(gb, gb->cpu.pc);
        gb->cpu.pc++;
    } else if (gb->cpu.step == 3) {
        gb->cpu.step = 4;
    } else if (gb->cpu.step == 4) {
        gb->cpu.step = 5;
        gb->cpu.sp--;
        write_u8(gb, gb->cpu.sp, gb->cpu.pc >> 8);
    } else if (gb->cpu.step == 5) {
        gb->cpu.step = 0;
        gb->cpu.sp--;
        write_u8(gb, gb->cpu.sp, gb->cpu.pc & 255);
        gb->cpu.pc = A16;
    }
}

// 0b110cc100: 0xc4 (NZ) 0xcc (Z), 0xd4 (NC), 0xdc (C)
// 3 bytes, 3 cycles (cc false) - or - 6 cycles (cc true)
void call_cc_a16(struct gameboy *gb) {
    if (gb->cpu.step == 0) {
        gb->cpu.step = 1;
        gb->cpu.pc++;
    } else if (gb->cpu.step == 1) {
        gb->cpu.step = 2;
        gb->cpu.lo = read_u8(gb, gb->cpu.pc);
        gb->cpu.pc++;
    } else if (gb->cpu.step == 2) {
        gb->cpu.step = (CONDITION) ? 3 : 0;
        gb->cpu.hi = read_u8(gb, gb->cpu.pc);
        gb->cpu.pc++;
    } else if (gb->cpu.step == 3) {
        gb->cpu.step = 4;
    } else if (gb->cpu.step == 4) {
        gb->cpu.step = 5;
        gb->cpu.sp--;
        write_u8(gb, gb->cpu.sp, gb->cpu.pc >> 8);
    } else if (gb->cpu.step == 5) {
        gb->cpu.step = 0;
        gb->cpu.sp--;
        write_u8(gb, gb->cpu.sp, gb->cpu.pc & 255);
        gb->cpu.pc = A16;
    }
}

// 0xc9, 1 byte, 4 cycles
void ret(struct gameboy *gb) {
    if (gb->cpu.step == 0) {
        gb->cpu.step = 1;
        gb->cpu.pc++;
    } else if (gb->cpu.step == 1) {
        gb->cpu.step = 2;
        gb->cpu.lo = read_u8(gb, gb->cpu.sp);
        gb->cpu.sp++;
    } else if (gb->cpu.step == 2) {
        gb->cpu.step = 3;
        gb->cpu.hi = read_u8(gb, gb->cpu.sp);
        gb->cpu.sp++;
    } else if (gb->cpu.step == 3) {
        gb->cpu.step = 0;
        gb->cpu.pc = A16;
    }
}

// 0b110cc000: 0xc0 (NZ), 0xc8 (Z), 0xd0 (NC), 0xd8 (C)
// 1 byte, 2 cycles (cc false) - or - 5 cycles (cc true)
void ret_cc(struct gameboy *gb) {
    if (gb->cpu.step == 0) {
        gb->cpu.step = 1;
        gb->cpu.pc++;
    } else if (gb->cpu.step == 1) {
        gb->cpu.step = (CONDITION) ? 2 : 0;
    } else if (gb->cpu.step == 2) {
        gb->cpu.step = 3;
        gb->cpu.lo = read_u8(gb, gb->cpu.sp);
        gb->cpu.sp++;
    } else if (gb->cpu.step == 3) {
        gb->cpu.step = 4;
        gb->cpu.hi = read_u8(gb, gb->cpu.sp);
        gb->cpu.sp++;
    } else if (gb->cpu.step == 4) {
        gb->cpu.step = 0;
        gb->cpu.pc = A16;
    }
}

// 0xd9, 1 byte, 4 cycles
void reti(struct gameboy *gb) {
    if (gb->cpu.step == 0) {
        gb->cpu.step = 1;
        gb->cpu.pc++;
    } else if (gb->cpu.step == 1) {
        gb->cpu.step = 2;
        gb->cpu.lo = read_u8(gb, gb->cpu.sp);
        gb->cpu.sp++;
    } else if (gb->cpu.step == 2) {
        gb->cpu.step = 3;
        gb->cpu.hi = read_u8(gb, gb->cpu.sp);
        gb->cpu.sp++;
    } else if (gb->cpu.step == 3) {
        gb->cpu.step = 0;
        gb->cpu.pc = A16;
        gb->cpu.ime = 1;
    }
}

// 0b11xxx111: c7,cf,d7,df,e7,ef,f7,ff
// 1 byte, 4 cycles;
void rst(struct gameboy *gb) {
    if (gb->cpu.step == 0) {
        gb->cpu.step = 1;
        gb->cpu.pc++;
    } else if (gb->cpu.step == 1) {
        gb->cpu.step = 2;
    } else if (gb->cpu.step == 2) {
        gb->cpu.step = 3;
        gb->cpu.sp--;
        write_u8(gb, gb->cpu.sp, gb->cpu.pc >> 8);
    } else if (gb->cpu.step == 3) {
        gb->cpu.step = 0;
        gb->cpu.sp--;
        write_u8(gb, gb->cpu.sp, gb->cpu.pc & 255);
        gb->cpu.pc = gb->cpu.opcode & 0b00111000;
    }
}

/*
** miscellaneous instructions
*/

// 0x76 XXX 1 byte, 1 cycle
void halt(struct gameboy *gb) {
    gb->cpu.pc++;
    gb->cpu.state = HALTED;
}

// 0x10 XXX
void stop(struct gameboy *gb) {
    gb->cpu.pc++;
    gb->cpu.state = STOPPED;
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
    nop,      ld_rr_d16, ld_bc_a,   inc_rr,  inc_r,       dec_r,   ld_r_d8,  rlca,    ld_a16_sp,  add_hl_rr, ld_a_bc,   dec_rr, inc_r,       dec_r,    ld_r_d8, rrca,
    stop,     ld_rr_d16, ld_de_a,   inc_rr,  inc_r,       dec_r,   ld_r_d8,  rla,     jr_e,       add_hl_rr, ld_a_de,   dec_rr, inc_r,       dec_r,    ld_r_d8, rra,
    jr_cc_e,  ld_rr_d16, ld_hli_a,  inc_rr,  inc_r,       dec_r,   ld_r_d8,  daa,     jr_cc_e,    add_hl_rr, ld_a_hli,  dec_rr, inc_r,       dec_r,    ld_r_d8, cpl,
    jr_cc_e,  ld_rr_d16, ld_hld_a,  inc_rr,  inc_hl,      dec_hl,  ld_hl_d8, scf,     jr_cc_e,    add_hl_rr, ld_a_hld,  dec_rr, inc_r,       dec_r,    ld_r_d8, ccf,
    ld_r_r,   ld_r_r,    ld_r_r,    ld_r_r,  ld_r_r,      ld_r_r,  ld_r_hl,  ld_r_r,  ld_r_r,     ld_r_r,    ld_r_r,    ld_r_r, ld_r_r,      ld_r_r,   ld_r_hl, ld_r_r,
    ld_r_r,   ld_r_r,    ld_r_r,    ld_r_r,  ld_r_r,      ld_r_r,  ld_r_hl,  ld_r_r,  ld_r_r,     ld_r_r,    ld_r_r,    ld_r_r, ld_r_r,      ld_r_r,   ld_r_hl, ld_r_r,
    ld_r_r,   ld_r_r,    ld_r_r,    ld_r_r,  ld_r_r,      ld_r_r,  ld_r_hl,  ld_r_r,  ld_r_r,     ld_r_r,    ld_r_r,    ld_r_r, ld_r_r,      ld_r_r,   ld_r_hl, ld_r_r,
    ld_hl_r,  ld_hl_r,   ld_hl_r,   ld_hl_r, ld_hl_r,     ld_hl_r, halt,     ld_hl_r, ld_r_r,     ld_r_r,    ld_r_r,    ld_r_r, ld_r_r,      ld_r_r,   ld_r_hl, ld_r_r,
    add_r,    add_r,     add_r,     add_r,   add_r,       add_r,   add_hl,   add_r,   adc_r,      adc_r,     adc_r,     adc_r,  adc_r,       adc_r,    adc_hl,  adc_r,
    sub_r,    sub_r,     sub_r,     sub_r,   sub_r,       sub_r,   sub_hl,   sub_r,   sbc_r,      sbc_r,     sbc_r,     sbc_r,  sbc_r,       sbc_r,    sbc_hl,  sbc_r,
    and_r,    and_r,     and_r,     and_r,   and_r,       and_r,   and_hl,   and_r,   xor_r,      xor_r,     xor_r,     xor_r,  xor_r,       xor_r,    xor_hl,  xor_r,
    or_r,     or_r,      or_r,      or_r,    or_r,        or_r,    or_hl,    or_r,    cp_r,       cp_r,      cp_r,      cp_r,   cp_r,        cp_r,     cp_hl,   cp_r,
    ret_cc,   pop_rr,    jp_cc_a16, jp_a16,  call_cc_a16, push_rr, add_n,    rst,     ret_cc,     ret,       jp_cc_a16, 0,      call_cc_a16, call_a16, adc_n,   rst,
    ret_cc,   pop_rr,    jp_cc_a16, 0,       call_cc_a16, push_rr, sub_n,    rst,     ret_cc,     reti,      jp_cc_a16, 0,      call_cc_a16, 0,        sbc_n,   rst,
    ldh_a8_a, pop_rr,    ldh_c_a,   0,       0,           push_rr, and_n,    rst,     add_sp_e,   jp_hl,     ld_a16_a,  0,      0,           0,        xor_n,   rst,
    ldh_a_a8, pop_rr,    ldh_a_c,   di,      0,           push_rr, or_n,     rst,     ld_hl_sp_e, ld_sp_hl,  ld_a_a16,  ei,     0,           0,        cp_n,    rst,

    rlc_r,    rlc_r,     rlc_r,     rlc_r,   rlc_r,       rlc_r,   rlc_hl,   rlc_r,   rrc_r,      rrc_r,     rrc_r,     rrc_r,  rrc_r,       rrc_r,    rrc_hl,  rrc_r,
    rl_r,     rl_r,      rl_r,      rl_r,    rl_r,        rl_r,    rl_hl,    rl_r,    rr_r,       rr_r,      rr_r,      rr_r,   rr_r,        rr_r,     rr_hl,   rr_r,
    sla_r,    sla_r,     sla_r,     sla_r,   sla_r,       sla_r,   sla_hl,   sla_r,   sra_r,      sra_r,     sra_r,     sra_r,  sra_r,       sra_r,    sra_hl,  sra_r,
    swap_r,   swap_r,    swap_r,    swap_r,  swap_r,      swap_r,  swap_hl,  swap_r,  srl_r,      srl_r,     srl_r,     srl_r,  srl_r,       srl_r,    srl_hl,  srl_r,
    bit_r,    bit_r,     bit_r,     bit_r,   bit_r,       bit_r,   bit_hl,   bit_r,   bit_r,      bit_r,     bit_r,     bit_r,  bit_r,       bit_r,    bit_hl,  bit_r,
    bit_r,    bit_r,     bit_r,     bit_r,   bit_r,       bit_r,   bit_hl,   bit_r,   bit_r,      bit_r,     bit_r,     bit_r,  bit_r,       bit_r,    bit_hl,  bit_r,
    bit_r,    bit_r,     bit_r,     bit_r,   bit_r,       bit_r,   bit_hl,   bit_r,   bit_r,      bit_r,     bit_r,     bit_r,  bit_r,       bit_r,    bit_hl,  bit_r,
    bit_r,    bit_r,     bit_r,     bit_r,   bit_r,       bit_r,   bit_hl,   bit_r,   bit_r,      bit_r,     bit_r,     bit_r,  bit_r,       bit_r,    bit_hl,  bit_r,
    res_r,    res_r,     res_r,     res_r,   res_r,       res_r,   res_hl,   res_r,   res_r,      res_r,     res_r,     res_r,  res_r,       res_r,    res_hl,  res_r,
    res_r,    res_r,     res_r,     res_r,   res_r,       res_r,   res_hl,   res_r,   res_r,      res_r,     res_r,     res_r,  res_r,       res_r,    res_hl,  res_r,
    res_r,    res_r,     res_r,     res_r,   res_r,       res_r,   res_hl,   res_r,   res_r,      res_r,     res_r,     res_r,  res_r,       res_r,    res_hl,  res_r,
    res_r,    res_r,     res_r,     res_r,   res_r,       res_r,   res_hl,   res_r,   res_r,      res_r,     res_r,     res_r,  res_r,       res_r,    res_hl,  res_r,
    set_r,    set_r,     set_r,     set_r,   set_r,       set_r,   set_hl,   set_r,   set_r,      set_r,     set_r,     set_r,  set_r,       set_r,    set_hl,  set_r,
    set_r,    set_r,     set_r,     set_r,   set_r,       set_r,   set_hl,   set_r,   set_r,      set_r,     set_r,     set_r,  set_r,       set_r,    set_hl,  set_r,
    set_r,    set_r,     set_r,     set_r,   set_r,       set_r,   set_hl,   set_r,   set_r,      set_r,     set_r,     set_r,  set_r,       set_r,    set_hl,  set_r,
    set_r,    set_r,     set_r,     set_r,   set_r,       set_r,   set_hl,   set_r,   set_r,      set_r,     set_r,     set_r,  set_r,       set_r,    set_hl,  set_r,
};

char *op_names0[] = {
    "nop", "ld bc,$%04X", "ld (bc),a", "inc bc", "inc b", "dec b", "ld b,$%02X", "rlca",
    "ld ($%04X),sp", "add hl,bc", "ld a,(bc)", "dec bc", "inc c", "dec c", "ld c,$%02X", "rrca",
    "stop 0", "ld de,$%04X", "ld (de),a", "inc de", "inc d", "dec d", "ld d,$%02X", "rla",
    "jr $%02X", "add hl,de", "ld a,(de)", "dec de", "inc e", "dec e", "ld e,$%02X", "rra",
    "jr nz,$%02X", "ld hl,$%04X", "ld (hl+),a", "inc hl", "inc h", "dec h", "ld h,$%02X", "daa",
    "jr z,$%02X", "add hl,hl", "ld a,(hl+)", "dec hl", "inc l", "dec l", "ld l,$%02X", "cpl",
    "jr nc,$%02X", "ld sp,$%04X", "ld (hl-),a", "inc sp", "inc (hl)", "dec (hl)", "ld (hl),$%02X", "scf",
    "jr c,$%02X", "add hl,sp", "ld a,(hl-)", "dec sp", "inc a", "dec a", "ld a,$%02X", "ccf",
    "ld b,b", "ld b,c", "ld b,d", "ld b,e", "ld b,h", "ld b,l", "ld b,(hl)", "ld b,a",
    "ld c,b", "ld c,c", "ld c,d", "ld c,e", "ld c,h", "ld c,l", "ld c,(hl)", "ld c,a",
    "ld d,b", "ld d,c", "ld d,d", "ld d,e", "ld d,h", "ld d,l", "ld d,(hl)", "ld d,a",
    "ld e,b", "ld e,c", "ld e,d", "ld e,e", "ld e,h", "ld e,l", "ld e,(hl)", "ld e,a",
    "ld h,b", "ld h,c", "ld h,d", "ld h,e", "ld h,h", "ld h,l", "ld h,(hl)", "ld h,a",
    "ld l,b", "ld l,c", "ld l,d", "ld l,e", "ld l,h", "ld l,l", "ld l,(hl)", "ld l,a",
    "ld (hl),b", "ld (hl),c", "ld (hl),d", "ld (hl),e", "ld (hl),h", "ld (hl),l", "halt", "ld (hl),a",
    "ld a,b", "ld a,c", "ld a,d", "ld a,e", "ld a,h", "ld a,l", "ld a,(hl)", "ld a,a",
    "add a,b", "add a,c", "add a,d", "add a,e", "add a,h", "add a,l", "add a,(hl)", "add a,a",
    "adc a,b", "adc a,c", "adc a,d", "adc a,e", "adc a,h", "adc a,l", "adc a,(hl)", "adc a,a",
    "sub b", "sub c", "sub d", "sub e", "sub h", "sub l", "sub (hl)", "sub a",
    "sbc a,b", "sbc a,c", "sbc a,d", "sbc a,e", "sbc a,h", "sbc a,l", "sbc a,(hl)", "sbc a,a",
    "and b", "and c", "and d", "and e", "and h", "and l", "and (hl)", "and a",
    "xor b", "xor c", "xor d", "xor e", "xor h", "xor l", "xor (hl)", "xor a",
    "or b", "or c", "or d", "or e", "or h", "or l", "or (hl)", "or a",
    "cp b", "cp c", "cp d", "cp e", "cp h", "cp l", "cp (hl)", "cp a",
    "ret nz", "pop bc", "jp nz,$%04X", "jp $%04X", "call nz,$%04X", "push bc", "add a,$%02X", "rst 00h",
    "ret z", "ret", "jp z,$%04X", "prefix cb", "call z,$%04X", "call $%04X", "adc a,$%02X", "rst 08h",
    "ret nc", "pop de", "jp nc,$%04X", "undef", "call nc,$%04X", "push de", "sub $%02X", "rst 10h",
    "ret c", "reti", "jp c,$%04X", "undef", "call c,$%04X", "undef", "sbc a,$%02X", "rst 18h",
    "ldh ($FF%02X),a", "pop hl", "ld (c),a", "undef", "undef", "push hl", "and $%02X", "rst 20h",
    "add sp,$%02X", "jp (hl)", "ld ($%04X),a", "undef", "undef", "undef", "xor $%02X", "rst 28h",
    "ldh a,($FF%02X)", "pop af", "ld a,(c)", "di", "undef", "push af", "or $%02X", "rst 30h",
    "ld hl,sp+$%02X", "ld sp,hl", "ld a,($%04X)", "ei", "undef", "undef", "cp $%02X", "rst 38h"
};

char *op_names1[] = {
    "rlc b", "rlc c", "rlc d", "rlc e", "rlc h", "rlc l", "rlc (hl)", "rlc a",
    "rrc b", "rrc c", "rrc d", "rrc e", "rrc h", "rrc l", "rrc (hl)", "rrc a",
    "rl b", "rl c", "rl d", "rl e", "rl h", "rl l", "rl (hl)", "rl a",
    "rr b", "rr c", "rr d", "rr e", "rr h", "rr l", "rr (hl)", "rr a",
    "sla b", "sla c", "sla d", "sla e", "sla h", "sla l", "sla (hl)", "sla a",
    "sra b", "sra c", "sra d", "sra e", "sra h", "sra l", "sra (hl)", "sra a",
    "swap b", "swap c", "swap d", "swap e", "swap h", "swap l", "swap (hl)", "swap a",
    "srl b", "srl c", "srl d", "srl e", "srl h", "srl l", "srl (hl)", "srl a",
    "bit 0,b", "bit 0,c", "bit 0,d", "bit 0,e", "bit 0,h", "bit 0,l", "bit 0,(hl)", "bit 0,a",
    "bit 1,b", "bit 1,c", "bit 1,d", "bit 1,e", "bit 1,h", "bit 1,l", "bit 1,(hl)", "bit 1,a",
    "bit 2,b", "bit 2,c", "bit 2,d", "bit 2,e", "bit 2,h", "bit 2,l", "bit 2,(hl)", "bit 2,a",
    "bit 3,b", "bit 3,c", "bit 3,d", "bit 3,e", "bit 3,h", "bit 3,l", "bit 3,(hl)", "bit 3,a",
    "bit 4,b", "bit 4,c", "bit 4,d", "bit 4,e", "bit 4,h", "bit 4,l", "bit 4,(hl)", "bit 4,a",
    "bit 5,b", "bit 5,c", "bit 5,d", "bit 5,e", "bit 5,h", "bit 5,l", "bit 5,(hl)", "bit 5,a",
    "bit 6,b", "bit 6,c", "bit 6,d", "bit 6,e", "bit 6,h", "bit 6,l", "bit 6,(hl)", "bit 6,a",
    "bit 7,b", "bit 7,c", "bit 7,d", "bit 7,e", "bit 7,h", "bit 7,l", "bit 7,(hl)", "bit 7,a",
    "res 0,b", "res 0,c", "res 0,d", "res 0,e", "res 0,h", "res 0,l", "res 0,(hl)", "res 0,a",
    "res 1,b", "res 1,c", "res 1,d", "res 1,e", "res 1,h", "res 1,l", "res 1,(hl)", "res 1,a",
    "res 2,b", "res 2,c", "res 2,d", "res 2,e", "res 2,h", "res 2,l", "res 2,(hl)", "res 2,a",
    "res 3,b", "res 3,c", "res 3,d", "res 3,e", "res 3,h", "res 3,l", "res 3,(hl)", "res 3,a",
    "res 4,b", "res 4,c", "res 4,d", "res 4,e", "res 4,h", "res 4,l", "res 4,(hl)", "res 4,a",
    "res 5,b", "res 5,c", "res 5,d", "res 5,e", "res 5,h", "res 5,l", "res 5,(hl)", "res 5,a",
    "res 6,b", "res 6,c", "res 6,d", "res 6,e", "res 6,h", "res 6,l", "res 6,(hl)", "res 6,a",
    "res 7,b", "res 7,c", "res 7,d", "res 7,e", "res 7,h", "res 7,l", "res 7,(hl)", "res 7,a",
    "set 0,b", "set 0,c", "set 0,d", "set 0,e", "set 0,h", "set 0,l", "set 0,(hl)", "set 0,a",
    "set 1,b", "set 1,c", "set 1,d", "set 1,e", "set 1,h", "set 1,l", "set 1,(hl)", "set 1,a",
    "set 2,b", "set 2,c", "set 2,d", "set 2,e", "set 2,h", "set 2,l", "set 2,(hl)", "set 2,a",
    "set 3,b", "set 3,c", "set 3,d", "set 3,e", "set 3,h", "set 3,l", "set 3,(hl)", "set 3,a",
    "set 4,b", "set 4,c", "set 4,d", "set 4,e", "set 4,h", "set 4,l", "set 4,(hl)", "set 4,a",
    "set 5,b", "set 5,c", "set 5,d", "set 5,e", "set 5,h", "set 5,l", "set 5,(hl)", "set 5,a",
    "set 6,b", "set 6,c", "set 6,d", "set 6,e", "set 6,h", "set 6,l", "set 6,(hl)", "set 6,a",
    "set 7,b", "set 7,c", "set 7,d", "set 7,e", "set 7,h", "set 7,l", "set 7,(hl)", "set 7,a"
};

int byte_lens0[] = {
    1, 3, 1, 1, 1, 1, 2, 1, 3, 1, 1, 1, 1, 1, 2, 1,
    1, 3, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1,
    2, 3, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1,
    2, 3, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 3, 3, 3, 1, 2, 1, 1, 1, 3, 1, 3, 3, 2, 1,
    1, 1, 3, 0, 3, 1, 2, 1, 1, 1, 3, 0, 3, 0, 2, 1,
    2, 1, 1, 0, 0, 1, 2, 1, 2, 1, 3, 0, 0, 0, 2, 1,     /* changed E2 and F2 lengths to 1 each */
    2, 1, 1, 1, 0, 1, 2, 1, 2, 1, 3, 1, 0, 0, 2, 1      /**/
};

int byte_lens1[] = {
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
};

/*

 -    0 : no condition,          use either table
 Z    1 : if Z flag is set,      use cycle table 0,  else use cycle table 1
NZ    2 : if Z flag is NOT set,  use cycle table 0,  else use cycle table 1
 C    3 : if C flag is set,      use cycle table 0,  else use cycle table 1
NC    4 : if C flag is NOT set,  use cycle table 0,  else use cycle table 1
*/

int is_conditional_num_cycles[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
    4, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    2, 0, 2, 0, 2, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0,
    4, 0, 4, 0, 4, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

int cycles_table0[] = {
    4, 12, 8, 8, 4, 4, 8, 4, 20, 8, 8, 8, 4, 4, 8, 4,
    0, 12, 8, 8, 4, 4, 8, 4, 12, 8, 8, 8, 4, 4, 8, 4,
    12, 12, 8, 8, 4, 4, 8, 4, 12, 8, 8, 8, 4, 4, 8, 4,
    12, 12, 8, 8, 12, 12, 12, 4, 12, 8, 8, 8, 4, 4, 8, 4,
    4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4,
    4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4,
    4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4,
    8, 8, 8, 8, 8, 8, 0, 8, 4, 4, 4, 4, 4, 4, 8, 4,
    4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4,
    4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4,
    4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4,
    4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4,
    20, 12, 16, 16, 24, 16, 8, 16, 20, 16, 16, 0, 24, 24, 8, 16,
    20, 12, 16, 0, 24, 16, 8, 16, 20, 16, 16, 0, 24, 0, 8, 16,
    12, 12, 8, 0, 0, 16, 8, 16, 16, 4, 16, 0, 0, 0, 8, 16,
    12, 12, 8, 4, 0, 16, 8, 16, 12, 8, 16, 4, 0, 0, 8, 16,
    8, 8, 8, 8, 8, 8, 16, 8, 8, 8, 8, 8, 8, 8, 16, 8,
    8, 8, 8, 8, 8, 8, 16, 8, 8, 8, 8, 8, 8, 8, 16, 8,
    8, 8, 8, 8, 8, 8, 16, 8, 8, 8, 8, 8, 8, 8, 16, 8,
    8, 8, 8, 8, 8, 8, 16, 8, 8, 8, 8, 8, 8, 8, 16, 8,
    8, 8, 8, 8, 8, 8, 12, 8, 8, 8, 8, 8, 8, 8, 12, 8,
    8, 8, 8, 8, 8, 8, 12, 8, 8, 8, 8, 8, 8, 8, 12, 8,
    8, 8, 8, 8, 8, 8, 12, 8, 8, 8, 8, 8, 8, 8, 12, 8,
    8, 8, 8, 8, 8, 8, 12, 8, 8, 8, 8, 8, 8, 8, 12, 8,
    8, 8, 8, 8, 8, 8, 16, 8, 8, 8, 8, 8, 8, 8, 16, 8,
    8, 8, 8, 8, 8, 8, 16, 8, 8, 8, 8, 8, 8, 8, 16, 8,
    8, 8, 8, 8, 8, 8, 16, 8, 8, 8, 8, 8, 8, 8, 16, 8,
    8, 8, 8, 8, 8, 8, 16, 8, 8, 8, 8, 8, 8, 8, 16, 8,
    8, 8, 8, 8, 8, 8, 16, 8, 8, 8, 8, 8, 8, 8, 16, 8,
    8, 8, 8, 8, 8, 8, 16, 8, 8, 8, 8, 8, 8, 8, 16, 8,
    8, 8, 8, 8, 8, 8, 16, 8, 8, 8, 8, 8, 8, 8, 16, 8,
    8, 8, 8, 8, 8, 8, 16, 8, 8, 8, 8, 8, 8, 8, 16, 8
};

int cycles_table1[] = {
    4, 12, 8, 8, 4, 4, 8, 4, 20, 8, 8, 8, 4, 4, 8, 4,
    0, 12, 8, 8, 4, 4, 8, 4, 12, 8, 8, 8, 4, 4, 8, 4,
    8, 12, 8, 8, 4, 4, 8, 4, 8, 8, 8, 8, 4, 4, 8, 4,
    8, 12, 8, 8, 12, 12, 12, 4, 8, 8, 8, 8, 4, 4, 8, 4,
    4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4,
    4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4,
    4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4,
    8, 8, 8, 8, 8, 8, 0, 8, 4, 4, 4, 4, 4, 4, 8, 4,
    4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4,
    4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4,
    4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4,
    4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4,
    8, 12, 12, 16, 12, 16, 8, 16, 8, 16, 12, 0, 12, 24, 8, 16,
    8, 12, 12, 0, 12, 16, 8, 16, 8, 16, 12, 0, 12, 0, 8, 16,
    12, 12, 8, 0, 0, 16, 8, 16, 16, 4, 16, 0, 0, 0, 8, 16,
    12, 12, 8, 4, 0, 16, 8, 16, 12, 8, 16, 4, 0, 0, 8, 16,
    8, 8, 8, 8, 8, 8, 16, 8, 8, 8, 8, 8, 8, 8, 16, 8,
    8, 8, 8, 8, 8, 8, 16, 8, 8, 8, 8, 8, 8, 8, 16, 8,
    8, 8, 8, 8, 8, 8, 16, 8, 8, 8, 8, 8, 8, 8, 16, 8,
    8, 8, 8, 8, 8, 8, 16, 8, 8, 8, 8, 8, 8, 8, 16, 8,
    8, 8, 8, 8, 8, 8, 12, 8, 8, 8, 8, 8, 8, 8, 12, 8,
    8, 8, 8, 8, 8, 8, 12, 8, 8, 8, 8, 8, 8, 8, 12, 8,
    8, 8, 8, 8, 8, 8, 12, 8, 8, 8, 8, 8, 8, 8, 12, 8,
    8, 8, 8, 8, 8, 8, 12, 8, 8, 8, 8, 8, 8, 8, 12, 8,
    8, 8, 8, 8, 8, 8, 16, 8, 8, 8, 8, 8, 8, 8, 16, 8,
    8, 8, 8, 8, 8, 8, 16, 8, 8, 8, 8, 8, 8, 8, 16, 8,
    8, 8, 8, 8, 8, 8, 16, 8, 8, 8, 8, 8, 8, 8, 16, 8,
    8, 8, 8, 8, 8, 8, 16, 8, 8, 8, 8, 8, 8, 8, 16, 8,
    8, 8, 8, 8, 8, 8, 16, 8, 8, 8, 8, 8, 8, 8, 16, 8,
    8, 8, 8, 8, 8, 8, 16, 8, 8, 8, 8, 8, 8, 8, 16, 8,
    8, 8, 8, 8, 8, 8, 16, 8, 8, 8, 8, 8, 8, 8, 16, 8,
    8, 8, 8, 8, 8, 8, 16, 8, 8, 8, 8, 8, 8, 8, 16, 8
};

int get_num_cycles(struct gameboy *gb) {
    int idx = read_u8(gb, gb->cpu.pc);

    if (idx == 0xcb) {
        idx = 256 + read_u8(gb, gb->cpu.pc + 1);
    }

    switch (is_conditional_num_cycles[idx]) {
    case 1:
        return (IS_Z_FLAG) ? cycles_table0[idx] : cycles_table1[idx];

    case 2:
        return (!IS_Z_FLAG) ? cycles_table0[idx] : cycles_table1[idx];

    case 3:
        return (IS_C_FLAG) ? cycles_table0[idx] : cycles_table1[idx];

    case 4:
        return (!IS_C_FLAG) ? cycles_table0[idx] : cycles_table1[idx];
    }

    return cycles_table0[idx];
}

int instruction(struct gameboy *gb) {
    static void (*instr)(struct gameboy *gb) = NULL;

    if ((gb->cpu.state != HALTED) && (!instr)) {
        gb->cpu.instr_cycles += get_num_cycles(gb);
        gb->cpu.opcode = read_u8(gb, gb->cpu.pc);

        if (gb->cpu.opcode == 0xcb) {
            gb->cpu.pc++;
            gb->cpu.opcode = read_u8(gb, gb->cpu.pc);
            instr = instruct[256 + gb->cpu.opcode];
        } else {
            instr = instruct[gb->cpu.opcode];
        }

        if (gb->cpu.halt_bug) {
            gb->cpu.pc--;
            gb->cpu.halt_bug = 0;
        }
    }

    if (gb->cpu.instr_cycles) {
        gb->cpu.instr_cycles -= 4;
    }

    if (!gb->cpu.instr_cycles) {
        if ((gb->cpu.state != HALTED) && (instr)) {
            (void)debug(gb); /* XXX */
            (void)instr(gb);
            instr = NULL;

            if (gb->cpu.state == HALTED) {
                if ((gb->memory[rIF] & gb->memory[rIE] & 0x1f) != 0) {
                    gb->cpu.halt_bug = !gb->cpu.ime;
                }
            }
        }
    }

    return instr != NULL;
}
