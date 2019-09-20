
void op_cb20(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SLA B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->B;
	CLEAR_N_FLAG;
	CLEAR_H_FLAG;
	op & 0x80 ? SET_C_FLAG : CLEAR_C_FLAG;
	op <<= 1;
	op == 0 ? SET_Z_FLAG : CLEAR_Z_FLAG;
	r8->B = op;
	r16->PC += 2;
}

void op_cb21(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SLA C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->C;
	CLEAR_N_FLAG;
	CLEAR_H_FLAG;
	op & 0x80 ? SET_C_FLAG : CLEAR_C_FLAG;
	op <<= 1;
	op == 0 ? SET_Z_FLAG : CLEAR_Z_FLAG;
	r8->C = op;
	r16->PC += 2;
}

void op_cb22(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SLA D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->D;
	CLEAR_N_FLAG;
	CLEAR_H_FLAG;
	op & 0x80 ? SET_C_FLAG : CLEAR_C_FLAG;
	op <<= 1;
	op == 0 ? SET_Z_FLAG : CLEAR_Z_FLAG;
	r8->D = op;
	r16->PC += 2;
}

void op_cb23(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SLA E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->E;
	CLEAR_N_FLAG;
	CLEAR_H_FLAG;
	op & 0x80 ? SET_C_FLAG : CLEAR_C_FLAG;
	op <<= 1;
	op == 0 ? SET_Z_FLAG : CLEAR_Z_FLAG;
	r8->E = op;
	r16->PC += 2;
}

void op_cb24(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SLA H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->H;
	CLEAR_N_FLAG;
	CLEAR_H_FLAG;
	op & 0x80 ? SET_C_FLAG : CLEAR_C_FLAG;
	op <<= 1;
	op == 0 ? SET_Z_FLAG : CLEAR_Z_FLAG;
	r8->H = op;
	r16->PC += 2;
}

void op_cb25(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SLA L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->L;
	CLEAR_N_FLAG;
	CLEAR_H_FLAG;
	op & 0x80 ? SET_C_FLAG : CLEAR_C_FLAG;
	op <<= 1;
	op == 0 ? SET_Z_FLAG : CLEAR_Z_FLAG;
	r8->L = op;
	r16->PC += 2;
}

void op_cb26(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SLA (HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = read_u8(r16->HL);
	CLEAR_N_FLAG;
	CLEAR_H_FLAG;
	op & 0x80 ? SET_C_FLAG : CLEAR_C_FLAG;
	op <<= 1;
	op == 0 ? SET_Z_FLAG : CLEAR_Z_FLAG;
	write_u8(r16->HL, op);
	r16->PC += 2;
}

void op_cb27(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SLA A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->A;
	CLEAR_N_FLAG;
	CLEAR_H_FLAG;
	op & 0x80 ? SET_C_FLAG : CLEAR_C_FLAG;
	op <<= 1;
	op == 0 ? SET_Z_FLAG : CLEAR_Z_FLAG;
	r8->A = op;
	r16->PC += 2;
}

