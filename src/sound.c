#include "gb.h"
#include <SDL.h>
#include "hardware.h"

/* http://gbdev.gg8.se/wiki/articles/Sound_Controller */
/* http://gbdev.gg8.se/wiki/articles/Gameboy_sound_hardware */
/* https://ia801906.us.archive.org/19/items/GameBoyProgManVer1.1/GameBoyProgManVer1.1.pdf */

#define VOLUME_CLOCK                (4194304 /  64)
#define SWEEP_CLOCK                 (4194304 / 128)
#define LENGTH_CLOCK                (4194304 / 256)
#define FREQUENCY_CLOCK             (4194304 / 512)

#define SAMPLING_FREQUENCY          (65536)
#define NUM_SAMPLES                 (SAMPLING_FREQUENCY / 60)
#define SAMPLE_CLOCK                (4194304 / SAMPLING_FREQUENCY)

#define NUM_CHANNELS                2
#define SAMPLE_SIZE                 2
#define CHANNEL_BUF_SIZE            (NUM_SAMPLES * SAMPLE_SIZE * NUM_CHANNELS)

typedef struct s_sound {
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
}               t_sound;

SDL_AudioSpec                sdl_received_spec;
SDL_AudioSpec                sdl_wanted_spec;
SDL_AudioDeviceID            sdl_audio_device = 0;

t_sound   s1;
t_sound   s2;
t_sound   s3;
t_sound   s4;

static volatile int32_t audio_done, sample_index;
uint8_t  sound_buffer[CHANNEL_BUF_SIZE] = {0};

void sweep_calc();

uint8_t sound_read_u8(uint16_t addr)
{
    switch (addr) {
    case rAUDENA:
        return (gb_mem[rAUDENA] & 128) | (s1.on<<0) | (s2.on<<1) | (s3.on<<2) | (s4.on<<3);
    default:
        return gb_mem[addr];
    }
}

void    sound_write_u8(uint16_t addr, uint8_t data)
{
    if (addr != rAUDENA) {
        if ((gb_mem[rAUDENA] & AUDENA_ON) == 0) {
            return ;      /*ignore all writes when sound off*/
        }
    }

    switch (addr) {

    case rAUD1SWEEP:    // rNR10
        gb_mem[rAUD1SWEEP] = data;
        s1.sweep_time = (data >> 4) & 7;        // 3 bits 6-4
        s1.sweep_dir = (data >> 3) & 1;         // 0 = add, 1 = sub
        s1.sweep_shift = data & 7;              // 3 bits 2-0
        break ;

    case rAUD1LEN:      // rNR11
        gb_mem[rAUD1LEN] = data;
        s1.duty = (data >> 6) & 3;              // 2 bits 7-6
        s1.length = data & 63;                  // 6 bits 5-0
        break ;

    case rAUD1ENV:      // rNR12
        gb_mem[rAUD1ENV] = data;
        s1.volume = (data >> 4) & 15;       // 4 bits 7-4
        s1.env_dir = (data >> 3) & 1;           // 0 = sub, 1 = add
        s1.env_sweep = data & 7;
        s1.on = (gb_mem[rAUD1ENV] >> 4) != 0;
        break ;

    case rAUD1LOW:      // rNR13
        gb_mem[rAUD1LOW] = data;
        s1.freq = ((gb_mem[rAUD1HIGH] & 7) << 8) | gb_mem[rAUD1LOW];
        break ;

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
                sweep_calc();
            }
            s1.on = (gb_mem[rAUD1ENV] >> 4) != 0;
        }
        break ;

    case rAUD2LEN:      // rNR21
        gb_mem[rAUD2LEN] = data;
        s2.duty = (data >> 6) & 3;              // 2 bits 7-6
        s2.length = data & 63;                  // 6 bits 5-0
        break ;

    case rAUD2ENV:      // rNR22
        gb_mem[rAUD2ENV] = data;
        s2.volume = (data >> 4) & 15;           // 4 bits 7-4
        s2.env_dir = (data >> 3) & 1;           // 0 = sub, 1 = add
        s2.env_sweep = data & 7;
        s2.on = (gb_mem[rAUD2ENV] >> 4) != 0;
        break ;

    case rAUD2LOW:      // rNR23
        gb_mem[rAUD2LOW] = data;
        s2.freq = ((gb_mem[rAUD2HIGH] & 7) << 8) | gb_mem[rAUD2LOW];
        break ;

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
        break ;

    case rAUD3ENA:      // rNR30
        gb_mem[rAUD3ENA] = data;
        s3.on = (gb_mem[rAUD3ENA] & 128) != 0;
        break ;

    case rAUD3LEN:      // rNR31
        gb_mem[rAUD3LEN] = data;
        s3.length = data;
        break ;

    case rAUD3LEVEL:    // rNR32
        gb_mem[rAUD3LEVEL] = data;
        s3.volume = (data >> 5) & 3;
        break ;

    case rAUD3LOW:      // rNR33
        gb_mem[rAUD3LOW] = data;
        s3.freq = ((gb_mem[rAUD3HIGH] & 7) << 8) | gb_mem[rAUD3LOW];
        break ;

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
        break ;

    case rAUD4LEN:      // rNR41
        gb_mem[rAUD4LEN] = data;
        s4.length = data & 63;
        break ;

    case rAUD4ENV:      // rNR42
        gb_mem[rAUD4ENV] = data;
        s4.volume = (data >> 4) & 15;           // 4 bits 7-4
        s4.env_dir = (data >> 3) & 1;           // 0 = sub, 1 = add
        s4.env_sweep = data & 7;
        s4.on = (gb_mem[rAUD4ENV] >> 4) != 0;
        break ;

    case rAUD4POLY:     // rNR43
        gb_mem[rAUD4POLY] = data;
        s4.lfsr_shift = (data >> 4) & 15;
        s4.lfsr_width = (data >> 3) & 1;        // 0 = 15 bits, 1 = 7 bits
        s4.lfsr_ratio = data & 7;
        uint32_t f = 524288;
        uint32_t tab[] = {f*2, f, f/2, f/3, f/4, f/5, f/6, f/7};
        s4.freq = tab[s4.lfsr_ratio] >> s4.lfsr_shift;
        break ;

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
        break ;

    case rAUDVOL:       // rNR50
        gb_mem[rAUDVOL] = data;
        break ;

    case rAUDTERM:      // rNR51
        gb_mem[rAUDTERM] = data;
        break ;

    case rAUDENA:       // rNR52
        gb_mem[rAUDENA] = data & 128;
        if ((gb_mem[rAUDENA] & 128) == 0) {
            s1.on = s2.on = s3.on = s4.on = 0;
        }
        break ;

    default:
        gb_mem[addr] = data;
    }
}

int16_t square_wave(t_sound *s)
{
    uint32_t duties[4][8] = {
        {0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,1},
        {1,0,0,0,0,1,1,1},
        {0,1,1,1,1,1,1,0}
    };

    if (!s->freq)
        return 0;

    uint32_t ticks = 4194304 / (131072 / (2048 - s->freq));
    uint32_t idx = (s->cycles / (ticks >> 3)) & 7;
    return (INT16_MAX/15) * s->volume * duties[s->duty][idx];
}

int16_t sound_3_wave()
{
    if (!s3.freq)
        return 0;

    uint32_t ticks = 4194304 / (65536 / (2048 - s3.freq));
    uint32_t idx = (s3.cycles / (ticks >> 5)) & 31;
    uint8_t nib = gb_mem[_AUD3WAVERAM + (idx >> 1)];
    nib = (idx & 1) ? (nib & 15) : (nib >> 4);

    switch (s3.volume) {
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
    return (INT16_MAX/15) * nib;
}


int apu_sync()
{
    if (sample_index < CHANNEL_BUF_SIZE) {
        return 0;
    }
    while (!audio_done)
        SDL_Delay(1);
    audio_done = 0;
    sample_index = 0;
    return 1;
}

void    write_sample()
{
    int32_t left, right, sample;

    left = right = 0;

    if ((s1.on) && (state->sound_channels[0])) {
        sample = square_wave(&s1);
        left += (gb_mem[rAUDTERM] & AUDTERM_1_LEFT) ? sample : 0;
        right += (gb_mem[rAUDTERM] & AUDTERM_1_RIGHT) ? sample : 0;
    }

    if ((s2.on) && (state->sound_channels[1])) {
        sample = square_wave(&s2);
        left += (gb_mem[rAUDTERM] & AUDTERM_2_LEFT) ? sample : 0;
        right += (gb_mem[rAUDTERM] & AUDTERM_2_RIGHT) ? sample : 0;
    }

    if ((s3.on) && (state->sound_channels[2])) {
        sample = sound_3_wave();
        left += (gb_mem[rAUDTERM] & AUDTERM_3_LEFT) ? sample : 0;
        right += (gb_mem[rAUDTERM] & AUDTERM_3_RIGHT) ? sample : 0;
    }

    if ((s4.on) && (state->sound_channels[3])) {
        sample = (INT16_MAX/15) * s4.volume;
        sample *= !(s4.lfsr & 1);
        left += (gb_mem[rAUDTERM] & AUDTERM_4_LEFT) ? sample : 0;
        right += (gb_mem[rAUDTERM] & AUDTERM_4_RIGHT) ? sample : 0;
    }

    left >>= 1;
    left = (left / 7) * ((gb_mem[rAUDVOL] >> 4) & 7);
    left = left > INT16_MAX ? INT16_MAX : left;
    left = left < INT16_MIN ? INT16_MIN : left;

    right >>= 1;
    right = (right / 7) * (gb_mem[rAUDVOL] & 7);
    right = right > INT16_MAX ? INT16_MAX : right;
    right = right < INT16_MIN ? INT16_MIN : right;

    *(int16_t *)&sound_buffer[sample_index] = (int16_t)left;
    *(int16_t *)&sound_buffer[sample_index + SAMPLE_SIZE] = (int16_t)right;
    sample_index += (SAMPLE_SIZE * 2);
    if (sample_index >= CHANNEL_BUF_SIZE) {
        apu_sync();
    }
}

void volume_tick(t_sound *s)
{
    if ((!s->on) || (!s->env_sweep))
        return ;
    s->env_ctr++;
    if (s->env_ctr < s->env_sweep)
        return ;
    s->env_ctr -= s->env_sweep;
    if ((s->env_dir) && (s->volume < 15))
        s->volume++;
    if ((!s->env_dir) && (s->volume > 0))
        s->volume--;
}

void length_tick(t_sound *s, uint32_t mask)
{
    if (!s->is_len_counter) {
        return ;
    }
    s->length = (s->length + 1) & mask;
    if ((s->on) && (s->length == 0)) {
        s->on = 0;
    }
}

void sweep_calc()
{
    uint32_t shadow_freq = s1.freq;
    if (s1.sweep_dir) {
        shadow_freq -= shadow_freq >> s1.sweep_shift;
    } else {
        shadow_freq += shadow_freq >> s1.sweep_shift;
    }
    if (shadow_freq > 2047) {
        s1.on = 0;
        shadow_freq = s1.freq;
    }
    s1.freq = shadow_freq;
    gb_mem[rAUD1HIGH] = (gb_mem[rAUD1HIGH] & 0b11111000) | (s1.freq >> 8);
    gb_mem[rAUD1LOW] = s1.freq & 255;
}

void    sweep_tick()
{
    if ((!s1.on) || (!s1.sweep_time) || (!s1.sweep_shift))
        return ;
    s1.sweep_ctr++;
    if (s1.sweep_ctr < s1.sweep_time)
        return ;
    s1.sweep_ctr -= s1.sweep_time;
    sweep_calc();
}

void lfsr()
{
    uint32_t ticks, new_bit;

    if ((!s4.on) || (!s4.freq)) {
        return ;
    }
    ticks = 4194304 / s4.freq;
    for (; s4.cycles >= ticks; s4.cycles -= ticks) {
        new_bit = ((s4.lfsr >> 1) & 1) ^ (s4.lfsr & 1);
        s4.lfsr >>= 1;
        s4.lfsr &= ~(1 << 14);
        s4.lfsr |= (new_bit << 14);
        if (s4.lfsr_width) {
            s4.lfsr &= ~(1 << 6);
            s4.lfsr |= (new_bit << 6);
        }
    }
}

void    apu_update(uint8_t *gb_mem, t_state *state, int cycles)
{
    static uint32_t volume, sweep, length, samples;

    if (!sdl_audio_device)
        return ;

    (void)state;

    s1.cycles += cycles ;
    s2.cycles += cycles ;
    s3.cycles += cycles ;
    s4.cycles += cycles ;
    lfsr();

    volume += cycles ;
    if (volume >= VOLUME_CLOCK) {
        volume -= VOLUME_CLOCK ;
        volume_tick(&s1);
        volume_tick(&s2);
        volume_tick(&s4);
    }

    sweep += cycles ;
    if (sweep >= SWEEP_CLOCK) {
        sweep -= SWEEP_CLOCK ;
        sweep_tick();
    }

    length += cycles ;
    if (length >= LENGTH_CLOCK) {
        length -= LENGTH_CLOCK ;
        length_tick(&s1, 63);
        length_tick(&s2, 63);
        length_tick(&s3, 255);
        length_tick(&s4, 63);
    }

    samples += cycles ;
    if (samples >= SAMPLE_CLOCK) {
        samples -= SAMPLE_CLOCK ;
        write_sample();
    }

    gb_mem[rAUDENA] = (gb_mem[rAUDENA] & 128) | (s1.on<<0) | (s2.on<<1) | (s3.on<<2) | (s4.on<<3);
}


void MyAudioCallback(void *userdata, Uint8 *stream, int len)
{
    (void)userdata;

    if (!sdl_audio_device)
        return ;
    memcpy(stream, sound_buffer, len);
    audio_done = 1;
}

/* gui_init() must be called first because it calls SDL_Init() */
void    apu_init()
{
    uint32_t i, enabled[] = {1, 1, 1, 1};

    SDL_memset(&sdl_received_spec, 0, sizeof(SDL_AudioSpec));
    SDL_memset(&sdl_wanted_spec, 0, sizeof(SDL_AudioSpec));
    sdl_wanted_spec.freq     = SAMPLING_FREQUENCY;
    sdl_wanted_spec.format   = AUDIO_S16;
    sdl_wanted_spec.channels = NUM_CHANNELS;
    sdl_wanted_spec.samples  = NUM_SAMPLES;
    sdl_wanted_spec.callback = MyAudioCallback;
    sdl_audio_device = SDL_OpenAudioDevice(NULL, 0, &sdl_wanted_spec, &sdl_received_spec, 0);

    if (!sdl_audio_device)
        return ;

    if (sdl_wanted_spec.freq != sdl_received_spec.freq)
        printf("    sound freq: wanted = %d, received = %d\n", sdl_wanted_spec.freq,     sdl_received_spec.freq);
    if (sdl_wanted_spec.format != sdl_received_spec.format)
        printf("  sound format: wanted = %d, received = %d\n", sdl_wanted_spec.format,   sdl_received_spec.format);
    if (sdl_wanted_spec.channels != sdl_received_spec.channels)
        printf("sound channels: wanted = %d, received = %d\n", sdl_wanted_spec.channels, sdl_received_spec.channels);
    if (sdl_wanted_spec.samples != sdl_received_spec.samples)
        printf(" sound samples: wanted = %d, received = %d\n", sdl_wanted_spec.samples,  sdl_received_spec.samples);

    SDL_PauseAudioDevice(sdl_audio_device, 0);
    for (i=0; i<4; i++)
        state->sound_channels[i] = enabled[i];
    return ;
}

void    apu_cleanup()
{
    if (!sdl_audio_device)
        return ;
    SDL_CloseAudioDevice(sdl_audio_device);
    sdl_audio_device = 0;
}
