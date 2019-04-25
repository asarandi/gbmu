#include "gb.h"

#define ROM_ADDRESS 0x4000
#define ROM_SIZE    0x4000
#define RAM_ADDRESS 0xa000
#define RAM_SIZE    0x2000

uint8_t mbc2_ram_read_u8(uint16_t addr)
{    
    uint8_t *gb_mem = state->gameboy_memory;

    if (state->ram_enabled)
        return gb_mem[addr];
    else
        return 0xff;
}

void    mbc2_ram_write_u8(uint16_t addr, uint8_t data)
{    
    uint8_t *gb_mem = state->gameboy_memory;

    if (state->ram_enabled)
    {
        if ((addr >= 0xa000) && (addr <= 0xa1ff))
        {
            gb_mem[addr] = 0xf0 | (data & 0x0f);        /* as per pan docs storing only lower 4 bits */
        }
    }
}

void    mbc2_handler(uint16_t addr, uint8_t data)
{
    uint8_t *gb_mem                 = state->gameboy_memory;    
    static  uint8_t rom_number      = 1;

    static  uint8_t ram_bank[RAM_SIZE] = {0xff};
    static  uint8_t ram_bank_number = 0;

    state->ram_read_u8 = &mbc2_ram_read_u8;
    state->ram_write_u8 = &mbc2_ram_write_u8;
    
    if (addr <= 0x1fff)
    {
        if (((addr >> 8) & 1) == 0)
            state->ram_enabled = ((data & 0x0f) == 0x0a) ? true : false;
    }

    if ((addr >= 0x2000) && (addr <= 0x3fff))       //rom bank number
    {
        if (addr & 0x100)
        {
            data &= 0x1f;
            if (data == 0)
                data |= 1;
            if (data != rom_number)
            {
                rom_number = data;
                (void)memcpy(&gb_mem[ROM_ADDRESS], &state->file_contents[data * ROM_SIZE], ROM_SIZE);            
            }
        }
    }
}

