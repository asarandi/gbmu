#include "gb.h"

#define ROM_ADDRESS 0x4000
#define ROM_SIZE    0x4000
#define RAM_ADDRESS 0xa000
#define RAM_SIZE    0x2000

uint8_t mbc1_ram_read_u8(uint16_t addr)
{    
    uint8_t *gb_mem = state->gameboy_memory;

    if (state->ram_enabled)
        return gb_mem[addr];
    else
        return 0xff;
}

void    mbc1_ram_write_u8(uint16_t addr, uint8_t data)
{    
    uint8_t *gb_mem = state->gameboy_memory;

    if (state->ram_enabled)
        gb_mem[addr] = data;
}


void    mbc1_handler(uint16_t addr, uint8_t data)
{
    
/*  
     00h = ROM Banking Mode (up to 8KByte RAM, 2MByte ROM) (default)
     01h = RAM Banking Mode (up to 32KByte RAM, 512KByte ROM)    
*/
    static  uint8_t banking_mode    = 0;
    static  uint8_t rom_number      = 1;
    uint8_t *gb_mem                 = state->gameboy_memory;

    static  uint8_t ram_banks[4][RAM_SIZE];
    static  uint8_t ram_bank_number = 0;

    state->ram_read_u8 = &mbc1_ram_read_u8;
    state->ram_write_u8 = &mbc1_ram_write_u8;

    if (addr <= 0x1fff) {
        state->ram_enabled = ((data & 0x0f) == 0x0a) ? true : false;
    }

    if ((addr >= 0x2000) && (addr <= 0x3fff))       //rom bank number
    {
        data = (rom_number & 0x60) | (data & 0x1f);        
        if ((data == 0) || (data == 0x60) || (data == 0x40) || (data == 0x20))
            data |= 1;

        if (data != rom_number) {
//            printf("setting rom_number; current = %d, new = %d\n", rom_number, data);
            rom_number = data;
            (void)memcpy(&gb_mem[ROM_ADDRESS], &state->file_contents[data * ROM_SIZE], ROM_SIZE);            
        }
    }

    if ((addr >= 0x4000) && (addr <= 0x5fff))       //ram bank number or rom idx upper bits (bits 5,6)
    {
        data &= 3;
        if (banking_mode == 0) {
            data = (data << 5) | (rom_number & 0x1f);     //call self with addr 0x2000 and updated rom_number ? XXX
            return mbc1_handler(0x2000, data);
        }
        if (ram_bank_number != data) {
            (void)memcpy(&ram_banks[ram_bank_number], &gb_mem[RAM_ADDRESS], RAM_SIZE);
        }
        ram_bank_number = data;
        (void)memcpy(&gb_mem[RAM_ADDRESS], &ram_banks[ram_bank_number], RAM_SIZE);
    }


    if ((addr >= 0x6000) && (addr <= 0x7fff))       //banking mode select
    {
        banking_mode = data & 1;
//        printf("setting banking mode to %d\n", banking_mode);
    }
}