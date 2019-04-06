#include "gb.h"

void op_3f(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: CCF
		   num bytes: 1
		      cycles: 4
		       flags: - 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	is_c_flag ? clear_c_flag : set_c_flag;
	clear_n_flag;
	clear_h_flag;
	r16->PC += 1;
}

