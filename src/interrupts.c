#include "gb.h"
#include "cpu.h"
#include "hardware.h"

int interrupt_step(struct gameboy *gb) {
    int i;

    if (gb->cpu.step == 0) {
        gb->cpu.step = 1;
        gb->cpu.ime = 0;
    } else if (gb->cpu.step == 1) {
        gb->cpu.step = 2;
    } else if (gb->cpu.step == 2) {
        gb->cpu.step = 3;
        gb->cpu.sp--;
        write_u8(gb, gb->cpu.sp, gb->cpu.pc >> 8);
    } else if (gb->cpu.step == 3) {
        gb->cpu.step = 4;
        gb->cpu.interrupt = gb->memory[rIE] & gb->memory[rIF] & 31;
        gb->cpu.sp--;
        write_u8(gb, gb->cpu.sp, gb->cpu.pc & 255);
    } else if (gb->cpu.step == 4) {
        gb->cpu.step = gb->cpu.pc = 0;
        gb->cpu.state = RUNNING;

        for (i = 0; i < 5; i++) {
            if (gb->cpu.interrupt & (1 << i)) {
                gb->memory[rIF] &= ~(1 << i);
                gb->cpu.pc = 0x40 + (i << 3);
                break ;
            }
        }
    }

    return gb->cpu.step;
}

int interrupts_update(struct gameboy *gb) {
    if ((gb->cpu.stat_irq) && (!gb->cpu.stat_irq_old)) {
        gb->memory[rIF] |= IEF_LCDC;
    }

    gb->cpu.stat_irq_old = gb->cpu.stat_irq;

    if (gb->memory[rIE] & gb->memory[rIF] & 31) {
        gb->cpu.state = RUNNING;
    }

    if (gb->cpu.ime_scheduled) {
        gb->cpu.ime_scheduled = false;

        if (!gb->cpu.ime) {
            gb->cpu.ime = true;
            return 0;
        }
    }

    if (!gb->cpu.ime) {
        return 0;
    }

    if ((gb->memory[rIE] & gb->memory[rIF] & 31) != 0) {
        gb->cpu.state = INTERRUPT_DISPATCH;
    }

    return gb->cpu.state;
}
