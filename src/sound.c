#include "gb.h"
#include <SDL.h>

/* http://gbdev.gg8.se/wiki/articles/Sound_Controller */
/* http://gbdev.gg8.se/wiki/articles/Gameboy_sound_hardware */
/* https://ia801906.us.archive.org/19/items/GameBoyProgManVer1.1/GameBoyProgManVer1.1.pdf */

#define VOLUME_CLOCK     (4194304 /  64)
#define SWEEP_CLOCK      (4194304 / 128)
#define LENGTH_CLOCK     (4194304 / 256)
#define FREQUENCY_CLOCK  (4194304 / 512)

#define SAMPLING_FREQUENCY          96000
#define NUM_SAMPLES                 32
#define NUM_CHANNELS                2
#define SAMPLE_SIZE                 2
#define CHANNEL_BUF_SIZE            (NUM_SAMPLES * SAMPLE_SIZE * NUM_CHANNELS)

#define MASTER_VOLUME_RIGHT         (gb_mem[0xff24] & 0x03)
#define MASTER_VOLUME_LEFT          ((gb_mem[0xff24] >> 4) & 0x03)

#define IS_SOUND_ENABLED            (gb_mem[0xff26] & 0x80 ? true : false)

#define IS_SOUND_1_RIGHT_ENABLED    (gb_mem[0xff25] & 0x01 ? true : false)
#define IS_SOUND_2_RIGHT_ENABLED    (gb_mem[0xff25] & 0x02 ? true : false)
#define IS_SOUND_3_RIGHT_ENABLED    (gb_mem[0xff25] & 0x04 ? true : false)
#define IS_SOUND_4_RIGHT_ENABLED    (gb_mem[0xff25] & 0x08 ? true : false)

#define IS_SOUND_1_LEFT_ENABLED     (gb_mem[0xff25] & 0x10 ? true : false)
#define IS_SOUND_2_LEFT_ENABLED     (gb_mem[0xff25] & 0x20 ? true : false)
#define IS_SOUND_3_LEFT_ENABLED     (gb_mem[0xff25] & 0x40 ? true : false)
#define IS_SOUND_4_LEFT_ENABLED     (gb_mem[0xff25] & 0x80 ? true : false)

#define NR10        gb_mem[0xff10]
#define NR11        gb_mem[0xff11]
#define NR12        gb_mem[0xff12]
#define NR13        gb_mem[0xff13]
#define NR14        gb_mem[0xff14]

#define NR20        gb_mem[0xff15]
#define NR21        gb_mem[0xff16]
#define NR22        gb_mem[0xff17]
#define NR23        gb_mem[0xff18]
#define NR24        gb_mem[0xff19]

#define NR30        gb_mem[0xff1a]
#define NR31        gb_mem[0xff1b]
#define NR32        gb_mem[0xff1c]
#define NR33        gb_mem[0xff1d]
#define NR34        gb_mem[0xff1e]

#define NR40        gb_mem[0xff1f]
#define NR41        gb_mem[0xff20]
#define NR42        gb_mem[0xff21]
#define NR43        gb_mem[0xff22]
#define NR44        gb_mem[0xff23]

#define NR50        gb_mem[0xff24]
#define NR51        gb_mem[0xff25]
#define NR52        gb_mem[0xff26]

#define ADDR_NR10   0xff10
#define ADDR_NR11   0xff11
#define ADDR_NR12   0xff12
#define ADDR_NR13   0xff13
#define ADDR_NR14   0xff14

#define ADDR_NR20   0xff15
#define ADDR_NR21   0xff16
#define ADDR_NR22   0xff17
#define ADDR_NR23   0xff18
#define ADDR_NR24   0xff19

#define ADDR_NR30   0xff1a
#define ADDR_NR31   0xff1b
#define ADDR_NR32   0xff1c
#define ADDR_NR33   0xff1d
#define ADDR_NR34   0xff1e

#define ADDR_NR40   0xff1f
#define ADDR_NR41   0xff20
#define ADDR_NR42   0xff21
#define ADDR_NR43   0xff22
#define ADDR_NR44   0xff23

#define ADDR_NR50   0xff24
#define ADDR_NR51   0xff25
#define ADDR_NR52   0xff26

#define             S1_IS_SWEEP_DECREASE    ((NR10 >> 3)   & 0x01)         //read each time
#define             S1_SWEEP_SHIFT_NUMBER   (NR10          & 0x07)         //read each time
#define             S1_DUTY_CYCLE           ((NR11 >> 6)   & 0x03)         //read each time
#define             S1_IS_LENGTH_ENABLED    ((NR14 >> 6)   & 0x01)         //read each time

#define             S2_DUTY_CYCLE           ((NR21 >> 6)   & 0x03)         //read each time
#define             S2_IS_LENGTH_ENABLED    ((NR24 >> 6)   & 0x01)         //read each time

#define             S3_IS_LENGTH_ENABLED    ((NR34 >> 6)   & 0x01)         //read each time
#define             S4_IS_LENGTH_ENABLED    ((NR44 >> 6)   & 0x01)         //read each time

typedef struct  s_sound
{
    int   sweep_time;              //nr10 bits 6-4
    int   sound_length;            //nr11 bits 5-0
    int   sound_volume;            //nr12 bits 7-4
    int   is_volume_increase;      //nr12 bit  3
    int   envelope_length;         //nr12 bits 2-0
    int   frequency;               //nr14 bits 2-0, nr13 bits 7-0
    int   is_enabled;              //nr14 bit  7
    int   volume_counter;
    int   sweep_counter;
    int   length_counter;
    int   sample_counter;
    int   frequency_counter;

}               t_sound;

SDL_AudioSpec                sdl_wanted_spec;
SDL_AudioDeviceID            sdl_audio_device = 0;

uint8_t  sound_1_buffer[CHANNEL_BUF_SIZE] = {0};
uint8_t  sound_2_buffer[CHANNEL_BUF_SIZE] = {0};
uint8_t  sound_3_buffer[CHANNEL_BUF_SIZE] = {0};
uint8_t  sound_4_buffer[CHANNEL_BUF_SIZE] = {0};

t_sound   s1;
t_sound   s2;
t_sound   s3;
t_sound   s4;


void    sound_nr10_update(uint8_t data)
{
    uint8_t     *gb_mem = state->gameboy_memory;

    NR10 = data;
    s1.sweep_time           = (NR10 >> 4)   & 0x07;         //set when nr10 written to
}

void    sound_nr11_update(uint8_t data)
{
    uint8_t     *gb_mem = state->gameboy_memory;
    NR11 = data;
    s1.sound_length         = 64 - (NR11          & 0x3f);         //set when nr11 written to
}

void    sound_nr12_update(uint8_t data)
{
    uint8_t     *gb_mem = state->gameboy_memory;
    NR12 = data;
    s1.sound_volume         = (NR12 >> 4)   & 0x0f;         //set when nr12 written to
    s1.is_volume_increase   = (NR12 >> 3)   & 0x01;         //set when nr12 written to
    s1.envelope_length      = NR12          & 0x07;         //set when nr12 written to
}

void    sound_nr13_update(uint8_t data)
{
    uint8_t     *gb_mem = state->gameboy_memory;
    NR13 = data;
    s1.frequency            = ((NR14 & 0x07) << 8) | NR13;  //set when nr13 or nr14 written to
}

void    sound_1_init()
{
    uint8_t     *gb_mem = state->gameboy_memory;
    sound_nr12_update(NR12);                                //set volume
    sound_nr13_update(NR13);                                //set frequency
    s1.volume_counter = 0;
    s1.sweep_counter = 0;
    s1.length_counter = 0;
    s1.sample_counter = 0;
    s1.is_enabled = true;
}

void    sound_nr14_update(uint8_t data)
{
    uint8_t     *gb_mem = state->gameboy_memory;
    NR14 = data;
    s1.frequency            = ((NR14 & 0x07) << 8) | NR13;  //set when nr13 or nr14 written to
    if (NR14 & 0x80)        sound_1_init();
}

void    sound_nr21_update(uint8_t data)
{
    uint8_t     *gb_mem = state->gameboy_memory;
    NR21 = data;
    s2.sound_length         = 64 - (NR21          & 0x3f);         //set when nr21 written to
}

void    sound_nr22_update(uint8_t data)
{
    uint8_t     *gb_mem = state->gameboy_memory;
    NR22 = data;
    s2.sound_volume         = (NR22 >> 4)   & 0x0f;         //set when nr22 written to
    s2.is_volume_increase   = (NR22 >> 3)   & 0x01;         //set when nr22 written to
    s2.envelope_length      = NR22          & 0x07;         //set when nr22 written to
}

void    sound_nr23_update(uint8_t data)
{
    uint8_t     *gb_mem = state->gameboy_memory;
    NR23 = data;
    s2.frequency            = ((NR24 & 0x07) << 8) | NR23;  //set when nr23 or nr24 written to
}

void    sound_2_init()
{
    uint8_t     *gb_mem = state->gameboy_memory;
    sound_nr22_update(NR22);                                //set volume
    sound_nr23_update(NR23);                                //set frequency
    s2.volume_counter = 0;
    s2.length_counter = 0;
    s2.sample_counter = 0;
    s2.is_enabled = true ;
}

void    sound_nr24_update(uint8_t data)
{
    uint8_t     *gb_mem = state->gameboy_memory;
    NR24 = data;
    s2.frequency            = ((NR24 & 0x07) << 8) | NR23;  //set when nr23 or nr24 written to
    if (NR24 & 0x80)         //set when nr24 written to, bit 7 set
        sound_2_init();
}

void    sound_nr30_update(uint8_t data)
{
    uint8_t     *gb_mem = state->gameboy_memory;
    NR30 = data;
    s3.is_enabled = ((NR30) >> 7) & 1;
}    //nr30 only bit 7 is writable

void    sound_nr31_update(uint8_t data)
{
    uint8_t     *gb_mem = state->gameboy_memory;
    NR31 = data;
    s3.sound_length = 256 - NR31;
}

void    sound_nr32_update(uint8_t data)
{
    uint8_t     *gb_mem = state->gameboy_memory;
    NR32 = data;
}

void    sound_3_init()
{
    uint8_t     *gb_mem = state->gameboy_memory;
    s3.length_counter = 0;
    s3.sample_counter = 0;
    s3.is_enabled = ((NR30 & 0x80) >> 7) & 1;
}

void    sound_nr33_update(uint8_t data)
{
    uint8_t     *gb_mem = state->gameboy_memory;
    NR33 = data;
    s3.frequency            = ((NR34 & 0x07) << 8) | NR33;
}

void    sound_nr34_update(uint8_t data)
{
    uint8_t     *gb_mem = state->gameboy_memory;
    NR34 = data;
    s3.frequency            = ((NR34 & 0x07) << 8) | NR33;
    if (NR34 & 0x80)
        sound_3_init();
}

void    sound_nr41_update(uint8_t data)
{
    uint8_t     *gb_mem = state->gameboy_memory;
    NR41 = data;
    s4.sound_length = 64 - (NR41 & 0x3f);
}

void    sound_nr42_update(uint8_t data)
{
    uint8_t     *gb_mem = state->gameboy_memory;
    NR42 = data;
    s4.sound_volume         = (NR42 >> 4)   & 0x0f;         //set when nr42 written to
    s4.is_volume_increase   = (NR42 >> 3)   & 0x01;         //set when nr42 written to
    s4.envelope_length      = NR42          & 0x07;         //set when nr42 written to
}

void    sound_nr43_update(uint8_t data)
{
    uint8_t     *gb_mem = state->gameboy_memory;
    NR43 = data;
}      // FIXME lfsr

void    sound_4_init()
{
    uint8_t     *gb_mem = state->gameboy_memory;
    s4.volume_counter = 0;
    s4.length_counter = 0;
    s4.sample_counter = 0;
    s4.frequency_counter = 0;
    s4.is_enabled = true;
}
void    sound_nr44_update(uint8_t data)
{
    uint8_t     *gb_mem = state->gameboy_memory;
    NR44 = data;
    if (NR44 & 0x80)
        sound_4_init();
}

void    sound_nr50_update(uint8_t data)
{
    uint8_t     *gb_mem = state->gameboy_memory;
    NR50 = data;
}

void    sound_nr51_update(uint8_t data)
{
    uint8_t     *gb_mem = state->gameboy_memory;
    NR51 = data;
}

void    sound_nr52_update(uint8_t data)
{
    uint8_t     *gb_mem = state->gameboy_memory;
    NR52 |= data & 0x80;
    if (NR52 & 0x80) return ;
/*    
    memset(&s1, 0, sizeof(s1));
    memset(&s2, 0, sizeof(s2));
    memset(&s3, 0, sizeof(s3));
    memset(&s4, 0, sizeof(s4));
*/
}    //nr52 only bit 7 is writable

void    sound_write_u8(uint16_t addr, uint8_t data)
{
    uint8_t     *gb_mem = state->gameboy_memory;
    if ((addr != ADDR_NR52) && (!(NR52 & 0x80)) )  return ;      //ignore all writes when sound off

    if (addr == ADDR_NR10) { sound_nr10_update(data); return; }
    if (addr == ADDR_NR11) { sound_nr11_update(data); return; }
    if (addr == ADDR_NR12) { sound_nr12_update(data); return; }
    if (addr == ADDR_NR13) { sound_nr13_update(data); return; }
    if (addr == ADDR_NR14) { sound_nr14_update(data); return; }

    if (addr == ADDR_NR21) { sound_nr21_update(data); return; }
    if (addr == ADDR_NR22) { sound_nr22_update(data); return; }
    if (addr == ADDR_NR23) { sound_nr23_update(data); return; }
    if (addr == ADDR_NR24) { sound_nr24_update(data); return; }

    if (addr == ADDR_NR30) { sound_nr30_update(data); return; }
    if (addr == ADDR_NR31) { sound_nr31_update(data); return; }
    if (addr == ADDR_NR32) { sound_nr32_update(data); return; }
    if (addr == ADDR_NR33) { sound_nr33_update(data); return; }
    if (addr == ADDR_NR34) { sound_nr34_update(data); return; }

    if (addr == ADDR_NR41) { sound_nr41_update(data); return; }
    if (addr == ADDR_NR42) { sound_nr42_update(data); return; }
    if (addr == ADDR_NR43) { sound_nr43_update(data); return; }
    if (addr == ADDR_NR44) { sound_nr44_update(data); return; }

    if (addr == ADDR_NR50) { sound_nr50_update(data); return; }
    if (addr == ADDR_NR51) { sound_nr51_update(data); return; }
    if (addr == ADDR_NR52) { sound_nr52_update(data); return; }
}

void    channel_volume_tick(t_sound *s0)
{
    if ((!(s0->is_enabled)) || (!(s0->envelope_length)))
        return ;
    s0->volume_counter++;
    if (s0->volume_counter < s0->envelope_length)
        return ;
    s0->volume_counter = 0; //counter - envelope_length;
    if ((s0->is_volume_increase) && (s0->sound_volume < 15))
        s0->sound_volume++;
    if ((!(s0->is_volume_increase)) && (s0->sound_volume > 0))
        s0->sound_volume--;
}

void    apu_volume_tick()
{
    uint8_t     *gb_mem = state->gameboy_memory;
    channel_volume_tick(&s1);
    channel_volume_tick(&s2);
    channel_volume_tick(&s4);
}

void    apu_sweep_tick()
{
    uint8_t     *gb_mem = state->gameboy_memory;
    uint16_t    shadow_freq;

    if ((!s1.is_enabled) || (!s1.sweep_time))
        return ;
    s1.sweep_counter++;
    if (s1.sweep_counter < s1.sweep_time)
        return ;
    s1.sweep_counter = 0;       //counter - sweep_time
    shadow_freq = s1.frequency;
    if (S1_IS_SWEEP_DECREASE)
        shadow_freq -= (shadow_freq >> S1_SWEEP_SHIFT_NUMBER);
    else
        shadow_freq += (shadow_freq >> S1_SWEEP_SHIFT_NUMBER);
    if (shadow_freq > 2047)
    {
        s1.is_enabled = false;
        return;
    }
    s1.frequency = shadow_freq;
    NR13 = shadow_freq & 0xff;
    NR14 = (NR14 & 0xf8) | (shadow_freq >> 8);
}

void    channel_length_tick(t_sound *s0, uint8_t reg)
{
    uint8_t     *gb_mem = state->gameboy_memory;
    if ((s0->is_enabled) && (s0->sound_length))
    {
        s0->length_counter++;
        if ((s0->length_counter >= s0->sound_length) && (reg & 0x40))
            s0->is_enabled = false;
    }
}

void    apu_length_tick()
{
    uint8_t     *gb_mem = state->gameboy_memory;
    channel_length_tick(&s1, NR14);
    channel_length_tick(&s2, NR24);
    channel_length_tick(&s3, NR34);
    channel_length_tick(&s4, NR44);
}

/*
void    print_channel_2()
{
    uint8_t     *gb_mem = state->gameboy_memory;
    static  uint8_t nr21, nr22, nr23, nr24;
    bool print = false;

    if (gb_mem[0xff16] != nr21) print = true;
    if (gb_mem[0xff17] != nr22) print = true;
    if (gb_mem[0xff18] != nr23) print = true;
    if (gb_mem[0xff19] != nr24) print = true;

    nr21 = gb_mem[0xff16];
    nr22 = gb_mem[0xff17];
    nr23 = gb_mem[0xff18];
    nr24 = gb_mem[0xff19];

    if (print)
        printf("nr21: %02x,  nr22: %02x,  nr23: %02x,  nr24: %02x\n", nr21, nr22, nr23, nr24);
}
*/

/*
void    print_controls()
{
    uint8_t     *gb_mem = state->gameboy_memory;
    static  uint8_t nr50, nr51, nr52;
    bool print = false;

    if (NR50 != nr50) print = true;
    if (NR51 != nr51) print = true;
    if (NR52 != nr52) print = true;

    nr50 = NR50;
    nr51 = NR51;
    nr52 = NR52;

    if (print)
        printf("nr50: %02x, nr51: %02x,  nr52: %02x\n", nr50, nr51, nr52);
}
*/

/*
void    print_channel_3()
{
    uint8_t     *gb_mem = state->gameboy_memory;
    static  uint8_t nr30, nr31, nr32, nr33, nr34;
    bool print = false;

    if (NR30 != nr30) print = true;
    if (NR31 != nr31) print = true;
    if (NR32 != nr32) print = true;
    if (NR33 != nr33) print = true;
    if (NR34 != nr34) print = true;

    nr30 = NR30;
    nr31 = NR31;
    nr32 = NR32;
    nr33 = NR33;
    nr34 = NR34;

    if (print)
    {
        printf("nr30: %02x, nr31: %02x,  nr32: %02x,  nr33: %02x,  nr34: %02x\n", nr30, nr31, nr32, nr33, nr34);
        for (int i = 0; i < 16; i++) printf("%02x ", gb_mem[0xff30 + i]);
        printf("\n\n");
    }
}
*/

void    apu_frequency_tick()
{
    uint8_t *gb_mem = state->gameboy_memory;

    if (!(s4.is_enabled))
        return ;
    s4.frequency_counter++;
    int divisor = (NR43 & 7) << 4;
    if (!divisor) divisor = 8;
    if (s4.frequency_counter < divisor)
        return ;
    s4.frequency_counter = 0;
    int new_data = (((NR43 >> 4) & 1) ^ ((NR43 >> 5) & 1)) << 7;
    new_data |= ((NR43 & 0xe0) >> 1);
    new_data |= (NR43 & 0x0f);
    if (NR43 & 8)
    {
        new_data &= 0xbf;
        new_data |= (((NR43 >> 4) & 1) ^ ((NR43 >> 5) & 1)) << 6;
    }
//    printf("NR43 %02x, %02x\n", gb_mem[0xff22], new_data);
    NR43 = new_data;
}

void    apu_update(uint8_t *gb_mem, t_state *state, int current_cycles)
{
    static uint64_t     cycles, prev_cycles;

    cycles += current_cycles;
    if ((cycles / VOLUME_CLOCK)    > (prev_cycles / VOLUME_CLOCK))      apu_volume_tick();
    if ((cycles / SWEEP_CLOCK)     > (prev_cycles / SWEEP_CLOCK))       apu_sweep_tick();
    if ((cycles / LENGTH_CLOCK)    > (prev_cycles / LENGTH_CLOCK))      apu_length_tick();
//    if ((cycles / FREQUENCY_CLOCK) > (prev_cycles / FREQUENCY_CLOCK))   apu_frequency_tick();
    prev_cycles = cycles;
    NR52 = (NR52 & 0x80) | (s1.is_enabled<<0) | (s2.is_enabled<<1) | (s3.is_enabled<<2) | (s4.is_enabled<<3);
}

int16_t SquareWave(int time, int freq, int vol, int duty)
{
    uint8_t     *gb_mem = state->gameboy_memory;
    freq = 131072 / (2048 - freq);

    uint8_t patterns[4][8] = {
        {0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,1},
        {1,0,0,0,0,1,1,1},
        {0,1,1,1,1,1,1,0}};

    if (freq > SAMPLING_FREQUENCY) freq = SAMPLING_FREQUENCY;
    int tpc = SAMPLING_FREQUENCY / freq;
    int cyclepart = time % tpc;
    if (tpc < 8) tpc |= 8;
    int idx = cyclepart / (tpc >> 3);
    int16_t result = (INT16_MAX/15) * vol * patterns[duty][idx & 7];
    return result ;
}

void    sound_1_fill_buffer()
{
    uint8_t     *gb_mem = state->gameboy_memory;
    int16_t             sample;

    (void)memset(sound_1_buffer, 0, sizeof(sound_1_buffer));

    if (!s1.is_enabled)
        return ;

    for (int i = 0; i < NUM_SAMPLES; i++)
    {
        sample = SquareWave(s1.sample_counter++, s1.frequency, s1.sound_volume, S1_DUTY_CYCLE);
        if (IS_SOUND_1_LEFT_ENABLED)
            *(int16_t *)&sound_1_buffer[i * 4] = sample;
        if (IS_SOUND_1_RIGHT_ENABLED)
            *(int16_t *)&sound_1_buffer[i * 4 + 2] = sample;
    }
}

void    sound_2_fill_buffer()
{
    uint8_t     *gb_mem = state->gameboy_memory;
    int16_t             sample;

    (void)memset(sound_2_buffer, 0, sizeof(sound_2_buffer));

    if (!s2.is_enabled)
        return ;

    for (int i = 0; i < NUM_SAMPLES; i++)
    {
        sample = SquareWave(s2.sample_counter++, s2.frequency, s2.sound_volume, S2_DUTY_CYCLE);
        if (IS_SOUND_2_LEFT_ENABLED)
            *(int16_t *)&sound_2_buffer[i * 4] = sample;
        if (IS_SOUND_2_RIGHT_ENABLED)
            *(int16_t *)&sound_2_buffer[i * 4 + 2] = sample;
    }
}

int16_t sound_3_wave(int time, int freq) {
    uint8_t     *gb_mem = state->gameboy_memory;
    freq = 65536 / (2048 - freq);
    int tpc = SAMPLING_FREQUENCY / freq;
    int cyclepart = time % tpc;
    if (tpc < 32) tpc |= 32;
    int idx = (cyclepart / (tpc >> 5)) & 31;
    uint8_t nibble = gb_mem[0xff30 + (idx >> 1)];
    if (!(idx & 1))
        nibble >>= 4;
    nibble &= 15;
    switch ((NR32 >> 5) & 3)
    {
        case 0: nibble = 0; break;
        case 2: nibble >>= 1; break;
        case 3: nibble >>= 2; break;
    }
    int16_t amplitude = nibble * (INT16_MAX/15);
    return amplitude;
}

void    sound_3_fill_buffer()
{
    uint8_t     *gb_mem = state->gameboy_memory;
    int16_t             sample;

    (void)memset(sound_3_buffer, 0, sizeof(sound_3_buffer));

    if (!s3.is_enabled)
        return ;

    for (int i = 0; i < NUM_SAMPLES; i++)
    {
        sample = sound_3_wave(s3.sample_counter++, s3.frequency);
        if (IS_SOUND_3_LEFT_ENABLED)
            *(int16_t *)&sound_3_buffer[i * 4] = sample;
        if (IS_SOUND_3_RIGHT_ENABLED)
            *(int16_t *)&sound_3_buffer[i * 4 + 2] = sample;
    }
}

void    sound_4_fill_buffer()
{
    uint8_t     *gb_mem = state->gameboy_memory;
    int16_t     sample;


    (void)memset(sound_4_buffer, 0, sizeof(sound_4_buffer));

    if ((!s4.is_enabled) || (!s4.sound_volume) || (!s4.sound_length))
        return ;

    sample = rand() & 1; //~((NR43 >> 4) & 1);
    sample *= ((INT16_MAX/15) * s4.sound_volume);

    for (int i = 0; i < NUM_SAMPLES; i++)
    {
        if (IS_SOUND_4_LEFT_ENABLED)
            *(int16_t *)&sound_4_buffer[i * 4] = sample;
        if (IS_SOUND_4_RIGHT_ENABLED)
            *(int16_t *)&sound_4_buffer[i * 4 + 2] = sample;
    }
}

void MyAudioCallback(void *userdata, Uint8 *stream, int len)
{
    uint8_t     *gb_mem = state->gameboy_memory;
    uint64_t    left, right;

    (void)userdata;
    (void)memset(stream, 0, len);

    if (!sdl_audio_device)
        return ;

    sound_1_fill_buffer();
    sound_2_fill_buffer();
    sound_3_fill_buffer();
    sound_4_fill_buffer();

    for (int i = 0; i < NUM_SAMPLES; i++)
    {
        int j = i * (NUM_CHANNELS * SAMPLE_SIZE);

        left = 0;
        left += *(int16_t *)&sound_1_buffer[j];
        left += *(int16_t *)&sound_2_buffer[j];
        left += *(int16_t *)&sound_3_buffer[j];
        left += *(int16_t *)&sound_4_buffer[j];
        left = (left / 7) * MASTER_VOLUME_LEFT;

        right = 0;
        right += *(int16_t *)&sound_1_buffer[j + SAMPLE_SIZE];
        right += *(int16_t *)&sound_2_buffer[j + SAMPLE_SIZE];
        right += *(int16_t *)&sound_3_buffer[j + SAMPLE_SIZE];
        right += *(int16_t *)&sound_4_buffer[j + SAMPLE_SIZE];
        right = (right / 7) * MASTER_VOLUME_RIGHT;

        left >>= 1;
        right >>= 1;
        left &= INT16_MAX;
        right &= INT16_MAX;

        *(int16_t *)&stream[j] = (int16_t)left;
        *(int16_t *)&stream[j + SAMPLE_SIZE] = (int16_t)right;
    }
}

/* gui_init() must be called first because it calls SDL_Init() */
void    apu_init()
{
    uint8_t     *gb_mem = state->gameboy_memory;

    SDL_memset(&sdl_wanted_spec, 0, sizeof(sdl_wanted_spec));
    sdl_wanted_spec.freq     = SAMPLING_FREQUENCY;
    sdl_wanted_spec.format   = AUDIO_S16;
    sdl_wanted_spec.channels = NUM_CHANNELS;
    sdl_wanted_spec.samples  = NUM_SAMPLES;
    sdl_wanted_spec.callback = MyAudioCallback;

    sdl_audio_device = SDL_OpenAudioDevice(NULL, 0, &sdl_wanted_spec, NULL, 0);
    if (!sdl_audio_device)
        return ;
    SDL_PauseAudioDevice(sdl_audio_device, 0);
    return ;
}

void    apu_cleanup()
{
    if (!sdl_audio_device)
        return ;
    SDL_CloseAudioDevice(sdl_audio_device);
    sdl_audio_device = 0;
}
