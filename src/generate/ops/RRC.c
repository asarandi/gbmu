
void op_cb08(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RRC B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->B;
	op = (op >> 1) | ((op & 1) << 7);
	op == 0 ? SET_Z_FLAG : CLEAR_Z_FLAG;
	CLEAR_N_FLAG;
	CLEAR_H_FLAG;
	op & 0x80 ? SET_C_FLAG : CLEAR_C_FLAG;
	r8->B = op;
	r16->PC += 2;
}

void op_cb09(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RRC C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->C;
	op = (op >> 1) | ((op & 1) << 7);
	op == 0 ? SET_Z_FLAG : CLEAR_Z_FLAG;
	CLEAR_N_FLAG;
	CLEAR_H_FLAG;
	op & 0x80 ? SET_C_FLAG : CLEAR_C_FLAG;
	r8->C = op;
	r16->PC += 2;
}

void op_cb0a(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RRC D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->D;
	op = (op >> 1) | ((op & 1) << 7);
	op == 0 ? SET_Z_FLAG : CLEAR_Z_FLAG;
	CLEAR_N_FLAG;
	CLEAR_H_FLAG;
	op & 0x80 ? SET_C_FLAG : CLEAR_C_FLAG;
	r8->D = op;
	r16->PC += 2;
}

void op_cb0b(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RRC E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->E;
	op = (op >> 1) | ((op & 1) << 7);
	op == 0 ? SET_Z_FLAG : CLEAR_Z_FLAG;
	CLEAR_N_FLAG;
	CLEAR_H_FLAG;
	op & 0x80 ? SET_C_FLAG : CLEAR_C_FLAG;
	r8->E = op;
	r16->PC += 2;
}

void op_cb0c(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RRC H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->H;
	op = (op >> 1) | ((op & 1) << 7);
	op == 0 ? SET_Z_FLAG : CLEAR_Z_FLAG;
	CLEAR_N_FLAG;
	CLEAR_H_FLAG;
	op & 0x80 ? SET_C_FLAG : CLEAR_C_FLAG;
	r8->H = op;
	r16->PC += 2;
}

void op_cb0d(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RRC L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->L;
	op = (op >> 1) | ((op & 1) << 7);
	op == 0 ? SET_Z_FLAG : CLEAR_Z_FLAG;
	CLEAR_N_FLAG;
	CLEAR_H_FLAG;
	op & 0x80 ? SET_C_FLAG : CLEAR_C_FLAG;
	r8->L = op;
	r16->PC += 2;
}

void op_cb0e(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RRC (HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = read_u8(r16->HL);
	op = (op >> 1) | ((op & 1) << 7);
	op == 0 ? SET_Z_FLAG : CLEAR_Z_FLAG;
	CLEAR_N_FLAG;
	CLEAR_H_FLAG;
	op & 0x80 ? SET_C_FLAG : CLEAR_C_FLAG;
	write_u8(r16->HL, op);
	r16->PC += 2;
}

void op_cb0f(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RRC A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->A;
	op = (op >> 1) | ((op & 1) << 7);
	op == 0 ? SET_Z_FLAG : CLEAR_Z_FLAG;
	CLEAR_N_FLAG;
	CLEAR_H_FLAG;
	op & 0x80 ? SET_C_FLAG : CLEAR_C_FLAG;
	r8->A = op;
	r16->PC += 2;
}

