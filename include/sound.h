#ifndef SOUND_H
# define SOUND_H

#include <SDL.h>

#define sampling_frequency          44100
#define num_samples                 32
#define num_channels                2
#define sample_size                 2
#define channel_buf_size            (num_samples * sample_size * num_channels)

#define master_volume_right         (gb_mem[0xff24] & 0x03)
#define master_volume_left          ((gb_mem[0xff24] >> 4) & 0x03)

#define is_sound_enabled            (gb_mem[0xff26] & 0x80 ? true : false)

#define is_sound_1_enabled          (gb_mem[0xff26] & 0x01 ? true : false)
#define is_sound_2_enabled          (gb_mem[0xff26] & 0x02 ? true : false)
#define is_sound_3_enabled          (gb_mem[0xff26] & 0x04 ? true : false)
#define is_sound_4_enabled          (gb_mem[0xff26] & 0x08 ? true : false)

#define is_sound_1_right_enabled    (gb_mem[0xff25] & 0x01 ? true : false)
#define is_sound_2_right_enabled    (gb_mem[0xff25] & 0x02 ? true : false)
#define is_sound_3_right_enabled    (gb_mem[0xff25] & 0x04 ? true : false)
#define is_sound_4_right_enabled    (gb_mem[0xff25] & 0x08 ? true : false)

#define is_sound_1_left_enabled     (gb_mem[0xff25] & 0x10 ? true : false)
#define is_sound_2_left_enabled     (gb_mem[0xff25] & 0x20 ? true : false)
#define is_sound_3_left_enabled     (gb_mem[0xff25] & 0x40 ? true : false)
#define is_sound_4_left_enabled     (gb_mem[0xff25] & 0x80 ? true : false)

#define nr1_freq                    (131072 / (2048 - (((gb_mem[0xff14] & 7) << 8) | gb_mem[0xff13])))
#define nr1_vol                     ((gb_mem[0xff12] >> 4) & 15)
#define nr1_duty                    ((gb_mem[0xff11] >> 6) & 3)

#define nr2_freq                    (131072 / (2048 - (((gb_mem[0xff19] & 7) << 8) | gb_mem[0xff18])))
#define nr2_vol                     ((gb_mem[0xff17] >> 4) & 15)
#define nr2_duty                    ((gb_mem[0xff16] >> 6) & 3)

#define nr3_freq                    (65536 / (2048 - (((gb_mem[0xff1e] & 7) << 8) | gb_mem[0xff1d])))

#define nr4_vol                     ((gb_mem[0xff21] >> 4) & 15)

void                                sound_1_update(int current_cycles);
void                                sound_1_fill_buffer();

void                                sound_2_update(int current_cycles);
void                                sound_2_fill_buffer();

void                                sound_3_update(int current_cycles);
void                                sound_3_fill_buffer();

int16_t                             SquareWave(int time, int freq, int vol, int duty);

#endif
