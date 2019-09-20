
void op_27(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: DAA
		   num bytes: 1
		      cycles: 4
		       flags: Z - 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	/*  https://forums.nesdev.com/viewtopic.php?f=20&t=15944  */
	if (!IS_N_FLAG) {
	    if ((IS_C_FLAG) || (r8->A > 0x99))              { r8->A += 0x60; SET_C_FLAG; }
	    if ((IS_H_FLAG) || ((r8->A & 0x0f) > 0x09))     { r8->A += 0x6; }
	} else {
	    if (IS_C_FLAG)                                  { r8->A -= 0x60; }
	    if (IS_H_FLAG)                                  { r8->A -= 0x6;  }     }
	r8->A == 0 ? SET_Z_FLAG : CLEAR_Z_FLAG;
	CLEAR_H_FLAG;
	r16->PC += 1;
}

