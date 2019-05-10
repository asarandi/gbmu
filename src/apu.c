#include "gb.h"
#include "sound.h"

SDL_AudioSpec                sdl_wanted_spec;
SDL_AudioDeviceID            sdl_audio_device = 0;

uint8_t                      sound_1_buffer[channel_buf_size];
uint8_t                      sound_2_buffer[channel_buf_size];
uint8_t                      sound_3_buffer[channel_buf_size];
uint8_t                      sound_4_buffer[channel_buf_size];

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

void    apu_update(uint8_t *gb_mem, t_state *state, int current_cycles)
{
    static uint64_t cycles;

    cycles += current_cycles;

    if (!sdl_audio_device)
        return ;

//    (void)print_channel_2(gb_mem);
    (void)sound_1_update(current_cycles);
    (void)sound_2_update(current_cycles);
    (void)sound_3_update(current_cycles);
}

void MyAudioCallback(void *userdata, Uint8 *stream, int len)
{
    uint8_t     *gb_mem = state->gameboy_memory;
    double      fcalc;
    uint64_t    left, right;

    (void)userdata;
    (void)memset(stream, 0, len);

    if (!sdl_audio_device)
        return ;

    sound_1_fill_buffer();
    sound_2_fill_buffer();
    sound_3_fill_buffer();

    for (int i = 0; i < num_samples; i++)
    {
        int j = i * (num_channels * sample_size);

        fcalc = 0;
        fcalc += *(int16_t *)&sound_1_buffer[j];
        fcalc += *(int16_t *)&sound_2_buffer[j];
        fcalc += *(int16_t *)&sound_3_buffer[j];
        fcalc += *(int16_t *)&sound_4_buffer[j];
        fcalc = fcalc * ((1.0 / 7) * master_volume_left);
        left = (uint64_t)fcalc;

        fcalc = 0;
        fcalc += *(int16_t *)&sound_1_buffer[j + sample_size];
        fcalc += *(int16_t *)&sound_2_buffer[j + sample_size];
        fcalc += *(int16_t *)&sound_3_buffer[j + sample_size];
        fcalc += *(int16_t *)&sound_4_buffer[j + sample_size];
        fcalc = fcalc * ((1.0 / 7) * master_volume_right);
        right = (uint64_t)fcalc;

        while ((left > UINT16_MAX) || (right > UINT16_MAX))
        {
            left >>= 1;
            right >>= 1;
        }

        *(int16_t *)&stream[j] = (int16_t)left;
        *(int16_t *)&stream[j + sample_size] = (int16_t)right;
    }
}

/* gui_init() must be called first because it calls SDL_Init() */
void    apu_init()
{
    SDL_memset(&sdl_wanted_spec, 0, sizeof(sdl_wanted_spec));
    sdl_wanted_spec.freq = sampling_frequency;
    sdl_wanted_spec.format = AUDIO_S16;
    sdl_wanted_spec.channels = num_channels;
    sdl_wanted_spec.samples = num_samples;
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
