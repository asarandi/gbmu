#include "gb.h"
#include "hardware.h"

void interrupts_update(uint8_t *gb_mem, t_state *state, void *registers) {
    if (state->interrupt_cycles) {
        state->interrupt_cycles -= 4;
        return;
    }

    if (gb_mem[rIE] & gb_mem[rIF] & 0x1f) {
        state->halt = false;
    }

    if (!state->interrupts_enabled) {
        return;
    }

    struct tab {
        uint16_t addr;
        uint8_t interrupt;
    } tab[] = {

        {0x0040, IEF_VBLANK},
        {0x0048, IEF_LCDC},
        {0x0050, IEF_TIMER},
        {0x0058, IEF_SERIAL},
        {0x0060, IEF_HILO},
    };
    t_r16 *r16 = registers;

    for (int i = 0; i < 5; i++) {
        if (gb_mem[rIE] & gb_mem[rIF] & tab[i].interrupt) {
            r16->SP -= 2;
            write_u16(r16->SP, r16->PC);
            r16->PC = tab[i].addr;
            state->interrupts_enabled = false;
            gb_mem[rIF] &= ~tab[i].interrupt;
            state->interrupt_cycles = 20;
            return ;
        }
    }
}
