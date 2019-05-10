#include "gb.h"
#include "sound.h"

extern uint8_t  sound_3_buffer[channel_buf_size];

static  uint64_t    ticks;

void    sound_3_update(int current_cycles)
{
    uint8_t *gb_mem = state->gameboy_memory;
    static uint64_t     sound_3_cycles, sound_3_prev_cycles;
    uint8_t length_calc;

    if (!(gb_mem[0xff1e] & 0x80))
    {
        sound_3_cycles = 0;
        sound_3_prev_cycles = 0;
        ticks = 0;
        return ;
    }
    gb_mem[0xff26] |= 4;

    sound_3_cycles += current_cycles;

    if ((sound_3_cycles / (4194304 / 256)) > (sound_3_prev_cycles / (4194304 / 256)))
    {
        length_calc = gb_mem[0xff1b];
        if (length_calc)
        {
            length_calc--;
            gb_mem[0xff1b] = length_calc;
            if ((gb_mem[0xff1e] & 0x40) && (!length_calc))
            {
                gb_mem[0xff1c] &= ~0x60;    //set output level to 0
                gb_mem[0xff26] &= ~4;       //clear nr52 flag for channel 3
            }
        }
    }

    sound_3_prev_cycles = sound_3_cycles;
}

int16_t sound_3_wave(uint64_t time, double freq, double amp) {
    uint8_t *gb_mem = state->gameboy_memory;
    int16_t result = 0;
    double tpc = sampling_frequency / freq;
    double cyclepart = fmod(time, tpc);
    uint8_t idx = round(cyclepart) / 32;
    uint8_t nibble = gb_mem[0xff30 + (idx >> 1)];
    if (!(idx & 1))
        nibble >>= 4;
    nibble &= 15;
    amp = (1.0 / 15) * nibble;  /* FIXME */
    int16_t amplitude = INT16_MAX * amp;

    uint8_t volume = (gb_mem[0xff1c] >> 5) & 3;
    switch (volume)
    {
        case 0: amplitude = 0; break;
        case 2: amplitude >>= 1; break;
        case 3: amplitude >>= 2; break;
    }

    result = amplitude;
    return result ;
}

void    sound_3_fill_buffer()
{

    uint8_t             *gb_mem = state->gameboy_memory;
    double              vol_left, vol_right;
    uint16_t            freq;

    (void)memset(sound_3_buffer, 0, sizeof(sound_3_buffer));

    if (!is_sound_enabled)
        return ;

    freq = nr3_freq;
    vol_left = 1.0;
    vol_right = 1.0;

    for (int i = 0; i < num_samples; i++)
    {
        if (is_sound_3_left_enabled)
            *(int16_t *)&sound_3_buffer[i * 4] = sound_3_wave(ticks, freq, vol_left);

        if (is_sound_3_right_enabled)
            *(int16_t *)&sound_3_buffer[i * 4 + 2] = sound_3_wave(ticks, freq, vol_right);

        ticks++;
    }
}
