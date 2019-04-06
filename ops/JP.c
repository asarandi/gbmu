#include "gb.h"

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
	r16->PC = *(uint16_t *)&mem[r16->PC + 1];
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
	r16->PC = *(uint16_t *)&mem[r16->PC + 1];
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
	r16->PC = *(uint16_t *)&mem[r16->PC + 1];
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
	r16->PC = *(uint16_t *)&mem[r16->PC + 1];
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
	r16->PC = *(uint16_t *)&mem[r16->PC + 1];
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

