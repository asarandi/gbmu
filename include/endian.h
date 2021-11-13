#ifndef ENDIAN_IO_H
# define ENDIAN_IO_H

void write_be16(uint8_t *dst, uint16_t val);
uint16_t read_be16(uint8_t *src);
void write_be32(uint8_t *dst, uint32_t val);
uint32_t read_be32(uint8_t *src);
void write_be64(uint8_t *dst, uint64_t val);
uint64_t read_be64(uint8_t *src);
void write_le16(uint8_t *dst, uint16_t val);
uint16_t read_le16(uint8_t *src);
void write_le32(uint8_t *dst, uint32_t val);
uint32_t read_le32(uint8_t *src);
void write_le64(uint8_t *dst, uint64_t val);
uint64_t read_le64(uint8_t *src);

#endif
