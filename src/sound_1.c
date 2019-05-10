#include "gb.h"
#include "sound.h"

extern uint8_t  sound_1_buffer[channel_buf_size];

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
