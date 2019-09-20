
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
	if (!is_n_flag) {
	    if ((is_c_flag) || (r8->A > 0x99))              { r8->A += 0x60; set_c_flag; }
	    if ((is_h_flag) || ((r8->A & 0x0f) > 0x09))     { r8->A += 0x6; }
	} else {
	    if (is_c_flag)                                  { r8->A -= 0x60; }
	    if (is_h_flag)                                  { r8->A -= 0x6;  }     }
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_h_flag;
	r16->PC += 1;
}

