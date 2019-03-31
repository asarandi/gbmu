#include "gb.h"

void op_c0(void *reg, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: RET NZ
		   num bytes: 1
		      cycles: 20/8
		       flags: - - - -
	*/

}

void op_c8(void *reg, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: RET Z
		   num bytes: 1
		      cycles: 20/8
		       flags: - - - -
	*/

}

void op_c9(void *reg, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: RET
		   num bytes: 1
		      cycles: 16
		       flags: - - - -
	*/

}

void op_d0(void *reg, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: RET NC
		   num bytes: 1
		      cycles: 20/8
		       flags: - - - -
	*/

}

void op_d8(void *reg, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: RET C
		   num bytes: 1
		      cycles: 20/8
		       flags: - - - -
	*/

}

