from instructions import *

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
    code.append('mem[r16->SP] = r16->PC + %s;' % (byte_len,))   #return addr on stack
    code.append('r16->PC = mem[r16->PC + 1];')   #
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

    code.append('r16->PC = mem[r16->PC + 1];')   #
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

    code.append('   r16->PC += (int8_t)mem[r16->PC + 1];')  #signed XXX
    code.append('r16->PC += %s;' % (byte_len,))

    return format_c_code_list(code)

def gb_op_push(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op = instr.split()[1]

    code.append('mem[r16->SP] = %s;' % (sixteen_bit_registers[op],))
    code.append('r16->SP -= 2;')
    code.append('r16->PC += %s;' % (byte_len,))
    return format_c_code_list(code)

def gb_op_pop(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    op = instr.split()[1]

    code.append('%s = mem[r16->SP];' % (sixteen_bit_registers[op],))
    code.append('r16->SP += 2;')
    code.append('r16->PC += %s;' % (byte_len,))
    return format_c_code_list(code)


'''
RET NZ 1 20/8 - - - -
RET Z 1 20/8 - - - -
RET 1 16 - - - -
RET NC 1 20/8 - - - -
RET C 1 20/8 - - - -
RETI 1 16 - - - -
'''


def gb_op_ret(instr, byte_len, cycles, flags):
    code = [] + cast_void_to_reg
    if len(instr.split()) == 1:         #unconditional ret
            code.append('r16->PC = mem[r16->SP]; r16->SP += 2; return ;')
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

    code.append('{ r16->PC = mem[r16->SP]; r16->SP += 2; return ; }')
    code.append('r16->PC += %s;' % (byte_len,))
    return format_c_code_list(code)


def gb_op_reti(instr, byte_len, cycles, flags):    
    code = [] + cast_void_to_reg
    code.append('r16->PC = mem[r16->SP];')
    code.append('r16->SP += 2;')
    code.append('state->interrupts_enabled = true;')    
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
       'RETI': gb_op_reti
        }
