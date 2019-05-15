#include "gb.h"

#define ROM_ADDRESS 0x4000
#define ROM_SIZE    0x4000
#define RAM_ADDRESS 0xa000
#define RAM_SIZE    0x2000

static  char    *ramfile_name;
static  uint8_t ram_banks[4][RAM_SIZE];
static  uint8_t ram_bank_number = 0;

uint8_t mbc1_ram_read_u8(uint16_t addr)
{    
    uint8_t *gb_mem = state->gameboy_memory;

    if (state->ram_enabled)
        return gb_mem[addr];
    else
        return 0xff;
}

void    ramfile_load(char *rom_file)
{
    int len, offset, fd;
    uint8_t *gb_mem = state->gameboy_memory;

    len = strlen(rom_file);
    ramfile_name = malloc(len + 5);
    strncpy(ramfile_name, rom_file, len);
    bzero(&ramfile_name[len], 5);
    offset = 0;
    if (!strcmp(&ramfile_name[len - 3], ".gb"))
        offset = 3;
    if (!strcmp(&ramfile_name[len - 4], ".gbc"))
        offset = 4;
    strncpy(&ramfile_name[len - offset], ".sav", 4);
    printf("ramfile: %s\n", ramfile_name);

    if ((fd = open(ramfile_name, O_RDONLY)) == -1) {
        printf("%s: open() failed\n", __func__);
        return ;
    }
    if ((read(fd, ram_banks, RAM_SIZE * 4)) == -1) {
        close(fd);        
        printf("%s: read() failed\n", __func__);
        return ;
    }
    close(fd);
    (void)memcpy(&gb_mem[RAM_ADDRESS], ram_banks, RAM_SIZE);
    printf("ramfile loaded\n");
}

void    ramfile_save()
{
    int fd;    
    uint8_t *gb_mem = state->gameboy_memory;

    (void)memcpy(&ram_banks[ram_bank_number], &gb_mem[RAM_ADDRESS], RAM_SIZE);
    if ((fd = open(ramfile_name, O_CREAT | O_WRONLY, 0644)) == -1) {
        printf("%s: open() failed\n", __func__);
        return ;
    }
    if (write(fd, ram_banks, RAM_SIZE * 4) == -1) {
        printf("%s: write() failed\n", __func__);
    }
    close(fd);
    printf("ramfile saved\n");
}

void    mbc1_ram_write_u8(uint16_t addr, uint8_t data)
{    
    uint8_t *gb_mem = state->gameboy_memory;

    if (!state->ram_enabled)
        return ;
    gb_mem[addr] = data;
}

void    mbc1_handler(uint16_t addr, uint8_t data)
{
    
/*  
     00h = ROM Banking Mode (up to 8KByte RAM, 2MByte ROM) (default)
     01h = RAM Banking Mode (up to 32KByte RAM, 512KByte ROM)    
*/
    static  bool    ram_init        = false;
    static  uint8_t banking_mode    = 0;
    static  uint8_t rom_number      = 1;
    uint8_t *gb_mem                 = state->gameboy_memory;


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
        if ((ram_bank_number != data) || (!ram_init)) {
            (void)memcpy(&ram_banks[ram_bank_number], &gb_mem[RAM_ADDRESS], RAM_SIZE);
            ram_init = true;
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
