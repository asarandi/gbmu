#include "gb.h"

void delay()
{
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = 50000000;

    struct timespec tz;
    tz.tv_sec = 0;
    tz.tv_nsec = 50000000;
    (void)nanosleep(&ts, &tz);
}

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
    void (*f)(void *, t_state *, uint8_t *);
    int         op_cycles;
    pthread_t   thread;

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

/*    
    if (stat_buf.st_size != 0x8000) {
        close(fd);
        printf("unsupported file format\n");
        return 1;
    }
*/
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

    /* default register values as per mgba debugger */

    r16->AF = 0x0000;
    r16->BC = 0x0000;
    r16->DE = 0x0000;
    r16->HL = 0x0000;
    r16->SP = 0x0000;
    r16->PC = 0x0000;

    uint8_t game100[0x100];

    (void)memcpy(game100, mem, 0x100);

    (void)memcpy(mem, DMG_ROM_bin, 0x100);
    pthread_create(&thread, NULL, &gui, (void *)gb_state);
    while (true)
    {
        op0 = mem[r16->PC];
        op1 = mem[r16->PC + 1];
        f = ops0[op0];
        if (op0 == 0xcb)
            f = ops1[op1];


        if (r16->PC == 0x100)
            memcpy(mem, game100, 0x100);
//        if (r16->PC >= 0x100)
//            dump_registers(registers, gb_state, gb_mem);
        op_cycles = get_num_cycles(registers, gb_mem);
//        printf("total cycles: %08lu, this op cycles: %02d\n", state->cycles, op_cycles);

        lcd_update(gb_mem, gb_state, op_cycles);
        f(registers, gb_state, gb_mem);

        state->cycles += op_cycles;

/*

        if (state->cycles % 456 == 0) {
            mem[0xff44] = 0x90;
        }

        if (r16->PC == 0x8c) {
            dump_background2(gb_mem, gb_state);           
*/

//            dump_background(gb_mem);
//            printf("%04X\n", mem[0xff40]);            
//            fflush(NULL);
//            delay();

//            dump_background(gb_mem);
//            break ;


//        if (r16->PC == 0x68){
//            dump_ram(mem);
//             break ; }
    }

//    dump_background2(gb_mem);

    free(gb_mem);
    free(gb_state);
    free(registers);

    return 0;
}
