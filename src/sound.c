#include "gb.h"
#include "hardware.h"

/* http://gbdev.gg8.se/wiki/articles/Sound_Controller */
/* http://gbdev.gg8.se/wiki/articles/Gameboy_sound_hardware */
/* https://ia801906.us.archive.org/19/items/GameBoyProgManVer1.1/GameBoyProgManVer1.1.pdf */

#define VOLUME_CLOCK            (4194304 /  64)
#define SWEEP_CLOCK             (4194304 / 128)
#define LENGTH_CLOCK            (4194304 / 256)
#define FREQUENCY_CLOCK         (4194304 / 512)
#define SAMPLE_CLOCK            (4194304 / SAMPLING_FREQUENCY)

struct s_sound {
    uint32_t cycles;
    uint32_t on;
    uint32_t sweep_time;
    uint32_t sweep_dir;
    uint32_t sweep_shift;
    uint32_t sweep_ctr;         //helper
    uint32_t duty;
    uint32_t length;
    uint32_t volume;
    uint32_t env_dir;
    uint32_t env_sweep;         //rename?
    uint32_t env_ctr;           //helper
    uint32_t is_len_counter;    //rename?
    uint32_t freq;
    uint32_t lfsr_width;
};
typedef struct s_sound t_sound;

t_sound s1, s2, s3, s4;         //globals

static int16_t tone_sample(t_sound *s) {
    uint32_t duties[4][8] = {
        {0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 1, 1, 1},
        {0, 1, 1, 1, 1, 1, 1, 0}
    };
    uint32_t ticks = 4194304 / (131072 / (2048 - s->freq));
    uint32_t idx = (s->cycles / (ticks >> 3)) & 7;
    return (INT16_MAX / 15) * s->volume * duties[s->duty][idx];
}

static int16_t wave_sample(t_sound *s) {
    uint32_t ticks = 4194304 / (65536 / (2048 - s->freq));
    uint32_t idx = (s->cycles / (ticks >> 5)) & 31;
    uint8_t nib = gb_mem[_AUD3WAVERAM + (idx >> 1)];
    nib = (idx & 1) ? (nib & 15) : (nib >> 4);

    switch (s->volume) {
    case 0:
        nib = 0;
        break;

    case 2:
        nib >>= 1;
        break;

    case 3:
        nib >>= 2;
        break;
    }

    return (INT16_MAX / 15) * nib;
}

static int16_t noise_sample(t_sound *s) {
    extern unsigned char noise7[], noise15[];
    uint32_t ticks, idx;
    int16_t sample;
    uint8_t *tab;

    if (!s->freq) {
        return 0;
    }

    ticks = 4194304 / s->freq;

    if (s->lfsr_width) {
        idx = (s->cycles / ticks) & 127;
        tab = noise7;
    } else {
        idx = (s->cycles / ticks) & 32767;
        tab = noise15;
    }

    sample = (tab[idx >> 3] >> (7 - (idx & 7))) & 1;
    return (INT16_MAX / 15) * s->volume * sample;
}

/*
    writes int16_t interleaved samples to `buf'
    returns 1 when `index' is greater than or equal to `size'
*/

static int write_sounds(uint8_t *buf, uint32_t size) {
    int32_t left, right, sample;
    static uint32_t index;

    if (!size) {
        return 1;
    }

    index %= size;
    left = right = 0;

    if (s1.on) {
        sample = tone_sample(&s1);
        left += (gb_mem[rAUDTERM] & AUDTERM_1_LEFT) ? sample : 0;
        right += (gb_mem[rAUDTERM] & AUDTERM_1_RIGHT) ? sample : 0;
    }

    if (s2.on) {
        sample = tone_sample(&s2);
        left += (gb_mem[rAUDTERM] & AUDTERM_2_LEFT) ? sample : 0;
        right += (gb_mem[rAUDTERM] & AUDTERM_2_RIGHT) ? sample : 0;
    }

    if (s3.on) {
        sample = wave_sample(&s3);
        left += (gb_mem[rAUDTERM] & AUDTERM_3_LEFT) ? sample : 0;
        right += (gb_mem[rAUDTERM] & AUDTERM_3_RIGHT) ? sample : 0;
    }

    if (s4.on) {
        sample = noise_sample(&s4);
        left += (gb_mem[rAUDTERM] & AUDTERM_4_LEFT) ? sample : 0;
        right += (gb_mem[rAUDTERM] & AUDTERM_4_RIGHT) ? sample : 0;
    }

    left >>= 2;
    left = (left / 7) * ((gb_mem[rAUDVOL] >> 4) & 7);
    right >>= 2;
    right = (right / 7) * (gb_mem[rAUDVOL] & 7);
    *(int16_t *) &buf[index] = (int16_t)left;
    *(int16_t *) &buf[index + 2] = (int16_t)right;
    /* one frame == 2 sixteen bit samples: L, R */
    index += 4;
    return index >= size;
}

static void volume_tick(t_sound *s) {
    if ((!s->on) || (!s->env_sweep)) {
        return;
    }

    s->env_ctr++;

    if (s->env_ctr < s->env_sweep) {
        return;
    }

    s->env_ctr -= s->env_sweep;

    if ((s->env_dir) && (s->volume < 15)) {
        s->volume++;
    }

    if ((!s->env_dir) && (s->volume > 0)) {
        s->volume--;
    }
}

static void length_tick(t_sound *s, uint32_t mask) {
    if (!s->is_len_counter) {
        return;
    }

    s->length = (s->length + 1) & mask;

    if ((s->on) && (s->length == 0)) {
        s->on = 0;
    }
}

static void sweep_calc(t_sound *s) {
    uint32_t shadow_freq = s->freq;

    if (s->sweep_dir) {
        shadow_freq -= shadow_freq >> s->sweep_shift;
    } else {
        shadow_freq += shadow_freq >> s->sweep_shift;
    }

    if (shadow_freq > 2047) {
        s->on = 0;
        shadow_freq = s->freq;
    }

    s->freq = shadow_freq;
    gb_mem[rAUD1HIGH] = (gb_mem[rAUD1HIGH] & 0b11111000) | (s->freq >> 8);
    gb_mem[rAUD1LOW] = s->freq & 255;
}

static void sweep_tick(t_sound *s) {
    if ((!s->on) || (!s->sweep_time) || (!s->sweep_shift)) {
        return;
    }

    s->sweep_ctr++;

    if (s->sweep_ctr < s->sweep_time) {
        return;
    }

    s->sweep_ctr -= s->sweep_time;
    return sweep_calc(s);
}

int sound_update(uint8_t *gb_mem, t_state *state, int cycles) {
    static int once;

    if (!once) {
        once = s1.on = 1;
    }

    static uint32_t volume, sweep, length, samples;
    s1.cycles += cycles;
    s2.cycles += cycles;
    s3.cycles += cycles;
    s4.cycles += cycles;
    volume += cycles;

    if (volume >= VOLUME_CLOCK) {
        volume -= VOLUME_CLOCK;
        volume_tick(&s1);
        volume_tick(&s2);
        volume_tick(&s4);
    }

    sweep += cycles;

    if (sweep >= SWEEP_CLOCK) {
        sweep -= SWEEP_CLOCK;
        sweep_tick(&s1);
    }

    length += cycles;

    if (length >= LENGTH_CLOCK) {
        length -= LENGTH_CLOCK;
        length_tick(&s1, 63);
        length_tick(&s2, 63);
        length_tick(&s3, 255);
        length_tick(&s4, 63);
    }

    gb_mem[rAUDENA] = (gb_mem[rAUDENA] & 128) | (s1.on << 0) | (s2.on << 1) |
                      (s3.on << 2) | (s4.on << 3);
    samples += cycles;

    if (samples >= SAMPLE_CLOCK) {
        samples -= SAMPLE_CLOCK;
        return write_sounds(state->sound_buf, SOUND_BUF_SIZE);
    }

    return 0;
}

uint8_t sound_read_u8(uint16_t addr) {
    switch (addr) {
    case rAUDENA:
        return (gb_mem[rAUDENA] & 128) | (s1.on << 0) | (s2.on << 1) | (s3.on << 2) |
               (s4.on << 3);

    default:
        return gb_mem[addr];
    }
}

void sound_write_u8(uint16_t addr, uint8_t data) {
    if (addr != rAUDENA) {
        if ((gb_mem[rAUDENA] & AUDENA_ON) == 0) {
            return;      /*ignore all writes when sound off*/
        }
    }

    switch (addr) {
    case rAUD1SWEEP:    // rNR10
        gb_mem[rAUD1SWEEP] = data;
        s1.sweep_time = (data >> 4) & 7;        // 3 bits 6-4
        s1.sweep_dir = (data >> 3) & 1;         // 0 = add, 1 = sub
        s1.sweep_shift = data & 7;              // 3 bits 2-0
        break;

    case rAUD1LEN:      // rNR11
        gb_mem[rAUD1LEN] = data;
        s1.duty = (data >> 6) & 3;              // 2 bits 7-6
        s1.length = data & 63;                  // 6 bits 5-0
        break;

    case rAUD1ENV:      // rNR12
        gb_mem[rAUD1ENV] = data;
        s1.volume = (data >> 4) & 15;           // 4 bits 7-4
        s1.env_dir = (data >> 3) & 1;           // 0 = sub, 1 = add
        s1.env_sweep = data & 7;
        s1.on = (gb_mem[rAUD1ENV] >> 4) != 0;
        break;

    case rAUD1LOW:      // rNR13
        gb_mem[rAUD1LOW] = data;
        s1.freq = ((gb_mem[rAUD1HIGH] & 7) << 8) | gb_mem[rAUD1LOW];
        break;

    case rAUD1HIGH:     // rNR14
        gb_mem[rAUD1HIGH] = data;
        s1.freq = ((gb_mem[rAUD1HIGH] & 7) << 8) | gb_mem[rAUD1LOW];
        s1.is_len_counter = (data >> 6) & 1;    // 1 = counter, 0 = continuous

        if (data & 128) {
            // trigger
            if (!s1.on) {
                s1.cycles = 0;
                s1.sweep_ctr = 0;
                s1.env_ctr = 0;
            }

            if ((s1.sweep_time) && (s1.sweep_shift)) {
                sweep_calc(&s1);
            }

            s1.on = (gb_mem[rAUD1ENV] >> 4) != 0;
        }

        break;

    case rAUD2LEN:      // rNR21
        gb_mem[rAUD2LEN] = data;
        s2.duty = (data >> 6) & 3;              // 2 bits 7-6
        s2.length = data & 63;                  // 6 bits 5-0
        break;

    case rAUD2ENV:      // rNR22
        gb_mem[rAUD2ENV] = data;
        s2.volume = (data >> 4) & 15;           // 4 bits 7-4
        s2.env_dir = (data >> 3) & 1;           // 0 = sub, 1 = add
        s2.env_sweep = data & 7;
        s2.on = (gb_mem[rAUD2ENV] >> 4) != 0;
        break;

    case rAUD2LOW:      // rNR23
        gb_mem[rAUD2LOW] = data;
        s2.freq = ((gb_mem[rAUD2HIGH] & 7) << 8) | gb_mem[rAUD2LOW];
        break;

    case rAUD2HIGH:     // rNR24
        gb_mem[rAUD2HIGH] = data;
        s2.freq = ((gb_mem[rAUD2HIGH] & 7) << 8) | gb_mem[rAUD2LOW];
        s2.is_len_counter = (data >> 6) & 1;

        if (data & 128) {
            // trigger
            if (!s2.on) {
                s2.cycles = 0;
                s2.env_ctr = 0;
            }

            s2.on = (gb_mem[rAUD2ENV] >> 4) != 0;
        }

        break;

    case rAUD3ENA:      // rNR30
        gb_mem[rAUD3ENA] = data;
        s3.on = (gb_mem[rAUD3ENA] & 128) != 0;
        break;

    case rAUD3LEN:      // rNR31
        gb_mem[rAUD3LEN] = data;
        s3.length = data;
        break;

    case rAUD3LEVEL:    // rNR32
        gb_mem[rAUD3LEVEL] = data;
        s3.volume = (data >> 5) & 3;
        break;

    case rAUD3LOW:      // rNR33
        gb_mem[rAUD3LOW] = data;
        s3.freq = ((gb_mem[rAUD3HIGH] & 7) << 8) | gb_mem[rAUD3LOW];
        break;

    case rAUD3HIGH:     // rNR34
        gb_mem[rAUD3HIGH] = data;
        s3.freq = ((gb_mem[rAUD3HIGH] & 7) << 8) | gb_mem[rAUD3LOW];
        s3.is_len_counter = (data >> 6) & 1;

        if (data & 128) {
            // trigger
            if (!s3.on) {
                s3.cycles = 0;
            }

            s3.on = (gb_mem[rAUD3ENA] & 128) != 0;
        }

        break;

    case rAUD4LEN:      // rNR41
        gb_mem[rAUD4LEN] = data;
        s4.length = data & 63;
        break;

    case rAUD4ENV:      // rNR42
        gb_mem[rAUD4ENV] = data;
        s4.volume = (data >> 4) & 15;           // 4 bits 7-4
        s4.env_dir = (data >> 3) & 1;           // 0 = sub, 1 = add
        s4.env_sweep = data & 7;
        s4.on = (gb_mem[rAUD4ENV] >> 4) != 0;
        break;

    case rAUD4POLY:     // rNR43
        gb_mem[rAUD4POLY] = data;
        uint32_t f = 524288, shift, ratio;
        uint32_t tab[] = {f * 2, f, f / 2, f / 3, f / 4, f / 5, f / 6, f / 7};
        s4.lfsr_width = (data >> 3) & 1;        // 0 = 15 bits, 1 = 7 bits
        shift = (data >> 4) & 15;
        ratio = data & 7;
        s4.freq = tab[ratio] >> (shift + 1);

        if (shift >= 14) {
            s4.freq = 0;
        }

        break;

    case rAUD4GO:       // rNR44
        gb_mem[rAUD4GO] = data;
        s4.is_len_counter = (data >> 6) & 1;

        if (data & 128) {
            s4.env_ctr = 0;
            s4.cycles = 0;
            s4.on = (gb_mem[rAUD4ENV] >> 4) != 0;
        }

        break;

    case rAUDVOL:       // rNR50
        gb_mem[rAUDVOL] = data;
        break;

    case rAUDTERM:      // rNR51
        gb_mem[rAUDTERM] = data;
        break;

    case rAUDENA:       // rNR52
        gb_mem[rAUDENA] = data & 128;

        if ((gb_mem[rAUDENA] & 128) == 0) {
            s1.on = s2.on = s3.on = s4.on = 0;
        }

        break;

    default:
        gb_mem[addr] = data;
    }
}

unsigned char noise7[] = {
    0xfe, 0x04, 0x18, 0x51, 0xe4, 0x59, 0xd4, 0xfa,
    0x1c, 0x49, 0xb5, 0xbd, 0x8d, 0x2e, 0xe6, 0x55
};
unsigned int noise7_len = 16;

unsigned char noise15[] = {
    0xff, 0xfe, 0x00, 0x04, 0x00, 0x18, 0x00, 0x50,
    0x01, 0xe0, 0x04, 0x40, 0x19, 0x80, 0x55, 0x01,
    0xfe, 0x04, 0x04, 0x18, 0x18, 0x50, 0x51, 0xe1,
    0xe4, 0x44, 0x59, 0x99, 0xd5, 0x54, 0xff, 0xfa,
    0x00, 0x1c, 0x00, 0x48, 0x01, 0xb0, 0x05, 0xa0,
    0x1d, 0xc0, 0x4c, 0x81, 0xab, 0x05, 0xfa, 0x1c,
    0x1c, 0x48, 0x49, 0xb1, 0xb5, 0xa5, 0xbd, 0xdd,
    0x8c, 0xcd, 0x2a, 0xae, 0xff, 0xe6, 0x00, 0x54,
    0x01, 0xf8, 0x04, 0x10, 0x18, 0x60, 0x51, 0x41,
    0xe7, 0x84, 0x51, 0x19, 0xe6, 0x54, 0x55, 0xf9,
    0xfc, 0x14, 0x08, 0x78, 0x31, 0x10, 0xa6, 0x63,
    0xd5, 0x48, 0xff, 0xb2, 0x01, 0xac, 0x05, 0xe8,
    0x1c, 0x70, 0x49, 0x21, 0xb6, 0xc5, 0xb6, 0x9d,
    0xb7, 0x4d, 0xb3, 0xad, 0xa9, 0xed, 0xf4, 0x6c,
    0x39, 0x68, 0x97, 0x73, 0x73, 0x2b, 0x2a, 0xfa,
    0xfe, 0x1e, 0x04, 0x44, 0x19, 0x98, 0x55, 0x51,
    0xff, 0xe4, 0x00, 0x58, 0x01, 0xd0, 0x04, 0xe0,
    0x1a, 0x40, 0x5d, 0x81, 0xcd, 0x04, 0xae, 0x1b,
    0xe4, 0x58, 0x59, 0xd1, 0xd4, 0xe4, 0xfa, 0x5a,
    0x1d, 0xdc, 0x4c, 0xc9, 0xaa, 0xb5, 0xff, 0xbc,
    0x01, 0x88, 0x05, 0x30, 0x1e, 0xa0, 0x47, 0xc1,
    0x90, 0x85, 0x63, 0x1f, 0x4a, 0x43, 0xbd, 0x89,
    0x8d, 0x35, 0x2e, 0xbe, 0xe7, 0x86, 0x51, 0x15,
    0xe6, 0x7c, 0x55, 0x09, 0xfe, 0x34, 0x04, 0xb8,
    0x1b, 0x90, 0x59, 0x61, 0xd7, 0x44, 0xf3, 0x9a,
    0x29, 0x5c, 0xf7, 0xca, 0x30, 0xbc, 0xa3, 0x8b,
    0xc9, 0x38, 0xb6, 0x93, 0xb7, 0x69, 0xb3, 0x75,
    0xab, 0x3d, 0xfa, 0x8c, 0x1f, 0x28, 0x42, 0xf1,
    0x8e, 0x25, 0x24, 0xde, 0xda, 0xc6, 0xde, 0x96,
    0xc7, 0x76, 0x93, 0x37, 0x6a, 0xb3, 0x7f, 0xab,
    0x01, 0xfa, 0x04, 0x1c, 0x18, 0x48, 0x51, 0xb1,
    0xe5, 0xa4, 0x5d, 0xd9, 0xcc, 0xd4, 0xaa, 0xfb,
    0xfe, 0x18, 0x04, 0x50, 0x19, 0xe0, 0x54, 0x41,
    0xf9, 0x84, 0x15, 0x18, 0x7e, 0x51, 0x05, 0xe6,
    0x1c, 0x54, 0x49, 0xf9, 0xb4, 0x15, 0xb8, 0x7d,
    0x91, 0x0d, 0x66, 0x2f, 0x54, 0xe3, 0xfa, 0x48,
    0x1d, 0xb0, 0x4d, 0xa1, 0xad, 0xc5, 0xec, 0x9c,
    0x6b, 0x49, 0x7b, 0xb7, 0x19, 0xb2, 0x55, 0xad,
    0xfd, 0xec, 0x0c, 0x68, 0x29, 0x70, 0xf7, 0x22,
    0x32, 0xcc, 0xae, 0xab, 0xe7, 0xf8, 0x50, 0x11,
    0xe0, 0x64, 0x41, 0x59, 0x87, 0xd5, 0x10, 0xfe,
    0x62, 0x05, 0x4c, 0x1f, 0xa8, 0x41, 0xf1, 0x84,
    0x25, 0x18, 0xde, 0x52, 0xc5, 0xee, 0x9c, 0x67,
    0x49, 0x53, 0xb7, 0xe9, 0xb0, 0x75, 0xa1, 0x3d,
    0xc6, 0x8c, 0x97, 0x2b, 0x72, 0xfb, 0x2e, 0x1a,
    0xe4, 0x5e, 0x59, 0xc5, 0xd4, 0x9c, 0xfb, 0x4a,
    0x1b, 0xbc, 0x59, 0x89, 0xd5, 0x34, 0xfe, 0xba,
    0x07, 0x9c, 0x11, 0x48, 0x67, 0xb1, 0x51, 0xa7,
    0xe5, 0xd0, 0x5c, 0xe1, 0xca, 0x44, 0xbd, 0x9b,
    0x8d, 0x59, 0x2f, 0xd6, 0xe0, 0xf6, 0x42, 0x35,
    0x8c, 0xbd, 0x2b, 0x8e, 0xf9, 0x26, 0x16, 0xd4,
    0x76, 0xf9, 0x36, 0x16, 0xb4, 0x77, 0xb9, 0x31,
    0x96, 0xa5, 0x77, 0xdf, 0x30, 0xc2, 0xa2, 0x8f,
    0xcf, 0x20, 0xa2, 0xc3, 0xce, 0x88, 0xa7, 0x33,
    0xd2, 0xa8, 0xef, 0xf2, 0x60, 0x2d, 0x40, 0xef,
    0x82, 0x61, 0x0d, 0x46, 0x2f, 0x94, 0xe1, 0x7a,
    0x47, 0x1d, 0x92, 0x4d, 0x6d, 0xaf, 0x6d, 0xe3,
    0x6c, 0x4b, 0x69, 0xbb, 0x75, 0x9b, 0x3d, 0x5a,
    0x8f, 0xdf, 0x20, 0xc2, 0xc2, 0x8e, 0x8f, 0x27,
    0x22, 0xd2, 0xce, 0xee, 0xa6, 0x67, 0xd5, 0x50,
    0xff, 0xe2, 0x00, 0x4c, 0x01, 0xa8, 0x05, 0xf0,
    0x1c, 0x20, 0x48, 0xc1, 0xb2, 0x85, 0xaf, 0x1d,
    0xe2, 0x4c, 0x4d, 0xa9, 0xad, 0xf5, 0xec, 0x3c,
    0x68, 0x89, 0x73, 0x37, 0x2a, 0xb2, 0xff, 0xae,
    0x01, 0xe4, 0x04, 0x58, 0x19, 0xd0, 0x54, 0xe1,
    0xfa, 0x44, 0x1d, 0x98, 0x4d, 0x51, 0xaf, 0xe5,
    0xe0, 0x5c, 0x41, 0xc9, 0x84, 0xb5, 0x1b, 0xbe,
    0x59, 0x85, 0xd5, 0x1c, 0xfe, 0x4a, 0x05, 0xbc,
    0x1d, 0x88, 0x4d, 0x31, 0xae, 0xa5, 0xe7, 0xdc,
    0x50, 0xc9, 0xe2, 0xb4, 0x4f, 0xb9, 0xa1, 0x95,
    0xc5, 0x7c, 0x9f, 0x0b, 0x42, 0x3b, 0x8c, 0x99,
    0x2b, 0x56, 0xfb, 0xf6, 0x18, 0x34, 0x50, 0xb9,
    0xe3, 0x94, 0x49, 0x79, 0xb7, 0x15, 0xb2, 0x7d,
    0xad, 0x0d, 0xee, 0x2c, 0x64, 0xe9, 0x5a, 0x77,
    0xdd, 0x30, 0xce, 0xa2, 0xa7, 0xcf, 0xd0, 0xa0,
    0xe3, 0xc2, 0x48, 0x8d, 0xb3, 0x2d, 0xaa, 0xed,
    0xfe, 0x6c, 0x05, 0x68, 0x1f, 0x70, 0x43, 0x21,
    0x8a, 0xc5, 0x3e, 0x9e, 0x87, 0x47, 0x13, 0x92,
    0x69, 0x6d, 0x77, 0x6f, 0x33, 0x62, 0xab, 0x4f,
    0xfb, 0xa0, 0x19, 0xc0, 0x54, 0x81, 0xfb, 0x04,
    0x1a, 0x18, 0x5c, 0x51, 0xc9, 0xe4, 0xb4, 0x5b,
    0xb9, 0xd9, 0x94, 0xd5, 0x7a, 0xff, 0x1e, 0x02,
    0x44, 0x0d, 0x98, 0x2d, 0x50, 0xef, 0xe2, 0x60,
    0x4d, 0x41, 0xaf, 0x85, 0xe1, 0x1c, 0x46, 0x49,
    0x95, 0xb5, 0x7d, 0xbf, 0x0d, 0x82, 0x2d, 0x0c,
    0xee, 0x2a, 0x64, 0xfd, 0x5a, 0x0f, 0xdc, 0x20,
    0xc8, 0xc2, 0xb2, 0x8f, 0xaf, 0x21, 0xe2, 0xc4,
    0x4e, 0x99, 0xa7, 0x55, 0xd3, 0xfc, 0xe8, 0x0a,
    0x70, 0x3d, 0x20, 0x8e, 0xc3, 0x26, 0x8a, 0xd7,
    0x3e, 0xf2, 0x86, 0x2f, 0x14, 0xe2, 0x7a, 0x4d,
    0x1d, 0xae, 0x4d, 0xe5, 0xac, 0x5d, 0xe9, 0xcc,
    0x74, 0xa9, 0x3b, 0xf6, 0x98, 0x37, 0x50, 0xb3,
    0xe3, 0xa8, 0x49, 0xf1, 0xb4, 0x25, 0xb8, 0xdd,
    0x92, 0xcd, 0x6e, 0xaf, 0x67, 0xe3, 0x50, 0x4b,
    0xe1, 0xb8, 0x45, 0x91, 0x9d, 0x65, 0x4f, 0x5f,
    0xa3, 0xc1, 0xc8, 0x84, 0xb3, 0x1b, 0xaa, 0x59,
    0xfd, 0xd4, 0x0c, 0xf8, 0x2a, 0x10, 0xfc, 0x62,
    0x09, 0x4c, 0x37, 0xa8, 0xb1, 0xf3, 0xa4, 0x29,
    0xd8, 0xf4, 0xd2, 0x3a, 0xec, 0x9e, 0x6b, 0x45,
    0x7b, 0x9f, 0x19, 0x42, 0x57, 0x8d, 0xf1, 0x2c,
    0x26, 0xe8, 0xd6, 0x72, 0xf5, 0x2e, 0x3e, 0xe4,
    0x86, 0x5b, 0x15, 0xda, 0x7c, 0xdd, 0x0a, 0xce,
    0x3e, 0xa4, 0x87, 0xdb, 0x10, 0xda, 0x62, 0xdd,
    0x4e, 0xcf, 0xa6, 0xa1, 0xd7, 0xc4, 0xf0, 0x9a,
    0x23, 0x5c, 0xcb, 0xca, 0xb8, 0xbf, 0x93, 0x81,
    0x69, 0x07, 0x76, 0x13, 0x34, 0x6a, 0xb9, 0x7f,
    0x97, 0x01, 0x72, 0x07, 0x2c, 0x12, 0xe8, 0x6e,
    0x71, 0x65, 0x27, 0x5e, 0xd3, 0xc6, 0xe8, 0x96,
    0x73, 0x75, 0x2b, 0x3e, 0xfa, 0x86, 0x1f, 0x14,
    0x42, 0x79, 0x8d, 0x15, 0x2e, 0x7e, 0xe5, 0x06,
    0x5e, 0x15, 0xc4, 0x7c, 0x99, 0x0b, 0x56, 0x3b,
    0xf4, 0x98, 0x3b, 0x50, 0x9b, 0xe3, 0x58, 0x4b,
    0xd1, 0xb8, 0xe5, 0x92, 0x5d, 0x6d, 0xcf, 0x6c,
    0xa3, 0x6b, 0xcb, 0x78, 0xbb, 0x13, 0x9a, 0x69,
    0x5d, 0x77, 0xcf, 0x30, 0xa2, 0xa3, 0xcf, 0xc8,
    0xa0, 0xb3, 0xc3, 0xa8, 0x89, 0xf3, 0x34, 0x2a,
    0xb8, 0xff, 0x92, 0x01, 0x6c, 0x07, 0x68, 0x13,
    0x70, 0x6b, 0x21, 0x7a, 0xc7, 0x1e, 0x92, 0x47,
    0x6d, 0x93, 0x6d, 0x6b, 0x6f, 0x7b, 0x63, 0x1b,
    0x4a, 0x5b, 0xbd, 0xd9, 0x8c, 0xd5, 0x2a, 0xfe,
    0xfe, 0x06, 0x04, 0x14, 0x18, 0x78, 0x51, 0x11,
    0xe6, 0x64, 0x55, 0x59, 0xff, 0xd4, 0x00, 0xf8,
    0x02, 0x10, 0x0c, 0x60, 0x29, 0x40, 0xf7, 0x82,
    0x31, 0x0c, 0xa6, 0x2b, 0xd4, 0xf8, 0xfa, 0x12,
    0x1c, 0x6c, 0x49, 0x69, 0xb7, 0x75, 0xb3, 0x3d,
    0xaa, 0x8d, 0xff, 0x2c, 0x02, 0xe8, 0x0e, 0x70,
    0x25, 0x20, 0xde, 0xc2, 0xc6, 0x8e, 0x97, 0x27,
    0x72, 0xd3, 0x2e, 0xea, 0xe6, 0x7e, 0x55, 0x05,
    0xfe, 0x1c, 0x04, 0x48, 0x19, 0xb0, 0x55, 0xa1,
    0xfd, 0xc4, 0x0c, 0x98, 0x2b, 0x50, 0xfb, 0xe2,
    0x18, 0x4c, 0x51, 0xa9, 0xe5, 0xf4, 0x5c, 0x39,
    0xc8, 0x94, 0xb3, 0x7b, 0xab, 0x19, 0xfa, 0x54,
    0x1d, 0xf8, 0x4c, 0x11, 0xa8, 0x65, 0xf1, 0x5c,
    0x27, 0xc8, 0xd0, 0xb2, 0xe3, 0xae, 0x49, 0xe5,
    0xb4, 0x5d, 0xb9, 0xcd, 0x94, 0xad, 0x7b, 0xef,
    0x18, 0x62, 0x51, 0x4d, 0xe7, 0xac, 0x51, 0xe9,
    0xe4, 0x74, 0x59, 0x39, 0xd6, 0x94, 0xf7, 0x7a,
    0x33, 0x1c, 0xaa, 0x4b, 0xfd, 0xb8, 0x0d, 0x90,
    0x2d, 0x60, 0xef, 0x42, 0x63, 0x8d, 0x49, 0x2f,
    0xb6, 0xe1, 0xb6, 0x45, 0xb5, 0x9d, 0xbd, 0x4d,
    0x8f, 0xad, 0x21, 0xee, 0xc4, 0x66, 0x99, 0x57,
    0x57, 0xf3, 0xf0, 0x28, 0x20, 0xf0, 0xc2, 0x22,
    0x8c, 0xcf, 0x2a, 0xa2, 0xff, 0xce, 0x00, 0xa4,
    0x03, 0xd8, 0x08, 0xd0, 0x32, 0xe0, 0xae, 0x43,
    0xe5, 0x88, 0x5d, 0x31, 0xce, 0xa4, 0xa7, 0xdb,
    0xd0, 0xd8, 0xe2, 0xd2, 0x4e, 0xed, 0xa6, 0x6d,
    0xd5, 0x6c, 0xff, 0x6a, 0x03, 0x7c, 0x0b, 0x08,
    0x3a, 0x30, 0x9c, 0xa3, 0x4b, 0xcb, 0xb8, 0xb9,
    0x93, 0x95, 0x69, 0x7f, 0x77, 0x03, 0x32, 0x0a,
    0xac, 0x3f, 0xe8, 0x80, 0x73, 0x01, 0x2a, 0x06,
    0xfc, 0x16, 0x08, 0x74, 0x31, 0x38, 0xa6, 0x93,
    0xd7, 0x68, 0xf3, 0x72, 0x2b, 0x2c, 0xfa, 0xea,
    0x1e, 0x7c, 0x45, 0x09, 0x9e, 0x35, 0x44, 0xbf,
    0x9b, 0x81, 0x59, 0x07, 0xd6, 0x10, 0xf4, 0x62,
    0x39, 0x4c, 0x97, 0xab, 0x71, 0xfb, 0x24, 0x1a,
    0xd8, 0x5e, 0xd1, 0xc6, 0xe4, 0x96, 0x5b, 0x75,
    0xdb, 0x3c, 0xda, 0x8a, 0xdf, 0x3e, 0xc2, 0x86,
    0x8f, 0x17, 0x22, 0x72, 0xcd, 0x2e, 0xae, 0xe7,
    0xe6, 0x50, 0x55, 0xe1, 0xfc, 0x44, 0x09, 0x98,
    0x35, 0x50, 0xbf, 0xe3, 0x80, 0x49, 0x01, 0xb6,
    0x05, 0xb4, 0x1d, 0xb8, 0x4d, 0x91, 0xad, 0x65,
    0xef, 0x5c, 0x63, 0xc9, 0x48, 0xb7, 0xb3, 0xb1,
    0xa9, 0xa5, 0xf5, 0xdc, 0x3c, 0xc8, 0x8a, 0xb3,
    0x3f, 0xaa, 0x81, 0xff, 0x04, 0x02, 0x18, 0x0c,
    0x50, 0x29, 0xe0, 0xf4, 0x42, 0x39, 0x8c, 0x95,
    0x2b, 0x7e, 0xfb, 0x06, 0x1a, 0x14, 0x5c, 0x79,
    0xc9, 0x14, 0xb6, 0x7b, 0xb5, 0x19, 0xbe, 0x55,
    0x85, 0xfd, 0x1c, 0x0e, 0x48, 0x25, 0xb0, 0xdd,
    0xa2, 0xcd, 0xce, 0xac, 0xa7, 0xeb, 0xd0, 0x78,
    0xe1, 0x12, 0x46, 0x6d, 0x95, 0x6d, 0x7f, 0x6f,
    0x03, 0x62, 0x0b, 0x4c, 0x3b, 0xa8, 0x99, 0xf3,
    0x54, 0x2b, 0xf8, 0xf8, 0x12, 0x10, 0x6c, 0x61,
    0x69, 0x47, 0x77, 0x93, 0x31, 0x6a, 0xa7, 0x7f,
    0xd3, 0x00, 0xea, 0x02, 0x7c, 0x0d, 0x08, 0x2e,
    0x30, 0xe4, 0xa2, 0x5b, 0xcd, 0xd8, 0xac, 0xd3,
    0xea, 0xe8, 0x7e, 0x71, 0x05, 0x26, 0x1e, 0xd4,
    0x46, 0xf9, 0x96, 0x15, 0x74, 0x7f, 0x39, 0x02,
    0x96, 0x0f, 0x74, 0x23, 0x38, 0xca, 0x92, 0xbf,
    0x6f, 0x83, 0x61, 0x0b, 0x46, 0x3b, 0x94, 0x99,
    0x7b, 0x57, 0x1b, 0xf2, 0x58, 0x2d, 0xd0, 0xec,
    0xe2, 0x6a, 0x4d, 0x7d, 0xaf, 0x0d, 0xe2, 0x2c,
    0x4c, 0xe9, 0xaa, 0x75, 0xfd, 0x3c, 0x0e, 0x88,
    0x27, 0x30, 0xd2, 0xa2, 0xef, 0xce, 0x60, 0xa5,
    0x43, 0xdf, 0x88, 0xc1, 0x32, 0x86, 0xaf, 0x17,
    0xe2, 0x70, 0x4d, 0x21, 0xae, 0xc5, 0xe6, 0x9c,
    0x57, 0x49, 0xf3, 0xb4, 0x29, 0xb8, 0xf5, 0x92,
    0x3d, 0x6c, 0x8f, 0x6b, 0x23, 0x7a, 0xcb, 0x1e,
    0xba, 0x47, 0x9d, 0x91, 0x4d, 0x67, 0xaf, 0x51,
    0xe3, 0xe4, 0x48, 0x59, 0xb1, 0xd5, 0xa4, 0xfd,
    0xda, 0x0c, 0xdc, 0x2a, 0xc8, 0xfe, 0xb2, 0x07,
    0xac, 0x11, 0xe8, 0x64, 0x71, 0x59, 0x27, 0xd6,
    0xd0, 0xf6, 0xe2, 0x36, 0x4c, 0xb5, 0xab, 0xbd,
    0xf9, 0x8c, 0x15, 0x28, 0x7e, 0xf1, 0x06, 0x26,
    0x14, 0xd4, 0x7a, 0xf9, 0x1e, 0x16, 0x44, 0x75,
    0x99, 0x3d, 0x56, 0x8f, 0xf7, 0x20, 0x32, 0xc0,
    0xae, 0x83, 0xe7, 0x08, 0x52, 0x31, 0xec, 0xa4,
    0x6b, 0xd9, 0x78, 0xd7, 0x12, 0xf2, 0x6e, 0x2d,
    0x64, 0xef, 0x5a, 0x63, 0xdd, 0x48, 0xcf, 0xb2,
    0xa1, 0xaf, 0xc5, 0xe0, 0x9c, 0x43, 0x49, 0x8b,
    0xb5, 0x39, 0xbe, 0x95, 0x87, 0x7d, 0x13, 0x0e,
    0x6a, 0x25, 0x7c, 0xdf, 0x0a, 0xc2, 0x3e, 0x8c,
    0x87, 0x2b, 0x12, 0xfa, 0x6e, 0x1d, 0x64, 0x4f,
    0x59, 0xa3, 0xd5, 0xc8, 0xfc, 0xb2, 0x0b, 0xac,
    0x39, 0xe8, 0x94, 0x73, 0x79, 0x2b, 0x16, 0xfa,
    0x76, 0x1d, 0x34, 0x4e, 0xb9, 0xa7, 0x95, 0xd1,
    0x7c, 0xe7, 0x0a, 0x52, 0x3d, 0xec, 0x8c, 0x6b,
    0x29, 0x7a, 0xf7, 0x1e, 0x32, 0x44, 0xad, 0x9b,
    0xed, 0x58, 0x6f, 0xd1, 0x60, 0xe7, 0x42, 0x53,
    0x8d, 0xe9, 0x2c, 0x76, 0xe9, 0x36, 0x76, 0xb5,
    0x37, 0xbe, 0xb1, 0x87, 0xa5, 0x11, 0xde, 0x64,
    0xc5, 0x5a, 0x9f, 0xdf, 0x40, 0xc3, 0x82, 0x89,
    0x0f, 0x36, 0x22, 0xb4, 0xcf, 0xba, 0xa1, 0x9f,
    0xc5, 0x40, 0x9f, 0x83, 0x41, 0x0b, 0x86, 0x39,
    0x14, 0x96, 0x7b, 0x75, 0x1b, 0x3e, 0x5a, 0x85,
    0xdf, 0x1c, 0xc2, 0x4a, 0x8d, 0xbf, 0x2d, 0x82,
    0xed, 0x0e, 0x6e, 0x25, 0x64, 0xdf, 0x5a, 0xc3,
    0xde, 0x88, 0xc7, 0x32, 0x92, 0xaf, 0x6f, 0xe3,
    0x60, 0x4b, 0x41, 0xbb, 0x85, 0x99, 0x1d, 0x56,
    0x4f, 0xf5, 0xa0, 0x3d, 0xc0, 0x8c, 0x83, 0x2b,
    0x0a, 0xfa, 0x3e, 0x1c, 0x84, 0x4b, 0x19, 0xba,
    0x55, 0x9d, 0xfd, 0x4c, 0x0f, 0xa8, 0x21, 0xf0,
    0xc4, 0x22, 0x98, 0xcf, 0x52, 0xa3, 0xef, 0xc8,
    0x60, 0xb1, 0x43, 0xa7, 0x89, 0xd1, 0x34, 0xe6,
    0xba, 0x57, 0x9d, 0xf1, 0x4c, 0x27, 0xa8, 0xd1,
    0xf2, 0xe4, 0x2e, 0x58, 0xe5, 0xd2, 0x5c, 0xed,
    0xca, 0x6c, 0xbd, 0x6b, 0x8f, 0x79, 0x23, 0x16,
    0xca, 0x76, 0xbd, 0x37, 0x8e, 0xb1, 0x27, 0xa6,
    0xd1, 0xd6, 0xe4, 0xf6, 0x5a, 0x35, 0xdc, 0xbc,
    0xcb, 0x8a, 0xb9, 0x3f, 0x96, 0x81, 0x77, 0x07,
    0x32, 0x12, 0xac, 0x6f, 0xe9, 0x60, 0x77, 0x41,
    0x33, 0x86, 0xa9, 0x17, 0xf6, 0x70, 0x35, 0x20,
    0xbe, 0xc3, 0x86, 0x89, 0x17, 0x36, 0x72, 0xb5,
    0x2f, 0xbe, 0xe1, 0x86, 0x45, 0x15, 0x9e, 0x7d,
    0x45, 0x0f, 0x9e, 0x21, 0x44, 0xc7, 0x9a, 0x91,
    0x5f, 0x67, 0xc3, 0x50, 0x8b, 0xe3, 0x38, 0x4a,
    0x91, 0xbf, 0x65, 0x83, 0x5d, 0x0b, 0xce, 0x38,
    0xa4, 0x93, 0xdb, 0x68, 0xdb, 0x72, 0xdb, 0x2e,
    0xda, 0xe6, 0xde, 0x56, 0xc5, 0xf6, 0x9c, 0x37,
    0x48, 0xb3, 0xb3, 0xa9, 0xa9, 0xf5, 0xf4, 0x3c,
    0x38, 0x88, 0x93, 0x33, 0x6a, 0xab, 0x7f, 0xfb,
    0x00, 0x1a, 0x00, 0x5c, 0x01, 0xc8, 0x04, 0xb0,
    0x1b, 0xa0, 0x59, 0xc1, 0xd4, 0x84, 0xfb, 0x1a,
    0x1a, 0x5c, 0x5d, 0xc9, 0xcc, 0xb4, 0xab, 0xbb,
    0xf9, 0x98, 0x15, 0x50, 0x7f, 0xe1, 0x00, 0x46,
    0x01, 0x94, 0x05, 0x78, 0x1f, 0x10, 0x42, 0x61,
    0x8d, 0x45, 0x2f, 0x9e, 0xe1, 0x46, 0x47, 0x95,
    0x91, 0x7d, 0x67, 0x0f, 0x52, 0x23, 0xec, 0xc8,
    0x6a, 0xb1, 0x7f, 0xa7, 0x01, 0xd2, 0x04, 0xec,
    0x1a, 0x68, 0x5d, 0x71, 0xcf, 0x24, 0xa2, 0xdb,
    0xce, 0xd8, 0xa6, 0xd3, 0xd6, 0xe8, 0xf6, 0x72,
    0x35, 0x2c, 0xbe, 0xeb, 0x86, 0x79, 0x15, 0x16,
    0x7e, 0x75, 0x05, 0x3e, 0x1e, 0x84, 0x47, 0x19,
    0x92, 0x55, 0x6d, 0xff, 0x6c, 0x03, 0x68, 0x0b,
    0x70, 0x3b, 0x20, 0x9a, 0xc3, 0x5e, 0x8b, 0xc7,
    0x38, 0x92, 0x93, 0x6f, 0x6b, 0x63, 0x7b, 0x4b,
    0x1b, 0xba, 0x59, 0x9d, 0xd5, 0x4c, 0xff, 0xaa,
    0x01, 0xfc, 0x04, 0x08, 0x18, 0x30, 0x50, 0xa1,
    0xe3, 0xc4, 0x48, 0x99, 0xb3, 0x55, 0xab, 0xfd,
    0xf8, 0x0c, 0x10, 0x28, 0x60, 0xf1, 0x42, 0x27,
    0x8c, 0xd1, 0x2a, 0xe6, 0xfe, 0x56, 0x05, 0xf4,
    0x1c, 0x38, 0x48, 0x91, 0xb3, 0x65, 0xab, 0x5d,
    0xfb, 0xcc, 0x18, 0xa8, 0x53, 0xf1, 0xe8, 0x24,
    0x70, 0xd9, 0x22, 0xd6, 0xce, 0xf6, 0xa6, 0x37,
    0xd4, 0xb0, 0xfb, 0xa2, 0x19, 0xcc, 0x54, 0xa9,
    0xfb, 0xf4, 0x18, 0x38, 0x50, 0x91, 0xe3, 0x64,
    0x4b, 0x59, 0xbb, 0xd5, 0x98, 0xfd, 0x52, 0x0f,
    0xec, 0x20, 0x68, 0xc1, 0x72, 0x87, 0x2f, 0x12,
    0xe2, 0x6e, 0x4d, 0x65, 0xaf, 0x5d, 0xe3, 0xcc,
    0x48, 0xa9, 0xb3, 0xf5, 0xa8, 0x3d, 0xf0, 0x8c,
    0x23, 0x28, 0xca, 0xf2, 0xbe, 0x2f, 0x84, 0xe1,
    0x1a, 0x46, 0x5d, 0x95, 0xcd, 0x7c, 0xaf, 0x0b,
    0xe2, 0x38, 0x4c, 0x91, 0xab, 0x65, 0xfb, 0x5c,
    0x1b, 0xc8, 0x58, 0xb1, 0xd3, 0xa4, 0xe9, 0xda,
    0x74, 0xdd, 0x3a, 0xce, 0x9e, 0xa7, 0x47, 0xd3,
    0x90, 0xe9, 0x62, 0x77, 0x4d, 0x33, 0xae, 0xa9,
    0xe7, 0xf4, 0x50, 0x39, 0xe0, 0x94, 0x43, 0x79,
    0x8b, 0x15, 0x3a, 0x7e, 0x9d, 0x07, 0x4e, 0x13,
    0xa4, 0x69, 0xd9, 0x74, 0xd7, 0x3a, 0xf2, 0x9e,
    0x2f, 0x44, 0xe3, 0x9a, 0x49, 0x5d, 0xb7, 0xcd,
    0xb0, 0xad, 0xa3, 0xed, 0xc8, 0x6c, 0xb1, 0x6b,
    0xa7, 0x79, 0xd3, 0x14, 0xea, 0x7a, 0x7d, 0x1d,
    0x0e, 0x4e, 0x25, 0xa4, 0xdd, 0xda, 0xcc, 0xde,
    0xaa, 0xc7, 0xfe, 0x90, 0x07, 0x60, 0x13, 0x40,
    0x6b, 0x81, 0x79, 0x07, 0x16, 0x12, 0x74, 0x6d,
    0x39, 0x6e, 0x97, 0x67, 0x73, 0x53, 0x2b, 0xea,
    0xf8, 0x7e, 0x11, 0x04, 0x66, 0x19, 0x54, 0x57,
    0xf9, 0xf0, 0x14, 0x20, 0x78, 0xc1, 0x12, 0x86,
    0x6f, 0x15, 0x62, 0x7f, 0x4d, 0x03, 0xae, 0x09,
    0xe4, 0x34, 0x58, 0xb9, 0xd3, 0x94, 0xe9, 0x7a,
    0x77, 0x1d, 0x32, 0x4e, 0xad, 0xa7, 0xed, 0xd0,
    0x6c, 0xe1, 0x6a, 0x47, 0x7d, 0x93, 0x0d, 0x6a,
    0x2f, 0x7c, 0xe3, 0x0a, 0x4a, 0x3d, 0xbc, 0x8d,
    0x8b, 0x2d, 0x3a, 0xee, 0x9e, 0x67, 0x45, 0x53,
    0x9f, 0xe9, 0x40, 0x77, 0x81, 0x31, 0x06, 0xa6,
    0x17, 0xd4, 0x70, 0xf9, 0x22, 0x16, 0xcc, 0x76,
    0xa9, 0x37, 0xf6, 0xb0, 0x37, 0xa0, 0xb1, 0xc3,
    0xa4, 0x89, 0xdb, 0x34, 0xda, 0xba, 0xdf, 0x9e,
    0xc1, 0x46, 0x87, 0x97, 0x11, 0x72, 0x67, 0x2d,
    0x52, 0xef, 0xee, 0x60, 0x65, 0x41, 0x5f, 0x87,
    0xc1, 0x10, 0x86, 0x63, 0x15, 0x4a, 0x7f, 0xbd,
    0x01, 0x8e, 0x05, 0x24, 0x1e, 0xd8, 0x46, 0xd1,
    0x96, 0xe5, 0x76, 0x5f, 0x35, 0xc2, 0xbc, 0x8f,
    0x8b, 0x21, 0x3a, 0xc6, 0x9e, 0x97, 0x47, 0x73,
    0x93, 0x29, 0x6a, 0xf7, 0x7e, 0x33, 0x04, 0xaa,
    0x1b, 0xfc, 0x58, 0x09, 0xd0, 0x34, 0xe0, 0xba,
    0x43, 0x9d, 0x89, 0x4d, 0x37, 0xae, 0xb1, 0xe7,
    0xa4, 0x51, 0xd9, 0xe4, 0xd4, 0x5a, 0xf9, 0xde,
    0x14, 0xc4, 0x7a, 0x99, 0x1f, 0x56, 0x43, 0xf5,
    0x88, 0x3d, 0x30, 0x8e, 0xa3, 0x27, 0xca, 0xd0,
    0xbe, 0xe3, 0x86, 0x49, 0x15, 0xb6, 0x7d, 0xb5,
    0x0d, 0xbe, 0x2d, 0x84, 0xed, 0x1a, 0x6e, 0x5d,
    0x65, 0xcf, 0x5c, 0xa3, 0xcb, 0xc8, 0xb8, 0xb3,
    0x93, 0xa9, 0x69, 0xf7, 0x74, 0x33, 0x38, 0xaa,
    0x93, 0xff, 0x68, 0x03, 0x70, 0x0b, 0x20, 0x3a,
    0xc0, 0x9e, 0x83, 0x47, 0x0b, 0x92, 0x39, 0x6c,
    0x97, 0x6b, 0x73, 0x7b, 0x2b, 0x1a, 0xfa, 0x5e,
    0x1d, 0xc4, 0x4c, 0x99, 0xab, 0x55, 0xfb, 0xfc,
    0x18, 0x08, 0x50, 0x31, 0xe0, 0xa4, 0x43, 0xd9,
    0x88, 0xd5, 0x32, 0xfe, 0xae, 0x07, 0xe4, 0x10,
    0x58, 0x61, 0xd1, 0x44, 0xe7, 0x9a, 0x51, 0x5d,
    0xe7, 0xcc, 0x50, 0xa9, 0xe3, 0xf4, 0x48, 0x39,
    0xb0, 0x95, 0xa3, 0x7d, 0xcb, 0x0c, 0xba, 0x2b,
    0x9c, 0xf9, 0x4a, 0x17, 0xbc, 0x71, 0x89, 0x25,
    0x36, 0xde, 0xb6, 0xc7, 0xb6, 0x91, 0xb7, 0x65,
    0xb3, 0x5d, 0xab, 0xcd, 0xf8, 0xac, 0x13, 0xe8,
    0x68, 0x71, 0x71, 0x27, 0x26, 0xd2, 0xd6, 0xee,
    0xf6, 0x66, 0x35, 0x54, 0xbf, 0xfb, 0x80, 0x19,
    0x00, 0x56, 0x01, 0xf4, 0x04, 0x38, 0x18, 0x90,
    0x53, 0x61, 0xeb, 0x44, 0x7b, 0x99, 0x19, 0x56,
    0x57, 0xf5, 0xf0, 0x3c, 0x20, 0x88, 0xc3, 0x32,
    0x8a, 0xaf, 0x3f, 0xe2, 0x80, 0x4f, 0x01, 0xa2,
    0x05, 0xcc, 0x1c, 0xa8, 0x4b, 0xf1, 0xb8, 0x25,
    0x90, 0xdd, 0x62, 0xcf, 0x4e, 0xa3, 0xa7, 0xc9,
    0xd0, 0xb4, 0xe3, 0xba, 0x49, 0x9d, 0xb5, 0x4d,
    0xbf, 0xad, 0x81, 0xed, 0x04, 0x6e, 0x19, 0x64,
    0x57, 0x59, 0xf3, 0xd4, 0x28, 0xf8, 0xf2, 0x12,
    0x2c, 0x6c, 0xe9, 0x6a, 0x77, 0x7d, 0x33, 0x0e,
    0xaa, 0x27, 0xfc, 0xd0, 0x0a, 0xe0, 0x3e, 0x40,
    0x85, 0x83, 0x1d, 0x0a, 0x4e, 0x3d, 0xa4, 0x8d,
    0xdb, 0x2c, 0xda, 0xea, 0xde, 0x7e, 0xc5, 0x06,
    0x9e, 0x17, 0x44, 0x73, 0x99, 0x29, 0x56, 0xf7,
    0xf6, 0x30, 0x34, 0xa0, 0xbb, 0xc3, 0x98, 0x89,
    0x53, 0x37, 0xea, 0xb0, 0x7f, 0xa1, 0x01, 0xc6,
    0x04, 0x94, 0x1b, 0x78, 0x5b, 0x11, 0xda, 0x64,
    0xdd, 0x5a, 0xcf, 0xde, 0xa0, 0xc7, 0xc2, 0x90,
    0x8f, 0x63, 0x23, 0x4a, 0xcb, 0xbe, 0xb9, 0x87,
    0x95, 0x11, 0x7e, 0x67, 0x05, 0x52, 0x1f, 0xec,
    0x40, 0x69, 0x81, 0x75, 0x07, 0x3e, 0x12, 0x84,
    0x6f, 0x19, 0x62, 0x57, 0x4d, 0xf3, 0xac, 0x29,
    0xe8, 0xf4, 0x72, 0x39, 0x2c, 0x96, 0xeb, 0x76,
    0x7b, 0x35, 0x1a, 0xbe, 0x5f, 0x85, 0xc1, 0x1c,
    0x86, 0x4b, 0x15, 0xba, 0x7d, 0x9d, 0x0d, 0x4e,
    0x2f, 0xa4, 0xe1, 0xda, 0x44, 0xdd, 0x9a, 0xcd,
    0x5e, 0xaf, 0xc7, 0xe0, 0x90, 0x43, 0x61, 0x8b,
    0x45, 0x3b, 0x9e, 0x99, 0x47, 0x57, 0x93, 0xf1,
    0x68, 0x27, 0x70, 0xd3, 0x22, 0xea, 0xce, 0x7e,
    0xa5, 0x07, 0xde, 0x10, 0xc4, 0x62, 0x99, 0x4f,
    0x57, 0xa3, 0xf1, 0xc8, 0x24, 0xb0, 0xdb, 0xa2,
    0xd9, 0xce, 0xd4, 0xa6, 0xfb, 0xd6, 0x18, 0xf4,
    0x52, 0x39, 0xec, 0x94, 0x6b, 0x79, 0x7b, 0x17,
    0x1a, 0x72, 0x5d, 0x2d, 0xce, 0xec, 0xa6, 0x6b,
    0xd5, 0x78, 0xff, 0x12, 0x02, 0x6c, 0x0d, 0x68,
    0x2f, 0x70, 0xe3, 0x22, 0x4a, 0xcd, 0xbe, 0xad,
    0x87, 0xed, 0x10, 0x6e, 0x61, 0x65, 0x47, 0x5f,
    0x93, 0xc1, 0x68, 0x87, 0x73, 0x13, 0x2a, 0x6a,
    0xfd, 0x7e, 0x0f, 0x04, 0x22, 0x18, 0xcc, 0x52,
    0xa9, 0xef, 0xf4, 0x60, 0x39, 0x40, 0x97, 0x83,
    0x71, 0x0b, 0x26, 0x3a, 0xd4, 0x9e, 0xfb, 0x46,
    0x1b, 0x94, 0x59, 0x79, 0xd7, 0x14, 0xf2, 0x7a,
    0x2d, 0x1c, 0xee, 0x4a, 0x65, 0xbd, 0x5d, 0x8f,
    0xcd, 0x20, 0xae, 0xc3, 0xe6, 0x88, 0x57, 0x31,
    0xf2, 0xa4, 0x2f, 0xd8, 0xe0, 0xd2, 0x42, 0xed,
    0x8e, 0x6d, 0x25, 0x6e, 0xdf, 0x66, 0xc3, 0x56,
    0x8b, 0xf7, 0x38, 0x32, 0x90, 0xaf, 0x63, 0xe3,
    0x48, 0x4b, 0xb1, 0xb9, 0xa5, 0x95, 0xdd, 0x7c,
    0xcf, 0x0a, 0xa2, 0x3f, 0xcc, 0x80, 0xab, 0x03,
    0xfa, 0x08, 0x1c, 0x30, 0x48, 0xa1, 0xb3, 0xc5,
    0xa8, 0x9d, 0xf3, 0x4c, 0x2b, 0xa8, 0xf9, 0xf2,
    0x14, 0x2c, 0x78, 0xe9, 0x12, 0x76, 0x6d, 0x35,
    0x6e, 0xbf, 0x67, 0x83, 0x51, 0x0b, 0xe6, 0x38,
    0x54, 0x91, 0xfb, 0x64, 0x1b, 0x58, 0x5b, 0xd1,
    0xd8, 0xe4, 0xd2, 0x5a, 0xed, 0xde, 0x6c, 0xc5,
    0x6a, 0x9f, 0x7f, 0x43, 0x03, 0x8a, 0x09, 0x3c,
    0x36, 0x88, 0xb7, 0x33, 0xb2, 0xa9, 0xaf, 0xf5,
    0xe0, 0x3c, 0x40, 0x89, 0x83, 0x35, 0x0a, 0xbe,
    0x3f, 0x84, 0x81, 0x1b, 0x06, 0x5a, 0x15, 0xdc,
    0x7c, 0xc9, 0x0a, 0xb6, 0x3f, 0xb4, 0x81, 0xbb,
    0x05, 0x9a, 0x1d, 0x5c, 0x4f, 0xc9, 0xa0, 0xb5,
    0xc3, 0xbc, 0x89, 0x8b, 0x35, 0x3a, 0xbe, 0x9f,
    0x87, 0x41, 0x13, 0x86, 0x69, 0x15, 0x76, 0x7f,
    0x35, 0x02, 0xbe, 0x0f, 0x84, 0x21, 0x18, 0xc6,
    0x52, 0x95, 0xef, 0x7c, 0x63, 0x09, 0x4a, 0x37,
    0xbc, 0xb1, 0x8b, 0xa5, 0x39, 0xde, 0x94, 0xc7,
    0x7a, 0x93, 0x1f, 0x6a, 0x43, 0x7d, 0x8b, 0x0d,
    0x3a, 0x2e, 0x9c, 0xe7, 0x4a, 0x53, 0xbd, 0xe9,
    0x8c, 0x75, 0x29, 0x3e, 0xf6, 0x86, 0x37, 0x14,
    0xb2, 0x7b, 0xad, 0x19, 0xee, 0x54, 0x65, 0xf9,
    0x5c, 0x17, 0xc8, 0x70, 0xb1, 0x23, 0xa6, 0xc9,
    0xd6, 0xb4, 0xf7, 0xba, 0x31, 0x9c, 0xa5, 0x4b,
    0xdf, 0xb8, 0xc1, 0x92, 0x85, 0x6f, 0x1f, 0x62,
    0x43, 0x4d, 0x8b, 0xad, 0x39, 0xee, 0x94, 0x67,
    0x79, 0x53, 0x17, 0xea, 0x70, 0x7d, 0x21, 0x0e,
    0xc6, 0x26, 0x94, 0xd7, 0x7a, 0xf3, 0x1e, 0x2a,
    0x44, 0xfd, 0x9a, 0x0d, 0x5c, 0x2f, 0xc8, 0xe0,
    0xb2, 0x43, 0xad, 0x89, 0xed, 0x34, 0x6e, 0xb9,
    0x67, 0x97, 0x51, 0x73, 0xe7, 0x28, 0x52, 0xf1,
    0xee, 0x24, 0x64, 0xd9, 0x5a, 0xd7, 0xde, 0xf0,
    0xc6, 0x22, 0x94, 0xcf, 0x7a, 0xa3, 0x1f, 0xca,
    0x40, 0xbd, 0x83, 0x8d, 0x09, 0x2e, 0x36, 0xe4,
    0xb6, 0x5b, 0xb5, 0xd9, 0xbc, 0xd5, 0x8a, 0xfd,
    0x3e, 0x0e, 0x84, 0x27, 0x18, 0xd2, 0x52, 0xed,
    0xee, 0x6c, 0x65, 0x69, 0x5f, 0x77, 0xc3, 0x30,
    0x8a, 0xa3, 0x3f, 0xca, 0x80, 0xbf, 0x03, 0x82,
    0x09, 0x0c, 0x36, 0x28, 0xb4, 0xf3, 0xba, 0x29,
    0x9c, 0xf5, 0x4a, 0x3f, 0xbc, 0x81, 0x8b, 0x05,
    0x3a, 0x1e, 0x9c, 0x47, 0x49, 0x93, 0xb5, 0x69,
    0xbf, 0x75, 0x83, 0x3d, 0x0a, 0x8e, 0x3f, 0x24,
    0x82, 0xdb, 0x0e, 0xda, 0x26, 0xdc, 0xd6, 0xca,
    0xf6, 0xbe, 0x37, 0x84, 0xb1, 0x1b, 0xa6, 0x59,
    0xd5, 0xd4, 0xfc, 0xfa, 0x0a, 0x1c, 0x3c, 0x48,
    0x89, 0xb3, 0x35, 0xaa, 0xbd, 0xff, 0x8c, 0x01,
    0x28, 0x06, 0xf0, 0x16, 0x20, 0x74, 0xc1, 0x3a,
    0x86, 0x9f, 0x17, 0x42, 0x73, 0x8d, 0x29, 0x2e,
    0xf6, 0xe6, 0x36, 0x54, 0xb5, 0xfb, 0xbc, 0x19,
    0x88, 0x55, 0x31, 0xfe, 0xa4, 0x07, 0xd8, 0x10,
    0xd0, 0x62, 0xe1, 0x4e, 0x47, 0xa5, 0x91, 0xdd,
    0x64, 0xcf, 0x5a, 0xa3, 0xdf, 0xc8, 0xc0, 0xb2,
    0x83, 0xaf, 0x09, 0xe2, 0x34, 0x4c, 0xb9, 0xab,
    0x95, 0xf9, 0x7c, 0x17, 0x08, 0x72, 0x31, 0x2c,
    0xa6, 0xeb, 0xd6, 0x78, 0xf5, 0x12, 0x3e, 0x6c,
    0x85, 0x6b, 0x1f, 0x7a, 0x43, 0x1d, 0x8a, 0x4d,
    0x3d, 0xae, 0x8d, 0xe7, 0x2c, 0x52, 0xe9, 0xee,
    0x74, 0x65, 0x39, 0x5e, 0x97, 0xc7, 0x70, 0x93,
    0x23, 0x6a, 0xcb, 0x7e, 0xbb, 0x07, 0x9a, 0x11,
    0x5c, 0x67, 0xc9, 0x50, 0xb7, 0xe3, 0xb0, 0x49,
    0xa1, 0xb5, 0xc5, 0xbc, 0x9d, 0x8b, 0x4d, 0x3b,
    0xae, 0x99, 0xe7, 0x54, 0x53, 0xf9, 0xe8, 0x14,
    0x70, 0x79, 0x21, 0x16, 0xc6, 0x76, 0x95, 0x37,
    0x7e, 0xb3, 0x07, 0xaa, 0x11, 0xfc, 0x64, 0x09,
    0x58, 0x37, 0xd0, 0xb0, 0xe3, 0xa2, 0x49, 0xcd,
    0xb4, 0xad, 0xbb, 0xed, 0x98, 0x6d, 0x51, 0x6f,
    0xe7, 0x60, 0x53, 0x41, 0xeb, 0x84, 0x79, 0x19,
    0x16, 0x56, 0x75, 0xf5, 0x3c, 0x3e, 0x88, 0x87,
    0x33, 0x12, 0xaa, 0x6f, 0xfd, 0x60, 0x0f, 0x40,
    0x23, 0x80, 0xc9, 0x02, 0xb6, 0x0f, 0xb4, 0x21,
    0xb8, 0xc5, 0x92, 0x9d, 0x6f, 0x4f, 0x63, 0xa3,
    0x49, 0xcb, 0xb4, 0xb9, 0xbb, 0x95, 0x99, 0x7d,
    0x57, 0x0f, 0xf2, 0x20, 0x2c, 0xc0, 0xea, 0x82,
    0x7f, 0x0d, 0x02, 0x2e, 0x0c, 0xe4, 0x2a, 0x58,
    0xfd, 0xd2, 0x0c, 0xec, 0x2a, 0x68, 0xfd, 0x72,
    0x0f, 0x2c, 0x22, 0xe8, 0xce, 0x72, 0xa5, 0x2f,
    0xde, 0xe0, 0xc6, 0x42, 0x95, 0x8f, 0x7d, 0x23,
    0x0e, 0xca, 0x26, 0xbc, 0xd7, 0x8a, 0xf1, 0x3e,
    0x26, 0x84, 0xd7, 0x1a, 0xf2, 0x5e, 0x2d, 0xc4,
    0xec, 0x9a, 0x6b, 0x5d, 0x7b, 0xcf, 0x18, 0xa2,
    0x53, 0xcd, 0xe8, 0xac, 0x73, 0xe9, 0x28, 0x76,
    0xf1, 0x36, 0x26, 0xb4, 0xd7, 0xba, 0xf1, 0x9e,
    0x25, 0x44, 0xdf, 0x9a, 0xc1, 0x5e, 0x87, 0xc7,
    0x10, 0x92, 0x63, 0x6d, 0x4b, 0x6f, 0xbb, 0x61,
    0x9b, 0x45, 0x5b, 0x9f, 0xd9, 0x40, 0xd7, 0x82,
    0xf1, 0x0e, 0x26, 0x24, 0xd4, 0xda, 0xfa, 0xde,
    0x1e, 0xc4, 0x46, 0x99, 0x97, 0x55, 0x73, 0xff,
    0x28, 0x02, 0xf0, 0x0e, 0x20, 0x24, 0xc0, 0xda,
    0x82, 0xdf, 0x0e, 0xc2, 0x26, 0x8c, 0xd7, 0x2a,
    0xf2, 0xfe, 0x2e, 0x04, 0xe4, 0x1a, 0x58, 0x5d,
    0xd1, 0xcc, 0xe4, 0xaa, 0x5b, 0xfd, 0xd8, 0x0c,
    0xd0, 0x2a, 0xe0, 0xfe, 0x42, 0x05, 0x8c, 0x1d,
    0x28, 0x4e, 0xf1, 0xa6, 0x25, 0xd4, 0xdc, 0xfa,
    0xca, 0x1e, 0xbc, 0x47, 0x89, 0x91, 0x35, 0x66,
    0xbf, 0x57, 0x83, 0xf1, 0x08, 0x26, 0x30, 0xd4,
    0xa2, 0xfb, 0xce, 0x18, 0xa4, 0x53, 0xd9, 0xe8,
    0xd4, 0x72, 0xf9, 0x2e, 0x16, 0xe4, 0x76, 0x59,
    0x35, 0xd6, 0xbc, 0xf7, 0x8a, 0x31, 0x3c, 0xa6,
    0x8b, 0xd7, 0x38, 0xf2, 0x92, 0x2f, 0x6c, 0xe3,
    0x6a, 0x4b, 0x7d, 0xbb, 0x0d, 0x9a, 0x2d, 0x5c,
    0xef, 0xca, 0x60, 0xbd, 0x43, 0x8f, 0x89, 0x21,
    0x36, 0xc6, 0xb6, 0x97, 0xb7, 0x71, 0xb3, 0x25,
    0xaa, 0xdd, 0xfe, 0xcc, 0x06, 0xa8, 0x17, 0xf0,
    0x70, 0x21, 0x20, 0xc6, 0xc2, 0x96, 0x8f, 0x77,
    0x23, 0x32, 0xca, 0xae, 0xbf, 0xe7, 0x80, 0x51,
    0x01, 0xe6, 0x04, 0x54, 0x19, 0xf8, 0x54, 0x11,
    0xf8, 0x64, 0x11, 0x58, 0x67, 0xd1, 0x50, 0xe7,
    0xe2, 0x50, 0x4d, 0xe1, 0xac, 0x45, 0xe9, 0x9c,
    0x75, 0x49, 0x3f, 0xb6, 0x81, 0xb7, 0x05, 0xb2,
    0x1d, 0xac, 0x4d, 0xe9, 0xac, 0x75, 0xe9, 0x3c,
    0x76, 0x89, 0x37, 0x36, 0xb2, 0xb7, 0xaf, 0xb1,
    0xe1, 0xa4, 0x45, 0xd9, 0x9c, 0xd5, 0x4a, 0xff,
    0xbe, 0x01, 0x84, 0x05, 0x18, 0x1e, 0x50, 0x45,
    0xe1, 0x9c, 0x45, 0x49, 0x9f, 0xb5, 0x41, 0xbf,
    0x85, 0x81, 0x1d, 0x06, 0x4e, 0x15, 0xa4, 0x7d,
    0xd9, 0x0c, 0xd6, 0x2a, 0xf4, 0xfe, 0x3a, 0x04,
    0x9c, 0x1b, 0x48, 0x5b, 0xb1, 0xd9, 0xa4, 0xd5,
    0xda, 0xfc, 0xde, 0x0a, 0xc4, 0x3e, 0x98, 0x87,
    0x53, 0x13, 0xea, 0x68, 0x7d, 0x71, 0x0f, 0x26,
    0x22, 0xd4, 0xce, 0xfa, 0xa6, 0x1f, 0xd4, 0x40,
    0xf9, 0x82, 0x15, 0x0c, 0x7e, 0x29, 0x04, 0xf6,
    0x1a, 0x34, 0x5c, 0xb9, 0xcb, 0x94, 0xb9, 0x7b,
    0x97, 0x19, 0x72, 0x57, 0x2d, 0xf2, 0xec, 0x2e,
    0x68, 0xe5, 0x72, 0x5f, 0x2d, 0xc2, 0xec, 0x8e,
    0x6b, 0x25, 0x7a, 0xdf, 0x1e, 0xc2, 0x46, 0x8d,
    0x97, 0x2d, 0x72, 0xef, 0x2e, 0x62, 0xe5, 0x4e,
    0x5f, 0xa5, 0xc1, 0xdc, 0x84, 0xcb, 0x1a, 0xba,
    0x5f, 0x9d, 0xc1, 0x4c, 0x87, 0xab, 0x11, 0xfa,
    0x64, 0x1d, 0x58, 0x4f, 0xd1, 0xa0, 0xe5, 0xc2,
    0x5c, 0x8d, 0xcb, 0x2c, 0xba, 0xeb, 0x9e, 0x79,
    0x45, 0x17, 0x9e, 0x71, 0x45, 0x27, 0x9e, 0xd1,
    0x46, 0xe7, 0x96, 0x51, 0x75, 0xe7, 0x3c, 0x52,
    0x89, 0xef, 0x34, 0x62, 0xb9, 0x4f, 0x97, 0xa1,
    0x71, 0xc7, 0x24, 0x92, 0xdb, 0x6e, 0xdb, 0x66,
    0xdb, 0x56, 0xdb, 0xf6, 0xd8, 0x36, 0xd0, 0xb6,
    0xe3, 0xb6, 0x49, 0xb5, 0xb5, 0xbd, 0xbd, 0x8d,
    0x8d, 0x2d, 0x2e, 0xee, 0xe6, 0x66, 0x55, 0x55
};
unsigned int noise15_len = 4096;
