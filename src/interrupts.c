#include "gb.h"
#include "cpu.h"
#include "hardware.h"

int interrupt_step(struct gameboy *gb) {
    static int i, step, interrupt;

    if (step == 0) {
        gb->cpu.ime = false;
        ++step;
    } else if (step == 1) {
        ++step;
    } else if (step == 2) {
        write_u8(gb, --(gb->cpu.sp), gb->cpu.pc >> 8);
        ++step;
    } else if (step == 3) {
        interrupt = gb->memory[rIE] & gb->memory[rIF] & 31;
        write_u8(gb, --(gb->cpu.sp), gb->cpu.pc & 255);
        ++step;
    } else if (step == 4) {
        step = gb->cpu.pc = gb->interrupt_dispatch = 0;

        for (i = 0; i < 5; i++) {
            if (interrupt & (1 << i)) {
                gb->memory[rIF] &= ~(1 << i);
                gb->cpu.pc = 0x40 + (i << 3);
                break ;
            }
        }
    }

    return step;
}

int interrupts_update(struct gameboy *gb) {
    static bool stat_irq_old;

    if ((gb->stat_irq) && (!stat_irq_old)) {
        gb->memory[rIF] |= IEF_LCDC;
    }

    stat_irq_old = gb->stat_irq;

    if (gb->memory[rIE] & gb->memory[rIF] & 31) {
        gb->halt = false;
    }

    if (gb->instr_cycles) {
        return 0;
    }

    if (gb->interrupt_dispatch) {
        return 0;
    }

    if (gb->ime_scheduled) {
        gb->ime_scheduled = false;

        if (!gb->ime) {
            gb->ime = true;
            return 0;
        }
    }

    if (!gb->ime) {
        return 0;
    }

    gb->interrupt_dispatch = (gb->memory[rIE] & gb->memory[rIF] & 31) != 0;
    return gb->interrupt_dispatch;
}
