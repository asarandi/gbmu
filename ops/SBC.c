#include "gb.h"

void op_98(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SBC A,B
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->B;
	(r8->A - (op + is_c_flag)) == 0 ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) < ((op + is_c_flag) & 0xf) ? set_h_flag : clear_h_flag;
	r8->A < (op + is_c_flag) ? set_c_flag : clear_c_flag;
	r8->A = r8->A - (op + is_c_flag);
	r16->PC += 1;
}

void op_99(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SBC A,C
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->C;
	(r8->A - (op + is_c_flag)) == 0 ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) < ((op + is_c_flag) & 0xf) ? set_h_flag : clear_h_flag;
	r8->A < (op + is_c_flag) ? set_c_flag : clear_c_flag;
	r8->A = r8->A - (op + is_c_flag);
	r16->PC += 1;
}

void op_9a(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SBC A,D
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->D;
	(r8->A - (op + is_c_flag)) == 0 ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) < ((op + is_c_flag) & 0xf) ? set_h_flag : clear_h_flag;
	r8->A < (op + is_c_flag) ? set_c_flag : clear_c_flag;
	r8->A = r8->A - (op + is_c_flag);
	r16->PC += 1;
}

void op_9b(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SBC A,E
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->E;
	(r8->A - (op + is_c_flag)) == 0 ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) < ((op + is_c_flag) & 0xf) ? set_h_flag : clear_h_flag;
	r8->A < (op + is_c_flag) ? set_c_flag : clear_c_flag;
	r8->A = r8->A - (op + is_c_flag);
	r16->PC += 1;
}

void op_9c(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SBC A,H
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->H;
	(r8->A - (op + is_c_flag)) == 0 ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) < ((op + is_c_flag) & 0xf) ? set_h_flag : clear_h_flag;
	r8->A < (op + is_c_flag) ? set_c_flag : clear_c_flag;
	r8->A = r8->A - (op + is_c_flag);
	r16->PC += 1;
}

void op_9d(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SBC A,L
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->L;
	(r8->A - (op + is_c_flag)) == 0 ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) < ((op + is_c_flag) & 0xf) ? set_h_flag : clear_h_flag;
	r8->A < (op + is_c_flag) ? set_c_flag : clear_c_flag;
	r8->A = r8->A - (op + is_c_flag);
	r16->PC += 1;
}

void op_9e(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SBC A,(HL)
		   num bytes: 1
		      cycles: 8
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = mem[r16->HL];
	(r8->A - (op + is_c_flag)) == 0 ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) < ((op + is_c_flag) & 0xf) ? set_h_flag : clear_h_flag;
	r8->A < (op + is_c_flag) ? set_c_flag : clear_c_flag;
	r8->A = r8->A - (op + is_c_flag);
	r16->PC += 1;
}

void op_9f(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SBC A,A
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = r8->A;
	(r8->A - (op + is_c_flag)) == 0 ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) < ((op + is_c_flag) & 0xf) ? set_h_flag : clear_h_flag;
	r8->A < (op + is_c_flag) ? set_c_flag : clear_c_flag;
	r8->A = r8->A - (op + is_c_flag);
	r16->PC += 1;
}

void op_de(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit arithmetic/logical instructions
		 instruction: SBC A,d8
		   num bytes: 2
		      cycles: 8
		       flags: Z 1 H C
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	uint8_t op;
	op = mem[(r16->PC)+1];
	(r8->A - (op + is_c_flag)) == 0 ? set_z_flag : clear_z_flag;
	set_n_flag;
	(r8->A & 0xf) < ((op + is_c_flag) & 0xf) ? set_h_flag : clear_h_flag;
	r8->A < (op + is_c_flag) ? set_c_flag : clear_c_flag;
	r8->A = r8->A - (op + is_c_flag);
	r16->PC += 2;
}

