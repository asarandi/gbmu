#include "gb.h"

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
	r16->SP -= 2;
	*(uint16_t *)&mem[r16->SP] = r16->BC;
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
	r16->SP -= 2;
	*(uint16_t *)&mem[r16->SP] = r16->DE;
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
	r16->SP -= 2;
	*(uint16_t *)&mem[r16->SP] = r16->HL;
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
	r16->SP -= 2;
	*(uint16_t *)&mem[r16->SP] = r16->AF;
	r16->PC += 1;
}

