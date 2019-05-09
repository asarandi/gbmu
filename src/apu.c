#include <SDL.h>
#include "gb.h"

static  SDL_AudioSpec           want;
static  SDL_AudioDeviceID       dev = 0;

#define sampling_frequency  44100
#define num_samples         32
#define num_channels        2
#define sample_size         2   //sizeof(int16_t)
#define channel_buf_size    (num_samples * sample_size * num_channels)

#define master_volume_right        (gb_mem[0xff24] & 0x03)
#define master_volume_left         ((gb_mem[0xff24] >> 4) & 0x03)

#define is_sound_enabled           (gb_mem[0xff26] & 0x80 ? true : false)

#define is_sound_1_enabled         (gb_mem[0xff26] & 0x01 ? true : false)
#define is_sound_2_enabled         (gb_mem[0xff26] & 0x02 ? true : false)
#define is_sound_3_enabled         (gb_mem[0xff26] & 0x04 ? true : false)
#define is_sound_4_enabled         (gb_mem[0xff26] & 0x08 ? true : false)

#define is_sound_1_right_enabled   (gb_mem[0xff25] & 0x01 ? true : false)
#define is_sound_2_right_enabled   (gb_mem[0xff25] & 0x02 ? true : false)
#define is_sound_3_right_enabled   (gb_mem[0xff25] & 0x04 ? true : false)
#define is_sound_4_right_enabled   (gb_mem[0xff25] & 0x08 ? true : false)

#define is_sound_1_left_enabled    (gb_mem[0xff25] & 0x10 ? true : false)
#define is_sound_2_left_enabled    (gb_mem[0xff25] & 0x20 ? true : false)
#define is_sound_3_left_enabled    (gb_mem[0xff25] & 0x40 ? true : false)
#define is_sound_4_left_enabled    (gb_mem[0xff25] & 0x80 ? true : false)

void    print_channel_2(uint8_t *gb_mem)
{
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

double  get_duty_cycles(uint8_t reg)    /* nr11, nr21 */
{
    double cycles[] = {0.125, 0.25, 0.5, 0.75};
    return cycles[(reg >> 6) & 3];
}

int16_t SquareWave(double time, double freq, double amp, double duty) {
//    printf("SquareWave() %f, %f, %f, %f\n", time, freq, amp, duty);
    int16_t result = 0;
    double tpc = sampling_frequency / freq; // ticks per cycle
    double cyclepart = fmod(time,tpc);
    double halfcycle = tpc * duty;
    int16_t amplitude = INT16_MAX * amp;
    if (cyclepart < halfcycle) {
        result = amplitude;
    }
    return result ;
}

#define nr1_freq   (131072 / (2048 - (((gb_mem[0xff14] & 7) << 8) | gb_mem[0xff13])))
#define nr1_vol    ((gb_mem[0xff12] >> 4) & 15)
static uint8_t      sound_1_buffer[channel_buf_size];

void    sound_1_update(int current_cycles)
{
    uint8_t *gb_mem = state->gameboy_memory;
    uint64_t envelope_step, sweep_step, sweep_freq, sweep_calc;
    uint8_t  envelope_volume, envelope_direction, sweep_shift;
    static uint64_t     sound_1_cycles, sound_1_prev_cycles;


    if (!(gb_mem[0xff14] & 0x80))
    {
        sound_1_cycles = 0;
        sound_1_prev_cycles = 0;
        return ;
    }

    sound_1_cycles += current_cycles;

    sweep_step = ((gb_mem[0xff10] >> 4) & 7) * (4194304 / 128);
    sweep_shift = gb_mem[0xff10] & 7;
    if ((sweep_step) && (sweep_shift))
    {
        if ((sound_1_cycles / sweep_step) > (sound_1_prev_cycles / sweep_step))
        {
            sweep_freq = ((gb_mem[0xff14] & 7) << 8) | gb_mem[0xff13];
            sweep_calc = sweep_freq >> sweep_shift;
            if (gb_mem[0xff10] & 0x8)
                sweep_freq -= sweep_calc;
            else
                sweep_freq += sweep_calc;

            if (sweep_freq < 2048)
            {
                gb_mem[0xff14] = (gb_mem[0xff14] & 0xf8) | ((sweep_freq >> 8) & 7);
                gb_mem[0xff13] = sweep_freq & 0xff;

//                printf("sweep shift %s\n", (gb_mem[0xff10] & 8) ? "down" : "up");
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

void    sound_1_fill_buffer()
{

    uint8_t             *gb_mem = state->gameboy_memory;
    double              duty, freq, vol_left, vol_right;
    static  uint64_t    ticks;

    (void)memset(sound_1_buffer, 0, sizeof(sound_1_buffer));

    if (!is_sound_enabled)
        return ;

    duty = get_duty_cycles(gb_mem[0xff11]);

    freq = nr1_freq;
    vol_left = (((1.0 / 7) * master_volume_left) / 15) * nr1_vol;
    vol_right = (((1.0 / 7) * master_volume_right) / 15) * nr1_vol;

    for (int i = 0; i < num_samples; i++)
    {
        if (is_sound_1_left_enabled)
            *(int16_t *)&sound_1_buffer[i * 4] = SquareWave(ticks, freq, vol_left, duty);

        if (is_sound_1_right_enabled)
            *(int16_t *)&sound_1_buffer[i * 4 + 2] = SquareWave(ticks, freq, vol_right, duty);

        ticks++;
    }
}

#define nr2_freq   (131072 / (2048 - (((gb_mem[0xff19] & 7) << 8) | gb_mem[0xff18])))
#define nr2_vol    ((gb_mem[0xff17] >> 4) & 15)

static uint8_t      sound_2_buffer[channel_buf_size];

void    sound_2_update(int current_cycles)
{
    uint8_t *gb_mem = state->gameboy_memory;
    uint64_t envelope_step;
    uint8_t  envelope_volume, envelope_direction;
    static uint64_t     sound_2_cycles, sound_2_prev_cycles;


    if (!(gb_mem[0xff19] & 0x80))
    {
        sound_2_cycles = 0;
        sound_2_prev_cycles = 0;
        return ;
    }

    sound_2_cycles += current_cycles;

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
    vol_left = (((1.0 / 7) * master_volume_left) / 15) * nr2_vol;
    vol_right = (((1.0 / 7) * master_volume_right) / 15) * nr2_vol;

    for (int i = 0; i < num_samples; i++)
    {
        if (is_sound_2_left_enabled)
            *(int16_t *)&sound_2_buffer[i * 4] = SquareWave(ticks, freq, vol_left, duty);

        if (is_sound_2_right_enabled)
            *(int16_t *)&sound_2_buffer[i * 4 + 2] = SquareWave(ticks, freq, vol_right, duty);

        ticks++;
    }
}

void    apu_update(uint8_t *gb_mem, t_state *state, int current_cycles)
{
    static uint64_t cycles;

    cycles += current_cycles;
    (void)sound_1_update(current_cycles);
    (void)sound_2_update(current_cycles);

//    (void)print_channel_2(gb_mem);

    if (!dev)
        return ;
}

void MyAudioCallback(void *userdata, Uint8 *stream, int len)
{
    uint64_t    calc_left, calc_right;

    (void)userdata;
    (void)memset(stream, 0, len);

    sound_1_fill_buffer();
    sound_2_fill_buffer();

    for (int i = 0; i < num_samples; i++)
    {
        int j = i * (num_channels * sample_size);

        calc_left = 0;
        calc_left += *(int16_t *)&sound_1_buffer[j];
        calc_left += *(int16_t *)&sound_2_buffer[j];

        calc_right = 0;
        calc_right += *(int16_t *)&sound_1_buffer[j + sample_size];
        calc_right += *(int16_t *)&sound_2_buffer[j + sample_size];

        *(int16_t *)&stream[j] = (int16_t)calc_left >> 1;
        *(int16_t *)&stream[j + sample_size] = (int16_t)calc_right >> 1;
    }
}

/* gui_init() must be called first because it calls SDL_Init() */
void    apu_init()
{
    SDL_memset(&want, 0, sizeof(want));
    want.freq = sampling_frequency;
    want.format = AUDIO_S16;
    want.channels = num_channels;
    want.samples = num_samples;
    want.callback = MyAudioCallback;

    dev = SDL_OpenAudioDevice(NULL, 0, &want, NULL, 0);
    if (!dev)
        return ;
    SDL_PauseAudioDevice(dev, 0);
    return ;
}

void    apu_cleanup()
{
    if (!dev)
        return ;
    SDL_CloseAudioDevice(dev);
    dev = 0;
}
