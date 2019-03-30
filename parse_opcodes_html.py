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

cells = soup.find_all('td')
for i in range(17*2):
    for j in range(17):
        if i % 17 == 0: continue
        if j % 17 == 0: continue
                
        opcode = '%02x' % (((i%17)-1) *16 +j-1,)
        if i > 17:
            opcode = '%04x' % (0xcb00 + ((i%17)-1) *16 +j-1,)

        data = cells[i*17+j].contents

        text = byte_len = cycles = flags = 'FIXME: undefined'   #vim highlight

        if len(data) > 1:
            text = data[0]
            byte_len = data[2].split()[0]
            cycles = data[2].split()[1]
            flags = data[4]
    
        c_code = [
                    'void op_%s(void *reg, void *data)' % (opcode,),
                    '{',
                    '\t/*',
                    '\t\t instruction: %s ' % (text,),
                    '\t\t   num bytes: %s ' % (byte_len,),
                    '\t\t      cycles: %s ' % (cycles,),
                    '\t\t       flags: %s ' % (flags,),
                    '\t*/',
                    '}'
                ]


        print('\n'.join(c_code)+'\n')





