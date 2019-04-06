#include "gb.h"

void op_cb38(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRL B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	clear_n_flag;
	clear_h_flag;
	r8->B & 1 ? set_c_flag : clear_c_flag;
	r8->B >>= 1;
	r8->B == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb39(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRL C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	clear_n_flag;
	clear_h_flag;
	r8->C & 1 ? set_c_flag : clear_c_flag;
	r8->C >>= 1;
	r8->C == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb3a(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRL D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	clear_n_flag;
	clear_h_flag;
	r8->D & 1 ? set_c_flag : clear_c_flag;
	r8->D >>= 1;
	r8->D == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb3b(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRL E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	clear_n_flag;
	clear_h_flag;
	r8->E & 1 ? set_c_flag : clear_c_flag;
	r8->E >>= 1;
	r8->E == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb3c(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRL H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	clear_n_flag;
	clear_h_flag;
	r8->H & 1 ? set_c_flag : clear_c_flag;
	r8->H >>= 1;
	r8->H == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb3d(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRL L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	clear_n_flag;
	clear_h_flag;
	r8->L & 1 ? set_c_flag : clear_c_flag;
	r8->L >>= 1;
	r8->L == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb3e(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRL (HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	clear_n_flag;
	clear_h_flag;
	mem[r16->HL] & 1 ? set_c_flag : clear_c_flag;
	mem[r16->HL] >>= 1;
	mem[r16->HL] == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb3f(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRL A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	clear_n_flag;
	clear_h_flag;
	r8->A & 1 ? set_c_flag : clear_c_flag;
	r8->A >>= 1;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

