#include "gb.h"

void op_cb08(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RRC B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->B;
	op = (op >> 1) | ((op & 1) << 7);
	op == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	op & 0x80 ? set_c_flag : clear_c_flag;
	r8->B = op;
	r16->PC += 2;
}

void op_cb09(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RRC C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->C;
	op = (op >> 1) | ((op & 1) << 7);
	op == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	op & 0x80 ? set_c_flag : clear_c_flag;
	r8->C = op;
	r16->PC += 2;
}

void op_cb0a(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RRC D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->D;
	op = (op >> 1) | ((op & 1) << 7);
	op == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	op & 0x80 ? set_c_flag : clear_c_flag;
	r8->D = op;
	r16->PC += 2;
}

void op_cb0b(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RRC E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->E;
	op = (op >> 1) | ((op & 1) << 7);
	op == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	op & 0x80 ? set_c_flag : clear_c_flag;
	r8->E = op;
	r16->PC += 2;
}

void op_cb0c(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RRC H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->H;
	op = (op >> 1) | ((op & 1) << 7);
	op == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	op & 0x80 ? set_c_flag : clear_c_flag;
	r8->H = op;
	r16->PC += 2;
}

void op_cb0d(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RRC L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->L;
	op = (op >> 1) | ((op & 1) << 7);
	op == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	op & 0x80 ? set_c_flag : clear_c_flag;
	r8->L = op;
	r16->PC += 2;
}

void op_cb0e(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RRC (HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = read_u8(r16->HL);
	op = (op >> 1) | ((op & 1) << 7);
	op == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	op & 0x80 ? set_c_flag : clear_c_flag;
	write_u8(r16->HL, op);
	r16->PC += 2;
}

void op_cb0f(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: RRC A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->A;
	op = (op >> 1) | ((op & 1) << 7);
	op == 0 ? set_z_flag : clear_z_flag;
	clear_n_flag;
	clear_h_flag;
	op & 0x80 ? set_c_flag : clear_c_flag;
	r8->A = op;
	r16->PC += 2;
}

