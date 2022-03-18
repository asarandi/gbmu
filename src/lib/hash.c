#include <stdint.h>

/* https://www.w3.org/TR/PNG/#D-CRCAppendix */
uint32_t my_crc32(uint8_t *buf, uint32_t len) {
    static uint32_t tab[256];
    uint32_t i, j, k;

    if (!tab[1]) {
        for (i = 0; i < 256; i++) {
            for (k = i, j = 0; j < 8; j++) {
                k = k & 1 ? 0xedb88320 ^ (k >> 1) : k >> 1;
            }

            tab[i] = k;
        }
    }

    for (k = 0xffffffff, i = 0; i < len; i++) {
        k = tab[(k ^ buf[i]) & 0xff] ^ (k >> 8);
    }

    return k ^ 0xffffffff;
}

/* https://en.wikipedia.org/wiki/Adler-32 */
uint32_t my_adler32(uint8_t *buf, uint32_t len) {
    uint32_t a, b, i;

    for (a = 1, b = i = 0; i < len; i++) {
        a = (a + buf[i]) % 65521;
        b = (b + a) % 65521;
    }

    return (b << 16) | a;
}
