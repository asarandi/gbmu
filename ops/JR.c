#include "gb.h"

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

