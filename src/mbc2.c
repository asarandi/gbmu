#include "gb.h"

static uint8_t ramg, romb = 1;

void    mbc2_ram_write_u8(uint16_t addr, uint8_t data)
{
    if (ramg != 0x0a)
        return ;
    state->ram_banks[addr & 0x1fff] = (data & 0x0f) | 0xf0;
}

uint8_t mbc2_ram_read_u8(uint16_t addr)
{
    if (ramg != 0x0a)
        return 0xff;
    return (state->ram_banks[addr & 0x1fff] & 0x0f) | 0xf0;
}

uint8_t     mbc2_rom_read_u8(uint16_t addr)
{
    uint8_t     *f = state->file_contents;
    int         idx;

    if (addr <= 0x3fff)
        return f[addr];
    if ((addr >= 0x4000) && (addr <= 0x7fff)) {
        idx = (romb << 14 ) | (addr & 0x3fff);
        idx &= state->file_size - 1;
        return f[idx];
    }
    return 0xff;
}

void        mbc2_rom_write_u8(uint16_t addr, uint8_t data)
{
    if (addr <= 0x1fff)
        ramg = data & 0x0f;
    if ((addr >= 0x2000) && (addr <= 0x3fff)) {
        romb = data & 0x0f;
        if (romb == 0)
            romb = 1;
    }
}
