#include "gb.h"

int main(int ac, char **av)
{

    int         fd;
    void        *registers;
    t_r16       *r16;
    t_r8        *r8;
    void        *gb_state;
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

    
    if ((stat_buf.st_size < 0x8000) || 
            (stat_buf.st_size > 0x800000) || 
            (stat_buf.st_size & 0x7fff)) {
        close(fd);
        printf("invalid file\n");
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

    state->gameboy_memory = gb_mem;
    state->gameboy_registers = registers;
    state->file_contents = malloc(stat_buf.st_size);

    if (read(fd, state->file_contents, stat_buf.st_size) != stat_buf.st_size) {
        printf("read() failed\n");
    }
    close(fd);
    (void)memcpy(state->gameboy_memory, state->file_contents, 0x8000);

#define dmg_rom 1

#ifdef dmg_rom

    r16->AF = 0x0000;
    r16->BC = 0x0000;
    r16->DE = 0x0000;
    r16->HL = 0x0000;
    r16->SP = 0x0000;
    r16->PC = 0x0000;

    uint8_t game100[0x100];
    (void)memcpy(game100, mem, 0x100);
    (void)memcpy(mem, DMG_ROM_bin, 0x100);

#else

    r16->AF = 0x01B0;
    r16->BC = 0x0013;
    r16->DE = 0x00D8;
    r16->HL = 0x014D;
    r16->SP = 0xFFFE;
    r16->PC = 0x0100;

#endif

/*
    (void)tui_init();    
    pthread_create(&thread, NULL, &tui_show, NULL);   
    pthread_create(&thread, NULL, &tui_input, NULL);
    state->debug = false;
*/  

    if (!gui_init())
        state->done = true;

    uint64_t    frame_counter = 0;        
    while (!state->done)
    {

        timers_update(gb_mem, gb_state, op_cycles);
        lcd_update(gb_mem, gb_state, op_cycles);

        if (state->cycles / 70224 != frame_counter) {
            frame_counter = state->cycles / 70224;
            gui_update();
        }

        interrupts_update(gb_mem, state, registers);

        op0 = mem[r16->PC];
        op1 = mem[r16->PC + 1];
        f = ops0[op0];
        if (op0 == 0xcb)
            f = ops1[op1];
#ifdef  dmg_rom
        if (r16->PC == 0x100)
            memcpy(mem, game100, 0x100);
#endif
        op_cycles = get_num_cycles(registers, gb_mem);
        if (state->halt == false) {
            f(registers, gb_state, gb_mem);
        } else {
            op_cycles = 4;
        }
        state->cycles += op_cycles;

//        if (state->cycles > 24296700) debug = true;
//        if (r16->PC == 0x2b79) { debug = true; }
//        if (r16->PC == 0x401d) { debug = true; }
//        if (r16->PC == 0x03ca) { state->debug = true; }
        if (state->debug && 1 == 2)
        {
            printf("state->cycles = %lu\n", state->cycles);
            dump_registers(registers, state, mem);
            uint8_t tmp; read(0, &tmp, 1);
            if (tmp == 'c') {
                state->cycles = 0;
                state->debug = false;
            }
        }
    }
    gui_cleanup();
    free(gb_mem);
    free(gb_state);
    free(registers);

    return 0;
}
