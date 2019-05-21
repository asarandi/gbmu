#include "gb.h"

#define ROM_ADDRESS 0x4000
#define ROM_SIZE    0x4000
#define RAM_ADDRESS 0xa000
#define RAM_SIZE    0x2000

static uint8_t ramg, bank1 = 1, bank2, mode;
static  char    *ramfile_name;
static  uint8_t ram_banks[RAM_SIZE * 4];

void    savefile_read(char *rom_file)
{
    int len, offset, fd;
    uint8_t *gb_mem = state->gameboy_memory;

    if (!is_savefile_enabled())
        return ;

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
    printf("ramfile loaded\n");
}
void    savefile_write()
{
    int fd, size;
    uint8_t *gb_mem = state->gameboy_memory;

    if (!is_savefile_enabled())
        return ;
    size = (RAM_SIZE*4)-1;
    while ((size >= 0) && (!ram_banks[size]))
        size--;
    size++;
    if (!size) return ; //game did not use ram?
    if ((fd = open(ramfile_name, O_CREAT | O_WRONLY, 0644)) == -1) {
        printf("%s: open() failed\n", __func__);
        return ;
    }
    if (write(fd, ram_banks, size) == -1) {
        printf("%s: write() failed\n", __func__);
    }
    close(fd);
    printf("ramfile saved\n");
}

void    mbc1_ram_write_u8(uint16_t addr, uint8_t data)
{    
    uint8_t *gb_mem = state->gameboy_memory;

    if (ramg != 0x0a)
        return ;
    if (mode == 0)
        ram_banks[addr & 0x1fff] = data;
    if (mode == 1)
        ram_banks[(bank2 << 13) + (addr & 0x1fff)] = data;
}

uint8_t mbc1_ram_read_u8(uint16_t addr)
{    
    uint8_t *gb_mem = state->gameboy_memory;

    if (ramg != 0x0a)
        return 0xff;    
    if (mode == 1)
        return ram_banks[(bank2 << 13) + (addr & 0x1fff)];
    return ram_banks[addr & 0x1fff];
}

uint8_t     mbc1_rom_read_u8(uint16_t addr)
{
    uint8_t     *f = state->file_contents;
    int         idx;

    if (addr <= 0x3fff) {
        if (mode == 0)  return f[addr];
        if (mode == 1) {
            idx = (bank2 << 19) + addr;
            idx &= state->file_size - 1;
            return f[idx];
        }
    }
    if ((addr >= 0x4000) && (addr <= 0x7fff)) {
        idx = (((bank2 << 5) | bank1) << 14 ) | (addr & 0x3fff);
        idx &= state->file_size - 1;
        return f[idx];
    }
    return 0xff;
}

void        mbc1_handler(uint16_t addr, uint8_t data)
{
    uint8_t *gb_mem = state->gameboy_memory;

    state->ram_read_u8 = &mbc1_ram_read_u8;
    state->ram_write_u8 = &mbc1_ram_write_u8;

    if (addr <= 0x1fff)
        ramg = data & 0x0f;
    if ((addr >= 0x2000) && (addr <= 0x3fff)) {
        bank1 = data & 0x1f;
        if (bank1 == 0)
            bank1 = 1;
    }
    if ((addr >= 0x4000) && (addr <= 0x5fff))
        bank2 = data & 3;
    if ((addr >= 0x6000) && (addr <= 0x7fff))
        mode = data & 1;
}
