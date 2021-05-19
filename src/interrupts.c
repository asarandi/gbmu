#include "gb.h"
#include "hardware.h"

int interrupt_step(uint8_t *mem, t_state *state, t_r16 *r16) {
    static int i, step, interrupt;

    if (step == 0) {
        state->ime = false;
        ++step;
    } else if (step == 1) {
        ++step;
    } else if (step == 2) {
        write_u8(--(r16->SP), r16->PC >> 8);
        ++step;
    } else if (step == 3) {
        interrupt = mem[rIE] & mem[rIF] & 31;
        write_u8(--(r16->SP), r16->PC & 255);
        ++step;
    } else if (step == 4) {
        step = r16->PC = state->interrupt_dispatch = 0;

        for (i = 0; i < 5; i++) {
            if (interrupt & (1 << i)) {
                mem[rIF] &= ~(1 << i);
                r16->PC = 0x40 + (i << 3);
                break ;
            }
        }
    }

    return step;
}

int interrupts_update(uint8_t *mem, t_state *state, t_r16 *r16) {
    (void)r16;
    static bool stat_irq_old;

    if ((state->stat_irq) && (!stat_irq_old)) {
        mem[rIF] |= IEF_LCDC;
    }

    stat_irq_old = state->stat_irq;

    if (mem[rIE] & mem[rIF] & 31) {
        state->halt = false;
    }

    if (state->instr_cycles) {
        return 0;
    }

    if (state->interrupt_dispatch) {
        return 0;
    }

    if (state->ime_scheduled) {
        state->ime_scheduled = false;

        if (!state->ime) {
            state->ime = true;
            return 0;
        }
    }

    if (!state->ime) {
        return 0;
    }

    state->interrupt_dispatch = (mem[rIE] & mem[rIF] & 31) != 0;
    return state->interrupt_dispatch;
}
