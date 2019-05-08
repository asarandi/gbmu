cast_void_to_reg = [
        't_r8  *r8  = reg;',
        't_r16 *r16 = reg;'
        ]

eight_bit_registers = {
        'A': 'r8->A',
        'B': 'r8->B',
        'C': 'r8->C',
        'D': 'r8->D',
        'E': 'r8->E',
        'H': 'r8->H',
        'L': 'r8->L'
#        '(HL)': 'read_u8(r16->HL)'
        }

sixteen_bit_registers = {
        'AF': 'r16->AF',
        'BC': 'r16->BC',
        'DE': 'r16->DE',
        'HL': 'r16->HL',
        'SP': 'r16->SP'
        }

sixteen_bit_reg_addr = {
          '(C)': '0xff00+r8->C',
         '(BC)': 'r16->BC',
         '(DE)': 'r16->DE',
         '(HL)': 'r16->HL',
        '(HL+)': 'r16->HL++',
        '(HL-)': 'r16->HL--'
        }

def format_c_code_list(lst):
    code = '\n'
    for item in lst:
        code += '\t' + item + '\n'
    return code

###############################################################################

def gb_op_call(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op = instr.split()[1]
    if op == 'NZ,a16':
        code.append('if (is_z_flag)  { r16->PC += %s; return; };' % (byte_len,))
    elif op == 'Z,a16':
        code.append('if (!is_z_flag)  { r16->PC += %s; return; };' % (byte_len,))
    elif op == 'a16':
        pass
    elif op == 'NC,a16':
        code.append('if (is_c_flag)  { r16->PC += %s; return; };' % (byte_len,))
    elif op == 'C,a16':
        code.append('if (!is_c_flag) { r16->PC += %s; return; };' % (byte_len,))

    code.append('r16->SP -= 2;')
    code.append('write_u16(r16->SP, r16->PC + %s);' % (byte_len,))   #return addr on stack
    code.append('r16->PC = read_u16(r16->PC + 1);')   #
    return format_c_code_list(code)

def gb_op_jp(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op = instr.split()[1]

    if op == '(HL)':
        code.append('r16->PC = r16->HL;')
        return format_c_code_list(code)

    elif op == 'NZ,a16':
        code.append('if (is_z_flag)  { r16->PC += %s; return; };' % (byte_len,))
    elif op == 'Z,a16':
        code.append('if (!is_z_flag)  { r16->PC += %s; return; };' % (byte_len,))
    elif op == 'a16':
        pass
    elif op == 'NC,a16':
        code.append('if (is_c_flag)  { r16->PC += %s; return; };' % (byte_len,))
    elif op == 'C,a16':
        code.append('if (!is_c_flag) { r16->PC += %s; return; };' % (byte_len,))

    code.append('r16->PC = read_u16(r16->PC + 1);')   #
    return format_c_code_list(code)

def gb_op_jr(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op = instr.split()[1]
    if op == 'r8':
        pass
    elif op == 'NZ,r8':
        code.append('if (!is_z_flag)')
    elif op == 'Z,r8':
        code.append('if (is_z_flag)')
    elif op == 'NC,r8':
        code.append('if (!is_c_flag)')
    elif op == 'C,r8':
        code.append('if (is_c_flag)')

    code.append('r16->PC += (int8_t)read_u8(r16->PC + 1);')  #signed XXX
    code.append('r16->PC += %s;' % (byte_len,))

    return format_c_code_list(code)

def gb_op_push(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op = instr.split()[1]

    code.append('r16->SP -= 2;')
    code.append('write_u16(r16->SP, %s);' % (sixteen_bit_registers[op],))
    code.append('r16->PC += %s;' % (byte_len,))
    return format_c_code_list(code)

def gb_op_pop(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op = instr.split()[1]
    code.append('%s = read_u16(r16->SP);' % (sixteen_bit_registers[op],))
    if op == 'AF':
        code.append('r8->F &= 0xf0;')
    code.append('r16->SP += 2;')
    code.append('r16->PC += %s;' % (byte_len,))
    return format_c_code_list(code)

def gb_op_ret(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    if len(instr.split()) == 1:         #unconditional ret
            code.append('r16->PC = read_u16(r16->SP);')
            code.append('r16->SP += 2;')
            code.append('return ;')
            return format_c_code_list(code)
    op = instr.split()[1]
    if op == 'NZ':
        code.append('if (!is_z_flag)')
    elif op == 'Z':
        code.append('if (is_z_flag)')

    elif op == 'NC':
        code.append('if (!is_c_flag)')
    elif op == 'C':
        code.append('if (is_c_flag)')

    code.append('{ r16->PC = read_u16(r16->SP); r16->SP += 2; return ; }')
    code.append('r16->PC += %s;' % (byte_len,))
    return format_c_code_list(code)


def gb_op_reti(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    code.append('r16->PC = read_u16(r16->SP);')
    code.append('r16->SP += 2;')
    code.append('state->interrupts_enabled = true;')
    return format_c_code_list(code)

def gb_op_ei(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    code.append('state->interrupts_enabled = true;')
    code.append('r16->PC += %s;' % (byte_len, ))
    return format_c_code_list(code)

def gb_op_di(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    code.append('state->interrupts_enabled = false;')
    code.append('r16->PC += %s;' % (byte_len, ))
    return format_c_code_list(code)

def gb_op_nop(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    code.append('r16->PC += %s;' % (byte_len, ))
    return format_c_code_list(code)

def gb_op_rst(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op = instr.split()[1][:-1]  #remove last 'H' character
    code.append('r16->SP -= 2;')
    code.append('write_u16(r16->SP, r16->PC + %s);' % (byte_len, ))
    code.append('r16->PC = 0x%s;' % (op, ))
    return format_c_code_list(code)

def gb_op_halt(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    code.append('r16->PC += %s;' % (byte_len, ))
    code.append('state->halt = true;')
    code.append('if (state->interrupts_enabled == false) {')
    code.append('    if (read_u8(0xffff) & read_u8(0xff0f) & 0x1f) {')
    code.append('        state->halt_bug = true; } }')    
#    code.append('state->interrupts_enabled = false;')
    return format_c_code_list(code)

def gb_op_stop(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    code.append('r16->PC += %s;' % (byte_len, ))
    code.append('state->stop = true;')
#    code.append('state->interrupts_enabled = false;')
    return format_c_code_list(code)

###############################################################################

def gb_op_ld(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op1 = instr.split()[1].split(',')[0]    
    op2 = instr.split()[1].split(',')[1]
    if op1 in sixteen_bit_registers:
        if op1 == 'SP' and op2 == 'HL':
            code.append('%s = %s;' % (sixteen_bit_registers[op1], sixteen_bit_registers[op2]))
        elif op2 == 'd16':            
            code.append('%s = read_u16(r16->PC+1);' % (sixteen_bit_registers[op1],))
        elif op1 == 'HL' and op2 == 'SP+r8':                    #obscure
            code.append('int offset = (int8_t)read_u8(r16->PC+1);')
            code.append('r16->HL = r16->SP + offset;')
            code.append('clear_z_flag;')
            code.append('clear_n_flag;')
            code.append('(offset & 0xf) + (r16->SP & 0xf) > 0xf ? set_h_flag : clear_h_flag;')
            code.append('(offset & 0xff) + (r16->SP & 0xff) > 0xff ? set_c_flag : clear_c_flag;')
    elif op1 in eight_bit_registers:
        if op2 in eight_bit_registers:
            code.append('%s = %s;' % (eight_bit_registers[op1], eight_bit_registers[op2]))
        elif op2 == 'd8':
            code.append('%s = read_u8(r16->PC+1);' % (eight_bit_registers[op1],))    # XXX    d8
        elif op2 == '(a16)':
            code.append('uint16_t a16 = read_u16(r16->PC+1);')
            code.append('%s = read_u8(a16);' % (eight_bit_registers[op1],))          # XXX    a16
        elif op2 in sixteen_bit_reg_addr:
            code.append('%s = read_u8(%s);' % (eight_bit_registers[op1], sixteen_bit_reg_addr[op2]))
    elif op1 == '(a16)':
        code.append('uint16_t a16 = read_u16(r16->PC+1);')
        if op2 == 'SP':
            code.append('write_u16(a16, %s);' % (sixteen_bit_registers[op2],))      # two byte write
        elif op2 == 'A':
            code.append('write_u8(a16, %s);' % (eight_bit_registers[op2],))        # one byte write?
    elif op1 in sixteen_bit_reg_addr:
        if op2 in eight_bit_registers:
            code.append('write_u8(%s, %s);' % (sixteen_bit_reg_addr[op1], eight_bit_registers[op2]))
        elif op2 == 'd8':
            code.append('write_u8(%s, read_u8(r16->PC+1));' % (sixteen_bit_reg_addr[op1],))
            
    code.append('r16->PC += %s;' % (byte_len,))
    return format_c_code_list(code)

def gb_op_ldh(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op1 = instr.split()[1].split(',')[0]    
    op2 = instr.split()[1].split(',')[1]
    code.append('uint8_t a8 = read_u8(r16->PC+1);')
    if op1 == '(a8)' and op2 == 'A':
        code.append('write_u8(0xff00 + a8, r8->A);')
    elif op1 == 'A' and op2 == '(a8)':
        code.append('r8->A = read_u8(0xff00 + a8);')        
    code.append('r16->PC += %s;' % (byte_len,))
    return format_c_code_list(code)

def  gb_op_adc(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op1 = instr.split()[1].split(',')[0]
    op2 = instr.split()[1].split(',')[1]
    code.append('uint8_t op;')
    code.append('uint32_t calc;')
    if op2 in eight_bit_registers:
        code.append('op = %s;' % (eight_bit_registers[op2],))
    elif op2 in sixteen_bit_reg_addr:
        code.append('op = read_u8(%s);' % (sixteen_bit_reg_addr[op2],))
    elif op2 == 'd8':
        code.append('op = read_u8(r16->PC+1);')
    else:
        code.append('/* FIXME: ADC */')
    code.append('calc = r8->A + op + is_c_flag;')

    code.append('(calc & 0xff) == 0 ? set_z_flag : clear_z_flag;')
    code.append('clear_n_flag;')
    code.append('is_c_flag + (r8->A & 0xf) + (op & 0xf) > 0xf ? set_h_flag : clear_h_flag;')
    code.append('is_c_flag + op + r8->A > 0xff ? set_c_flag : clear_c_flag;');
    code.append('r8->A = calc & 0xff;')
    
    code.append('r16->PC += %s;' % (byte_len,))
    return format_c_code_list(code)

def  gb_op_add(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg

    op1 = instr.split()[1].split(',')[0]
    op2 = instr.split()[1].split(',')[1]

    if op1 == 'A':
        code.append('uint8_t op;')
        code.append('uint32_t calc;')
        if op2 == '(HL)':
            code.append('op = read_u8(r16->HL);')
        elif op2 in eight_bit_registers:
            code.append('op = %s;' % (eight_bit_registers[op2],))
        elif op2 == 'd8':
            code.append('op = read_u8(r16->PC+1);')
        code.append('calc = r8->A + op;')
        code.append('(calc & 0xff) == 0 ? set_z_flag : clear_z_flag;')
        code.append('clear_n_flag;')
        code.append('(r8->A & 0xf) + (op & 0xf) > 0xf ? set_h_flag : clear_h_flag;')
        code.append('calc > 0xff ? set_c_flag : clear_c_flag;');
        code.append('r8->A += op;')
    elif op1 == 'HL':
        code.append('uint16_t op;')
        code.append('uint32_t calc;')
        code.append('clear_n_flag;')
        code.append('op = %s;' % (sixteen_bit_registers[op2],))
        code.append('(r16->HL & 0xfff) + (op & 0xfff) > 0xfff ? set_h_flag : clear_h_flag;')
        code.append('calc = r16->HL + op;')
        code.append('calc > 0xffff ? set_c_flag : clear_c_flag;');
        code.append('r16->HL += op;')
    elif op1 == 'SP':
        code.append('clear_z_flag;')
        code.append('clear_n_flag;')
        code.append('int16_t op = (int8_t)read_u8(r16->PC+1);')    #signed as per GBCPUman
        code.append('(r16->SP & 0xf) + (op & 0xf) > 0xf ? set_h_flag : clear_h_flag;')
        code.append('(r16->SP & 0xff) + (op & 0xff) > 0xff ? set_c_flag : clear_c_flag;');
        code.append('r16->SP += op;')

    else:
        code.append('/* FIXME: ADD */')
        
    code.append('r16->PC += %s;' % (byte_len,))
    return format_c_code_list(code)

def  gb_op_and(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op1 = instr.split()[1]
    code.append('uint8_t op;')
    if op1 in eight_bit_registers:
        code.append('op = %s;' % (eight_bit_registers[op1],))
    elif op1 == '(HL)':
        code.append('op = read_u8(%s);' % (sixteen_bit_reg_addr[op1],))
    elif op1 == 'd8':
        code.append('op = read_u8(r16->PC+1);')
    else:
        code.append('/* FIXME: AND */')
    code.append('r8->A &= op;')
    code.append('r8->A == 0 ? set_z_flag : clear_z_flag;')
    code.append('clear_n_flag;')
    code.append('set_h_flag;')
    code.append('clear_c_flag;')
    code.append('r16->PC += %s;' % (byte_len,))
    return format_c_code_list(code)


def  gb_op_or(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op1 = instr.split()[1]
    if op1 in eight_bit_registers:
        op0 = eight_bit_registers[op1]
    elif op1 == '(HL)':
        op0 = 'read_u8(r16->HL)'
    elif op1 == 'd8':
        op0 = 'read_u8(r16->PC+1)'
    else:
        code.append('/* FIXME: OR */')
    code.append('r8->A |= %s;' % (op0,))
    code.append('r8->A == 0 ? set_z_flag : clear_z_flag;')
    code.append('clear_n_flag;')
    code.append('clear_h_flag;')
    code.append('clear_c_flag;')
    code.append('r16->PC += %s;' % (byte_len,))
    return format_c_code_list(code)

def  gb_op_bit(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op1 = instr.split()[1].split(',')[0]    #bit
    op2 = instr.split()[1].split(',')[1]    #reg/mem

    if op2 in eight_bit_registers:
        code.append('uint8_t op = %s;' % (eight_bit_registers[op2], ))
    elif op2 == '(HL)':
        code.append('uint8_t op = read_u8(r16->HL);')
    else:
        code.append('/* FIXME: BIT */')
    code.append('op & (1 << %s) ? clear_z_flag : set_z_flag;' % (op1,))#set Z flag if bit not set
    code.append('clear_n_flag;')
    code.append('set_h_flag;')    
    code.append('r16->PC += %s;' % (byte_len,))
    return format_c_code_list(code)

def  gb_op_ccf(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    code.append('is_c_flag ? clear_c_flag : set_c_flag;')
    code.append('clear_n_flag;')
    code.append('clear_h_flag;')
    code.append('r16->PC += %s;' % (byte_len,))
    return format_c_code_list(code)

def  gb_op_scf(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    code.append('clear_n_flag;')
    code.append('clear_h_flag;')    
    code.append('set_c_flag;')    
    code.append('r16->PC += %s;' % (byte_len,))
    return format_c_code_list(code)

def  gb_op_cp(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op1 = instr.split()[1]
    if op1 in eight_bit_registers:
        op0 = eight_bit_registers[op1]
    elif op1 == '(HL)':
        op0 = 'read_u8(r16->HL)'
    elif op1 == 'd8':
        op0 = 'read_u8(r16->PC+1)'
    else:
        code.append('/* FIXME: CP */')
    code.append('uint8_t op = %s;' % (op0,))
    code.append('r8->A == op ? set_z_flag : clear_z_flag;')
    code.append('set_n_flag;')
    code.append('(r8->A & 0xf) < (op & 0xf) ? set_h_flag : clear_h_flag;')
    code.append('r8->A < op ? set_c_flag : clear_c_flag;')
    code.append('r16->PC += %s;' % (byte_len,))
    return format_c_code_list(code)

def  gb_op_cpl(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    code.append('r8->A = (~r8->A);')
    code.append('set_n_flag;')
    code.append('set_h_flag;')        
    code.append('r16->PC += %s;' % (byte_len,))
    return format_c_code_list(code)

def  gb_op_dec(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op1 = instr.split()[1]
    if op1 in eight_bit_registers:
        code.append('uint8_t op = %s;' % (eight_bit_registers[op1],))        
    elif op1 == '(HL)':
        code.append('uint8_t op = read_u8(r16->HL);')
    elif op1 in sixteen_bit_registers:
        code.append('uint16_t op = %s;' % (sixteen_bit_registers[op1],))
    code.append('op--;')
    if (op1 in eight_bit_registers) or (op1 == '(HL)'):
        code.append('op == 0 ? set_z_flag : clear_z_flag;')
        code.append('set_n_flag;')
        code.append('(op & 0xf) == 0xf ? set_h_flag : clear_h_flag;')
    if op1 == '(HL)':
        code.append('write_u8(r16->HL, op);')
    elif op1 in eight_bit_registers:
        code.append('%s = op;' % (eight_bit_registers[op1],))
    elif op1 in sixteen_bit_registers:
        code.append('%s = op;' % (sixteen_bit_registers[op1],))
    code.append('r16->PC += %s;' % (byte_len,))
    return format_c_code_list(code)


def  gb_op_inc(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op1 = instr.split()[1]
    if op1 in eight_bit_registers:
        code.append('uint8_t op = %s;' % (eight_bit_registers[op1],))
    elif op1 == '(HL)':
        code.append('uint8_t op = read_u8(r16->HL);')
    elif op1 in sixteen_bit_registers:
        code.append('uint16_t op = %s;' % (sixteen_bit_registers[op1],))
    code.append('op++;')
    if (op1 in eight_bit_registers) or (op1 == '(HL)'):
        code.append('op == 0 ? set_z_flag : clear_z_flag;')
        code.append('clear_n_flag;')
        code.append('(op & 0xf) == 0 ? set_h_flag : clear_h_flag;')
    if op1 == '(HL)':
        code.append('write_u8(r16->HL, op);')
    elif op1 in eight_bit_registers:
        code.append('%s = op;' % (eight_bit_registers[op1],))
    elif op1 in sixteen_bit_registers:
        code.append('%s = op;' % (sixteen_bit_registers[op1],))
    code.append('r16->PC += %s;' % (byte_len,))
    return format_c_code_list(code)

def  gb_op_sbc(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op1 = instr.split()[1].split(',')[0]
    op2 = instr.split()[1].split(',')[1]
    code.append('uint8_t op;')
    if op2 in eight_bit_registers:
        code.append('op = %s;' % (eight_bit_registers[op2],))
    elif op2 == '(HL)':
        code.append('op = read_u8(r16->HL);')
    elif op2 == 'd8':
        code.append('op = read_u8(r16->PC+1);')
    else:
        code.append('/* FIXME: SBC */')        
    code.append('uint8_t calc = r8->A - op - is_c_flag;')
    code.append('calc == 0 ? set_z_flag : clear_z_flag;')
    code.append('set_n_flag;')
    code.append('((r8->A & 0xf)-(op & 0xf)-is_c_flag)<0 ? set_h_flag : clear_h_flag;')
    code.append('r8->A < (op + is_c_flag) ? set_c_flag : clear_c_flag;');
    code.append('r8->A = calc;')    
    code.append('r16->PC += %s;' % (byte_len,))
    return format_c_code_list(code)

def  gb_op_sub(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op2 = instr.split()[1]
    code.append('uint8_t op;')
    if op2 in eight_bit_registers:
        code.append('op = %s;' % (eight_bit_registers[op2],))
    elif op2 == '(HL)':
        code.append('op = read_u8(r16->HL);')
    elif op2 == 'd8':
        code.append('op = read_u8(r16->PC+1);')
    else:
        code.append('/* FIXME: SUB */')
    code.append('r8->A == op ? set_z_flag : clear_z_flag;')
    code.append('set_n_flag;')
    code.append('(r8->A & 0xf) < (op & 0xf) ? set_h_flag : clear_h_flag;')
    code.append('r8->A < op ? set_c_flag : clear_c_flag;');
    code.append('r8->A = r8->A - op;')
    
    code.append('r16->PC += %s;' % (byte_len,))
    return format_c_code_list(code)

def  gb_op_swap(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op1 = instr.split()[1]
    if op1 in eight_bit_registers:
        op0 = eight_bit_registers[op1]
    elif op1 == '(HL)':
        op0 = 'read_u8(r16->HL)'
    code.append('uint8_t op = %s;' % (op0,))
    code.append('op == 0 ? set_z_flag : clear_z_flag;')
    code.append('clear_n_flag;')
    code.append('clear_h_flag;')
    code.append('clear_c_flag;')
    code.append('op = ((op & 0xf) << 4) | ((op & 0xf0) >> 4);')
    if op1 == '(HL)':
        code.append('write_u8(r16->HL, op);')
    else:
        code.append('%s = op;' % (op0,))
    code.append('r16->PC += %s;' % (byte_len,))
    return format_c_code_list(code)

def  gb_op_xor(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op1 = instr.split()[1]
    if op1 in eight_bit_registers:
        op0 = eight_bit_registers[op1]
    elif op1 == '(HL)':
        op0 = 'read_u8(r16->HL)'
    elif op1 == 'd8':
        op0 = 'read_u8(r16->PC+1)'
    else:
        code.append('/* FIXME: XOR */')
    code.append('r8->A ^= %s;' % (op0,))
    code.append('r8->A == 0 ? set_z_flag : clear_z_flag;')
    code.append('clear_n_flag;')
    code.append('clear_h_flag;')
    code.append('clear_c_flag;')    
    code.append('r16->PC += %s;' % (byte_len,))
    return format_c_code_list(code)

def  gb_op_res(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op1 = instr.split()[1].split(',')[0]    #bit
    op2 = instr.split()[1].split(',')[1]    #reg/mem
    if op2 == '(HL)':
        code.append('uint8_t op = read_u8(r16->HL);')
        code.append('op &= ~(1 << %s);' % (op1,))
        code.append('write_u8(r16->HL, op);')
    elif op2 in eight_bit_registers:
        op0 = eight_bit_registers[op2]        
        code.append('%s &= ~(1 << %s);' % (op0, op1))
    code.append('r16->PC += %s;' % (byte_len,))
    return format_c_code_list(code)

def  gb_op_set(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op1 = instr.split()[1].split(',')[0]    #bit
    op2 = instr.split()[1].split(',')[1]    #reg/mem
    if op2 == '(HL)':
        code.append('uint8_t op = read_u8(r16->HL);')
        code.append('op |= (1 << %s);' % (op1, ))
        code.append('write_u8(r16->HL, op);')        
    elif op2 in eight_bit_registers:
        op0 = eight_bit_registers[op2]
        code.append('%s |= (1 << %s);' % (op0, op1))
    code.append('r16->PC += %s;' % (byte_len,))
    return format_c_code_list(code)

def  gb_op_sla(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op1 = instr.split()[1]
    if op1 == '(HL)':
        code.append('uint8_t op = read_u8(r16->HL);')
    elif op1 in eight_bit_registers:
        code.append('uint8_t op = %s;' % (eight_bit_registers[op1],))
    code.append('clear_n_flag;')    
    code.append('clear_h_flag;')
    code.append('op & 0x80 ? set_c_flag : clear_c_flag;')
    code.append('op <<= 1;')
    code.append('op == 0 ? set_z_flag : clear_z_flag;')
    if op1 == '(HL)':
        code.append('write_u8(r16->HL, op);')        
    elif op1 in eight_bit_registers:
        code.append('%s = op;' % (eight_bit_registers[op1],))
    code.append('r16->PC += %s;' % (byte_len,))
    return format_c_code_list(code)

def  gb_op_sra(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op1 = instr.split()[1]
    if op1 == '(HL)':
        code.append('uint8_t op = read_u8(r16->HL);')        
    elif op1 in eight_bit_registers:
        code.append('uint8_t op = %s;' % (eight_bit_registers[op1],))
    code.append('clear_n_flag;')    
    code.append('clear_h_flag;')
    code.append('op & 1 ? set_c_flag : clear_c_flag;')
    code.append('op = (op & 0x80) | (op >> 1) ;')
    code.append('op == 0 ? set_z_flag : clear_z_flag;')
    if op1 == '(HL)':
        code.append('write_u8(r16->HL, op);')        
    elif op1 in eight_bit_registers:
        code.append('%s = op;' % (eight_bit_registers[op1],))
    code.append('r16->PC += %s;' % (byte_len,))
    return format_c_code_list(code)

def  gb_op_srl(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op1 = instr.split()[1]
    if op1 == '(HL)':
        code.append('uint8_t op = read_u8(r16->HL);')        
    elif op1 in eight_bit_registers:
        code.append('uint8_t op = %s;' % (eight_bit_registers[op1],))
    code.append('clear_n_flag;')    
    code.append('clear_h_flag;')
    code.append('op & 1 ? set_c_flag : clear_c_flag;')
    code.append('op >>= 1;')
    code.append('op == 0 ? set_z_flag : clear_z_flag;')
    if op1 == '(HL)':
        code.append('write_u8(r16->HL, op);')
    elif op1 in eight_bit_registers:
        code.append('%s = op;' % (eight_bit_registers[op1],))
    code.append('r16->PC += %s;' % (byte_len,))
    return format_c_code_list(code)

def  gb_op_rr(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op1 = instr.split()[1]
    if op1 == '(HL)':
        code.append('uint8_t op = read_u8(r16->HL);')
    elif op1 in eight_bit_registers:
        code.append('uint8_t op = %s;' % (eight_bit_registers[op1],))
    code.append('uint8_t carry = is_c_flag;')
    code.append('op & 1 ? set_c_flag : clear_c_flag;')
    code.append('op = (op >> 1) | (carry << 7);')
    code.append('clear_n_flag;')    
    code.append('clear_h_flag;')
    code.append('op == 0 ? set_z_flag : clear_z_flag;')
    if op1 == '(HL)':
        code.append('write_u8(r16->HL, op);')        
    elif op1 in eight_bit_registers:
        code.append('%s = op;' % (eight_bit_registers[op1],))
    code.append('r16->PC += %s;' % (byte_len,))
    return format_c_code_list(code)

def  gb_op_rl(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op1 = instr.split()[1]
    if op1 == '(HL)':
        code.append('uint8_t op = read_u8(r16->HL);')        
    elif op1 in eight_bit_registers:
        code.append('uint8_t op = %s;' % (eight_bit_registers[op1],))
    code.append('uint8_t carry = is_c_flag;')
    code.append('op & 0x80 ? set_c_flag : clear_c_flag;')
    code.append('op = (op << 1) | carry;')
    code.append('clear_n_flag;')    
    code.append('clear_h_flag;')
    code.append('op == 0 ? set_z_flag : clear_z_flag;')
    if op1 == '(HL)':                   
        code.append('write_u8(r16->HL, op);')
    elif op1 in eight_bit_registers:    
        code.append('%s = op;' % (eight_bit_registers[op1],))
    code.append('r16->PC += %s;' % (byte_len,))
    return format_c_code_list(code)

def  gb_op_rlc(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op1 = instr.split()[1]    
    if op1 == '(HL)':
        code.append('uint8_t op = read_u8(r16->HL);')
    elif op1 in eight_bit_registers:
        code.append('uint8_t op = %s;' % (eight_bit_registers[op1],))
    code.append('op = (op << 1) | (op >> 7);')
    code.append('op == 0 ? set_z_flag : clear_z_flag;')
    code.append('clear_n_flag;')    
    code.append('clear_h_flag;')    
    code.append('op & 1 ? set_c_flag : clear_c_flag;')
    if op1 == '(HL)':
        code.append('write_u8(r16->HL, op);')        
    elif op1 in eight_bit_registers:
        code.append('%s = op;' % (eight_bit_registers[op1],))
    code.append('r16->PC += %s;' % (byte_len,))
    return format_c_code_list(code)

def  gb_op_rrc(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op1 = instr.split()[1]
    if op1 == '(HL)':
        code.append('uint8_t op = read_u8(r16->HL);')        
    elif op1 in eight_bit_registers:
        code.append('uint8_t op = %s;' % (eight_bit_registers[op1],))
    code.append('op = (op >> 1) | ((op & 1) << 7);')
    code.append('op == 0 ? set_z_flag : clear_z_flag;')
    code.append('clear_n_flag;')    
    code.append('clear_h_flag;')    
    code.append('op & 0x80 ? set_c_flag : clear_c_flag;')    
    if op1 == '(HL)':
        code.append('write_u8(r16->HL, op);')
    elif op1 in eight_bit_registers:
        code.append('%s = op;' % (eight_bit_registers[op1],))
    code.append('r16->PC += %s;' % (byte_len,))
    return format_c_code_list(code)

#####
def  gb_op_rla(instr, byte_len, cycles, flags):  #same like rl, but z flag always set to 0
    code = [] + cast_void_to_reg
    op0 = eight_bit_registers['A']  #XXX
    code.append('uint8_t carry = is_c_flag;')
    code.append('%s & 0x80 ? set_c_flag : clear_c_flag;' % (op0,))
    code.append('%s = (%s << 1) | carry;' % (op0,op0))
    code.append('clear_n_flag;')    
    code.append('clear_h_flag;')
    code.append('clear_z_flag;')
    code.append('r16->PC += %s;' % (byte_len,))
    return format_c_code_list(code)

def  gb_op_rlca(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op0 = eight_bit_registers['A']  #XXX
    code.append('%s = (%s << 1) | (%s >> 7);' % (op0,op0,op0))
    code.append('clear_z_flag;')
    code.append('clear_n_flag;')    
    code.append('clear_h_flag;')    
    code.append('%s & 1 ? set_c_flag : clear_c_flag;' % (op0,))
    code.append('r16->PC += %s;' % (byte_len,))
    return format_c_code_list(code)

def gb_op_rrca(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op0 = eight_bit_registers['A']  #XXX
    code.append('%s = (%s >> 1) | ((%s & 1) << 7);' % (op0,op0,op0))
    code.append('clear_z_flag;')
    code.append('clear_n_flag;')    
    code.append('clear_h_flag;')    
    code.append('%s & 0x80 ? set_c_flag : clear_c_flag;' % (op0,))
    code.append('r16->PC += %s;' % (byte_len,))
    return format_c_code_list(code)

def gb_op_rra(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op0 = eight_bit_registers['A']  #XXX
    code.append('uint8_t carry = is_c_flag;')
    code.append('%s & 1 ? set_c_flag : clear_c_flag;' % (op0,))
    code.append('%s = (%s >> 1) | (carry << 7);' % (op0,op0))    
    code.append('clear_z_flag;')
    code.append('clear_n_flag;')    
    code.append('clear_h_flag;')
    code.append('r16->PC += %s;' % (byte_len,))
    return format_c_code_list(code)

def gb_op_daa(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    code.append('/*  https://forums.nesdev.com/viewtopic.php?f=20&t=15944  */')
    code.append('if (!is_n_flag) {')
    code.append('    if ((is_c_flag) || (r8->A > 0x99))              { r8->A += 0x60; set_c_flag; }')
    code.append('    if ((is_h_flag) || ((r8->A & 0x0f) > 0x09))     { r8->A += 0x6; }')
    code.append('} else {')
    code.append('    if (is_c_flag)                                  { r8->A -= 0x60; }')
    code.append('    if (is_h_flag)                                  { r8->A -= 0x6;  }     }')
    code.append('r8->A == 0 ? set_z_flag : clear_z_flag;')
    code.append('clear_h_flag;')
    code.append('r16->PC += %s;' % (byte_len,))
    return format_c_code_list(code)

gb_ops = {
        'DAA': gb_op_daa,   #decimal adjust register A 
        'ADC': gb_op_adc,   #add with carry
        'ADD': gb_op_add,
        'AND': gb_op_and,
         'OR': gb_op_or,
        'BIT': gb_op_bit,   #test bit x, set z flag if bit x is 0
        'CCF': gb_op_ccf,   #toggle c flag
        'SCF': gb_op_scf,   #set c flag
         'CP': gb_op_cp,    #compare
        'CPL': gb_op_cpl,   #complement
        'DEC': gb_op_dec,
        'INC': gb_op_inc,
        'SBC': gb_op_sbc,   #subtract with carry
        'SUB': gb_op_sub,
       'SWAP': gb_op_swap,  #swap hi/low nibbles
        'XOR': gb_op_xor,
        'RES': gb_op_res,   #clear bit x
        'SET': gb_op_set,   #set bit x
        'SLA': gb_op_sla,   #store old bit 7 in C flag, shift left by 1, set Z if needed
        'SRA': gb_op_sra,   #store old bit 0 in C flag, preserve bit 7, shift right by 1, set Z if needed
        'SRL': gb_op_srl,   #store old bit 0 in C flag,                 shift right by 1, set Z if needed
         'RR': gb_op_rr,
         'RL': gb_op_rl,
        'RLA': gb_op_rla,    #op cb17: RL A, op 17: RLA
        'RLC': gb_op_rlc,
       'RLCA': gb_op_rlca,
        'RRC': gb_op_rrc,
       'RRCA': gb_op_rrca,
        'RRA': gb_op_rra,
         'LD': gb_op_ld,
        'LDH': gb_op_ldh,
       'CALL': gb_op_call,
         'JP': gb_op_jp,
         'JR': gb_op_jr,
       'PUSH': gb_op_push,
        'POP': gb_op_pop,
        'RET': gb_op_ret,
       'RETI': gb_op_reti,
         'EI': gb_op_ei,
         'DI': gb_op_di,
        'NOP': gb_op_nop,
        'RST': gb_op_rst,
       'HALT': gb_op_halt,
       'STOP': gb_op_stop
        }