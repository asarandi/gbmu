#include "gb.h"

void op_cb20(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SLA B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	clear_n_flag;
	clear_h_flag;
	r8->B & 0x80 ? set_c_flag : clear_c_flag;
	r8->B <<= 1;
	r8->B == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb21(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SLA C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	clear_n_flag;
	clear_h_flag;
	r8->C & 0x80 ? set_c_flag : clear_c_flag;
	r8->C <<= 1;
	r8->C == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb22(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SLA D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	clear_n_flag;
	clear_h_flag;
	r8->D & 0x80 ? set_c_flag : clear_c_flag;
	r8->D <<= 1;
	r8->D == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb23(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SLA E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	clear_n_flag;
	clear_h_flag;
	r8->E & 0x80 ? set_c_flag : clear_c_flag;
	r8->E <<= 1;
	r8->E == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb24(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SLA H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	clear_n_flag;
	clear_h_flag;
	r8->H & 0x80 ? set_c_flag : clear_c_flag;
	r8->H <<= 1;
	r8->H == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb25(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SLA L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	clear_n_flag;
	clear_h_flag;
	r8->L & 0x80 ? set_c_flag : clear_c_flag;
	r8->L <<= 1;
	r8->L == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb26(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SLA (HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	clear_n_flag;
	clear_h_flag;
	mem[r16->HL] & 0x80 ? set_c_flag : clear_c_flag;
	mem[r16->HL] <<= 1;
	mem[r16->HL] == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

void op_cb27(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SLA A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	clear_n_flag;
	clear_h_flag;
	r8->A & 0x80 ? set_c_flag : clear_c_flag;
	r8->A <<= 1;
	r8->A == 0 ? set_z_flag : clear_z_flag;
	r16->PC += 2;
}

