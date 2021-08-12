#include "gb.h"
#include "hardware.h"

static int print_usage(struct gameboy *gb, int ac, char **av)  {
    (void)gb;
    (void)ac;
    (void)fprintf(stdout, "usage: %s romfile.gb\n", av[0]);
    return 0;
}

static int arg_parse(struct gameboy *gb, int ac, char **av) {
    int c, ret = 1;

    if (ac < 2) {
        (void)print_usage(gb, ac, av);
        return 0;
    }

    while ((c = getopt(ac, av, "dt:")) != -1) {
        switch (c) {
        case 't':
            ret &= testing_setup(gb, optarg);
            break;

        case 'd':
            gb->debug = true;
            break;

        case '?':
        default:
            return 0;
        }
    }

    return ret;
}

static int cleanup(struct gameboy *gb, bool save) {
    if (!gb->testing) {
        if (!input_close(gb)) {
            (void)fprintf(stderr, "input_close() failed\n");
        }

        if (!audio_close(gb)) {
            (void)fprintf(stderr, "audio_close() failed\n");
        }

        if (!video_close(gb)) {
            (void)fprintf(stderr, "video_close() failed\n");
        }

        if ((save) && (!savefile_write(gb))) {
            (void)fprintf(stderr, "savefile_write() failed\n");
        }
    }

    if (gb->file_contents) {
        (void)free(gb->file_contents);
        gb->file_contents = NULL;
    }

    return gb->exit_code;
}
int main(int ac, char **av) {
    static struct gameboy gameboy = {0};
    struct gameboy *gb = &gameboy;
    static int fd, i, ret;
    struct stat stat_buf;

    if (!arg_parse(gb, ac, av)) {
        return 1;
    }

    gb->rom_file = av[ac - 1];

    if ((fd = open(gb->rom_file, O_RDONLY | O_BINARY)) == -1) {
        (void)fprintf(stderr, "failed to open file\n");
        return 1;
    }

    if (fstat(fd, &stat_buf) != 0) {
        (void)close(fd);
        (void)fprintf(stderr, "fstat() failed\n");
        return 1;
    }

    if ((stat_buf.st_size < 0x8000) ||
            (stat_buf.st_size > 0x800000) ||
            (stat_buf.st_size & 0x7fff)) {
        (void)close(fd);
        (void)fprintf(stderr, "invalid file\n");
        return 1;
    }

    gb->file_contents = malloc(stat_buf.st_size);
    gb->file_size = stat_buf.st_size;
    ret = read(fd, gb->file_contents, stat_buf.st_size);
    (void)close(fd);

    if (ret != stat_buf.st_size) {
        (void)fprintf(stderr, "read() failed\n");
        (void)free(gb->file_contents);
        return 1;
    }

    (void)memcpy(gb->memory, gb->file_contents, 0x8000);
    io_init(gb);

    if (!cartridge_init(gb)) {
        return cleanup(gb, 0);
    };

    if (!gb->testing) {
        struct fn {
            int(*f)(struct gameboy *gb);
            char *n;
        } fn[] = {
            {&savefile_read, "savefile_read()"},
            {&video_open, "video_open()"},
            {&audio_open, "audio_open()"},
            {&input_open, "input_open()"},
        };

        for (i = 0; i < 4; i++) {
            if (!fn[i].f(gb)) {
                (void)fprintf(stderr, "%s: failed\n", fn[i].n);
                return cleanup(gb, 0);
            }
        }
    }

    gb->serial_cycles = 0xabcc;

    while (!gb->done) {
        (void)cpu_update(gb);
        (void)dma_update(gb);
        (void)serial_update(gb);

        if (timer_update(gb)) {
            sequencer_step(gb);
        }

        if (lcd_update(gb)) {
            if (!gb->testing) {
                (void)video_write(gb, gb->screen_buf, 160 * 144);
                (void)input_read(gb);
            }

            if (gb->screenshot) {
                screenshot(gb, "screenshot.png");
                gb->screenshot = false;
            }
        }

        if (sound_update(gb)) {
            if (!gb->testing) {
                (void)audio_write(gb, gb->sound_buf, SOUND_BUF_SIZE);
            }
        }

        if (gb->testing) {
            (void)gb->testing_run_hook(gb);
        }

        if (!(gb->cpu.state == INTERRUPT_DISPATCH)) {
            if (!gb->cpu.step) {
                interrupts_update(gb);
            }
        }

        gb->cycles += 4;
    }

    return cleanup(gb, 1);
}
