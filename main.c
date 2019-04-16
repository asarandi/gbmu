#include "gb.h"

void    timers_update(uint8_t *gb_mem, t_state *state, int current_cycles)
{
    static  uint64_t    cycles;
    static  uint8_t     div;
    static  uint8_t     freq = 10;

    cycles += current_cycles;
    cycles %= 4194304;

    if (gb_mem[0xff04] != div) {
        div = 0;
        gb_mem[0xff04] = 0;
    }
    else {
        div = (cycles >> 8) & 0xff;
        gb_mem[0xff04] = div;
    }


    if ((gb_mem[0xff07] & 0x04) == 0) { //timer disabled
        cycles = 0;
        return ;
    }

    switch (gb_mem[0xff07] & 0x03) {
        case 0: {
            if (freq != 10) cycles = 0;
            freq = 10;
            break ;
        }
        case 1: {
            if (freq != 4) cycles = 0;
            freq = 4;
            break ;
        }
        case 2: {
            if (freq != 6) cycles = 0;
            freq = 6;
            break ;
        }
        case 3: {
            if (freq != 8) cycles = 0;
            freq = 8;
            break ;
        }
    }

    gb_mem[0xff05] = (cycles >> freq) & 0xff;

    if ((gb_mem[0xff05] == 0) && (cycles != 0)) {
        gb_mem[0xff05] = gb_mem[0xff06];
        gb_mem[0xff0f] |= 4; 
    }
}

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

    state->gameboy_memory = gb_mem;
    state->gameboy_registers = registers;

    if (read(fd, gb_mem, 0x8000) != 0x8000) {
        printf("read() failed\n");
    }
    close(fd);

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

    r16->AF = 0x1180;
    r16->BC = 0x0000;
    r16->DE = 0x0008;
    r16->HL = 0x007c;

    r16->AF = 0x0000;
    r16->BC = 0x0000;
    r16->DE = 0x0000;
    r16->HL = 0x0000;
    r16->SP = 0x0000;
    r16->PC = 0x0000;

#endif    
    pthread_create(&thread, NULL, &gui, (void *)gb_state);

    uint8_t dma = mem[0xff46];
    bool debug = false;
    while (true)
    {
        if (mem[0xff46] != dma) {
            printf("dma current = %02x, new = %02x\n", dma, mem[0xff46]);
            dma = mem[0xff46];
            uint16_t dm = dma << 8;
            for (uint8_t dma_i=0; dma_i < 0xa0; dma_i++) {
                mem[0xfe00+dma_i] = mem[dm + dma_i];
            }
            dump_ram(mem);
        }

        interrupts_update(gb_mem, state, registers);
        lcd_update(gb_mem, gb_state, op_cycles);
        timers_update(gb_mem, gb_state, op_cycles);

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
        if (r16->PC == 0xe0) debug = true;
        if (debug) {
            dump_registers(registers, state, mem);
            uint8_t tmp; read(0, &tmp, 1);
        }
    }
    free(gb_mem);
    free(gb_state);
    free(registers);

    return 0;
}
