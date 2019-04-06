#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "gb.h"


extern void (*ops0[])(void *, t_state *, uint8_t *);
extern void (*ops1[])(void *, t_state *, uint8_t *);

int main(int ac, char **av)
{

    int         fd;
    void        *registers;
    t_r16       *r16;
    t_r8        *r8;
    void        *gb_state;
    t_state     *state;
    void        *gb_mem;    
    uint8_t     *mem;

    uint8_t     op0;
    uint8_t     op1;

    struct stat stat_buf;


    if (ac != 2)
        return 1;

    if ((fd = open(av[1], O_RDONLY)) == -1) {
        printf("failed to open file\n");
        return 1;
    }

    if (fstat(fd, &stat_buf) != 0) {
        close(fd);
        printf("fstat() failed\n");
        return 1;
    }

    if (stat_buf.st_size != 0x8000) {
        close(fd);
        printf("unsupported file format\n");
        return 1;
    }

    registers = malloc(sizeof(t_r8));
    (void)memset(registers, 0, sizeof(t_r8));
    r16 = registers;
    r8 = registers;

    gb_state = malloc(sizeof(t_state));
    (void)memset(gb_state, 0, sizeof(t_state));    
    state = gb_state;

    gb_mem = malloc(0x10000);
    (void)memset(gb_mem, 0, 0x10000);
    mem = gb_mem;


    if (read(fd, gb_mem, 0x8000) != 0x8000) {
        printf("read() failed\n");
    }
    close(fd);

    r16->PC = 0x100;

    void (*f)(void *, t_state *, uint8_t *);

    while (true)
    {
        op0 = mem[r16->PC];
        op1 = mem[r16->PC + 1];
        f = ops0[op0];
        if (op0 == 0xcb)
            f = ops1[op1];
        f(registers, gb_state, gb_mem);

    }


    free(gb_mem);
    free(gb_state);
    free(registers);

    return 0;
}
