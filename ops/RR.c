#include "gb.h"

void op_cb18(void *reg, uint8_t *mem)
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
	uint8_t carry = is_c_flag;
	r8->B & 1 ? set_c_flag : clear_c_flag;
	r8->B = (r8->B >> 1) | (carry << 7);
	clear_n_flag;
	clear_h_flag;
	r8->B == 0 ? set_z_flag : clear_z_flag;
}

void op_cb19(void *reg, uint8_t *mem)
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
	uint8_t carry = is_c_flag;
	r8->C & 1 ? set_c_flag : clear_c_flag;
	r8->C = (r8->C >> 1) | (carry << 7);
	clear_n_flag;
	clear_h_flag;
	r8->C == 0 ? set_z_flag : clear_z_flag;
}

void op_cb1a(void *reg, uint8_t *mem)
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
	uint8_t carry = is_c_flag;
	r8->D & 1 ? set_c_flag : clear_c_flag;
	r8->D = (r8->D >> 1) | (carry << 7);
	clear_n_flag;
	clear_h_flag;
	r8->D == 0 ? set_z_flag : clear_z_flag;
}

void op_cb1b(void *reg, uint8_t *mem)
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
	uint8_t carry = is_c_flag;
	r8->E & 1 ? set_c_flag : clear_c_flag;
	r8->E = (r8->E >> 1) | (carry << 7);
	clear_n_flag;
	clear_h_flag;
	r8->E == 0 ? set_z_flag : clear_z_flag;
}

void op_cb1c(void *reg, uint8_t *mem)
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
	uint8_t carry = is_c_flag;
	r8->H & 1 ? set_c_flag : clear_c_flag;
	r8->H = (r8->H >> 1) | (carry << 7);
	clear_n_flag;
	clear_h_flag;
	r8->H == 0 ? set_z_flag : clear_z_flag;
}

void op_cb1d(void *reg, uint8_t *mem)
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
	uint8_t carry = is_c_flag;
	r8->L & 1 ? set_c_flag : clear_c_flag;
	r8->L = (r8->L >> 1) | (carry << 7);
	clear_n_flag;
	clear_h_flag;
	r8->L == 0 ? set_z_flag : clear_z_flag;
}

void op_cb1e(void *reg, uint8_t *mem)
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
	uint8_t carry = is_c_flag;
	mem[r16->HL] & 1 ? set_c_flag : clear_c_flag;
	mem[r16->HL] = (mem[r16->HL] >> 1) | (carry << 7);
	clear_n_flag;
	clear_h_flag;
	mem[r16->HL] == 0 ? set_z_flag : clear_z_flag;
}

void op_cb1f(void *reg, uint8_t *mem)
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
	uint8_t carry = is_c_flag;
	r8->A & 1 ? set_c_flag : clear_c_flag;
	r8->A = (r8->A >> 1) | (carry << 7);
	clear_n_flag;
	clear_h_flag;
	r8->A == 0 ? set_z_flag : clear_z_flag;
}

