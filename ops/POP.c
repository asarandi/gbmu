#include "gb.h"

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
	r16->BC = *(uint16_t *)&mem[r16->SP];
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
	r16->DE = *(uint16_t *)&mem[r16->SP];
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
	r16->HL = *(uint16_t *)&mem[r16->SP];
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
	r16->AF = *(uint16_t *)&mem[r16->SP];
	r16->SP += 2;
	r16->PC += 1;
}

