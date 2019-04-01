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
        }

sixteen_bit_registers = {
        'BC': 'r16->BC',
        'DE': 'r16->DE',
        'HL': 'r16->HL',
        'SP': 'r16->SP'
        }

sixteen_bit_reg_addr = {        
         '(BC)': 'mem[r16->BC]',
         '(DE)': 'mem[r16->DE]',
         '(HL)': 'mem[r16->HL]',
        '(HL+)': 'mem[(r16->HL)++]',
        '(HL-)': 'mem[(r16->HL)--]'
        }

def format_c_code_list(lst):
    code = '\n'
    for item in lst:
        code += '\t' + item + '\n'
    return code

def  gb_op_adc(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op1 = instr.split()[1].split(',')[0]
    op2 = instr.split()[1].split(',')[1]
    code.append('uint8_t op;')
    code.append('uint32_t calc;')
    if op2 in eight_bit_registers:
        code.append('op = %s;' % (eight_bit_registers[op2],))
    elif op2 in sixteen_bit_reg_addr:
        code.append('op = %s;' % (sixteen_bit_reg_addr[op2],))
    elif op2 == 'd8':
        code.append('op = mem[(r16->PC)+1];')
    else:
        code.append('/* FIXME: ADC */')
    code.append('calc = r8->A + op + is_c_flag;')

    code.append('(calc & 0xff) == 0 ? set_z_flag : clear_z_flag;')
    code.append('clear_n_flag;')
    code.append('is_c_flag + (r8->A & 0xf) + (op & 0xf) > 0xf ? set_h_flag : clear_h_flag;')
    code.append('is_c_flag + calc > 0xff ? set_c_flag : clear_c_flag;');
    code.append('r8->A = r8->A + op + is_c_flag;')
    return format_c_code_list(code)

def  gb_op_add(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg

    op1 = instr.split()[1].split(',')[0]
    op2 = instr.split()[1].split(',')[1]

    if op1 in eight_bit_registers:
        code.append('uint8_t op;')
        code.append('uint32_t calc;')
        if op2 in eight_bit_registers:
            code.append('op = %s;' % (eight_bit_registers[op2],))
        elif op2 == 'd8':
            code.append('op = mem[(r16->PC)+1];')
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
        code.append('int16_t op = (int8_t)mem[(r16->PC)+1];')    #signed as per GBCPUman
        code.append('(r16->SP & 0xf) + (op & 0xf) > 0xf ? set_h_flag : clear_h_flag;')
        code.append('(r16->SP & 0xff) + (op & 0xff) > 0xff ? set_c_flag : clear_c_flag;');
        code.append('r16->SP += op;')

    else:
        code.append('/* FIXME: ADD */')
    return format_c_code_list(code)

def  gb_op_and(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op1 = instr.split()[1]
    code.append('uint8_t op;')
    if op1 in eight_bit_registers:
        code.append('op = %s;' % (eight_bit_registers[op1],))
    elif op1 == '(HL)':
        code.append('op = %s;' % (sixteen_bit_reg_addr[op1],))
    elif op1 == 'd8':
        code.append('op = mem[(r16->PC)+1];')
    else:
        code.append('/* FIXME: AND */')
    code.append('r8->A &= op;')
    code.append('r8->A == 0 ? set_z_flag : clear_z_flag;')
    code.append('clear_n_flag;')
    code.append('set_h_flag;')
    code.append('clear_c_flag;')
    return format_c_code_list(code)


def  gb_op_or(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op1 = instr.split()[1]
    if op1 in eight_bit_registers:
        op0 = eight_bit_registers[op1]
    elif op1 == '(HL)':
        op0 = sixteen_bit_reg_addr[op1]
    elif op1 == 'd8':
        op0 = 'mem[(r16->PC)+1]'
    else:
        code.append('/* FIXME: OR */')
    code.append('r8->A |= %s;' % (op0,))
    code.append('r8->A == 0 ? set_z_flag : clear_z_flag;')
    code.append('clear_n_flag;')
    code.append('clear_h_flag;')
    code.append('clear_c_flag;')
    return format_c_code_list(code)

def  gb_op_bit(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op1 = instr.split()[1].split(',')[0]    #bit
    op2 = instr.split()[1].split(',')[1]    #reg/mem

    if op2 in eight_bit_registers:
        op0 = eight_bit_registers[op2]
    elif op2 == '(HL)':
        op0 = sixteen_bit_reg_addr[op2]
    else:
        code.append('/* FIXME: BIT */')
    code.append('%s & (1 << %s) ? clear_z_flag : set_z_flag;' % (op0, op1) )    #set Z flag if bit no set
    code.append('clear_n_flag;')
    code.append('set_h_flag;')
    return format_c_code_list(code)

def  gb_op_ccf(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    code.append('is_c_flag ? clear_c_flag : set_c_flag;')
    code.append('clear_n_flag;')
    code.append('clear_h_flag;')
    return format_c_code_list(code)

def  gb_op_scf(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    code.append('clear_n_flag;')
    code.append('clear_h_flag;')    
    code.append('set_c_flag;')
    return format_c_code_list(code)

def  gb_op_cp(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op1 = instr.split()[1]
    if op1 in eight_bit_registers:
        op0 = eight_bit_registers[op1]
    elif op1 == '(HL)':
        op0 = sixteen_bit_reg_addr[op1]
    elif op1 == 'd8':
        op0 = 'mem[(r16->PC)+1]'
    else:
        code.append('/* FIXME: CP */')
    code.append('uint8_t op = %s;' % (op0,))

    code.append('r8->A == op ? set_z_flag : clear_z_flag;')
    code.append('set_n_flag;')
    code.append('(r8->A & 0xf) < (op & 0xf) ? set_h_flag : clear_h_flag;')
    code.append('r8->A < op ? set_c_flag : clear_c_flag;')
    return format_c_code_list(code)

def  gb_op_cpl(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    code.append('r8->A = (~r8->A);')
    code.append('set_n_flag;')
    code.append('set_h_flag;')    
    return format_c_code_list(code)

def  gb_op_dec(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op1 = instr.split()[1]
    if (op1 in eight_bit_registers) or (op1 == '(HL)'):
        if op1 in eight_bit_registers:
            op0 = eight_bit_registers[op1]
        else:   # (HL)
            op0 = sixteen_bit_reg_addr[op1]
        code.append('%s--;' % (op0,))
        code.append('%s == 0 ? set_z_flag : clear_z_flag;' % (op0,))
        code.append('set_n_flag;')
        code.append('(%s & 0xf) == 0xf ? set_h_flag : clear_h_flag;' % (op0,))

    elif op1 in sixteen_bit_registers:
        code.append('%s--;' % (sixteen_bit_registers[op1],))
    else:
        code.append('/* FIXME: DEC */')
    return format_c_code_list(code)



def  gb_op_inc(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op1 = instr.split()[1]
    if (op1 in eight_bit_registers) or (op1 == '(HL)'):
        if op1 in eight_bit_registers:
            op0 = eight_bit_registers[op1]
        else:   # (HL)
            op0 = sixteen_bit_reg_addr[op1]
        code.append('%s++;' % (op0,))
        code.append('%s == 0 ? set_z_flag : clear_z_flag;' % (op0,))
        code.append('set_n_flag;')
        code.append('(%s & 0xf) == 0x0 ? set_h_flag : clear_h_flag;' % (op0,))

    elif op1 in sixteen_bit_registers:
        code.append('%s++;' % (sixteen_bit_registers[op1],))
    else:
        code.append('/* FIXME: INC */')
    return format_c_code_list(code)

def  gb_op_sbc(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op1 = instr.split()[1].split(',')[0]
    op2 = instr.split()[1].split(',')[1]
    code.append('uint8_t op;')
    if op2 in eight_bit_registers:
        code.append('op = %s;' % (eight_bit_registers[op2],))
    elif op2 == '(HL)':
        code.append('op = %s;' % (sixteen_bit_reg_addr[op2],))
    elif op2 == 'd8':
        code.append('op = mem[(r16->PC)+1];')
    else:
        code.append('/* FIXME: SBC */')
    code.append('(r8->A - (op + is_c_flag)) == 0 ? set_z_flag : clear_z_flag;')
    code.append('set_n_flag;')
    code.append('(r8->A & 0xf) < ((op + is_c_flag) & 0xf) ? set_h_flag : clear_h_flag;')
    code.append('r8->A < (op + is_c_flag) ? set_c_flag : clear_c_flag;');
    code.append('r8->A = r8->A - (op + is_c_flag);')
    return format_c_code_list(code)

def  gb_op_sub(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op2 = instr.split()[1]
    code.append('uint8_t op;')
    if op2 in eight_bit_registers:
        code.append('op = %s;' % (eight_bit_registers[op2],))
    elif op2 == '(HL)':
        code.append('op = %s;' % (sixteen_bit_reg_addr[op2],))
    elif op2 == 'd8':
        code.append('op = mem[(r16->PC)+1];')
    else:
        code.append('/* FIXME: SUB */')
    code.append('r8->A == op ? set_z_flag : clear_z_flag;')
    code.append('set_n_flag;')
    code.append('(r8->A & 0xf) < (op & 0xf) ? set_h_flag : clear_h_flag;')
    code.append('r8->A < op ? set_c_flag : clear_c_flag;');
    code.append('r8->A = r8->A - op;')
    return format_c_code_list(code)

def  gb_op_swap(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op2 = instr.split()[1]
    if op2 in eight_bit_registers:
        op0 = eight_bit_registers[op2]
    elif op2 == '(HL)':
        op0 = sixteen_bit_reg_addr[op2]
    else:
        code.append('/* FIXME: SWAP */')

    code.append('%s == 0 ? set_z_flag : clear_z_flag;' % (op0,))
    code.append('clear_n_flag;')
    code.append('clear_h_flag;')
    code.append('clear_c_flag;')
    code.append('%s = ((%s & 0xf) << 4) | ((%s & 0xf0) >> 4);' % (op0,op0,op0))
    return format_c_code_list(code)


def  gb_op_xor(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op1 = instr.split()[1]
    if op1 in eight_bit_registers:
        op0 = eight_bit_registers[op1]
    elif op1 == '(HL)':
        op0 = sixteen_bit_reg_addr[op1]
    elif op1 == 'd8':
        op0 = 'mem[(r16->PC)+1]'
    else:
        code.append('/* FIXME: XOR */')
    code.append('r8->A ^= %s;' % (op0,))
    code.append('r8->A == 0 ? set_z_flag : clear_z_flag;')
    code.append('clear_n_flag;')
    code.append('clear_h_flag;')
    code.append('clear_c_flag;')
    return format_c_code_list(code)


def  gb_op_res(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op1 = instr.split()[1].split(',')[0]    #bit
    op2 = instr.split()[1].split(',')[1]    #reg/mem

    if op2 in eight_bit_registers:
        op0 = eight_bit_registers[op2]
    elif op2 == '(HL)':
        op0 = sixteen_bit_reg_addr[op2]
    else:
        code.append('/* FIXME: RES */')
    code.append('%s &= ~(1 << %s);' % (op0, op1))
    return format_c_code_list(code)

def  gb_op_set(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op1 = instr.split()[1].split(',')[0]    #bit
    op2 = instr.split()[1].split(',')[1]    #reg/mem

    if op2 in eight_bit_registers:
        op0 = eight_bit_registers[op2]
    elif op2 == '(HL)':
        op0 = sixteen_bit_reg_addr[op2]
    else:
        code.append('/* FIXME: SET */')
    code.append('%s |= (1 << %s);' % (op0, op1))
    return format_c_code_list(code)

def  gb_op_sla(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op1 = instr.split()[1]

    if op1 in eight_bit_registers:
        op0 = eight_bit_registers[op1]
    elif op1 == '(HL)':
        op0 = sixteen_bit_reg_addr[op1]
    else:
        code.append('/* FIXME: SLA */')

    code.append('(%s << 1) == 0 ? set_z_flag : clear_z_flag;' % (op0,))
    code.append('clear_n_flag;')    
    code.append('clear_h_flag;')
    code.append('%s & 0x80 ? set_c_flag : clear_c_flag;' % (op0,))
    code.append('%s <<= 1;' % (op0,))
    return format_c_code_list(code)

def  gb_op_sra(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op1 = instr.split()[1]

    if op1 in eight_bit_registers:
        op0 = eight_bit_registers[op1]
    elif op1 == '(HL)':
        op0 = sixteen_bit_reg_addr[op1]
    else:
        code.append('/* FIXME: SRA */')
    code.append('clear_n_flag;')    
    code.append('clear_h_flag;')
    code.append('%s & 1 ? set_c_flag : clear_c_flag;' % (op0,))
    code.append('%s = (%s & 0x80) | (%s >> 1) ;' % (op0,op0,op0))
    code.append('%s == 0 ? set_z_flag : clear_z_flag;' % (op0,))
    return format_c_code_list(code)


def  gb_op_srl(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op1 = instr.split()[1]

    if op1 in eight_bit_registers:
        op0 = eight_bit_registers[op1]
    elif op1 == '(HL)':
        op0 = sixteen_bit_reg_addr[op1]
    else:
        code.append('/* FIXME: SRL */')

    code.append('clear_n_flag;')    
    code.append('clear_h_flag;')
    code.append('%s & 1 ? set_c_flag : clear_c_flag;' % (op0,))
    code.append('%s >>= 1;' % (op0,))
    code.append('%s == 0 ? set_z_flag : clear_z_flag;' % (op0,))
    return format_c_code_list(code)


def  gb_op_rr(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op1 = instr.split()[1]

    if op1 in eight_bit_registers:
        op0 = eight_bit_registers[op1]
    elif op1 == '(HL)':
        op0 = sixteen_bit_reg_addr[op1]
    else:
        code.append('/* FIXME: RR */')

    code.append('uint8_t carry = is_c_flag;')
    code.append('%s & 1 ? set_c_flag : clear_c_flag;' % (op0,))
    code.append('%s = (%s >> 1) | (carry << 7);' % (op0,op0))
    code.append('clear_n_flag;')    
    code.append('clear_h_flag;')
    code.append('%s == 0 ? set_z_flag : clear_z_flag;' % (op0,))
    return format_c_code_list(code)

def  gb_op_rl(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op1 = instr.split()[1]

    if op1 in eight_bit_registers:
        op0 = eight_bit_registers[op1]
    elif op1 == '(HL)':
        op0 = sixteen_bit_reg_addr[op1]
    else:
        code.append('/* FIXME: RL */')

    code.append('uint8_t carry = is_c_flag;')
    code.append('%s & 0x80 ? set_c_flag : clear_c_flag;' % (op0,))
    code.append('%s = (%s << 1) | carry;' % (op0,op0))
    code.append('clear_n_flag;')    
    code.append('clear_h_flag;')
    code.append('%s == 0 ? set_z_flag : clear_z_flag;' % (op0,))
    return format_c_code_list(code)


gb_ops = {
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
         'RL': gb_op_rl





        }


