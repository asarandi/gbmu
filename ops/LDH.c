#include "gb.h"

void op_e0(void *reg, uint8_t *mem)
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
}

void op_f0(void *reg, uint8_t *mem)
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
}

