#ifndef SOUND_H
# define SOUND_H

#define  SAMPLING_FREQUENCY 65536
#define  NUM_FRAMES         1024
#define  NUM_CHANNELS       2
#define  SAMPLE_SIZE        2
#define  SOUND_BUF_SIZE     (NUM_FRAMES * SAMPLE_SIZE * NUM_CHANNELS)
#define  VOLUME_CLOCK       (4194304 /  64)
#define  SWEEP_CLOCK        (4194304 / 128)
#define  FREQUENCY_CLOCK    (4194304 / 512)
#define  SAMPLE_CLOCK       (4194304 / SAMPLING_FREQUENCY)

struct channel {
    uint32_t on;
    uint32_t dac;
    uint32_t sweep_on;
    uint32_t sweep_period;
    uint32_t sweep_neg;
    uint32_t sweep_down;
    uint32_t sweep_shift;
    uint32_t sweep_ctr;         //helper
    uint32_t shadow_freq;
    uint32_t length;
    uint32_t len_enabled;    //rename?
    uint32_t volume;
    uint32_t env_dir;
    uint32_t env_period;         //rename?
    uint32_t env_ctr;           //helper
    uint32_t env_on;
    uint32_t lfsr_width;
    uint32_t duty;
    uint32_t phase;
    uint32_t freq;
    int32_t period;
    uint32_t clocks;
    int32_t counter;
};
#endif
