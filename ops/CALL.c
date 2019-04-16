#include "gb.h"

void op_c4(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: CALL NZ,a16
		   num bytes: 3
		      cycles: 24/12
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	if (is_z_flag)  { r16->PC += 3; return; };
	r16->SP -= 2;
	write_u16(r16->SP, r16->PC + 3);
	r16->PC = read_u16(r16->PC + 1);
}

void op_cc(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: CALL Z,a16
		   num bytes: 3
		      cycles: 24/12
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	if (!is_z_flag)  { r16->PC += 3; return; };
	r16->SP -= 2;
	write_u16(r16->SP, r16->PC + 3);
	r16->PC = read_u16(r16->PC + 1);
}

void op_cd(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: CALL a16
		   num bytes: 3
		      cycles: 24
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r16->SP -= 2;
	write_u16(r16->SP, r16->PC + 3);
	r16->PC = read_u16(r16->PC + 1);
}

void op_d4(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: CALL NC,a16
		   num bytes: 3
		      cycles: 24/12
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	if (is_c_flag)  { r16->PC += 3; return; };
	r16->SP -= 2;
	write_u16(r16->SP, r16->PC + 3);
	r16->PC = read_u16(r16->PC + 1);
}

void op_dc(void *reg, t_state *state, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: CALL C,a16
		   num bytes: 3
		      cycles: 24/12
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	if (!is_c_flag) { r16->PC += 3; return; };
	r16->SP -= 2;
	write_u16(r16->SP, r16->PC + 3);
	r16->PC = read_u16(r16->PC + 1);
}

