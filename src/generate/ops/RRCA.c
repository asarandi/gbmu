
void op_0f(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RRCA
		   num bytes: 1
		      cycles: 4
		       flags: 0 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A = (r8->A >> 1) | ((r8->A & 1) << 7);
	CLEAR_Z_FLAG;
	CLEAR_N_FLAG;
	CLEAR_H_FLAG;
	r8->A & 0x80 ? SET_C_FLAG : CLEAR_C_FLAG;
	r16->PC += 1;
}

