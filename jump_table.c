#include "gb.h"

void op_88(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADC A,B
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	uint32_t calc;
	op = r8->B;
	calc = r8->A + op + is_c_flag;
	(calc & 0xff) == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	is_c_flag + (r8->A & 0xf) + (op & 0xf) > 0xf ? set_h_flag : clear_h_flag;
	is_c_flag + calc > 0xff ? set_c_flag : clear_c_flag;
	r8->A = r8->A + op + is_c_flag;
	r16->PC += 1;
}

void op_89(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADC A,C
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	uint32_t calc;
	op = r8->C;
	calc = r8->A + op + is_c_flag;
	(calc & 0xff) == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	is_c_flag + (r8->A & 0xf) + (op & 0xf) > 0xf ? set_h_flag : clear_h_flag;
	is_c_flag + calc > 0xff ? set_c_flag : clear_c_flag;
	r8->A = r8->A + op + is_c_flag;
	r16->PC += 1;
}

void op_8a(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADC A,D
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	uint32_t calc;
	op = r8->D;
	calc = r8->A + op + is_c_flag;
	(calc & 0xff) == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	is_c_flag + (r8->A & 0xf) + (op & 0xf) > 0xf ? set_h_flag : clear_h_flag;
	is_c_flag + calc > 0xff ? set_c_flag : clear_c_flag;
	r8->A = r8->A + op + is_c_flag;
	r16->PC += 1;
}

void op_8b(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADC A,E
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	uint32_t calc;
	op = r8->E;
	calc = r8->A + op + is_c_flag;
	(calc & 0xff) == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	is_c_flag + (r8->A & 0xf) + (op & 0xf) > 0xf ? set_h_flag : clear_h_flag;
	is_c_flag + calc > 0xff ? set_c_flag : clear_c_flag;
	r8->A = r8->A + op + is_c_flag;
	r16->PC += 1;
}

void op_8c(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADC A,H
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	uint32_t calc;
	op = r8->H;
	calc = r8->A + op + is_c_flag;
	(calc & 0xff) == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	is_c_flag + (r8->A & 0xf) + (op & 0xf) > 0xf ? set_h_flag : clear_h_flag;
	is_c_flag + calc > 0xff ? set_c_flag : clear_c_flag;
	r8->A = r8->A + op + is_c_flag;
	r16->PC += 1;
}

void op_8d(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADC A,L
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	uint32_t calc;
	op = r8->L;
	calc = r8->A + op + is_c_flag;
	(calc & 0xff) == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	is_c_flag + (r8->A & 0xf) + (op & 0xf) > 0xf ? set_h_flag : clear_h_flag;
	is_c_flag + calc > 0xff ? set_c_flag : clear_c_flag;
	r8->A = r8->A + op + is_c_flag;
	r16->PC += 1;
}

void op_8e(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADC A,(HL)
		   num bytes: 1
		      cycles: 8
		       flags: Z 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	uint32_t calc;
	op = mem[r16->HL];
	calc = r8->A + op + is_c_flag;
	(calc & 0xff) == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	is_c_flag + (r8->A & 0xf) + (op & 0xf) > 0xf ? set_h_flag : clear_h_flag;
	is_c_flag + calc > 0xff ? set_c_flag : clear_c_flag;
	r8->A = r8->A + op + is_c_flag;
	r16->PC += 1;
}

void op_8f(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADC A,A
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	uint32_t calc;
	op = r8->A;
	calc = r8->A + op + is_c_flag;
	(calc & 0xff) == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	is_c_flag + (r8->A & 0xf) + (op & 0xf) > 0xf ? set_h_flag : clear_h_flag;
	is_c_flag + calc > 0xff ? set_c_flag : clear_c_flag;
	r8->A = r8->A + op + is_c_flag;
	r16->PC += 1;
}

void op_ce(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADC A,d8
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	uint32_t calc;
	op = mem[(r16->PC)+1];
	calc = r8->A + op + is_c_flag;
	(calc & 0xff) == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	is_c_flag + (r8->A & 0xf) + (op & 0xf) > 0xf ? set_h_flag : clear_h_flag;
	is_c_flag + calc > 0xff ? set_c_flag : clear_c_flag;
	r8->A = r8->A + op + is_c_flag;
	r16->PC += 2;
}



void op_09(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 16bit arithmetic/logical instructions
		 instruction: ADD HL,BC
		   num bytes: 1
		      cycles: 8
		       flags: - 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint16_t op;
	uint32_t calc;
	clear_n_flag;
	op = r16->BC;
	(r16->HL & 0xfff) + (op & 0xfff) > 0xfff ? set_h_flag : clear_h_flag;
	calc = r16->HL + op;
	calc > 0xffff ? set_c_flag : clear_c_flag;
	r16->HL += op;
	r16->PC += 1;
}

void op_19(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 16bit arithmetic/logical instructions
		 instruction: ADD HL,DE
		   num bytes: 1
		      cycles: 8
		       flags: - 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint16_t op;
	uint32_t calc;
	clear_n_flag;
	op = r16->DE;
	(r16->HL & 0xfff) + (op & 0xfff) > 0xfff ? set_h_flag : clear_h_flag;
	calc = r16->HL + op;
	calc > 0xffff ? set_c_flag : clear_c_flag;
	r16->HL += op;
	r16->PC += 1;
}

void op_29(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 16bit arithmetic/logical instructions
		 instruction: ADD HL,HL
		   num bytes: 1
		      cycles: 8
		       flags: - 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint16_t op;
	uint32_t calc;
	clear_n_flag;
	op = r16->HL;
	(r16->HL & 0xfff) + (op & 0xfff) > 0xfff ? set_h_flag : clear_h_flag;
	calc = r16->HL + op;
	calc > 0xffff ? set_c_flag : clear_c_flag;
	r16->HL += op;
	r16->PC += 1;
}

void op_39(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 16bit arithmetic/logical instructions
		 instruction: ADD HL,SP
		   num bytes: 1
		      cycles: 8
		       flags: - 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint16_t op;
	uint32_t calc;
	clear_n_flag;
	op = r16->SP;
	(r16->HL & 0xfff) + (op & 0xfff) > 0xfff ? set_h_flag : clear_h_flag;
	calc = r16->HL + op;
	calc > 0xffff ? set_c_flag : clear_c_flag;
	r16->HL += op;
	r16->PC += 1;
}

void op_80(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADD A,B
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	uint32_t calc;
	op = r8->B;
	calc = r8->A + op;
	(calc & 0xff) == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	(r8->A & 0xf) + (op & 0xf) > 0xf ? set_h_flag : clear_h_flag;
	calc > 0xff ? set_c_flag : clear_c_flag;
	r8->A += op;
	r16->PC += 1;
}

void op_81(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADD A,C
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	uint32_t calc;
	op = r8->C;
	calc = r8->A + op;
	(calc & 0xff) == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	(r8->A & 0xf) + (op & 0xf) > 0xf ? set_h_flag : clear_h_flag;
	calc > 0xff ? set_c_flag : clear_c_flag;
	r8->A += op;
	r16->PC += 1;
}

void op_82(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADD A,D
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	uint32_t calc;
	op = r8->D;
	calc = r8->A + op;
	(calc & 0xff) == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	(r8->A & 0xf) + (op & 0xf) > 0xf ? set_h_flag : clear_h_flag;
	calc > 0xff ? set_c_flag : clear_c_flag;
	r8->A += op;
	r16->PC += 1;
}

void op_83(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADD A,E
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	uint32_t calc;
	op = r8->E;
	calc = r8->A + op;
	(calc & 0xff) == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	(r8->A & 0xf) + (op & 0xf) > 0xf ? set_h_flag : clear_h_flag;
	calc > 0xff ? set_c_flag : clear_c_flag;
	r8->A += op;
	r16->PC += 1;
}

void op_84(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADD A,H
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	uint32_t calc;
	op = r8->H;
	calc = r8->A + op;
	(calc & 0xff) == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	(r8->A & 0xf) + (op & 0xf) > 0xf ? set_h_flag : clear_h_flag;
	calc > 0xff ? set_c_flag : clear_c_flag;
	r8->A += op;
	r16->PC += 1;
}

void op_85(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADD A,L
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	uint32_t calc;
	op = r8->L;
	calc = r8->A + op;
	(calc & 0xff) == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	(r8->A & 0xf) + (op & 0xf) > 0xf ? set_h_flag : clear_h_flag;
	calc > 0xff ? set_c_flag : clear_c_flag;
	r8->A += op;
	r16->PC += 1;
}

void op_86(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADD A,(HL)
		   num bytes: 1
		      cycles: 8
		       flags: Z 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	uint32_t calc;
	op = mem[r16->HL];
	calc = r8->A + op;
	(calc & 0xff) == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	(r8->A & 0xf) + (op & 0xf) > 0xf ? set_h_flag : clear_h_flag;
	calc > 0xff ? set_c_flag : clear_c_flag;
	r8->A += op;
	r16->PC += 1;
}

void op_87(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADD A,A
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	uint32_t calc;
	op = r8->A;
	calc = r8->A + op;
	(calc & 0xff) == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	(r8->A & 0xf) + (op & 0xf) > 0xf ? set_h_flag : clear_h_flag;
	calc > 0xff ? set_c_flag : clear_c_flag;
	r8->A += op;
	r16->PC += 1;
}

void op_c6(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADD A,d8
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	uint32_t calc;
	op = mem[(r16->PC)+1];
	calc = r8->A + op;
	(calc & 0xff) == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	(r8->A & 0xf) + (op & 0xf) > 0xf ? set_h_flag : clear_h_flag;
	calc > 0xff ? set_c_flag : clear_c_flag;
	r8->A += op;
	r16->PC += 2;
}

void op_e8(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 16bit arithmetic/logical instructions
		 instruction: ADD SP,r8
		   num bytes: 2
		      cycles: 16
		       flags: 0 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	clear_z_flag;
	clear_n_flag;
	int16_t op = (int8_t)mem[(r16->PC)+1];
	(r16->SP & 0xf) + (op & 0xf) > 0xf ? set_h_flag : clear_h_flag;
	(r16->SP & 0xff) + (op & 0xff) > 0xff ? set_c_flag : clear_c_flag;
	r16->SP += op;
	r16->PC += 2;
}



void op_a0(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: AND B
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 1 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->B;
	r8->A &= op;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	set_h_flag;
	clear_c_flag;
	r16->PC += 1;
}

void op_a1(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: AND C
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 1 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->C;
	r8->A &= op;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	set_h_flag;
	clear_c_flag;
	r16->PC += 1;
}

void op_a2(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: AND D
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 1 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->D;
	r8->A &= op;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	set_h_flag;
	clear_c_flag;
	r16->PC += 1;
}

void op_a3(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: AND E
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 1 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->E;
	r8->A &= op;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	set_h_flag;
	clear_c_flag;
	r16->PC += 1;
}

void op_a4(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: AND H
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 1 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->H;
	r8->A &= op;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	set_h_flag;
	clear_c_flag;
	r16->PC += 1;
}

void op_a5(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: AND L
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 1 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->L;
	r8->A &= op;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	set_h_flag;
	clear_c_flag;
	r16->PC += 1;
}

void op_a6(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: AND (HL)
		   num bytes: 1
		      cycles: 8
		       flags: Z 0 1 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = mem[r16->HL];
	r8->A &= op;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	set_h_flag;
	clear_c_flag;
	r16->PC += 1;
}

void op_a7(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: AND A
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 1 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->A;
	r8->A &= op;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	set_h_flag;
	clear_c_flag;
	r16->PC += 1;
}

void op_e6(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: AND d8
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = mem[(r16->PC)+1];
	r8->A &= op;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	set_h_flag;
	clear_c_flag;
	r16->PC += 2;
}



void op_cb40(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 0,B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B & (1 << 0) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb41(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 0,C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C & (1 << 0) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb42(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 0,D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D & (1 << 0) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb43(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 0,E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E & (1 << 0) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb44(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 0,H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H & (1 << 0) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb45(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 0,L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L & (1 << 0) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb46(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 0,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL] & (1 << 0) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb47(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 0,A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A & (1 << 0) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb48(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 1,B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B & (1 << 1) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb49(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 1,C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C & (1 << 1) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb4a(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 1,D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D & (1 << 1) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb4b(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 1,E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E & (1 << 1) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb4c(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 1,H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H & (1 << 1) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb4d(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 1,L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L & (1 << 1) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb4e(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 1,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL] & (1 << 1) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb4f(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 1,A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A & (1 << 1) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb50(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 2,B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B & (1 << 2) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb51(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 2,C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C & (1 << 2) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb52(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 2,D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D & (1 << 2) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb53(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 2,E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E & (1 << 2) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb54(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 2,H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H & (1 << 2) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb55(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 2,L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L & (1 << 2) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb56(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 2,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL] & (1 << 2) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb57(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 2,A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A & (1 << 2) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb58(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 3,B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B & (1 << 3) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb59(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 3,C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C & (1 << 3) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb5a(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 3,D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D & (1 << 3) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb5b(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 3,E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E & (1 << 3) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb5c(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 3,H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H & (1 << 3) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb5d(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 3,L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L & (1 << 3) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb5e(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 3,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL] & (1 << 3) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb5f(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 3,A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A & (1 << 3) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb60(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 4,B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B & (1 << 4) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb61(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 4,C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C & (1 << 4) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb62(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 4,D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D & (1 << 4) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb63(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 4,E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E & (1 << 4) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb64(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 4,H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H & (1 << 4) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb65(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 4,L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L & (1 << 4) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb66(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 4,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL] & (1 << 4) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb67(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 4,A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A & (1 << 4) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb68(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 5,B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B & (1 << 5) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb69(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 5,C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C & (1 << 5) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb6a(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 5,D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D & (1 << 5) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb6b(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 5,E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E & (1 << 5) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb6c(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 5,H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H & (1 << 5) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb6d(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 5,L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L & (1 << 5) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb6e(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 5,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL] & (1 << 5) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb6f(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 5,A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A & (1 << 5) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb70(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 6,B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B & (1 << 6) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb71(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 6,C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C & (1 << 6) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb72(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 6,D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D & (1 << 6) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb73(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 6,E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E & (1 << 6) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb74(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 6,H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H & (1 << 6) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb75(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 6,L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L & (1 << 6) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb76(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 6,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL] & (1 << 6) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb77(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 6,A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A & (1 << 6) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb78(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 7,B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B & (1 << 7) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb79(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 7,C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C & (1 << 7) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb7a(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 7,D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D & (1 << 7) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb7b(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 7,E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E & (1 << 7) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb7c(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 7,H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H & (1 << 7) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb7d(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 7,L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L & (1 << 7) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb7e(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 7,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL] & (1 << 7) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb7f(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 7,A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A & (1 << 7) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}



void op_c4(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: CALL NZ,a16
		   num bytes: 3
		      cycles: 24/12
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	if (is_z_flag)  { r16->PC += 3; return; };
	r16->SP -= 2;
	mem[r16->SP] = r16->PC + 3;
	r16->PC = mem[r16->PC + 1];
}

void op_cc(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: CALL Z,a16
		   num bytes: 3
		      cycles: 24/12
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	if (!is_z_flag)  { r16->PC += 3; return; };
	r16->SP -= 2;
	mem[r16->SP] = r16->PC + 3;
	r16->PC = mem[r16->PC + 1];
}

void op_cd(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: CALL a16
		   num bytes: 3
		      cycles: 24
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r16->SP -= 2;
	mem[r16->SP] = r16->PC + 3;
	r16->PC = mem[r16->PC + 1];
}

void op_d4(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: CALL NC,a16
		   num bytes: 3
		      cycles: 24/12
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	if (is_c_flag)  { r16->PC += 3; return; };
	r16->SP -= 2;
	mem[r16->SP] = r16->PC + 3;
	r16->PC = mem[r16->PC + 1];
}

void op_dc(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: CALL C,a16
		   num bytes: 3
		      cycles: 24/12
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	if (!is_c_flag) { r16->PC += 3; return; };
	r16->SP -= 2;
	mem[r16->SP] = r16->PC + 3;
	r16->PC = mem[r16->PC + 1];
}



void op_3f(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: CCF
		   num bytes: 1
		      cycles: 4
		       flags: - 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	is_c_flag ? clear_c_flag : set_c_flag;
	clear_n_flag;
	clear_h_flag;
	r16->PC += 1;
}



void op_b8(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: CP B
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->B;
	r8->A == op ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) < (op & 0xf) ? set_h_flag : clear_h_flag;
	r8->A < op ? set_c_flag : clear_c_flag;
	r16->PC += 1;
}

void op_b9(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: CP C
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->C;
	r8->A == op ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) < (op & 0xf) ? set_h_flag : clear_h_flag;
	r8->A < op ? set_c_flag : clear_c_flag;
	r16->PC += 1;
}

void op_ba(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: CP D
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->D;
	r8->A == op ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) < (op & 0xf) ? set_h_flag : clear_h_flag;
	r8->A < op ? set_c_flag : clear_c_flag;
	r16->PC += 1;
}

void op_bb(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: CP E
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->E;
	r8->A == op ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) < (op & 0xf) ? set_h_flag : clear_h_flag;
	r8->A < op ? set_c_flag : clear_c_flag;
	r16->PC += 1;
}

void op_bc(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: CP H
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->H;
	r8->A == op ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) < (op & 0xf) ? set_h_flag : clear_h_flag;
	r8->A < op ? set_c_flag : clear_c_flag;
	r16->PC += 1;
}

void op_bd(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: CP L
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->L;
	r8->A == op ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) < (op & 0xf) ? set_h_flag : clear_h_flag;
	r8->A < op ? set_c_flag : clear_c_flag;
	r16->PC += 1;
}

void op_be(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: CP (HL)
		   num bytes: 1
		      cycles: 8
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = mem[r16->HL];
	r8->A == op ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) < (op & 0xf) ? set_h_flag : clear_h_flag;
	r8->A < op ? set_c_flag : clear_c_flag;
	r16->PC += 1;
}

void op_bf(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: CP A
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->A;
	r8->A == op ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) < (op & 0xf) ? set_h_flag : clear_h_flag;
	r8->A < op ? set_c_flag : clear_c_flag;
	r16->PC += 1;
}

void op_fe(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: CP d8
		   num bytes: 2
		      cycles: 8
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = mem[(r16->PC)+1];
	r8->A == op ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) < (op & 0xf) ? set_h_flag : clear_h_flag;
	r8->A < op ? set_c_flag : clear_c_flag;
	r16->PC += 2;
}



void op_2f(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: CPL
		   num bytes: 1
		      cycles: 4
		       flags: - 1 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A = (~r8->A);
	set_n_flag;
	set_h_flag;
	r16->PC += 1;
}



void op_27(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: DAA
		   num bytes: 1
		      cycles: 4
		       flags: Z - 0 C
	*/

}



void op_05(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: DEC B
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B--;
	r8->B == 0 ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->B & 0xf) == 0xf ? set_h_flag : clear_h_flag;
	r16->PC += 1;
}

void op_0b(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 16bit arithmetic/logical instructions
		 instruction: DEC BC
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r16->BC--;
	r16->PC += 1;
}

void op_0d(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: DEC C
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C--;
	r8->C == 0 ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->C & 0xf) == 0xf ? set_h_flag : clear_h_flag;
	r16->PC += 1;
}

void op_15(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: DEC D
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D--;
	r8->D == 0 ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->D & 0xf) == 0xf ? set_h_flag : clear_h_flag;
	r16->PC += 1;
}

void op_1b(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 16bit arithmetic/logical instructions
		 instruction: DEC DE
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r16->DE--;
	r16->PC += 1;
}

void op_1d(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: DEC E
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E--;
	r8->E == 0 ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->E & 0xf) == 0xf ? set_h_flag : clear_h_flag;
	r16->PC += 1;
}

void op_25(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: DEC H
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H--;
	r8->H == 0 ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->H & 0xf) == 0xf ? set_h_flag : clear_h_flag;
	r16->PC += 1;
}

void op_2b(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 16bit arithmetic/logical instructions
		 instruction: DEC HL
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r16->HL--;
	r16->PC += 1;
}

void op_2d(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: DEC L
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L--;
	r8->L == 0 ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->L & 0xf) == 0xf ? set_h_flag : clear_h_flag;
	r16->PC += 1;
}

void op_35(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: DEC (HL)
		   num bytes: 1
		      cycles: 12
		       flags: Z 1 H -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL]--;
	mem[r16->HL] == 0 ? set_z_flag : clear_z_flag;
	set_n_flag;
	(mem[r16->HL] & 0xf) == 0xf ? set_h_flag : clear_h_flag;
	r16->PC += 1;
}

void op_3b(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 16bit arithmetic/logical instructions
		 instruction: DEC SP
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r16->SP--;
	r16->PC += 1;
}

void op_3d(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: DEC A
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A--;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) == 0xf ? set_h_flag : clear_h_flag;
	r16->PC += 1;
}



void op_f3(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Misc/control instructions
		 instruction: DI
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	state->interrupts_enabled = false;
	r16->PC += 1;
}



void op_fb(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Misc/control instructions
		 instruction: EI
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	state->interrupts_enabled = true;
	r16->PC += 1;
}



void op_76(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Misc/control instructions
		 instruction: HALT
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r16->PC += 1;
	state->halt = true;
}



void op_03(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 16bit arithmetic/logical instructions
		 instruction: INC BC
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r16->BC++;
	r16->PC += 1;
}

void op_04(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: INC B
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B++;
	r8->B == 0 ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->B & 0xf) == 0x0 ? set_h_flag : clear_h_flag;
	r16->PC += 1;
}

void op_0c(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: INC C
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C++;
	r8->C == 0 ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->C & 0xf) == 0x0 ? set_h_flag : clear_h_flag;
	r16->PC += 1;
}

void op_13(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 16bit arithmetic/logical instructions
		 instruction: INC DE
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r16->DE++;
	r16->PC += 1;
}

void op_14(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: INC D
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D++;
	r8->D == 0 ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->D & 0xf) == 0x0 ? set_h_flag : clear_h_flag;
	r16->PC += 1;
}

void op_1c(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: INC E
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E++;
	r8->E == 0 ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->E & 0xf) == 0x0 ? set_h_flag : clear_h_flag;
	r16->PC += 1;
}

void op_23(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 16bit arithmetic/logical instructions
		 instruction: INC HL
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r16->HL++;
	r16->PC += 1;
}

void op_24(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: INC H
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H++;
	r8->H == 0 ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->H & 0xf) == 0x0 ? set_h_flag : clear_h_flag;
	r16->PC += 1;
}

void op_2c(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: INC L
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L++;
	r8->L == 0 ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->L & 0xf) == 0x0 ? set_h_flag : clear_h_flag;
	r16->PC += 1;
}

void op_33(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 16bit arithmetic/logical instructions
		 instruction: INC SP
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r16->SP++;
	r16->PC += 1;
}

void op_34(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: INC (HL)
		   num bytes: 1
		      cycles: 12
		       flags: Z 0 H -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL]++;
	mem[r16->HL] == 0 ? set_z_flag : clear_z_flag;
	set_n_flag;
	(mem[r16->HL] & 0xf) == 0x0 ? set_h_flag : clear_h_flag;
	r16->PC += 1;
}

void op_3c(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: INC A
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A++;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) == 0x0 ? set_h_flag : clear_h_flag;
	r16->PC += 1;
}



void op_c2(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: JP NZ,a16
		   num bytes: 3
		      cycles: 16/12
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	if (is_z_flag)  { r16->PC += 3; return; };
	r16->PC = mem[r16->PC + 1];
}

void op_c3(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: JP a16
		   num bytes: 3
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r16->PC = mem[r16->PC + 1];
}

void op_ca(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: JP Z,a16
		   num bytes: 3
		      cycles: 16/12
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	if (!is_z_flag)  { r16->PC += 3; return; };
	r16->PC = mem[r16->PC + 1];
}

void op_d2(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: JP NC,a16
		   num bytes: 3
		      cycles: 16/12
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	if (is_c_flag)  { r16->PC += 3; return; };
	r16->PC = mem[r16->PC + 1];
}

void op_da(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: JP C,a16
		   num bytes: 3
		      cycles: 16/12
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	if (!is_c_flag) { r16->PC += 3; return; };
	r16->PC = mem[r16->PC + 1];
}

void op_e9(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: JP (HL)
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r16->PC = r16->HL;
}



void op_18(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: JR r8
		   num bytes: 2
		      cycles: 12
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	   r16->PC += (int8_t)mem[r16->PC + 1];
	r16->PC += 2;
}

void op_20(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: JR NZ,r8
		   num bytes: 2
		      cycles: 12/8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	if (!is_z_flag)
	   r16->PC += (int8_t)mem[r16->PC + 1];
	r16->PC += 2;
}

void op_28(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: JR Z,r8
		   num bytes: 2
		      cycles: 12/8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	if (is_z_flag)
	   r16->PC += (int8_t)mem[r16->PC + 1];
	r16->PC += 2;
}

void op_30(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: JR NC,r8
		   num bytes: 2
		      cycles: 12/8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	if (!is_c_flag)
	   r16->PC += (int8_t)mem[r16->PC + 1];
	r16->PC += 2;
}

void op_38(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: JR C,r8
		   num bytes: 2
		      cycles: 12/8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	if (is_c_flag)
	   r16->PC += (int8_t)mem[r16->PC + 1];
	r16->PC += 2;
}



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
	r16->BC = (uint16_t)mem[(r16->PC)+1];
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
	uint16_t a16 = mem[(r16->PC)+1];
	mem[a16] = r16->SP;
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
	r16->DE = (uint16_t)mem[(r16->PC)+1];
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
	r16->HL = (uint16_t)mem[(r16->PC)+1];
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
	r16->SP = (uint16_t)mem[(r16->PC)+1];
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
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[(0xff00)+r8->C] = r8->A;
	r16->PC += 2;
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
	uint16_t a16 = mem[(r16->PC)+1];
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
	uint16_t a16 = mem[(r16->PC)+1];
	r8->A = mem[a16];
	r16->PC += 3;
}



void op_e0(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LDH (a8),A
		   num bytes: 2
		      cycles: 12
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t a8 = mem[(r16->PC)+1];
	mem[0xff00 + a8] = r8->A;
	r16->PC += 2;
}

void op_f0(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LDH A,(a8)
		   num bytes: 2
		      cycles: 12
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t a8 = mem[(r16->PC)+1];
	r8->A = mem[0xff00 + a8];
	r16->PC += 2;
}



void op_00(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Misc/control instructions
		 instruction: NOP
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r16->PC += 1;
}



void op_b0(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: OR B
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A |= r8->B;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
	r16->PC += 1;
}

void op_b1(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: OR C
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A |= r8->C;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
	r16->PC += 1;
}

void op_b2(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: OR D
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A |= r8->D;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
	r16->PC += 1;
}

void op_b3(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: OR E
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A |= r8->E;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
	r16->PC += 1;
}

void op_b4(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: OR H
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A |= r8->H;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
	r16->PC += 1;
}

void op_b5(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: OR L
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A |= r8->L;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
	r16->PC += 1;
}

void op_b6(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: OR (HL)
		   num bytes: 1
		      cycles: 8
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A |= mem[r16->HL];
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
	r16->PC += 1;
}

void op_b7(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: OR A
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A |= r8->A;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
	r16->PC += 1;
}

void op_f6(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: OR d8
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A |= mem[(r16->PC)+1];
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
	r16->PC += 2;
}



void op_c1(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 16bit load/store/move instructions
		 instruction: POP BC
		   num bytes: 1
		      cycles: 12
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r16->BC = mem[r16->SP];
	r16->SP += 2;
	r16->PC += 1;
}

void op_d1(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 16bit load/store/move instructions
		 instruction: POP DE
		   num bytes: 1
		      cycles: 12
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r16->DE = mem[r16->SP];
	r16->SP += 2;
	r16->PC += 1;
}

void op_e1(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 16bit load/store/move instructions
		 instruction: POP HL
		   num bytes: 1
		      cycles: 12
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r16->HL = mem[r16->SP];
	r16->SP += 2;
	r16->PC += 1;
}

void op_f1(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 16bit load/store/move instructions
		 instruction: POP AF
		   num bytes: 1
		      cycles: 12
		       flags: Z N H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r16->AF = mem[r16->SP];
	r16->SP += 2;
	r16->PC += 1;
}



void op_cb(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Misc/control instructions
		 instruction: PREFIX CB
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}



void op_c5(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 16bit load/store/move instructions
		 instruction: PUSH BC
		   num bytes: 1
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->SP] = r16->BC;
	r16->SP -= 2;
	r16->PC += 1;
}

void op_d5(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 16bit load/store/move instructions
		 instruction: PUSH DE
		   num bytes: 1
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->SP] = r16->DE;
	r16->SP -= 2;
	r16->PC += 1;
}

void op_e5(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 16bit load/store/move instructions
		 instruction: PUSH HL
		   num bytes: 1
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->SP] = r16->HL;
	r16->SP -= 2;
	r16->PC += 1;
}

void op_f5(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 16bit load/store/move instructions
		 instruction: PUSH AF
		   num bytes: 1
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->SP] = r16->AF;
	r16->SP -= 2;
	r16->PC += 1;
}



void op_cb80(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 0,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B &= ~(1 << 0);
	r16->PC += 2;
}

void op_cb81(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 0,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C &= ~(1 << 0);
	r16->PC += 2;
}

void op_cb82(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 0,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D &= ~(1 << 0);
	r16->PC += 2;
}

void op_cb83(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 0,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E &= ~(1 << 0);
	r16->PC += 2;
}

void op_cb84(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 0,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H &= ~(1 << 0);
	r16->PC += 2;
}

void op_cb85(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 0,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L &= ~(1 << 0);
	r16->PC += 2;
}

void op_cb86(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 0,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL] &= ~(1 << 0);
	r16->PC += 2;
}

void op_cb87(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 0,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A &= ~(1 << 0);
	r16->PC += 2;
}

void op_cb88(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 1,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B &= ~(1 << 1);
	r16->PC += 2;
}

void op_cb89(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 1,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C &= ~(1 << 1);
	r16->PC += 2;
}

void op_cb8a(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 1,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D &= ~(1 << 1);
	r16->PC += 2;
}

void op_cb8b(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 1,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E &= ~(1 << 1);
	r16->PC += 2;
}

void op_cb8c(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 1,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H &= ~(1 << 1);
	r16->PC += 2;
}

void op_cb8d(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 1,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L &= ~(1 << 1);
	r16->PC += 2;
}

void op_cb8e(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 1,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL] &= ~(1 << 1);
	r16->PC += 2;
}

void op_cb8f(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 1,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A &= ~(1 << 1);
	r16->PC += 2;
}

void op_cb90(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 2,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B &= ~(1 << 2);
	r16->PC += 2;
}

void op_cb91(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 2,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C &= ~(1 << 2);
	r16->PC += 2;
}

void op_cb92(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 2,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D &= ~(1 << 2);
	r16->PC += 2;
}

void op_cb93(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 2,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E &= ~(1 << 2);
	r16->PC += 2;
}

void op_cb94(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 2,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H &= ~(1 << 2);
	r16->PC += 2;
}

void op_cb95(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 2,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L &= ~(1 << 2);
	r16->PC += 2;
}

void op_cb96(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 2,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL] &= ~(1 << 2);
	r16->PC += 2;
}

void op_cb97(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 2,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A &= ~(1 << 2);
	r16->PC += 2;
}

void op_cb98(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 3,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B &= ~(1 << 3);
	r16->PC += 2;
}

void op_cb99(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 3,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C &= ~(1 << 3);
	r16->PC += 2;
}

void op_cb9a(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 3,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D &= ~(1 << 3);
	r16->PC += 2;
}

void op_cb9b(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 3,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E &= ~(1 << 3);
	r16->PC += 2;
}

void op_cb9c(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 3,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H &= ~(1 << 3);
	r16->PC += 2;
}

void op_cb9d(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 3,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L &= ~(1 << 3);
	r16->PC += 2;
}

void op_cb9e(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 3,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL] &= ~(1 << 3);
	r16->PC += 2;
}

void op_cb9f(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 3,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A &= ~(1 << 3);
	r16->PC += 2;
}

void op_cba0(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 4,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B &= ~(1 << 4);
	r16->PC += 2;
}

void op_cba1(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 4,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C &= ~(1 << 4);
	r16->PC += 2;
}

void op_cba2(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 4,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D &= ~(1 << 4);
	r16->PC += 2;
}

void op_cba3(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 4,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E &= ~(1 << 4);
	r16->PC += 2;
}

void op_cba4(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 4,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H &= ~(1 << 4);
	r16->PC += 2;
}

void op_cba5(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 4,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L &= ~(1 << 4);
	r16->PC += 2;
}

void op_cba6(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 4,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL] &= ~(1 << 4);
	r16->PC += 2;
}

void op_cba7(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 4,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A &= ~(1 << 4);
	r16->PC += 2;
}

void op_cba8(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 5,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B &= ~(1 << 5);
	r16->PC += 2;
}

void op_cba9(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 5,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C &= ~(1 << 5);
	r16->PC += 2;
}

void op_cbaa(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 5,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D &= ~(1 << 5);
	r16->PC += 2;
}

void op_cbab(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 5,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E &= ~(1 << 5);
	r16->PC += 2;
}

void op_cbac(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 5,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H &= ~(1 << 5);
	r16->PC += 2;
}

void op_cbad(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 5,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L &= ~(1 << 5);
	r16->PC += 2;
}

void op_cbae(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 5,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL] &= ~(1 << 5);
	r16->PC += 2;
}

void op_cbaf(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 5,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A &= ~(1 << 5);
	r16->PC += 2;
}

void op_cbb0(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 6,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B &= ~(1 << 6);
	r16->PC += 2;
}

void op_cbb1(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 6,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C &= ~(1 << 6);
	r16->PC += 2;
}

void op_cbb2(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 6,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D &= ~(1 << 6);
	r16->PC += 2;
}

void op_cbb3(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 6,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E &= ~(1 << 6);
	r16->PC += 2;
}

void op_cbb4(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 6,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H &= ~(1 << 6);
	r16->PC += 2;
}

void op_cbb5(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 6,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L &= ~(1 << 6);
	r16->PC += 2;
}

void op_cbb6(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 6,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL] &= ~(1 << 6);
	r16->PC += 2;
}

void op_cbb7(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 6,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A &= ~(1 << 6);
	r16->PC += 2;
}

void op_cbb8(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 7,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B &= ~(1 << 7);
	r16->PC += 2;
}

void op_cbb9(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 7,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C &= ~(1 << 7);
	r16->PC += 2;
}

void op_cbba(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 7,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D &= ~(1 << 7);
	r16->PC += 2;
}

void op_cbbb(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 7,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E &= ~(1 << 7);
	r16->PC += 2;
}

void op_cbbc(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 7,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H &= ~(1 << 7);
	r16->PC += 2;
}

void op_cbbd(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 7,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L &= ~(1 << 7);
	r16->PC += 2;
}

void op_cbbe(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 7,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL] &= ~(1 << 7);
	r16->PC += 2;
}

void op_cbbf(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 7,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A &= ~(1 << 7);
	r16->PC += 2;
}



void op_c0(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: RET NZ
		   num bytes: 1
		      cycles: 20/8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	if (!is_z_flag)
	{ r16->PC = mem[r16->SP]; r16->SP += 2; return ; }
	r16->PC += 1;
}

void op_c8(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: RET Z
		   num bytes: 1
		      cycles: 20/8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	if (is_z_flag)
	{ r16->PC = mem[r16->SP]; r16->SP += 2; return ; }
	r16->PC += 1;
}

void op_c9(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: RET
		   num bytes: 1
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r16->PC = mem[r16->SP]; r16->SP += 2; return ;
}

void op_d0(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: RET NC
		   num bytes: 1
		      cycles: 20/8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	if (!is_c_flag)
	{ r16->PC = mem[r16->SP]; r16->SP += 2; return ; }
	r16->PC += 1;
}

void op_d8(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: RET C
		   num bytes: 1
		      cycles: 20/8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	if (is_c_flag)
	{ r16->PC = mem[r16->SP]; r16->SP += 2; return ; }
	r16->PC += 1;
}



void op_d9(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: RETI
		   num bytes: 1
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r16->PC = mem[r16->SP];
	r16->SP += 2;
	state->interrupts_enabled = true;
}



void op_cb10(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RL B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t carry = is_c_flag;
	r8->B & 0x80 ? set_c_flag : clear_c_flag;
	r8->B = (r8->B << 1) | carry;
	clear_n_flag;
	clear_h_flag;
	r8->B == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb11(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RL C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t carry = is_c_flag;
	r8->C & 0x80 ? set_c_flag : clear_c_flag;
	r8->C = (r8->C << 1) | carry;
	clear_n_flag;
	clear_h_flag;
	r8->C == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb12(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RL D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t carry = is_c_flag;
	r8->D & 0x80 ? set_c_flag : clear_c_flag;
	r8->D = (r8->D << 1) | carry;
	clear_n_flag;
	clear_h_flag;
	r8->D == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb13(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RL E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t carry = is_c_flag;
	r8->E & 0x80 ? set_c_flag : clear_c_flag;
	r8->E = (r8->E << 1) | carry;
	clear_n_flag;
	clear_h_flag;
	r8->E == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb14(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RL H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t carry = is_c_flag;
	r8->H & 0x80 ? set_c_flag : clear_c_flag;
	r8->H = (r8->H << 1) | carry;
	clear_n_flag;
	clear_h_flag;
	r8->H == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb15(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RL L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t carry = is_c_flag;
	r8->L & 0x80 ? set_c_flag : clear_c_flag;
	r8->L = (r8->L << 1) | carry;
	clear_n_flag;
	clear_h_flag;
	r8->L == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb16(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RL (HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t carry = is_c_flag;
	mem[r16->HL] & 0x80 ? set_c_flag : clear_c_flag;
	mem[r16->HL] = (mem[r16->HL] << 1) | carry;
	clear_n_flag;
	clear_h_flag;
	mem[r16->HL] == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb17(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RL A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t carry = is_c_flag;
	r8->A & 0x80 ? set_c_flag : clear_c_flag;
	r8->A = (r8->A << 1) | carry;
	clear_n_flag;
	clear_h_flag;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}



void op_17(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RLA
		   num bytes: 1
		      cycles: 4
		       flags: 0 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t carry = is_c_flag;
	r8->A & 0x80 ? set_c_flag : clear_c_flag;
	r8->A = (r8->A << 1) | carry;
	clear_n_flag;
	clear_h_flag;
	clear_z_flag;
	r16->PC += 1;
}



void op_cb00(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RLC B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B = (r8->B << 1) | (r8->B >> 7);
	r8->B == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	r8->B & 1 ? set_c_flag : clear_c_flag;
	r16->PC += 2;
}

void op_cb01(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RLC C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C = (r8->C << 1) | (r8->C >> 7);
	r8->C == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	r8->C & 1 ? set_c_flag : clear_c_flag;
	r16->PC += 2;
}

void op_cb02(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RLC D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D = (r8->D << 1) | (r8->D >> 7);
	r8->D == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	r8->D & 1 ? set_c_flag : clear_c_flag;
	r16->PC += 2;
}

void op_cb03(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RLC E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E = (r8->E << 1) | (r8->E >> 7);
	r8->E == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	r8->E & 1 ? set_c_flag : clear_c_flag;
	r16->PC += 2;
}

void op_cb04(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RLC H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H = (r8->H << 1) | (r8->H >> 7);
	r8->H == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	r8->H & 1 ? set_c_flag : clear_c_flag;
	r16->PC += 2;
}

void op_cb05(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RLC L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L = (r8->L << 1) | (r8->L >> 7);
	r8->L == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	r8->L & 1 ? set_c_flag : clear_c_flag;
	r16->PC += 2;
}

void op_cb06(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RLC (HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL] = (mem[r16->HL] << 1) | (mem[r16->HL] >> 7);
	mem[r16->HL] == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	mem[r16->HL] & 1 ? set_c_flag : clear_c_flag;
	r16->PC += 2;
}

void op_cb07(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RLC A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A = (r8->A << 1) | (r8->A >> 7);
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	r8->A & 1 ? set_c_flag : clear_c_flag;
	r16->PC += 2;
}



void op_07(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RLCA
		   num bytes: 1
		      cycles: 4
		       flags: 0 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A = (r8->A << 1) | (r8->A >> 7);
	clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	r8->A & 1 ? set_c_flag : clear_c_flag;
	r16->PC += 1;
}



void op_cb18(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RR B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t carry = is_c_flag;
	r8->B & 1 ? set_c_flag : clear_c_flag;
	r8->B = (r8->B >> 1) | (carry << 7);
	clear_n_flag;
	clear_h_flag;
	r8->B == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb19(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RR C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t carry = is_c_flag;
	r8->C & 1 ? set_c_flag : clear_c_flag;
	r8->C = (r8->C >> 1) | (carry << 7);
	clear_n_flag;
	clear_h_flag;
	r8->C == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb1a(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RR D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t carry = is_c_flag;
	r8->D & 1 ? set_c_flag : clear_c_flag;
	r8->D = (r8->D >> 1) | (carry << 7);
	clear_n_flag;
	clear_h_flag;
	r8->D == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb1b(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RR E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t carry = is_c_flag;
	r8->E & 1 ? set_c_flag : clear_c_flag;
	r8->E = (r8->E >> 1) | (carry << 7);
	clear_n_flag;
	clear_h_flag;
	r8->E == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb1c(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RR H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t carry = is_c_flag;
	r8->H & 1 ? set_c_flag : clear_c_flag;
	r8->H = (r8->H >> 1) | (carry << 7);
	clear_n_flag;
	clear_h_flag;
	r8->H == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb1d(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RR L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t carry = is_c_flag;
	r8->L & 1 ? set_c_flag : clear_c_flag;
	r8->L = (r8->L >> 1) | (carry << 7);
	clear_n_flag;
	clear_h_flag;
	r8->L == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb1e(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RR (HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t carry = is_c_flag;
	mem[r16->HL] & 1 ? set_c_flag : clear_c_flag;
	mem[r16->HL] = (mem[r16->HL] >> 1) | (carry << 7);
	clear_n_flag;
	clear_h_flag;
	mem[r16->HL] == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb1f(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RR A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t carry = is_c_flag;
	r8->A & 1 ? set_c_flag : clear_c_flag;
	r8->A = (r8->A >> 1) | (carry << 7);
	clear_n_flag;
	clear_h_flag;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}



void op_1f(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RRA
		   num bytes: 1
		      cycles: 4
		       flags: 0 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t carry = is_c_flag;
	r8->A & 1 ? set_c_flag : clear_c_flag;
	r8->A = (r8->A >> 1) | (carry << 7);
	clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	r16->PC += 1;
}



void op_cb08(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RRC B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B = (r8->B >> 1) | ((r8->B & 1) << 7);
	r8->B == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	r8->B & 0x80 ? set_c_flag : clear_c_flag;
	r16->PC += 2;
}

void op_cb09(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RRC C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C = (r8->C >> 1) | ((r8->C & 1) << 7);
	r8->C == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	r8->C & 0x80 ? set_c_flag : clear_c_flag;
	r16->PC += 2;
}

void op_cb0a(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RRC D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D = (r8->D >> 1) | ((r8->D & 1) << 7);
	r8->D == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	r8->D & 0x80 ? set_c_flag : clear_c_flag;
	r16->PC += 2;
}

void op_cb0b(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RRC E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E = (r8->E >> 1) | ((r8->E & 1) << 7);
	r8->E == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	r8->E & 0x80 ? set_c_flag : clear_c_flag;
	r16->PC += 2;
}

void op_cb0c(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RRC H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H = (r8->H >> 1) | ((r8->H & 1) << 7);
	r8->H == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	r8->H & 0x80 ? set_c_flag : clear_c_flag;
	r16->PC += 2;
}

void op_cb0d(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RRC L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L = (r8->L >> 1) | ((r8->L & 1) << 7);
	r8->L == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	r8->L & 0x80 ? set_c_flag : clear_c_flag;
	r16->PC += 2;
}

void op_cb0e(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RRC (HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL] = (mem[r16->HL] >> 1) | ((mem[r16->HL] & 1) << 7);
	mem[r16->HL] == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	mem[r16->HL] & 0x80 ? set_c_flag : clear_c_flag;
	r16->PC += 2;
}

void op_cb0f(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RRC A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A = (r8->A >> 1) | ((r8->A & 1) << 7);
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	r8->A & 0x80 ? set_c_flag : clear_c_flag;
	r16->PC += 2;
}



void op_0f(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RRCA
		   num bytes: 1
		      cycles: 4
		       flags: 0 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A = (r8->A >> 1) | ((r8->A & 1) << 7);
	clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	r8->A & 0x80 ? set_c_flag : clear_c_flag;
	r16->PC += 1;
}



void op_c7(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: RST 00H
		   num bytes: 1
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r16->SP -= 2;
	mem[r16->SP] = r16->PC + 1;
	r16->PC = 0x00;
}

void op_cf(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: RST 08H
		   num bytes: 1
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r16->SP -= 2;
	mem[r16->SP] = r16->PC + 1;
	r16->PC = 0x08;
}

void op_d7(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: RST 10H
		   num bytes: 1
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r16->SP -= 2;
	mem[r16->SP] = r16->PC + 1;
	r16->PC = 0x10;
}

void op_df(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: RST 18H
		   num bytes: 1
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r16->SP -= 2;
	mem[r16->SP] = r16->PC + 1;
	r16->PC = 0x18;
}

void op_e7(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: RST 20H
		   num bytes: 1
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r16->SP -= 2;
	mem[r16->SP] = r16->PC + 1;
	r16->PC = 0x20;
}

void op_ef(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: RST 28H
		   num bytes: 1
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r16->SP -= 2;
	mem[r16->SP] = r16->PC + 1;
	r16->PC = 0x28;
}

void op_f7(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: RST 30H
		   num bytes: 1
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r16->SP -= 2;
	mem[r16->SP] = r16->PC + 1;
	r16->PC = 0x30;
}

void op_ff(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: RST 38H
		   num bytes: 1
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r16->SP -= 2;
	mem[r16->SP] = r16->PC + 1;
	r16->PC = 0x38;
}



void op_98(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SBC A,B
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->B;
	(r8->A - (op + is_c_flag)) == 0 ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) < ((op + is_c_flag) & 0xf) ? set_h_flag : clear_h_flag;
	r8->A < (op + is_c_flag) ? set_c_flag : clear_c_flag;
	r8->A = r8->A - (op + is_c_flag);
	r16->PC += 1;
}

void op_99(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SBC A,C
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->C;
	(r8->A - (op + is_c_flag)) == 0 ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) < ((op + is_c_flag) & 0xf) ? set_h_flag : clear_h_flag;
	r8->A < (op + is_c_flag) ? set_c_flag : clear_c_flag;
	r8->A = r8->A - (op + is_c_flag);
	r16->PC += 1;
}

void op_9a(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SBC A,D
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->D;
	(r8->A - (op + is_c_flag)) == 0 ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) < ((op + is_c_flag) & 0xf) ? set_h_flag : clear_h_flag;
	r8->A < (op + is_c_flag) ? set_c_flag : clear_c_flag;
	r8->A = r8->A - (op + is_c_flag);
	r16->PC += 1;
}

void op_9b(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SBC A,E
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->E;
	(r8->A - (op + is_c_flag)) == 0 ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) < ((op + is_c_flag) & 0xf) ? set_h_flag : clear_h_flag;
	r8->A < (op + is_c_flag) ? set_c_flag : clear_c_flag;
	r8->A = r8->A - (op + is_c_flag);
	r16->PC += 1;
}

void op_9c(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SBC A,H
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->H;
	(r8->A - (op + is_c_flag)) == 0 ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) < ((op + is_c_flag) & 0xf) ? set_h_flag : clear_h_flag;
	r8->A < (op + is_c_flag) ? set_c_flag : clear_c_flag;
	r8->A = r8->A - (op + is_c_flag);
	r16->PC += 1;
}

void op_9d(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SBC A,L
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->L;
	(r8->A - (op + is_c_flag)) == 0 ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) < ((op + is_c_flag) & 0xf) ? set_h_flag : clear_h_flag;
	r8->A < (op + is_c_flag) ? set_c_flag : clear_c_flag;
	r8->A = r8->A - (op + is_c_flag);
	r16->PC += 1;
}

void op_9e(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SBC A,(HL)
		   num bytes: 1
		      cycles: 8
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = mem[r16->HL];
	(r8->A - (op + is_c_flag)) == 0 ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) < ((op + is_c_flag) & 0xf) ? set_h_flag : clear_h_flag;
	r8->A < (op + is_c_flag) ? set_c_flag : clear_c_flag;
	r8->A = r8->A - (op + is_c_flag);
	r16->PC += 1;
}

void op_9f(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SBC A,A
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->A;
	(r8->A - (op + is_c_flag)) == 0 ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) < ((op + is_c_flag) & 0xf) ? set_h_flag : clear_h_flag;
	r8->A < (op + is_c_flag) ? set_c_flag : clear_c_flag;
	r8->A = r8->A - (op + is_c_flag);
	r16->PC += 1;
}

void op_de(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SBC A,d8
		   num bytes: 2
		      cycles: 8
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = mem[(r16->PC)+1];
	(r8->A - (op + is_c_flag)) == 0 ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) < ((op + is_c_flag) & 0xf) ? set_h_flag : clear_h_flag;
	r8->A < (op + is_c_flag) ? set_c_flag : clear_c_flag;
	r8->A = r8->A - (op + is_c_flag);
	r16->PC += 2;
}



void op_37(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SCF
		   num bytes: 1
		      cycles: 4
		       flags: - 0 0 1
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	clear_n_flag;
	clear_h_flag;
	set_c_flag;
	r16->PC += 1;
}



void op_cbc0(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 0,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B |= (1 << 0);
	r16->PC += 2;
}

void op_cbc1(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 0,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C |= (1 << 0);
	r16->PC += 2;
}

void op_cbc2(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 0,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D |= (1 << 0);
	r16->PC += 2;
}

void op_cbc3(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 0,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E |= (1 << 0);
	r16->PC += 2;
}

void op_cbc4(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 0,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H |= (1 << 0);
	r16->PC += 2;
}

void op_cbc5(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 0,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L |= (1 << 0);
	r16->PC += 2;
}

void op_cbc6(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 0,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL] |= (1 << 0);
	r16->PC += 2;
}

void op_cbc7(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 0,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A |= (1 << 0);
	r16->PC += 2;
}

void op_cbc8(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 1,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B |= (1 << 1);
	r16->PC += 2;
}

void op_cbc9(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 1,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C |= (1 << 1);
	r16->PC += 2;
}

void op_cbca(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 1,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D |= (1 << 1);
	r16->PC += 2;
}

void op_cbcb(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 1,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E |= (1 << 1);
	r16->PC += 2;
}

void op_cbcc(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 1,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H |= (1 << 1);
	r16->PC += 2;
}

void op_cbcd(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 1,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L |= (1 << 1);
	r16->PC += 2;
}

void op_cbce(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 1,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL] |= (1 << 1);
	r16->PC += 2;
}

void op_cbcf(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 1,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A |= (1 << 1);
	r16->PC += 2;
}

void op_cbd0(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 2,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B |= (1 << 2);
	r16->PC += 2;
}

void op_cbd1(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 2,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C |= (1 << 2);
	r16->PC += 2;
}

void op_cbd2(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 2,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D |= (1 << 2);
	r16->PC += 2;
}

void op_cbd3(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 2,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E |= (1 << 2);
	r16->PC += 2;
}

void op_cbd4(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 2,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H |= (1 << 2);
	r16->PC += 2;
}

void op_cbd5(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 2,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L |= (1 << 2);
	r16->PC += 2;
}

void op_cbd6(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 2,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL] |= (1 << 2);
	r16->PC += 2;
}

void op_cbd7(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 2,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A |= (1 << 2);
	r16->PC += 2;
}

void op_cbd8(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 3,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B |= (1 << 3);
	r16->PC += 2;
}

void op_cbd9(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 3,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C |= (1 << 3);
	r16->PC += 2;
}

void op_cbda(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 3,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D |= (1 << 3);
	r16->PC += 2;
}

void op_cbdb(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 3,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E |= (1 << 3);
	r16->PC += 2;
}

void op_cbdc(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 3,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H |= (1 << 3);
	r16->PC += 2;
}

void op_cbdd(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 3,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L |= (1 << 3);
	r16->PC += 2;
}

void op_cbde(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 3,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL] |= (1 << 3);
	r16->PC += 2;
}

void op_cbdf(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 3,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A |= (1 << 3);
	r16->PC += 2;
}

void op_cbe0(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 4,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B |= (1 << 4);
	r16->PC += 2;
}

void op_cbe1(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 4,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C |= (1 << 4);
	r16->PC += 2;
}

void op_cbe2(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 4,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D |= (1 << 4);
	r16->PC += 2;
}

void op_cbe3(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 4,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E |= (1 << 4);
	r16->PC += 2;
}

void op_cbe4(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 4,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H |= (1 << 4);
	r16->PC += 2;
}

void op_cbe5(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 4,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L |= (1 << 4);
	r16->PC += 2;
}

void op_cbe6(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 4,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL] |= (1 << 4);
	r16->PC += 2;
}

void op_cbe7(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 4,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A |= (1 << 4);
	r16->PC += 2;
}

void op_cbe8(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 5,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B |= (1 << 5);
	r16->PC += 2;
}

void op_cbe9(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 5,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C |= (1 << 5);
	r16->PC += 2;
}

void op_cbea(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 5,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D |= (1 << 5);
	r16->PC += 2;
}

void op_cbeb(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 5,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E |= (1 << 5);
	r16->PC += 2;
}

void op_cbec(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 5,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H |= (1 << 5);
	r16->PC += 2;
}

void op_cbed(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 5,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L |= (1 << 5);
	r16->PC += 2;
}

void op_cbee(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 5,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL] |= (1 << 5);
	r16->PC += 2;
}

void op_cbef(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 5,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A |= (1 << 5);
	r16->PC += 2;
}

void op_cbf0(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 6,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B |= (1 << 6);
	r16->PC += 2;
}

void op_cbf1(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 6,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C |= (1 << 6);
	r16->PC += 2;
}

void op_cbf2(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 6,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D |= (1 << 6);
	r16->PC += 2;
}

void op_cbf3(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 6,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E |= (1 << 6);
	r16->PC += 2;
}

void op_cbf4(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 6,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H |= (1 << 6);
	r16->PC += 2;
}

void op_cbf5(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 6,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L |= (1 << 6);
	r16->PC += 2;
}

void op_cbf6(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 6,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL] |= (1 << 6);
	r16->PC += 2;
}

void op_cbf7(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 6,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A |= (1 << 6);
	r16->PC += 2;
}

void op_cbf8(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 7,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B |= (1 << 7);
	r16->PC += 2;
}

void op_cbf9(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 7,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C |= (1 << 7);
	r16->PC += 2;
}

void op_cbfa(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 7,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D |= (1 << 7);
	r16->PC += 2;
}

void op_cbfb(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 7,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E |= (1 << 7);
	r16->PC += 2;
}

void op_cbfc(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 7,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H |= (1 << 7);
	r16->PC += 2;
}

void op_cbfd(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 7,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L |= (1 << 7);
	r16->PC += 2;
}

void op_cbfe(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 7,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL] |= (1 << 7);
	r16->PC += 2;
}

void op_cbff(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 7,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A |= (1 << 7);
	r16->PC += 2;
}



void op_cb20(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SLA B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	(r8->B << 1) == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	r8->B & 0x80 ? set_c_flag : clear_c_flag;
	r8->B <<= 1;
	r16->PC += 2;
}

void op_cb21(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SLA C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	(r8->C << 1) == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	r8->C & 0x80 ? set_c_flag : clear_c_flag;
	r8->C <<= 1;
	r16->PC += 2;
}

void op_cb22(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SLA D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	(r8->D << 1) == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	r8->D & 0x80 ? set_c_flag : clear_c_flag;
	r8->D <<= 1;
	r16->PC += 2;
}

void op_cb23(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SLA E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	(r8->E << 1) == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	r8->E & 0x80 ? set_c_flag : clear_c_flag;
	r8->E <<= 1;
	r16->PC += 2;
}

void op_cb24(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SLA H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	(r8->H << 1) == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	r8->H & 0x80 ? set_c_flag : clear_c_flag;
	r8->H <<= 1;
	r16->PC += 2;
}

void op_cb25(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SLA L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	(r8->L << 1) == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	r8->L & 0x80 ? set_c_flag : clear_c_flag;
	r8->L <<= 1;
	r16->PC += 2;
}

void op_cb26(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SLA (HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	(mem[r16->HL] << 1) == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	mem[r16->HL] & 0x80 ? set_c_flag : clear_c_flag;
	mem[r16->HL] <<= 1;
	r16->PC += 2;
}

void op_cb27(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SLA A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	(r8->A << 1) == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	r8->A & 0x80 ? set_c_flag : clear_c_flag;
	r8->A <<= 1;
	r16->PC += 2;
}



void op_cb28(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRA B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	clear_n_flag;
	clear_h_flag;
	r8->B & 1 ? set_c_flag : clear_c_flag;
	r8->B = (r8->B & 0x80) | (r8->B >> 1) ;
	r8->B == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb29(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRA C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	clear_n_flag;
	clear_h_flag;
	r8->C & 1 ? set_c_flag : clear_c_flag;
	r8->C = (r8->C & 0x80) | (r8->C >> 1) ;
	r8->C == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb2a(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRA D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	clear_n_flag;
	clear_h_flag;
	r8->D & 1 ? set_c_flag : clear_c_flag;
	r8->D = (r8->D & 0x80) | (r8->D >> 1) ;
	r8->D == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb2b(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRA E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	clear_n_flag;
	clear_h_flag;
	r8->E & 1 ? set_c_flag : clear_c_flag;
	r8->E = (r8->E & 0x80) | (r8->E >> 1) ;
	r8->E == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb2c(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRA H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	clear_n_flag;
	clear_h_flag;
	r8->H & 1 ? set_c_flag : clear_c_flag;
	r8->H = (r8->H & 0x80) | (r8->H >> 1) ;
	r8->H == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb2d(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRA L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	clear_n_flag;
	clear_h_flag;
	r8->L & 1 ? set_c_flag : clear_c_flag;
	r8->L = (r8->L & 0x80) | (r8->L >> 1) ;
	r8->L == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb2e(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRA (HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	clear_n_flag;
	clear_h_flag;
	mem[r16->HL] & 1 ? set_c_flag : clear_c_flag;
	mem[r16->HL] = (mem[r16->HL] & 0x80) | (mem[r16->HL] >> 1) ;
	mem[r16->HL] == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb2f(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRA A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	clear_n_flag;
	clear_h_flag;
	r8->A & 1 ? set_c_flag : clear_c_flag;
	r8->A = (r8->A & 0x80) | (r8->A >> 1) ;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}



void op_cb38(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRL B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	clear_n_flag;
	clear_h_flag;
	r8->B & 1 ? set_c_flag : clear_c_flag;
	r8->B >>= 1;
	r8->B == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb39(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRL C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	clear_n_flag;
	clear_h_flag;
	r8->C & 1 ? set_c_flag : clear_c_flag;
	r8->C >>= 1;
	r8->C == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb3a(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRL D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	clear_n_flag;
	clear_h_flag;
	r8->D & 1 ? set_c_flag : clear_c_flag;
	r8->D >>= 1;
	r8->D == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb3b(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRL E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	clear_n_flag;
	clear_h_flag;
	r8->E & 1 ? set_c_flag : clear_c_flag;
	r8->E >>= 1;
	r8->E == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb3c(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRL H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	clear_n_flag;
	clear_h_flag;
	r8->H & 1 ? set_c_flag : clear_c_flag;
	r8->H >>= 1;
	r8->H == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb3d(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRL L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	clear_n_flag;
	clear_h_flag;
	r8->L & 1 ? set_c_flag : clear_c_flag;
	r8->L >>= 1;
	r8->L == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb3e(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRL (HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	clear_n_flag;
	clear_h_flag;
	mem[r16->HL] & 1 ? set_c_flag : clear_c_flag;
	mem[r16->HL] >>= 1;
	mem[r16->HL] == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb3f(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRL A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	clear_n_flag;
	clear_h_flag;
	r8->A & 1 ? set_c_flag : clear_c_flag;
	r8->A >>= 1;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}



void op_10(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Misc/control instructions
		 instruction: STOP 0
		   num bytes: 2
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r16->PC += 2;
	state->stop = true;
}



void op_90(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SUB B
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->B;
	r8->A == op ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) < (op & 0xf) ? set_h_flag : clear_h_flag;
	r8->A < op ? set_c_flag : clear_c_flag;
	r8->A = r8->A - op;
	r16->PC += 1;
}

void op_91(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SUB C
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->C;
	r8->A == op ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) < (op & 0xf) ? set_h_flag : clear_h_flag;
	r8->A < op ? set_c_flag : clear_c_flag;
	r8->A = r8->A - op;
	r16->PC += 1;
}

void op_92(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SUB D
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->D;
	r8->A == op ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) < (op & 0xf) ? set_h_flag : clear_h_flag;
	r8->A < op ? set_c_flag : clear_c_flag;
	r8->A = r8->A - op;
	r16->PC += 1;
}

void op_93(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SUB E
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->E;
	r8->A == op ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) < (op & 0xf) ? set_h_flag : clear_h_flag;
	r8->A < op ? set_c_flag : clear_c_flag;
	r8->A = r8->A - op;
	r16->PC += 1;
}

void op_94(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SUB H
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->H;
	r8->A == op ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) < (op & 0xf) ? set_h_flag : clear_h_flag;
	r8->A < op ? set_c_flag : clear_c_flag;
	r8->A = r8->A - op;
	r16->PC += 1;
}

void op_95(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SUB L
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->L;
	r8->A == op ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) < (op & 0xf) ? set_h_flag : clear_h_flag;
	r8->A < op ? set_c_flag : clear_c_flag;
	r8->A = r8->A - op;
	r16->PC += 1;
}

void op_96(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SUB (HL)
		   num bytes: 1
		      cycles: 8
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = mem[r16->HL];
	r8->A == op ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) < (op & 0xf) ? set_h_flag : clear_h_flag;
	r8->A < op ? set_c_flag : clear_c_flag;
	r8->A = r8->A - op;
	r16->PC += 1;
}

void op_97(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SUB A
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->A;
	r8->A == op ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) < (op & 0xf) ? set_h_flag : clear_h_flag;
	r8->A < op ? set_c_flag : clear_c_flag;
	r8->A = r8->A - op;
	r16->PC += 1;
}

void op_d6(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SUB d8
		   num bytes: 2
		      cycles: 8
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = mem[(r16->PC)+1];
	r8->A == op ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) < (op & 0xf) ? set_h_flag : clear_h_flag;
	r8->A < op ? set_c_flag : clear_c_flag;
	r8->A = r8->A - op;
	r16->PC += 2;
}



void op_cb30(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SWAP B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
	r8->B = ((r8->B & 0xf) << 4) | ((r8->B & 0xf0) >> 4);
	r16->PC += 2;
}

void op_cb31(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SWAP C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
	r8->C = ((r8->C & 0xf) << 4) | ((r8->C & 0xf0) >> 4);
	r16->PC += 2;
}

void op_cb32(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SWAP D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
	r8->D = ((r8->D & 0xf) << 4) | ((r8->D & 0xf0) >> 4);
	r16->PC += 2;
}

void op_cb33(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SWAP E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
	r8->E = ((r8->E & 0xf) << 4) | ((r8->E & 0xf0) >> 4);
	r16->PC += 2;
}

void op_cb34(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SWAP H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
	r8->H = ((r8->H & 0xf) << 4) | ((r8->H & 0xf0) >> 4);
	r16->PC += 2;
}

void op_cb35(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SWAP L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
	r8->L = ((r8->L & 0xf) << 4) | ((r8->L & 0xf0) >> 4);
	r16->PC += 2;
}

void op_cb36(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SWAP (HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL] == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
	mem[r16->HL] = ((mem[r16->HL] & 0xf) << 4) | ((mem[r16->HL] & 0xf0) >> 4);
	r16->PC += 2;
}

void op_cb37(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SWAP A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
	r8->A = ((r8->A & 0xf) << 4) | ((r8->A & 0xf0) >> 4);
	r16->PC += 2;
}



void op_a8(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: XOR B
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A ^= r8->B;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
	r16->PC += 1;
}

void op_a9(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: XOR C
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A ^= r8->C;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
	r16->PC += 1;
}

void op_aa(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: XOR D
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A ^= r8->D;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
	r16->PC += 1;
}

void op_ab(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: XOR E
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A ^= r8->E;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
	r16->PC += 1;
}

void op_ac(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: XOR H
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A ^= r8->H;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
	r16->PC += 1;
}

void op_ad(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: XOR L
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A ^= r8->L;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
	r16->PC += 1;
}

void op_ae(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: XOR (HL)
		   num bytes: 1
		      cycles: 8
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A ^= mem[r16->HL];
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
	r16->PC += 1;
}

void op_af(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: XOR A
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A ^= r8->A;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
	r16->PC += 1;
}

void op_ee(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: XOR d8
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A ^= mem[(r16->PC)+1];
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
	r16->PC += 2;
}



void op_d3(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: UNDEFINED XXX
		 instruction: undefined
		   num bytes: undefined
		      cycles: undefined
		       flags: undefined
	*/

}

void op_db(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: UNDEFINED XXX
		 instruction: undefined
		   num bytes: undefined
		      cycles: undefined
		       flags: undefined
	*/

}

void op_dd(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: UNDEFINED XXX
		 instruction: undefined
		   num bytes: undefined
		      cycles: undefined
		       flags: undefined
	*/

}

void op_e3(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: UNDEFINED XXX
		 instruction: undefined
		   num bytes: undefined
		      cycles: undefined
		       flags: undefined
	*/

}

void op_e4(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: UNDEFINED XXX
		 instruction: undefined
		   num bytes: undefined
		      cycles: undefined
		       flags: undefined
	*/

}

void op_eb(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: UNDEFINED XXX
		 instruction: undefined
		   num bytes: undefined
		      cycles: undefined
		       flags: undefined
	*/

}

void op_ec(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: UNDEFINED XXX
		 instruction: undefined
		   num bytes: undefined
		      cycles: undefined
		       flags: undefined
	*/

}

void op_ed(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: UNDEFINED XXX
		 instruction: undefined
		   num bytes: undefined
		      cycles: undefined
		       flags: undefined
	*/

}

void op_f4(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: UNDEFINED XXX
		 instruction: undefined
		   num bytes: undefined
		      cycles: undefined
		       flags: undefined
	*/

}

void op_fc(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: UNDEFINED XXX
		 instruction: undefined
		   num bytes: undefined
		      cycles: undefined
		       flags: undefined
	*/

}

void op_fd(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: UNDEFINED XXX
		 instruction: undefined
		   num bytes: undefined
		      cycles: undefined
		       flags: undefined
	*/

}



void (*ops0[])(void *, t_state *, uint8_t *) =
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
 op_f0, op_f1, op_f2, op_f3, op_f4, op_f5, op_f6, op_f7, op_f8, op_f9, op_fa, op_fb, op_fc, op_fd, op_fe, op_ff
};


void (*ops1[])(void *, t_state *, uint8_t *) =
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
 op_cbf0, op_cbf1, op_cbf2, op_cbf3, op_cbf4, op_cbf5, op_cbf6, op_cbf7, op_cbf8, op_cbf9, op_cbfa, op_cbfb, op_cbfc, op_cbfd, op_cbfe, op_cbff
};
