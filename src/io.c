#include "gb.h"
#include "hardware.h"

const struct io_register io_registers[] = {
    {"rP1",     0xff00, 0b11000000},
    {"rSB",     0xff01, 0b00000000},
    {"rSC",     0xff02, 0b01111110},
    {"",        0xff03, 0b11111111},
    {"rDIV",    0xff04, 0b00000000},
    {"rTIMA",   0xff05, 0b00000000},
    {"rTMA",    0xff06, 0b00000000},
    {"rTAC",    0xff07, 0b11111000},
    {"",        0xff08, 0b11111111},
    {"",        0xff09, 0b11111111},
    {"",        0xff0a, 0b11111111},
    {"",        0xff0b, 0b11111111},
    {"",        0xff0c, 0b11111111},
    {"",        0xff0d, 0b11111111},
    {"",        0xff0e, 0b11111111},
    {"rIF",     0xff0f, 0b11100000},
    {"rNR10",   0xff10, 0b10000000},
    {"rNR11",   0xff11, 0b00000000},
    {"rNR12",   0xff12, 0b00000000},
    {"rNR13",   0xff13, 0b00000000},
    {"rNR14",   0xff14, 0b00000000},
    {"",        0xff15, 0b11111111},
    {"rNR21",   0xff16, 0b00000000},
    {"rNR22",   0xff17, 0b00000000},
    {"rNR23",   0xff18, 0b00000000},
    {"rNR24",   0xff19, 0b00000000},
    {"rNR30",   0xff1a, 0b01111111},
    {"rNR31",   0xff1b, 0b00000000},
    {"rNR32",   0xff1c, 0b10011111},
    {"rNR33",   0xff1d, 0b00000000},
    {"rNR34",   0xff1e, 0b00000000},
    {"",        0xff1f, 0b11111111},
    {"rNR41",   0xff20, 0b11000000},
    {"rNR42",   0xff21, 0b00000000},
    {"rNR43",   0xff22, 0b00000000},
    {"rNR44",   0xff23, 0b00111111},
    {"rNR50",   0xff24, 0b00000000},
    {"rNR51",   0xff25, 0b00000000},
    {"rNR52",   0xff26, 0b01110000},
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
    {"rLCDC",   0xff40, 0b00000000},
    {"rSTAT",   0xff41, 0b10000000},
    {"rSCY",    0xff42, 0b00000000},
    {"rSCX",    0xff43, 0b00000000},
    {"rLY",     0xff44, 0b00000000},
    {"rLYC",    0xff45, 0b00000000},
    {"rDMA",    0xff46, 0b00000000},
    {"rBGP",    0xff47, 0b00000000},
    {"rOBP0",   0xff48, 0b00000000},
    {"rOBP1",   0xff49, 0b00000000},
    {"rWY",     0xff4a, 0b00000000},
    {"rWX",     0xff4b, 0b00000000},
    {"",        0xff4c, 0b11111111},
    {"rKEY1",   0xff4d, 0b11111111},
    {"",        0xff4e, 0b11111111},
    {"rVBK",    0xff4f, 0b11111111},
    {"",        0xff50, 0b11111111},
    {"rHDMA1",  0xff51, 0b11111111},
    {"rHDMA2",  0xff52, 0b11111111},
    {"rHDMA3",  0xff53, 0b11111111},
    {"rHDMA4",  0xff54, 0b11111111},
    {"rHDMA5",  0xff55, 0b11111111},
    {"rRP",     0xff56, 0b11111111},
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
    {"rBCPS",   0xff68, 0b11111111},
    {"rBCPD",   0xff69, 0b11111111},
    {"rOCPS",   0xff6a, 0b11111111},
    {"rOCPD",   0xff6b, 0b11111111},
    {"",        0xff6c, 0b11111111},
    {"",        0xff6d, 0b11111111},
    {"",        0xff6e, 0b11111111},
    {"",        0xff6f, 0b11111111},
    {"rSVBK",   0xff70, 0b11111111},
    {"",        0xff71, 0b11111111},
    {"",        0xff72, 0b11111111},
    {"",        0xff73, 0b11111111},
    {"",        0xff74, 0b11111111},
    {"",        0xff75, 0b11111111},
    {"rPCM12",  0xff76, 0b11111111},
    {"rPCM34",  0xff77, 0b11111111},
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
    {"rIE",     0xffff, 0b00000000},
};

/* http://gbdev.gg8.se/wiki/articles/Power_Up_Sequence */

uint8_t io_read_u8(struct gameboy *gb, uint16_t addr) {
    uint8_t data, mask;
    mask = io_registers[addr & 255].mask;
    data = gb->memory[addr];

    switch (addr) {
    case rP1:
        data = joypad_read_u8(gb, addr);
        break ;

    case rSB:
    case rSC:
        data = serial_read_u8(gb, addr);
        break ;

    case rDIV:
    case rTIMA:
    case rTMA:
    case rTAC:
        data = timer_read_u8(gb, addr);
        break ;

    default:
        break ;
    }

    data |= mask;

    if ((addr >= 0xff10) && (addr < 0xff40)) {
        data = sound_read_u8(gb, addr);
    }

    return data;
}

void io_write_u8(struct gameboy *gb, uint16_t addr, uint8_t data) {
    (void)debug_log_io(gb, addr, data);

    switch (addr) {
    case rP1:
        (void)joypad_write_u8(gb, addr, data);
        return;

    case rSB:
    case rSC:
        (void)serial_write_u8(gb, addr, data);
        return;

    case rDIV:
    case rTIMA:
    case rTMA:
    case rTAC:
        (void)timer_write_u8(gb, addr, data);
        return;

    case rSTAT:
        if (gb->memory[rLCDC] & LCDCF_ON) {
            if ((gb->memory[rSTAT] & STATF_LCD) < 2) {
                gb->cpu.stat_irq |= true;
            }
        }

        data = 128 | (data & 0b01111000) | (gb->memory[rSTAT] & 7);
        break ;

    case rDMA:
        if (!gb->dma.clocks) {
            gb->dma.clocks = 8;
        }

        break ;

    case rPCM12:
    case rPCM34:
        return;

    default:
        break ;
    }

    if ((addr >= rNR10) && (addr < rNR10 + 0x30)) {
        (void)sound_write_u8(gb, addr, data);
        return;
    }

    gb->memory[addr] = data;
}
