#include "gb.h"
#include "endian.h"

// https://gbdev.io/pandocs/MBC3.html#mbc3
// https://github.com/aaaaaa123456789/rtc3test/blob/master/tests.md
// https://bgb.bircd.org/rtcsave.html
//
//  08h  RTC S   Seconds   0-59 (0-3Bh)
//  09h  RTC M   Minutes   0-59 (0-3Bh)
//  0Ah  RTC H   Hours     0-23 (0-17h)
//  0Bh  RTC DL  Lower 8 bits of Day Counter (0-FFh)
//  0Ch  RTC DH  Upper 1 bit of Day Counter, Carry Bit, Halt Flag
//        Bit 0  Most significant bit of Day Counter (Bit 8)
//        Bit 6  Halt (0=Active, 1=Stop Timer)
//        Bit 7  Day Counter Carry Bit (1=Counter Overflow)

// FIXME: remove strings
int rtc_update_to_current(struct gameboy *gb) {
    struct rtc *rtc = &(gb->cartridge.rtc);
    uint32_t t, d;
    t = time(NULL);

    if (t < rtc->time) {
        fprintf(stderr, "rtc time is in the future?\n");
        fflush(stderr);
        return 0;
    }

    d = t - rtc->time;
    d += rtc->hidden[0];
    d += rtc->hidden[1] * 60;
    d += rtc->hidden[2] * 3600;
    d += rtc->hidden[3] * 86400;
    d += rtc->hidden[4] & 1 ? 256 * 86400 : 0;
    rtc->hidden[0] = d % 60;
    rtc->hidden[1] = (d / 60) % 60;
    rtc->hidden[2] = (d / 3600) % 24;
    rtc->hidden[3] = (d / 86400) % 256;
    rtc->hidden[4] |= (d / 86400) > 255 ? 1 : 0;
    rtc->hidden[4] |= (d / 86400) > 511 ? 0x80 : 0;
    rtc->time = t;
    return 1;
}

int rtc_deserialize(struct gameboy *gb) {
    struct rtc *rtc = &(gb->cartridge.rtc);
    int i;

    for (i = 0; i < 5; i++) {
        rtc->hidden[i] = read_le32(&(rtc->buf[i * 4]));
        rtc->latched[i] = read_le32(&(rtc->buf[i * 4 + 20]));
    }

    rtc->time = read_le32(&(rtc->buf[40]));
    return rtc_update_to_current(gb);
}

int rtc_serialize(struct gameboy *gb) {
    struct rtc *rtc = &(gb->cartridge.rtc);
    int i;
    gb->cartridge.rtc.time = time(NULL);

    if (!rtc_update_to_current(gb)) {
        return 0;
    }

    (void)memset(rtc->buf, 0, sizeof(rtc->buf));

    for (i = 0; i < 5; i++) {
        (void)write_le32(&(rtc->buf[i * 4]), rtc->hidden[i]);
        (void)write_le32(&(rtc->buf[i * 4 + 20]), rtc->latched[i]);
    }

    (void)write_le32(&(rtc->buf[40]), rtc->time);
    return 1;
}

// FIXME: calculate increment, divisor dynamically
int rtc_tick(struct gameboy *gb) {
    struct rtc *rtc = &(gb->cartridge.rtc);
    rtc->ticks += RTC_TICK_INCREMENT;
    rtc->ticks %= RTC_TICK_DIVISOR;

    if (rtc->ticks) {
        return 1;
    }

// timer halt
    if (rtc->hidden[4] & 0x40) {
        return 1;
    }

// seconds
    rtc->hidden[0]++;
    rtc->hidden[0] &= 63;

    if (rtc->hidden[0] == 60) {
        rtc->hidden[0] = 0;
        rtc->hidden[1]++;
    }

// minutes
    rtc->hidden[1] &= 63;

    if (rtc->hidden[1] == 60) {
        rtc->hidden[1] = 0;
        rtc->hidden[2]++;
    }

// hours
    rtc->hidden[2] &= 31;

    if (rtc->hidden[2] != 24) {
        return 1;
    }

// days low
    rtc->hidden[2] = 0;
    rtc->hidden[3]++;
    rtc->hidden[3] &= 255;

    if (rtc->hidden[3] != 0) {
        return 1;
    }

// days high
    rtc->hidden[4] ^= 1;
    rtc->hidden[4] |= (rtc->hidden[4] & 1) ? 0 : 128;
    rtc->hidden[4] &= 193;
    return 1;
}
