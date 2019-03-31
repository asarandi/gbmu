#include "gb.h"

void op_c4(void *reg, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: CALL NZ,a16
		   num bytes: 3
		      cycles: 24/12
		       flags: - - - -
	*/

}

void op_cc(void *reg, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: CALL Z,a16
		   num bytes: 3
		      cycles: 24/12
		       flags: - - - -
	*/

}

void op_cd(void *reg, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: CALL a16
		   num bytes: 3
		      cycles: 24
		       flags: - - - -
	*/

}

void op_d4(void *reg, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: CALL NC,a16
		   num bytes: 3
		      cycles: 24/12
		       flags: - - - -
	*/

}

void op_dc(void *reg, uint8_t *mem)
{
	/*
		    category: Jumps/calls
		 instruction: CALL C,a16
		   num bytes: 3
		      cycles: 24/12
		       flags: - - - -
	*/

}

