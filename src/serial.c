#include "gb.h"

void serial_data(uint8_t data) {
    gb_mem[0xff01] = data;
}

void serial_control(uint8_t data) {
    gb_mem[0xff02] = data & 0x81;
    if ((gb_mem[0xff02] & 0x81) == 0x81) {
        gb_mem[0xff01] = 0xff;
        gb_mem[0xff02] &= 1;
        gb_mem[0xff0f] |= 8;
    }
}
