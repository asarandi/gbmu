#include <SDL.h>
#include <stdio.h>

void MyAudioCallback(void *userdata, Uint8 *stream, int len)
{

}

int main()
{
    SDL_AudioSpec want, have;
    SDL_AudioDeviceID dev;

    if (SDL_Init(SDL_INIT_AUDIO) != 0) {
        printf("Failed to initialise SDL\n");
        return EXIT_FAILURE;
    }

    SDL_memset(&want, 0, sizeof(want));
    want.freq = 48000;
    want.format = AUDIO_F32;
    want.channels = 2;
    want.samples = 4096;
    want.callback = MyAudioCallback; /* you wrote this function elsewhere -- see SDL_AudioSpec for details */

    dev = SDL_OpenAudioDevice(NULL, 0, &want, &have, 0);
    if (dev == 0)
    {
        SDL_Log("Failed to open audio: %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    if (have.format != want.format) { /* we let this one thing change. */
        SDL_Log("We didn't get Float32 audio format.");
    }
    SDL_PauseAudioDevice(dev, 0); /* start audio playing. */
    SDL_Delay(5000); /* let the audio callback play some sound for 5 seconds. */

    SDL_CloseAudioDevice(dev);
    SDL_Quit();

    return EXIT_SUCCESS;
}
