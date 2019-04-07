#include "ops.h"
#include "gb.h"

#define OP_PROTO void *, t_state *, uint8_t *

void (*ops0[])(OP_PROTO) =
{
 op_00, op_01, op_02, op_03, op_04, op_05, op_06, op_07, op_08, op_09, op_0a, op_0b, op_0c, op_0d, op_0e, op_0f,
 op_10, op_11, op_12, op_13, op_14, op_15, op_16, op_17, op_18, op_19, op_1a, op_1b, op_1c, op_1d, op_1e, op_1f,
 op_20, op_21, op_22, op_23, op_24, op_25, op_26, op_27, op_28, op_29, op_2a, op_2b, op_2c, op_2d, op_2e, op_2f,
 op_30, op_31, op_32, op_33, op_34, op_35, op_36, op_37, op_38, op_39, op_3a, op_3b, op_3c, op_3d, op_3e, op_3f,
 op_40, op_41, op_42, op_43, op_44, op_45, op_46, op_47, op_48, op_49, op_4a, op_4b, op_4c, op_4d, op_4e, op_4f,
 op_50, op_51, op_52, op_53, op_54, op_55, op_56, op_57, op_58, op_59, op_5a, op_5b, op_5c, op_5d, op_5e, op_5f,
 op_60, op_61, op_62, op_63, op_64, op_65, op_66, op_67, op_68, op_69, op_6a, op_6b, op_6c, op_6d, op_6e, op_6f,
 op_70, op_71, op_72, op_73, op_74, op_75, op_76, op_77, op_78, op_79, op_7a, op_7b, op_7c, op_7d, op_7e, op_7f,
 op_80, op_81, op_82, op_83, op_84, op_85, op_86, op_87, op_88, op_89, op_8a, op_8b, op_8c, op_8d, op_8e, op_8f,
 op_90, op_91, op_92, op_93, op_94, op_95, op_96, op_97, op_98, op_99, op_9a, op_9b, op_9c, op_9d, op_9e, op_9f,
 op_a0, op_a1, op_a2, op_a3, op_a4, op_a5, op_a6, op_a7, op_a8, op_a9, op_aa, op_ab, op_ac, op_ad, op_ae, op_af,
 op_b0, op_b1, op_b2, op_b3, op_b4, op_b5, op_b6, op_b7, op_b8, op_b9, op_ba, op_bb, op_bc, op_bd, op_be, op_bf,
 op_c0, op_c1, op_c2, op_c3, op_c4, op_c5, op_c6, op_c7, op_c8, op_c9, op_ca, op_cb, op_cc, op_cd, op_ce, op_cf,
 op_d0, op_d1, op_d2, op_d3, op_d4, op_d5, op_d6, op_d7, op_d8, op_d9, op_da, op_db, op_dc, op_dd, op_de, op_df,
 op_e0, op_e1, op_e2, op_e3, op_e4, op_e5, op_e6, op_e7, op_e8, op_e9, op_ea, op_eb, op_ec, op_ed, op_ee, op_ef,
 op_f0, op_f1, op_f2, op_f3, op_f4, op_f5, op_f6, op_f7, op_f8, op_f9, op_fa, op_fb, op_fc, op_fd, op_fe, op_ff,
};


void (*ops1[])(OP_PROTO) =
{
 op_cb00, op_cb01, op_cb02, op_cb03, op_cb04, op_cb05, op_cb06, op_cb07, op_cb08, op_cb09, op_cb0a, op_cb0b, op_cb0c, op_cb0d, op_cb0e, op_cb0f,
 op_cb10, op_cb11, op_cb12, op_cb13, op_cb14, op_cb15, op_cb16, op_cb17, op_cb18, op_cb19, op_cb1a, op_cb1b, op_cb1c, op_cb1d, op_cb1e, op_cb1f,
 op_cb20, op_cb21, op_cb22, op_cb23, op_cb24, op_cb25, op_cb26, op_cb27, op_cb28, op_cb29, op_cb2a, op_cb2b, op_cb2c, op_cb2d, op_cb2e, op_cb2f,
 op_cb30, op_cb31, op_cb32, op_cb33, op_cb34, op_cb35, op_cb36, op_cb37, op_cb38, op_cb39, op_cb3a, op_cb3b, op_cb3c, op_cb3d, op_cb3e, op_cb3f,
 op_cb40, op_cb41, op_cb42, op_cb43, op_cb44, op_cb45, op_cb46, op_cb47, op_cb48, op_cb49, op_cb4a, op_cb4b, op_cb4c, op_cb4d, op_cb4e, op_cb4f,
 op_cb50, op_cb51, op_cb52, op_cb53, op_cb54, op_cb55, op_cb56, op_cb57, op_cb58, op_cb59, op_cb5a, op_cb5b, op_cb5c, op_cb5d, op_cb5e, op_cb5f,
 op_cb60, op_cb61, op_cb62, op_cb63, op_cb64, op_cb65, op_cb66, op_cb67, op_cb68, op_cb69, op_cb6a, op_cb6b, op_cb6c, op_cb6d, op_cb6e, op_cb6f,
 op_cb70, op_cb71, op_cb72, op_cb73, op_cb74, op_cb75, op_cb76, op_cb77, op_cb78, op_cb79, op_cb7a, op_cb7b, op_cb7c, op_cb7d, op_cb7e, op_cb7f,
 op_cb80, op_cb81, op_cb82, op_cb83, op_cb84, op_cb85, op_cb86, op_cb87, op_cb88, op_cb89, op_cb8a, op_cb8b, op_cb8c, op_cb8d, op_cb8e, op_cb8f,
 op_cb90, op_cb91, op_cb92, op_cb93, op_cb94, op_cb95, op_cb96, op_cb97, op_cb98, op_cb99, op_cb9a, op_cb9b, op_cb9c, op_cb9d, op_cb9e, op_cb9f,
 op_cba0, op_cba1, op_cba2, op_cba3, op_cba4, op_cba5, op_cba6, op_cba7, op_cba8, op_cba9, op_cbaa, op_cbab, op_cbac, op_cbad, op_cbae, op_cbaf,
 op_cbb0, op_cbb1, op_cbb2, op_cbb3, op_cbb4, op_cbb5, op_cbb6, op_cbb7, op_cbb8, op_cbb9, op_cbba, op_cbbb, op_cbbc, op_cbbd, op_cbbe, op_cbbf,
 op_cbc0, op_cbc1, op_cbc2, op_cbc3, op_cbc4, op_cbc5, op_cbc6, op_cbc7, op_cbc8, op_cbc9, op_cbca, op_cbcb, op_cbcc, op_cbcd, op_cbce, op_cbcf,
 op_cbd0, op_cbd1, op_cbd2, op_cbd3, op_cbd4, op_cbd5, op_cbd6, op_cbd7, op_cbd8, op_cbd9, op_cbda, op_cbdb, op_cbdc, op_cbdd, op_cbde, op_cbdf,
 op_cbe0, op_cbe1, op_cbe2, op_cbe3, op_cbe4, op_cbe5, op_cbe6, op_cbe7, op_cbe8, op_cbe9, op_cbea, op_cbeb, op_cbec, op_cbed, op_cbee, op_cbef,
 op_cbf0, op_cbf1, op_cbf2, op_cbf3, op_cbf4, op_cbf5, op_cbf6, op_cbf7, op_cbf8, op_cbf9, op_cbfa, op_cbfb, op_cbfc, op_cbfd, op_cbfe, op_cbff,
};

    char* op_names0[] = {
"nop", "ld bc,$%04X", "ld (bc),a", "inc bc", "inc b", "dec b", "ld b,$%02X", "rlca", "ld ($%04X),sp", "add hl,bc", "ld a,(bc)", "dec bc", "inc c", "dec c", "ld c,$%02X", "rrca",
"stop 0", "ld de,$%04X", "ld (de),a", "inc de", "inc d", "dec d", "ld d,$%02X", "rla", "jr $%02X", "add hl,de", "ld a,(de)", "dec de", "inc e", "dec e", "ld e,$%02X", "rra",
"jr nz,$%02X", "ld hl,$%04X", "ld (hl+),a", "inc hl", "inc h", "dec h", "ld h,$%02X", "daa", "jr z,$%02X", "add hl,hl", "ld a,(hl+)", "dec hl", "inc l", "dec l", "ld l,$%02X", "cpl",
"jr nc,$%02X", "ld sp,$%04X", "ld (hl-),a", "inc sp", "inc (hl)", "dec (hl)", "ld (hl),$%02X", "scf", "jr c,$%02X", "add hl,sp", "ld a,(hl-)", "dec sp", "inc a", "dec a", "ld a,$%02X", "ccf",
"ld b,b", "ld b,c", "ld b,d", "ld b,e", "ld b,h", "ld b,l", "ld b,(hl)", "ld b,a", "ld c,b", "ld c,c", "ld c,d", "ld c,e", "ld c,h", "ld c,l", "ld c,(hl)", "ld c,a",
"ld d,b", "ld d,c", "ld d,d", "ld d,e", "ld d,h", "ld d,l", "ld d,(hl)", "ld d,a", "ld e,b", "ld e,c", "ld e,d", "ld e,e", "ld e,h", "ld e,l", "ld e,(hl)", "ld e,a",
"ld h,b", "ld h,c", "ld h,d", "ld h,e", "ld h,h", "ld h,l", "ld h,(hl)", "ld h,a", "ld l,b", "ld l,c", "ld l,d", "ld l,e", "ld l,h", "ld l,l", "ld l,(hl)", "ld l,a",
"ld (hl),b", "ld (hl),c", "ld (hl),d", "ld (hl),e", "ld (hl),h", "ld (hl),l", "halt", "ld (hl),a", "ld a,b", "ld a,c", "ld a,d", "ld a,e", "ld a,h", "ld a,l", "ld a,(hl)", "ld a,a",
"add a,b", "add a,c", "add a,d", "add a,e", "add a,h", "add a,l", "add a,(hl)", "add a,a", "adc a,b", "adc a,c", "adc a,d", "adc a,e", "adc a,h", "adc a,l", "adc a,(hl)", "adc a,a",
"sub b", "sub c", "sub d", "sub e", "sub h", "sub l", "sub (hl)", "sub a", "sbc a,b", "sbc a,c", "sbc a,d", "sbc a,e", "sbc a,h", "sbc a,l", "sbc a,(hl)", "sbc a,a",
"and b", "and c", "and d", "and e", "and h", "and l", "and (hl)", "and a", "xor b", "xor c", "xor d", "xor e", "xor h", "xor l", "xor (hl)", "xor a",
"or b", "or c", "or d", "or e", "or h", "or l", "or (hl)", "or a", "cp b", "cp c", "cp d", "cp e", "cp h", "cp l", "cp (hl)", "cp a",
"ret nz", "pop bc", "jp nz,$%04X", "jp $%04X", "call nz,$%04X", "push bc", "add a,$%02X", "rst 00h", "ret z", "ret", "jp z,$%04X", "prefix cb", "call z,$%04X", "call $%04X", "adc a,$%02X", "rst 08h",
"ret nc", "pop de", "jp nc,$%04X", "undefined", "call nc,$%04X", "push de", "sub $%02X", "rst 10h", "ret c", "reti", "jp c,$%04X", "undefined", "call c,$%04X", "undefined", "sbc a,$%02X", "rst 18h",
"ldh ($FF%02X),a", "pop hl", "ld (c),a", "undefined", "undefined", "push hl", "and $%02X", "rst 20h", "add sp,$%02X", "jp (hl)", "ld ($%04X),a", "undefined", "undefined", "undefined", "xor $%02X", "rst 28h",
"ldh a,($FF%02X)", "pop af", "ld a,(c)", "di", "undefined", "push af", "or $%02X", "rst 30h", "ld hl,sp+$%02X", "ld sp,hl", "ld a,($%04X)", "ei", "undefined", "undefined", "cp $%02X", "rst 38h"
    };

char* op_names1[] = {
"rlc b", "rlc c", "rlc d", "rlc e", "rlc h", "rlc l", "rlc (hl)", "rlc a", "rrc b", "rrc c", "rrc d", "rrc e", "rrc h", "rrc l", "rrc (hl)", "rrc a",
"rl b", "rl c", "rl d", "rl e", "rl h", "rl l", "rl (hl)", "rl a", "rr b", "rr c", "rr d", "rr e", "rr h", "rr l", "rr (hl)", "rr a",
"sla b", "sla c", "sla d", "sla e", "sla h", "sla l", "sla (hl)", "sla a", "sra b", "sra c", "sra d", "sra e", "sra h", "sra l", "sra (hl)", "sra a",
"swap b", "swap c", "swap d", "swap e", "swap h", "swap l", "swap (hl)", "swap a", "srl b", "srl c", "srl d", "srl e", "srl h", "srl l", "srl (hl)", "srl a",
"bit 0,b", "bit 0,c", "bit 0,d", "bit 0,e", "bit 0,h", "bit 0,l", "bit 0,(hl)", "bit 0,a", "bit 1,b", "bit 1,c", "bit 1,d", "bit 1,e", "bit 1,h", "bit 1,l", "bit 1,(hl)", "bit 1,a",
"bit 2,b", "bit 2,c", "bit 2,d", "bit 2,e", "bit 2,h", "bit 2,l", "bit 2,(hl)", "bit 2,a", "bit 3,b", "bit 3,c", "bit 3,d", "bit 3,e", "bit 3,h", "bit 3,l", "bit 3,(hl)", "bit 3,a",
"bit 4,b", "bit 4,c", "bit 4,d", "bit 4,e", "bit 4,h", "bit 4,l", "bit 4,(hl)", "bit 4,a", "bit 5,b", "bit 5,c", "bit 5,d", "bit 5,e", "bit 5,h", "bit 5,l", "bit 5,(hl)", "bit 5,a",
"bit 6,b", "bit 6,c", "bit 6,d", "bit 6,e", "bit 6,h", "bit 6,l", "bit 6,(hl)", "bit 6,a", "bit 7,b", "bit 7,c", "bit 7,d", "bit 7,e", "bit 7,h", "bit 7,l", "bit 7,(hl)", "bit 7,a",
"res 0,b", "res 0,c", "res 0,d", "res 0,e", "res 0,h", "res 0,l", "res 0,(hl)", "res 0,a", "res 1,b", "res 1,c", "res 1,d", "res 1,e", "res 1,h", "res 1,l", "res 1,(hl)", "res 1,a",
"res 2,b", "res 2,c", "res 2,d", "res 2,e", "res 2,h", "res 2,l", "res 2,(hl)", "res 2,a", "res 3,b", "res 3,c", "res 3,d", "res 3,e", "res 3,h", "res 3,l", "res 3,(hl)", "res 3,a",
"res 4,b", "res 4,c", "res 4,d", "res 4,e", "res 4,h", "res 4,l", "res 4,(hl)", "res 4,a", "res 5,b", "res 5,c", "res 5,d", "res 5,e", "res 5,h", "res 5,l", "res 5,(hl)", "res 5,a",
"res 6,b", "res 6,c", "res 6,d", "res 6,e", "res 6,h", "res 6,l", "res 6,(hl)", "res 6,a", "res 7,b", "res 7,c", "res 7,d", "res 7,e", "res 7,h", "res 7,l", "res 7,(hl)", "res 7,a",
"set 0,b", "set 0,c", "set 0,d", "set 0,e", "set 0,h", "set 0,l", "set 0,(hl)", "set 0,a", "set 1,b", "set 1,c", "set 1,d", "set 1,e", "set 1,h", "set 1,l", "set 1,(hl)", "set 1,a",
"set 2,b", "set 2,c", "set 2,d", "set 2,e", "set 2,h", "set 2,l", "set 2,(hl)", "set 2,a", "set 3,b", "set 3,c", "set 3,d", "set 3,e", "set 3,h", "set 3,l", "set 3,(hl)", "set 3,a",
"set 4,b", "set 4,c", "set 4,d", "set 4,e", "set 4,h", "set 4,l", "set 4,(hl)", "set 4,a", "set 5,b", "set 5,c", "set 5,d", "set 5,e", "set 5,h", "set 5,l", "set 5,(hl)", "set 5,a",
"set 6,b", "set 6,c", "set 6,d", "set 6,e", "set 6,h", "set 6,l", "set 6,(hl)", "set 6,a", "set 7,b", "set 7,c", "set 7,d", "set 7,e", "set 7,h", "set 7,l", "set 7,(hl)", "set 7,a"
};

    int byte_lens0[] = {    
1, 3, 1, 1, 1, 1, 2, 1, 3, 1, 1, 1, 1, 1, 2, 1,
2, 3, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1,
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
2, 1, 2, 0, 0, 1, 2, 1, 2, 1, 3, 0, 0, 0, 2, 1,
2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 3, 1, 0, 0, 2, 1
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


unsigned char DMG_ROM_bin[] = {
  0x31, 0xfe, 0xff, 0xaf, 0x21, 0xff, 0x9f, 0x32, 0xcb, 0x7c, 0x20, 0xfb,
  0x21, 0x26, 0xff, 0x0e, 0x11, 0x3e, 0x80, 0x32, 0xe2, 0x0c, 0x3e, 0xf3,
  0xe2, 0x32, 0x3e, 0x77, 0x77, 0x3e, 0xfc, 0xe0, 0x47, 0x11, 0x04, 0x01,
  0x21, 0x10, 0x80, 0x1a, 0xcd, 0x95, 0x00, 0xcd, 0x96, 0x00, 0x13, 0x7b,
  0xfe, 0x34, 0x20, 0xf3, 0x11, 0xd8, 0x00, 0x06, 0x08, 0x1a, 0x13, 0x22,
  0x23, 0x05, 0x20, 0xf9, 0x3e, 0x19, 0xea, 0x10, 0x99, 0x21, 0x2f, 0x99,
  0x0e, 0x0c, 0x3d, 0x28, 0x08, 0x32, 0x0d, 0x20, 0xf9, 0x2e, 0x0f, 0x18,
  0xf3, 0x67, 0x3e, 0x64, 0x57, 0xe0, 0x42, 0x3e, 0x91, 0xe0, 0x40, 0x04,
  0x1e, 0x02, 0x0e, 0x0c, 0xf0, 0x44, 0xfe, 0x90, 0x20, 0xfa, 0x0d, 0x20,
  0xf7, 0x1d, 0x20, 0xf2, 0x0e, 0x13, 0x24, 0x7c, 0x1e, 0x83, 0xfe, 0x62,
  0x28, 0x06, 0x1e, 0xc1, 0xfe, 0x64, 0x20, 0x06, 0x7b, 0xe2, 0x0c, 0x3e,
  0x87, 0xe2, 0xf0, 0x42, 0x90, 0xe0, 0x42, 0x15, 0x20, 0xd2, 0x05, 0x20,
  0x4f, 0x16, 0x20, 0x18, 0xcb, 0x4f, 0x06, 0x04, 0xc5, 0xcb, 0x11, 0x17,
  0xc1, 0xcb, 0x11, 0x17, 0x05, 0x20, 0xf5, 0x22, 0x23, 0x22, 0x23, 0xc9,
  0xce, 0xed, 0x66, 0x66, 0xcc, 0x0d, 0x00, 0x0b, 0x03, 0x73, 0x00, 0x83,
  0x00, 0x0c, 0x00, 0x0d, 0x00, 0x08, 0x11, 0x1f, 0x88, 0x89, 0x00, 0x0e,
  0xdc, 0xcc, 0x6e, 0xe6, 0xdd, 0xdd, 0xd9, 0x99, 0xbb, 0xbb, 0x67, 0x63,
  0x6e, 0x0e, 0xec, 0xcc, 0xdd, 0xdc, 0x99, 0x9f, 0xbb, 0xb9, 0x33, 0x3e,
  0x3c, 0x42, 0xb9, 0xa5, 0xb9, 0xa5, 0x42, 0x3c, 0x21, 0x04, 0x01, 0x11,
  0xa8, 0x00, 0x1a, 0x13, 0xbe, 0x20, 0xfe, 0x23, 0x7d, 0xfe, 0x34, 0x20,
  0xf5, 0x06, 0x19, 0x78, 0x86, 0x23, 0x05, 0x20, 0xfb, 0x86, 0x20, 0xfe,
  0x3e, 0x01, 0xe0, 0x50
};
unsigned int DMG_ROM_bin_len = 256;
