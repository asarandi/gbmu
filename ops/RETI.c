#include "gb.h"

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

