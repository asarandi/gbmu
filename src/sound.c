#include "gb.h"
#include "hardware.h"

/* http://gbdev.gg8.se/wiki/articles/Sound_Controller */
/* http://gbdev.gg8.se/wiki/articles/Gameboy_sound_hardware */
/* https://ia801906.us.archive.org/19/items/GameBoyProgManVer1.1/GameBoyProgManVer1.1.pdf */

#define VOLUME_CLOCK                (4194304 /  64)
#define SWEEP_CLOCK                 (4194304 / 128)
#define LENGTH_CLOCK                (4194304 / 256)
#define FREQUENCY_CLOCK             (4194304 / 512)
#define SAMPLE_CLOCK                (4194304 / SAMPLING_FREQUENCY)

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
    uint32_t lfsr;
    uint32_t lfsr_shift;
    uint32_t lfsr_width;
    uint32_t lfsr_ratio;
};
typedef struct s_sound t_sound;

t_sound s1, s2, s3, s4; // globals

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

/*
    writes int16_t interleaved samples to `buf'
    returns 1 when `index' is greater than or equal to `size'
*/

static int write_sounds(uint8_t *buf, uint32_t size) {
    int32_t left, right, sample;
    static uint32_t index;

    if (!size)
        return 1;

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
        sample = (INT16_MAX / 15) * s4.volume;
        sample *= !(s4.lfsr & 1);
        left += (gb_mem[rAUDTERM] & AUDTERM_4_LEFT) ? sample : 0;
        right += (gb_mem[rAUDTERM] & AUDTERM_4_RIGHT) ? sample : 0;
    }

    left >>= 2;
    left = (left / 7) * ((gb_mem[rAUDVOL] >> 4) & 7);

    right >>= 2;
    right = (right / 7) * (gb_mem[rAUDVOL] & 7);

    *(int16_t * ) & buf[index] = (int16_t)left;
    *(int16_t * ) & buf[index + 2] = (int16_t)right;
    index += 4;  /* one frame == 2 sixteen bit samples: L, R */
    return index >= size;
}

static void volume_tick(t_sound *s) {
    if ((!s->on) || (!s->env_sweep))
        return;
    s->env_ctr++;
    if (s->env_ctr < s->env_sweep)
        return;
    s->env_ctr -= s->env_sweep;
    if ((s->env_dir) && (s->volume < 15))
        s->volume++;
    if ((!s->env_dir) && (s->volume > 0))
        s->volume--;
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
    if ((!s->on) || (!s->sweep_time) || (!s->sweep_shift))
        return;
    s->sweep_ctr++;
    if (s->sweep_ctr < s->sweep_time)
        return;
    s->sweep_ctr -= s->sweep_time;
    return sweep_calc(s);
}

static void lfsr_calc(t_sound *s) {
    uint32_t ticks, new_bit;

    if ((!s->on) || (!s->freq)) {
        return;
    }
    ticks = 4194304 / s->freq;
    for (; s->cycles >= ticks; s->cycles -= ticks) {
        new_bit = ((s->lfsr >> 1) & 1) ^ (s->lfsr & 1);
        s->lfsr >>= 1;
        s->lfsr &= ~(1 << 14);
        s->lfsr |= (new_bit << 14);
        if (s->lfsr_width) {
            s->lfsr &= ~(1 << 6);
            s->lfsr |= (new_bit << 6);
        }
    }
}

int sound_update(uint8_t *gb_mem, t_state *state, int cycles) {
    static uint32_t volume, sweep, length, samples;

    s1.cycles += cycles;
    s2.cycles += cycles;
    s3.cycles += cycles;
    s4.cycles += cycles;
    lfsr_calc(&s4);

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

    gb_mem[rAUDENA] = (gb_mem[rAUDENA] & 128) | (s1.on << 0) | (s2.on << 1) | (s3.on << 2) | (s4.on << 3);

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
        return (gb_mem[rAUDENA] & 128) | (s1.on << 0) | (s2.on << 1) | (s3.on << 2) | (s4.on << 3);
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
        s1.volume = (data >> 4) & 15;       // 4 bits 7-4
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
        s1.is_len_counter = (data >> 6) & 1;        // 1 = counter, 0 = continuous
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
        s4.lfsr_shift = (data >> 4) & 15;
        s4.lfsr_width = (data >> 3) & 1;        // 0 = 15 bits, 1 = 7 bits
        s4.lfsr_ratio = data & 7;
        uint32_t f = 524288;
        uint32_t tab[] = {f * 2, f, f / 2, f / 3, f / 4, f / 5, f / 6, f / 7};
        s4.freq = tab[s4.lfsr_ratio] >> s4.lfsr_shift;
        break;

    case rAUD4GO:       // rNR44
        gb_mem[rAUD4GO] = data;
        s4.is_len_counter = (data >> 6) & 1;
        if (data & 128) {
            // trigger
            if (!s4.on) {
                s4.lfsr = 0x7fff;
                s4.cycles = 0;
                s4.env_ctr = 0;
            }
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
