
void op_cb80(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 0,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B &= ~(1 << 0);
	r16->PC += 2;
}

void op_cb81(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 0,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C &= ~(1 << 0);
	r16->PC += 2;
}

void op_cb82(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 0,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D &= ~(1 << 0);
	r16->PC += 2;
}

void op_cb83(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 0,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E &= ~(1 << 0);
	r16->PC += 2;
}

void op_cb84(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 0,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H &= ~(1 << 0);
	r16->PC += 2;
}

void op_cb85(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 0,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L &= ~(1 << 0);
	r16->PC += 2;
}

void op_cb86(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 0,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = read_u8(r16->HL);
	op &= ~(1 << 0);
	write_u8(r16->HL, op);
	r16->PC += 2;
}

void op_cb87(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 0,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A &= ~(1 << 0);
	r16->PC += 2;
}

void op_cb88(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 1,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B &= ~(1 << 1);
	r16->PC += 2;
}

void op_cb89(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 1,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C &= ~(1 << 1);
	r16->PC += 2;
}

void op_cb8a(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 1,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D &= ~(1 << 1);
	r16->PC += 2;
}

void op_cb8b(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 1,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E &= ~(1 << 1);
	r16->PC += 2;
}

void op_cb8c(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 1,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H &= ~(1 << 1);
	r16->PC += 2;
}

void op_cb8d(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 1,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L &= ~(1 << 1);
	r16->PC += 2;
}

void op_cb8e(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 1,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = read_u8(r16->HL);
	op &= ~(1 << 1);
	write_u8(r16->HL, op);
	r16->PC += 2;
}

void op_cb8f(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 1,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A &= ~(1 << 1);
	r16->PC += 2;
}

void op_cb90(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 2,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B &= ~(1 << 2);
	r16->PC += 2;
}

void op_cb91(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 2,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C &= ~(1 << 2);
	r16->PC += 2;
}

void op_cb92(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 2,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D &= ~(1 << 2);
	r16->PC += 2;
}

void op_cb93(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 2,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E &= ~(1 << 2);
	r16->PC += 2;
}

void op_cb94(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 2,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H &= ~(1 << 2);
	r16->PC += 2;
}

void op_cb95(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 2,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L &= ~(1 << 2);
	r16->PC += 2;
}

void op_cb96(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 2,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = read_u8(r16->HL);
	op &= ~(1 << 2);
	write_u8(r16->HL, op);
	r16->PC += 2;
}

void op_cb97(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 2,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A &= ~(1 << 2);
	r16->PC += 2;
}

void op_cb98(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 3,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B &= ~(1 << 3);
	r16->PC += 2;
}

void op_cb99(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 3,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C &= ~(1 << 3);
	r16->PC += 2;
}

void op_cb9a(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 3,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D &= ~(1 << 3);
	r16->PC += 2;
}

void op_cb9b(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 3,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E &= ~(1 << 3);
	r16->PC += 2;
}

void op_cb9c(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 3,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H &= ~(1 << 3);
	r16->PC += 2;
}

void op_cb9d(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 3,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L &= ~(1 << 3);
	r16->PC += 2;
}

void op_cb9e(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 3,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = read_u8(r16->HL);
	op &= ~(1 << 3);
	write_u8(r16->HL, op);
	r16->PC += 2;
}

void op_cb9f(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 3,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A &= ~(1 << 3);
	r16->PC += 2;
}

void op_cba0(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 4,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B &= ~(1 << 4);
	r16->PC += 2;
}

void op_cba1(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 4,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C &= ~(1 << 4);
	r16->PC += 2;
}

void op_cba2(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 4,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D &= ~(1 << 4);
	r16->PC += 2;
}

void op_cba3(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 4,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E &= ~(1 << 4);
	r16->PC += 2;
}

void op_cba4(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 4,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H &= ~(1 << 4);
	r16->PC += 2;
}

void op_cba5(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 4,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L &= ~(1 << 4);
	r16->PC += 2;
}

void op_cba6(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 4,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = read_u8(r16->HL);
	op &= ~(1 << 4);
	write_u8(r16->HL, op);
	r16->PC += 2;
}

void op_cba7(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 4,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A &= ~(1 << 4);
	r16->PC += 2;
}

void op_cba8(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 5,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B &= ~(1 << 5);
	r16->PC += 2;
}

void op_cba9(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 5,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C &= ~(1 << 5);
	r16->PC += 2;
}

void op_cbaa(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 5,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D &= ~(1 << 5);
	r16->PC += 2;
}

void op_cbab(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 5,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E &= ~(1 << 5);
	r16->PC += 2;
}

void op_cbac(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 5,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H &= ~(1 << 5);
	r16->PC += 2;
}

void op_cbad(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 5,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L &= ~(1 << 5);
	r16->PC += 2;
}

void op_cbae(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 5,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = read_u8(r16->HL);
	op &= ~(1 << 5);
	write_u8(r16->HL, op);
	r16->PC += 2;
}

void op_cbaf(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 5,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A &= ~(1 << 5);
	r16->PC += 2;
}

void op_cbb0(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 6,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B &= ~(1 << 6);
	r16->PC += 2;
}

void op_cbb1(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 6,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C &= ~(1 << 6);
	r16->PC += 2;
}

void op_cbb2(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 6,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D &= ~(1 << 6);
	r16->PC += 2;
}

void op_cbb3(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 6,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E &= ~(1 << 6);
	r16->PC += 2;
}

void op_cbb4(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 6,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H &= ~(1 << 6);
	r16->PC += 2;
}

void op_cbb5(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 6,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L &= ~(1 << 6);
	r16->PC += 2;
}

void op_cbb6(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 6,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = read_u8(r16->HL);
	op &= ~(1 << 6);
	write_u8(r16->HL, op);
	r16->PC += 2;
}

void op_cbb7(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 6,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A &= ~(1 << 6);
	r16->PC += 2;
}

void op_cbb8(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 7,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B &= ~(1 << 7);
	r16->PC += 2;
}

void op_cbb9(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 7,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C &= ~(1 << 7);
	r16->PC += 2;
}

void op_cbba(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 7,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D &= ~(1 << 7);
	r16->PC += 2;
}

void op_cbbb(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 7,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E &= ~(1 << 7);
	r16->PC += 2;
}

void op_cbbc(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 7,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H &= ~(1 << 7);
	r16->PC += 2;
}

void op_cbbd(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 7,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L &= ~(1 << 7);
	r16->PC += 2;
}

void op_cbbe(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 7,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = read_u8(r16->HL);
	op &= ~(1 << 7);
	write_u8(r16->HL, op);
	r16->PC += 2;
}

void op_cbbf(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RES 7,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A &= ~(1 << 7);
	r16->PC += 2;
}

