#include "gb.h"

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

