#include "gb.h"

#define is_int40_enabled   (gb_mem[0xffff] &  1 ? 1:0)      //v-blank
#define is_int48_enabled   (gb_mem[0xffff] &  2 ? 1:0)      //lcd
#define is_int50_enabled   (gb_mem[0xffff] &  4 ? 1:0)      //timer
#define is_int58_enabled   (gb_mem[0xffff] &  8 ? 1:0)      //serial
#define is_int60_enabled   (gb_mem[0xffff] & 16 ? 1:0)      //joypad


#define is_int40_requested (gb_mem[0xff0f] &  1 ? 1:0)
#define is_int48_requested (gb_mem[0xff0f] &  2 ? 1:0)
#define is_int50_requested (gb_mem[0xff0f] &  4 ? 1:0)
#define is_int58_requested (gb_mem[0xff0f] &  8 ? 1:0)
#define is_int60_requested (gb_mem[0xff0f] & 16 ? 1:0)

void    service_interrupt(uint8_t *gb_mem, t_state *state, void *registers,
        uint16_t interrupt_address, uint8_t clear_bit)
{
    t_r16       *r16;
    t_r8        *r8;

    r16 = registers;
    r8 = registers;

    r16->SP -= 2 ;
    *(uint16_t *)&gb_mem[r16->SP] = r16->PC ;
    r16->PC = interrupt_address;

    state->cycles += 20;

    state->interrupts_enabled = false;
    gb_mem[0xff0f] &= (~clear_bit);
}

void    interrupts_update(uint8_t *gb_mem, t_state *state, void *registers)
{   
    if (!state->interrupts_enabled)
        return ;
    if (is_int40_enabled && is_int40_requested)
        return service_interrupt(gb_mem, state, registers, 0x40,  1);
    if (is_int48_enabled && is_int48_requested)
        return service_interrupt(gb_mem, state, registers, 0x48,  2);
    if (is_int50_enabled && is_int50_requested)
        return service_interrupt(gb_mem, state, registers, 0x50,  4);
    if (is_int58_enabled && is_int58_requested)        
        return service_interrupt(gb_mem, state, registers, 0x58,  8);
    if (is_int60_enabled && is_int60_requested)
        return service_interrupt(gb_mem, state, registers, 0x60, 16);
}
