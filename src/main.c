#include "gb.h"

bool is_argument(int ac, char **av, char *s)
{
    int i;

    for (i = 1; i < ac; i++) {
        if (!strcmp(av[i], s))
            return true ;
    }
    return false;
}

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
    int         i, op_cycles = 4;

    if (ac < 2)
        return 1;

    if ((fd = open(av[ac - 1], O_RDONLY)) == -1) {
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
	state->file_size = stat_buf.st_size;
    state->rom_file = av[ac - 1];

    if (is_argument(ac, av, "--server"))
        state->is_server = true ;
    if (is_argument(ac, av, "--client"))
        state->is_client = true ;

    state->serial_data = 0xff;

    if (read(fd, state->file_contents, stat_buf.st_size) != stat_buf.st_size) {
        printf("read() failed\n");
    }
    close(fd);
    (void)memcpy(state->gameboy_memory, state->file_contents, 0x8000);

    if (!gui_init())
        state->done = true;

    if (!is_argument(ac, av, "--nosound"))
        (void)apu_init();

    state->bootrom_enabled = BOOTROM_ENABLED;
    gameboy_init();
    cartridge_init();

    uint16_t    pc_history[100] = {0};
    int         pc_idx = 0;
    bool        show_pc_history = false;

    savefile_read(av[1]);

    while (!state->done)
    {
        serial(op_cycles);
        timers_update(gb_mem, gb_state, op_cycles);
        lcd_update(gb_mem, gb_state, op_cycles);
        apu_update(gb_mem, gb_state, op_cycles);
        interrupts_update(gb_mem, state, registers);

        op0 = read_u8(r16->PC);
        op1 = read_u8(r16->PC + 1);
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
            printf("state->cycles = %u\n", state->cycles);
            dump_registers(registers, state, mem);
            uint8_t tmp; read(0, &tmp, 1);
            if (tmp == 'c') {
                state->cycles = 0;
                state->debug = false;
            }
        }
        pc_history[pc_idx++] = r16->PC;
        pc_idx %= 100;

        
        static int instr_cycles;
        if ((!state->halt) && (!state->interrupt_cycles)) {
            if (!instr_cycles)
                instr_cycles = get_num_cycles(registers, gb_mem);
            if (instr_cycles)
                instr_cycles -= 4;
            if (!instr_cycles)
                f(registers, gb_state, gb_mem);
        }

        op_cycles = 4;
        state->cycles += op_cycles;
        gb_throttle();

    }
    if (show_pc_history) {
        for (i=pc_idx; i<100; i++) { printf("PC %02d: %04x\n", i, pc_history[i]); };
        for (i=0; i<pc_idx; i++) { printf("PC %02d: %04x\n", i, pc_history[i]); };
    }

    serial_cleanup();
    savefile_write();
    apu_cleanup();
    gui_cleanup();
    free(gb_mem);
    free(gb_state);
    free(registers);

    return 0;
}
