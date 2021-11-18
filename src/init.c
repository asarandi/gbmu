#include "gb.h"
#include "hardware.h"

int set_dmg_initial_memory_values(struct gameboy *gb) {
    int i;
    // hacktix/BullyGB
    const uint8_t dmg_initial_tile_data_at_0x8010[] = {
        0xf0, 0xf0, 0xfc, 0xfc, 0xfc, 0xfc, 0xf3, 0xf3,
        0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c,
        0xf0, 0xf0, 0xf0, 0xf0, 0x00, 0x00, 0xf3, 0xf3,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xcf, 0xcf,
        0x00, 0x00, 0x0f, 0x0f, 0x3f, 0x3f, 0x0f, 0x0f,
        0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0x0f, 0x0f,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf3, 0xf3,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0,
        0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0xff, 0xff,
        0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc3, 0xc3,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xfc,
        0xf3, 0xf3, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0,
        0x3c, 0x3c, 0xfc, 0xfc, 0xfc, 0xfc, 0x3c, 0x3c,
        0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3,
        0xf3, 0xf3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
        0xcf, 0xcf, 0xcf, 0xcf, 0xcf, 0xcf, 0xcf, 0xcf,
        0x3c, 0x3c, 0x3f, 0x3f, 0x3c, 0x3c, 0x0f, 0x0f,
        0x3c, 0x3c, 0xfc, 0xfc, 0x00, 0x00, 0xfc, 0xfc,
        0xfc, 0xfc, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0,
        0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf0, 0xf0,
        0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xff,
        0xcf, 0xcf, 0xcf, 0xcf, 0xcf, 0xcf, 0xc3, 0xc3,
        0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0xfc, 0xfc,
        0x3c, 0x42, 0xb9, 0xa5, 0xb9, 0xa5, 0x42, 0x3c,
    };

    for (i = 0; i < 200; i++) {
        gb->memory[0x8010 + i * 2] = dmg_initial_tile_data_at_0x8010[i];
    }

    const uint8_t dmg_initial_map_data_at_0x9904[] = {
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
        0x09, 0x0a, 0x0b, 0x0c, 0x19, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14,
        0x15, 0x16, 0x17, 0x18,
    };
    (void)memcpy(gb->memory + 0x9904, dmg_initial_map_data_at_0x9904, 44);
    const uint8_t dmg_initial_waveram_data[] = {
        0x84, 0x40, 0x43, 0xaa, 0x2d, 0x78, 0x92, 0x3c,
        0x60, 0x59, 0x59, 0xb0, 0x34, 0xb8, 0x2e, 0xda,
    };
    (void)memcpy(gb->memory + _AUD3WAVERAM, dmg_initial_waveram_data, 16);
    /*
        const uint8_t cgb_initial_waveram_data[] = {
            0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff,
            0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff,
        };
        (void)memcpy(gb->memory + _AUD3WAVERAM, cgb_initial_waveram_data, 16);
    */
    return 0;
}

int set_dmg_initial_register_values(struct gameboy *gb) {
    gb->ch[0].on = 1;
    gb->cartridge.romb0 = 1;
    gb->cartridge.last_write = 255; // rtc3
    gb->cartridge.rtc.hidden[4] = 0x80; // rtc3
    gb->cartridge.rtc.latched[4] = 0x80; // rtc3
    gb->serial_cycles = 0xabcc;
    gb->timer.div = 0xabcc;
    gb->cpu.r8[0] = 0x00, gb->cpu.r8[1] = 0x13; // bc = 0x0013
    gb->cpu.r8[2] = 0x00, gb->cpu.r8[3] = 0xd8; // de = 0x00d8
    gb->cpu.r8[4] = 0x01, gb->cpu.r8[5] = 0x4d; // hl = 0x014d
    gb->cpu.r8[7] = 0x01, gb->cpu.r8[6] = 0xb0; // af = 0x01b0
    gb->cpu.sp = 0xfffe;
    gb->cpu.pc = 0x0100;
    gb->memory[rP1] = 0xcf;
    gb->memory[rSB] = 0x00;
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
    return 0;
}

void dummy_run_hook(struct gameboy *gb) {
    (void)gb;
}

void dummy_write_hook(struct gameboy *gb, uint16_t addr, uint8_t data) {
    (void)gb;
    (void)addr;
    (void)data;
}


void io_init(struct gameboy *gb) {
    (void)memset(gb->memory + _RAM, 255, 0x2000);
    (void)memset(gb->ram_banks, 255, sizeof(gb->ram_banks));
    (void)set_dmg_initial_memory_values(gb);
    (void)set_dmg_initial_register_values(gb);

    if (!gb->testing_run_hook) {
        gb->testing_run_hook = &dummy_run_hook;
    }

    if (!gb->testing_write_hook) {
        gb->testing_write_hook = &dummy_write_hook;
    }
}

