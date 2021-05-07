#include "gb.h"
#include "hardware.h"
#include <arpa/inet.h>

extern unsigned long crc32(unsigned char *buf, int len);
extern unsigned long adler32(unsigned char *buf, int len);

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
        {"LY",     0xFF44, 0b00000000},
        {"LYC",    0xFF45, 0b00000000},
        {"DMA",    0xFF46, 0b00000000},
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

    (void)printf(" ime %02x dma %02x cycles %u", state->ime, state->is_dma,
                 state->cycles);
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
    uint8_t buf[5972] = {0};
    const uint8_t png_head[] = {
        0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, // png
        0x00, 0x00, 0x00, 0x0d, 0x49, 0x48, 0x44, 0x52, // ihdr size 13
        0x00, 0x00, 0x00, 0xa0, 0x00, 0x00, 0x00, 0x90, // 160, 144
        0x02, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x6e, 0x27, // 2 bit depth, crc
        0xfd, 0x00, 0x00, 0x17, 0x1b, 0x49, 0x44, 0x41, // idat size 5915
        0x54, 0x58, 0x09, 0x01, 0x10, 0x17, 0xef, 0xe8  // zlib hdr
    };
    const uint8_t png_tail[] = {
        0xaa, 0xaa, 0xaa, 0xaa, 0xbb, 0xbb, 0xbb, 0xbb, // crc aa=zlib, bb=idat
        0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, // iend size 0
        0xae, 0x42, 0x60, 0x82                          // iend crc
    };
    (void)memcpy(buf, png_head, sizeof(png_head));
    (void)memcpy(buf + 5952, png_tail, sizeof(png_tail));
    int i, o = 48;

    for (i = 0; i < 144 * 160;) {
        if (!(i % 160)) {
            buf[o++] = 0;
        }

        buf[o] = (3 - state->screen_buf[i++]) << 6;
        buf[o] |= (3 - state->screen_buf[i++]) << 4;
        buf[o] |= (3 - state->screen_buf[i++]) << 2;
        buf[o++] |= 3 - state->screen_buf[i++];
    }

    *(unsigned long *)(buf + o) = htonl(adler32(buf + 48, 5904)); // zlib
    *(unsigned long *)(buf + o + 4) = htonl(crc32(buf + 37, 5919)); // idat
    int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);

    if (fd < 1) {
        perror(__func__);
        return 0;
    }

    (void)write(fd, buf, sizeof(buf));
    (void)close(fd);
    return 1;
}

void debug(uint8_t *mem, t_state *state, t_r16 *r16) {
    //(void)mem;
    //(void)state;
    //(void)r16;
    //
    if (state->debug) {
        dump_instr(mem, state, r16);
        printf("    ");
        dump_io(mem, state, r16);
        printf("\n");
        fflush(stdout);
    }
}
