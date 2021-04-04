#include "gb.h"

bool arg_parse(int ac, char **av) {
    int c;

    while ((c = getopt(ac, av, "t")) != -1) {
        switch (c) {
        case 't':
            state->testing = 1;
            state->test_timeout = 15;
            break;

        case '?':
        default:
            printf("failed to parse options");
            return false;
        }
    }

    return true;
}

uint8_t gb_mem[0x10000];
t_state gb_state;
t_state *state = &gb_state;
t_r16 registers;
t_r16 *r16 = &registers;

static int cleanup();

int main(int ac, char **av) {
    static int fd, i, op, instr_cycles, op_cycles = 4;
    void (*f)(void *, t_state *, uint8_t *);
    struct stat stat_buf;

    if (!arg_parse(ac, av)) {
        return 1;
    }

    state->rom_file = av[ac - 1];

    if ((fd = open(state->rom_file, O_RDONLY)) == -1) {
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

    state->gameboy_registers = &registers;
    state->file_contents = malloc(stat_buf.st_size);
    state->file_size = stat_buf.st_size;

    if (read(fd, state->file_contents, stat_buf.st_size) != stat_buf.st_size) {
        printf("read() failed\n");
    }

    close(fd);
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
                perror(fn[i].n);
                return cleanup();
            }
        }
    }

    while (!state->done) {
        timers_update(gb_mem, &gb_state, op_cycles);

        if (lcd_update(gb_mem, &gb_state, op_cycles)) {
            if (!state->testing) {
                video_write(state->screen_buf, 160 * 144);
                input_read();
            }
        }

        if (sound_update(gb_mem, &gb_state, op_cycles)) {
            if (!state->testing) {
                audio_write(state->sound_buf, SOUND_BUF_SIZE);
            }
        }

        interrupts_update(gb_mem, state, &registers);
        op = read_u8(r16->PC);
        f = ops0[op];

        if (op == 0xcb) {
            f = ops1[read_u8(r16->PC + 1)];
        }

        if ((!state->halt) && (!state->interrupt_cycles)) {
            if (!instr_cycles) {
                instr_cycles = get_num_cycles(&registers, gb_mem);
            }

            if (instr_cycles) {
                instr_cycles -= 4;
            }

            if (!instr_cycles) {
                f((void *)&registers, (void *)&gb_state, gb_mem);
            }
        }

        op_cycles = 4;
        state->cycles += op_cycles;
    }

    return cleanup();
}

static int cleanup() {
    if (!state->testing) {
        if (!input_close()) {
            printf("input_close() failed\n");
        }

        if (!audio_close()) {
            printf("audio_close() failed\n");
        }

        if (!video_close()) {
            printf("video_close() failed\n");
        }

        if (!savefile_write()) {
            printf("savefile_write() failed\n");
        }
    }

    if (state->file_contents) {
        free(state->file_contents);
        state->file_contents = NULL;
    }

    return 0;
}
