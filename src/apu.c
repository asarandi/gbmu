#include <SDL.h>
#include "gb.h"

static  SDL_AudioSpec           want;
static  SDL_AudioDeviceID       dev = 0;

#define sampling_frequency  44100
#define num_samples         32

#define master_volume_right     (gb_mem[0xff24] & 0x03)
#define master_volume_left      ((gb_mem[0xff24] >> 4) & 0x03)

#define is_sound_enabled        (gb_mem[0xff26] & 0x80 ? true : false)

#define is_snd1_right_enabled   (gb_mem[0xff25] & 0x01 ? true : false)
#define is_snd2_right_enabled   (gb_mem[0xff25] & 0x02 ? true : false)
#define is_snd3_right_enabled   (gb_mem[0xff25] & 0x04 ? true : false)
#define is_snd4_right_enabled   (gb_mem[0xff25] & 0x08 ? true : false)

#define is_snd1_left_enabled    (gb_mem[0xff25] & 0x10 ? true : false)
#define is_snd2_left_enabled    (gb_mem[0xff25] & 0x20 ? true : false)
#define is_snd3_left_enabled    (gb_mem[0xff25] & 0x40 ? true : false)
#define is_snd4_left_enabled    (gb_mem[0xff25] & 0x80 ? true : false)


int16_t SquareWave(double time, double freq, double amp) {
    int16_t result = 0;
    int tpc = sampling_frequency / freq; // ticks per cycle
    int cyclepart = (int)time % tpc;
    int halfcycle = tpc / 2;
    int16_t amplitude = INT16_MAX * amp;
    if (cyclepart < halfcycle) {
        result = amplitude;
    }
    return result ;
}

void MyAudioCallback(void *userdata, Uint8 *stream, int len)
{
    (void)userdata;
    (void)memset(stream, 0, len);
}

/* gui_init() must be called first because it calls SDL_Init() */
void    apu_init()
{
    SDL_memset(&want, 0, sizeof(want));
    want.freq = sampling_frequency;
    want.format = AUDIO_S16;
    want.channels = 2;
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

    (void)print_channel_2(gb_mem);


    if (!dev)
        return ;
}
