#include "gb.h"
#include "bridge.h"
#include "pipeline.h"
#include <pthread.h>

struct player players[2];
pthread_mutex_t lock;
volatile int throttle = 0, done = 0;

void timer_callback() {
    throttle = 1;
}

void set_input(int player_id, int input) {
    struct gameboy *gb = &(players[player_id].gb);
    int i, val, flag;

    for (i = flag = 0; i < 8; i++) {
        val = (input >> (7 - i)) & 1;
        flag |= gb->buttons[i] != val;
        gb->buttons[i] = val;
    }

    if (flag) {
        joypad_request_interrupt(gb);
    }
}

static void *load_with_ram(struct gameboy *gb, void *rom_data, int rom_size,
                           void *ram_data, int ram_size) {
    (void)memset(gb, 0, sizeof(*gb));
    gb->cartridge.data = rom_data;
    gb->cartridge.size = rom_size;
    (void)memcpy(gb->memory, gb->cartridge.data, 0x8000);
    (void)io_init(gb);

    if (!mbc_init(gb)) {
        return "unsupported rom";
    }

    if (!ram_data || !ram_size) {
        return 0; // ok
    }

    if (!save_deserialize_from_bytes(gb, ram_data, ram_size)) {
        return "save does not match";
    }

    return 0; // ok
}

int load_ram_from_bytes(int player_id, void *ram_data, int ram_size) {
    struct gameboy *gb;
    char *s = NULL;
    (void)pthread_mutex_lock(&lock);
    gb = &(players[player_id].gb);
    s = load_with_ram(gb, gb->cartridge.data, gb->cartridge.size, ram_data,
                      ram_size);
    (void)pthread_mutex_unlock(&lock);
    return s ? video_message(player_id, s) : 1;
}

int save_ram_to_bytes(int player_id, void *buf, int size) {
    (void)pthread_mutex_lock(&lock);
    int ret = save_serialize_to_bytes(&(players[player_id].gb), (uint8_t *)buf,
                                      (uint64_t)size);
    (void)pthread_mutex_unlock(&lock);
    return ret;
}

int load_rom_from_bytes(int player_id, void *rom_data, int rom_size) {
    struct gameboy *gb;
    char *s = NULL;
    (void)pthread_mutex_lock(&lock);
    gb = &(players[player_id].gb);
    s = load_with_ram(gb, rom_data, rom_size, 0, 0);
    (void)pthread_mutex_unlock(&lock);
    return s ? video_message(player_id, s) : 1;
}

int reload_both() {
    int i, size;
    void *data;

    for (i = 0; i < 2; i++) {
        data = players[i].gb.cartridge.data;
        size = players[i].gb.cartridge.size;
        load_rom_from_bytes(i, data, size);
    }

    return 1;
}

int set_frame_blending(int player_id, bool enabled) {
    players[player_id].frame_blending = enabled;
    return 1;
}

static int video_frame(struct player *player) {
    struct gameboy *gb = &player->gb;
    uint8_t px, palette[] = {0xff, 0xaa, 0x55, 0x00};
    uint16_t i, blend;

    for (i = 0; i < 160 * 144; i++) {
        px = blend = palette[gb->lcd.buf[i]];
        blend += gb->prev_frame[i];
        gb->prev_frame[i] = px;
        gb->video_buf[i] = player->frame_blending ? (blend >> 1) : px;
    }

    return 1;
}

static int step(struct player players[2], int player_id) {
    struct gameboy *gb;
    int ret;
    gb = &(players[player_id].gb);
    ret = 0 <= cpu_update(gb);
    (void)dma_update(gb);
    (void)serial_update(gb, &players[!player_id].gb);

    if (timer_update(gb)) {
        (void)sequencer_step(gb);
    }

    if (lcd_update(gb)) {
        (void)video_frame(&players[player_id]);
    }

    if (sound_update(gb)) {
        (void)rtc_tick(gb);
    }

    if (!(gb->cpu.state == INTERRUPT_DISPATCH)) {
        if (!gb->cpu.step) {
            (void)interrupts_update(gb);
        }
    }

    gb->cycles += 4;
    return ret;
}

int finish() {
    done = 1;
    return 1;
}

void debug_cpu_instr(struct gameboy *gb) {
    (void)gb;
}

void debug_log_io(struct gameboy *gb, uint16_t addr, uint8_t data) {
    (void)gb;
    (void)addr;
    (void)data;
}

int run() {
    struct timespec ts = {.tv_sec = 0, .tv_nsec = 1000L};
    int i, ret[2];

    for (i = 0; i < 4; i++) {
        pipeline_open(i);
    }

    if (pthread_mutex_init(&lock, NULL) != 0) {
        (void)fprintf(stderr, "pthread_mutex_init() failed\n");
        return 0;
    }

    (void)video_message(0, "load rom");
    (void)video_message(1, "load rom");

    for (; !done;) {
        pthread_mutex_lock(&lock);

        for (i = 0; i < 16384; i++) {
            ret[0] = step(players, 0);
            ret[1] = step(players, 1);
        }

        pthread_mutex_unlock(&lock);

        for (i = 0; i < 2; i++) {
            if (!ret[i]) {
                (void)video_message(i, "crash");
            }
        }

        while (!throttle) {
            (void)nanosleep(&ts, NULL);
        }

        throttle = 0;
        (void)pipeline_write(0, players[0].gb.sound_buf, SOUND_BUF_SIZE);
        (void)pipeline_write(1, players[0].gb.video_buf, VIDEO_BUF_SIZE);
        (void)pipeline_write(2, players[1].gb.sound_buf, SOUND_BUF_SIZE);
        (void)pipeline_write(3, players[1].gb.video_buf, VIDEO_BUF_SIZE);
    }

    if (pthread_mutex_destroy(&lock) != 0) {
        (void)fprintf(stderr, "pthread_mutex_destroy() failed\n");
    }

    for (i = 0; i < 4; i++) {
        pipeline_close(i);
    }

    return 1;
}
