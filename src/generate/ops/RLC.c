
void op_cb00(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RLC B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->B;
	op = (op << 1) | (op >> 7);
	op == 0 ? SET_Z_FLAG : CLEAR_Z_FLAG;
	CLEAR_N_FLAG;
	CLEAR_H_FLAG;
	op & 1 ? SET_C_FLAG : CLEAR_C_FLAG;
	r8->B = op;
	r16->PC += 2;
}

void op_cb01(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RLC C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->C;
	op = (op << 1) | (op >> 7);
	op == 0 ? SET_Z_FLAG : CLEAR_Z_FLAG;
	CLEAR_N_FLAG;
	CLEAR_H_FLAG;
	op & 1 ? SET_C_FLAG : CLEAR_C_FLAG;
	r8->C = op;
	r16->PC += 2;
}

void op_cb02(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RLC D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->D;
	op = (op << 1) | (op >> 7);
	op == 0 ? SET_Z_FLAG : CLEAR_Z_FLAG;
	CLEAR_N_FLAG;
	CLEAR_H_FLAG;
	op & 1 ? SET_C_FLAG : CLEAR_C_FLAG;
	r8->D = op;
	r16->PC += 2;
}

void op_cb03(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RLC E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->E;
	op = (op << 1) | (op >> 7);
	op == 0 ? SET_Z_FLAG : CLEAR_Z_FLAG;
	CLEAR_N_FLAG;
	CLEAR_H_FLAG;
	op & 1 ? SET_C_FLAG : CLEAR_C_FLAG;
	r8->E = op;
	r16->PC += 2;
}

void op_cb04(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RLC H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->H;
	op = (op << 1) | (op >> 7);
	op == 0 ? SET_Z_FLAG : CLEAR_Z_FLAG;
	CLEAR_N_FLAG;
	CLEAR_H_FLAG;
	op & 1 ? SET_C_FLAG : CLEAR_C_FLAG;
	r8->H = op;
	r16->PC += 2;
}

void op_cb05(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RLC L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->L;
	op = (op << 1) | (op >> 7);
	op == 0 ? SET_Z_FLAG : CLEAR_Z_FLAG;
	CLEAR_N_FLAG;
	CLEAR_H_FLAG;
	op & 1 ? SET_C_FLAG : CLEAR_C_FLAG;
	r8->L = op;
	r16->PC += 2;
}

void op_cb06(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RLC (HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = read_u8(r16->HL);
	op = (op << 1) | (op >> 7);
	op == 0 ? SET_Z_FLAG : CLEAR_Z_FLAG;
	CLEAR_N_FLAG;
	CLEAR_H_FLAG;
	op & 1 ? SET_C_FLAG : CLEAR_C_FLAG;
	write_u8(r16->HL, op);
	r16->PC += 2;
}

void op_cb07(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RLC A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->A;
	op = (op << 1) | (op >> 7);
	op == 0 ? SET_Z_FLAG : CLEAR_Z_FLAG;
	CLEAR_N_FLAG;
	CLEAR_H_FLAG;
	op & 1 ? SET_C_FLAG : CLEAR_C_FLAG;
	r8->A = op;
	r16->PC += 2;
}

