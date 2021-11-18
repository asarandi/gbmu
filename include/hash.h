#ifndef HASH_H
# define HASH_H

# include <stdint.h>

uint32_t my_crc32(uint8_t *buf, uint32_t len);
uint32_t my_adler32(uint8_t *buf, uint32_t len);

#endif
