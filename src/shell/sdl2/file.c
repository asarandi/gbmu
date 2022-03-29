#include <SDL2/SDL.h>
#include <stddef.h>
#include <stdint.h>

int file_read(const char *filename, uint8_t **buf, int64_t *size) {
    SDL_RWops *rw;
    size_t ret;

    if ((rw = SDL_RWFromFile(filename, "rb")) == NULL) {
        SDL_Log("%s", SDL_GetError());
        return 0;
    }

    if ((*size = SDL_RWsize(rw)) < 0) {
        SDL_Log("%s", SDL_GetError());
        SDL_RWclose(rw);
        return 0;
    }

    if ((*buf = calloc(1, *size)) == NULL) {
        SDL_Log("failed to allocate buffer");
        SDL_RWclose(rw);
        return 0;
    }

    ret = SDL_RWread(rw, *buf, *size, 1);
    SDL_RWclose(rw);

    if (ret < 1) {
        SDL_Log("%s", SDL_GetError());
    }

    return ret == 1;
}

int file_write(const char *filename, uint8_t *buf, int64_t size) {
    SDL_RWops *rw;
    size_t ret;

    if ((rw = SDL_RWFromFile(filename, "wb")) == NULL) {
        SDL_Log("%s", SDL_GetError());
        return 0;
    }

    ret = SDL_RWwrite(rw, buf, size, 1);
    SDL_RWclose(rw);

    if (ret < 1) {
        SDL_Log("%s", SDL_GetError());
    }

    return ret == 1;
}
