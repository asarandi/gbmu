#include "gb.h"

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
	uint8_t op = r8->B;
	op--;
	op == 0 ? set_z_flag : clear_z_flag;
	set_n_flag;
	(op & 0xf) == 0xf ? set_h_flag : clear_h_flag;
	r8->B = op;
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
	uint16_t op = r16->BC;
	op--;
	r16->BC = op;
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
	uint8_t op = r8->C;
	op--;
	op == 0 ? set_z_flag : clear_z_flag;
	set_n_flag;
	(op & 0xf) == 0xf ? set_h_flag : clear_h_flag;
	r8->C = op;
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
	uint8_t op = r8->D;
	op--;
	op == 0 ? set_z_flag : clear_z_flag;
	set_n_flag;
	(op & 0xf) == 0xf ? set_h_flag : clear_h_flag;
	r8->D = op;
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
	uint16_t op = r16->DE;
	op--;
	r16->DE = op;
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
	uint8_t op = r8->E;
	op--;
	op == 0 ? set_z_flag : clear_z_flag;
	set_n_flag;
	(op & 0xf) == 0xf ? set_h_flag : clear_h_flag;
	r8->E = op;
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
	uint8_t op = r8->H;
	op--;
	op == 0 ? set_z_flag : clear_z_flag;
	set_n_flag;
	(op & 0xf) == 0xf ? set_h_flag : clear_h_flag;
	r8->H = op;
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
	uint16_t op = r16->HL;
	op--;
	r16->HL = op;
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
	uint8_t op = r8->L;
	op--;
	op == 0 ? set_z_flag : clear_z_flag;
	set_n_flag;
	(op & 0xf) == 0xf ? set_h_flag : clear_h_flag;
	r8->L = op;
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
	uint8_t op = read_u8(r16->HL);
	op--;
	op == 0 ? set_z_flag : clear_z_flag;
	set_n_flag;
	(op & 0xf) == 0xf ? set_h_flag : clear_h_flag;
	write_u8(r16->HL, op);
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
	uint16_t op = r16->SP;
	op--;
	r16->SP = op;
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
	uint8_t op = r8->A;
	op--;
	op == 0 ? set_z_flag : clear_z_flag;
	set_n_flag;
	(op & 0xf) == 0xf ? set_h_flag : clear_h_flag;
	r8->A = op;
	r16->PC += 1;
}

