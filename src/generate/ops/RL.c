
void op_cb10(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RL B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op, carry;
	op = r8->B;
	carry = is_c_flag;
	op & 0x80 ? set_c_flag : clear_c_flag;
	op = (op << 1) | carry;
	clear_n_flag;
	clear_h_flag;
	op == 0 ? set_z_flag : clear_z_flag;
	r8->B = op;
	r16->PC += 2;
}

void op_cb11(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RL C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op, carry;
	op = r8->C;
	carry = is_c_flag;
	op & 0x80 ? set_c_flag : clear_c_flag;
	op = (op << 1) | carry;
	clear_n_flag;
	clear_h_flag;
	op == 0 ? set_z_flag : clear_z_flag;
	r8->C = op;
	r16->PC += 2;
}

void op_cb12(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RL D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op, carry;
	op = r8->D;
	carry = is_c_flag;
	op & 0x80 ? set_c_flag : clear_c_flag;
	op = (op << 1) | carry;
	clear_n_flag;
	clear_h_flag;
	op == 0 ? set_z_flag : clear_z_flag;
	r8->D = op;
	r16->PC += 2;
}

void op_cb13(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RL E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op, carry;
	op = r8->E;
	carry = is_c_flag;
	op & 0x80 ? set_c_flag : clear_c_flag;
	op = (op << 1) | carry;
	clear_n_flag;
	clear_h_flag;
	op == 0 ? set_z_flag : clear_z_flag;
	r8->E = op;
	r16->PC += 2;
}

void op_cb14(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RL H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op, carry;
	op = r8->H;
	carry = is_c_flag;
	op & 0x80 ? set_c_flag : clear_c_flag;
	op = (op << 1) | carry;
	clear_n_flag;
	clear_h_flag;
	op == 0 ? set_z_flag : clear_z_flag;
	r8->H = op;
	r16->PC += 2;
}

void op_cb15(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RL L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op, carry;
	op = r8->L;
	carry = is_c_flag;
	op & 0x80 ? set_c_flag : clear_c_flag;
	op = (op << 1) | carry;
	clear_n_flag;
	clear_h_flag;
	op == 0 ? set_z_flag : clear_z_flag;
	r8->L = op;
	r16->PC += 2;
}

void op_cb16(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RL (HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op, carry;
	op = read_u8(r16->HL);
	carry = is_c_flag;
	op & 0x80 ? set_c_flag : clear_c_flag;
	op = (op << 1) | carry;
	clear_n_flag;
	clear_h_flag;
	op == 0 ? set_z_flag : clear_z_flag;
	write_u8(r16->HL, op);
	r16->PC += 2;
}

void op_cb17(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RL A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op, carry;
	op = r8->A;
	carry = is_c_flag;
	op & 0x80 ? set_c_flag : clear_c_flag;
	op = (op << 1) | carry;
	clear_n_flag;
	clear_h_flag;
	op == 0 ? set_z_flag : clear_z_flag;
	r8->A = op;
	r16->PC += 2;
}

