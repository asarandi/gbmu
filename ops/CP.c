#include "gb.h"

void op_b8(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: CP B
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->B;
	r8->A == op ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) < (op & 0xf) ? set_h_flag : clear_h_flag;
	r8->A < op ? set_c_flag : clear_c_flag;
	r16->PC += 1;
}

void op_b9(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: CP C
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->C;
	r8->A == op ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) < (op & 0xf) ? set_h_flag : clear_h_flag;
	r8->A < op ? set_c_flag : clear_c_flag;
	r16->PC += 1;
}

void op_ba(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: CP D
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->D;
	r8->A == op ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) < (op & 0xf) ? set_h_flag : clear_h_flag;
	r8->A < op ? set_c_flag : clear_c_flag;
	r16->PC += 1;
}

void op_bb(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: CP E
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->E;
	r8->A == op ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) < (op & 0xf) ? set_h_flag : clear_h_flag;
	r8->A < op ? set_c_flag : clear_c_flag;
	r16->PC += 1;
}

void op_bc(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: CP H
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->H;
	r8->A == op ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) < (op & 0xf) ? set_h_flag : clear_h_flag;
	r8->A < op ? set_c_flag : clear_c_flag;
	r16->PC += 1;
}

void op_bd(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: CP L
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->L;
	r8->A == op ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) < (op & 0xf) ? set_h_flag : clear_h_flag;
	r8->A < op ? set_c_flag : clear_c_flag;
	r16->PC += 1;
}

void op_be(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: CP (HL)
		   num bytes: 1
		      cycles: 8
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = mem[r16->HL];
	r8->A == op ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) < (op & 0xf) ? set_h_flag : clear_h_flag;
	r8->A < op ? set_c_flag : clear_c_flag;
	r16->PC += 1;
}

void op_bf(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: CP A
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = r8->A;
	r8->A == op ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) < (op & 0xf) ? set_h_flag : clear_h_flag;
	r8->A < op ? set_c_flag : clear_c_flag;
	r16->PC += 1;
}

void op_fe(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: CP d8
		   num bytes: 2
		      cycles: 8
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op = mem[(r16->PC)+1];
	r8->A == op ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) < (op & 0xf) ? set_h_flag : clear_h_flag;
	r8->A < op ? set_c_flag : clear_c_flag;
	r16->PC += 2;
}

