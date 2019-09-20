
void op_cb30(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SWAP B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->B;
	op == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
	op = ((op & 0xf) << 4) | ((op & 0xf0) >> 4);
	r8->B = op;
	r16->PC += 2;
}

void op_cb31(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SWAP C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->C;
	op == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
	op = ((op & 0xf) << 4) | ((op & 0xf0) >> 4);
	r8->C = op;
	r16->PC += 2;
}

void op_cb32(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SWAP D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->D;
	op == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
	op = ((op & 0xf) << 4) | ((op & 0xf0) >> 4);
	r8->D = op;
	r16->PC += 2;
}

void op_cb33(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SWAP E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->E;
	op == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
	op = ((op & 0xf) << 4) | ((op & 0xf0) >> 4);
	r8->E = op;
	r16->PC += 2;
}

void op_cb34(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SWAP H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->H;
	op == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
	op = ((op & 0xf) << 4) | ((op & 0xf0) >> 4);
	r8->H = op;
	r16->PC += 2;
}

void op_cb35(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SWAP L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->L;
	op == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
	op = ((op & 0xf) << 4) | ((op & 0xf0) >> 4);
	r8->L = op;
	r16->PC += 2;
}

void op_cb36(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SWAP (HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = read_u8(r16->HL);
	op == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
	op = ((op & 0xf) << 4) | ((op & 0xf0) >> 4);
	write_u8(r16->HL, op);
	r16->PC += 2;
}

void op_cb37(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SWAP A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->A;
	op == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
	op = ((op & 0xf) << 4) | ((op & 0xf0) >> 4);
	r8->A = op;
	r16->PC += 2;
}

