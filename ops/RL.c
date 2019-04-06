#include "gb.h"

void op_cb10(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RL B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t carry = is_c_flag;
	r8->B & 0x80 ? set_c_flag : clear_c_flag;
	r8->B = (r8->B << 1) | carry;
	clear_n_flag;
	clear_h_flag;
	r8->B == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb11(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RL C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t carry = is_c_flag;
	r8->C & 0x80 ? set_c_flag : clear_c_flag;
	r8->C = (r8->C << 1) | carry;
	clear_n_flag;
	clear_h_flag;
	r8->C == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb12(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RL D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t carry = is_c_flag;
	r8->D & 0x80 ? set_c_flag : clear_c_flag;
	r8->D = (r8->D << 1) | carry;
	clear_n_flag;
	clear_h_flag;
	r8->D == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb13(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RL E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t carry = is_c_flag;
	r8->E & 0x80 ? set_c_flag : clear_c_flag;
	r8->E = (r8->E << 1) | carry;
	clear_n_flag;
	clear_h_flag;
	r8->E == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb14(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RL H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t carry = is_c_flag;
	r8->H & 0x80 ? set_c_flag : clear_c_flag;
	r8->H = (r8->H << 1) | carry;
	clear_n_flag;
	clear_h_flag;
	r8->H == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb15(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RL L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t carry = is_c_flag;
	r8->L & 0x80 ? set_c_flag : clear_c_flag;
	r8->L = (r8->L << 1) | carry;
	clear_n_flag;
	clear_h_flag;
	r8->L == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb16(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RL (HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t carry = is_c_flag;
	mem[r16->HL] & 0x80 ? set_c_flag : clear_c_flag;
	mem[r16->HL] = (mem[r16->HL] << 1) | carry;
	clear_n_flag;
	clear_h_flag;
	mem[r16->HL] == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb17(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RL A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t carry = is_c_flag;
	r8->A & 0x80 ? set_c_flag : clear_c_flag;
	r8->A = (r8->A << 1) | carry;
	clear_n_flag;
	clear_h_flag;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

