#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "gb.h"

int main(int ac, char **av)
{

    void    *registers = malloc(sizeof(t_r8));
    (void)memset(registers, 0, sizeof(t_r8));
    t_r16   *r16 = registers;
    t_r8    *r8 = registers;

    void    *gb_state = malloc(sizeof(t_state));
    (void)memset(gb_state, 0, sizeof(t_state));    
    t_state *state = gb_state;

    void    *game_space = malloc(0x10000);
    (void)memset(game_space, 0, 0x10000);
    uint8_t *mem = game_space;






    free(game_space);
    free(gb_state);
    free(registers);

    return 0;
}
