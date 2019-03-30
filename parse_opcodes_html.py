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
            0: 'UNDEFINED XXX',
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

        text = byte_len = cycles = flags = 'FIXME: undefined'   #vim highlight


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

    
        c  = 'void op_%s(uint8_t *reg, uint8_t *data)\n' % (opcode,)
        c += '{\n'
        c += '\t/*\n'
        c += '\t\t    category: %s\n' % (bgcolor[bgc],)
        c += '\t\t instruction: %s\n' % (text,)
        c += '\t\t   num bytes: %s\n' % (byte_len,)
        c += '\t\t      cycles: %s\n' % (cycles,)
        c += '\t\t       flags: %s\n' % (flags,)
        c +=  '\t*/\n'
        if clear_flags_mask != 0:
            c += '\treg[1] &= (~%s); /* clear flags */\n' % (hex(clear_flags_mask),)
        if set_flags_mask != 0:
            c += '\treg[1] |= %s; /* set flags */\n' % (hex(set_flags_mask),)
        c += '}\n'
        c += '\n'


        print(c)





