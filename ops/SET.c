#include "gb.h"

void op_cbc0(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 0,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B |= (1 << 0);
}

void op_cbc1(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 0,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C |= (1 << 0);
}

void op_cbc2(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 0,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D |= (1 << 0);
}

void op_cbc3(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 0,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E |= (1 << 0);
}

void op_cbc4(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 0,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H |= (1 << 0);
}

void op_cbc5(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 0,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L |= (1 << 0);
}

void op_cbc6(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 0,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL] |= (1 << 0);
}

void op_cbc7(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 0,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A |= (1 << 0);
}

void op_cbc8(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 1,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B |= (1 << 1);
}

void op_cbc9(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 1,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C |= (1 << 1);
}

void op_cbca(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 1,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D |= (1 << 1);
}

void op_cbcb(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 1,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E |= (1 << 1);
}

void op_cbcc(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 1,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H |= (1 << 1);
}

void op_cbcd(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 1,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L |= (1 << 1);
}

void op_cbce(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 1,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL] |= (1 << 1);
}

void op_cbcf(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 1,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A |= (1 << 1);
}

void op_cbd0(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 2,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B |= (1 << 2);
}

void op_cbd1(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 2,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C |= (1 << 2);
}

void op_cbd2(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 2,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D |= (1 << 2);
}

void op_cbd3(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 2,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E |= (1 << 2);
}

void op_cbd4(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 2,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H |= (1 << 2);
}

void op_cbd5(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 2,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L |= (1 << 2);
}

void op_cbd6(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 2,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL] |= (1 << 2);
}

void op_cbd7(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 2,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A |= (1 << 2);
}

void op_cbd8(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 3,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B |= (1 << 3);
}

void op_cbd9(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 3,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C |= (1 << 3);
}

void op_cbda(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 3,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D |= (1 << 3);
}

void op_cbdb(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 3,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E |= (1 << 3);
}

void op_cbdc(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 3,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H |= (1 << 3);
}

void op_cbdd(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 3,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L |= (1 << 3);
}

void op_cbde(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 3,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL] |= (1 << 3);
}

void op_cbdf(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 3,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A |= (1 << 3);
}

void op_cbe0(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 4,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B |= (1 << 4);
}

void op_cbe1(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 4,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C |= (1 << 4);
}

void op_cbe2(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 4,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D |= (1 << 4);
}

void op_cbe3(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 4,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E |= (1 << 4);
}

void op_cbe4(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 4,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H |= (1 << 4);
}

void op_cbe5(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 4,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L |= (1 << 4);
}

void op_cbe6(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 4,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL] |= (1 << 4);
}

void op_cbe7(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 4,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A |= (1 << 4);
}

void op_cbe8(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 5,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B |= (1 << 5);
}

void op_cbe9(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 5,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C |= (1 << 5);
}

void op_cbea(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 5,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D |= (1 << 5);
}

void op_cbeb(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 5,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E |= (1 << 5);
}

void op_cbec(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 5,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H |= (1 << 5);
}

void op_cbed(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 5,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L |= (1 << 5);
}

void op_cbee(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 5,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL] |= (1 << 5);
}

void op_cbef(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 5,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A |= (1 << 5);
}

void op_cbf0(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 6,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B |= (1 << 6);
}

void op_cbf1(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 6,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C |= (1 << 6);
}

void op_cbf2(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 6,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D |= (1 << 6);
}

void op_cbf3(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 6,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E |= (1 << 6);
}

void op_cbf4(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 6,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H |= (1 << 6);
}

void op_cbf5(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 6,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L |= (1 << 6);
}

void op_cbf6(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 6,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL] |= (1 << 6);
}

void op_cbf7(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 6,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A |= (1 << 6);
}

void op_cbf8(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 7,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->B |= (1 << 7);
}

void op_cbf9(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 7,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->C |= (1 << 7);
}

void op_cbfa(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 7,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->D |= (1 << 7);
}

void op_cbfb(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 7,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->E |= (1 << 7);
}

void op_cbfc(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 7,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->H |= (1 << 7);
}

void op_cbfd(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 7,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->L |= (1 << 7);
}

void op_cbfe(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 7,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	mem[r16->HL] |= (1 << 7);
}

void op_cbff(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit rotations/shifts and bit instructions
		 instruction: SET 7,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/


	t_r8  *r8  = reg;
	t_r16 *r16 = reg;
	r8->A |= (1 << 7);
}

