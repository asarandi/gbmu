#!/usr/bin/env python3

from bs4 import BeautifulSoup
import os, glob
from calls import *

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
        if not os.path.exists(fn):
            with open(fn, 'a+') as fp:
                fp.write('#include "gb.h"\n\n')
                fp.close()

        with open(fn, 'a+') as fp:
            fp.write(c)
            fp.close()
