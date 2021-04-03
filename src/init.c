#include "gb.h"
#include "hardware.h"

/* http://gbdev.gg8.se/wiki/articles/Power_Up_Sequence */

void set_initial_register_values() {
    t_r16 *r16 = state->gameboy_registers;

    r16->AF = 0x01b0;
    r16->BC = 0x0013;
    r16->DE = 0x00d8;
    r16->HL = 0x014d;
    r16->SP = 0xfffe;
    r16->PC = 0x0100;

    gb_mem[0xff00] = 0xcf;  /* P1   */
    gb_mem[rSB] = 0xff;

    gb_mem[0xff04] = 0x42;  /* DIV  */
    gb_mem[0xff05] = 0x00;  /* TIMA */
    gb_mem[0xff06] = 0x00;  /* TMA  */
    gb_mem[0xff07] = 0x00;  /* TAC  */

    gb_mem[0xff10] = 0x80;  /* NR10 */
    gb_mem[0xff11] = 0xbf;  /* NR11 */
    gb_mem[0xff12] = 0xf3;  /* NR12 */
    gb_mem[0xff14] = 0xbf;  /* NR14 */
    gb_mem[0xff16] = 0x3f;  /* NR21 */
    gb_mem[0xff17] = 0x00;  /* NR22 */
    gb_mem[0xff19] = 0xbf;  /* NR24 */
    gb_mem[0xff1a] = 0x7f;  /* NR30 */
    gb_mem[0xff1b] = 0xff;  /* NR31 */
    gb_mem[0xff1c] = 0x9f;  /* NR32 */
    gb_mem[0xff1e] = 0xbf;  /* NR33 */
    gb_mem[0xff20] = 0xff;  /* NR41 */
    gb_mem[0xff21] = 0x00;  /* NR42 */
    gb_mem[0xff22] = 0x00;  /* NR43 */
    gb_mem[0xff23] = 0xbf;  /* NR44 */
    gb_mem[0xff24] = 0x77;  /* NR50 */
    gb_mem[0xff25] = 0xf3;  /* NR51 */
    gb_mem[0xff26] = 0xf1;  /* NR52 */

    gb_mem[0xff40] = 0x91;  /* LCDC */
    gb_mem[0xff42] = 0x00;  /* SCY  */
    gb_mem[0xff43] = 0x00;  /* SCX  */
    gb_mem[0xff45] = 0x00;  /* LYC  */
    gb_mem[0xff47] = 0xfc;  /* BGP  */
    gb_mem[0xff48] = 0xff;  /* OBP0 */
    gb_mem[0xff49] = 0xff;  /* OBP1 */
    gb_mem[0xff4a] = 0x00;  /* WY   */
    gb_mem[0xff4b] = 0x00;  /* WX   */
    gb_mem[0xffff] = 0x00;  /* IE   */
}
