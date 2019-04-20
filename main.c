#include "gb.h"
#include <ncurses.h>

void    *tui_input()
{
    int rv, flags;   
    int key_delays[8] = {0};
    int ncurses_keys[8] = {KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT, 'n', 'm', 'z', 'x'};    
    char key;

    flags = fcntl(STDIN_FILENO, F_GETFL, 0);

    while (true)
    {
        key = 0;
        fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
        read(0, &key, 1);
        fcntl(STDIN_FILENO, F_SETFL, flags);

        for (int i=0; i<8; i++) {
            if (key == ncurses_keys[i]) {
                state->buttons[i] = 1;
                key_delays[i] = 0;
            }
            key_delays[i]++;
            if (key_delays[i] > 20) {   //delay duration
                key_delays[i] = 0;
                state->buttons[i] = 0;
            }
        }
        if (key != 0) continue ;
        usleep(1000);
    }
    return NULL;
}

void    tui_input_print()
{
    addch('\n');
    for (int i=0; i<8; i++) {
        if (state->buttons[i] == 1)
            addch('1');
        else
            addch('0');
    }    
}

void    *tui_show(void *arg)
{
    char    *pixels = "o*. ";
    char    buf[144*161];
    int     key;

    (void)arg;
    while (true) {
        for (int y=0;y<144;y++) {
            for (int x=0;x<161;x++) {
                int idx = state->screen_buf[y*160+x];
                buf[y*161+x] = pixels[idx];
                if (x == 160) buf[y*161+x] = '\n';                   
            }
        }
        clear();
        addnstr(buf,144*161);
        tui_input_print();
        refresh();
        usleep(1000000 / 30);
    }
    return NULL;
}


void    tui_init()
{
    int flags;

    initscr();
    raw();
//    cbreak();
    keypad(stdscr, TRUE);
    noecho();
}
 
void    timers_update(uint8_t *gb_mem, t_state *state, int current_cycles)
{
    static  uint16_t    div;
    static  uint64_t    cycles;
    static  uint64_t    freq = 1024;

    div = (gb_mem[0xff04] << 8) | gb_mem[0xff03];
    div += current_cycles;
    gb_mem[0xff04] = div >> 8;
    gb_mem[0xff03] = div & 0xff;

    if ((gb_mem[0xff07] & 0x04) == 0) { //timer disabled
        cycles = 0;
        return ;
    }

    switch (gb_mem[0xff07] & 0x03) {
        case 0: {
            if (freq != 1024) cycles = 0;
            freq = 1024;
            break ;
        }
        case 1: {
            if (freq != 16) cycles = 0;
            freq = 16;
            break ;
        }
        case 2: {
            if (freq != 64) cycles = 0;
            freq = 64;
            break ;
        }
        case 3: {
            if (freq != 256) cycles = 0;
            freq = 256;
            break ;
        }
    }


    if (gb_mem[0xff05] == 0) {
        gb_mem[0xff05] = gb_mem[0xff06];
        gb_mem[0xff0f] |= 4; 
    }

    cycles += current_cycles;
    if (cycles > freq) {
        cycles %= freq;
        gb_mem[0xff05]++;
    }

}


void delay()
{
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = 1000000000L / 30;

    struct timespec tz;
    tz.tv_sec = 0;
    tz.tv_nsec = 1000000000L / 30;
    (void)nanosleep(&ts, &tz);
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
    (void)tui_init();    
    pthread_create(&thread, NULL, &tui_show, NULL);   
    pthread_create(&thread, NULL, &tui_input, NULL);
    state->debug = false;
    while (true)
    {

        timers_update(gb_mem, gb_state, op_cycles);
        lcd_update(gb_mem, gb_state, op_cycles);
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
            printf("state->cycles = %llu\n", state->cycles);
            dump_registers(registers, state, mem);
            uint8_t tmp; read(0, &tmp, 1);
            if (tmp == 'c') {
                state->cycles = 0;
                state->debug = false;
            }
        }
    }
    free(gb_mem);
    free(gb_state);
    free(registers);

    return 0;
}
