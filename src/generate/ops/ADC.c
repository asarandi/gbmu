
void op_88(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADC A,B
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	uint32_t calc;
	op = r8->B;
	calc = r8->A + op + is_c_flag;
	(calc & 0xff) == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	is_c_flag + (r8->A & 0xf) + (op & 0xf) > 0xf ? set_h_flag : clear_h_flag;
	is_c_flag + op + r8->A > 0xff ? set_c_flag : clear_c_flag;
	r8->A = calc & 0xff;
	r16->PC += 1;
}

void op_89(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADC A,C
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	uint32_t calc;
	op = r8->C;
	calc = r8->A + op + is_c_flag;
	(calc & 0xff) == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	is_c_flag + (r8->A & 0xf) + (op & 0xf) > 0xf ? set_h_flag : clear_h_flag;
	is_c_flag + op + r8->A > 0xff ? set_c_flag : clear_c_flag;
	r8->A = calc & 0xff;
	r16->PC += 1;
}

void op_8a(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADC A,D
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	uint32_t calc;
	op = r8->D;
	calc = r8->A + op + is_c_flag;
	(calc & 0xff) == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	is_c_flag + (r8->A & 0xf) + (op & 0xf) > 0xf ? set_h_flag : clear_h_flag;
	is_c_flag + op + r8->A > 0xff ? set_c_flag : clear_c_flag;
	r8->A = calc & 0xff;
	r16->PC += 1;
}

void op_8b(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADC A,E
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	uint32_t calc;
	op = r8->E;
	calc = r8->A + op + is_c_flag;
	(calc & 0xff) == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	is_c_flag + (r8->A & 0xf) + (op & 0xf) > 0xf ? set_h_flag : clear_h_flag;
	is_c_flag + op + r8->A > 0xff ? set_c_flag : clear_c_flag;
	r8->A = calc & 0xff;
	r16->PC += 1;
}

void op_8c(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADC A,H
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	uint32_t calc;
	op = r8->H;
	calc = r8->A + op + is_c_flag;
	(calc & 0xff) == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	is_c_flag + (r8->A & 0xf) + (op & 0xf) > 0xf ? set_h_flag : clear_h_flag;
	is_c_flag + op + r8->A > 0xff ? set_c_flag : clear_c_flag;
	r8->A = calc & 0xff;
	r16->PC += 1;
}

void op_8d(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADC A,L
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	uint32_t calc;
	op = r8->L;
	calc = r8->A + op + is_c_flag;
	(calc & 0xff) == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	is_c_flag + (r8->A & 0xf) + (op & 0xf) > 0xf ? set_h_flag : clear_h_flag;
	is_c_flag + op + r8->A > 0xff ? set_c_flag : clear_c_flag;
	r8->A = calc & 0xff;
	r16->PC += 1;
}

void op_8e(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADC A,(HL)
		   num bytes: 1
		      cycles: 8
		       flags: Z 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	uint32_t calc;
	op = read_u8(r16->HL);
	calc = r8->A + op + is_c_flag;
	(calc & 0xff) == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	is_c_flag + (r8->A & 0xf) + (op & 0xf) > 0xf ? set_h_flag : clear_h_flag;
	is_c_flag + op + r8->A > 0xff ? set_c_flag : clear_c_flag;
	r8->A = calc & 0xff;
	r16->PC += 1;
}

void op_8f(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADC A,A
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	uint32_t calc;
	op = r8->A;
	calc = r8->A + op + is_c_flag;
	(calc & 0xff) == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	is_c_flag + (r8->A & 0xf) + (op & 0xf) > 0xf ? set_h_flag : clear_h_flag;
	is_c_flag + op + r8->A > 0xff ? set_c_flag : clear_c_flag;
	r8->A = calc & 0xff;
	r16->PC += 1;
}

void op_ce(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADC A,d8
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	uint32_t calc;
	op = read_u8(r16->PC+1);
	calc = r8->A + op + is_c_flag;
	(calc & 0xff) == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	is_c_flag + (r8->A & 0xf) + (op & 0xf) > 0xf ? set_h_flag : clear_h_flag;
	is_c_flag + op + r8->A > 0xff ? set_c_flag : clear_c_flag;
	r8->A = calc & 0xff;
	r16->PC += 2;
}

