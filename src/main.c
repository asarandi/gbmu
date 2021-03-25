#include "gb.h"
#include <arpa/inet.h>
#include <getopt.h>

static char *default_network_address = "0.0.0.0";
static int default_network_port = 4242;

bool is_valid_ip(char *s) {
    struct sockaddr_in sa;
    return inet_pton(AF_INET, s, &(sa.sin_addr)) == 1;
}

bool arg_parse(int ac, char **av) {
    int c;

    state->network_address = &default_network_address[0];
    state->network_port = default_network_port;

    while ((c = getopt(ac, av, "c:s:p:td:")) != -1) {
        switch (c) {
        case 't':
            state->testing = 1;
            if (!state->test_timeout)
                state->test_timeout = 15;
            break;
        case 'd':
            state->test_timeout = atoi(optarg);
            break;
        case 'c':
        case 's':
            state->is_client = c == 'c';
            state->is_server = c == 's';
            if (is_valid_ip(optarg))
                state->network_address = optarg;
            else
                optind--;
            break;
        case 'p':
            state->network_port = atoi(optarg);
            break;
        case '?':
        default:
            printf("failed to parse options");
            return false;
        }
    }
    if (state->is_client || state->is_server)
        printf("netplay %s: %s:%d\n", state->is_client ? "client" : "server", state->network_address,
               state->network_port);
    return true;
}

uint8_t gb_mem[0x10000];
t_state gb_state;
t_state *state = &gb_state;
t_r16 registers;
t_r16 *r16 = &registers;

int main(int ac, char **av) {
    int fd;
    uint8_t op;
    struct stat stat_buf;
    void (*f)(void *, t_state *, uint8_t *);
    int i, op_cycles = 4;
    uint8_t dbgcmd = 0;
    uint16_t pc_history[100] = {0};
    int pc_idx = 0;
    bool show_pc_history = false;
    static int instr_cycles;

    if (!arg_parse(ac, av))
        return 1;

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

    state->serial_data = 0xff;
    state->gameboy_registers = &registers;
    state->file_contents = malloc(stat_buf.st_size);
    state->file_size = stat_buf.st_size;

    if (read(fd, state->file_contents, stat_buf.st_size) != stat_buf.st_size) {
        printf("read() failed\n");
    }
    close(fd);
    (void)memcpy(gb_mem, state->file_contents, 0x8000);

    if (!state->testing) {
        video_open();
        audio_open();
        input_open();
    }

    state->bootrom_enabled = BOOTROM_ENABLED;
    gameboy_init();
    cartridge_init();
    savefile_read();

    while (!state->done) {
        serial(op_cycles);
        timers_update(gb_mem, &gb_state, op_cycles);
        if (lcd_update(gb_mem, &gb_state, op_cycles)) {
            video_write(state->screen_buf, 160 * 144);
            input_read();
        }
        if (sound_update(gb_mem, &gb_state, op_cycles)) {
            audio_write(state->sound_buf, SOUND_BUF_SIZE);
            av_sync();
        }
        interrupts_update(gb_mem, state, &registers);

        op = read_u8(r16->PC);
        f = ops0[op];
        if (op == 0xcb)
            f = ops1[read_u8(r16->PC + 1)];

        if (r16->PC == 0x100 && state->bootrom_enabled) {
            (void)memcpy(gb_mem, state->file_contents, 0x100);
            state->bootrom_enabled = false;
        }

        if (state->debug) {
            printf("state->cycles = %u\n", state->cycles);
            dump_registers(&registers, state, gb_mem);
            if ((read(0, &dbgcmd, 1) == 1) && (dbgcmd == 'c')) {
                state->cycles = 0;
                state->debug = false;
                dbgcmd = 0;
            }
        }
        pc_history[pc_idx++] = r16->PC;
        pc_idx %= 100;

        if ((!state->halt) && (!state->interrupt_cycles)) {
            if (!instr_cycles)
                instr_cycles = get_num_cycles(&registers, gb_mem);
            if (instr_cycles)
                instr_cycles -= 4;
            if (!instr_cycles)
                f((void *)&registers, (void *)&gb_state, gb_mem);
        }

        op_cycles = 4;
        state->cycles += op_cycles;
    }
    if (show_pc_history) {
        for (i = pc_idx; i < 100; i++) {
            printf("PC %02d: %04x\n", i, pc_history[i]);
        };
        for (i = 0; i < pc_idx; i++) {
            printf("PC %02d: %04x\n", i, pc_history[i]);
        };
    }

    serial_cleanup();
    savefile_write();
    if (!state->testing) {
        input_close();
        audio_close();
        video_close();
    }
    free(state->file_contents);

    return 0;
}
