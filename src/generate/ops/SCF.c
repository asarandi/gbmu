
void op_37(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SCF
		   num bytes: 1
		      cycles: 4
		       flags: - 0 0 1
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	CLEAR_N_FLAG;
	CLEAR_H_FLAG;
	SET_C_FLAG;
	r16->PC += 1;
}

