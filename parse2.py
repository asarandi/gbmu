#!/usr/bin/env python3

from bs4 import BeautifulSoup
import os, glob

with open('gameboy_opcodes.html') as fp:
    soup = BeautifulSoup(fp, 'html.parser')
    fp.close

for f in glob.glob('ops/*.c'):
    os.unlink(f)

bgcolor = {
            0: 'UNDEFINED XXX',                 #vim highlight
    '#ff99cc': 'Misc/control instructions',
    '#ffcc99': 'Jumps/calls',
    '#ccccff': '8bit load/store/move instructions',
    '#ccffcc': '16bit load/store/move instructions',
    '#ffff99': '8bit arithmetic/logical instructions',
    '#ffcccc': '16bit arithmetic/logical instructions',
    '#80ffff': '8bit rotations/shifts and bit instructions'
    }


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
    op2 = instr.split(',')[1]
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
    code.append('calc = r8->A + op;')

    code.append('(calc & 0xff) == 0 ? set_z_flag : clear_z_flag;')
    code.append('clear_n_flag;')
    code.append('is_c_flag + (r8->A & 0xf) + (op & 0xf) > 0xf ? set_h_flag : clear_h_flag;')
    code.append('is_c_flag + calc > 0xff ? set_c_flag : clear_c_flag;');
    code.append('r8->A += op;')
    return format_c_code_list(code)


gb_ops = {
        'ADC': gb_op_adc
        }

cells = soup.find_all('td')
for i in range(17*2):
    for j in range(17):
        if i % 17 == 0: continue
        if j % 17 == 0: continue
                
        opcode = '%02x' % (((i%17)-1) *16 +j-1,)
        if i > 17:
            opcode = '%04x' % (0xcb00 + ((i%17)-1) *16 +j-1,)

        cell = cells[i*17+j]
        data = cell.contents

        bgc = 0
        if cell.has_attr('bgcolor'):
            bgc = cell['bgcolor']

        instr = byte_len = cycles = flags = 'undefined'
        if len(data) > 1:
            instr = data[0]
            byte_len = data[2].split()[0]
            cycles = data[2].split()[1]
            flags = data[4]

        code = ''
        op = instr.split()[0]
        if op in gb_ops:
            code = gb_ops[op](instr, byte_len, cycles, flags)

        c  = 'void op_%s(void *reg, uint8_t *mem)\n' % (opcode,)
        c += '{\n'
        c += '\t/*\n'
        c += '\t\t    category: %s\n' % (bgcolor[bgc],)
        c += '\t\t instruction: %s\n' % (instr,)
        c += '\t\t   num bytes: %s\n' % (byte_len,)
        c += '\t\t      cycles: %s\n' % (cycles,)
        c += '\t\t       flags: %s\n' % (flags,)
        c +=  '\t*/\n\n'
        c += code
        c += '}\n'
        c += '\n'
        
        fn = 'ops/' + op + '.c'
        with open(fn, 'a+') as fp:
            fp.write(c)
            fp.close()
