#include "gb.h"

#define     IS_ROM_ONLY                              (gb_mem[0x0147] == 0x00 ? 1:0) 
#define     IS_MBC1                                  (gb_mem[0x0147] == 0x01 ? 1:0)
#define     IS_MBC1_RAM                              (gb_mem[0x0147] == 0x02 ? 1:0)
#define     IS_MBC1_RAM_BATTERY                      (gb_mem[0x0147] == 0x03 ? 1:0)
#define     IS_MBC2                                  (gb_mem[0x0147] == 0x05 ? 1:0)
#define     IS_MBC2_BATTERY                          (gb_mem[0x0147] == 0x06 ? 1:0)
#define     IS_ROM_RAM                               (gb_mem[0x0147] == 0x08 ? 1:0)
#define     IS_ROM_RAM_BATTERY                       (gb_mem[0x0147] == 0x09 ? 1:0)
#define     IS_MMM01                                 (gb_mem[0x0147] == 0x0B ? 1:0)
#define     IS_MMM01_RAM                             (gb_mem[0x0147] == 0x0C ? 1:0)
#define     IS_MMM01_RAM_BATTERY                     (gb_mem[0x0147] == 0x0D ? 1:0)
#define     IS_MBC3_TIMER_BATTERY                    (gb_mem[0x0147] == 0x0F ? 1:0)
#define     IS_MBC3_TIMER_RAM_BATTERY                (gb_mem[0x0147] == 0x10 ? 1:0)
#define     IS_MBC3                                  (gb_mem[0x0147] == 0x11 ? 1:0)
#define     IS_MBC3_RAM                              (gb_mem[0x0147] == 0x12 ? 1:0)
#define     IS_MBC3_RAM_BATTERY                      (gb_mem[0x0147] == 0x13 ? 1:0)
#define     IS_MBC5                                  (gb_mem[0x0147] == 0x19 ? 1:0)
#define     IS_MBC5_RAM                              (gb_mem[0x0147] == 0x1A ? 1:0)
#define     IS_MBC5_RAM_BATTERY                      (gb_mem[0x0147] == 0x1B ? 1:0)
#define     IS_MBC5_RUMBLE                           (gb_mem[0x0147] == 0x1C ? 1:0)
#define     IS_MBC5_RUMBLE_RAM                       (gb_mem[0x0147] == 0x1D ? 1:0)
#define     IS_MBC5_RUMBLE_RAM_BATTERY               (gb_mem[0x0147] == 0x1E ? 1:0)
#define     IS_MBC6                                  (gb_mem[0x0147] == 0x20 ? 1:0)
#define     IS_MBC7_SENSOR_RUMBLE_RAM_BATTERY        (gb_mem[0x0147] == 0x22 ? 1:0)
#define     IS_POCKET CAMERA                         (gb_mem[0x0147] == 0xFC ? 1:0)
#define     IS_BANDAI TAMA5                          (gb_mem[0x0147] == 0xFD ? 1:0)
#define     IS_HuC3                                  (gb_mem[0x0147] == 0xFE ? 1:0)
#define     IS_HuC1_RAM_BATTERY                      (gb_mem[0x0147] == 0xFF ? 1:0)

typedef struct  s_cartridge {
    uint8_t     id;
    char        *name;
}               t_cartridge;

t_cartridge cartridge_types[] = { 
    {0x00, "ROM ONLY"},
    {0x01, "MBC1"},
    {0x02, "MBC1+RAM"},
    {0x03, "MBC1+RAM+BATTERY"},
    {0x05, "MBC2"},
    {0x06, "MBC2+BATTERY"},
    {0x08, "ROM+RAM"},
    {0x09, "ROM+RAM+BATTERY"},
    {0x0B, "MMM01"},
    {0x0C, "MMM01+RAM"},
    {0x0D, "MMM01+RAM+BATTERY"},
    {0x0F, "MBC3+TIMER+BATTERY"},
    {0x10, "MBC3+TIMER+RAM+BATTERY"},
    {0x11, "MBC3"},
    {0x12, "MBC3+RAM"},
    {0x13, "MBC3+RAM+BATTERY"},
    {0x19, "MBC5"},
    {0x1A, "MBC5+RAM"},
    {0x1B, "MBC5+RAM+BATTERY"},
    {0x1C, "MBC5+RUMBLE"},
    {0x1D, "MBC5+RUMBLE+RAM"},
    {0x1E, "MBC5+RUMBLE+RAM+BATTERY"},
    {0x20, "MBC6"},
    {0x22, "MBC7+SENSOR+RUMBLE+RAM+BATTERY"},
    {0xFC, "POCKET CAMERA"},
    {0xFD, "BANDAI TAMA5"},
    {0xFE, "HuC3"},
    {0xFF, "HuC1+RAM+BATTERY"}
};


#define ROM_ADDRESS 0x4000
#define ROM_SIZE    0x4000

void    mbc1_handler(uint16_t addr, uint8_t data)
{
    
/*  
     00h = ROM Banking Mode (up to 8KByte RAM, 2MByte ROM) (default)
     01h = RAM Banking Mode (up to 32KByte RAM, 512KByte ROM)    
*/
    static  uint8_t banking_mode    = 0;
    static  uint8_t rom_number      = 1;
    static  bool    ram_enabled     = false;
    uint8_t *gb_mem                 = state->gameboy_memory;

    if (addr <= 0x1fff) {
        ram_enabled = ((data & 0x0f) == 0x0a) ? true : false;
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
        if (banking_mode == 0)
            rom_number |= (data & 3)<<5;
    }


    if ((addr >= 0x6000) && (addr <= 0x7fff))       //banking mode select
    {
        banking_mode = data & 1;
        printf("setting banking mode to %d\n", banking_mode);
    }


}

void    mbc(uint16_t addr, uint8_t data)
{
    uint8_t *gb_mem = state->gameboy_memory;

    if (IS_MBC1)
        (void)mbc1_handler(addr, data);
    if (IS_MBC1_RAM_BATTERY)
        (void)mbc1_handler(addr, data);
}
