
void op_c2(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: JP NZ,a16
		   num bytes: 3
		      cycles: 16/12
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	if (IS_Z_FLAG)  { r16->PC += 3; return; };
	r16->PC = read_u16(r16->PC + 1);
}

void op_c3(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: JP a16
		   num bytes: 3
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r16->PC = read_u16(r16->PC + 1);
}

void op_ca(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: JP Z,a16
		   num bytes: 3
		      cycles: 16/12
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	if (!IS_Z_FLAG)  { r16->PC += 3; return; };
	r16->PC = read_u16(r16->PC + 1);
}

void op_d2(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: JP NC,a16
		   num bytes: 3
		      cycles: 16/12
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	if (IS_C_FLAG)  { r16->PC += 3; return; };
	r16->PC = read_u16(r16->PC + 1);
}

void op_da(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: JP C,a16
		   num bytes: 3
		      cycles: 16/12
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	if (!IS_C_FLAG) { r16->PC += 3; return; };
	r16->PC = read_u16(r16->PC + 1);
}

void op_e9(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: JP (HL)
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r16->PC = r16->HL;
}

