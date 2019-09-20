
void op_fb(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Misc/control instructions
		 instruction: EI
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	state->interrupts_enabled = true;
	r16->PC += 1;
}

