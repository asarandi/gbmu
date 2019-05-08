#include "gb.h"

void op_76(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Misc/control instructions
		 instruction: HALT
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r16->PC += 1;
	state->halt = true;
	if (state->interrupts_enabled == false) {
	    if (read_u8(0xffff) & read_u8(0xff0f) & 0x1f) {
	        state->halt_bug = true; } }
}
