#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>

int main() {
    uint8_t buf[0x1000];
    uint16_t i, k, b;
    int ret, fd;

    (void)memset(buf, 0, 0x1000);

    for (i = 0, k = 0x7fff; i < 0x8000; i++) {        
        printf("%04x %04x %04x %d\n", i, k, i >> 3, k & 1);
        buf[i >> 3] |= (k & 1) << (7 - (i & 7));
        b = ((k >> 1) ^ k) & 1;
        k >>= 1;
        k &= ~(1 << 14);
        k |= (b << 14);
    }

    fd = open("lfsr.out", O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (fd < 0) {
        perror("open()");
        return 1;
    }
    ret = write(fd, buf, 0x1000);
    if (ret != 0x1000) {
        perror("write()");
    }
    close(fd);
    return 0;
}
