
void op_98(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SBC A,B
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op, calc;
	op = r8->B;
	calc = r8->A - op - IS_C_FLAG;
	calc == 0 ? SET_Z_FLAG : CLEAR_Z_FLAG;
	SET_N_FLAG;
	((r8->A & 0xf)-(op & 0xf)-IS_C_FLAG)<0 ? SET_H_FLAG : CLEAR_H_FLAG;
	r8->A < (op + IS_C_FLAG) ? SET_C_FLAG : CLEAR_C_FLAG;
	r8->A = calc;
	r16->PC += 1;
}

void op_99(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SBC A,C
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op, calc;
	op = r8->C;
	calc = r8->A - op - IS_C_FLAG;
	calc == 0 ? SET_Z_FLAG : CLEAR_Z_FLAG;
	SET_N_FLAG;
	((r8->A & 0xf)-(op & 0xf)-IS_C_FLAG)<0 ? SET_H_FLAG : CLEAR_H_FLAG;
	r8->A < (op + IS_C_FLAG) ? SET_C_FLAG : CLEAR_C_FLAG;
	r8->A = calc;
	r16->PC += 1;
}

void op_9a(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SBC A,D
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op, calc;
	op = r8->D;
	calc = r8->A - op - IS_C_FLAG;
	calc == 0 ? SET_Z_FLAG : CLEAR_Z_FLAG;
	SET_N_FLAG;
	((r8->A & 0xf)-(op & 0xf)-IS_C_FLAG)<0 ? SET_H_FLAG : CLEAR_H_FLAG;
	r8->A < (op + IS_C_FLAG) ? SET_C_FLAG : CLEAR_C_FLAG;
	r8->A = calc;
	r16->PC += 1;
}

void op_9b(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SBC A,E
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op, calc;
	op = r8->E;
	calc = r8->A - op - IS_C_FLAG;
	calc == 0 ? SET_Z_FLAG : CLEAR_Z_FLAG;
	SET_N_FLAG;
	((r8->A & 0xf)-(op & 0xf)-IS_C_FLAG)<0 ? SET_H_FLAG : CLEAR_H_FLAG;
	r8->A < (op + IS_C_FLAG) ? SET_C_FLAG : CLEAR_C_FLAG;
	r8->A = calc;
	r16->PC += 1;
}

void op_9c(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SBC A,H
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op, calc;
	op = r8->H;
	calc = r8->A - op - IS_C_FLAG;
	calc == 0 ? SET_Z_FLAG : CLEAR_Z_FLAG;
	SET_N_FLAG;
	((r8->A & 0xf)-(op & 0xf)-IS_C_FLAG)<0 ? SET_H_FLAG : CLEAR_H_FLAG;
	r8->A < (op + IS_C_FLAG) ? SET_C_FLAG : CLEAR_C_FLAG;
	r8->A = calc;
	r16->PC += 1;
}

void op_9d(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SBC A,L
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op, calc;
	op = r8->L;
	calc = r8->A - op - IS_C_FLAG;
	calc == 0 ? SET_Z_FLAG : CLEAR_Z_FLAG;
	SET_N_FLAG;
	((r8->A & 0xf)-(op & 0xf)-IS_C_FLAG)<0 ? SET_H_FLAG : CLEAR_H_FLAG;
	r8->A < (op + IS_C_FLAG) ? SET_C_FLAG : CLEAR_C_FLAG;
	r8->A = calc;
	r16->PC += 1;
}

void op_9e(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SBC A,(HL)
		   num bytes: 1
		      cycles: 8
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op, calc;
	op = read_u8(r16->HL);
	calc = r8->A - op - IS_C_FLAG;
	calc == 0 ? SET_Z_FLAG : CLEAR_Z_FLAG;
	SET_N_FLAG;
	((r8->A & 0xf)-(op & 0xf)-IS_C_FLAG)<0 ? SET_H_FLAG : CLEAR_H_FLAG;
	r8->A < (op + IS_C_FLAG) ? SET_C_FLAG : CLEAR_C_FLAG;
	r8->A = calc;
	r16->PC += 1;
}

void op_9f(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SBC A,A
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op, calc;
	op = r8->A;
	calc = r8->A - op - IS_C_FLAG;
	calc == 0 ? SET_Z_FLAG : CLEAR_Z_FLAG;
	SET_N_FLAG;
	((r8->A & 0xf)-(op & 0xf)-IS_C_FLAG)<0 ? SET_H_FLAG : CLEAR_H_FLAG;
	r8->A < (op + IS_C_FLAG) ? SET_C_FLAG : CLEAR_C_FLAG;
	r8->A = calc;
	r16->PC += 1;
}

void op_de(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SBC A,d8
		   num bytes: 2
		      cycles: 8
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op, calc;
	op = read_u8(r16->PC+1);
	calc = r8->A - op - IS_C_FLAG;
	calc == 0 ? SET_Z_FLAG : CLEAR_Z_FLAG;
	SET_N_FLAG;
	((r8->A & 0xf)-(op & 0xf)-IS_C_FLAG)<0 ? SET_H_FLAG : CLEAR_H_FLAG;
	r8->A < (op + IS_C_FLAG) ? SET_C_FLAG : CLEAR_C_FLAG;
	r8->A = calc;
	r16->PC += 2;
}

