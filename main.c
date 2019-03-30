#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>

void    clear_flags_mask(uint8_t *reg, uint8_t mask)    
{
    reg[1] = reg[1] & (~mask);
}

void    set_flags_mask(uint8_t *reg, uint8_t mask)
{
    reg[1] = reg[1] | mask;
}

int main(int ac, char **av)
{
    uint8_t     a;
    uint8_t     f;
    uint8_t     b;
    uint8_t     c;
    uint8_t     d;
    uint8_t     e;
    uint8_t     h;
    uint8_t     l;
    uint16_t    sp;
    uint16_t    pc;

    return 0;
}
