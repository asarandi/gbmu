void op_01(void *reg, uint8_t *mem)
{
	/*
		    category: 16bit load/store/move instructions
		 instruction: LD BC,d16
		   num bytes: 3
		      cycles: 12
		       flags: - - - -
	*/

}

void op_02(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD (BC),A
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/

}

void op_06(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD B,d8
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/

}

void op_08(void *reg, uint8_t *mem)
{
	/*
		    category: 16bit load/store/move instructions
		 instruction: LD (a16),SP
		   num bytes: 3
		      cycles: 20
		       flags: - - - -
	*/

}

void op_0a(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD A,(BC)
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/

}

void op_0e(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD C,d8
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/

}

void op_11(void *reg, uint8_t *mem)
{
	/*
		    category: 16bit load/store/move instructions
		 instruction: LD DE,d16
		   num bytes: 3
		      cycles: 12
		       flags: - - - -
	*/

}

void op_12(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD (DE),A
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/

}

void op_16(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD D,d8
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/

}

void op_1a(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD A,(DE)
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/

}

void op_1e(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD E,d8
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/

}

void op_21(void *reg, uint8_t *mem)
{
	/*
		    category: 16bit load/store/move instructions
		 instruction: LD HL,d16
		   num bytes: 3
		      cycles: 12
		       flags: - - - -
	*/

}

void op_22(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD (HL+),A
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/

}

void op_26(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD H,d8
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/

}

void op_2a(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD A,(HL+)
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/

}

void op_2e(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD L,d8
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/

}

void op_31(void *reg, uint8_t *mem)
{
	/*
		    category: 16bit load/store/move instructions
		 instruction: LD SP,d16
		   num bytes: 3
		      cycles: 12
		       flags: - - - -
	*/

}

void op_32(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD (HL-),A
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/

}

void op_36(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD (HL),d8
		   num bytes: 2
		      cycles: 12
		       flags: - - - -
	*/

}

void op_3a(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD A,(HL-)
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/

}

void op_3e(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD A,d8
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/

}

void op_40(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD B,B
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_41(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD B,C
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_42(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD B,D
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_43(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD B,E
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_44(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD B,H
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_45(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD B,L
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_46(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD B,(HL)
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/

}

void op_47(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD B,A
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_48(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD C,B
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_49(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD C,C
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_4a(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD C,D
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_4b(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD C,E
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_4c(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD C,H
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_4d(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD C,L
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_4e(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD C,(HL)
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/

}

void op_4f(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD C,A
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_50(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD D,B
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_51(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD D,C
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_52(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD D,D
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_53(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD D,E
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_54(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD D,H
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_55(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD D,L
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_56(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD D,(HL)
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/

}

void op_57(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD D,A
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_58(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD E,B
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_59(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD E,C
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_5a(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD E,D
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_5b(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD E,E
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_5c(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD E,H
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_5d(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD E,L
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_5e(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD E,(HL)
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/

}

void op_5f(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD E,A
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_60(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD H,B
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_61(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD H,C
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_62(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD H,D
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_63(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD H,E
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_64(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD H,H
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_65(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD H,L
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_66(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD H,(HL)
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/

}

void op_67(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD H,A
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_68(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD L,B
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_69(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD L,C
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_6a(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD L,D
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_6b(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD L,E
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_6c(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD L,H
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_6d(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD L,L
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_6e(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD L,(HL)
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/

}

void op_6f(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD L,A
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_70(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD (HL),B
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/

}

void op_71(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD (HL),C
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/

}

void op_72(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD (HL),D
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/

}

void op_73(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD (HL),E
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/

}

void op_74(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD (HL),H
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/

}

void op_75(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD (HL),L
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/

}

void op_77(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD (HL),A
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/

}

void op_78(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD A,B
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_79(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD A,C
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_7a(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD A,D
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_7b(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD A,E
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_7c(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD A,H
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_7d(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD A,L
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_7e(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD A,(HL)
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/

}

void op_7f(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD A,A
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/

}

void op_e2(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD (C),A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/

}

void op_ea(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD (a16),A
		   num bytes: 3
		      cycles: 16
		       flags: - - - -
	*/

}

void op_f2(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD A,(C)
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/

}

void op_f8(void *reg, uint8_t *mem)
{
	/*
		    category: 16bit load/store/move instructions
		 instruction: LD HL,SP+r8
		   num bytes: 2
		      cycles: 12
		       flags: 0 0 H C
	*/

}

void op_f9(void *reg, uint8_t *mem)
{
	/*
		    category: 16bit load/store/move instructions
		 instruction: LD SP,HL
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/

}

void op_fa(void *reg, uint8_t *mem)
{
	/*
		    category: 8bit load/store/move instructions
		 instruction: LD A,(a16)
		   num bytes: 3
		      cycles: 16
		       flags: - - - -
	*/

}

