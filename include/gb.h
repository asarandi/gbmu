#ifndef GB_H
# define GB_H

#include <stdbool.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

#define ROM_ADDRESS 0x4000
#define ROM_SIZE    0x4000
#define RAM_ADDRESS 0xa000
#define RAM_SIZE    0x2000

typedef struct s_r16 {
    uint16_t AF;
    uint16_t BC;
    uint16_t DE;
    uint16_t HL;
    uint16_t SP;
    uint16_t PC;
} t_r16;

typedef struct s_r8 {
    uint8_t F;
    uint8_t A;
    uint8_t C;
    uint8_t B;
    uint8_t E;
    uint8_t D;
    uint8_t L;
    uint8_t H;
    uint16_t SP;
    uint16_t PC;
} t_r8;

#define  SAMPLING_FREQUENCY 32768
#define  NUM_FRAMES         1024
#define  NUM_CHANNELS       2
#define  SAMPLE_SIZE        2
#define  SOUND_BUF_SIZE     (NUM_FRAMES * SAMPLE_SIZE * NUM_CHANNELS)

typedef struct s_state {
    void *gameboy_memory;
    void *gameboy_registers;
    bool ime_scheduled;
    bool ime;
    bool halt;
    bool halt_bug;
    bool stop;
    bool ram_enabled;
    bool done;
    bool testing;
    int dma_clocks;
    bool is_dma;
    int exit_code;
    char *rom_file;
    char *ram_file;
    size_t file_size;
    uint8_t *file_contents;
    uint8_t ram_banks[RAM_SIZE * 16];
    uint32_t interrupt_cycles;
    uint32_t div_cycles;
    uint32_t cycles;
    uint8_t screen_buf[144 * 160];
    uint8_t sound_buf[SOUND_BUF_SIZE];
    uint8_t buttons[8];

    uint8_t (*ram_read_u8)(uint16_t);

    void (*ram_write_u8)(uint16_t, uint8_t);

    uint8_t (*rom_read_u8)(uint16_t);

    void (*rom_write_u8)(uint16_t, uint8_t);

    void (*testing_run_hook)();

    void (*testing_write_hook)(uint16_t, uint8_t);

} t_state;

extern uint8_t gb_mem[];
extern t_state *state;

#define CLEAR_Z_FLAG     (r8->F &= (~0x80))
#define CLEAR_N_FLAG     (r8->F &= (~0x40))
#define CLEAR_H_FLAG     (r8->F &= (~0x20))
#define CLEAR_C_FLAG     (r8->F &= (~0x10))

#define SET_Z_FLAG       (r8->F |= 0x80)
#define SET_N_FLAG       (r8->F |= 0x40)
#define SET_H_FLAG       (r8->F |= 0x20)
#define SET_C_FLAG       (r8->F |= 0x10)

#define IS_Z_FLAG        (r8->F & 0x80 ? 1:0)
#define IS_N_FLAG        (r8->F & 0x40 ? 1:0)
#define IS_H_FLAG        (r8->F & 0x20 ? 1:0)
#define IS_C_FLAG        (r8->F & 0x10 ? 1:0)

void dump_registers(uint8_t *mem, t_state *state, t_r16 *r16);

int get_num_cycles(void *gb_reg, void *gb_mem);

int lcd_update(uint8_t *gb_mem, t_state *state, int current_cycles);

void interrupts_update(uint8_t *gb_mem, t_state *state, void *registers);

void timers_update(uint8_t *gb_mem, t_state *state, int current_cycles);

int sound_update(uint8_t *gb_mem, t_state *state, int current_cycles);

void sound_write_u8(uint16_t addr, uint8_t data);

void dma_update(uint8_t *gb_mem, t_state *state, t_r16 *r16);

uint8_t sound_read_u8(uint16_t addr);

int video_open();

int video_close();

int video_write(uint8_t *data, uint32_t size);

int audio_open();

int audio_close();

int audio_write(uint8_t *data, uint32_t size);

int input_open();

int input_close();

int input_read();

int av_sync();

uint8_t joypad_read();

void joypad_write(uint8_t data);

void joypad_request_interrupt();

void set_initial_register_values();

uint8_t io_read_u8(uint16_t addr);

uint8_t read_u8(uint16_t addr);

uint16_t read_u16(uint16_t addr);

void write_u8(uint16_t addr, uint8_t data);

void write_u16(uint16_t addr, uint16_t data);

/* cartridge/mbc */

void cartridge_init();

uint8_t mbc1_ram_read_u8(uint16_t addr);

void mbc1_ram_write_u8(uint16_t addr, uint8_t data);

uint8_t mbc1_rom_read_u8(uint16_t addr);

void mbc1_rom_write_u8(uint16_t addr, uint8_t data);

uint8_t mbc2_ram_read_u8(uint16_t addr);

void mbc2_ram_write_u8(uint16_t addr, uint8_t data);

uint8_t mbc2_rom_read_u8(uint16_t addr);

void mbc2_rom_write_u8(uint16_t addr, uint8_t data);

uint8_t mbc3_ram_read_u8(uint16_t addr);

void mbc3_ram_write_u8(uint16_t addr, uint8_t data);

uint8_t mbc3_rom_read_u8(uint16_t addr);

void mbc3_rom_write_u8(uint16_t addr, uint8_t data);

uint8_t mbc5_ram_read_u8(uint16_t addr);

void mbc5_ram_write_u8(uint16_t addr, uint8_t data);

uint8_t mbc5_rom_read_u8(uint16_t addr);

void mbc5_rom_write_u8(uint16_t addr, uint8_t data);

int savefile_read();

int savefile_write();

/* jump tables */

extern void (*ops0[])(void *, t_state *, uint8_t *);

extern void (*ops1[])(void *, t_state *, uint8_t *);

extern int byte_lens0[];
extern int byte_lens1[];
extern char *op_names0[];
extern char *op_names1[];

/* serial */

uint8_t serial_read_u8(uint16_t addr);

void serial_write_u8(uint16_t addr, uint8_t data);

/* testing  */

int testing_setup();

#endif
