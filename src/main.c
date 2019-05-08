#include "gb.h"

int main(int ac, char **av)
{

    int         fd;
    void        *registers;
    t_r16       *r16;
    void        *gb_state;
    void        *gb_mem;    
    uint8_t     *mem;
    uint8_t     op0;
    uint8_t     op1;
    struct stat stat_buf;
    void (*f)(void *, t_state *, uint8_t *);
    int         op_cycles = 0;
    uint64_t    frame_counter = 0;        

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

    if (!gui_init())
        state->done = true;
    (void)apu_init();

    state->bootrom_enabled = BOOTROM_ENABLED;
    gameboy_init();

    uint16_t    pc_history[100] = {0};
    int         pc_idx = 0;
    bool        show_pc_history = false;


    while (!state->done)
    {
        timers_update(gb_mem, gb_state, op_cycles);
        lcd_update(gb_mem, gb_state, op_cycles);
        apu_update(gb_mem, gb_state, op_cycles);
        interrupts_update(gb_mem, state, registers);

        op0 = mem[r16->PC];
        op1 = mem[r16->PC + 1];
        f = ops0[op0];
        if (op0 == 0xcb)
            f = ops1[op1];

        if (r16->PC == 0x100 && state->bootrom_enabled) {
            (void)memcpy(state->gameboy_memory, state->file_contents, 0x100);
            state->bootrom_enabled = false;
        }

//        if (r16->PC == 0x03ca) { state->debug = true; }
        if (state->debug)
        {
            printf("state->cycles = %lu\n", state->cycles);
            dump_registers(registers, state, mem);
            uint8_t tmp; read(0, &tmp, 1);
            if (tmp == 'c') {
                state->cycles = 0;
                state->debug = false;
            }
        }
        pc_history[pc_idx++] = r16->PC;
        pc_idx %= 100;

        
        op_cycles = 4;
        if (state->halt == false) {
            f(registers, gb_state, gb_mem);
            op_cycles = get_num_cycles(registers, gb_mem);
        }
        state->cycles += op_cycles;
        gb_throttle();

    }
    if (show_pc_history) {
        for (int i=pc_idx; i<100; i++) { printf("PC %02d: %04x\n", i, pc_history[i]); };
        for (int i=0; i<pc_idx; i++) { printf("PC %02d: %04x\n", i, pc_history[i]); };
    }

    apu_cleanup();
    gui_cleanup();
    free(gb_mem);
    free(gb_state);
    free(registers);

    return 0;
}
