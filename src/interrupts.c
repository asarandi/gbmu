#include "gb.h"

#define IS_INT40_ENABLED   (gb_mem[0xffff] &  1 ? 1:0)      /* v-blank */
#define IS_INT48_ENABLED   (gb_mem[0xffff] &  2 ? 1:0)      /* lcd     */
#define IS_INT50_ENABLED   (gb_mem[0xffff] &  4 ? 1:0)      /* timer   */
#define IS_INT58_ENABLED   (gb_mem[0xffff] &  8 ? 1:0)      /* serial  */
#define IS_INT60_ENABLED   (gb_mem[0xffff] & 16 ? 1:0)      /* joypad  */

#define IS_INT40_REQUESTED (gb_mem[0xff0f] &  1 ? 1:0)
#define IS_INT48_REQUESTED (gb_mem[0xff0f] &  2 ? 1:0)
#define IS_INT50_REQUESTED (gb_mem[0xff0f] &  4 ? 1:0)
#define IS_INT58_REQUESTED (gb_mem[0xff0f] &  8 ? 1:0)
#define IS_INT60_REQUESTED (gb_mem[0xff0f] & 16 ? 1:0)

void    service_interrupt(uint8_t *gb_mem, t_state *state, void *registers,
        uint16_t interrupt_address, uint8_t clear_bit)
{
    t_r16   *r16    = registers;
    r16->SP         -= 2 ;

    write_u16(r16->SP, r16->PC);

    r16->PC = interrupt_address;

    state->interrupts_enabled = false;
    gb_mem[0xff0f] &= (~clear_bit);

    state->interrupt_cycles = 20;
/*    printf("interrupt %04x\n", r16->PC); */
}

void    interrupts_update(uint8_t *gb_mem, t_state *state, void *registers)
{
    if (state->interrupt_cycles) {
        state->interrupt_cycles -= 4;
        return ;
    }
    if (gb_mem[0xffff] & gb_mem[0xff0f] & 0x1f) {
        state->halt = false;
/*  if (state->halt)
        state->debug = true ;   */
    }
    if (!state->interrupts_enabled)
        return ;

    if (IS_INT40_ENABLED && IS_INT40_REQUESTED)
        (void)service_interrupt(gb_mem, state, registers, 0x40,  1);
    else if (IS_INT48_ENABLED && IS_INT48_REQUESTED)
        (void)service_interrupt(gb_mem, state, registers, 0x48,  2);
    else if (IS_INT50_ENABLED && IS_INT50_REQUESTED)
        (void)service_interrupt(gb_mem, state, registers, 0x50,  4);
    else if (IS_INT58_ENABLED && IS_INT58_REQUESTED)
        (void)service_interrupt(gb_mem, state, registers, 0x58,  8);
    else if (IS_INT60_ENABLED && IS_INT60_REQUESTED)
        (void)service_interrupt(gb_mem, state, registers, 0x60, 16);
}
