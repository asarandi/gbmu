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

#define BOOTROM_ENABLED     false
#define GUI_SCALE_FACTOR    3

//#define GUI_RENDER_COLORS    0xffffff, 0xaaaaaa, 0x555555, 0x000000      /* classic black and white */
//#define GUI_RENDER_COLORS    0xebdd77, 0xa1bc00, 0x0d8833, 0x004333
//#define GUI_RENDER_COLORS    0xd0d058, 0xa0a840, 0x708028, 0x405010      /* lospec.com nostalgia */
//#define GUI_RENDER_COLORS    0x9bbc0f, 0x8bac0f, 0x306230, 0x0f380f      /* wikipedia */
//#define GUI_RENDER_COLORS    0xf8e3c4, 0xcc3495, 0x6b1fb1, 0x0b0630      /* lospec.com: spacehaze */
//#define GUI_RENDER_COLORS    0xeefded, 0x9a7bbc, 0x2d757e, 0x001b2e      /* lospec.com: purpledawn */
//#define GUI_RENDER_COLORS    0xe0f0e8, 0xa8c0b0, 0x507868, 0x183030      /* lospec.com: platinum */
//#define GUI_RENDER_COLORS    0xd0d058, 0xa0a840, 0x708028, 0x405010      /* lospec.com: nostalgia */
//#define GUI_RENDER_COLORS    0xf4fbd0, 0x68cf68, 0x1e9178, 0x05241f      /* lospec.com: lightgreen */
//#define GUI_RENDER_COLORS    0xbeeb71, 0x6ab417, 0x376d03, 0x172808      /* lospec.com: harshgreens */
//#define GUI_RENDER_COLORS    0xc4cfa1, 0x8b956d, 0x4d533c, 0x1f1f1f      /* lospec.com: dirtyboy */
//#define GUI_RENDER_COLORS    0xeff9d6, 0xba5044, 0x7a1c4b, 0x1b0326      /* lospec.com: crimson */
//#define GUI_RENDER_COLORS    0xd0f4f8, 0x70b0c0, 0x3c3468, 0x1c0820      /* lospec.com: blue-seni */
//#define GUI_RENDER_COLORS    0x000000, 0x676767, 0xb6b6b6, 0xffffff      /* lospec.com: 2-bit-grayscale */
//#define GUI_RENDER_COLORS    0x332c50, 0x46878f, 0x94e344, 0xe2f3e4      /* lospec.com: kirokaze-gameboy */
//#define GUI_RENDER_COLORS    0x5a3921, 0x6b8c42, 0x7bc67b, 0xffffb5      /* lospec.com: links-awakening-sgb */
//#define GUI_RENDER_COLORS    0x331e50, 0xa63725, 0xd68e49, 0xf7e7c6      /* lospec.com: nintendo-super-gameboy */
//#define GUI_RENDER_COLORS    0x081820, 0x346856, 0x88c070, 0xe0f8d0      /* lospec.com: nintendo-gameboy-bgb */
//#define GUI_RENDER_COLORS    0x181010, 0x84739c, 0xf7b58c, 0xffefff      /* lospec.com: pokemon-sgb */
//#define GUI_RENDER_COLORS    0x2b2b26, 0x706b66, 0xa89f94, 0xe0dbcd      /* lospec.com: grafxkid-gameboy-pocket-gray */
#define GUI_RENDER_COLORS    0xffe4c2, 0xdca456, 0xa9604c, 0x422936      /* lospec.com: gb-chocolate */
//#define GUI_RENDER_COLORS    0x102533, 0x42678e, 0x6f9edf, 0xcecece      /* lospec.com: megaman-v-sgb */
//#define GUI_RENDER_COLORS    0x7c3f58, 0xeb6b6f, 0xf9a875, 0xfff6d3      /* lospec.com: ice-cream-gb */
//#define GUI_RENDER_COLORS    0x2d1b00, 0x1e606e, 0x5ab9a8, 0xc4f0c2      /* lospec.com: mist-gb */
//#define GUI_RENDER_COLORS    0x2c2137, 0x764462, 0xedb4a1, 0xa96868      /* lospec.com: rustic-gb */
//#define GUI_RENDER_COLORS    0x243137, 0x3f503f, 0x768448, 0xacb56b      /* lospec.com: nintendo-gameboy-arne */
//#define GUI_RENDER_COLORS    0x65296c, 0xb76591, 0xf4b26b, 0xfff5dd      /* lospec.com: grapefruit */
//#define GUI_RENDER_COLORS    0x2c2c96, 0x7733e7, 0xe78686, 0xf7bef7      /* lospec.com: kirby-sgb */
//#define GUI_RENDER_COLORS    0x2e463d, 0x385d49, 0x577b46, 0x7e8416      /* lospec.com: nintendo-gameboy-black-zero */
//#define GUI_RENDER_COLORS    0x202020, 0x5e6745, 0xaeba89, 0xe3eec0      /* lospec.com: andrade-gameboy */
//#define GUI_RENDER_COLORS    0x1f1f1f, 0x4d533c, 0x8b956d, 0xc4cfa1      /* lospec.com: pj-gameboy */
//#define GUI_RENDER_COLORS    0xe7e8f3, 0x8c83c3, 0x634d8f, 0x120b19      /* lospec.com: darkboy4 */
//#define GUI_RENDER_COLORS    0x4c625a, 0x7b9278, 0xabc396, 0xdbf4b4      /* lospec.com: grafxkid-gameboy-pocket-green */
//#define GUI_RENDER_COLORS    0x2c1700, 0x047e60, 0xb62558, 0xaedf1e      /* lospec.com: metroid-ii-sgb */
//#define GUI_RENDER_COLORS    0x2c2137, 0x446176, 0x3fac95, 0xa1ef8c      /* lospec.com: nymph-gb */
//#define GUI_RENDER_COLORS    0x1e0000, 0x9e0000, 0xf78e50, 0xcef7f7      /* lospec.com: kid-icarus-sgb */
//#define GUI_RENDER_COLORS    0x004333, 0x0d8833, 0xa1bc00, 0xebdd77      /* lospec.com: gb-easy-greens */
//#define GUI_RENDER_COLORS    0x33ccff, 0x2086fd, 0x57001a, 0xb2194c      /* lospec.com: gameboy-pop */
//#define GUI_RENDER_COLORS    0x622e4c, 0x7550e8, 0x608fcf, 0x8be5ff      /* lospec.com: wish-gb */
//#define GUI_RENDER_COLORS    0x000000, 0x11c600, 0xdfa677, 0xeff7b6      /* lospec.com: super-mario-land-2-sgb */

#define ROM_ADDRESS 0x4000
#define ROM_SIZE    0x4000
#define RAM_ADDRESS 0xa000
#define RAM_SIZE    0x2000

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
    void            *gameboy_memory;
    void            *gameboy_registers;
    bool            interrupts_enabled;
    bool            halt;
    bool            halt_bug;
    bool            stop;
    bool            ram_enabled;
    bool            bootrom_enabled;
    bool            debug;
    bool            done;
    bool            dma_update;
    char            *rom_file;
    char            *ram_file;    
	size_t          file_size;    
    uint8_t         *file_contents;
    uint8_t         ram_banks[RAM_SIZE * 16];
    unsigned int    interrupt_cycles;
    unsigned int    div_cycles;
    unsigned int    cycles;
    uint8_t         screen_buf[144*160];
    uint8_t         buttons[8];
    uint8_t         (*ram_read_u8)(uint16_t);
    void            (*ram_write_u8)(uint16_t, uint8_t);
    uint8_t         (*rom_read_u8)(uint16_t);
    void            (*rom_write_u8)(uint16_t, uint8_t);
/*    serial/tcp    */        
    bool            is_server;
    bool            is_client;
    bool            is_transfer;
    uint8_t         serial_data;
    unsigned int    serial_cycles;
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

void        cartridge_init();

uint8_t     mbc1_ram_read_u8(uint16_t addr);
void        mbc1_ram_write_u8(uint16_t addr, uint8_t data);
uint8_t     mbc1_rom_read_u8(uint16_t addr);
void        mbc1_rom_write_u8(uint16_t addr, uint8_t data);

uint8_t     mbc2_ram_read_u8(uint16_t addr);
void        mbc2_ram_write_u8(uint16_t addr, uint8_t data);
uint8_t     mbc2_rom_read_u8(uint16_t addr);
void        mbc2_rom_write_u8(uint16_t addr, uint8_t data);

uint8_t     mbc3_ram_read_u8(uint16_t addr);
void        mbc3_ram_write_u8(uint16_t addr, uint8_t data);
uint8_t     mbc3_rom_read_u8(uint16_t addr);
void        mbc3_rom_write_u8(uint16_t addr, uint8_t data);

uint8_t     mbc5_ram_read_u8(uint16_t addr);
void        mbc5_ram_write_u8(uint16_t addr, uint8_t data);
uint8_t     mbc5_rom_read_u8(uint16_t addr);
void        mbc5_rom_write_u8(uint16_t addr, uint8_t data);

bool        is_savefile_enabled();
void        savefile_read();
void        savefile_write();

extern      void (*ops0[])(void *, t_state *, uint8_t *);
extern      void (*ops1[])(void *, t_state *, uint8_t *);
extern      int byte_lens0[];
extern      int byte_lens1[];
extern      char* op_names0[];
extern      char* op_names1[];

/*  serial/tcp  */
bool    client_create();
bool    client_connect();
bool    client_send(uint8_t *octet);
bool    client_recv(uint8_t *octet);
bool    server_create();
bool    server_accept();
bool    server_send(uint8_t *octet);
bool    server_recv(uint8_t *octet);
bool    is_online();
bool    socket_send(uint8_t *octet);
bool    socket_receive(uint8_t *octet);
void    serial_cleanup();
void    set_blocking();
void    set_nonblocking();
void    serial_connect();
void    bit_transfer_ok(uint8_t octet_recv);
void    byte_transfer_ok(uint8_t octet_recv);
void    master_offline();
void    master_init();
void    slave_init();
void    master_bit_transfer();
void    master_byte_transfer();
void    slave_bit_transfer();
void    slave_byte_transfer();
void    serial(uint8_t current_cycles);
void    serial_data(uint8_t data);
void    serial_control(uint8_t data);

#endif
