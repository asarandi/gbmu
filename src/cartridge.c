#include "gb.h"
#include <errno.h>

static uint8_t ramg, romb0 = 1, romb1, ramb, mode;

#define IS_ROM_ONLY                       (gb_mem[0x0147] == 0x00 ? 1:0)
#define IS_MBC1                           (gb_mem[0x0147] == 0x01 ? 1:0)
#define IS_MBC1_RAM                       (gb_mem[0x0147] == 0x02 ? 1:0)
#define IS_MBC1_RAM_BATTERY               (gb_mem[0x0147] == 0x03 ? 1:0)
#define IS_MBC2                           (gb_mem[0x0147] == 0x05 ? 1:0)
#define IS_MBC2_BATTERY                   (gb_mem[0x0147] == 0x06 ? 1:0)
#define IS_ROM_RAM                        (gb_mem[0x0147] == 0x08 ? 1:0)
#define IS_ROM_RAM_BATTERY                (gb_mem[0x0147] == 0x09 ? 1:0)
#define IS_MMM01                          (gb_mem[0x0147] == 0x0B ? 1:0)
#define IS_MMM01_RAM                      (gb_mem[0x0147] == 0x0C ? 1:0)
#define IS_MMM01_RAM_BATTERY              (gb_mem[0x0147] == 0x0D ? 1:0)
#define IS_MBC3_TIMER_BATTERY             (gb_mem[0x0147] == 0x0F ? 1:0)
#define IS_MBC3_TIMER_RAM_BATTERY         (gb_mem[0x0147] == 0x10 ? 1:0)
#define IS_MBC3                           (gb_mem[0x0147] == 0x11 ? 1:0)
#define IS_MBC3_RAM                       (gb_mem[0x0147] == 0x12 ? 1:0)
#define IS_MBC3_RAM_BATTERY               (gb_mem[0x0147] == 0x13 ? 1:0)
#define IS_MBC5                           (gb_mem[0x0147] == 0x19 ? 1:0)
#define IS_MBC5_RAM                       (gb_mem[0x0147] == 0x1A ? 1:0)
#define IS_MBC5_RAM_BATTERY               (gb_mem[0x0147] == 0x1B ? 1:0)
#define IS_MBC5_RUMBLE                    (gb_mem[0x0147] == 0x1C ? 1:0)
#define IS_MBC5_RUMBLE_RAM                (gb_mem[0x0147] == 0x1D ? 1:0)
#define IS_MBC5_RUMBLE_RAM_BATTERY        (gb_mem[0x0147] == 0x1E ? 1:0)
#define IS_MBC6                           (gb_mem[0x0147] == 0x20 ? 1:0)
#define IS_MBC7_SENSOR_RUMBLE_RAM_BATTERY (gb_mem[0x0147] == 0x22 ? 1:0)
#define IS_POCKET_CAMERA                  (gb_mem[0x0147] == 0xFC ? 1:0)
#define IS_BANDAI_TAMA5                   (gb_mem[0x0147] == 0xFD ? 1:0)
#define IS_HuC3                           (gb_mem[0x0147] == 0xFE ? 1:0)
#define IS_HuC1_RAM_BATTERY               (gb_mem[0x0147] == 0xFF ? 1:0)

typedef struct s_cartridge {
    uint8_t id;
    char *name;
} t_cartridge;

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

static bool is_savefile_enabled() {
    if (IS_MBC1_RAM_BATTERY) {
        return true;
    }

    if (IS_MBC2_BATTERY) {
        return true;
    }

    if (IS_ROM_RAM_BATTERY) {
        return true;
    }

    if (IS_MMM01_RAM_BATTERY) {
        return true;
    }

    if (IS_MBC3_TIMER_BATTERY) {
        return true;
    }

    if (IS_MBC3_TIMER_RAM_BATTERY) {
        return true;
    }

    if (IS_MBC3_RAM_BATTERY) {
        return true;
    }

    if (IS_MBC5_RAM_BATTERY) {
        return true;
    }

    if (IS_MBC5_RUMBLE_RAM_BATTERY) {
        return true;
    }

    if (IS_MBC7_SENSOR_RUMBLE_RAM_BATTERY) {
        return true;
    }

    if (IS_HuC1_RAM_BATTERY) {
        return true;
    }

    return false;
}

int savefile_read() {
    int len, offset, fd;
    struct stat st;

    if (!is_savefile_enabled()) {
        return 1;
    }

    len = strlen(state->rom_file);
    state->ram_file = calloc(len + 6, 1);
    (void)strncpy(state->ram_file, state->rom_file, len + 1);
    (void)memset(&state->ram_file[len], 0, 5);
    offset = 0;

    if (!strcmp(&state->ram_file[len - 3], ".gb")) {
        offset = 3;
    }

    if (!strcmp(&state->ram_file[len - 4], ".gbc")) {
        offset = 4;
    }

    strncpy(&state->ram_file[len - offset], ".sav", 5);

    if (stat(state->ram_file, &st) != 0) {
        if (errno == ENOENT) {
            /* file does not exist ? */
            return 1;
        }

        (void)perror(__func__);
        return 0;
    }

    if ((fd = open(state->ram_file, O_RDONLY)) == -1) {
        (void)perror(__func__);
        return 0;
    }

    if ((read(fd, state->ram_banks, RAM_SIZE * 16)) == -1) {
        (void)perror(__func__);
        (void)close(fd);
        return 0;
    }

    (void)close(fd);
    (void)printf("savefile loaded: %s\n", state->ram_file);
    return 1;
}

int savefile_write() {
    int fd, size;

    if (!is_savefile_enabled()) {
        return 1;
    }

    size = (RAM_SIZE * 16) - 1;

    while ((size >= 0) && (!state->ram_banks[size])) {
        size--;
    }

    size++;

    /* no ram data ? */
    if (!size) {
        return 1;
    }

    fd = open(state->ram_file, O_CREAT | O_TRUNC | O_WRONLY, 0644);

    if (fd == -1) {
        perror(__func__);
        return 0;
    }

    if (write(fd, state->ram_banks, size) == -1) {
        (void)perror(__func__);
        (void)close(fd);
        return 0;
    }

    (void)close(fd);
    (void)printf("savefile stored: %s\n", state->ram_file);
    return 1;
}

void default_ram_write_u8(uint16_t addr, uint8_t data) {
    (void)addr;
    (void)data;
    return;
}

uint8_t default_ram_read_u8(uint16_t addr) {
    (void)addr;
    return 0xff;
}

uint8_t default_rom_read_u8(uint16_t addr) {
    (void)addr;
    return state->file_contents[addr & 0x7fff];
}

void default_rom_write_u8(uint16_t addr, uint8_t data) {
    (void)addr;
    (void)data;
    return;
}

void cartridge_init() {
    state->ram_read_u8 = &default_ram_read_u8;
    state->ram_write_u8 = &default_ram_write_u8;
    state->rom_read_u8 = &default_rom_read_u8;
    state->rom_write_u8 = &default_rom_write_u8;

    if ((IS_MBC1) || (IS_MBC1_RAM) || (IS_MBC1_RAM_BATTERY)) {
        state->ram_read_u8 = &mbc1_ram_read_u8;
        state->ram_write_u8 = &mbc1_ram_write_u8;
        state->rom_read_u8 = &mbc1_rom_read_u8;
        state->rom_write_u8 = &mbc1_rom_write_u8;
    }

    if ((IS_MBC2) || (IS_MBC2_BATTERY)) {
        state->ram_read_u8 = &mbc2_ram_read_u8;
        state->ram_write_u8 = &mbc2_ram_write_u8;
        state->rom_read_u8 = &mbc2_rom_read_u8;
        state->rom_write_u8 = &mbc2_rom_write_u8;
    }

    if ((IS_MBC3_TIMER_BATTERY) || (IS_MBC3_TIMER_RAM_BATTERY) || (IS_MBC3)
            || (IS_MBC3_RAM) || (IS_MBC3_RAM_BATTERY)) {
        state->ram_read_u8 = &mbc3_ram_read_u8;
        state->ram_write_u8 = &mbc3_ram_write_u8;
        state->rom_read_u8 = &mbc3_rom_read_u8;
        state->rom_write_u8 = &mbc3_rom_write_u8;
    }

    if ((IS_MBC5) || (IS_MBC5_RAM) || (IS_MBC5_RAM_BATTERY) || (IS_MBC5_RUMBLE)
            || (IS_MBC5_RUMBLE_RAM) || (IS_MBC5_RUMBLE_RAM_BATTERY)) {
        state->ram_read_u8 = &mbc5_ram_read_u8;
        state->ram_write_u8 = &mbc5_ram_write_u8;
        state->rom_read_u8 = &mbc5_rom_read_u8;
        state->rom_write_u8 = &mbc5_rom_write_u8;
    }
}

void mbc1_ram_write_u8(uint16_t addr, uint8_t data) {
    uint8_t *f = state->file_contents;

    if (ramg != 0x0a) {
        return;
    }

    if ((mode == 1) && (f[0x149] > 2)) {
        state->ram_banks[(romb1 << 13) + (addr & 0x1fff)] = data;
        return;
    }

    state->ram_banks[addr & 0x1fff] = data;
}

uint8_t mbc1_ram_read_u8(uint16_t addr) {
    uint8_t *f = state->file_contents;

    if (ramg != 0x0a) {
        return 0xff;
    }

    if ((mode == 1) && (f[0x149] > 2)) {
        return state->ram_banks[(romb1 << 13) + (addr & 0x1fff)];
    }

    return state->ram_banks[addr & 0x1fff];
}

uint8_t mbc1_rom_read_u8(uint16_t addr) {
    uint8_t *f = state->file_contents;
    int idx;

    if (addr <= 0x3fff) {
        if (mode == 0) {
            return f[addr];
        }

        if (mode == 1) {
            idx = (romb1 << 19) + addr;
            idx &= state->file_size - 1;
            return f[idx];
        }
    }

    if ((addr >= 0x4000) && (addr <= 0x7fff)) {
        idx = (((romb1 << 5) | romb0) << 14) | (addr & 0x3fff);
        idx &= state->file_size - 1;
        return f[idx];
    }

    return 0xff;
}

void mbc1_rom_write_u8(uint16_t addr, uint8_t data) {
    if (addr <= 0x1fff) {
        ramg = data & 0x0f;
    }

    if ((addr >= 0x2000) && (addr <= 0x3fff)) {
        romb0 = data & 0x1f;

        if (romb0 == 0) {
            romb0 = 1;
        }
    }

    if ((addr >= 0x4000) && (addr <= 0x5fff)) {
        romb1 = data & 3;
    }

    if ((addr >= 0x6000) && (addr <= 0x7fff)) {
        mode = data & 1;
    }
}

void mbc2_ram_write_u8(uint16_t addr, uint8_t data) {
    if (ramg != 0x0a) {
        return;
    }

    state->ram_banks[addr & 0x1ff] = (data & 0x0f) | 0xf0;
}

uint8_t mbc2_ram_read_u8(uint16_t addr) {
    if (ramg != 0x0a) {
        return 0xff;
    }

    return (state->ram_banks[addr & 0x1ff] & 0x0f) | 0xf0;
}

uint8_t mbc2_rom_read_u8(uint16_t addr) {
    uint8_t *f = state->file_contents;
    int idx;

    if (addr <= 0x3fff) {
        return f[addr];
    }

    if ((addr >= 0x4000) && (addr <= 0x7fff)) {
        idx = (romb0 << 14) | (addr & 0x3fff);
        idx &= state->file_size - 1;
        return f[idx];
    }

    return 0xff;
}

void mbc2_rom_write_u8(uint16_t addr, uint8_t data) {
    if (addr <= 0x3fff) {
        if (addr & 0x100) {
            romb0 = data & 15;

            if (romb0 == 0) {
                romb0 = 1;
            }
        } else {
            ramg = data & 15;
        }
    }
}

void mbc3_ram_write_u8(uint16_t addr, uint8_t data) {
    if (ramg != 0x0a) {
        return;
    }

    state->ram_banks[(ramb << 13) + (addr & 0x1fff)] = data;
}

uint8_t mbc3_ram_read_u8(uint16_t addr) {
    if (ramg != 0x0a) {
        return 0xff;
    }

    return state->ram_banks[(ramb << 13) + (addr & 0x1fff)];
}

uint8_t mbc3_rom_read_u8(uint16_t addr) {
    uint8_t *f = state->file_contents;
    int idx;

    if (addr <= 0x3fff) {
        return f[addr];
    }

    if ((addr >= 0x4000) && (addr <= 0x7fff)) {
        idx = (romb0 << 14) | (addr & 0x3fff);
        idx &= state->file_size - 1;
        return f[idx];
    }

    return 0xff;
}

void mbc3_rom_write_u8(uint16_t addr, uint8_t data) {
    if (addr <= 0x1fff) {
        ramg = data;
    }

    if ((addr >= 0x2000) && (addr <= 0x3fff)) {
        romb0 = data;

        if (romb0 == 0) {
            romb0 = 1;
        }
    }

    if ((addr >= 0x4000) && (addr <= 0x5fff)) {
        data &= 0x0f;

        if (data <= 3) {
            ramb = data & 3;
        } else {
            printf("mbc3 rtc register select, data = %02x\n", data);    /* TODO */
        }
    }

    if ((addr >= 0x6000) && (addr <= 0x7fff)) {
        printf("mbc3 latch clock data, data = %02x\n", data);    /* TODO */
    }
}

void mbc5_ram_write_u8(uint16_t addr, uint8_t data) {
    if (ramg != 0x0a) {
        return;
    }

    state->ram_banks[(ramb << 13) + (addr & 0x1fff)] = data;
}

uint8_t mbc5_ram_read_u8(uint16_t addr) {
    if (ramg != 0x0a) {
        return 0xff;
    }

    return state->ram_banks[(ramb << 13) + (addr & 0x1fff)];
}

uint8_t mbc5_rom_read_u8(uint16_t addr) {
    uint8_t *f = state->file_contents;
    int idx;

    if (addr <= 0x3fff) {
        return f[addr];
    }

    if ((addr >= 0x4000) && (addr <= 0x7fff)) {
        idx = (((romb1 << 8) | romb0) << 14) | (addr & 0x3fff);
        idx &= state->file_size - 1;
        return f[idx];
    }

    return 0xff;
}

void mbc5_rom_write_u8(uint16_t addr, uint8_t data) {
    if (addr <= 0x1fff) {
        ramg = data;
    }

    if ((addr >= 0x2000) && (addr <= 0x2fff)) {
        romb0 = data;
    }

    if ((addr >= 0x3000) && (addr <= 0x3fff)) {
        romb1 = data & 1;
    }

    if ((addr >= 0x4000) && (addr <= 0x5fff)) {
        ramb = data & 15;
    }
}
