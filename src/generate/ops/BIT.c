#include "gb.h"

void op_cb40(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 0,B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->B;
	op & (1 << 0) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb41(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 0,C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->C;
	op & (1 << 0) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb42(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 0,D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->D;
	op & (1 << 0) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb43(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 0,E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->E;
	op & (1 << 0) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb44(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 0,H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->H;
	op & (1 << 0) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb45(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 0,L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->L;
	op & (1 << 0) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb46(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 0,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = read_u8(r16->HL);
	op & (1 << 0) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb47(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 0,A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->A;
	op & (1 << 0) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb48(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 1,B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->B;
	op & (1 << 1) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb49(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 1,C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->C;
	op & (1 << 1) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb4a(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 1,D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->D;
	op & (1 << 1) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb4b(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 1,E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->E;
	op & (1 << 1) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb4c(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 1,H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->H;
	op & (1 << 1) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb4d(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 1,L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->L;
	op & (1 << 1) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb4e(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 1,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = read_u8(r16->HL);
	op & (1 << 1) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb4f(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 1,A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->A;
	op & (1 << 1) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb50(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 2,B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->B;
	op & (1 << 2) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb51(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 2,C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->C;
	op & (1 << 2) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb52(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 2,D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->D;
	op & (1 << 2) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb53(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 2,E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->E;
	op & (1 << 2) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb54(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 2,H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->H;
	op & (1 << 2) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb55(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 2,L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->L;
	op & (1 << 2) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb56(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 2,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = read_u8(r16->HL);
	op & (1 << 2) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb57(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 2,A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->A;
	op & (1 << 2) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb58(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 3,B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->B;
	op & (1 << 3) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb59(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 3,C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->C;
	op & (1 << 3) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb5a(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 3,D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->D;
	op & (1 << 3) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb5b(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 3,E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->E;
	op & (1 << 3) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb5c(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 3,H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->H;
	op & (1 << 3) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb5d(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 3,L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->L;
	op & (1 << 3) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb5e(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 3,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = read_u8(r16->HL);
	op & (1 << 3) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb5f(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 3,A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->A;
	op & (1 << 3) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb60(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 4,B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->B;
	op & (1 << 4) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb61(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 4,C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->C;
	op & (1 << 4) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb62(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 4,D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->D;
	op & (1 << 4) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb63(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 4,E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->E;
	op & (1 << 4) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb64(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 4,H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->H;
	op & (1 << 4) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb65(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 4,L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->L;
	op & (1 << 4) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb66(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 4,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = read_u8(r16->HL);
	op & (1 << 4) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb67(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 4,A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->A;
	op & (1 << 4) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb68(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 5,B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->B;
	op & (1 << 5) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb69(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 5,C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->C;
	op & (1 << 5) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb6a(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 5,D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->D;
	op & (1 << 5) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb6b(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 5,E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->E;
	op & (1 << 5) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb6c(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 5,H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->H;
	op & (1 << 5) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb6d(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 5,L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->L;
	op & (1 << 5) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb6e(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 5,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = read_u8(r16->HL);
	op & (1 << 5) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb6f(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 5,A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->A;
	op & (1 << 5) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb70(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 6,B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->B;
	op & (1 << 6) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb71(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 6,C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->C;
	op & (1 << 6) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb72(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 6,D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->D;
	op & (1 << 6) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb73(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 6,E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->E;
	op & (1 << 6) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb74(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 6,H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->H;
	op & (1 << 6) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb75(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 6,L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->L;
	op & (1 << 6) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb76(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 6,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = read_u8(r16->HL);
	op & (1 << 6) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb77(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 6,A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->A;
	op & (1 << 6) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb78(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 7,B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->B;
	op & (1 << 7) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb79(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 7,C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->C;
	op & (1 << 7) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb7a(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 7,D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->D;
	op & (1 << 7) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb7b(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 7,E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->E;
	op & (1 << 7) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb7c(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 7,H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->H;
	op & (1 << 7) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb7d(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 7,L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->L;
	op & (1 << 7) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb7e(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 7,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = read_u8(r16->HL);
	op & (1 << 7) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}

void op_cb7f(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: BIT 7,A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->A;
	op & (1 << 7) ? clear_z_flag : set_z_flag;
	clear_n_flag;
	set_h_flag;
	r16->PC += 2;
}
