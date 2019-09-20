
void op_90(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SUB B
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->B;
	r8->A == op ? SET_Z_FLAG : CLEAR_Z_FLAG;
	SET_N_FLAG;
	(r8->A & 0xf) < (op & 0xf) ? SET_H_FLAG : CLEAR_H_FLAG;
	r8->A < op ? SET_C_FLAG : CLEAR_C_FLAG;
	r8->A = r8->A - op;
	r16->PC += 1;
}

void op_91(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SUB C
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->C;
	r8->A == op ? SET_Z_FLAG : CLEAR_Z_FLAG;
	SET_N_FLAG;
	(r8->A & 0xf) < (op & 0xf) ? SET_H_FLAG : CLEAR_H_FLAG;
	r8->A < op ? SET_C_FLAG : CLEAR_C_FLAG;
	r8->A = r8->A - op;
	r16->PC += 1;
}

void op_92(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SUB D
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->D;
	r8->A == op ? SET_Z_FLAG : CLEAR_Z_FLAG;
	SET_N_FLAG;
	(r8->A & 0xf) < (op & 0xf) ? SET_H_FLAG : CLEAR_H_FLAG;
	r8->A < op ? SET_C_FLAG : CLEAR_C_FLAG;
	r8->A = r8->A - op;
	r16->PC += 1;
}

void op_93(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SUB E
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->E;
	r8->A == op ? SET_Z_FLAG : CLEAR_Z_FLAG;
	SET_N_FLAG;
	(r8->A & 0xf) < (op & 0xf) ? SET_H_FLAG : CLEAR_H_FLAG;
	r8->A < op ? SET_C_FLAG : CLEAR_C_FLAG;
	r8->A = r8->A - op;
	r16->PC += 1;
}

void op_94(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SUB H
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->H;
	r8->A == op ? SET_Z_FLAG : CLEAR_Z_FLAG;
	SET_N_FLAG;
	(r8->A & 0xf) < (op & 0xf) ? SET_H_FLAG : CLEAR_H_FLAG;
	r8->A < op ? SET_C_FLAG : CLEAR_C_FLAG;
	r8->A = r8->A - op;
	r16->PC += 1;
}

void op_95(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SUB L
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->L;
	r8->A == op ? SET_Z_FLAG : CLEAR_Z_FLAG;
	SET_N_FLAG;
	(r8->A & 0xf) < (op & 0xf) ? SET_H_FLAG : CLEAR_H_FLAG;
	r8->A < op ? SET_C_FLAG : CLEAR_C_FLAG;
	r8->A = r8->A - op;
	r16->PC += 1;
}

void op_96(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SUB (HL)
		   num bytes: 1
		      cycles: 8
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = read_u8(r16->HL);
	r8->A == op ? SET_Z_FLAG : CLEAR_Z_FLAG;
	SET_N_FLAG;
	(r8->A & 0xf) < (op & 0xf) ? SET_H_FLAG : CLEAR_H_FLAG;
	r8->A < op ? SET_C_FLAG : CLEAR_C_FLAG;
	r8->A = r8->A - op;
	r16->PC += 1;
}

void op_97(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SUB A
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->A;
	r8->A == op ? SET_Z_FLAG : CLEAR_Z_FLAG;
	SET_N_FLAG;
	(r8->A & 0xf) < (op & 0xf) ? SET_H_FLAG : CLEAR_H_FLAG;
	r8->A < op ? SET_C_FLAG : CLEAR_C_FLAG;
	r8->A = r8->A - op;
	r16->PC += 1;
}

void op_d6(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SUB d8
		   num bytes: 2
		      cycles: 8
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = read_u8(r16->PC+1);
	r8->A == op ? SET_Z_FLAG : CLEAR_Z_FLAG;
	SET_N_FLAG;
	(r8->A & 0xf) < (op & 0xf) ? SET_H_FLAG : CLEAR_H_FLAG;
	r8->A < op ? SET_C_FLAG : CLEAR_C_FLAG;
	r8->A = r8->A - op;
	r16->PC += 2;
}

