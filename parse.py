#!/usr/bin/env python3

from bs4 import BeautifulSoup
import os, glob
from instructions import *

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

signatures = [
        '#include "gb.h"\n'
        ]
instr_names = []
byte_lens = []
cycles_list = []
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

        byte_len = 0
        flag = 0
        cycles = '0'
        instr = 'undefined'
        if len(data) > 1:
            instr = data[0]
            byte_len = data[2].split()[0]
            cycles = data[2].split()[1]
            flags = data[4]

        code = '\tprintf("undefined instruction 0x%02x\\n");\n' % ((i-1)*16+(j-1))
        code += ('\tprintf("state->cycles = %llu\\n", state->cycles);\n')
        code += ('\texit(1);\n')

        op = instr.split()[0]
        if op in gb_ops:
            code = gb_ops[op](instr, byte_len, cycles, flags)


        sig = 'void op_%s(void *reg, t_state *state, uint8_t *mem);' % (opcode,)
#        signatures.append(sig)
        instr_names.append(instr)
#        byte_lens.append(int(byte_len))
        cycles_list.append(cycles)

        c = sig[:-1] + '\n'
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
        if not os.path.exists(fn):
            with open(fn, 'a+') as fp:
                fp.write('#include "gb.h"\n\n')
                fp.close()

        with open(fn, 'a+') as fp:
            fp.write(c)
            fp.close()

#
#with open('ops.h', 'w') as fp:
#    fp.write('\n'.join(signatures))
#    fp.close()
#
#for idx, instr_name in enumerate(instr_names):
#    if idx % 16 == 0:
#        print()
#    print('"%s", ' % (instr_name.lower(),), end='')
#
#print()
#
#for idx, byte_len in enumerate(byte_lens):
#    if idx % 16 == 0:
#        print()
#    print('%d, ' % (byte_len,), end='')
#

#
#
#for idx, cycles in enumerate(cycles_list):
#    if idx % 16 == 0:
#        print()
#    if '/' in cycles:        
#        '''
#        cond = instr_names[idx].split()[1].split(',')[0]
#        if cond == 'Z':
#            print('%s, ' % ('1',), end='')
#        elif cond == 'NZ':
#            print('%s, ' % ('2',), end='')
#        elif cond == 'C':
#            print('%s, ' % ('3',), end='')
#        elif cond == 'NC':
#            print('%s, ' % ('4',), end='')
#        else:
#            print('%s, ' % ('5',), end='')
#        '''
#
#        print('%2s, ' %  (cycles_list[idx].split('/')[1],), end='')
#
#    else:
#        print('%2s, ' %  (cycles_list[idx],), end='')
#
