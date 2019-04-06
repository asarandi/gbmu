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

