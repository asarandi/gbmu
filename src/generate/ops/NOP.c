
void op_00(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Misc/control instructions
		 instruction: NOP
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r16->PC += 1;
}

