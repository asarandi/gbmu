#include "gb.h"

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
	*(uint16_t *)&mem[r16->SP] = r16->PC + 1;
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
	*(uint16_t *)&mem[r16->SP] = r16->PC + 1;
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
	*(uint16_t *)&mem[r16->SP] = r16->PC + 1;
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
	*(uint16_t *)&mem[r16->SP] = r16->PC + 1;
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
	*(uint16_t *)&mem[r16->SP] = r16->PC + 1;
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
	*(uint16_t *)&mem[r16->SP] = r16->PC + 1;
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
	*(uint16_t *)&mem[r16->SP] = r16->PC + 1;
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
	*(uint16_t *)&mem[r16->SP] = r16->PC + 1;
	r16->PC = 0x38;
}

