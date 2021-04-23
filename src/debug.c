#include "gb.h"
#include "hardware.h"

static void dump_io(uint8_t *mem, t_state *state, t_r16 *r16) {
    struct io_register {
        char      *name;
        uint16_t   addr;
        uint8_t    mask;
    } io_registers[] = {
        {"IF",     0xFF0F, 0b11100000},
        {"IE",     0xFFFF, 0b00000000},
        {"LCDC",   0xFF40, 0b00000000},
        {"STAT",   0xFF41, 0b10000000},
        {"SCY",    0xFF42, 0b00000000},
        {"SCX",    0xFF43, 0b00000000},
        {"LY",     0xFF44, 0b00000000},
        {"LYC",    0xFF45, 0b00000000},
        {"DMA",    0xFF46, 0b00000000},
        {"BGP",    0xFF47, 0b00000000},
        {"OBP0",   0xFF48, 0b00000000},
        {"OBP1",   0xFF49, 0b00000000},
        {"WY",     0xFF4A, 0b00000000},
        {"WX",     0xFF4B, 0b00000000},
    };
    (void)state;
    (void)r16;
    int i, num_io_regs = sizeof(io_registers)/sizeof(struct io_register);

    for (i = 0; i < num_io_regs; i++) {
        printf("%s%.4s %02x",
               i > 0 ? " " : "",
               io_registers[i].name,
               mem[io_registers[i].addr]
              );
    }
}

static void dump_instr(uint8_t *mem, t_state *state, t_r16 *r16) {
    char buf_instr_name[16], *op_name;
    char buf_instr_bytes[16], byte_len;
    (void)mem;
    (void)state;
    uint8_t idx = read_u8(r16->PC);

    if (idx == 0xcb) {
        idx = read_u8(r16->PC + 1);
        byte_len = byte_lens1[idx];
        op_name = op_names1[idx];
        sprintf(buf_instr_name, "%s", op_name);
    } else {
        byte_len = byte_lens0[idx];
        op_name = op_names0[idx];

        if (strstr(op_name, "%02")) {
            sprintf(buf_instr_name, op_name, read_u8(r16->PC + 1));
        } else if (strstr(op_name, "%04")) {
            sprintf(buf_instr_name, op_name, read_u16(r16->PC + 1));
        } else {
            sprintf(buf_instr_name, "%s", op_name);
        }
    }

    if (byte_len == 0) {
        sprintf(buf_instr_bytes, "wtf");
    } else if (byte_len == 1) {
        sprintf(buf_instr_bytes, "%02x", read_u8(r16->PC));
    } else if (byte_len == 2) {
        sprintf(buf_instr_bytes, "%02x%02x",
                read_u8(r16->PC),
                read_u8(r16->PC + 1)
               );
    } else if (byte_len == 3) {
        sprintf(buf_instr_bytes, "%02x%02x%02x",
                read_u8(r16->PC),
                read_u8(r16->PC + 1),
                read_u8(r16->PC + 2)
               );
    }

    printf("pc:%04x sp:%04x   %-8s  %-16s", r16->PC, r16->SP, buf_instr_bytes,
           buf_instr_name);
}

int screenshot(t_state *state, char *filename) {
    uint32_t palette[] = {0xffffff, 0xaaaaaa, 0x555555, 0x000000};
    uint8_t buf[144 * 160 * 4];
    int i, j, k, fd;

    for (i = 0; i < 144; i++) {
        for (j = 0; j < 160; j++) {
            k = ((144 - 1 - i) * 160 + j) * 4;
            *(uint32_t *)&buf[k] = palette[state->screen_buf[i * 160 + j]];
        }
    }

    uint8_t bmphdr[] = {
        0x42, 0x4d, 0x8a, 0x68, 0x01, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x8a, 0x00, 0x00, 0x00, 0x7c, 0x00,
        0x00, 0x00, 0xa0, 0x00, 0x00, 0x00, 0x90, 0x00,
        0x00, 0x00, 0x01, 0x00, 0x20, 0x00, 0x03, 0x00,
        0x00, 0x00, 0x00, 0x68, 0x01, 0x00, 0x13, 0x0b,
        0x00, 0x00, 0x13, 0x0b, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x47,
        0x52, 0x73, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00
    };
    fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);

    if (fd < 1) {
        perror(__func__);
        return 0;
    }

    (void)write(fd, bmphdr, sizeof(bmphdr));
    (void)write(fd, buf, sizeof(buf));
    (void)close(fd);
    return 1;
}

void debug(uint8_t *mem, t_state *state, t_r16 *r16) {
    //dump_instr(mem, state, r16);
    //printf("    ");
    //dump_io(mem, state, r16);
    //printf("\n");
    //fflush(stdout);
    (void)mem;
    (void)r16;
    static int once;

    if ((!once) && (state->cycles > (15 * 60 * 70224)) && (state->video_render)) {
        once = 1;
        (void)printf("screenshot = %d\n",
                     screenshot(state, "screenshot.bmp"));
        (void)fflush(stdout);
    }
}
