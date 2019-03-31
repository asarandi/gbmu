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
            'typedef struct s_r16 {',
            '    uint16_t    AF; ',
            '    uint16_t    BC; ',
            '    uint16_t    DE; ',
            '    uint16_t    HL; ',
            '    uint16_t    SP; ',
            '    uint16_t    PC; ',
            '} t_r16;            ',
            '                    ',
            'typedef struct s_r8 {',
            '    uint8_t     A;  ',
            '    uint8_t     F;  ',
            '    uint8_t     B;  ',
            '    uint8_t     C;  ',
            '    uint8_t     D;  ',
            '    uint8_t     E;  ',
            '    uint8_t     H;  ',
            '    uint8_t     L;  ',
            '    uint16_t    SP; ',
            '    uint16_t    PC; ',
            '} t_r8;             ',
            '',            
            '#define set_z      (r8->F |= 0x80)',
            '#define set_n      (r8->F |= 0x40)',
            '#define set_h      (r8->F |= 0x20)',
            '#define set_c      (r8->F |= 0x10)',
            '',
            '#define clear_z    (r8->F &= (~0x80))',
            '#define clear_n    (r8->F &= (~0x40))',
            '#define clear_h    (r8->F &= (~0x20))',
            '#define clear_c    (r8->F &= (~0x10))',
            '',



            
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

        set_z_flag_if_a_is_zero     = '\tr8->A  ==   0   ? set_z : clear_z;\n'
        set_h_flag_if_half_carry    = '\tr8->A  &    8   ? set_h : clear_h;\n'
        set_c_flag_if_full_carry    = '\tr8->A  & 0x80   ? set_c : clear_c;\n'


        if sp[0] == 'LD':   #loads
            ops = sp[1].split(',')
            if ops[0] in addr:
                if ops[1] == 'd8':  # 8-bit loads
                    code = '\tr8->%s = mem[(r8->PC)+1]; /* code LD imm */\n' % (ops[0],)
                elif ops[1] in addr:
                    code = '\tr8->%s = r8->%s; /* code LD reg */\n' % (ops[0], ops[1])
                else:                    
                    code = '/* FIXME: code LD REG,d8*/\n'
                    
        elif sp[0] == 'AND':                
            if sp[1] in addr:
                code  = '\tr8->A &= r8->%s;    /* code AND */\n' % (sp[1], )
            elif sp[1] == 'd8':
                code  = '\tr8->A &= mem[r16->PC+1]; /* code AND */\n'
            elif sp[1] == '(HL)':
                code  = '\tr8->A &= mem[r16->HL]; /* code AND A,(HL)*/\n'
            else:
                code = '/* FIXME: code AND */\n'
            code += set_z_flag_if_a_is_zero

        elif sp[0] == 'OR':                
            if sp[1] in addr:
                code  = '\tr8->A |= r8->%s;    /* code OR */\n' % (sp[1], )
            elif sp[1] == 'd8':
                code  = '\tr8->A |= mem[r16->PC+1]; /* code OR */\n'
            elif sp[1] == '(HL)':
                code  = '\tr8->A |= mem[r16->HL]; /* code OR A,(HL)*/\n'
            else:
                code = '/* FIXME: code OR */\n'
            code += set_z_flag_if_a_is_zero


        elif sp[0] == 'XOR':                
            if sp[1] in addr:
                code  = '\tr8->A ^= r8->%s;    /* code XOR */\n' % (sp[1], )
            elif sp[1] == 'd8':
                code  = '\tr8->A ^= mem[r16->PC+1]; /* code XOR */\n'
            elif sp[1] == '(HL)':
                code  = '\tr8->A ^= mem[r16->HL]; /* code XOR A,(HL)*/\n'
            else:
                code = '/* FIXME: code XOR */\n'
            code += set_z_flag_if_a_is_zero

    
        c  = 'void op_%s(void *reg, uint8_t *mem)\n' % (opcode,)
        c += '{\n'
        c += '\t/*\n'
        c += '\t\t    category: %s\n' % (bgcolor[bgc],)
        c += '\t\t instruction: %s\n' % (text,)
        c += '\t\t   num bytes: %s\n' % (byte_len,)
        c += '\t\t      cycles: %s\n' % (cycles,)
        c += '\t\t       flags: %s\n' % (flags,)
        c +=  '\t*/\n'
        c += '\t\tt_r8 *r8 = reg;\n'
        c += '\t\tt_r16 *r16 = reg;\n'

        if code:
            c += code

        if clear_flags_mask != 0:
            c += '\tr8->F &= (~%s); /* clear flags */\n' % (hex(clear_flags_mask),)
        if set_flags_mask != 0:
            c += '\tr8->F |= %s; /* set flags */\n' % (hex(set_flags_mask),)

        c += '}\n'
        c += '\n'


        print(c)





