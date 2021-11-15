#ifndef GAMEBOY_H
# define GAMEBOY_H

#include <stdbool.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

#include "sound.h"
#include "timer.h"
#include "cpu.h"

#ifndef O_BINARY
# define O_BINARY 0
#endif

#define FRAME_DURATION  70224
#define VIDEO_BUF_SIZE (160 * 144)
#define RTC_TICK_INCREMENT 3125
#define RTC_TICK_DIVISOR 100000

#define ROM_ADDRESS 0x4000
#define ROM_SIZE    0x4000
#define RAM_ADDRESS 0xa000
#define RAM_SIZE    0x2000


struct dma {
    int index;
    int clocks;
    bool active;
    uint8_t byte;
    uint16_t source;
};

struct rtc {
    uint32_t ticks;
    uint32_t hidden[5];
    uint32_t latched[5];
    uint32_t time;
    uint8_t buf[48];
};

struct cartridge {
    uint8_t *data;
    size_t size;
    uint8_t ramg;
    uint8_t romb0;
    uint8_t romb1;
    uint8_t ramb;
    uint8_t mode;
    uint8_t last_write;
    struct rtc rtc;
};

struct lcd {
    int on;
    int frames;
    int render;
    int wy;
    uint32_t cycle;
    uint8_t buf[160 * 144];
    struct OAM_ATTRS *sprites[10 + 1];
};

struct gameboy {
    struct cpu cpu;
    uint8_t memory[0x10000];
    bool ram_enabled;
    bool done;
    bool debug;
    bool log_io;
    bool screenshot;
    bool testing;
    struct dma dma;
    uint16_t serial_cycles;
    int serial_ctr;
    int exit_code;
    struct cartridge cartridge;
    struct lcd lcd;
    char *rom_file;
    char *ram_file;
    uint64_t ram_size;
    uint8_t ram_banks[RAM_SIZE * 16];
    struct timer timer;
    uint32_t cycles;
    struct channel ch[4];
    uint8_t sound_buf[SOUND_BUF_SIZE];
    uint8_t video_buf[VIDEO_BUF_SIZE];
    uint8_t prev_frame[VIDEO_BUF_SIZE];
    int audio_render;
    uint32_t seq_clocks, seq_frame;
    int32_t samples_clock, samples_index;
    uint8_t buttons[8];
    uint8_t (*ram_read_u8)(struct gameboy *, uint16_t);
    void (*ram_write_u8)(struct gameboy *, uint16_t, uint8_t);
    uint8_t (*rom_read_u8)(struct gameboy *, uint16_t);
    void (*rom_write_u8)(struct gameboy *, uint16_t, uint8_t);
    void (*testing_run_hook)(struct gameboy *);
    void (*testing_write_hook)(struct gameboy *, uint16_t, uint8_t);
};

struct io_register {
    char      *name;
    uint16_t   addr;
    uint8_t    mask;
};

int screenshot(struct gameboy *gb, char *filename);

char *replace_exten(char *rom, char *ext);

void debug(struct gameboy *gb);

void dma_update(struct gameboy *gb);

int lcd_update(struct gameboy *gb);

/* io registers, cpu, interrupts */

void io_init(struct gameboy *gb);

uint8_t io_read_u8(struct gameboy *gb, uint16_t addr);

void io_write_u8(struct gameboy *gb, uint16_t addr, uint8_t data);

int cpu_update(struct gameboy *gb);

int interrupts_update(struct gameboy *gb);

int interrupt_step(struct gameboy *gb);

/* joypad */

uint8_t joypad_read_u8(struct gameboy *gb, uint16_t addr);

void joypad_write_u8(struct gameboy *gb, uint16_t addr, uint8_t data);

void joypad_request_interrupt(struct gameboy *gb);

/* serial */

int serial_update(struct gameboy *gb);

uint8_t serial_read_u8(struct gameboy *gb, uint16_t addr);

void serial_write_u8(struct gameboy *gb, uint16_t addr, uint8_t data);

/* timer*/

uint8_t timer_read_u8(struct gameboy *gb, uint16_t addr);

void timer_write_u8(struct gameboy *gb, uint16_t addr, uint8_t data);

int timer_update(struct gameboy *gb);

/* sound */

uint8_t sound_read_u8(struct gameboy *gb, uint16_t addr);

void sound_write_u8(struct gameboy *gb, uint16_t addr, uint8_t data);

int sound_update(struct gameboy *gb);

int sequencer_step(struct gameboy *gb);

/* bus */

uint8_t read_u8(struct gameboy *gb, uint16_t addr);

void write_u8(struct gameboy *gb, uint16_t addr, uint8_t data);

/* cartridge/mbc */

int cartridge_init(struct gameboy *gb);

int savefile_read(struct gameboy *gb);

int savefile_write(struct gameboy *gb);

int rtc_serialize(struct gameboy *gb);

int rtc_deserialize(struct gameboy *gb);

int rtc_update_to_current(struct gameboy *gb);

int rtc_tick(struct gameboy *gb);

/* testing  */

int testing_setup(struct gameboy *gb, char *test_name);

/* host */

int video_open(struct gameboy *gb);

int video_close(struct gameboy *gb);

int video_write(struct gameboy *gb, uint8_t *data, uint32_t size);

int audio_open(struct gameboy *gb);

int audio_close(struct gameboy *gb);

int audio_write(struct gameboy *gb, uint8_t *data, uint32_t size);

int input_open(struct gameboy *gb);

int input_close(struct gameboy *gb);

int input_read(struct gameboy *gb);

int av_sync(struct gameboy *gb);

/* hash.c */

unsigned long crc32(unsigned char *buf, int len);

unsigned long adler32(unsigned char *buf, int len);

#endif
