#include "gb.h"
#include "sound.h"

extern uint8_t  sound_1_buffer[channel_buf_size];

/* http://gbdev.gg8.se/wiki/articles/Sound_Controller */
/* http://gbdev.gg8.se/wiki/articles/Gameboy_sound_hardware */
/* https://ia801906.us.archive.org/19/items/GameBoyProgManVer1.1/GameBoyProgManVer1.1.pdf */

#define gb_mem  state->gameboy_memory

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
    uint8_t     sweep_time;              //nr10 bits 6-4
    uint8_t     sound_length;            //nr11 bits 5-0
    uint8_t     sound_volume;            //nr12 bits 7-4
    bool        is_volume_increase;      //nr12 bit  3
    uint8_t     envelope_length;         //nr12 bits 2-0
    uint16_t    frequency;               //nr14 bits 2-0, nr13 bits 7-0
    bool        is_enabled;              //nr14 bit  7

    uint32_t     volume_counter;
    uint32_t     sweep_counter;
    uint32_t     length_counter;

}               t_sound;



static t_sound   s1;
static t_sound   s2;
static t_sound   s3;
static t_sound   s4;

void    sound_nr10_update(uint8_t data)
{
    NR10 = data;
    s1.sweep_time           = (NR10 >> 4)   & 0x07;         //set when nr10 written to
}

void    sound_nr11_update(uint8_t data)
{
    NR11 = data;
    s1.sound_length         = NR11          & 0x3f;         //set when nr11 written to
}

void    sound_nr12_update(uint8_t data)
{
    NR12 = data;
    s1.sound_volume         = (NR12 >> 4)   & 0x0f;         //set when nr12 written to
    s1.is_volume_increase   = (NR12 >> 3)   & 0x01;         //set when nr12 written to
    s1.envelope_length      = NR12          & 0x07;         //set when nr12 written to
}

void    sound_nr13_update(uint8_t data)
{
    NR13 = data;
    s1.frequency            = ((NR14 & 0x07) << 8) | NR13;  //set when nr13 or nr14 written to
}

void    sound_nr14_update(uint8_t data)
{
    NR14 = data;
    s1.frequency            = ((NR14 & 0x07) << 8) | NR13;  //set when nr13 or nr14 written to
    s1.is_enabled           = (NR14 >> 7)   & 0x01;         //set when nr14 written to, bit 7 set
    if (s1.is_enabled)      sound_1_init();
}

void    sound_1_init()
{    
    sound_nr12_update(NR12);                                //set volume
    sound_nr13_update(NR13);                                //set frequency    
    s1.volume_counter = 0;
    s1.sweep_counter = 0;
    s1.length_counter = 0;    
}

void    sound_nr21_update(uint8_t data)
{
    NR21 = data;
    s2.sound_length         = NR21          & 0x3f;         //set when nr21 written to
}

void    sound_nr22_update(uint8_t data)
{
    NR22 = data;
    s2.sound_volume         = (NR22 >> 4)   & 0x0f;         //set when nr22 written to
    s2.is_volume_increase   = (NR22 >> 3)   & 0x01;         //set when nr22 written to
    s2.envelope_length      = NR22          & 0x07;         //set when nr22 written to
}

void    sound_nr23_update(uint8_t data)
{
    NR23 = data;
    s2.frequency            = ((NR24 & 0x07) << 8) | NR23;  //set when nr23 or nr24 written to
}

void    sound_2_init()
{    
    sound_nr22_update(NR22);                                //set volume    
    sound_nr23_update(NR23);                                //set frequency    
    s1.volume_counter = 0;
    s1.length_counter = 0;
}

void    sound_nr24_update(uint8_t data)
{
    NR24 = data;
    s2.frequency            = ((NR24 & 0x07) << 8) | NR23;  //set when nr23 or nr24 written to
    s2.is_enabled           = (NR24 >> 7)   & 0x01;         //set when nr24 written to, bit 7 set
    if (s2.is_enabled)      sound_2_init();
}

void    sound_nr30_update(uint8_t data) { NR30 |= data & 0x80; if (!(NR30 & 0x80)) s3.is_enabled = false;}    //nr30 only bit 7 is writable
void    sound_nr31_update(uint8_t data) { NR31 = data; s3.sound_length = NR31; }
void    sound_nr32_update(uint8_t data) { NR32 = data; }
void    sound_nr33_update(uint8_t data) { NR33 = data; s3.frequency = ((NR34 & 0x07) << 8) | NR33; }
void    sound_3_init() {}
void    sound_nr34_update(uint8_t data)
{
    NR34 = data;
    s3.frequency            = ((NR34 & 0x07) << 8) | NR33;
    s3.is_enabled           = (NR34 >> 7) & 0x01;
    if (s3.is_enabled)      sound_3_init();    
}

void    sound_nr41_update(uint8_t data) { NR41 = data; s4.sound_length = NR41 & 0x3f; }
void    sound_nr42_update(uint8_t data)
{
    NR42 = data;
    s4.sound_volume         = (NR42 >> 4)   & 0x0f;         //set when nr42 written to
    s4.is_volume_increase   = (NR42 >> 3)   & 0x01;         //set when nr42 written to
    s4.envelope_length      = NR42          & 0x07;         //set when nr42 written to
}

void    sound_nr43_update(uint8_t data) {NR43 = data;}      // FIXME lfsr
void    sound_4_init() {}
void    sound_nr44_update(uint8_t data)
{
    NR44 = data;
    s4.is_enabled           = (NR44 >> 7) & 0x01;
    if (s4.is_enabled)      sound_4_init();
}

void    sound_nr50_update(uint8_t data) { NR50 = data; }
void    sound_nr51_update(uint8_t data) { NR51 = data; }
void    sound_nr52_update(uint8_t data) { NR52 |= data & 0x80; }    //nr52 only bit 7 is writable

void    sound_write_u8(uint16_t addr, uint8_t data)
{
    if ((addr != ADDR_NR52) && (!(nr52 & 0x80)) )  return ;      //ignore all writes when sound off

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

#define VOLUME_CLOCK     (4194304 /  64)
#define SWEEP_CLOCK      (4194304 / 128)
#define LENGTH_CLOCK     (4194304 / 256)

void    apu_volume_tick()
{
}

void    apu_sweep_tick()
{
    uint16_t    shadow_freq;

    if ((!s1.is_enabled) || (!s1.sweep_time))
        return ;
    s1.sweep_counter++;
    if (s1.sweep_counter < s1.sweep_time)
        return ;
    s1.sweep_counter = 0;
    shadow_freq = s1.frequency;
    if (S1_IS_SWEEP_DECREASE)
        shadow_freq -= shadow_freq >> S1_SWEEP_SHIFT_NUMBER;
    else
        shadow_freq += shadow_freq >> S1_SWEEP_SHIFT_NUMBER;
    if (shadow_freq > 2047)
    {
        s1.is_enabled = false;
        return;
    }
    s1.frequency = shadow_freq;
    NR13 = shadow_freq & 0xff;
    NR14 = (NR14 & 0xf8) | (shadow_freq >> 8);
}



#define             S1_IS_SWEEP_DECREASE    ((NR10 >> 3)   & 0x01)         //read each time
#define             S1_SWEEP_SHIFT_NUMBER   (NR10          & 0x07)         //read each time
#define             S1_DUTY_CYCLE           ((NR11 >> 6)   & 0x03)         //read each time
#define             S1_IS_LENGTH_ENABLED    ((NR14 >> 6)   & 0x01)         //read each time

#define             S2_DUTY_CYCLE           ((NR21 >> 6)   & 0x03)         //read each time
#define             S2_IS_LENGTH_ENABLED    ((NR24 >> 6)   & 0x01)         //read each time

#define             S3_IS_LENGTH_ENABLED    ((NR34 >> 6)   & 0x01)         //read each time
#define             S4_IS_LENGTH_ENABLED    ((NR44 >> 6)   & 0x01)         //read each time


void    apu_length_tick()
{
}

void    apu_clock(int current_cycles)
{
    static uint64_t     cycles, prev_cycles;

    cycles += current_cycles;

    if ((cycles / VOLUME_CLOCK) > (prev_cycles / VOLUME_CLOCK)   apu_volume_tick();
    if ((cycles / SWEEP_CLOCK ) > (prev_cycles / SWEEP_CLOCK)    apu_sweep_tick();
    if ((cycles / LENGTH_CLOCK) > (prev_cycles / LENGTH_CLOCK)   apu_length_tick();

    prev_cycles = cycles;
}

/////////////////////



    if (!(gb_mem[0xff14] & 0x80))
    {
        sound_1_cycles = 0;
        sound_1_prev_cycles = 0;
        return ;
    }
//    gb_mem[0xff26] |= 1;

    sound_1_cycles += current_cycles;

    sweep_step = ((gb_mem[0xff10] >> 4) & 7) * (4194304 / 128);
    sweep_shift = gb_mem[0xff10] & 7;
    if ((sweep_step) && (sweep_shift))
    {
        if ((sound_1_cycles / sweep_step) > (sound_1_prev_cycles / sweep_step))
        {
            sweep_freq = ((gb_mem[0xff14] & 7) << 8) | gb_mem[0xff13];
            sweep_calc = sweep_freq >> sweep_shift;
            if (gb_mem[0xff10] & 0x08)
                sweep_freq -= sweep_calc;
            else
                sweep_freq += sweep_calc;

            if (sweep_freq < 2048)
            {
                gb_mem[0xff14] = (gb_mem[0xff14] & 0xf8) | ((sweep_freq >> 8) & 7);
                gb_mem[0xff13] = sweep_freq & 0xff;
            }
            else
            {
                gb_mem[0xff14] &= ~0x80;
                sweep_freq = 0;
            }
        }
    }















void    sound_1_update(int current_cycles)
{
    uint8_t *gb_mem = state->gameboy_memory;
    uint64_t envelope_step, sweep_step, sweep_freq, sweep_calc;
    uint8_t  envelope_volume, envelope_direction, sweep_shift, length_calc;
    static uint64_t     sound_1_cycles, sound_1_prev_cycles;


    if (!(gb_mem[0xff14] & 0x80))
    {
        sound_1_cycles = 0;
        sound_1_prev_cycles = 0;
        return ;
    }
//    gb_mem[0xff26] |= 1;

    sound_1_cycles += current_cycles;

    sweep_step = ((gb_mem[0xff10] >> 4) & 7) * (4194304 / 128);
    sweep_shift = gb_mem[0xff10] & 7;
    if ((sweep_step) && (sweep_shift))
    {
        if ((sound_1_cycles / sweep_step) > (sound_1_prev_cycles / sweep_step))
        {
            sweep_freq = ((gb_mem[0xff14] & 7) << 8) | gb_mem[0xff13];
            sweep_calc = sweep_freq >> sweep_shift;
            if (gb_mem[0xff10] & 0x08)
                sweep_freq -= sweep_calc;
            else
                sweep_freq += sweep_calc;

            if (sweep_freq < 2048)
            {
                gb_mem[0xff14] = (gb_mem[0xff14] & 0xf8) | ((sweep_freq >> 8) & 7);
                gb_mem[0xff13] = sweep_freq & 0xff;
            }
            else
            {
                gb_mem[0xff14] &= ~0x80;
                sweep_freq = 0;
            }
        }
    }

    if ((sound_1_cycles / (4194304 / 256)) > (sound_1_prev_cycles / (4194304 / 256)))
    {
        length_calc = gb_mem[0xff11] & 0x3f;
        if (length_calc)
        {
            length_calc--;
            gb_mem[0xff11] = (gb_mem[0xff11] & 0xc0) | (length_calc & 0x3f);
            if ((gb_mem[0xff14] & 0x40) && (!length_calc))
            {
//                gb_mem[0xff12] &= 0x0f;
                gb_mem[0xff26] &= ~1;   //nr52
            }
        }
    }

    envelope_step = (gb_mem[0xff12] & 7) * (4194304 / 64);
    if (envelope_step)
    {
        envelope_volume = (gb_mem[0xff12] >> 4) & 15;
        envelope_direction = (gb_mem[0xff12] >> 3) & 1;

        if ((sound_1_cycles / envelope_step) > (sound_1_prev_cycles / envelope_step))
        {
            if ((envelope_volume) && (!envelope_direction))
            {
                envelope_volume--;
                gb_mem[0xff12] = ((envelope_volume & 15) << 4) | (gb_mem[0xff12] & 15);
            }

            if ((envelope_volume < 15) && (envelope_direction))
            {
                envelope_volume++;
                gb_mem[0xff12] = ((envelope_volume & 15) << 4) | (gb_mem[0xff12] & 15);
            }
        }
    }
    sound_1_prev_cycles = sound_1_cycles;
}

int16_t SquareWave(int time, int freq, int vol, int duty)
{
    uint8_t patterns[4][8] = {
        {0,0,0,0,0,0,0,1},
        {0,0,0,0,0,0,1,1},
        {0,0,0,0,1,1,1,1},
        {0,0,1,1,1,1,1,1}};

    if ((!freq) || (!vol))
        return 0;

    int tpc0 = sampling_frequency / freq;
    int tpc1 = (sampling_frequency / freq) >> 3;
    int idx;
    if (tpc1)
        idx = (time % tpc0) / tpc1;
    else
        idx = 0;
    int16_t result = (INT16_MAX / 15) * vol * patterns[duty][idx % 8];
    return result ;
}

void    sound_1_fill_buffer()
{

    uint8_t             *gb_mem = state->gameboy_memory;
    static  int         ticks;
    int16_t             sample;

    (void)memset(sound_1_buffer, 0, sizeof(sound_1_buffer));

    if (!is_sound_enabled)
        return ;

    for (int i = 0; i < num_samples; i++)
    {
        sample = SquareWave(ticks++, nr1_freq, nr1_vol, nr1_duty);
        if (is_sound_1_left_enabled)
            *(int16_t *)&sound_1_buffer[i * 4] = sample;
        if (is_sound_1_right_enabled)
            *(int16_t *)&sound_1_buffer[i * 4 + 2] = sample;
    }
}
