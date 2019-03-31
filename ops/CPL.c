#include "gb.h"

void op_2f(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: CPL
		   num bytes: 1
		      cycles: 4
		       flags: - 1 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A = (~r8->A);
	set_n_flag;
	set_h_flag;
}

