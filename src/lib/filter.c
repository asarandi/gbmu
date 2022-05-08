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


// >>> gameboy_frequency = 4194304
// >>> sample_rate = 44100
//
// >>> unscaled_factor = 0.999958
// >>> scaled_factor = math.pow(unscaled_factor, gameboy_frequency / sample_rate)
// >>> scaled_factor
// 0.9960133089108504
//
// >>> cutoff_frequency = math.log(scaled_factor) / (-2 * math.pi) * sample_rate
// >>> cutoff_frequency
// 28.037445796538698
//
// >>> math.exp(-2 * math.pi * cutoff_frequency / sample_rate)
// 0.9960133089108504
//
// >>> unscaled_factor = 0.998943
// >>> scaled_factor = math.pow(unscaled_factor, gameboy_frequency / sample_rate)
// >>> scaled_factor
// 0.9043097701950136
//
// >>> cutoff_frequency = math.log(scaled_factor) / (-2 * math.pi) * sample_rate
// >>> cutoff_frequency
// 705.9674041889306
//
// >>> math.exp(-2 * math.pi * cutoff_frequency / sample_rate)
// 0.9043097701950136
//
//
// highpass cutoff frequency according to blargg's constants:
// DMG: 28.0374
// CGB: 705.9674


void highpass(int16_t *left, int16_t *right) {
    const int32_t alpha = (int32_t)((pow(FILTER_CONST_OFF,
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
