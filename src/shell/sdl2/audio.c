#include <SDL2/SDL.h>
#include "gb.h"
#include "hardware.h"

static SDL_AudioDeviceID audio_device;
static uint8_t sdl_sound_buffer[SOUND_BUF_SIZE * 4];
static volatile int audio_index_write, audio_index_read, audio_num_available;

int audio_write(struct gameboy *gb, uint8_t *data, uint32_t size) {
    if (gb->testing) {
        return 1;
    }

    while (audio_num_available > (SOUND_BUF_SIZE * 3)) {
        SDL_Delay(1);    /* wait */
    }

    memcpy(sdl_sound_buffer + audio_index_write, data, size);
    audio_index_write = (audio_index_write + size) % (SOUND_BUF_SIZE * 4);
    audio_num_available += size;
    return 1;
}

static void audio_callback(void *userdata, Uint8 *stream, int len) {
    (void)userdata;
    memcpy(stream, sdl_sound_buffer + audio_index_read, len);
    audio_index_read = (audio_index_read + len) % (SOUND_BUF_SIZE * 4);
    audio_num_available -= len;
}

/* to be called after SDL_Init() */
int audio_open(struct gameboy *gb) {
    (void)gb;
    int retval;
    SDL_AudioSpec want, have;
    SDL_memset(&have, 0, sizeof(SDL_AudioSpec));
    SDL_memset(&want, 0, sizeof(SDL_AudioSpec));
    want.freq = SAMPLING_FREQUENCY;
    want.format = AUDIO_S16;
    want.channels = NUM_CHANNELS;
    want.samples = NUM_FRAMES;
    want.callback = audio_callback;
    audio_device = SDL_OpenAudioDevice(NULL, 0, &want, &have, 0);
    retval = audio_device != 0;

    if (!audio_device) {
        SDL_Log("SDL_OpenAudioDevice(): %s", SDL_GetError());
        retval = 0;
    }

    if (want.freq != have.freq) {
        SDL_Log("frequency want: %d, have: %d", want.freq, have.freq);
        retval = 0;
    }

    if (want.format != have.format) {
        SDL_Log("   format want: %d, have: %d", want.format, have.format);
        retval = 0;
    }

    if (want.channels != have.channels) {
        SDL_Log(" channels want: %d, have: %d", want.channels, have.channels);
        retval = 0;
    }

    if (want.samples != have.samples) {
        SDL_Log("  samples want: %d, have: %d", want.samples, have.samples);
        retval = 0;
    }

    if (retval) {
        SDL_PauseAudioDevice(audio_device, 0);
    }

    return retval;
}

int audio_close(struct gameboy *gb) {
    (void)gb;

    if (!audio_device) {
        return 1;
    }

    SDL_PauseAudioDevice(audio_device, 1);
    SDL_CloseAudioDevice(audio_device);
    audio_device = 0;
    return 1;
}
