#include "gb.h"

void op_01(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 16bit load/store/move instructions
		 instruction: LD BC,d16
		   num bytes: 3
		      cycles: 12
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r16->BC = *(uint16_t *)&mem[(r16->PC)+1];
	r16->PC += 3;
}

void op_02(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD (BC),A
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->BC] = r8->A;
	r16->PC += 1;
}

void op_06(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD B,d8
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B = mem[(r16->PC)+1];
	r16->PC += 2;
}

void op_08(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 16bit load/store/move instructions
		 instruction: LD (a16),SP
		   num bytes: 3
		      cycles: 20
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint16_t a16 = *(uint16_t *)&mem[(r16->PC)+1];
	*(uint16_t *)&mem[a16] = r16->SP;
	r16->PC += 3;
}

void op_0a(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD A,(BC)
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A = mem[r16->BC];
	r16->PC += 1;
}

void op_0e(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD C,d8
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C = mem[(r16->PC)+1];
	r16->PC += 2;
}

void op_11(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 16bit load/store/move instructions
		 instruction: LD DE,d16
		   num bytes: 3
		      cycles: 12
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r16->DE = *(uint16_t *)&mem[(r16->PC)+1];
	r16->PC += 3;
}

void op_12(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD (DE),A
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->DE] = r8->A;
	r16->PC += 1;
}

void op_16(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD D,d8
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D = mem[(r16->PC)+1];
	r16->PC += 2;
}

void op_1a(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD A,(DE)
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A = mem[r16->DE];
	r16->PC += 1;
}

void op_1e(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD E,d8
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E = mem[(r16->PC)+1];
	r16->PC += 2;
}

void op_21(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 16bit load/store/move instructions
		 instruction: LD HL,d16
		   num bytes: 3
		      cycles: 12
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r16->HL = *(uint16_t *)&mem[(r16->PC)+1];
	r16->PC += 3;
}

void op_22(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD (HL+),A
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[(r16->HL)++] = r8->A;
	r16->PC += 1;
}

void op_26(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD H,d8
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H = mem[(r16->PC)+1];
	r16->PC += 2;
}

void op_2a(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD A,(HL+)
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A = mem[(r16->HL)++];
	r16->PC += 1;
}

void op_2e(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD L,d8
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L = mem[(r16->PC)+1];
	r16->PC += 2;
}

void op_31(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 16bit load/store/move instructions
		 instruction: LD SP,d16
		   num bytes: 3
		      cycles: 12
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r16->SP = *(uint16_t *)&mem[(r16->PC)+1];
	r16->PC += 3;
}

void op_32(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD (HL-),A
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[(r16->HL)--] = r8->A;
	r16->PC += 1;
}

void op_36(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD (HL),d8
		   num bytes: 2
		      cycles: 12
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL] = mem[(r16->PC)+1];
	r16->PC += 2;
}

void op_3a(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD A,(HL-)
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A = mem[(r16->HL)--];
	r16->PC += 1;
}

void op_3e(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD A,d8
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A = mem[(r16->PC)+1];
	r16->PC += 2;
}

void op_40(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD B,B
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B = r8->B;
	r16->PC += 1;
}

void op_41(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD B,C
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B = r8->C;
	r16->PC += 1;
}

void op_42(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD B,D
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B = r8->D;
	r16->PC += 1;
}

void op_43(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD B,E
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B = r8->E;
	r16->PC += 1;
}

void op_44(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD B,H
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B = r8->H;
	r16->PC += 1;
}

void op_45(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD B,L
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B = r8->L;
	r16->PC += 1;
}

void op_46(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD B,(HL)
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B = mem[r16->HL];
	r16->PC += 1;
}

void op_47(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD B,A
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B = r8->A;
	r16->PC += 1;
}

void op_48(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD C,B
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C = r8->B;
	r16->PC += 1;
}

void op_49(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD C,C
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C = r8->C;
	r16->PC += 1;
}

void op_4a(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD C,D
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C = r8->D;
	r16->PC += 1;
}

void op_4b(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD C,E
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C = r8->E;
	r16->PC += 1;
}

void op_4c(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD C,H
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C = r8->H;
	r16->PC += 1;
}

void op_4d(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD C,L
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C = r8->L;
	r16->PC += 1;
}

void op_4e(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD C,(HL)
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C = mem[r16->HL];
	r16->PC += 1;
}

void op_4f(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD C,A
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C = r8->A;
	r16->PC += 1;
}

void op_50(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD D,B
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D = r8->B;
	r16->PC += 1;
}

void op_51(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD D,C
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D = r8->C;
	r16->PC += 1;
}

void op_52(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD D,D
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D = r8->D;
	r16->PC += 1;
}

void op_53(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD D,E
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D = r8->E;
	r16->PC += 1;
}

void op_54(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD D,H
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D = r8->H;
	r16->PC += 1;
}

void op_55(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD D,L
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D = r8->L;
	r16->PC += 1;
}

void op_56(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD D,(HL)
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D = mem[r16->HL];
	r16->PC += 1;
}

void op_57(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD D,A
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D = r8->A;
	r16->PC += 1;
}

void op_58(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD E,B
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E = r8->B;
	r16->PC += 1;
}

void op_59(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD E,C
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E = r8->C;
	r16->PC += 1;
}

void op_5a(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD E,D
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E = r8->D;
	r16->PC += 1;
}

void op_5b(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD E,E
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E = r8->E;
	r16->PC += 1;
}

void op_5c(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD E,H
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E = r8->H;
	r16->PC += 1;
}

void op_5d(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD E,L
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E = r8->L;
	r16->PC += 1;
}

void op_5e(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD E,(HL)
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E = mem[r16->HL];
	r16->PC += 1;
}

void op_5f(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD E,A
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E = r8->A;
	r16->PC += 1;
}

void op_60(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD H,B
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H = r8->B;
	r16->PC += 1;
}

void op_61(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD H,C
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H = r8->C;
	r16->PC += 1;
}

void op_62(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD H,D
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H = r8->D;
	r16->PC += 1;
}

void op_63(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD H,E
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H = r8->E;
	r16->PC += 1;
}

void op_64(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD H,H
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H = r8->H;
	r16->PC += 1;
}

void op_65(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD H,L
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H = r8->L;
	r16->PC += 1;
}

void op_66(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD H,(HL)
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H = mem[r16->HL];
	r16->PC += 1;
}

void op_67(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD H,A
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H = r8->A;
	r16->PC += 1;
}

void op_68(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD L,B
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L = r8->B;
	r16->PC += 1;
}

void op_69(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD L,C
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L = r8->C;
	r16->PC += 1;
}

void op_6a(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD L,D
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L = r8->D;
	r16->PC += 1;
}

void op_6b(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD L,E
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L = r8->E;
	r16->PC += 1;
}

void op_6c(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD L,H
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L = r8->H;
	r16->PC += 1;
}

void op_6d(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD L,L
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L = r8->L;
	r16->PC += 1;
}

void op_6e(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD L,(HL)
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L = mem[r16->HL];
	r16->PC += 1;
}

void op_6f(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD L,A
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L = r8->A;
	r16->PC += 1;
}

void op_70(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD (HL),B
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL] = r8->B;
	r16->PC += 1;
}

void op_71(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD (HL),C
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL] = r8->C;
	r16->PC += 1;
}

void op_72(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD (HL),D
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL] = r8->D;
	r16->PC += 1;
}

void op_73(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD (HL),E
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL] = r8->E;
	r16->PC += 1;
}

void op_74(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD (HL),H
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL] = r8->H;
	r16->PC += 1;
}

void op_75(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD (HL),L
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL] = r8->L;
	r16->PC += 1;
}

void op_77(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD (HL),A
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL] = r8->A;
	r16->PC += 1;
}

void op_78(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD A,B
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A = r8->B;
	r16->PC += 1;
}

void op_79(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD A,C
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A = r8->C;
	r16->PC += 1;
}

void op_7a(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD A,D
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A = r8->D;
	r16->PC += 1;
}

void op_7b(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD A,E
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A = r8->E;
	r16->PC += 1;
}

void op_7c(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD A,H
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A = r8->H;
	r16->PC += 1;
}

void op_7d(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD A,L
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A = r8->L;
	r16->PC += 1;
}

void op_7e(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD A,(HL)
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A = mem[r16->HL];
	r16->PC += 1;
}

void op_7f(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD A,A
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A = r8->A;
	r16->PC += 1;
}

void op_e2(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD (C),A
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[(0xff00)+r8->C] = r8->A;
	r16->PC += 1;
}

void op_ea(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD (a16),A
		   num bytes: 3
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint16_t a16 = *(uint16_t *)&mem[(r16->PC)+1];
	mem[a16] = r8->A;
	r16->PC += 3;
}

void op_f2(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD A,(C)
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A = mem[(0xff00)+r8->C];
	r16->PC += 2;
}

void op_f8(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 16bit load/store/move instructions
		 instruction: LD HL,SP+r8
		   num bytes: 2
		      cycles: 12
		       flags: 0 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	int offset = (int8_t)mem[(r16->PC)+1];
	r16->HL = (int)r16->SP + offset;
	clear_z_flag;
	clear_n_flag;
	(offset & 0xf) + (r16->HL & 0xf) > 0xf ? set_h_flag : clear_h_flag;
	(offset & 0xff) + (r16->HL & 0xff) > 0xff ? set_c_flag : clear_c_flag;
	r16->PC += 2;
}

void op_f9(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 16bit load/store/move instructions
		 instruction: LD SP,HL
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r16->SP = r16->HL;
	r16->PC += 1;
}

void op_fa(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD A,(a16)
		   num bytes: 3
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint16_t a16 = *(uint16_t *)&mem[(r16->PC)+1];
	r8->A = mem[a16];
	r16->PC += 3;
}

