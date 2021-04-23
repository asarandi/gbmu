#include "gb.h"
#include "hardware.h"

int arg_parse(int ac, char **av) {
    int c, ret = 1;

    while ((c = getopt(ac, av, "t:")) != -1) {
        switch (c) {
        case 't':
            ret &= testing_setup(optarg);
            break;

        case '?':
        default:
            return 0;
        }
    }

    return ret;
}

uint8_t gb_mem[0x10000];
t_state gb_state;
t_state *state = &gb_state;
t_r16 registers;
t_r16 *r16 = &registers;

static int cleanup();

int main(int ac, char **av) {
    static int fd, i, op, ret, instr_cycles;
    void (*f)(void *, t_state *, uint8_t *);
    struct stat stat_buf;

    if (!arg_parse(ac, av)) {
        return 1;
    }

    state->rom_file = av[ac - 1];

    if ((fd = open(state->rom_file, O_RDONLY)) == -1) {
        (void)fprintf(stderr, "failed to open file\n");
        return 1;
    }

    if (fstat(fd, &stat_buf) != 0) {
        (void)close(fd);
        (void)fprintf(stderr, "fstat() failed\n");
        return 1;
    }

    if ((stat_buf.st_size < 0x8000) ||
            (stat_buf.st_size > 0x800000) ||
            (stat_buf.st_size & 0x7fff)) {
        (void)close(fd);
        (void)fprintf(stderr, "invalid file\n");
        return 1;
    }

    state->gameboy_registers = &registers;
    state->file_contents = malloc(stat_buf.st_size);
    state->file_size = stat_buf.st_size;
    ret = read(fd, state->file_contents, stat_buf.st_size);
    (void)close(fd);

    if (ret != stat_buf.st_size) {
        (void)fprintf(stderr, "read() failed\n");
        (void)free(state->file_contents);
        return 1;
    }

    (void)memcpy(gb_mem, state->file_contents, 0x8000);
    set_initial_register_values();
    cartridge_init();

    if (!state->testing) {
        struct fn {
            int(*f)();
            char *n;
        } fn[] = {
            {&savefile_read, "savefile_read"},
            {&video_open, "video_open"},
            {&audio_open, "audio_open"},
            {&input_open, "input_open"},
        };

        for (i = 0; i < 4; i++) {
            if (!fn[i].f()) {
                (void)perror(fn[i].n);
                return cleanup();
            }
        }
    }

    state->div_cycles = 0xac00;

    while (!state->done) {
        (void)timers_update(gb_mem, &gb_state, 4);
        (void)dma_update((void *)&gb_mem, state, r16);

        if (lcd_update(gb_mem, &gb_state, 4)) {
            if (!state->testing) {
                (void)video_write(state->screen_buf, 160 * 144);
                (void)input_read();
            }
        }

        if (sound_update(gb_mem, &gb_state, 4)) {
            if (!state->testing) {
                (void)audio_write(state->sound_buf, SOUND_BUF_SIZE);
            }
        }

        if (state->testing) {
            (void)state->testing_run_hook();
        }

        (void)interrupts_update(gb_mem, state, &registers);
        state->cycles += 4;

        if ((state->halt) || (state->interrupt_cycles)) {
            continue ;
        }

        if (!instr_cycles) {
            instr_cycles = get_num_cycles(&registers, gb_mem);
        }

        if (instr_cycles) {
            instr_cycles -= 4;
        }

        if (!instr_cycles) {
            if (state->halt_bug) {
                static uint16_t addr, a16, b16;

                if (!addr) {
                    addr = r16->PC;
                    a16 = *(uint16_t *)&gb_mem[addr];
                    b16 = *(uint16_t *)&gb_mem[addr + 1];
                    *(uint16_t *)&gb_mem[addr + 1] = a16;
                } else {
                    *(uint16_t *)&gb_mem[addr] = a16;
                    *(uint16_t *)&gb_mem[addr + 1] = b16;
                    addr = state->halt_bug = 0;
                }
            }

            op = read_u8(r16->PC);
            f = ops0[op];

            if (op == 0xcb) {
                f = ops1[read_u8(r16->PC + 1)];
            }

            //(void)dump_registers(gb_mem, state, r16);
            (void)f((void *)&registers, (void *)&gb_state, gb_mem);
        }
    }

    return cleanup();
}

static int cleanup() {
    if (!state->testing) {
        if (!input_close()) {
            (void)fprintf(stderr, "input_close() failed\n");
        }

        if (!audio_close()) {
            (void)fprintf(stderr, "audio_close() failed\n");
        }

        if (!video_close()) {
            (void)fprintf(stderr, "video_close() failed\n");
        }

        if (!savefile_write()) {
            (void)fprintf(stderr, "savefile_write() failed\n");
        }
    }

    if (state->file_contents) {
        (void)free(state->file_contents);
        state->file_contents = NULL;
    }

    return state->exit_code;
}
