#include "gb.h"

void op_f3(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Misc/control instructions
		 instruction: DI
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	state->interrupts_enabled = false;
	r16->PC += 1;
}

