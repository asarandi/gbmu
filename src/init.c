#include "gb.h"
#include "hardware.h"

struct io_register io_registers[] = {
    {"rP1",     0xFF00, 0b11000000},
    {"rSB",     0xFF01, 0b00000000},
    {"rSC",     0xFF02, 0b01111110},
    {"",        0xff03, 0b11111111},
    {"rDIV",    0xFF04, 0b00000000},
    {"rTIMA",   0xFF05, 0b00000000},
    {"rTMA",    0xFF06, 0b00000000},
    {"rTAC",    0xFF07, 0b11111000},
    {"",        0xff08, 0b11111111},
    {"",        0xff09, 0b11111111},
    {"",        0xff0a, 0b11111111},
    {"",        0xff0b, 0b11111111},
    {"",        0xff0c, 0b11111111},
    {"",        0xff0d, 0b11111111},
    {"",        0xff0e, 0b11111111},
    {"rIF",     0xFF0F, 0b11100000},
    {"rNR10",   0xFF10, 0b10000000},
    {"rNR11",   0xFF11, 0b00000000},
    {"rNR12",   0xFF12, 0b00000000},
    {"rNR13",   0xFF13, 0b00000000},
    {"rNR14",   0xFF14, 0b00000000},
    {"",        0xff15, 0b11111111},
    {"rNR21",   0xFF16, 0b00000000},
    {"rNR22",   0xFF17, 0b00000000},
    {"rNR23",   0xFF18, 0b00000000},
    {"rNR24",   0xFF19, 0b00000000},
    {"rNR30",   0xFF1A, 0b01111111},
    {"rNR31",   0xFF1B, 0b00000000},
    {"rNR32",   0xFF1C, 0b10011111},
    {"rNR33",   0xFF1D, 0b00000000},
    {"rNR34",   0xFF1E, 0b00000000},
    {"",        0xff1f, 0b11111111},
    {"rNR41",   0xFF20, 0b11000000},
    {"rNR42",   0xFF21, 0b00000000},
    {"rNR43",   0xFF22, 0b00000000},
    {"rNR44",   0xFF23, 0b00111111},
    {"rNR50",   0xFF24, 0b00000000},
    {"rNR51",   0xFF25, 0b00000000},
    {"rNR52",   0xFF26, 0b01110000},
    {"",        0xff27, 0b11111111},
    {"",        0xff28, 0b11111111},
    {"",        0xff29, 0b11111111},
    {"",        0xff2a, 0b11111111},
    {"",        0xff2b, 0b11111111},
    {"",        0xff2c, 0b11111111},
    {"",        0xff2d, 0b11111111},
    {"",        0xff2e, 0b11111111},
    {"",        0xff2f, 0b11111111},
    {"WAVE0",   0xff30, 0b00000000},
    {"WAVE1",   0xff31, 0b00000000},
    {"WAVE2",   0xff32, 0b00000000},
    {"WAVE3",   0xff33, 0b00000000},
    {"WAVE4",   0xff34, 0b00000000},
    {"WAVE5",   0xff35, 0b00000000},
    {"WAVE6",   0xff36, 0b00000000},
    {"WAVE7",   0xff37, 0b00000000},
    {"WAVE8",   0xff38, 0b00000000},
    {"WAVE9",   0xff39, 0b00000000},
    {"WAVEA",   0xff3a, 0b00000000},
    {"WAVEB",   0xff3b, 0b00000000},
    {"WAVEC",   0xff3c, 0b00000000},
    {"WAVED",   0xff3d, 0b00000000},
    {"WAVEE",   0xff3e, 0b00000000},
    {"WAVEF",   0xff3f, 0b00000000},
    {"rLCDC",   0xFF40, 0b00000000},
    {"rSTAT",   0xFF41, 0b10000000},
    {"rSCY",    0xFF42, 0b00000000},
    {"rSCX",    0xFF43, 0b00000000},
    {"rLY",     0xFF44, 0b00000000},
    {"rLYC",    0xFF45, 0b00000000},
    {"rDMA",    0xFF46, 0b00000000},
    {"rBGP",    0xFF47, 0b00000000},
    {"rOBP0",   0xFF48, 0b00000000},
    {"rOBP1",   0xFF49, 0b00000000},
    {"rWY",     0xFF4A, 0b00000000},
    {"rWX",     0xFF4B, 0b00000000},
    {"",        0xff4c, 0b11111111},
    {"rKEY1",   0xFF4D, 0b11111111},
    {"",        0xff4e, 0b11111111},
    {"rVBK",    0xFF4F, 0b11111111},
    {"",        0xff50, 0b11111111},
    {"rHDMA1",  0xFF51, 0b11111111},
    {"rHDMA2",  0xFF52, 0b11111111},
    {"rHDMA3",  0xFF53, 0b11111111},
    {"rHDMA4",  0xFF54, 0b11111111},
    {"rHDMA5",  0xFF55, 0b11111111},
    {"rRP",     0xFF56, 0b11111111},
    {"",        0xff57, 0b11111111},
    {"",        0xff58, 0b11111111},
    {"",        0xff59, 0b11111111},
    {"",        0xff5a, 0b11111111},
    {"",        0xff5b, 0b11111111},
    {"",        0xff5c, 0b11111111},
    {"",        0xff5d, 0b11111111},
    {"",        0xff5e, 0b11111111},
    {"",        0xff5f, 0b11111111},
    {"",        0xff60, 0b11111111},
    {"",        0xff61, 0b11111111},
    {"",        0xff62, 0b11111111},
    {"",        0xff63, 0b11111111},
    {"",        0xff64, 0b11111111},
    {"",        0xff65, 0b11111111},
    {"",        0xff66, 0b11111111},
    {"",        0xff67, 0b11111111},
    {"rBCPS",   0xFF68, 0b11111111},
    {"rBCPD",   0xFF69, 0b11111111},
    {"rOCPS",   0xFF6A, 0b11111111},
    {"rOCPD",   0xFF6B, 0b11111111},
    {"",        0xff6c, 0b11111111},
    {"",        0xff6d, 0b11111111},
    {"",        0xff6e, 0b11111111},
    {"",        0xff6f, 0b11111111},
    {"rSVBK",   0xFF70, 0b11111111},
    {"",        0xff71, 0b11111111},
    {"",        0xff72, 0b11111111},
    {"",        0xff73, 0b11111111},
    {"",        0xff74, 0b11111111},
    {"",        0xff75, 0b11111111},
    {"rPCM12",  0xFF76, 0b11111111},
    {"rPCM34",  0xFF77, 0b11111111},
    {"",        0xff78, 0b11111111},
    {"",        0xff79, 0b11111111},
    {"",        0xff7a, 0b11111111},
    {"",        0xff7b, 0b11111111},
    {"",        0xff7c, 0b11111111},
    {"",        0xff7d, 0b11111111},
    {"",        0xff7e, 0b11111111},
    {"",        0xff7f, 0b11111111},
    {"",        0xff80, 0b00000000},
    {"",        0xff81, 0b00000000},
    {"",        0xff82, 0b00000000},
    {"",        0xff83, 0b00000000},
    {"",        0xff84, 0b00000000},
    {"",        0xff85, 0b00000000},
    {"",        0xff86, 0b00000000},
    {"",        0xff87, 0b00000000},
    {"",        0xff88, 0b00000000},
    {"",        0xff89, 0b00000000},
    {"",        0xff8a, 0b00000000},
    {"",        0xff8b, 0b00000000},
    {"",        0xff8c, 0b00000000},
    {"",        0xff8d, 0b00000000},
    {"",        0xff8e, 0b00000000},
    {"",        0xff8f, 0b00000000},
    {"",        0xff90, 0b00000000},
    {"",        0xff91, 0b00000000},
    {"",        0xff92, 0b00000000},
    {"",        0xff93, 0b00000000},
    {"",        0xff94, 0b00000000},
    {"",        0xff95, 0b00000000},
    {"",        0xff96, 0b00000000},
    {"",        0xff97, 0b00000000},
    {"",        0xff98, 0b00000000},
    {"",        0xff99, 0b00000000},
    {"",        0xff9a, 0b00000000},
    {"",        0xff9b, 0b00000000},
    {"",        0xff9c, 0b00000000},
    {"",        0xff9d, 0b00000000},
    {"",        0xff9e, 0b00000000},
    {"",        0xff9f, 0b00000000},
    {"",        0xffa0, 0b00000000},
    {"",        0xffa1, 0b00000000},
    {"",        0xffa2, 0b00000000},
    {"",        0xffa3, 0b00000000},
    {"",        0xffa4, 0b00000000},
    {"",        0xffa5, 0b00000000},
    {"",        0xffa6, 0b00000000},
    {"",        0xffa7, 0b00000000},
    {"",        0xffa8, 0b00000000},
    {"",        0xffa9, 0b00000000},
    {"",        0xffaa, 0b00000000},
    {"",        0xffab, 0b00000000},
    {"",        0xffac, 0b00000000},
    {"",        0xffad, 0b00000000},
    {"",        0xffae, 0b00000000},
    {"",        0xffaf, 0b00000000},
    {"",        0xffb0, 0b00000000},
    {"",        0xffb1, 0b00000000},
    {"",        0xffb2, 0b00000000},
    {"",        0xffb3, 0b00000000},
    {"",        0xffb4, 0b00000000},
    {"",        0xffb5, 0b00000000},
    {"",        0xffb6, 0b00000000},
    {"",        0xffb7, 0b00000000},
    {"",        0xffb8, 0b00000000},
    {"",        0xffb9, 0b00000000},
    {"",        0xffba, 0b00000000},
    {"",        0xffbb, 0b00000000},
    {"",        0xffbc, 0b00000000},
    {"",        0xffbd, 0b00000000},
    {"",        0xffbe, 0b00000000},
    {"",        0xffbf, 0b00000000},
    {"",        0xffc0, 0b00000000},
    {"",        0xffc1, 0b00000000},
    {"",        0xffc2, 0b00000000},
    {"",        0xffc3, 0b00000000},
    {"",        0xffc4, 0b00000000},
    {"",        0xffc5, 0b00000000},
    {"",        0xffc6, 0b00000000},
    {"",        0xffc7, 0b00000000},
    {"",        0xffc8, 0b00000000},
    {"",        0xffc9, 0b00000000},
    {"",        0xffca, 0b00000000},
    {"",        0xffcb, 0b00000000},
    {"",        0xffcc, 0b00000000},
    {"",        0xffcd, 0b00000000},
    {"",        0xffce, 0b00000000},
    {"",        0xffcf, 0b00000000},
    {"",        0xffd0, 0b00000000},
    {"",        0xffd1, 0b00000000},
    {"",        0xffd2, 0b00000000},
    {"",        0xffd3, 0b00000000},
    {"",        0xffd4, 0b00000000},
    {"",        0xffd5, 0b00000000},
    {"",        0xffd6, 0b00000000},
    {"",        0xffd7, 0b00000000},
    {"",        0xffd8, 0b00000000},
    {"",        0xffd9, 0b00000000},
    {"",        0xffda, 0b00000000},
    {"",        0xffdb, 0b00000000},
    {"",        0xffdc, 0b00000000},
    {"",        0xffdd, 0b00000000},
    {"",        0xffde, 0b00000000},
    {"",        0xffdf, 0b00000000},
    {"",        0xffe0, 0b00000000},
    {"",        0xffe1, 0b00000000},
    {"",        0xffe2, 0b00000000},
    {"",        0xffe3, 0b00000000},
    {"",        0xffe4, 0b00000000},
    {"",        0xffe5, 0b00000000},
    {"",        0xffe6, 0b00000000},
    {"",        0xffe7, 0b00000000},
    {"",        0xffe8, 0b00000000},
    {"",        0xffe9, 0b00000000},
    {"",        0xffea, 0b00000000},
    {"",        0xffeb, 0b00000000},
    {"",        0xffec, 0b00000000},
    {"",        0xffed, 0b00000000},
    {"",        0xffee, 0b00000000},
    {"",        0xffef, 0b00000000},
    {"",        0xfff0, 0b00000000},
    {"",        0xfff1, 0b00000000},
    {"",        0xfff2, 0b00000000},
    {"",        0xfff3, 0b00000000},
    {"",        0xfff4, 0b00000000},
    {"",        0xfff5, 0b00000000},
    {"",        0xfff6, 0b00000000},
    {"",        0xfff7, 0b00000000},
    {"",        0xfff8, 0b00000000},
    {"",        0xfff9, 0b00000000},
    {"",        0xfffa, 0b00000000},
    {"",        0xfffb, 0b00000000},
    {"",        0xfffc, 0b00000000},
    {"",        0xfffd, 0b00000000},
    {"",        0xfffe, 0b00000000},
    {"rIE",     0xFFFF, 0b00000000},
};

/* http://gbdev.gg8.se/wiki/articles/Power_Up_Sequence */

void set_initial_register_values(struct gameboy *gb) {
    gb->cpu.r8[0] = 0x00, gb->cpu.r8[1] = 0x13; // bc = 0x0013
    gb->cpu.r8[2] = 0x00, gb->cpu.r8[3] = 0x8d; // de = 0x00d8
    gb->cpu.r8[4] = 0x01, gb->cpu.r8[5] = 0x4d; // hl = 0x014d
    gb->cpu.r8[7] = 0x01, gb->cpu.r8[6] = 0xb0; // af = 0x01b0
    gb->cpu.sp = 0xfffe;
    gb->cpu.pc = 0x0100;
    gb->memory[rP1] = 0xcf;
    gb->memory[rSB] = 0x00;
    gb->memory[rDIV] = 0x00;
    gb->memory[rTIMA] = 0x00;
    gb->memory[rTMA] = 0x00;
    gb->memory[rTAC] = 0x00;
    gb->memory[rIF] = 0xe1;
    gb->memory[rNR10] = 0x80;
    gb->memory[rNR11] = 0xbf;
    gb->memory[rNR12] = 0xf3;
    gb->memory[rNR13] = 0xff;
    gb->memory[rNR14] = 0xbf;
    gb->memory[rNR21] = 0x3f;
    gb->memory[rNR22] = 0x00;
    gb->memory[rNR23] = 0xff;
    gb->memory[rNR24] = 0xbf;
    gb->memory[rNR30] = 0x7f;
    gb->memory[rNR31] = 0xff;
    gb->memory[rNR32] = 0x9f;
    gb->memory[rNR33] = 0xff;
    gb->memory[rNR34] = 0xbf;
    gb->memory[rNR41] = 0xff;
    gb->memory[rNR42] = 0x00;
    gb->memory[rNR43] = 0x00;
    gb->memory[rNR44] = 0xbf;
    gb->memory[rNR50] = 0x77;
    gb->memory[rNR51] = 0xf3;
    gb->memory[rNR52] = 0xf1;
    gb->memory[rLCDC] = 0x91;
    gb->memory[rSTAT] = 0x80;
    gb->memory[rSCY] = 0x00;
    gb->memory[rSCX] = 0x00;
    gb->memory[rLYC] = 0x00;
    gb->memory[rBGP] = 0xfc;
    gb->memory[rOBP0] = 0xff;
    gb->memory[rOBP1] = 0xff;
    gb->memory[rWY] = 0x00;
    gb->memory[rWX] = 0x00;
    gb->memory[rIE] = 0x00;
    uint8_t dmg_wave[] = {0x84, 0x40, 0x43, 0xaa, 0x2d, 0x78, 0x92, 0x3c,
                          0x60, 0x59, 0x59, 0xb0, 0x34, 0xb8, 0x2e, 0xda,
                         };
//    uint8_t cgb_wave[] =  {0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff,
//                           0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff,
//                          };
    (void)memcpy(gb->memory + _AUD3WAVERAM, dmg_wave, 16);
}

uint8_t io_read_u8(struct gameboy *gb, uint16_t addr) {
    uint8_t val, mask;
    mask = io_registers[addr & 255].mask;
    val = gb->memory[addr];

    switch (addr) {
    case rP1:
        val = joypad_read(gb);
        break ;

    case rSB:
    case rSC:
        val = serial_read_u8(gb, addr);
        break ;

    default:
        break ;
    }

    val |= mask;

    if ((addr >= 0xff10) && (addr < 0xff40)) {
        val = sound_read_u8(gb, addr);
    }

    return val;
}
