#include "gb.h"

void op_a0(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: AND B
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 1 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->B;
	r8->A &= op;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	set_h_flag;
	clear_c_flag;
}

void op_a1(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: AND C
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 1 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->C;
	r8->A &= op;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	set_h_flag;
	clear_c_flag;
}

void op_a2(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: AND D
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 1 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->D;
	r8->A &= op;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	set_h_flag;
	clear_c_flag;
}

void op_a3(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: AND E
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 1 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->E;
	r8->A &= op;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	set_h_flag;
	clear_c_flag;
}

void op_a4(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: AND H
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 1 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->H;
	r8->A &= op;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	set_h_flag;
	clear_c_flag;
}

void op_a5(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: AND L
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 1 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->L;
	r8->A &= op;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	set_h_flag;
	clear_c_flag;
}

void op_a6(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: AND (HL)
		   num bytes: 1
		      cycles: 8
		       flags: Z 0 1 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = mem[r16->HL];
	r8->A &= op;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	set_h_flag;
	clear_c_flag;
}

void op_a7(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: AND A
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 1 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->A;
	r8->A &= op;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	set_h_flag;
	clear_c_flag;
}

void op_e6(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: AND d8
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = mem[(r16->PC)+1];
	r8->A &= op;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	set_h_flag;
	clear_c_flag;
}

