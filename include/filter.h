#ifndef FILTER_H
# define FILTER_H

# include <stdint.h>

void highpass(int16_t *left, int16_t *right);
void lowpass(int16_t *left, int16_t *right);

#endif
