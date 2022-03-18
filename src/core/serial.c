#include "gb.h"
#include "hardware.h"

uint8_t serial_read_u8(struct gameboy *gb, uint16_t addr) {
    uint8_t res = 0xff;

    if (addr == rSB) {
        res = gb->memory[rSB];
    } else if (addr == rSC) {
        res = ((gb->memory[rSC] & 0x81) | 0x7e);
    }

    return res;
}

// send/receive 1 bit every 512 clock cycles
int serial_update(struct gameboy *p, struct gameboy *q) {
    static struct gameboy *transfer = NULL;
    bool bitflip, pb, qb;
    bitflip = (p->serial_cycles & (1 << 9)) !=
              ((p->serial_cycles + 4) & (1 << 9));
    p->serial_cycles += 4;

    if (!bitflip) {
        return 0;
    }

    if ((!transfer) && ((p->memory[rSC] & 0x81) == 0x81)) {
        transfer = p;
        p->serial_ctr = 8;
    }

    if (transfer != p) {
        return 1;
    }

    pb = (p->memory[rSB] >> 7) & 1;
    qb = q ? (q->memory[rSB] >> 7) & 1 : 1;
    p->memory[rSB] <<= 1;
    p->memory[rSB] |= qb;

    if (q) {
        q->memory[rSB] <<= 1;
        q->memory[rSB] |= pb;
    }

    if (--(p->serial_ctr) > 0) {
        return 2;
    }

    p->memory[rIF] |= IEF_SERIAL;
    p->memory[rSC] &= ~0x80;

    if (q) {
        q->memory[rIF] |= IEF_SERIAL;
        q->memory[rSC] &= ~0x80;
    }

    transfer = NULL;
    return 3;
}

void serial_write_u8(struct gameboy *gb, uint16_t addr, uint8_t data) {
    if (addr == rSB) {
        gb->memory[rSB] = data;
    } else if (addr == rSC) {
        gb->memory[rSC] = data & 0x81;
    }
}
