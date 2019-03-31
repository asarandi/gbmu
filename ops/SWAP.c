#include "gb.h"

void op_cb30(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SWAP B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
	r8->B = ((r8->B & 0xf) << 4) | ((r8->B & 0xf0) >> 4);
}

void op_cb31(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SWAP C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
	r8->C = ((r8->C & 0xf) << 4) | ((r8->C & 0xf0) >> 4);
}

void op_cb32(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SWAP D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
	r8->D = ((r8->D & 0xf) << 4) | ((r8->D & 0xf0) >> 4);
}

void op_cb33(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SWAP E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
	r8->E = ((r8->E & 0xf) << 4) | ((r8->E & 0xf0) >> 4);
}

void op_cb34(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SWAP H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
	r8->H = ((r8->H & 0xf) << 4) | ((r8->H & 0xf0) >> 4);
}

void op_cb35(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SWAP L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
	r8->L = ((r8->L & 0xf) << 4) | ((r8->L & 0xf0) >> 4);
}

void op_cb36(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SWAP (HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL] == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
	mem[r16->HL] = ((mem[r16->HL] & 0xf) << 4) | ((mem[r16->HL] & 0xf0) >> 4);
}

void op_cb37(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SWAP A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
	r8->A = ((r8->A & 0xf) << 4) | ((r8->A & 0xf0) >> 4);
}

