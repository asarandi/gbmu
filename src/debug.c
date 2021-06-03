#include "gb.h"
#include "cpu.h"
#include "hardware.h"

struct {
    int n;
    char *s;
} opcodes[] = {
    {0, "nop"},             {2, "ld bc, $%04X"},{0, "ld (bc), a"},   {0, "inc bc"},    {0, "inc b"},        {0, "dec b"},     {1, "ld b, $%02X"},   {0, "rlca"},
    {2, "ld ($%04X), sp"},  {0, "add hl, bc"},  {0, "ld a, (bc)"},   {0, "dec bc"},    {0, "inc c"},        {0, "dec c"},     {1, "ld c, $%02X"},   {0, "rrca"},
    {1, "stop $%02X"},      {2, "ld de, $%04X"},{0, "ld (de), a"},   {0, "inc de"},    {0, "inc d"},        {0, "dec d"},     {1, "ld d, $%02X"},   {0, "rla"},
    {1, "jr %hhd"},         {0, "add hl, de"},  {0, "ld a, (de)"},   {0, "dec de"},    {0, "inc e"},        {0, "dec e"},     {1, "ld e, $%02X"},   {0, "rra"},
    {1, "jr nz, %hhd"},     {2, "ld hl, $%04X"},{0, "ld (hl+), a"},  {0, "inc hl"},    {0, "inc h"},        {0, "dec h"},     {1, "ld h, $%02X"},   {0, "daa"},
    {1, "jr z, %hhd"},      {0, "add hl, hl"},  {0, "ld a, (hl+)"},  {0, "dec hl"},    {0, "inc l"},        {0, "dec l"},     {1, "ld l, $%02X"},   {0, "cpl"},
    {1, "jr nc, %hhd"},     {2, "ld sp, $%04X"},{0, "ld (hl-), a"},  {0, "inc sp"},    {0, "inc (hl)"},     {0, "dec (hl)"},  {1, "ld (hl), $%02X"},{0, "scf"},
    {1, "jr c, %hhd"},      {0, "add hl, sp"},  {0, "ld a, (hl-)"},  {0, "dec sp"},    {0, "inc a"},        {0, "dec a"},     {1, "ld a, $%02X"},   {0, "ccf"},
    {0, "ld b, b"},         {0, "ld b, c"},     {0, "ld b, d"},      {0, "ld b, e"},   {0, "ld b, h"},      {0, "ld b, l"},   {0, "ld b, (hl)"},    {0, "ld b, a"},
    {0, "ld c, b"},         {0, "ld c, c"},     {0, "ld c, d"},      {0, "ld c, e"},   {0, "ld c, h"},      {0, "ld c, l"},   {0, "ld c, (hl)"},    {0, "ld c, a"},
    {0, "ld d, b"},         {0, "ld d, c"},     {0, "ld d, d"},      {0, "ld d, e"},   {0, "ld d, h"},      {0, "ld d, l"},   {0, "ld d, (hl)"},    {0, "ld d, a"},
    {0, "ld e, b"},         {0, "ld e, c"},     {0, "ld e, d"},      {0, "ld e, e"},   {0, "ld e, h"},      {0, "ld e, l"},   {0, "ld e, (hl)"},    {0, "ld e, a"},
    {0, "ld h, b"},         {0, "ld h, c"},     {0, "ld h, d"},      {0, "ld h, e"},   {0, "ld h, h"},      {0, "ld h, l"},   {0, "ld h, (hl)"},    {0, "ld h, a"},
    {0, "ld l, b"},         {0, "ld l, c"},     {0, "ld l, d"},      {0, "ld l, e"},   {0, "ld l, h"},      {0, "ld l, l"},   {0, "ld l, (hl)"},    {0, "ld l, a"},
    {0, "ld (hl), b"},      {0, "ld (hl), c"},  {0, "ld (hl), d"},   {0, "ld (hl), e"},{0, "ld (hl), h"},   {0, "ld (hl), l"},{0, "halt"},         {0,"ld (hl), a"},
    {0, "ld a, b"},         {0, "ld a, c"},     {0, "ld a, d"},      {0, "ld a, e"},   {0, "ld a, h"},      {0, "ld a, l"},   {0, "ld a, (hl)"},    {0, "ld a, a"},
    {0, "add a, b"},        {0, "add a, c"},    {0, "add a, d"},     {0, "add a, e"},  {0, "add a, h"},     {0, "add a, l"},  {0, "add a, (hl)"},   {0, "add a, a"},
    {0, "adc a, b"},        {0, "adc a, c"},    {0, "adc a, d"},     {0, "adc a, e"},  {0, "adc a, h"},     {0, "adc a, l"},  {0, "adc a, (hl)"},   {0, "adc a, a"},
    {0, "sub b"},           {0, "sub c"},       {0, "sub d"},        {0, "sub e"},     {0, "sub h"},        {0, "sub l"},     {0, "sub (hl)"},      {0, "sub a"},
    {0, "sbc a, b"},        {0, "sbc a, c"},    {0, "sbc a, d"},     {0, "sbc a, e"},  {0, "sbc a, h"},     {0, "sbc a, l"},  {0, "sbc a, (hl)"},   {0, "sbc a, a"},
    {0, "and b"},           {0, "and c"},       {0, "and d"},        {0, "and e"},     {0, "and h"},        {0, "and l"},     {0, "and (hl)"},      {0, "and a"},
    {0, "xor b"},           {0, "xor c"},       {0, "xor d"},        {0, "xor e"},     {0, "xor h"},        {0, "xor l"},     {0, "xor (hl)"},      {0, "xor a"},
    {0, "or b"},            {0, "or c"},        {0, "or d"},         {0, "or e"},      {0, "or h"},         {0, "or l"},      {0, "or (hl)"},       {0, "or a"},
    {0, "cp b"},            {0, "cp c"},        {0, "cp d"},         {0, "cp e"},      {0, "cp h"},         {0, "cp l"},      {0, "cp (hl)"},       {0, "cp a"},
    {0, "ret nz"},          {0, "pop bc"},      {2, "jp nz, $%04X"}, {2, "jp $%04X"},  {2,"call nz, $%04X"},{0, "push bc"},   {1, "add a, $%02X"},  {0, "rst 00h"},
    {0, "ret z"},           {0, "ret"},         {2, "jp z, $%04X"},  {0, "prefix"},    {2,"call z, $%04X"}, {2, "call $%04X"},{1, "adc a, $%02X"},  {0, "rst 08h"},
    {0, "ret nc"},          {0, "pop de"},      {2, "jp nc, $%04X"}, {0, "illegal_d3"},{2,"call nc, $%04X"},{0, "push de"},   {1, "sub $%02X"},     {0, "rst 10h"},
    {0, "ret c"},           {0, "reti"},        {2, "jp c, $%04X"},  {0, "illegal_db"},{2,"call c, $%04X"}, {0, "illegal_dd"},{1, "sbc a, $%02X"},  {0, "rst 18h"},
    {1, "ldh ($FF%02X), a"},{0, "pop hl"},      {0, "ld (c), a"},    {0, "illegal_e3"},{0, "illegal_e4"},   {0, "push hl"},   {1, "and $%02X"},     {0, "rst 20h"},
    {1, "add sp, %hhd"},    {0, "jp hl"},       {2, "ld ($%04X), a"},{0, "illegal_eb"},{0, "illegal_ec"},   {0, "illegal_ed"},{1, "xor $%02X"},     {0, "rst 28h"},
    {1, "ldh a, ($FF%02X)"},{0, "pop af"},      {0, "ld a, (c)"},    {0, "di"},        {0, "illegal_f4"},   {0, "push af"},   {1, "or $%02X"},      {0, "rst 30h"},
    {1, "ld hl, sp%+hhd"},  {0, "ld sp, hl"},   {2, "ld a, ($%04X)"},{0, "ei"},        {0, "illegal_fc"},   {0, "illegal_fd"},{1, "cp $%02X"},      {0, "rst 38h"},
    {0, "rlc b"},           {0, "rlc c"},       {0, "rlc d"},        {0, "rlc e"},     {0, "rlc h"},        {0, "rlc l"},     {0, "rlc (hl)"},      {0, "rlc a"},
    {0, "rrc b"},           {0, "rrc c"},       {0, "rrc d"},        {0, "rrc e"},     {0, "rrc h"},        {0, "rrc l"},     {0, "rrc (hl)"},      {0, "rrc a"},
    {0, "rl b"},            {0, "rl c"},        {0, "rl d"},         {0, "rl e"},      {0, "rl h"},         {0, "rl l"},      {0, "rl (hl)"},       {0, "rl a"},
    {0, "rr b"},            {0, "rr c"},        {0, "rr d"},         {0, "rr e"},      {0, "rr h"},         {0, "rr l"},      {0, "rr (hl)"},       {0, "rr a"},
    {0, "sla b"},           {0, "sla c"},       {0, "sla d"},        {0, "sla e"},     {0, "sla h"},        {0, "sla l"},     {0, "sla (hl)"},      {0, "sla a"},
    {0, "sra b"},           {0, "sra c"},       {0, "sra d"},        {0, "sra e"},     {0, "sra h"},        {0, "sra l"},     {0, "sra (hl)"},      {0, "sra a"},
    {0, "swap b"},          {0, "swap c"},      {0, "swap d"},       {0, "swap e"},    {0, "swap h"},       {0, "swap l"},    {0, "swap (hl)"},     {0, "swap a"},
    {0, "srl b"},           {0, "srl c"},       {0, "srl d"},        {0, "srl e"},     {0, "srl h"},        {0, "srl l"},     {0, "srl (hl)"},      {0, "srl a"},
    {0, "bit 0, b"},        {0, "bit 0, c"},    {0, "bit 0, d"},     {0, "bit 0, e"},  {0, "bit 0, h"},     {0, "bit 0, l"},  {0, "bit 0, (hl)"},   {0, "bit 0, a"},
    {0, "bit 1, b"},        {0, "bit 1, c"},    {0, "bit 1, d"},     {0, "bit 1, e"},  {0, "bit 1, h"},     {0, "bit 1, l"},  {0, "bit 1, (hl)"},   {0, "bit 1, a"},
    {0, "bit 2, b"},        {0, "bit 2, c"},    {0, "bit 2, d"},     {0, "bit 2, e"},  {0, "bit 2, h"},     {0, "bit 2, l"},  {0, "bit 2, (hl)"},   {0, "bit 2, a"},
    {0, "bit 3, b"},        {0, "bit 3, c"},    {0, "bit 3, d"},     {0, "bit 3, e"},  {0, "bit 3, h"},     {0, "bit 3, l"},  {0, "bit 3, (hl)"},   {0, "bit 3, a"},
    {0, "bit 4, b"},        {0, "bit 4, c"},    {0, "bit 4, d"},     {0, "bit 4, e"},  {0, "bit 4, h"},     {0, "bit 4, l"},  {0, "bit 4, (hl)"},   {0, "bit 4, a"},
    {0, "bit 5, b"},        {0, "bit 5, c"},    {0, "bit 5, d"},     {0, "bit 5, e"},  {0, "bit 5, h"},     {0, "bit 5, l"},  {0, "bit 5, (hl)"},   {0, "bit 5, a"},
    {0, "bit 6, b"},        {0, "bit 6, c"},    {0, "bit 6, d"},     {0, "bit 6, e"},  {0, "bit 6, h"},     {0, "bit 6, l"},  {0, "bit 6, (hl)"},   {0, "bit 6, a"},
    {0, "bit 7, b"},        {0, "bit 7, c"},    {0, "bit 7, d"},     {0, "bit 7, e"},  {0, "bit 7, h"},     {0, "bit 7, l"},  {0, "bit 7, (hl)"},   {0, "bit 7, a"},
    {0, "res 0, b"},        {0, "res 0, c"},    {0, "res 0, d"},     {0, "res 0, e"},  {0, "res 0, h"},     {0, "res 0, l"},  {0, "res 0, (hl)"},   {0, "res 0, a"},
    {0, "res 1, b"},        {0, "res 1, c"},    {0, "res 1, d"},     {0, "res 1, e"},  {0, "res 1, h"},     {0, "res 1, l"},  {0, "res 1, (hl)"},   {0, "res 1, a"},
    {0, "res 2, b"},        {0, "res 2, c"},    {0, "res 2, d"},     {0, "res 2, e"},  {0, "res 2, h"},     {0, "res 2, l"},  {0, "res 2, (hl)"},   {0, "res 2, a"},
    {0, "res 3, b"},        {0, "res 3, c"},    {0, "res 3, d"},     {0, "res 3, e"},  {0, "res 3, h"},     {0, "res 3, l"},  {0, "res 3, (hl)"},   {0, "res 3, a"},
    {0, "res 4, b"},        {0, "res 4, c"},    {0, "res 4, d"},     {0, "res 4, e"},  {0, "res 4, h"},     {0, "res 4, l"},  {0, "res 4, (hl)"},   {0, "res 4, a"},
    {0, "res 5, b"},        {0, "res 5, c"},    {0, "res 5, d"},     {0, "res 5, e"},  {0, "res 5, h"},     {0, "res 5, l"},  {0, "res 5, (hl)"},   {0, "res 5, a"},
    {0, "res 6, b"},        {0, "res 6, c"},    {0, "res 6, d"},     {0, "res 6, e"},  {0, "res 6, h"},     {0, "res 6, l"},  {0, "res 6, (hl)"},   {0, "res 6, a"},
    {0, "res 7, b"},        {0, "res 7, c"},    {0, "res 7, d"},     {0, "res 7, e"},  {0, "res 7, h"},     {0, "res 7, l"},  {0, "res 7, (hl)"},   {0, "res 7, a"},
    {0, "set 0, b"},        {0, "set 0, c"},    {0, "set 0, d"},     {0, "set 0, e"},  {0, "set 0, h"},     {0, "set 0, l"},  {0, "set 0, (hl)"},   {0, "set 0, a"},
    {0, "set 1, b"},        {0, "set 1, c"},    {0, "set 1, d"},     {0, "set 1, e"},  {0, "set 1, h"},     {0, "set 1, l"},  {0, "set 1, (hl)"},   {0, "set 1, a"},
    {0, "set 2, b"},        {0, "set 2, c"},    {0, "set 2, d"},     {0, "set 2, e"},  {0, "set 2, h"},     {0, "set 2, l"},  {0, "set 2, (hl)"},   {0, "set 2, a"},
    {0, "set 3, b"},        {0, "set 3, c"},    {0, "set 3, d"},     {0, "set 3, e"},  {0, "set 3, h"},     {0, "set 3, l"},  {0, "set 3, (hl)"},   {0, "set 3, a"},
    {0, "set 4, b"},        {0, "set 4, c"},    {0, "set 4, d"},     {0, "set 4, e"},  {0, "set 4, h"},     {0, "set 4, l"},  {0, "set 4, (hl)"},   {0, "set 4, a"},
    {0, "set 5, b"},        {0, "set 5, c"},    {0, "set 5, d"},     {0, "set 5, e"},  {0, "set 5, h"},     {0, "set 5, l"},  {0, "set 5, (hl)"},   {0, "set 5, a"},
    {0, "set 6, b"},        {0, "set 6, c"},    {0, "set 6, d"},     {0, "set 6, e"},  {0, "set 6, h"},     {0, "set 6, l"},  {0, "set 6, (hl)"},   {0, "set 6, a"},
    {0, "set 7, b"},        {0, "set 7, c"},    {0, "set 7, d"},     {0, "set 7, e"},  {0, "set 7, h"},     {0, "set 7, l"},  {0, "set 7, (hl)"},   {0, "set 7, a"},
};

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

static void dump_instr(struct gameboy *gb) {
    char name[16], hexdump[16];
    uint8_t buf[16];
    int i;

    for (i = 0; i < 3; i++) {
        buf[i] = read_u8(gb, gb->cpu.pc + i);
    }

    i = buf[0];

    if (i == 0xcb) {
        i = 256 + buf[1];
        sprintf(name, "%s", opcodes[i].s);
        sprintf(hexdump, "%02x%02x", buf[0], buf[1]);
    } else {
        if (opcodes[i].n == 1) {
            sprintf(name, opcodes[i].s, buf[1]);
            sprintf(hexdump, "%02x%02x", buf[0], buf[1]);
        } else if (opcodes[i].n == 2) {
            sprintf(name, opcodes[i].s, buf[1] | buf[2] << 8);
            sprintf(hexdump, "%02x%02x%02x", buf[0], buf[1], buf[2]);
        } else {
            sprintf(name, "%s", opcodes[i].s);
            sprintf(hexdump, "%02x", buf[0]);
        }
    }

    printf("af:%04x bc:%04x de:%04x hl:%04x pc:%04x sp:%04x   %-8s  %-16s",
           R16AF, R16BC, R16DE, R16HL, R16PC, R16SP, hexdump, name);
}

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
        dump_instr(gb);
        printf("    ");
        dump_io(gb);
        printf("\n");
        fflush(stdout);
    }
}
