#include "gb.h"

void op_1f(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RRA
		   num bytes: 1
		      cycles: 4
		       flags: 0 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t carry = is_c_flag;
	r8->A & 1 ? set_c_flag : clear_c_flag;
	r8->A = (r8->A >> 1) | (carry << 7);
	clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	r16->PC += 1;
}

