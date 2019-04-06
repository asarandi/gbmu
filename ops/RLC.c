#include "gb.h"

void op_cb00(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RLC B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B = (r8->B << 1) | (r8->B >> 7);
	r8->B == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	r8->B & 1 ? set_c_flag : clear_c_flag;
	r16->PC += 2;
}

void op_cb01(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RLC C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C = (r8->C << 1) | (r8->C >> 7);
	r8->C == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	r8->C & 1 ? set_c_flag : clear_c_flag;
	r16->PC += 2;
}

void op_cb02(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RLC D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D = (r8->D << 1) | (r8->D >> 7);
	r8->D == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	r8->D & 1 ? set_c_flag : clear_c_flag;
	r16->PC += 2;
}

void op_cb03(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RLC E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E = (r8->E << 1) | (r8->E >> 7);
	r8->E == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	r8->E & 1 ? set_c_flag : clear_c_flag;
	r16->PC += 2;
}

void op_cb04(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RLC H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H = (r8->H << 1) | (r8->H >> 7);
	r8->H == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	r8->H & 1 ? set_c_flag : clear_c_flag;
	r16->PC += 2;
}

void op_cb05(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RLC L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L = (r8->L << 1) | (r8->L >> 7);
	r8->L == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	r8->L & 1 ? set_c_flag : clear_c_flag;
	r16->PC += 2;
}

void op_cb06(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RLC (HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL] = (mem[r16->HL] << 1) | (mem[r16->HL] >> 7);
	mem[r16->HL] == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	mem[r16->HL] & 1 ? set_c_flag : clear_c_flag;
	r16->PC += 2;
}

void op_cb07(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RLC A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A = (r8->A << 1) | (r8->A >> 7);
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	r8->A & 1 ? set_c_flag : clear_c_flag;
	r16->PC += 2;
}

