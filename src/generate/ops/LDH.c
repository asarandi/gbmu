
void op_e0(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LDH (a8),A
		   num bytes: 2
		      cycles: 12
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t a8;
	a8 = read_u8(r16->PC+1);
	write_u8(0xff00 + a8, r8->A);
	r16->PC += 2;
}

void op_f0(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LDH A,(a8)
		   num bytes: 2
		      cycles: 12
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t a8;
	a8 = read_u8(r16->PC+1);
	r8->A = read_u8(0xff00 + a8);
	r16->PC += 2;
}

