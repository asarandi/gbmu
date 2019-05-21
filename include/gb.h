#ifndef GB_H
# define GB_H

#include <stdbool.h>
#include <pthread.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

#define BOOTROM_ENABLED     false
#define GUI_SCALE_FACTOR    3
//#define GUI_RENDER_COLORS   0x00ffffff, 0x00aaaaaa, 0x00555555, 0x00000000
#define GUI_RENDER_COLORS   0x00ebdd77, 0x00a1bc00, 0x000d8833, 0x00004333, 0x00ff0000

typedef struct  s_r16 {
    uint16_t    AF; 
    uint16_t    BC; 
    uint16_t    DE; 
    uint16_t    HL; 
    uint16_t    SP; 
    uint16_t    PC; 
}               t_r16;            

typedef struct  s_r8 {
    uint8_t     F;  
    uint8_t     A;  
    uint8_t     C;  
    uint8_t     B;  
    uint8_t     E;  
    uint8_t     D;  
    uint8_t     L;  
    uint8_t     H;  
    uint16_t    SP; 
    uint16_t    PC; 
}               t_r8;             

typedef struct  s_state {
    void        *gameboy_memory;
    void        *gameboy_registers;
    bool        interrupts_enabled;
    bool        halt;
    bool        halt_bug;
    bool        stop;
    bool        ram_enabled;
    bool        bootrom_enabled;
    bool        debug;
    bool        done;
    bool        dma_update;
    uint64_t    interrupt_cycles;
    uint64_t    div_cycles;
    uint64_t    cycles;
    uint8_t     screen_buf[144*160];
    uint8_t     *file_contents;
	size_t		file_size;
    uint8_t     buttons[8];
    uint8_t     (*ram_read_u8)(uint16_t);
    void        (*ram_write_u8)(uint16_t, uint8_t);
} t_state;

t_state     *state;

#define clear_z_flag     (r8->F &= (~0x80))
#define clear_n_flag     (r8->F &= (~0x40))
#define clear_h_flag     (r8->F &= (~0x20))
#define clear_c_flag     (r8->F &= (~0x10))

#define set_z_flag       (r8->F |= 0x80)
#define set_n_flag       (r8->F |= 0x40)
#define set_h_flag       (r8->F |= 0x20)
#define set_c_flag       (r8->F |= 0x10)

#define is_z_flag        (r8->F & 0x80 ? 1:0)
#define is_n_flag        (r8->F & 0x40 ? 1:0)
#define is_h_flag        (r8->F & 0x20 ? 1:0)
#define is_c_flag        (r8->F & 0x10 ? 1:0)

int         get_num_cycles(void *gb_reg, void *gb_mem);
void        dump_background2(uint8_t *gb_mem, t_state *state);
void        dump_background(uint8_t *gb_mem);
void        dump_ram(void *ram);
void        dump_registers(void *registers, void *gb_state, uint8_t *gb_mem);
void        *gui(void *arg);
void        lcd_update(uint8_t *gb_mem, t_state *state, int current_cycles);
void        interrupts_update(uint8_t *gb_mem, t_state *state, void *registers);
void        timers_update(uint8_t *gb_mem, t_state *state, int current_cycles);

void        apu_init();
void        apu_cleanup();
void        apu_update(uint8_t *gb_mem, t_state *state, int current_cycles);
void        sound_write_u8(uint16_t addr, uint8_t data);

bool        gui_init();
void        gui_cleanup();
void        gui_update();

uint8_t     joypad_read();
void        joypad_request_interrupt();

void        gameboy_init();
void        gb_throttle();

uint8_t     read_u8(uint16_t addr);
uint16_t    read_u16(uint16_t addr);
void        write_u8(uint16_t addr, uint8_t data);
void        write_u16(uint16_t addr, uint16_t data);
void        mbc(uint16_t addr, uint8_t data);
void        mbc1_handler(uint16_t addr, uint8_t data);
void        mbc2_handler(uint16_t addr, uint8_t data);
uint8_t     mbc1_rom_read_u8(uint16_t addr);
uint8_t     mbc1_ram_read_u8(uint16_t addr);

bool        is_savefile_enabled();
void        savefile_read(char *rom_file);
void        savefile_write();

extern      void (*ops0[])(void *, t_state *, uint8_t *);
extern      void (*ops1[])(void *, t_state *, uint8_t *);
extern      int byte_lens0[];
extern      int byte_lens1[];
extern      char* op_names0[];
extern      char* op_names1[];

#endif
