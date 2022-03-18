#include <stdint.h>

void write_be16(uint8_t *dst, uint16_t val) {
    for (int i = 0; i < 2; i++) {
        dst[i] = (val >> ((1 - i) * 8)) & 255;
    }
}

uint16_t read_be16(uint8_t *src) {
    uint16_t val = 0;

    for (int i = 0; i < 2; i++) {
        val = (val << 8) | src[i];
    }

    return val;
}

void write_be32(uint8_t *dst, uint32_t val) {
    for (int i = 0; i < 4; i++) {
        dst[i] = (val >> ((3 - i) * 8)) & 255;
    }
}

uint32_t read_be32(uint8_t *src) {
    uint32_t val = 0;

    for (int i = 0; i < 4; i++) {
        val = (val << 8) | src[i];
    }

    return val;
}

void write_be64(uint8_t *dst, uint64_t val) {
    for (int i = 0; i < 8; i++) {
        dst[i] = (val >> ((7 - i) * 8)) & 255;
    }
}

uint64_t read_be64(uint8_t *src) {
    uint64_t val = 0;

    for (int i = 0; i < 8; i++) {
        val = (val << 8) | src[i];
    }

    return val;
}

void write_le16(uint8_t *dst, uint16_t val) {
    for (int i = 0; i < 2; i++) {
        dst[i] = (val >> (i * 8)) & 255;
    }
}

uint16_t read_le16(uint8_t *src) {
    uint16_t val = 0;

    for (int i = 0; i < 2; i++) {
        val |= src[i] << (i * 8);
    }

    return val;
}

void write_le32(uint8_t *dst, uint32_t val) {
    for (int i = 0; i < 4; i++) {
        dst[i] = (val >> (i * 8)) & 255;
    }
}

uint32_t read_le32(uint8_t *src) {
    uint32_t val = 0;

    for (int i = 0; i < 4; i++) {
        val |= src[i] << (i * 8);
    }

    return val;
}

void write_le64(uint8_t *dst, uint64_t val) {
    for (int i = 0; i < 8; i++) {
        dst[i] = (val >> (i * 8)) & 255;
    }
}

uint64_t read_le64(uint8_t *src) {
    uint64_t val = 0;

    for (int i = 0; i < 8; i++) {
        val |= src[i] << (i * 8);
    }

    return val;
}

/*

#include <assert.h>
#include <string.h>

int main() {
    uint8_t buf[8];

    uint16_t val16 = 0x3210;
    uint8_t buf16_be[2] = {0x32, 0x10};
    uint8_t buf16_le[2] = {0x10, 0x32};

    uint32_t val32 = 0x76543210;
    uint8_t buf32_be[4] = {0x76, 0x54, 0x32, 0x10};
    uint8_t buf32_le[4] = {0x10, 0x32, 0x54, 0x76};


    uint64_t val64 = 0xfedcba9876543210;
    uint8_t buf64_be[8] = {0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10};
    uint8_t buf64_le[8] = {0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe};

    write_be16(buf, val16);
    assert(memcmp(buf, buf16_be, 2) == 0);

    write_le16(buf, val16);
    assert(memcmp(buf, buf16_le, 2) == 0);

    write_be32(buf, val32);
    assert(memcmp(buf, buf32_be, 4) == 0);

    write_le32(buf, val32);
    assert(memcmp(buf, buf32_le, 4) == 0);

    write_be64(buf, val64);
    assert(memcmp(buf, buf64_be, 8) == 0);

    write_le64(buf, val64);
    assert(memcmp(buf, buf64_le, 8) == 0);

    return 0;

}

*/
