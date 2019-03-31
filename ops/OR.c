#include "gb.h"

void op_b0(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: OR B
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A |= r8->B;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
}

void op_b1(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: OR C
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A |= r8->C;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
}

void op_b2(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: OR D
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A |= r8->D;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
}

void op_b3(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: OR E
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A |= r8->E;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
}

void op_b4(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: OR H
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A |= r8->H;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
}

void op_b5(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: OR L
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A |= r8->L;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
}

void op_b6(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: OR (HL)
		   num bytes: 1
		      cycles: 8
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A |= mem[r16->HL];
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
}

void op_b7(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: OR A
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A |= r8->A;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
}

void op_f6(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: OR d8
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A |= mem[(r16->PC)+1];
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	clear_c_flag;
}

