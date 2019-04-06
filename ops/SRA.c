#include "gb.h"

void op_cb28(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRA B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	clear_n_flag;
	clear_h_flag;
	r8->B & 1 ? set_c_flag : clear_c_flag;
	r8->B = (r8->B & 0x80) | (r8->B >> 1) ;
	r8->B == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb29(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRA C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	clear_n_flag;
	clear_h_flag;
	r8->C & 1 ? set_c_flag : clear_c_flag;
	r8->C = (r8->C & 0x80) | (r8->C >> 1) ;
	r8->C == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb2a(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRA D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	clear_n_flag;
	clear_h_flag;
	r8->D & 1 ? set_c_flag : clear_c_flag;
	r8->D = (r8->D & 0x80) | (r8->D >> 1) ;
	r8->D == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb2b(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRA E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	clear_n_flag;
	clear_h_flag;
	r8->E & 1 ? set_c_flag : clear_c_flag;
	r8->E = (r8->E & 0x80) | (r8->E >> 1) ;
	r8->E == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb2c(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRA H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	clear_n_flag;
	clear_h_flag;
	r8->H & 1 ? set_c_flag : clear_c_flag;
	r8->H = (r8->H & 0x80) | (r8->H >> 1) ;
	r8->H == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb2d(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRA L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	clear_n_flag;
	clear_h_flag;
	r8->L & 1 ? set_c_flag : clear_c_flag;
	r8->L = (r8->L & 0x80) | (r8->L >> 1) ;
	r8->L == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb2e(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRA (HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	clear_n_flag;
	clear_h_flag;
	mem[r16->HL] & 1 ? set_c_flag : clear_c_flag;
	mem[r16->HL] = (mem[r16->HL] & 0x80) | (mem[r16->HL] >> 1) ;
	mem[r16->HL] == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb2f(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SRA A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	clear_n_flag;
	clear_h_flag;
	r8->A & 1 ? set_c_flag : clear_c_flag;
	r8->A = (r8->A & 0x80) | (r8->A >> 1) ;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

