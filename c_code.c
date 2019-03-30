#include <stdint.h>

#define set_z       (reg[1] |= 0x80)
#define set_n       (reg[1] |= 0x40)
#define set_h       (reg[1] |= 0x20)
#define set_c       (reg[1] |= 0x10)

#define clear_z     (reg[1] &= (~0x80))
#define clear_n     (reg[1] &= (~0x40))
#define clear_h     (reg[1] &= (~0x20))
#define clear_c     (reg[1] &= (~0x10))

void op_00(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: Misc/control instructions
		 instruction: NOP
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_01(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 16bit load/store/move instructions
		 instruction: LD BC,d16
		   num bytes: 3
		      cycles: 12
		       flags: - - - -
	*/
}


void op_02(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD (BC),A
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_03(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 16bit arithmetic/logical instructions
		 instruction: INC BC
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_04(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: INC B
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H -
	*/
	reg[1] &= (~0x40); /* clear flags */
}


void op_05(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: DEC B
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H -
	*/
	reg[1] |= 0x40; /* set flags */
}


void op_06(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD B,d8
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
	reg[2] = mem[1]; /* code LD imm */
}


void op_07(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RLCA
		   num bytes: 1
		      cycles: 4
		       flags: 0 0 0 C
	*/
	reg[1] &= (~0xe0); /* clear flags */
}


void op_08(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 16bit load/store/move instructions
		 instruction: LD (a16),SP
		   num bytes: 3
		      cycles: 20
		       flags: - - - -
	*/
}


void op_09(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 16bit arithmetic/logical instructions
		 instruction: ADD HL,BC
		   num bytes: 1
		      cycles: 8
		       flags: - 0 H C
	*/
	reg[1] &= (~0x40); /* clear flags */
}


void op_0a(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD A,(BC)
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
/* FIXME: code LD */
}


void op_0b(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 16bit arithmetic/logical instructions
		 instruction: DEC BC
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_0c(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: INC C
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H -
	*/
	reg[1] &= (~0x40); /* clear flags */
}


void op_0d(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: DEC C
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H -
	*/
	reg[1] |= 0x40; /* set flags */
}


void op_0e(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD C,d8
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
	reg[3] = mem[1]; /* code LD imm */
}


void op_0f(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RRCA
		   num bytes: 1
		      cycles: 4
		       flags: 0 0 0 C
	*/
	reg[1] &= (~0xe0); /* clear flags */
}


void op_10(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: Misc/control instructions
		 instruction: STOP 0
		   num bytes: 2
		      cycles: 4
		       flags: - - - -
	*/
}


void op_11(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 16bit load/store/move instructions
		 instruction: LD DE,d16
		   num bytes: 3
		      cycles: 12
		       flags: - - - -
	*/
}


void op_12(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD (DE),A
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_13(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 16bit arithmetic/logical instructions
		 instruction: INC DE
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_14(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: INC D
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H -
	*/
	reg[1] &= (~0x40); /* clear flags */
}


void op_15(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: DEC D
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H -
	*/
	reg[1] |= 0x40; /* set flags */
}


void op_16(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD D,d8
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
	reg[4] = mem[1]; /* code LD imm */
}


void op_17(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RLA
		   num bytes: 1
		      cycles: 4
		       flags: 0 0 0 C
	*/
	reg[1] &= (~0xe0); /* clear flags */
}


void op_18(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: JR r8
		   num bytes: 2
		      cycles: 12
		       flags: - - - -
	*/
}


void op_19(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 16bit arithmetic/logical instructions
		 instruction: ADD HL,DE
		   num bytes: 1
		      cycles: 8
		       flags: - 0 H C
	*/
	reg[1] &= (~0x40); /* clear flags */
}


void op_1a(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD A,(DE)
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
/* FIXME: code LD */
}


void op_1b(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 16bit arithmetic/logical instructions
		 instruction: DEC DE
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_1c(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: INC E
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H -
	*/
	reg[1] &= (~0x40); /* clear flags */
}


void op_1d(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: DEC E
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H -
	*/
	reg[1] |= 0x40; /* set flags */
}


void op_1e(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD E,d8
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
	reg[5] = mem[1]; /* code LD imm */
}


void op_1f(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RRA
		   num bytes: 1
		      cycles: 4
		       flags: 0 0 0 C
	*/
	reg[1] &= (~0xe0); /* clear flags */
}


void op_20(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: JR NZ,r8
		   num bytes: 2
		      cycles: 12/8
		       flags: - - - -
	*/
}


void op_21(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 16bit load/store/move instructions
		 instruction: LD HL,d16
		   num bytes: 3
		      cycles: 12
		       flags: - - - -
	*/
}


void op_22(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD (HL+),A
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_23(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 16bit arithmetic/logical instructions
		 instruction: INC HL
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_24(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: INC H
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H -
	*/
	reg[1] &= (~0x40); /* clear flags */
}


void op_25(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: DEC H
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H -
	*/
	reg[1] |= 0x40; /* set flags */
}


void op_26(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD H,d8
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
	reg[6] = mem[1]; /* code LD imm */
}


void op_27(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: DAA
		   num bytes: 1
		      cycles: 4
		       flags: Z - 0 C
	*/
	reg[1] &= (~0x20); /* clear flags */
}


void op_28(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: JR Z,r8
		   num bytes: 2
		      cycles: 12/8
		       flags: - - - -
	*/
}


void op_29(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 16bit arithmetic/logical instructions
		 instruction: ADD HL,HL
		   num bytes: 1
		      cycles: 8
		       flags: - 0 H C
	*/
	reg[1] &= (~0x40); /* clear flags */
}


void op_2a(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD A,(HL+)
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
/* FIXME: code LD */
}


void op_2b(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 16bit arithmetic/logical instructions
		 instruction: DEC HL
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_2c(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: INC L
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H -
	*/
	reg[1] &= (~0x40); /* clear flags */
}


void op_2d(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: DEC L
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H -
	*/
	reg[1] |= 0x40; /* set flags */
}


void op_2e(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD L,d8
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
	reg[7] = mem[1]; /* code LD imm */
}


void op_2f(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: CPL
		   num bytes: 1
		      cycles: 4
		       flags: - 1 1 -
	*/
	reg[1] |= 0x60; /* set flags */
}


void op_30(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: JR NC,r8
		   num bytes: 2
		      cycles: 12/8
		       flags: - - - -
	*/
}


void op_31(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 16bit load/store/move instructions
		 instruction: LD SP,d16
		   num bytes: 3
		      cycles: 12
		       flags: - - - -
	*/
}


void op_32(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD (HL-),A
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_33(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 16bit arithmetic/logical instructions
		 instruction: INC SP
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_34(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: INC (HL)
		   num bytes: 1
		      cycles: 12
		       flags: Z 0 H -
	*/
	reg[1] &= (~0x40); /* clear flags */
}


void op_35(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: DEC (HL)
		   num bytes: 1
		      cycles: 12
		       flags: Z 1 H -
	*/
	reg[1] |= 0x40; /* set flags */
}


void op_36(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD (HL),d8
		   num bytes: 2
		      cycles: 12
		       flags: - - - -
	*/
}


void op_37(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SCF
		   num bytes: 1
		      cycles: 4
		       flags: - 0 0 1
	*/
	reg[1] &= (~0x60); /* clear flags */
	reg[1] |= 0x10; /* set flags */
}


void op_38(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: JR C,r8
		   num bytes: 2
		      cycles: 12/8
		       flags: - - - -
	*/
}


void op_39(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 16bit arithmetic/logical instructions
		 instruction: ADD HL,SP
		   num bytes: 1
		      cycles: 8
		       flags: - 0 H C
	*/
	reg[1] &= (~0x40); /* clear flags */
}


void op_3a(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD A,(HL-)
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
/* FIXME: code LD */
}


void op_3b(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 16bit arithmetic/logical instructions
		 instruction: DEC SP
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_3c(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: INC A
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H -
	*/
	reg[1] &= (~0x40); /* clear flags */
}


void op_3d(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: DEC A
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H -
	*/
	reg[1] |= 0x40; /* set flags */
}


void op_3e(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD A,d8
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
	reg[0] = mem[1]; /* code LD imm */
}


void op_3f(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: CCF
		   num bytes: 1
		      cycles: 4
		       flags: - 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_40(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD B,B
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[2] = reg[2]; /* code LD reg */
}


void op_41(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD B,C
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[2] = reg[3]; /* code LD reg */
}


void op_42(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD B,D
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[2] = reg[4]; /* code LD reg */
}


void op_43(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD B,E
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[2] = reg[5]; /* code LD reg */
}


void op_44(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD B,H
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[2] = reg[6]; /* code LD reg */
}


void op_45(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD B,L
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[2] = reg[7]; /* code LD reg */
}


void op_46(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD B,(HL)
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
/* FIXME: code LD */
}


void op_47(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD B,A
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[2] = reg[0]; /* code LD reg */
}


void op_48(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD C,B
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[3] = reg[2]; /* code LD reg */
}


void op_49(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD C,C
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[3] = reg[3]; /* code LD reg */
}


void op_4a(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD C,D
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[3] = reg[4]; /* code LD reg */
}


void op_4b(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD C,E
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[3] = reg[5]; /* code LD reg */
}


void op_4c(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD C,H
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[3] = reg[6]; /* code LD reg */
}


void op_4d(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD C,L
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[3] = reg[7]; /* code LD reg */
}


void op_4e(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD C,(HL)
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
/* FIXME: code LD */
}


void op_4f(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD C,A
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[3] = reg[0]; /* code LD reg */
}


void op_50(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD D,B
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[4] = reg[2]; /* code LD reg */
}


void op_51(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD D,C
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[4] = reg[3]; /* code LD reg */
}


void op_52(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD D,D
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[4] = reg[4]; /* code LD reg */
}


void op_53(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD D,E
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[4] = reg[5]; /* code LD reg */
}


void op_54(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD D,H
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[4] = reg[6]; /* code LD reg */
}


void op_55(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD D,L
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[4] = reg[7]; /* code LD reg */
}


void op_56(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD D,(HL)
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
/* FIXME: code LD */
}


void op_57(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD D,A
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[4] = reg[0]; /* code LD reg */
}


void op_58(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD E,B
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[5] = reg[2]; /* code LD reg */
}


void op_59(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD E,C
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[5] = reg[3]; /* code LD reg */
}


void op_5a(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD E,D
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[5] = reg[4]; /* code LD reg */
}


void op_5b(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD E,E
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[5] = reg[5]; /* code LD reg */
}


void op_5c(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD E,H
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[5] = reg[6]; /* code LD reg */
}


void op_5d(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD E,L
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[5] = reg[7]; /* code LD reg */
}


void op_5e(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD E,(HL)
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
/* FIXME: code LD */
}


void op_5f(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD E,A
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[5] = reg[0]; /* code LD reg */
}


void op_60(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD H,B
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[6] = reg[2]; /* code LD reg */
}


void op_61(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD H,C
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[6] = reg[3]; /* code LD reg */
}


void op_62(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD H,D
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[6] = reg[4]; /* code LD reg */
}


void op_63(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD H,E
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[6] = reg[5]; /* code LD reg */
}


void op_64(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD H,H
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[6] = reg[6]; /* code LD reg */
}


void op_65(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD H,L
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[6] = reg[7]; /* code LD reg */
}


void op_66(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD H,(HL)
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
/* FIXME: code LD */
}


void op_67(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD H,A
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[6] = reg[0]; /* code LD reg */
}


void op_68(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD L,B
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[7] = reg[2]; /* code LD reg */
}


void op_69(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD L,C
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[7] = reg[3]; /* code LD reg */
}


void op_6a(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD L,D
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[7] = reg[4]; /* code LD reg */
}


void op_6b(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD L,E
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[7] = reg[5]; /* code LD reg */
}


void op_6c(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD L,H
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[7] = reg[6]; /* code LD reg */
}


void op_6d(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD L,L
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[7] = reg[7]; /* code LD reg */
}


void op_6e(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD L,(HL)
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
/* FIXME: code LD */
}


void op_6f(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD L,A
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[7] = reg[0]; /* code LD reg */
}


void op_70(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD (HL),B
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_71(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD (HL),C
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_72(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD (HL),D
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_73(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD (HL),E
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_74(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD (HL),H
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_75(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD (HL),L
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_76(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: Misc/control instructions
		 instruction: HALT
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_77(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD (HL),A
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_78(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD A,B
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[0] = reg[2]; /* code LD reg */
}


void op_79(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD A,C
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[0] = reg[3]; /* code LD reg */
}


void op_7a(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD A,D
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[0] = reg[4]; /* code LD reg */
}


void op_7b(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD A,E
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[0] = reg[5]; /* code LD reg */
}


void op_7c(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD A,H
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[0] = reg[6]; /* code LD reg */
}


void op_7d(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD A,L
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[0] = reg[7]; /* code LD reg */
}


void op_7e(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD A,(HL)
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
/* FIXME: code LD */
}


void op_7f(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD A,A
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
	reg[0] = reg[0]; /* code LD reg */
}


void op_80(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADD A,B
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/
	reg[1] &= (~0x40); /* clear flags */
}


void op_81(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADD A,C
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/
	reg[1] &= (~0x40); /* clear flags */
}


void op_82(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADD A,D
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/
	reg[1] &= (~0x40); /* clear flags */
}


void op_83(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADD A,E
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/
	reg[1] &= (~0x40); /* clear flags */
}


void op_84(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADD A,H
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/
	reg[1] &= (~0x40); /* clear flags */
}


void op_85(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADD A,L
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/
	reg[1] &= (~0x40); /* clear flags */
}


void op_86(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADD A,(HL)
		   num bytes: 1
		      cycles: 8
		       flags: Z 0 H C
	*/
	reg[1] &= (~0x40); /* clear flags */
}


void op_87(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADD A,A
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/
	reg[1] &= (~0x40); /* clear flags */
}


void op_88(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADC A,B
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/
	reg[1] &= (~0x40); /* clear flags */
}


void op_89(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADC A,C
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/
	reg[1] &= (~0x40); /* clear flags */
}


void op_8a(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADC A,D
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/
	reg[1] &= (~0x40); /* clear flags */
}


void op_8b(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADC A,E
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/
	reg[1] &= (~0x40); /* clear flags */
}


void op_8c(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADC A,H
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/
	reg[1] &= (~0x40); /* clear flags */
}


void op_8d(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADC A,L
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/
	reg[1] &= (~0x40); /* clear flags */
}


void op_8e(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADC A,(HL)
		   num bytes: 1
		      cycles: 8
		       flags: Z 0 H C
	*/
	reg[1] &= (~0x40); /* clear flags */
}


void op_8f(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADC A,A
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/
	reg[1] &= (~0x40); /* clear flags */
}


void op_90(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SUB B
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/
	reg[1] |= 0x40; /* set flags */
}


void op_91(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SUB C
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/
	reg[1] |= 0x40; /* set flags */
}


void op_92(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SUB D
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/
	reg[1] |= 0x40; /* set flags */
}


void op_93(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SUB E
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/
	reg[1] |= 0x40; /* set flags */
}


void op_94(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SUB H
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/
	reg[1] |= 0x40; /* set flags */
}


void op_95(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SUB L
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/
	reg[1] |= 0x40; /* set flags */
}


void op_96(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SUB (HL)
		   num bytes: 1
		      cycles: 8
		       flags: Z 1 H C
	*/
	reg[1] |= 0x40; /* set flags */
}


void op_97(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SUB A
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/
	reg[1] |= 0x40; /* set flags */
}


void op_98(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SBC A,B
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/
	reg[1] |= 0x40; /* set flags */
}


void op_99(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SBC A,C
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/
	reg[1] |= 0x40; /* set flags */
}


void op_9a(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SBC A,D
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/
	reg[1] |= 0x40; /* set flags */
}


void op_9b(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SBC A,E
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/
	reg[1] |= 0x40; /* set flags */
}


void op_9c(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SBC A,H
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/
	reg[1] |= 0x40; /* set flags */
}


void op_9d(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SBC A,L
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/
	reg[1] |= 0x40; /* set flags */
}


void op_9e(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SBC A,(HL)
		   num bytes: 1
		      cycles: 8
		       flags: Z 1 H C
	*/
	reg[1] |= 0x40; /* set flags */
}


void op_9f(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SBC A,A
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/
	reg[1] |= 0x40; /* set flags */
}


void op_a0(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: AND B
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 1 0
	*/
	reg[0] &= reg[2];    /* code AND */
	reg[0] == 0 ? set_z : clear_z;
	reg[1] &= (~0x50); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_a1(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: AND C
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 1 0
	*/
	reg[0] &= reg[3];    /* code AND */
	reg[0] == 0 ? set_z : clear_z;
	reg[1] &= (~0x50); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_a2(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: AND D
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 1 0
	*/
	reg[0] &= reg[4];    /* code AND */
	reg[0] == 0 ? set_z : clear_z;
	reg[1] &= (~0x50); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_a3(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: AND E
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 1 0
	*/
	reg[0] &= reg[5];    /* code AND */
	reg[0] == 0 ? set_z : clear_z;
	reg[1] &= (~0x50); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_a4(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: AND H
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 1 0
	*/
	reg[0] &= reg[6];    /* code AND */
	reg[0] == 0 ? set_z : clear_z;
	reg[1] &= (~0x50); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_a5(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: AND L
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 1 0
	*/
	reg[0] &= reg[7];    /* code AND */
	reg[0] == 0 ? set_z : clear_z;
	reg[1] &= (~0x50); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_a6(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: AND (HL)
		   num bytes: 1
		      cycles: 8
		       flags: Z 0 1 0
	*/
/* FIXME: code AND */
	reg[1] &= (~0x50); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_a7(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: AND A
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 1 0
	*/
	reg[0] &= reg[0];    /* code AND */
	reg[0] == 0 ? set_z : clear_z;
	reg[1] &= (~0x50); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_a8(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: XOR B
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/
	reg[1] &= (~0x70); /* clear flags */
}


void op_a9(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: XOR C
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/
	reg[1] &= (~0x70); /* clear flags */
}


void op_aa(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: XOR D
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/
	reg[1] &= (~0x70); /* clear flags */
}


void op_ab(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: XOR E
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/
	reg[1] &= (~0x70); /* clear flags */
}


void op_ac(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: XOR H
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/
	reg[1] &= (~0x70); /* clear flags */
}


void op_ad(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: XOR L
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/
	reg[1] &= (~0x70); /* clear flags */
}


void op_ae(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: XOR (HL)
		   num bytes: 1
		      cycles: 8
		       flags: Z 0 0 0
	*/
	reg[1] &= (~0x70); /* clear flags */
}


void op_af(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: XOR A
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/
	reg[1] &= (~0x70); /* clear flags */
}


void op_b0(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: OR B
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/
	reg[1] &= (~0x70); /* clear flags */
}


void op_b1(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: OR C
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/
	reg[1] &= (~0x70); /* clear flags */
}


void op_b2(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: OR D
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/
	reg[1] &= (~0x70); /* clear flags */
}


void op_b3(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: OR E
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/
	reg[1] &= (~0x70); /* clear flags */
}


void op_b4(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: OR H
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/
	reg[1] &= (~0x70); /* clear flags */
}


void op_b5(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: OR L
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/
	reg[1] &= (~0x70); /* clear flags */
}


void op_b6(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: OR (HL)
		   num bytes: 1
		      cycles: 8
		       flags: Z 0 0 0
	*/
	reg[1] &= (~0x70); /* clear flags */
}


void op_b7(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: OR A
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/
	reg[1] &= (~0x70); /* clear flags */
}


void op_b8(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: CP B
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/
	reg[1] |= 0x40; /* set flags */
}


void op_b9(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: CP C
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/
	reg[1] |= 0x40; /* set flags */
}


void op_ba(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: CP D
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/
	reg[1] |= 0x40; /* set flags */
}


void op_bb(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: CP E
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/
	reg[1] |= 0x40; /* set flags */
}


void op_bc(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: CP H
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/
	reg[1] |= 0x40; /* set flags */
}


void op_bd(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: CP L
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/
	reg[1] |= 0x40; /* set flags */
}


void op_be(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: CP (HL)
		   num bytes: 1
		      cycles: 8
		       flags: Z 1 H C
	*/
	reg[1] |= 0x40; /* set flags */
}


void op_bf(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: CP A
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/
	reg[1] |= 0x40; /* set flags */
}


void op_c0(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: RET NZ
		   num bytes: 1
		      cycles: 20/8
		       flags: - - - -
	*/
}


void op_c1(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 16bit load/store/move instructions
		 instruction: POP BC
		   num bytes: 1
		      cycles: 12
		       flags: - - - -
	*/
}


void op_c2(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: JP NZ,a16
		   num bytes: 3
		      cycles: 16/12
		       flags: - - - -
	*/
}


void op_c3(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: JP a16
		   num bytes: 3
		      cycles: 16
		       flags: - - - -
	*/
}


void op_c4(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: CALL NZ,a16
		   num bytes: 3
		      cycles: 24/12
		       flags: - - - -
	*/
}


void op_c5(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 16bit load/store/move instructions
		 instruction: PUSH BC
		   num bytes: 1
		      cycles: 16
		       flags: - - - -
	*/
}


void op_c6(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADD A,d8
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 H C
	*/
	reg[1] &= (~0x40); /* clear flags */
}


void op_c7(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: RST 00H
		   num bytes: 1
		      cycles: 16
		       flags: - - - -
	*/
}


void op_c8(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: RET Z
		   num bytes: 1
		      cycles: 20/8
		       flags: - - - -
	*/
}


void op_c9(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: RET
		   num bytes: 1
		      cycles: 16
		       flags: - - - -
	*/
}


void op_ca(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: JP Z,a16
		   num bytes: 3
		      cycles: 16/12
		       flags: - - - -
	*/
}


void op_cb(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: Misc/control instructions
		 instruction: PREFIX CB
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_cc(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: CALL Z,a16
		   num bytes: 3
		      cycles: 24/12
		       flags: - - - -
	*/
}


void op_cd(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: CALL a16
		   num bytes: 3
		      cycles: 24
		       flags: - - - -
	*/
}


void op_ce(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADC A,d8
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 H C
	*/
	reg[1] &= (~0x40); /* clear flags */
}


void op_cf(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: RST 08H
		   num bytes: 1
		      cycles: 16
		       flags: - - - -
	*/
}


void op_d0(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: RET NC
		   num bytes: 1
		      cycles: 20/8
		       flags: - - - -
	*/
}


void op_d1(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 16bit load/store/move instructions
		 instruction: POP DE
		   num bytes: 1
		      cycles: 12
		       flags: - - - -
	*/
}


void op_d2(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: JP NC,a16
		   num bytes: 3
		      cycles: 16/12
		       flags: - - - -
	*/
}


void op_d3(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: UNDEFINED XXX
		 instruction: undefined
		   num bytes: undefined
		      cycles: undefined
		       flags: undefined
	*/
}


void op_d4(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: CALL NC,a16
		   num bytes: 3
		      cycles: 24/12
		       flags: - - - -
	*/
}


void op_d5(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 16bit load/store/move instructions
		 instruction: PUSH DE
		   num bytes: 1
		      cycles: 16
		       flags: - - - -
	*/
}


void op_d6(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SUB d8
		   num bytes: 2
		      cycles: 8
		       flags: Z 1 H C
	*/
	reg[1] |= 0x40; /* set flags */
}


void op_d7(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: RST 10H
		   num bytes: 1
		      cycles: 16
		       flags: - - - -
	*/
}


void op_d8(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: RET C
		   num bytes: 1
		      cycles: 20/8
		       flags: - - - -
	*/
}


void op_d9(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: RETI
		   num bytes: 1
		      cycles: 16
		       flags: - - - -
	*/
}


void op_da(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: JP C,a16
		   num bytes: 3
		      cycles: 16/12
		       flags: - - - -
	*/
}


void op_db(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: UNDEFINED XXX
		 instruction: undefined
		   num bytes: undefined
		      cycles: undefined
		       flags: undefined
	*/
}


void op_dc(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: CALL C,a16
		   num bytes: 3
		      cycles: 24/12
		       flags: - - - -
	*/
}


void op_dd(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: UNDEFINED XXX
		 instruction: undefined
		   num bytes: undefined
		      cycles: undefined
		       flags: undefined
	*/
}


void op_de(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SBC A,d8
		   num bytes: 2
		      cycles: 8
		       flags: Z 1 H C
	*/
	reg[1] |= 0x40; /* set flags */
}


void op_df(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: RST 18H
		   num bytes: 1
		      cycles: 16
		       flags: - - - -
	*/
}


void op_e0(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LDH (a8),A
		   num bytes: 2
		      cycles: 12
		       flags: - - - -
	*/
}


void op_e1(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 16bit load/store/move instructions
		 instruction: POP HL
		   num bytes: 1
		      cycles: 12
		       flags: - - - -
	*/
}


void op_e2(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD (C),A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_e3(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: UNDEFINED XXX
		 instruction: undefined
		   num bytes: undefined
		      cycles: undefined
		       flags: undefined
	*/
}


void op_e4(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: UNDEFINED XXX
		 instruction: undefined
		   num bytes: undefined
		      cycles: undefined
		       flags: undefined
	*/
}


void op_e5(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 16bit load/store/move instructions
		 instruction: PUSH HL
		   num bytes: 1
		      cycles: 16
		       flags: - - - -
	*/
}


void op_e6(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: AND d8
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 0
	*/
/* FIXME: code AND */
	reg[1] &= (~0x50); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_e7(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: RST 20H
		   num bytes: 1
		      cycles: 16
		       flags: - - - -
	*/
}


void op_e8(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 16bit arithmetic/logical instructions
		 instruction: ADD SP,r8
		   num bytes: 2
		      cycles: 16
		       flags: 0 0 H C
	*/
	reg[1] &= (~0xc0); /* clear flags */
}


void op_e9(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: JP (HL)
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_ea(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD (a16),A
		   num bytes: 3
		      cycles: 16
		       flags: - - - -
	*/
}


void op_eb(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: UNDEFINED XXX
		 instruction: undefined
		   num bytes: undefined
		      cycles: undefined
		       flags: undefined
	*/
}


void op_ec(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: UNDEFINED XXX
		 instruction: undefined
		   num bytes: undefined
		      cycles: undefined
		       flags: undefined
	*/
}


void op_ed(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: UNDEFINED XXX
		 instruction: undefined
		   num bytes: undefined
		      cycles: undefined
		       flags: undefined
	*/
}


void op_ee(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: XOR d8
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/
	reg[1] &= (~0x70); /* clear flags */
}


void op_ef(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: RST 28H
		   num bytes: 1
		      cycles: 16
		       flags: - - - -
	*/
}


void op_f0(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LDH A,(a8)
		   num bytes: 2
		      cycles: 12
		       flags: - - - -
	*/
}


void op_f1(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 16bit load/store/move instructions
		 instruction: POP AF
		   num bytes: 1
		      cycles: 12
		       flags: Z N H C
	*/
}


void op_f2(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD A,(C)
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
/* FIXME: code LD */
}


void op_f3(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: Misc/control instructions
		 instruction: DI
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_f4(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: UNDEFINED XXX
		 instruction: undefined
		   num bytes: undefined
		      cycles: undefined
		       flags: undefined
	*/
}


void op_f5(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 16bit load/store/move instructions
		 instruction: PUSH AF
		   num bytes: 1
		      cycles: 16
		       flags: - - - -
	*/
}


void op_f6(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: OR d8
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/
	reg[1] &= (~0x70); /* clear flags */
}


void op_f7(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: RST 30H
		   num bytes: 1
		      cycles: 16
		       flags: - - - -
	*/
}


void op_f8(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 16bit load/store/move instructions
		 instruction: LD HL,SP+r8
		   num bytes: 2
		      cycles: 12
		       flags: 0 0 H C
	*/
	reg[1] &= (~0xc0); /* clear flags */
}


void op_f9(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 16bit load/store/move instructions
		 instruction: LD SP,HL
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_fa(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD A,(a16)
		   num bytes: 3
		      cycles: 16
		       flags: - - - -
	*/
/* FIXME: code LD */
}


void op_fb(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: Misc/control instructions
		 instruction: EI
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_fc(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: UNDEFINED XXX
		 instruction: undefined
		   num bytes: undefined
		      cycles: undefined
		       flags: undefined
	*/
}


void op_fd(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: UNDEFINED XXX
		 instruction: undefined
		   num bytes: undefined
		      cycles: undefined
		       flags: undefined
	*/
}


void op_fe(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: CP d8
		   num bytes: 2
		      cycles: 8
		       flags: Z 1 H C
	*/
	reg[1] |= 0x40; /* set flags */
}


void op_ff(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: RST 38H
		   num bytes: 1
		      cycles: 16
		       flags: - - - -
	*/
}


void op_cb00(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RLC B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb01(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RLC C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb02(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RLC D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb03(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RLC E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb04(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RLC H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb05(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RLC L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb06(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RLC (HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb07(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RLC A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb08(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RRC B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb09(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RRC C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb0a(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RRC D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb0b(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RRC E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb0c(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RRC H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb0d(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RRC L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb0e(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RRC (HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb0f(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RRC A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb10(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RL B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb11(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RL C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb12(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RL D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb13(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RL E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb14(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RL H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb15(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RL L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb16(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RL (HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb17(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RL A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb18(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RR B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb19(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RR C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb1a(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RR D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb1b(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RR E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb1c(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RR H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb1d(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RR L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb1e(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RR (HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb1f(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RR A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb20(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SLA B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb21(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SLA C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb22(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SLA D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb23(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SLA E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb24(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SLA H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb25(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SLA L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb26(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SLA (HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb27(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SLA A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb28(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRA B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/
	reg[1] &= (~0x70); /* clear flags */
}


void op_cb29(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRA C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/
	reg[1] &= (~0x70); /* clear flags */
}


void op_cb2a(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRA D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/
	reg[1] &= (~0x70); /* clear flags */
}


void op_cb2b(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRA E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/
	reg[1] &= (~0x70); /* clear flags */
}


void op_cb2c(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRA H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/
	reg[1] &= (~0x70); /* clear flags */
}


void op_cb2d(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRA L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/
	reg[1] &= (~0x70); /* clear flags */
}


void op_cb2e(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRA (HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 0 0
	*/
	reg[1] &= (~0x70); /* clear flags */
}


void op_cb2f(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRA A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/
	reg[1] &= (~0x70); /* clear flags */
}


void op_cb30(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SWAP B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/
	reg[1] &= (~0x70); /* clear flags */
}


void op_cb31(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SWAP C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/
	reg[1] &= (~0x70); /* clear flags */
}


void op_cb32(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SWAP D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/
	reg[1] &= (~0x70); /* clear flags */
}


void op_cb33(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SWAP E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/
	reg[1] &= (~0x70); /* clear flags */
}


void op_cb34(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SWAP H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/
	reg[1] &= (~0x70); /* clear flags */
}


void op_cb35(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SWAP L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/
	reg[1] &= (~0x70); /* clear flags */
}


void op_cb36(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SWAP (HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 0 0
	*/
	reg[1] &= (~0x70); /* clear flags */
}


void op_cb37(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SWAP A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/
	reg[1] &= (~0x70); /* clear flags */
}


void op_cb38(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRL B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb39(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRL C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb3a(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRL D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb3b(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRL E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb3c(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRL H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb3d(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRL L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb3e(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRL (HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb3f(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRL A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	reg[1] &= (~0x60); /* clear flags */
}


void op_cb40(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 0,B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb41(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 0,C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb42(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 0,D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb43(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 0,E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb44(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 0,H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb45(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 0,L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb46(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 0,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb47(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 0,A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb48(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 1,B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb49(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 1,C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb4a(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 1,D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb4b(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 1,E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb4c(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 1,H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb4d(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 1,L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb4e(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 1,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb4f(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 1,A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb50(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 2,B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb51(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 2,C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb52(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 2,D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb53(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 2,E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb54(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 2,H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb55(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 2,L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb56(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 2,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb57(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 2,A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb58(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 3,B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb59(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 3,C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb5a(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 3,D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb5b(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 3,E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb5c(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 3,H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb5d(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 3,L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb5e(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 3,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb5f(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 3,A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb60(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 4,B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb61(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 4,C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb62(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 4,D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb63(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 4,E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb64(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 4,H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb65(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 4,L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb66(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 4,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb67(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 4,A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb68(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 5,B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb69(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 5,C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb6a(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 5,D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb6b(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 5,E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb6c(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 5,H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb6d(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 5,L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb6e(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 5,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb6f(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 5,A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb70(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 6,B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb71(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 6,C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb72(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 6,D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb73(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 6,E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb74(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 6,H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb75(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 6,L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb76(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 6,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb77(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 6,A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb78(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 7,B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb79(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 7,C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb7a(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 7,D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb7b(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 7,E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb7c(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 7,H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb7d(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 7,L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb7e(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 7,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb7f(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 7,A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	reg[1] &= (~0x40); /* clear flags */
	reg[1] |= 0x20; /* set flags */
}


void op_cb80(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 0,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb81(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 0,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb82(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 0,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb83(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 0,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb84(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 0,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb85(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 0,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb86(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 0,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/
}


void op_cb87(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 0,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb88(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 1,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb89(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 1,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb8a(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 1,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb8b(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 1,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb8c(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 1,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb8d(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 1,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb8e(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 1,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/
}


void op_cb8f(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 1,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb90(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 2,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb91(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 2,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb92(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 2,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb93(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 2,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb94(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 2,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb95(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 2,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb96(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 2,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/
}


void op_cb97(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 2,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb98(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 3,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb99(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 3,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb9a(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 3,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb9b(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 3,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb9c(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 3,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb9d(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 3,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb9e(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 3,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/
}


void op_cb9f(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 3,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cba0(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 4,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cba1(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 4,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cba2(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 4,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cba3(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 4,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cba4(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 4,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cba5(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 4,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cba6(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 4,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/
}


void op_cba7(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 4,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cba8(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 5,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cba9(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 5,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbaa(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 5,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbab(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 5,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbac(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 5,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbad(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 5,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbae(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 5,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/
}


void op_cbaf(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 5,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbb0(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 6,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbb1(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 6,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbb2(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 6,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbb3(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 6,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbb4(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 6,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbb5(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 6,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbb6(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 6,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/
}


void op_cbb7(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 6,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbb8(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 7,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbb9(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 7,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbba(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 7,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbbb(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 7,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbbc(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 7,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbbd(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 7,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbbe(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 7,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/
}


void op_cbbf(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 7,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbc0(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 0,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbc1(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 0,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbc2(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 0,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbc3(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 0,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbc4(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 0,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbc5(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 0,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbc6(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 0,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/
}


void op_cbc7(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 0,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbc8(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 1,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbc9(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 1,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbca(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 1,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbcb(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 1,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbcc(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 1,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbcd(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 1,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbce(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 1,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/
}


void op_cbcf(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 1,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbd0(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 2,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbd1(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 2,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbd2(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 2,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbd3(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 2,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbd4(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 2,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbd5(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 2,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbd6(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 2,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/
}


void op_cbd7(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 2,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbd8(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 3,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbd9(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 3,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbda(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 3,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbdb(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 3,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbdc(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 3,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbdd(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 3,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbde(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 3,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/
}


void op_cbdf(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 3,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbe0(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 4,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbe1(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 4,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbe2(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 4,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbe3(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 4,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbe4(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 4,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbe5(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 4,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbe6(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 4,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/
}


void op_cbe7(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 4,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbe8(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 5,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbe9(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 5,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbea(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 5,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbeb(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 5,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbec(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 5,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbed(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 5,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbee(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 5,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/
}


void op_cbef(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 5,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbf0(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 6,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbf1(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 6,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbf2(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 6,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbf3(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 6,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbf4(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 6,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbf5(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 6,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbf6(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 6,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/
}


void op_cbf7(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 6,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbf8(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 7,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbf9(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 7,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbfa(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 7,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbfb(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 7,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbfc(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 7,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbfd(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 7,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbfe(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 7,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/
}


void op_cbff(uint8_t *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 7,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


