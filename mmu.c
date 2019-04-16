#include "gb.h"

/*
    the purpose of read_memory() and write_memory()
    is to control reads/writes to restricted memory areas;
    tetris is stuck at copyright screen because it tries to write to 0xff80
*/

uint8_t read_u8(uint16_t addr) {
    uint8_t *mem = state->gameboy_memory;
    return mem[addr];
}

uint16_t read_u16(uint16_t addr) {    
    uint8_t *mem = state->gameboy_memory;
    return ((read_u8(addr+1) << 8) | read_u8(addr));
}

void    write_u8(uint16_t addr, uint8_t data) {    
    uint8_t *mem = state->gameboy_memory;
    mem[addr] = data;    
}

void    write_u16(uint16_t addr, uint16_t data) {    
    uint8_t *mem = state->gameboy_memory;
    (void)write_u8(addr, (uint8_t) data & 0xff);
    (void)write_u8(addr + 1, (uint8_t) (data >> 8));
}
