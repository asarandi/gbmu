#!/usr/bin/env python3

from bs4 import BeautifulSoup

# data from http://pastraiser.com/cpu/gameboy/gameboy_opcodes.html
text = None
with open('gameboy_opcodes.html') as fp:
    soup = BeautifulSoup(fp, 'html.parser')
    fp.close

# we have two tables with data
# first row of the table contains the lower nibble of each opcode
# first column of each subsequent row contains the upper nibble

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


headers = [
            '#include <stdint.h>',
            '',
            '#define set_z       (reg[1] |= 0x80)',
            '#define set_n       (reg[1] |= 0x40)',
            '#define set_h       (reg[1] |= 0x20)',
            '#define set_c       (reg[1] |= 0x10)',
            '',
            '#define clear_z     (reg[1] &= (~0x80))',
            '#define clear_n     (reg[1] &= (~0x40))',
            '#define clear_h     (reg[1] &= (~0x20))',
            '#define clear_c     (reg[1] &= (~0x10))',
            ''

        ]

print('\n'.join(headers))


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

        text = byte_len = cycles = flags = 'undefined'


        clear_flags_mask = 0
        set_flags_mask = 0

        if len(data) > 1:
            text = data[0]
            byte_len = data[2].split()[0]
            cycles = data[2].split()[1]
            flags = data[4]

            flags_sp = flags.split()

            for f in range(4):
                if flags_sp[f] == '0':
                    clear_flags_mask += (1 << (7-f))
                elif flags_sp[f] == '1':
                    set_flags_mask += (1 << (7-f))

        sp = text.split()

        addr = {
                'A': '0',
                'B': '2',
                'C': '3',
                'D': '4',
                'E': '5',
                'H': '6',
                'L': '7'
                }


        code = None

        if sp[0] == 'LD':   #loads
            ops = sp[1].split(',')
            if ops[0] in addr:
                if ops[1] == 'd8':  # 8-bit loads
                    code = '\treg[%s] = mem[1]; /* code LD imm */\n' % (addr[ops[0]],)
                elif ops[1] in addr:
                    code = '\treg[%s] = reg[%s]; /* code LD reg */\n' % (addr[ops[0]], addr[ops[1]])
                else:                    
                    code = '/* FIXME: code LD */\n'
                    
        elif sp[0] == 'AND':                
            if sp[1] in addr:
                code  = '\treg[0] &= reg[%s];    /* code AND */\n' % (addr[sp[1]], )
                code += '\treg[0] == 0 ? set_z : clear_z;\n'
            else:
                code = '/* FIXME: code AND */\n'




    
        c  = 'void op_%s(uint8_t *reg, uint8_t *mem)\n' % (opcode,)
        c += '{\n'
        c += '\t/*\n'
        c += '\t\t    category: %s\n' % (bgcolor[bgc],)
        c += '\t\t instruction: %s\n' % (text,)
        c += '\t\t   num bytes: %s\n' % (byte_len,)
        c += '\t\t      cycles: %s\n' % (cycles,)
        c += '\t\t       flags: %s\n' % (flags,)
        c +=  '\t*/\n'

        if code:
            c += code

        if clear_flags_mask != 0:
            c += '\treg[1] &= (~%s); /* clear flags */\n' % (hex(clear_flags_mask),)
        if set_flags_mask != 0:
            c += '\treg[1] |= %s; /* set flags */\n' % (hex(set_flags_mask),)

        c += '}\n'
        c += '\n'


        print(c)





