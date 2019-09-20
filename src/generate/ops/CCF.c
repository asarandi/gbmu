
void op_3f(void *reg, t_state *state, uint8_t *mem)
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
	IS_C_FLAG ? CLEAR_C_FLAG : SET_C_FLAG;
	CLEAR_N_FLAG;
	CLEAR_H_FLAG;
	r16->PC += 1;
}

