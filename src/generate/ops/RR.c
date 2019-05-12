#include "gb.h"

void op_cb18(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RR B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->B;
	uint8_t carry = is_c_flag;
	op & 1 ? set_c_flag : clear_c_flag;
	op = (op >> 1) | (carry << 7);
	clear_n_flag;
	clear_h_flag;
	op == 0 ? set_z_flag : clear_z_flag;
	r8->B = op;
	r16->PC += 2;
}

void op_cb19(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RR C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->C;
	uint8_t carry = is_c_flag;
	op & 1 ? set_c_flag : clear_c_flag;
	op = (op >> 1) | (carry << 7);
	clear_n_flag;
	clear_h_flag;
	op == 0 ? set_z_flag : clear_z_flag;
	r8->C = op;
	r16->PC += 2;
}

void op_cb1a(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RR D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->D;
	uint8_t carry = is_c_flag;
	op & 1 ? set_c_flag : clear_c_flag;
	op = (op >> 1) | (carry << 7);
	clear_n_flag;
	clear_h_flag;
	op == 0 ? set_z_flag : clear_z_flag;
	r8->D = op;
	r16->PC += 2;
}

void op_cb1b(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RR E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->E;
	uint8_t carry = is_c_flag;
	op & 1 ? set_c_flag : clear_c_flag;
	op = (op >> 1) | (carry << 7);
	clear_n_flag;
	clear_h_flag;
	op == 0 ? set_z_flag : clear_z_flag;
	r8->E = op;
	r16->PC += 2;
}

void op_cb1c(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RR H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->H;
	uint8_t carry = is_c_flag;
	op & 1 ? set_c_flag : clear_c_flag;
	op = (op >> 1) | (carry << 7);
	clear_n_flag;
	clear_h_flag;
	op == 0 ? set_z_flag : clear_z_flag;
	r8->H = op;
	r16->PC += 2;
}

void op_cb1d(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RR L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->L;
	uint8_t carry = is_c_flag;
	op & 1 ? set_c_flag : clear_c_flag;
	op = (op >> 1) | (carry << 7);
	clear_n_flag;
	clear_h_flag;
	op == 0 ? set_z_flag : clear_z_flag;
	r8->L = op;
	r16->PC += 2;
}

void op_cb1e(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RR (HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = read_u8(r16->HL);
	uint8_t carry = is_c_flag;
	op & 1 ? set_c_flag : clear_c_flag;
	op = (op >> 1) | (carry << 7);
	clear_n_flag;
	clear_h_flag;
	op == 0 ? set_z_flag : clear_z_flag;
	write_u8(r16->HL, op);
	r16->PC += 2;
}

void op_cb1f(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RR A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->A;
	uint8_t carry = is_c_flag;
	op & 1 ? set_c_flag : clear_c_flag;
	op = (op >> 1) | (carry << 7);
	clear_n_flag;
	clear_h_flag;
	op == 0 ? set_z_flag : clear_z_flag;
	r8->A = op;
	r16->PC += 2;
}

