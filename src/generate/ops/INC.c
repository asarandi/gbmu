
void op_03(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 16bit arithmetic/logical instructions
		 instruction: INC BC
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint16_t op;
	op = r16->BC;
	op++;
	r16->BC = op;
	r16->PC += 1;
}

void op_04(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: INC B
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->B;
	op++;
	op == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	(op & 0xf) == 0 ? set_h_flag : clear_h_flag;
	r8->B = op;
	r16->PC += 1;
}

void op_0c(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: INC C
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->C;
	op++;
	op == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	(op & 0xf) == 0 ? set_h_flag : clear_h_flag;
	r8->C = op;
	r16->PC += 1;
}

void op_13(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 16bit arithmetic/logical instructions
		 instruction: INC DE
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint16_t op;
	op = r16->DE;
	op++;
	r16->DE = op;
	r16->PC += 1;
}

void op_14(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: INC D
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->D;
	op++;
	op == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	(op & 0xf) == 0 ? set_h_flag : clear_h_flag;
	r8->D = op;
	r16->PC += 1;
}

void op_1c(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: INC E
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->E;
	op++;
	op == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	(op & 0xf) == 0 ? set_h_flag : clear_h_flag;
	r8->E = op;
	r16->PC += 1;
}

void op_23(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 16bit arithmetic/logical instructions
		 instruction: INC HL
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint16_t op;
	op = r16->HL;
	op++;
	r16->HL = op;
	r16->PC += 1;
}

void op_24(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: INC H
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->H;
	op++;
	op == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	(op & 0xf) == 0 ? set_h_flag : clear_h_flag;
	r8->H = op;
	r16->PC += 1;
}

void op_2c(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: INC L
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->L;
	op++;
	op == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	(op & 0xf) == 0 ? set_h_flag : clear_h_flag;
	r8->L = op;
	r16->PC += 1;
}

void op_33(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 16bit arithmetic/logical instructions
		 instruction: INC SP
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint16_t op;
	op = r16->SP;
	op++;
	r16->SP = op;
	r16->PC += 1;
}

void op_34(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: INC (HL)
		   num bytes: 1
		      cycles: 12
		       flags: Z 0 H -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = read_u8(r16->HL);
	op++;
	op == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	(op & 0xf) == 0 ? set_h_flag : clear_h_flag;
	write_u8(r16->HL, op);
	r16->PC += 1;
}

void op_3c(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: INC A
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->A;
	op++;
	op == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	(op & 0xf) == 0 ? set_h_flag : clear_h_flag;
	r8->A = op;
	r16->PC += 1;
}

