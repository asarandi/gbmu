#include <math.h>
#include "gb.h"

// https://raw.githubusercontent.com/mackron/miniaudio/master/miniaudio.h
// ma_hpf1_process_pcm_frame_s16, ma_lpf1_process_pcm_frame_s16
// https://github.com/mmitch/gbsplay/blob/master/gbhw.c
// https://gist.github.com/drhelius/3652407

#ifndef MA_BIQUAD_FIXED_POINT_SHIFT
#define MA_BIQUAD_FIXED_POINT_SHIFT 14
#endif

#define FILTER_CONST_OFF 1.0
#define FILTER_CONST_DMG 0.999958
#define FILTER_CONST_CGB 0.998943

void highpass(int16_t *left, int16_t *right) {
    const int32_t alpha = (int32_t)((pow(FILTER_CONST_DMG,
                                         4194304 / SAMPLING_FREQUENCY)) * (1 << MA_BIQUAD_FIXED_POINT_SHIFT));
    const int32_t a = ((1 << MA_BIQUAD_FIXED_POINT_SHIFT) - alpha);
    const int32_t b = ((1 << MA_BIQUAD_FIXED_POINT_SHIFT) - a);
    static int32_t lcap, rcap;
    int32_t x, y;
    /* left */
    x = *left;
    y = (b*x - a*lcap) >> MA_BIQUAD_FIXED_POINT_SHIFT;
    *left = (int16_t)y;
    lcap = (int32_t)y;
    /* right */
    x = *right;
    y = (b*x - a*rcap) >> MA_BIQUAD_FIXED_POINT_SHIFT;
    *right = (int16_t)y;
    rcap = (int32_t)y;
}

void lowpass(int16_t *left, int16_t *right) {
    const int cutoff_frequency = 1000;
    const int32_t alpha = (int32_t)(exp(-2 * M_PI * cutoff_frequency /
                                        SAMPLING_FREQUENCY) * (1 << MA_BIQUAD_FIXED_POINT_SHIFT));
    const int32_t a = alpha;
    const int32_t b = ((1 << MA_BIQUAD_FIXED_POINT_SHIFT) - a);
    static int32_t lcap, rcap;
    int32_t x, y;
    /* left */
    x = *left;
    y = (b*x + a*lcap) >> MA_BIQUAD_FIXED_POINT_SHIFT;
    *left = (int16_t)y;
    lcap = (int32_t)y;
    /* right */
    x = *right;
    y = (b*x + a*rcap) >> MA_BIQUAD_FIXED_POINT_SHIFT;
    *right = (int16_t)y;
    rcap = (int32_t)y;
}

// https://github.com/GNOME/gegl/blob/master/operations/common-gpl3%2B/video-degradation.c
void video_degradation(uint8_t *rgba, int height, int width) {
#define MAX_PATTERNS       9
#define MAX_PATTERN_SIZE 108
    const int pattern_width[MAX_PATTERNS] = {2, 4, 1, 1, 2, 3, 6, 6, 5};
    const int pattern_height[MAX_PATTERNS] = {6, 12, 3, 6, 12, 3, 6, 18, 15};
    const int pattern[MAX_PATTERNS][MAX_PATTERN_SIZE] = {
        {
            0, 1,
            0, 2,
            1, 2,
            1, 0,
            2, 0,
            2, 1,
        },
        {
            0, 0, 1, 1,
            0, 0, 1, 1,
            0, 0, 2, 2,
            0, 0, 2, 2,
            1, 1, 2, 2,
            1, 1, 2, 2,
            1, 1, 0, 0,
            1, 1, 0, 0,
            2, 2, 0, 0,
            2, 2, 0, 0,
            2, 2, 1, 1,
            2, 2, 1, 1,
        },
        {
            0,
            1,
            2,
        },
        {
            0,
            0,
            1,
            1,
            2,
            2,
        },
        {
            0, 1,
            0, 1,
            0, 2,
            0, 2,
            1, 2,
            1, 2,
            1, 0,
            1, 0,
            2, 0,
            2, 0,
            2, 1,
            2, 1,
        },
        {
            0, 1, 2,
            2, 0, 1,
            1, 2, 0,
        },
        {
            0, 0, 1, 1, 2, 2,
            0, 0, 1, 1, 2, 2,
            2, 2, 0, 0, 1, 1,
            2, 2, 0, 0, 1, 1,
            1, 1, 2, 2, 0, 0,
            1, 1, 2, 2, 0, 0,
        },
        {
            2, 2, 0, 0, 0, 0,
            2, 2, 2, 0, 0, 2,
            2, 2, 2, 2, 2, 2,
            2, 2, 2, 1, 1, 2,
            2, 2, 1, 1, 1, 1,
            1, 1, 1, 1, 1, 1,
            0, 0, 1, 1, 1, 1,
            0, 0, 0, 1, 1, 0,
            0, 0, 0, 0, 0, 0,
            0, 0, 0, 2, 2, 0,
            0, 0, 2, 2, 2, 2,
            2, 2, 2, 2, 2, 2,
            1, 1, 2, 2, 2, 2,
            1, 1, 1, 2, 2, 1,
            1, 1, 1, 1, 1, 1,
            1, 1, 1, 0, 0, 1,
            1, 1, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0,
        },
        {
            0, 1, 2, 0, 0,
            1, 1, 1, 2, 0,
            0, 1, 2, 2, 2,
            0, 0, 1, 2, 0,
            0, 1, 1, 1, 2,
            2, 0, 1, 2, 2,
            0, 0, 0, 1, 2,
            2, 0, 1, 1, 1,
            2, 2, 0, 1, 2,
            2, 0, 0, 0, 1,
            1, 2, 0, 1, 1,
            2, 2, 2, 0, 1,
            1, 2, 0, 0, 0,
            1, 1, 2, 0, 1,
            1, 2, 2, 2, 0,
        }
    };
    // config
    const int pattern_index = 5;
    const bool additive = 1;
    const bool rotated = 0;
    int y, x, i, j, sel, cc;
    uint8_t *ptr;

    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            i = (rotated) ? x : y;
            j = (rotated) ? y : x;
            sel = pattern[pattern_index][pattern_width[pattern_index] *
                                         (i % pattern_height[pattern_index]) + (j % pattern_width[pattern_index])];
            ptr = &rgba[(y * width + x) * 4];

            for (i = 0; i < 3; i++) {
                cc = (sel == i) ? ptr[i] : 0;

                if (additive) {
                    cc = cc + ptr[i];
                    cc = (cc > 255) ? 255 : cc;
                }

                ptr[i] = (uint8_t)cc;
            }
        }
    }
}
