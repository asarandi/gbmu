#include "gb.h"
#include "sound.h"

extern uint8_t  sound_2_buffer[channel_buf_size];

void    sound_2_update(int current_cycles)
{
    uint8_t *gb_mem = state->gameboy_memory;
    uint64_t envelope_step;
    uint8_t  envelope_volume, envelope_direction, length_calc;
    static uint64_t     sound_2_cycles, sound_2_prev_cycles;


    if (!(gb_mem[0xff19] & 0x80))
    {
        sound_2_cycles = 0;
        sound_2_prev_cycles = 0;
        return ;
    }
//    gb_mem[0xff26] |= 2;

    sound_2_cycles += current_cycles;

    if ((sound_2_cycles / (4194304 / 256)) > (sound_2_prev_cycles / (4194304 / 256)))
    {
        length_calc = gb_mem[0xff16] & 0x3f;
        if (length_calc)
        {
            length_calc--;
            gb_mem[0xff16] = (gb_mem[0xff16] & 0xc0) | (length_calc & 0x3f);
            if ((gb_mem[0xff19] & 0x40) && (!length_calc))
            {
//                gb_mem[0xff17] &= 0x0f;     //set volume to 0
                gb_mem[0xff26] &= ~2;   //nr52
            }
        }
    }

    envelope_step = (gb_mem[0xff17] & 7) * (4194304 / 64);
    if (envelope_step)
    {
        envelope_volume = (gb_mem[0xff17] >> 4) & 15;
        envelope_direction = (gb_mem[0xff17] >> 3) & 1;

        if ((sound_2_cycles / envelope_step) > (sound_2_prev_cycles / envelope_step))
        {
            if ((envelope_volume) && (!envelope_direction))
            {
                envelope_volume--;
                gb_mem[0xff17] = ((envelope_volume & 15) << 4) | (gb_mem[0xff17] & 15);
            }

            if ((envelope_volume < 15) && (envelope_direction))
            {
                envelope_volume++;
                gb_mem[0xff17] = ((envelope_volume & 15) << 4) | (gb_mem[0xff17] & 15);
            }
        }
    }

    sound_2_prev_cycles = sound_2_cycles;
}

void    sound_2_fill_buffer()
{

    uint8_t             *gb_mem = state->gameboy_memory;
    double              duty, freq, vol_left, vol_right;
    static  uint64_t    ticks;

    (void)memset(sound_2_buffer, 0, sizeof(sound_2_buffer));

    if (!is_sound_enabled)
        return ;

    duty = get_duty_cycles(gb_mem[0xff16]);

    freq = nr2_freq;
    vol_left = (1.0 / 15) * nr2_vol;
    vol_right = (1.0 / 15) * nr2_vol;

    for (int i = 0; i < num_samples; i++)
    {
        if (is_sound_2_left_enabled)
            *(int16_t *)&sound_2_buffer[i * 4] = SquareWave(ticks, freq, vol_left, duty);

        if (is_sound_2_right_enabled)
            *(int16_t *)&sound_2_buffer[i * 4 + 2] = SquareWave(ticks, freq, vol_right, duty);

        ticks++;
    }
}
