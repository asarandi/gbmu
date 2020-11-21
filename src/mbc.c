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
#define     IS_POCKET_CAMERA                         (gb_mem[0x0147] == 0xFC ? 1:0)
#define     IS_BANDAI_TAMA5                          (gb_mem[0x0147] == 0xFD ? 1:0)
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

bool    is_savefile_enabled()
{
    if (IS_MBC1_RAM_BATTERY)                return true;
    if (IS_MBC2_BATTERY)                    return true;
    if (IS_ROM_RAM_BATTERY)                 return true;
    if (IS_MMM01_RAM_BATTERY)               return true;
    if (IS_MBC3_TIMER_BATTERY)              return true;
    if (IS_MBC3_TIMER_RAM_BATTERY)          return true;
    if (IS_MBC3_RAM_BATTERY)                return true;
    if (IS_MBC5_RAM_BATTERY)                return true;
    if (IS_MBC5_RUMBLE_RAM_BATTERY)         return true;
    if (IS_MBC7_SENSOR_RUMBLE_RAM_BATTERY)  return true;
    if (IS_HuC1_RAM_BATTERY)                return true;
    return false;
}

void    savefile_read()
{
    int len, offset, fd;

    if (!is_savefile_enabled())
        return ;

    len = strlen(state->rom_file);
    state->ram_file = malloc(len + 5);
    strncpy(state->ram_file, state->rom_file, len);
    (void)memset(&state->ram_file[len], 0, 5);
    offset = 0;
    if (!strcmp(&state->ram_file[len - 3], ".gb"))
        offset = 3;
    if (!strcmp(&state->ram_file[len - 4], ".gbc"))
        offset = 4;
    strncpy(&state->ram_file[len - offset], ".sav", 5);
    printf("ramfile: %s\n", state->ram_file);

    if ((fd = open(state->ram_file, O_RDONLY)) == -1) {
        printf("%s: open() failed\n", "savefile_read()");
        return ;
    }
    if ((read(fd, state->ram_banks, RAM_SIZE * 16)) == -1) {
        close(fd);
        printf("%s: read() failed\n", "savefile_read()");
        return ;
    }
    close(fd);
    printf("ramfile loaded\n");
}

void    savefile_write()
{
    int fd, size;

    if (!is_savefile_enabled())
        return ;
    size = (RAM_SIZE * 16)-1;
    while ((size >= 0) && (!state->ram_banks[size]))
        size--;
    size++;
    if (!size) return ; /* game did not use ram? */
    if ((fd = open(state->ram_file, O_CREAT | O_WRONLY, 0644)) == -1) {
        printf("%s: open() failed\n", "savefile_write()");
        return ;
    }
    if (write(fd, state->ram_banks, size) == -1) {
        printf("%s: write() failed\n", "savefile_write()");
    }
    close(fd);
    printf("ramfile saved\n");
}

void    default_ram_write_u8(uint16_t addr, uint8_t data)
{
    (void)addr;
    (void)data;
    return ;
}

uint8_t default_ram_read_u8(uint16_t addr)
{
    (void)addr;
    return 0xff ;
}

uint8_t default_rom_read_u8(uint16_t addr)
{
    (void)addr;
    return state->file_contents[addr & 0x7fff];
}

void    default_rom_write_u8(uint16_t addr, uint8_t data)
{
    (void)addr;
    (void)data;
    return ;
}

void    cartridge_init()
{
    state->ram_read_u8  = &default_ram_read_u8;
    state->ram_write_u8 = &default_ram_write_u8;
    state->rom_read_u8  = &default_rom_read_u8;
    state->rom_write_u8 = &default_rom_write_u8;

    if ((IS_MBC1) || (IS_MBC1_RAM) || (IS_MBC1_RAM_BATTERY)) {
        state->ram_read_u8  = &mbc1_ram_read_u8;
        state->ram_write_u8 = &mbc1_ram_write_u8;
        state->rom_read_u8  = &mbc1_rom_read_u8;
        state->rom_write_u8 = &mbc1_rom_write_u8;
    }

    if ((IS_MBC2) || (IS_MBC2_BATTERY)) {
        state->ram_read_u8  = &mbc2_ram_read_u8;
        state->ram_write_u8 = &mbc2_ram_write_u8;
        state->rom_read_u8  = &mbc2_rom_read_u8;
        state->rom_write_u8 = &mbc2_rom_write_u8;
    }

    if ((IS_MBC3_TIMER_BATTERY) || (IS_MBC3_TIMER_RAM_BATTERY) || (IS_MBC3) || (IS_MBC3_RAM) || (IS_MBC3_RAM_BATTERY)) {
        state->ram_read_u8  = &mbc3_ram_read_u8;
        state->ram_write_u8 = &mbc3_ram_write_u8;
        state->rom_read_u8  = &mbc3_rom_read_u8;
        state->rom_write_u8 = &mbc3_rom_write_u8;
    }

    if ((IS_MBC5) || (IS_MBC5_RAM) || (IS_MBC5_RAM_BATTERY) || (IS_MBC5_RUMBLE) || (IS_MBC5_RUMBLE_RAM) || (IS_MBC5_RUMBLE_RAM_BATTERY)) {
        state->ram_read_u8  = &mbc5_ram_read_u8;
        state->ram_write_u8 = &mbc5_ram_write_u8;
        state->rom_read_u8  = &mbc5_rom_read_u8;
        state->rom_write_u8 = &mbc5_rom_write_u8;
    }
}
