#include "gb.h"
#include "cpu.h"
#include "hardware.h"

static void dump_io(struct gameboy *gb) {
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
    int i;

    for (i = 0; i < 7; i++) {
        printf("%s%.4s %02x",
               i > 0 ? " " : "",
               io_registers[i].name,
               gb->memory[io_registers[i].addr]
              );
    }

    (void)printf(" ime %02x dma %02x cycles %u", gb->cpu.ime, gb->is_dma,
                 gb->cycles);
}

//static void dump_instr(struct gameboy *gb) {
//    char buf_instr_name[16], *op_name;
//    char buf_instr_bytes[16], byte_len;
//    uint8_t idx = read_u8(gb, gb->cpu.pc);
//
//    if (idx == 0xcb) {
//        idx = read_u8(gb, gb->cpu.pc + 1);
//        byte_len = byte_lens1[idx];
//        op_name = op_names1[idx];
//        sprintf(buf_instr_name, "%s", op_name);
//    } else {
//        byte_len = byte_lens0[idx];
//        op_name = op_names0[idx];
//
//        if (strstr(op_name, "%02")) {
//            sprintf(buf_instr_name, op_name, read_u8(gb, gb->cpu.pc + 1));
//        } else if (strstr(op_name, "%04")) {
//            sprintf(buf_instr_name, op_name, read_u16(gb, gb->cpu.pc + 1));
//        } else {
//            sprintf(buf_instr_name, "%s", op_name);
//        }
//    }
//
//    if (byte_len == 0) {
//        sprintf(buf_instr_bytes, "wtf");
//    } else if (byte_len == 1) {
//        sprintf(buf_instr_bytes, "%02x", read_u8(gb, gb->cpu.pc));
//    } else if (byte_len == 2) {
//        sprintf(buf_instr_bytes, "%02x%02x",
//                read_u8(gb, gb->cpu.pc),
//                read_u8(gb, gb->cpu.pc + 1)
//               );
//    } else if (byte_len == 3) {
//        sprintf(buf_instr_bytes, "%02x%02x%02x",
//                read_u8(gb, gb->cpu.pc),
//                read_u8(gb, gb->cpu.pc + 1),
//                read_u8(gb, gb->cpu.pc + 2)
//               );
//    }
//
//    printf("af:%04x bc:%04x de:%04x hl:%04x pc:%04x sp:%04x   %-8s  %-16s",
//           R16AF, R16BC, R16DE, R16HL, R16PC, R16SP, buf_instr_bytes, buf_instr_name);
//}

void write_be32(uint8_t *dst, uint32_t val) {
    for (int i = 0; i < 4; i++) {
        dst[i] = (val >> ((3 - i) << 3)) & 255;
    }
}

int screenshot(struct gameboy *gb, char *filename) {
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
    int fd, i, o = 48;

    for (i = 0; i < 144 * 160;) {
        if (!(i % 160)) {
            buf[o++] = 0;
        }

        buf[o] = (3 - gb->screen_buf[i++]) << 6;
        buf[o] |= (3 - gb->screen_buf[i++]) << 4;
        buf[o] |= (3 - gb->screen_buf[i++]) << 2;
        buf[o++] |= 3 - gb->screen_buf[i++];
    }

    (void)write_be32(buf + o, adler32(buf + 48, 5904)); // zlib
    (void)write_be32(buf + o + 4, crc32(buf + 37, 5919)); // idat
    fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC | O_BINARY, 0644);

    if (fd < 1) {
        perror(__func__);
        return 0;
    }

    (void)write(fd, buf, sizeof(buf));
    (void)close(fd);
    return 1;
}

void debug(struct gameboy *gb) {
    if (gb->debug) {
//        dump_instr(gb);
        printf("    ");
        dump_io(gb);
        printf("\n");
        fflush(stdout);
    }
}
