void op_00(void *reg, void *data)
{
	/*
		 instruction: NOP
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_01(void *reg, void *data)
{
	/*
		 instruction: LD BC,d16
		   num bytes: 3
		      cycles: 12
		       flags: - - - -
	*/
}


void op_02(void *reg, void *data)
{
	/*
		 instruction: LD (BC),A
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_03(void *reg, void *data)
{
	/*
		 instruction: INC BC
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_04(void *reg, void *data)
{
	/*
		 instruction: INC B
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H -
	*/
	clear_flags_mask(reg, 0x40)
}


void op_05(void *reg, void *data)
{
	/*
		 instruction: DEC B
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H -
	*/
	set_flags_mask(reg, 0x40)
}


void op_06(void *reg, void *data)
{
	/*
		 instruction: LD B,d8
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_07(void *reg, void *data)
{
	/*
		 instruction: RLCA
		   num bytes: 1
		      cycles: 4
		       flags: 0 0 0 C
	*/
	clear_flags_mask(reg, 0xe0)
}


void op_08(void *reg, void *data)
{
	/*
		 instruction: LD (a16),SP
		   num bytes: 3
		      cycles: 20
		       flags: - - - -
	*/
}


void op_09(void *reg, void *data)
{
	/*
		 instruction: ADD HL,BC
		   num bytes: 1
		      cycles: 8
		       flags: - 0 H C
	*/
	clear_flags_mask(reg, 0x40)
}


void op_0a(void *reg, void *data)
{
	/*
		 instruction: LD A,(BC)
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_0b(void *reg, void *data)
{
	/*
		 instruction: DEC BC
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_0c(void *reg, void *data)
{
	/*
		 instruction: INC C
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H -
	*/
	clear_flags_mask(reg, 0x40)
}


void op_0d(void *reg, void *data)
{
	/*
		 instruction: DEC C
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H -
	*/
	set_flags_mask(reg, 0x40)
}


void op_0e(void *reg, void *data)
{
	/*
		 instruction: LD C,d8
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_0f(void *reg, void *data)
{
	/*
		 instruction: RRCA
		   num bytes: 1
		      cycles: 4
		       flags: 0 0 0 C
	*/
	clear_flags_mask(reg, 0xe0)
}


void op_10(void *reg, void *data)
{
	/*
		 instruction: STOP 0
		   num bytes: 2
		      cycles: 4
		       flags: - - - -
	*/
}


void op_11(void *reg, void *data)
{
	/*
		 instruction: LD DE,d16
		   num bytes: 3
		      cycles: 12
		       flags: - - - -
	*/
}


void op_12(void *reg, void *data)
{
	/*
		 instruction: LD (DE),A
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_13(void *reg, void *data)
{
	/*
		 instruction: INC DE
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_14(void *reg, void *data)
{
	/*
		 instruction: INC D
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H -
	*/
	clear_flags_mask(reg, 0x40)
}


void op_15(void *reg, void *data)
{
	/*
		 instruction: DEC D
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H -
	*/
	set_flags_mask(reg, 0x40)
}


void op_16(void *reg, void *data)
{
	/*
		 instruction: LD D,d8
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_17(void *reg, void *data)
{
	/*
		 instruction: RLA
		   num bytes: 1
		      cycles: 4
		       flags: 0 0 0 C
	*/
	clear_flags_mask(reg, 0xe0)
}


void op_18(void *reg, void *data)
{
	/*
		 instruction: JR r8
		   num bytes: 2
		      cycles: 12
		       flags: - - - -
	*/
}


void op_19(void *reg, void *data)
{
	/*
		 instruction: ADD HL,DE
		   num bytes: 1
		      cycles: 8
		       flags: - 0 H C
	*/
	clear_flags_mask(reg, 0x40)
}


void op_1a(void *reg, void *data)
{
	/*
		 instruction: LD A,(DE)
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_1b(void *reg, void *data)
{
	/*
		 instruction: DEC DE
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_1c(void *reg, void *data)
{
	/*
		 instruction: INC E
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H -
	*/
	clear_flags_mask(reg, 0x40)
}


void op_1d(void *reg, void *data)
{
	/*
		 instruction: DEC E
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H -
	*/
	set_flags_mask(reg, 0x40)
}


void op_1e(void *reg, void *data)
{
	/*
		 instruction: LD E,d8
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_1f(void *reg, void *data)
{
	/*
		 instruction: RRA
		   num bytes: 1
		      cycles: 4
		       flags: 0 0 0 C
	*/
	clear_flags_mask(reg, 0xe0)
}


void op_20(void *reg, void *data)
{
	/*
		 instruction: JR NZ,r8
		   num bytes: 2
		      cycles: 12/8
		       flags: - - - -
	*/
}


void op_21(void *reg, void *data)
{
	/*
		 instruction: LD HL,d16
		   num bytes: 3
		      cycles: 12
		       flags: - - - -
	*/
}


void op_22(void *reg, void *data)
{
	/*
		 instruction: LD (HL+),A
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_23(void *reg, void *data)
{
	/*
		 instruction: INC HL
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_24(void *reg, void *data)
{
	/*
		 instruction: INC H
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H -
	*/
	clear_flags_mask(reg, 0x40)
}


void op_25(void *reg, void *data)
{
	/*
		 instruction: DEC H
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H -
	*/
	set_flags_mask(reg, 0x40)
}


void op_26(void *reg, void *data)
{
	/*
		 instruction: LD H,d8
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_27(void *reg, void *data)
{
	/*
		 instruction: DAA
		   num bytes: 1
		      cycles: 4
		       flags: Z - 0 C
	*/
	clear_flags_mask(reg, 0x20)
}


void op_28(void *reg, void *data)
{
	/*
		 instruction: JR Z,r8
		   num bytes: 2
		      cycles: 12/8
		       flags: - - - -
	*/
}


void op_29(void *reg, void *data)
{
	/*
		 instruction: ADD HL,HL
		   num bytes: 1
		      cycles: 8
		       flags: - 0 H C
	*/
	clear_flags_mask(reg, 0x40)
}


void op_2a(void *reg, void *data)
{
	/*
		 instruction: LD A,(HL+)
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_2b(void *reg, void *data)
{
	/*
		 instruction: DEC HL
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_2c(void *reg, void *data)
{
	/*
		 instruction: INC L
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H -
	*/
	clear_flags_mask(reg, 0x40)
}


void op_2d(void *reg, void *data)
{
	/*
		 instruction: DEC L
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H -
	*/
	set_flags_mask(reg, 0x40)
}


void op_2e(void *reg, void *data)
{
	/*
		 instruction: LD L,d8
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_2f(void *reg, void *data)
{
	/*
		 instruction: CPL
		   num bytes: 1
		      cycles: 4
		       flags: - 1 1 -
	*/
	set_flags_mask(reg, 0x60)
}


void op_30(void *reg, void *data)
{
	/*
		 instruction: JR NC,r8
		   num bytes: 2
		      cycles: 12/8
		       flags: - - - -
	*/
}


void op_31(void *reg, void *data)
{
	/*
		 instruction: LD SP,d16
		   num bytes: 3
		      cycles: 12
		       flags: - - - -
	*/
}


void op_32(void *reg, void *data)
{
	/*
		 instruction: LD (HL-),A
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_33(void *reg, void *data)
{
	/*
		 instruction: INC SP
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_34(void *reg, void *data)
{
	/*
		 instruction: INC (HL)
		   num bytes: 1
		      cycles: 12
		       flags: Z 0 H -
	*/
	clear_flags_mask(reg, 0x40)
}


void op_35(void *reg, void *data)
{
	/*
		 instruction: DEC (HL)
		   num bytes: 1
		      cycles: 12
		       flags: Z 1 H -
	*/
	set_flags_mask(reg, 0x40)
}


void op_36(void *reg, void *data)
{
	/*
		 instruction: LD (HL),d8
		   num bytes: 2
		      cycles: 12
		       flags: - - - -
	*/
}


void op_37(void *reg, void *data)
{
	/*
		 instruction: SCF
		   num bytes: 1
		      cycles: 4
		       flags: - 0 0 1
	*/
	clear_flags_mask(reg, 0x60)
	set_flags_mask(reg, 0x10)
}


void op_38(void *reg, void *data)
{
	/*
		 instruction: JR C,r8
		   num bytes: 2
		      cycles: 12/8
		       flags: - - - -
	*/
}


void op_39(void *reg, void *data)
{
	/*
		 instruction: ADD HL,SP
		   num bytes: 1
		      cycles: 8
		       flags: - 0 H C
	*/
	clear_flags_mask(reg, 0x40)
}


void op_3a(void *reg, void *data)
{
	/*
		 instruction: LD A,(HL-)
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_3b(void *reg, void *data)
{
	/*
		 instruction: DEC SP
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_3c(void *reg, void *data)
{
	/*
		 instruction: INC A
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H -
	*/
	clear_flags_mask(reg, 0x40)
}


void op_3d(void *reg, void *data)
{
	/*
		 instruction: DEC A
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H -
	*/
	set_flags_mask(reg, 0x40)
}


void op_3e(void *reg, void *data)
{
	/*
		 instruction: LD A,d8
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_3f(void *reg, void *data)
{
	/*
		 instruction: CCF
		   num bytes: 1
		      cycles: 4
		       flags: - 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_40(void *reg, void *data)
{
	/*
		 instruction: LD B,B
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_41(void *reg, void *data)
{
	/*
		 instruction: LD B,C
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_42(void *reg, void *data)
{
	/*
		 instruction: LD B,D
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_43(void *reg, void *data)
{
	/*
		 instruction: LD B,E
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_44(void *reg, void *data)
{
	/*
		 instruction: LD B,H
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_45(void *reg, void *data)
{
	/*
		 instruction: LD B,L
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_46(void *reg, void *data)
{
	/*
		 instruction: LD B,(HL)
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_47(void *reg, void *data)
{
	/*
		 instruction: LD B,A
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_48(void *reg, void *data)
{
	/*
		 instruction: LD C,B
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_49(void *reg, void *data)
{
	/*
		 instruction: LD C,C
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_4a(void *reg, void *data)
{
	/*
		 instruction: LD C,D
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_4b(void *reg, void *data)
{
	/*
		 instruction: LD C,E
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_4c(void *reg, void *data)
{
	/*
		 instruction: LD C,H
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_4d(void *reg, void *data)
{
	/*
		 instruction: LD C,L
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_4e(void *reg, void *data)
{
	/*
		 instruction: LD C,(HL)
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_4f(void *reg, void *data)
{
	/*
		 instruction: LD C,A
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_50(void *reg, void *data)
{
	/*
		 instruction: LD D,B
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_51(void *reg, void *data)
{
	/*
		 instruction: LD D,C
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_52(void *reg, void *data)
{
	/*
		 instruction: LD D,D
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_53(void *reg, void *data)
{
	/*
		 instruction: LD D,E
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_54(void *reg, void *data)
{
	/*
		 instruction: LD D,H
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_55(void *reg, void *data)
{
	/*
		 instruction: LD D,L
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_56(void *reg, void *data)
{
	/*
		 instruction: LD D,(HL)
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_57(void *reg, void *data)
{
	/*
		 instruction: LD D,A
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_58(void *reg, void *data)
{
	/*
		 instruction: LD E,B
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_59(void *reg, void *data)
{
	/*
		 instruction: LD E,C
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_5a(void *reg, void *data)
{
	/*
		 instruction: LD E,D
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_5b(void *reg, void *data)
{
	/*
		 instruction: LD E,E
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_5c(void *reg, void *data)
{
	/*
		 instruction: LD E,H
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_5d(void *reg, void *data)
{
	/*
		 instruction: LD E,L
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_5e(void *reg, void *data)
{
	/*
		 instruction: LD E,(HL)
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_5f(void *reg, void *data)
{
	/*
		 instruction: LD E,A
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_60(void *reg, void *data)
{
	/*
		 instruction: LD H,B
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_61(void *reg, void *data)
{
	/*
		 instruction: LD H,C
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_62(void *reg, void *data)
{
	/*
		 instruction: LD H,D
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_63(void *reg, void *data)
{
	/*
		 instruction: LD H,E
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_64(void *reg, void *data)
{
	/*
		 instruction: LD H,H
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_65(void *reg, void *data)
{
	/*
		 instruction: LD H,L
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_66(void *reg, void *data)
{
	/*
		 instruction: LD H,(HL)
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_67(void *reg, void *data)
{
	/*
		 instruction: LD H,A
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_68(void *reg, void *data)
{
	/*
		 instruction: LD L,B
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_69(void *reg, void *data)
{
	/*
		 instruction: LD L,C
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_6a(void *reg, void *data)
{
	/*
		 instruction: LD L,D
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_6b(void *reg, void *data)
{
	/*
		 instruction: LD L,E
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_6c(void *reg, void *data)
{
	/*
		 instruction: LD L,H
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_6d(void *reg, void *data)
{
	/*
		 instruction: LD L,L
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_6e(void *reg, void *data)
{
	/*
		 instruction: LD L,(HL)
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_6f(void *reg, void *data)
{
	/*
		 instruction: LD L,A
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_70(void *reg, void *data)
{
	/*
		 instruction: LD (HL),B
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_71(void *reg, void *data)
{
	/*
		 instruction: LD (HL),C
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_72(void *reg, void *data)
{
	/*
		 instruction: LD (HL),D
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_73(void *reg, void *data)
{
	/*
		 instruction: LD (HL),E
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_74(void *reg, void *data)
{
	/*
		 instruction: LD (HL),H
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_75(void *reg, void *data)
{
	/*
		 instruction: LD (HL),L
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_76(void *reg, void *data)
{
	/*
		 instruction: HALT
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_77(void *reg, void *data)
{
	/*
		 instruction: LD (HL),A
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_78(void *reg, void *data)
{
	/*
		 instruction: LD A,B
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_79(void *reg, void *data)
{
	/*
		 instruction: LD A,C
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_7a(void *reg, void *data)
{
	/*
		 instruction: LD A,D
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_7b(void *reg, void *data)
{
	/*
		 instruction: LD A,E
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_7c(void *reg, void *data)
{
	/*
		 instruction: LD A,H
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_7d(void *reg, void *data)
{
	/*
		 instruction: LD A,L
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_7e(void *reg, void *data)
{
	/*
		 instruction: LD A,(HL)
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_7f(void *reg, void *data)
{
	/*
		 instruction: LD A,A
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_80(void *reg, void *data)
{
	/*
		 instruction: ADD A,B
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/
	clear_flags_mask(reg, 0x40)
}


void op_81(void *reg, void *data)
{
	/*
		 instruction: ADD A,C
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/
	clear_flags_mask(reg, 0x40)
}


void op_82(void *reg, void *data)
{
	/*
		 instruction: ADD A,D
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/
	clear_flags_mask(reg, 0x40)
}


void op_83(void *reg, void *data)
{
	/*
		 instruction: ADD A,E
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/
	clear_flags_mask(reg, 0x40)
}


void op_84(void *reg, void *data)
{
	/*
		 instruction: ADD A,H
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/
	clear_flags_mask(reg, 0x40)
}


void op_85(void *reg, void *data)
{
	/*
		 instruction: ADD A,L
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/
	clear_flags_mask(reg, 0x40)
}


void op_86(void *reg, void *data)
{
	/*
		 instruction: ADD A,(HL)
		   num bytes: 1
		      cycles: 8
		       flags: Z 0 H C
	*/
	clear_flags_mask(reg, 0x40)
}


void op_87(void *reg, void *data)
{
	/*
		 instruction: ADD A,A
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/
	clear_flags_mask(reg, 0x40)
}


void op_88(void *reg, void *data)
{
	/*
		 instruction: ADC A,B
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/
	clear_flags_mask(reg, 0x40)
}


void op_89(void *reg, void *data)
{
	/*
		 instruction: ADC A,C
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/
	clear_flags_mask(reg, 0x40)
}


void op_8a(void *reg, void *data)
{
	/*
		 instruction: ADC A,D
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/
	clear_flags_mask(reg, 0x40)
}


void op_8b(void *reg, void *data)
{
	/*
		 instruction: ADC A,E
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/
	clear_flags_mask(reg, 0x40)
}


void op_8c(void *reg, void *data)
{
	/*
		 instruction: ADC A,H
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/
	clear_flags_mask(reg, 0x40)
}


void op_8d(void *reg, void *data)
{
	/*
		 instruction: ADC A,L
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/
	clear_flags_mask(reg, 0x40)
}


void op_8e(void *reg, void *data)
{
	/*
		 instruction: ADC A,(HL)
		   num bytes: 1
		      cycles: 8
		       flags: Z 0 H C
	*/
	clear_flags_mask(reg, 0x40)
}


void op_8f(void *reg, void *data)
{
	/*
		 instruction: ADC A,A
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 H C
	*/
	clear_flags_mask(reg, 0x40)
}


void op_90(void *reg, void *data)
{
	/*
		 instruction: SUB B
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/
	set_flags_mask(reg, 0x40)
}


void op_91(void *reg, void *data)
{
	/*
		 instruction: SUB C
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/
	set_flags_mask(reg, 0x40)
}


void op_92(void *reg, void *data)
{
	/*
		 instruction: SUB D
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/
	set_flags_mask(reg, 0x40)
}


void op_93(void *reg, void *data)
{
	/*
		 instruction: SUB E
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/
	set_flags_mask(reg, 0x40)
}


void op_94(void *reg, void *data)
{
	/*
		 instruction: SUB H
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/
	set_flags_mask(reg, 0x40)
}


void op_95(void *reg, void *data)
{
	/*
		 instruction: SUB L
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/
	set_flags_mask(reg, 0x40)
}


void op_96(void *reg, void *data)
{
	/*
		 instruction: SUB (HL)
		   num bytes: 1
		      cycles: 8
		       flags: Z 1 H C
	*/
	set_flags_mask(reg, 0x40)
}


void op_97(void *reg, void *data)
{
	/*
		 instruction: SUB A
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/
	set_flags_mask(reg, 0x40)
}


void op_98(void *reg, void *data)
{
	/*
		 instruction: SBC A,B
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/
	set_flags_mask(reg, 0x40)
}


void op_99(void *reg, void *data)
{
	/*
		 instruction: SBC A,C
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/
	set_flags_mask(reg, 0x40)
}


void op_9a(void *reg, void *data)
{
	/*
		 instruction: SBC A,D
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/
	set_flags_mask(reg, 0x40)
}


void op_9b(void *reg, void *data)
{
	/*
		 instruction: SBC A,E
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/
	set_flags_mask(reg, 0x40)
}


void op_9c(void *reg, void *data)
{
	/*
		 instruction: SBC A,H
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/
	set_flags_mask(reg, 0x40)
}


void op_9d(void *reg, void *data)
{
	/*
		 instruction: SBC A,L
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/
	set_flags_mask(reg, 0x40)
}


void op_9e(void *reg, void *data)
{
	/*
		 instruction: SBC A,(HL)
		   num bytes: 1
		      cycles: 8
		       flags: Z 1 H C
	*/
	set_flags_mask(reg, 0x40)
}


void op_9f(void *reg, void *data)
{
	/*
		 instruction: SBC A,A
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/
	set_flags_mask(reg, 0x40)
}


void op_a0(void *reg, void *data)
{
	/*
		 instruction: AND B
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 1 0
	*/
	clear_flags_mask(reg, 0x50)
	set_flags_mask(reg, 0x20)
}


void op_a1(void *reg, void *data)
{
	/*
		 instruction: AND C
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 1 0
	*/
	clear_flags_mask(reg, 0x50)
	set_flags_mask(reg, 0x20)
}


void op_a2(void *reg, void *data)
{
	/*
		 instruction: AND D
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 1 0
	*/
	clear_flags_mask(reg, 0x50)
	set_flags_mask(reg, 0x20)
}


void op_a3(void *reg, void *data)
{
	/*
		 instruction: AND E
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 1 0
	*/
	clear_flags_mask(reg, 0x50)
	set_flags_mask(reg, 0x20)
}


void op_a4(void *reg, void *data)
{
	/*
		 instruction: AND H
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 1 0
	*/
	clear_flags_mask(reg, 0x50)
	set_flags_mask(reg, 0x20)
}


void op_a5(void *reg, void *data)
{
	/*
		 instruction: AND L
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 1 0
	*/
	clear_flags_mask(reg, 0x50)
	set_flags_mask(reg, 0x20)
}


void op_a6(void *reg, void *data)
{
	/*
		 instruction: AND (HL)
		   num bytes: 1
		      cycles: 8
		       flags: Z 0 1 0
	*/
	clear_flags_mask(reg, 0x50)
	set_flags_mask(reg, 0x20)
}


void op_a7(void *reg, void *data)
{
	/*
		 instruction: AND A
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 1 0
	*/
	clear_flags_mask(reg, 0x50)
	set_flags_mask(reg, 0x20)
}


void op_a8(void *reg, void *data)
{
	/*
		 instruction: XOR B
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/
	clear_flags_mask(reg, 0x70)
}


void op_a9(void *reg, void *data)
{
	/*
		 instruction: XOR C
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/
	clear_flags_mask(reg, 0x70)
}


void op_aa(void *reg, void *data)
{
	/*
		 instruction: XOR D
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/
	clear_flags_mask(reg, 0x70)
}


void op_ab(void *reg, void *data)
{
	/*
		 instruction: XOR E
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/
	clear_flags_mask(reg, 0x70)
}


void op_ac(void *reg, void *data)
{
	/*
		 instruction: XOR H
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/
	clear_flags_mask(reg, 0x70)
}


void op_ad(void *reg, void *data)
{
	/*
		 instruction: XOR L
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/
	clear_flags_mask(reg, 0x70)
}


void op_ae(void *reg, void *data)
{
	/*
		 instruction: XOR (HL)
		   num bytes: 1
		      cycles: 8
		       flags: Z 0 0 0
	*/
	clear_flags_mask(reg, 0x70)
}


void op_af(void *reg, void *data)
{
	/*
		 instruction: XOR A
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/
	clear_flags_mask(reg, 0x70)
}


void op_b0(void *reg, void *data)
{
	/*
		 instruction: OR B
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/
	clear_flags_mask(reg, 0x70)
}


void op_b1(void *reg, void *data)
{
	/*
		 instruction: OR C
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/
	clear_flags_mask(reg, 0x70)
}


void op_b2(void *reg, void *data)
{
	/*
		 instruction: OR D
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/
	clear_flags_mask(reg, 0x70)
}


void op_b3(void *reg, void *data)
{
	/*
		 instruction: OR E
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/
	clear_flags_mask(reg, 0x70)
}


void op_b4(void *reg, void *data)
{
	/*
		 instruction: OR H
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/
	clear_flags_mask(reg, 0x70)
}


void op_b5(void *reg, void *data)
{
	/*
		 instruction: OR L
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/
	clear_flags_mask(reg, 0x70)
}


void op_b6(void *reg, void *data)
{
	/*
		 instruction: OR (HL)
		   num bytes: 1
		      cycles: 8
		       flags: Z 0 0 0
	*/
	clear_flags_mask(reg, 0x70)
}


void op_b7(void *reg, void *data)
{
	/*
		 instruction: OR A
		   num bytes: 1
		      cycles: 4
		       flags: Z 0 0 0
	*/
	clear_flags_mask(reg, 0x70)
}


void op_b8(void *reg, void *data)
{
	/*
		 instruction: CP B
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/
	set_flags_mask(reg, 0x40)
}


void op_b9(void *reg, void *data)
{
	/*
		 instruction: CP C
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/
	set_flags_mask(reg, 0x40)
}


void op_ba(void *reg, void *data)
{
	/*
		 instruction: CP D
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/
	set_flags_mask(reg, 0x40)
}


void op_bb(void *reg, void *data)
{
	/*
		 instruction: CP E
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/
	set_flags_mask(reg, 0x40)
}


void op_bc(void *reg, void *data)
{
	/*
		 instruction: CP H
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/
	set_flags_mask(reg, 0x40)
}


void op_bd(void *reg, void *data)
{
	/*
		 instruction: CP L
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/
	set_flags_mask(reg, 0x40)
}


void op_be(void *reg, void *data)
{
	/*
		 instruction: CP (HL)
		   num bytes: 1
		      cycles: 8
		       flags: Z 1 H C
	*/
	set_flags_mask(reg, 0x40)
}


void op_bf(void *reg, void *data)
{
	/*
		 instruction: CP A
		   num bytes: 1
		      cycles: 4
		       flags: Z 1 H C
	*/
	set_flags_mask(reg, 0x40)
}


void op_c0(void *reg, void *data)
{
	/*
		 instruction: RET NZ
		   num bytes: 1
		      cycles: 20/8
		       flags: - - - -
	*/
}


void op_c1(void *reg, void *data)
{
	/*
		 instruction: POP BC
		   num bytes: 1
		      cycles: 12
		       flags: - - - -
	*/
}


void op_c2(void *reg, void *data)
{
	/*
		 instruction: JP NZ,a16
		   num bytes: 3
		      cycles: 16/12
		       flags: - - - -
	*/
}


void op_c3(void *reg, void *data)
{
	/*
		 instruction: JP a16
		   num bytes: 3
		      cycles: 16
		       flags: - - - -
	*/
}


void op_c4(void *reg, void *data)
{
	/*
		 instruction: CALL NZ,a16
		   num bytes: 3
		      cycles: 24/12
		       flags: - - - -
	*/
}


void op_c5(void *reg, void *data)
{
	/*
		 instruction: PUSH BC
		   num bytes: 1
		      cycles: 16
		       flags: - - - -
	*/
}


void op_c6(void *reg, void *data)
{
	/*
		 instruction: ADD A,d8
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 H C
	*/
	clear_flags_mask(reg, 0x40)
}


void op_c7(void *reg, void *data)
{
	/*
		 instruction: RST 00H
		   num bytes: 1
		      cycles: 16
		       flags: - - - -
	*/
}


void op_c8(void *reg, void *data)
{
	/*
		 instruction: RET Z
		   num bytes: 1
		      cycles: 20/8
		       flags: - - - -
	*/
}


void op_c9(void *reg, void *data)
{
	/*
		 instruction: RET
		   num bytes: 1
		      cycles: 16
		       flags: - - - -
	*/
}


void op_ca(void *reg, void *data)
{
	/*
		 instruction: JP Z,a16
		   num bytes: 3
		      cycles: 16/12
		       flags: - - - -
	*/
}


void op_cb(void *reg, void *data)
{
	/*
		 instruction: PREFIX CB
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_cc(void *reg, void *data)
{
	/*
		 instruction: CALL Z,a16
		   num bytes: 3
		      cycles: 24/12
		       flags: - - - -
	*/
}


void op_cd(void *reg, void *data)
{
	/*
		 instruction: CALL a16
		   num bytes: 3
		      cycles: 24
		       flags: - - - -
	*/
}


void op_ce(void *reg, void *data)
{
	/*
		 instruction: ADC A,d8
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 H C
	*/
	clear_flags_mask(reg, 0x40)
}


void op_cf(void *reg, void *data)
{
	/*
		 instruction: RST 08H
		   num bytes: 1
		      cycles: 16
		       flags: - - - -
	*/
}


void op_d0(void *reg, void *data)
{
	/*
		 instruction: RET NC
		   num bytes: 1
		      cycles: 20/8
		       flags: - - - -
	*/
}


void op_d1(void *reg, void *data)
{
	/*
		 instruction: POP DE
		   num bytes: 1
		      cycles: 12
		       flags: - - - -
	*/
}


void op_d2(void *reg, void *data)
{
	/*
		 instruction: JP NC,a16
		   num bytes: 3
		      cycles: 16/12
		       flags: - - - -
	*/
}


void op_d3(void *reg, void *data)
{
	/*
		 instruction: FIXME: undefined
		   num bytes: FIXME: undefined
		      cycles: FIXME: undefined
		       flags: FIXME: undefined
	*/
}


void op_d4(void *reg, void *data)
{
	/*
		 instruction: CALL NC,a16
		   num bytes: 3
		      cycles: 24/12
		       flags: - - - -
	*/
}


void op_d5(void *reg, void *data)
{
	/*
		 instruction: PUSH DE
		   num bytes: 1
		      cycles: 16
		       flags: - - - -
	*/
}


void op_d6(void *reg, void *data)
{
	/*
		 instruction: SUB d8
		   num bytes: 2
		      cycles: 8
		       flags: Z 1 H C
	*/
	set_flags_mask(reg, 0x40)
}


void op_d7(void *reg, void *data)
{
	/*
		 instruction: RST 10H
		   num bytes: 1
		      cycles: 16
		       flags: - - - -
	*/
}


void op_d8(void *reg, void *data)
{
	/*
		 instruction: RET C
		   num bytes: 1
		      cycles: 20/8
		       flags: - - - -
	*/
}


void op_d9(void *reg, void *data)
{
	/*
		 instruction: RETI
		   num bytes: 1
		      cycles: 16
		       flags: - - - -
	*/
}


void op_da(void *reg, void *data)
{
	/*
		 instruction: JP C,a16
		   num bytes: 3
		      cycles: 16/12
		       flags: - - - -
	*/
}


void op_db(void *reg, void *data)
{
	/*
		 instruction: FIXME: undefined
		   num bytes: FIXME: undefined
		      cycles: FIXME: undefined
		       flags: FIXME: undefined
	*/
}


void op_dc(void *reg, void *data)
{
	/*
		 instruction: CALL C,a16
		   num bytes: 3
		      cycles: 24/12
		       flags: - - - -
	*/
}


void op_dd(void *reg, void *data)
{
	/*
		 instruction: FIXME: undefined
		   num bytes: FIXME: undefined
		      cycles: FIXME: undefined
		       flags: FIXME: undefined
	*/
}


void op_de(void *reg, void *data)
{
	/*
		 instruction: SBC A,d8
		   num bytes: 2
		      cycles: 8
		       flags: Z 1 H C
	*/
	set_flags_mask(reg, 0x40)
}


void op_df(void *reg, void *data)
{
	/*
		 instruction: RST 18H
		   num bytes: 1
		      cycles: 16
		       flags: - - - -
	*/
}


void op_e0(void *reg, void *data)
{
	/*
		 instruction: LDH (a8),A
		   num bytes: 2
		      cycles: 12
		       flags: - - - -
	*/
}


void op_e1(void *reg, void *data)
{
	/*
		 instruction: POP HL
		   num bytes: 1
		      cycles: 12
		       flags: - - - -
	*/
}


void op_e2(void *reg, void *data)
{
	/*
		 instruction: LD (C),A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_e3(void *reg, void *data)
{
	/*
		 instruction: FIXME: undefined
		   num bytes: FIXME: undefined
		      cycles: FIXME: undefined
		       flags: FIXME: undefined
	*/
}


void op_e4(void *reg, void *data)
{
	/*
		 instruction: FIXME: undefined
		   num bytes: FIXME: undefined
		      cycles: FIXME: undefined
		       flags: FIXME: undefined
	*/
}


void op_e5(void *reg, void *data)
{
	/*
		 instruction: PUSH HL
		   num bytes: 1
		      cycles: 16
		       flags: - - - -
	*/
}


void op_e6(void *reg, void *data)
{
	/*
		 instruction: AND d8
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 0
	*/
	clear_flags_mask(reg, 0x50)
	set_flags_mask(reg, 0x20)
}


void op_e7(void *reg, void *data)
{
	/*
		 instruction: RST 20H
		   num bytes: 1
		      cycles: 16
		       flags: - - - -
	*/
}


void op_e8(void *reg, void *data)
{
	/*
		 instruction: ADD SP,r8
		   num bytes: 2
		      cycles: 16
		       flags: 0 0 H C
	*/
	clear_flags_mask(reg, 0xc0)
}


void op_e9(void *reg, void *data)
{
	/*
		 instruction: JP (HL)
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_ea(void *reg, void *data)
{
	/*
		 instruction: LD (a16),A
		   num bytes: 3
		      cycles: 16
		       flags: - - - -
	*/
}


void op_eb(void *reg, void *data)
{
	/*
		 instruction: FIXME: undefined
		   num bytes: FIXME: undefined
		      cycles: FIXME: undefined
		       flags: FIXME: undefined
	*/
}


void op_ec(void *reg, void *data)
{
	/*
		 instruction: FIXME: undefined
		   num bytes: FIXME: undefined
		      cycles: FIXME: undefined
		       flags: FIXME: undefined
	*/
}


void op_ed(void *reg, void *data)
{
	/*
		 instruction: FIXME: undefined
		   num bytes: FIXME: undefined
		      cycles: FIXME: undefined
		       flags: FIXME: undefined
	*/
}


void op_ee(void *reg, void *data)
{
	/*
		 instruction: XOR d8
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/
	clear_flags_mask(reg, 0x70)
}


void op_ef(void *reg, void *data)
{
	/*
		 instruction: RST 28H
		   num bytes: 1
		      cycles: 16
		       flags: - - - -
	*/
}


void op_f0(void *reg, void *data)
{
	/*
		 instruction: LDH A,(a8)
		   num bytes: 2
		      cycles: 12
		       flags: - - - -
	*/
}


void op_f1(void *reg, void *data)
{
	/*
		 instruction: POP AF
		   num bytes: 1
		      cycles: 12
		       flags: Z N H C
	*/
}


void op_f2(void *reg, void *data)
{
	/*
		 instruction: LD A,(C)
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_f3(void *reg, void *data)
{
	/*
		 instruction: DI
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_f4(void *reg, void *data)
{
	/*
		 instruction: FIXME: undefined
		   num bytes: FIXME: undefined
		      cycles: FIXME: undefined
		       flags: FIXME: undefined
	*/
}


void op_f5(void *reg, void *data)
{
	/*
		 instruction: PUSH AF
		   num bytes: 1
		      cycles: 16
		       flags: - - - -
	*/
}


void op_f6(void *reg, void *data)
{
	/*
		 instruction: OR d8
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/
	clear_flags_mask(reg, 0x70)
}


void op_f7(void *reg, void *data)
{
	/*
		 instruction: RST 30H
		   num bytes: 1
		      cycles: 16
		       flags: - - - -
	*/
}


void op_f8(void *reg, void *data)
{
	/*
		 instruction: LD HL,SP+r8
		   num bytes: 2
		      cycles: 12
		       flags: 0 0 H C
	*/
	clear_flags_mask(reg, 0xc0)
}


void op_f9(void *reg, void *data)
{
	/*
		 instruction: LD SP,HL
		   num bytes: 1
		      cycles: 8
		       flags: - - - -
	*/
}


void op_fa(void *reg, void *data)
{
	/*
		 instruction: LD A,(a16)
		   num bytes: 3
		      cycles: 16
		       flags: - - - -
	*/
}


void op_fb(void *reg, void *data)
{
	/*
		 instruction: EI
		   num bytes: 1
		      cycles: 4
		       flags: - - - -
	*/
}


void op_fc(void *reg, void *data)
{
	/*
		 instruction: FIXME: undefined
		   num bytes: FIXME: undefined
		      cycles: FIXME: undefined
		       flags: FIXME: undefined
	*/
}


void op_fd(void *reg, void *data)
{
	/*
		 instruction: FIXME: undefined
		   num bytes: FIXME: undefined
		      cycles: FIXME: undefined
		       flags: FIXME: undefined
	*/
}


void op_fe(void *reg, void *data)
{
	/*
		 instruction: CP d8
		   num bytes: 2
		      cycles: 8
		       flags: Z 1 H C
	*/
	set_flags_mask(reg, 0x40)
}


void op_ff(void *reg, void *data)
{
	/*
		 instruction: RST 38H
		   num bytes: 1
		      cycles: 16
		       flags: - - - -
	*/
}


void op_cb00(void *reg, void *data)
{
	/*
		 instruction: RLC B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb01(void *reg, void *data)
{
	/*
		 instruction: RLC C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb02(void *reg, void *data)
{
	/*
		 instruction: RLC D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb03(void *reg, void *data)
{
	/*
		 instruction: RLC E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb04(void *reg, void *data)
{
	/*
		 instruction: RLC H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb05(void *reg, void *data)
{
	/*
		 instruction: RLC L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb06(void *reg, void *data)
{
	/*
		 instruction: RLC (HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb07(void *reg, void *data)
{
	/*
		 instruction: RLC A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb08(void *reg, void *data)
{
	/*
		 instruction: RRC B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb09(void *reg, void *data)
{
	/*
		 instruction: RRC C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb0a(void *reg, void *data)
{
	/*
		 instruction: RRC D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb0b(void *reg, void *data)
{
	/*
		 instruction: RRC E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb0c(void *reg, void *data)
{
	/*
		 instruction: RRC H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb0d(void *reg, void *data)
{
	/*
		 instruction: RRC L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb0e(void *reg, void *data)
{
	/*
		 instruction: RRC (HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb0f(void *reg, void *data)
{
	/*
		 instruction: RRC A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb10(void *reg, void *data)
{
	/*
		 instruction: RL B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb11(void *reg, void *data)
{
	/*
		 instruction: RL C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb12(void *reg, void *data)
{
	/*
		 instruction: RL D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb13(void *reg, void *data)
{
	/*
		 instruction: RL E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb14(void *reg, void *data)
{
	/*
		 instruction: RL H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb15(void *reg, void *data)
{
	/*
		 instruction: RL L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb16(void *reg, void *data)
{
	/*
		 instruction: RL (HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb17(void *reg, void *data)
{
	/*
		 instruction: RL A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb18(void *reg, void *data)
{
	/*
		 instruction: RR B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb19(void *reg, void *data)
{
	/*
		 instruction: RR C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb1a(void *reg, void *data)
{
	/*
		 instruction: RR D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb1b(void *reg, void *data)
{
	/*
		 instruction: RR E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb1c(void *reg, void *data)
{
	/*
		 instruction: RR H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb1d(void *reg, void *data)
{
	/*
		 instruction: RR L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb1e(void *reg, void *data)
{
	/*
		 instruction: RR (HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb1f(void *reg, void *data)
{
	/*
		 instruction: RR A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb20(void *reg, void *data)
{
	/*
		 instruction: SLA B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb21(void *reg, void *data)
{
	/*
		 instruction: SLA C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb22(void *reg, void *data)
{
	/*
		 instruction: SLA D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb23(void *reg, void *data)
{
	/*
		 instruction: SLA E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb24(void *reg, void *data)
{
	/*
		 instruction: SLA H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb25(void *reg, void *data)
{
	/*
		 instruction: SLA L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb26(void *reg, void *data)
{
	/*
		 instruction: SLA (HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb27(void *reg, void *data)
{
	/*
		 instruction: SLA A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb28(void *reg, void *data)
{
	/*
		 instruction: SRA B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/
	clear_flags_mask(reg, 0x70)
}


void op_cb29(void *reg, void *data)
{
	/*
		 instruction: SRA C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/
	clear_flags_mask(reg, 0x70)
}


void op_cb2a(void *reg, void *data)
{
	/*
		 instruction: SRA D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/
	clear_flags_mask(reg, 0x70)
}


void op_cb2b(void *reg, void *data)
{
	/*
		 instruction: SRA E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/
	clear_flags_mask(reg, 0x70)
}


void op_cb2c(void *reg, void *data)
{
	/*
		 instruction: SRA H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/
	clear_flags_mask(reg, 0x70)
}


void op_cb2d(void *reg, void *data)
{
	/*
		 instruction: SRA L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/
	clear_flags_mask(reg, 0x70)
}


void op_cb2e(void *reg, void *data)
{
	/*
		 instruction: SRA (HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 0 0
	*/
	clear_flags_mask(reg, 0x70)
}


void op_cb2f(void *reg, void *data)
{
	/*
		 instruction: SRA A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/
	clear_flags_mask(reg, 0x70)
}


void op_cb30(void *reg, void *data)
{
	/*
		 instruction: SWAP B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/
	clear_flags_mask(reg, 0x70)
}


void op_cb31(void *reg, void *data)
{
	/*
		 instruction: SWAP C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/
	clear_flags_mask(reg, 0x70)
}


void op_cb32(void *reg, void *data)
{
	/*
		 instruction: SWAP D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/
	clear_flags_mask(reg, 0x70)
}


void op_cb33(void *reg, void *data)
{
	/*
		 instruction: SWAP E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/
	clear_flags_mask(reg, 0x70)
}


void op_cb34(void *reg, void *data)
{
	/*
		 instruction: SWAP H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/
	clear_flags_mask(reg, 0x70)
}


void op_cb35(void *reg, void *data)
{
	/*
		 instruction: SWAP L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/
	clear_flags_mask(reg, 0x70)
}


void op_cb36(void *reg, void *data)
{
	/*
		 instruction: SWAP (HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 0 0
	*/
	clear_flags_mask(reg, 0x70)
}


void op_cb37(void *reg, void *data)
{
	/*
		 instruction: SWAP A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 0
	*/
	clear_flags_mask(reg, 0x70)
}


void op_cb38(void *reg, void *data)
{
	/*
		 instruction: SRL B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb39(void *reg, void *data)
{
	/*
		 instruction: SRL C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb3a(void *reg, void *data)
{
	/*
		 instruction: SRL D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb3b(void *reg, void *data)
{
	/*
		 instruction: SRL E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb3c(void *reg, void *data)
{
	/*
		 instruction: SRL H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb3d(void *reg, void *data)
{
	/*
		 instruction: SRL L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb3e(void *reg, void *data)
{
	/*
		 instruction: SRL (HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb3f(void *reg, void *data)
{
	/*
		 instruction: SRL A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 0 C
	*/
	clear_flags_mask(reg, 0x60)
}


void op_cb40(void *reg, void *data)
{
	/*
		 instruction: BIT 0,B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb41(void *reg, void *data)
{
	/*
		 instruction: BIT 0,C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb42(void *reg, void *data)
{
	/*
		 instruction: BIT 0,D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb43(void *reg, void *data)
{
	/*
		 instruction: BIT 0,E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb44(void *reg, void *data)
{
	/*
		 instruction: BIT 0,H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb45(void *reg, void *data)
{
	/*
		 instruction: BIT 0,L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb46(void *reg, void *data)
{
	/*
		 instruction: BIT 0,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb47(void *reg, void *data)
{
	/*
		 instruction: BIT 0,A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb48(void *reg, void *data)
{
	/*
		 instruction: BIT 1,B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb49(void *reg, void *data)
{
	/*
		 instruction: BIT 1,C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb4a(void *reg, void *data)
{
	/*
		 instruction: BIT 1,D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb4b(void *reg, void *data)
{
	/*
		 instruction: BIT 1,E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb4c(void *reg, void *data)
{
	/*
		 instruction: BIT 1,H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb4d(void *reg, void *data)
{
	/*
		 instruction: BIT 1,L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb4e(void *reg, void *data)
{
	/*
		 instruction: BIT 1,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb4f(void *reg, void *data)
{
	/*
		 instruction: BIT 1,A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb50(void *reg, void *data)
{
	/*
		 instruction: BIT 2,B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb51(void *reg, void *data)
{
	/*
		 instruction: BIT 2,C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb52(void *reg, void *data)
{
	/*
		 instruction: BIT 2,D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb53(void *reg, void *data)
{
	/*
		 instruction: BIT 2,E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb54(void *reg, void *data)
{
	/*
		 instruction: BIT 2,H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb55(void *reg, void *data)
{
	/*
		 instruction: BIT 2,L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb56(void *reg, void *data)
{
	/*
		 instruction: BIT 2,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb57(void *reg, void *data)
{
	/*
		 instruction: BIT 2,A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb58(void *reg, void *data)
{
	/*
		 instruction: BIT 3,B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb59(void *reg, void *data)
{
	/*
		 instruction: BIT 3,C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb5a(void *reg, void *data)
{
	/*
		 instruction: BIT 3,D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb5b(void *reg, void *data)
{
	/*
		 instruction: BIT 3,E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb5c(void *reg, void *data)
{
	/*
		 instruction: BIT 3,H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb5d(void *reg, void *data)
{
	/*
		 instruction: BIT 3,L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb5e(void *reg, void *data)
{
	/*
		 instruction: BIT 3,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb5f(void *reg, void *data)
{
	/*
		 instruction: BIT 3,A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb60(void *reg, void *data)
{
	/*
		 instruction: BIT 4,B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb61(void *reg, void *data)
{
	/*
		 instruction: BIT 4,C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb62(void *reg, void *data)
{
	/*
		 instruction: BIT 4,D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb63(void *reg, void *data)
{
	/*
		 instruction: BIT 4,E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb64(void *reg, void *data)
{
	/*
		 instruction: BIT 4,H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb65(void *reg, void *data)
{
	/*
		 instruction: BIT 4,L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb66(void *reg, void *data)
{
	/*
		 instruction: BIT 4,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb67(void *reg, void *data)
{
	/*
		 instruction: BIT 4,A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb68(void *reg, void *data)
{
	/*
		 instruction: BIT 5,B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb69(void *reg, void *data)
{
	/*
		 instruction: BIT 5,C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb6a(void *reg, void *data)
{
	/*
		 instruction: BIT 5,D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb6b(void *reg, void *data)
{
	/*
		 instruction: BIT 5,E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb6c(void *reg, void *data)
{
	/*
		 instruction: BIT 5,H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb6d(void *reg, void *data)
{
	/*
		 instruction: BIT 5,L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb6e(void *reg, void *data)
{
	/*
		 instruction: BIT 5,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb6f(void *reg, void *data)
{
	/*
		 instruction: BIT 5,A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb70(void *reg, void *data)
{
	/*
		 instruction: BIT 6,B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb71(void *reg, void *data)
{
	/*
		 instruction: BIT 6,C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb72(void *reg, void *data)
{
	/*
		 instruction: BIT 6,D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb73(void *reg, void *data)
{
	/*
		 instruction: BIT 6,E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb74(void *reg, void *data)
{
	/*
		 instruction: BIT 6,H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb75(void *reg, void *data)
{
	/*
		 instruction: BIT 6,L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb76(void *reg, void *data)
{
	/*
		 instruction: BIT 6,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb77(void *reg, void *data)
{
	/*
		 instruction: BIT 6,A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb78(void *reg, void *data)
{
	/*
		 instruction: BIT 7,B
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb79(void *reg, void *data)
{
	/*
		 instruction: BIT 7,C
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb7a(void *reg, void *data)
{
	/*
		 instruction: BIT 7,D
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb7b(void *reg, void *data)
{
	/*
		 instruction: BIT 7,E
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb7c(void *reg, void *data)
{
	/*
		 instruction: BIT 7,H
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb7d(void *reg, void *data)
{
	/*
		 instruction: BIT 7,L
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb7e(void *reg, void *data)
{
	/*
		 instruction: BIT 7,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb7f(void *reg, void *data)
{
	/*
		 instruction: BIT 7,A
		   num bytes: 2
		      cycles: 8
		       flags: Z 0 1 -
	*/
	clear_flags_mask(reg, 0x40)
	set_flags_mask(reg, 0x20)
}


void op_cb80(void *reg, void *data)
{
	/*
		 instruction: RES 0,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb81(void *reg, void *data)
{
	/*
		 instruction: RES 0,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb82(void *reg, void *data)
{
	/*
		 instruction: RES 0,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb83(void *reg, void *data)
{
	/*
		 instruction: RES 0,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb84(void *reg, void *data)
{
	/*
		 instruction: RES 0,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb85(void *reg, void *data)
{
	/*
		 instruction: RES 0,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb86(void *reg, void *data)
{
	/*
		 instruction: RES 0,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/
}


void op_cb87(void *reg, void *data)
{
	/*
		 instruction: RES 0,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb88(void *reg, void *data)
{
	/*
		 instruction: RES 1,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb89(void *reg, void *data)
{
	/*
		 instruction: RES 1,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb8a(void *reg, void *data)
{
	/*
		 instruction: RES 1,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb8b(void *reg, void *data)
{
	/*
		 instruction: RES 1,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb8c(void *reg, void *data)
{
	/*
		 instruction: RES 1,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb8d(void *reg, void *data)
{
	/*
		 instruction: RES 1,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb8e(void *reg, void *data)
{
	/*
		 instruction: RES 1,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/
}


void op_cb8f(void *reg, void *data)
{
	/*
		 instruction: RES 1,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb90(void *reg, void *data)
{
	/*
		 instruction: RES 2,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb91(void *reg, void *data)
{
	/*
		 instruction: RES 2,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb92(void *reg, void *data)
{
	/*
		 instruction: RES 2,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb93(void *reg, void *data)
{
	/*
		 instruction: RES 2,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb94(void *reg, void *data)
{
	/*
		 instruction: RES 2,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb95(void *reg, void *data)
{
	/*
		 instruction: RES 2,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb96(void *reg, void *data)
{
	/*
		 instruction: RES 2,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/
}


void op_cb97(void *reg, void *data)
{
	/*
		 instruction: RES 2,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb98(void *reg, void *data)
{
	/*
		 instruction: RES 3,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb99(void *reg, void *data)
{
	/*
		 instruction: RES 3,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb9a(void *reg, void *data)
{
	/*
		 instruction: RES 3,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb9b(void *reg, void *data)
{
	/*
		 instruction: RES 3,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb9c(void *reg, void *data)
{
	/*
		 instruction: RES 3,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb9d(void *reg, void *data)
{
	/*
		 instruction: RES 3,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cb9e(void *reg, void *data)
{
	/*
		 instruction: RES 3,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/
}


void op_cb9f(void *reg, void *data)
{
	/*
		 instruction: RES 3,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cba0(void *reg, void *data)
{
	/*
		 instruction: RES 4,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cba1(void *reg, void *data)
{
	/*
		 instruction: RES 4,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cba2(void *reg, void *data)
{
	/*
		 instruction: RES 4,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cba3(void *reg, void *data)
{
	/*
		 instruction: RES 4,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cba4(void *reg, void *data)
{
	/*
		 instruction: RES 4,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cba5(void *reg, void *data)
{
	/*
		 instruction: RES 4,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cba6(void *reg, void *data)
{
	/*
		 instruction: RES 4,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/
}


void op_cba7(void *reg, void *data)
{
	/*
		 instruction: RES 4,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cba8(void *reg, void *data)
{
	/*
		 instruction: RES 5,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cba9(void *reg, void *data)
{
	/*
		 instruction: RES 5,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbaa(void *reg, void *data)
{
	/*
		 instruction: RES 5,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbab(void *reg, void *data)
{
	/*
		 instruction: RES 5,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbac(void *reg, void *data)
{
	/*
		 instruction: RES 5,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbad(void *reg, void *data)
{
	/*
		 instruction: RES 5,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbae(void *reg, void *data)
{
	/*
		 instruction: RES 5,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/
}


void op_cbaf(void *reg, void *data)
{
	/*
		 instruction: RES 5,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbb0(void *reg, void *data)
{
	/*
		 instruction: RES 6,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbb1(void *reg, void *data)
{
	/*
		 instruction: RES 6,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbb2(void *reg, void *data)
{
	/*
		 instruction: RES 6,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbb3(void *reg, void *data)
{
	/*
		 instruction: RES 6,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbb4(void *reg, void *data)
{
	/*
		 instruction: RES 6,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbb5(void *reg, void *data)
{
	/*
		 instruction: RES 6,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbb6(void *reg, void *data)
{
	/*
		 instruction: RES 6,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/
}


void op_cbb7(void *reg, void *data)
{
	/*
		 instruction: RES 6,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbb8(void *reg, void *data)
{
	/*
		 instruction: RES 7,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbb9(void *reg, void *data)
{
	/*
		 instruction: RES 7,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbba(void *reg, void *data)
{
	/*
		 instruction: RES 7,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbbb(void *reg, void *data)
{
	/*
		 instruction: RES 7,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbbc(void *reg, void *data)
{
	/*
		 instruction: RES 7,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbbd(void *reg, void *data)
{
	/*
		 instruction: RES 7,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbbe(void *reg, void *data)
{
	/*
		 instruction: RES 7,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/
}


void op_cbbf(void *reg, void *data)
{
	/*
		 instruction: RES 7,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbc0(void *reg, void *data)
{
	/*
		 instruction: SET 0,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbc1(void *reg, void *data)
{
	/*
		 instruction: SET 0,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbc2(void *reg, void *data)
{
	/*
		 instruction: SET 0,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbc3(void *reg, void *data)
{
	/*
		 instruction: SET 0,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbc4(void *reg, void *data)
{
	/*
		 instruction: SET 0,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbc5(void *reg, void *data)
{
	/*
		 instruction: SET 0,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbc6(void *reg, void *data)
{
	/*
		 instruction: SET 0,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/
}


void op_cbc7(void *reg, void *data)
{
	/*
		 instruction: SET 0,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbc8(void *reg, void *data)
{
	/*
		 instruction: SET 1,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbc9(void *reg, void *data)
{
	/*
		 instruction: SET 1,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbca(void *reg, void *data)
{
	/*
		 instruction: SET 1,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbcb(void *reg, void *data)
{
	/*
		 instruction: SET 1,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbcc(void *reg, void *data)
{
	/*
		 instruction: SET 1,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbcd(void *reg, void *data)
{
	/*
		 instruction: SET 1,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbce(void *reg, void *data)
{
	/*
		 instruction: SET 1,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/
}


void op_cbcf(void *reg, void *data)
{
	/*
		 instruction: SET 1,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbd0(void *reg, void *data)
{
	/*
		 instruction: SET 2,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbd1(void *reg, void *data)
{
	/*
		 instruction: SET 2,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbd2(void *reg, void *data)
{
	/*
		 instruction: SET 2,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbd3(void *reg, void *data)
{
	/*
		 instruction: SET 2,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbd4(void *reg, void *data)
{
	/*
		 instruction: SET 2,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbd5(void *reg, void *data)
{
	/*
		 instruction: SET 2,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbd6(void *reg, void *data)
{
	/*
		 instruction: SET 2,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/
}


void op_cbd7(void *reg, void *data)
{
	/*
		 instruction: SET 2,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbd8(void *reg, void *data)
{
	/*
		 instruction: SET 3,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbd9(void *reg, void *data)
{
	/*
		 instruction: SET 3,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbda(void *reg, void *data)
{
	/*
		 instruction: SET 3,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbdb(void *reg, void *data)
{
	/*
		 instruction: SET 3,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbdc(void *reg, void *data)
{
	/*
		 instruction: SET 3,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbdd(void *reg, void *data)
{
	/*
		 instruction: SET 3,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbde(void *reg, void *data)
{
	/*
		 instruction: SET 3,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/
}


void op_cbdf(void *reg, void *data)
{
	/*
		 instruction: SET 3,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbe0(void *reg, void *data)
{
	/*
		 instruction: SET 4,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbe1(void *reg, void *data)
{
	/*
		 instruction: SET 4,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbe2(void *reg, void *data)
{
	/*
		 instruction: SET 4,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbe3(void *reg, void *data)
{
	/*
		 instruction: SET 4,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbe4(void *reg, void *data)
{
	/*
		 instruction: SET 4,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbe5(void *reg, void *data)
{
	/*
		 instruction: SET 4,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbe6(void *reg, void *data)
{
	/*
		 instruction: SET 4,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/
}


void op_cbe7(void *reg, void *data)
{
	/*
		 instruction: SET 4,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbe8(void *reg, void *data)
{
	/*
		 instruction: SET 5,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbe9(void *reg, void *data)
{
	/*
		 instruction: SET 5,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbea(void *reg, void *data)
{
	/*
		 instruction: SET 5,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbeb(void *reg, void *data)
{
	/*
		 instruction: SET 5,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbec(void *reg, void *data)
{
	/*
		 instruction: SET 5,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbed(void *reg, void *data)
{
	/*
		 instruction: SET 5,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbee(void *reg, void *data)
{
	/*
		 instruction: SET 5,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/
}


void op_cbef(void *reg, void *data)
{
	/*
		 instruction: SET 5,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbf0(void *reg, void *data)
{
	/*
		 instruction: SET 6,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbf1(void *reg, void *data)
{
	/*
		 instruction: SET 6,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbf2(void *reg, void *data)
{
	/*
		 instruction: SET 6,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbf3(void *reg, void *data)
{
	/*
		 instruction: SET 6,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbf4(void *reg, void *data)
{
	/*
		 instruction: SET 6,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbf5(void *reg, void *data)
{
	/*
		 instruction: SET 6,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbf6(void *reg, void *data)
{
	/*
		 instruction: SET 6,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/
}


void op_cbf7(void *reg, void *data)
{
	/*
		 instruction: SET 6,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbf8(void *reg, void *data)
{
	/*
		 instruction: SET 7,B
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbf9(void *reg, void *data)
{
	/*
		 instruction: SET 7,C
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbfa(void *reg, void *data)
{
	/*
		 instruction: SET 7,D
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbfb(void *reg, void *data)
{
	/*
		 instruction: SET 7,E
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbfc(void *reg, void *data)
{
	/*
		 instruction: SET 7,H
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbfd(void *reg, void *data)
{
	/*
		 instruction: SET 7,L
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


void op_cbfe(void *reg, void *data)
{
	/*
		 instruction: SET 7,(HL)
		   num bytes: 2
		      cycles: 16
		       flags: - - - -
	*/
}


void op_cbff(void *reg, void *data)
{
	/*
		 instruction: SET 7,A
		   num bytes: 2
		      cycles: 8
		       flags: - - - -
	*/
}


