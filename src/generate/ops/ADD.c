
void op_09(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 16bit arithmetic/logical instructions
		 instruction: ADD HL,BC
		   num bytes: 1
		      cycles: 8
		       flags: - 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint16_t op;
	uint32_t calc;
	CLEAR_N_FLAG;
	op = r16->BC;
	(r16->HL & 0xfff) + (op & 0xfff) > 0xfff ? SET_H_FLAG : CLEAR_H_FLAG;
	calc = r16->HL + op;
	calc > 0xffff ? SET_C_FLAG : CLEAR_C_FLAG;
	r16->HL += op;
	r16->PC += 1;
}

void op_19(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 16bit arithmetic/logical instructions
		 instruction: ADD HL,DE
		   num bytes: 1
		      cycles: 8
		       flags: - 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint16_t op;
	uint32_t calc;
	CLEAR_N_FLAG;
	op = r16->DE;
	(r16->HL & 0xfff) + (op & 0xfff) > 0xfff ? SET_H_FLAG : CLEAR_H_FLAG;
	calc = r16->HL + op;
	calc > 0xffff ? SET_C_FLAG : CLEAR_C_FLAG;
	r16->HL += op;
	r16->PC += 1;
}

void op_29(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 16bit arithmetic/logical instructions
		 instruction: ADD HL,HL
		   num bytes: 1
		      cycles: 8
		       flags: - 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint16_t op;
	uint32_t calc;
	CLEAR_N_FLAG;
	op = r16->HL;
	(r16->HL & 0xfff) + (op & 0xfff) > 0xfff ? SET_H_FLAG : CLEAR_H_FLAG;
	calc = r16->HL + op;
	calc > 0xffff ? SET_C_FLAG : CLEAR_C_FLAG;
	r16->HL += op;
	r16->PC += 1;
}

void op_39(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 16bit arithmetic/logical instructions
		 instruction: ADD HL,SP
		   num bytes: 1
		      cycles: 8
		       flags: - 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint16_t op;
	uint32_t calc;
	CLEAR_N_FLAG;
	op = r16->SP;
	(r16->HL & 0xfff) + (op & 0xfff) > 0xfff ? SET_H_FLAG : CLEAR_H_FLAG;
	calc = r16->HL + op;
	calc > 0xffff ? SET_C_FLAG : CLEAR_C_FLAG;
	r16->HL += op;
	r16->PC += 1;
}

void op_80(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADD A,B
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	uint32_t calc;
	op = r8->B;
	calc = r8->A + op;
	(calc & 0xff) == 0 ? SET_Z_FLAG : CLEAR_Z_FLAG;
	CLEAR_N_FLAG;
	(r8->A & 0xf) + (op & 0xf) > 0xf ? SET_H_FLAG : CLEAR_H_FLAG;
	calc > 0xff ? SET_C_FLAG : CLEAR_C_FLAG;
	r8->A += op;
	r16->PC += 1;
}

void op_81(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADD A,C
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	uint32_t calc;
	op = r8->C;
	calc = r8->A + op;
	(calc & 0xff) == 0 ? SET_Z_FLAG : CLEAR_Z_FLAG;
	CLEAR_N_FLAG;
	(r8->A & 0xf) + (op & 0xf) > 0xf ? SET_H_FLAG : CLEAR_H_FLAG;
	calc > 0xff ? SET_C_FLAG : CLEAR_C_FLAG;
	r8->A += op;
	r16->PC += 1;
}

void op_82(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADD A,D
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	uint32_t calc;
	op = r8->D;
	calc = r8->A + op;
	(calc & 0xff) == 0 ? SET_Z_FLAG : CLEAR_Z_FLAG;
	CLEAR_N_FLAG;
	(r8->A & 0xf) + (op & 0xf) > 0xf ? SET_H_FLAG : CLEAR_H_FLAG;
	calc > 0xff ? SET_C_FLAG : CLEAR_C_FLAG;
	r8->A += op;
	r16->PC += 1;
}

void op_83(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADD A,E
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	uint32_t calc;
	op = r8->E;
	calc = r8->A + op;
	(calc & 0xff) == 0 ? SET_Z_FLAG : CLEAR_Z_FLAG;
	CLEAR_N_FLAG;
	(r8->A & 0xf) + (op & 0xf) > 0xf ? SET_H_FLAG : CLEAR_H_FLAG;
	calc > 0xff ? SET_C_FLAG : CLEAR_C_FLAG;
	r8->A += op;
	r16->PC += 1;
}

void op_84(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADD A,H
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	uint32_t calc;
	op = r8->H;
	calc = r8->A + op;
	(calc & 0xff) == 0 ? SET_Z_FLAG : CLEAR_Z_FLAG;
	CLEAR_N_FLAG;
	(r8->A & 0xf) + (op & 0xf) > 0xf ? SET_H_FLAG : CLEAR_H_FLAG;
	calc > 0xff ? SET_C_FLAG : CLEAR_C_FLAG;
	r8->A += op;
	r16->PC += 1;
}

void op_85(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADD A,L
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	uint32_t calc;
	op = r8->L;
	calc = r8->A + op;
	(calc & 0xff) == 0 ? SET_Z_FLAG : CLEAR_Z_FLAG;
	CLEAR_N_FLAG;
	(r8->A & 0xf) + (op & 0xf) > 0xf ? SET_H_FLAG : CLEAR_H_FLAG;
	calc > 0xff ? SET_C_FLAG : CLEAR_C_FLAG;
	r8->A += op;
	r16->PC += 1;
}

void op_86(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADD A,(HL)
		   num bytes: 1
		      cycles: 8
		       flags: Z 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	uint32_t calc;
	op = read_u8(r16->HL);
	calc = r8->A + op;
	(calc & 0xff) == 0 ? SET_Z_FLAG : CLEAR_Z_FLAG;
	CLEAR_N_FLAG;
	(r8->A & 0xf) + (op & 0xf) > 0xf ? SET_H_FLAG : CLEAR_H_FLAG;
	calc > 0xff ? SET_C_FLAG : CLEAR_C_FLAG;
	r8->A += op;
	r16->PC += 1;
}

void op_87(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADD A,A
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	uint32_t calc;
	op = r8->A;
	calc = r8->A + op;
	(calc & 0xff) == 0 ? SET_Z_FLAG : CLEAR_Z_FLAG;
	CLEAR_N_FLAG;
	(r8->A & 0xf) + (op & 0xf) > 0xf ? SET_H_FLAG : CLEAR_H_FLAG;
	calc > 0xff ? SET_C_FLAG : CLEAR_C_FLAG;
	r8->A += op;
	r16->PC += 1;
}

void op_c6(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: ADD A,d8
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	uint32_t calc;
	op = read_u8(r16->PC+1);
	calc = r8->A + op;
	(calc & 0xff) == 0 ? SET_Z_FLAG : CLEAR_Z_FLAG;
	CLEAR_N_FLAG;
	(r8->A & 0xf) + (op & 0xf) > 0xf ? SET_H_FLAG : CLEAR_H_FLAG;
	calc > 0xff ? SET_C_FLAG : CLEAR_C_FLAG;
	r8->A += op;
	r16->PC += 2;
}

void op_e8(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 16bit arithmetic/logical instructions
		 instruction: ADD SP,r8
		   num bytes: 2
		      cycles: 16
		       flags: 0 0 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	int16_t op;
	CLEAR_Z_FLAG;
	CLEAR_N_FLAG;
	op = (int8_t)read_u8(r16->PC+1);
	(r16->SP & 0xf) + (op & 0xf) > 0xf ? SET_H_FLAG : CLEAR_H_FLAG;
	(r16->SP & 0xff) + (op & 0xff) > 0xff ? SET_C_FLAG : CLEAR_C_FLAG;
	r16->SP += op;
	r16->PC += 2;
}

