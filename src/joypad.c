#include "gb.h"

#define IS_SGB      ((gb_mem[0x146] == 3) && (gb_mem[0x14b] == 0x33))

void    joypad_request_interrupt()
{
    uint8_t *gb_mem = state->gameboy_memory;
    gb_mem[0xff0f] |= 0x10;
}

uint8_t    joypad_read()
{
    uint8_t *gb_mem = state->gameboy_memory;
    uint8_t joypad = gb_mem[0xff00];
    int     i, val;

    if ((joypad & 0x10) == 0) {
        for (i = 0; i < 4; i++) {
            val = (state->buttons[i] & 1) ^ 1;
            joypad &=  ~(1 << (3 - i));
            joypad |= val << (3 - i);
        }
    }

    if ((joypad & 0x20) == 0) {
        for (i = 0; i < 4; i++) {
            val = (state->buttons[i + 4] & 1) ^ 1;
            joypad &=  ~(1 << (3 - i));
            joypad |= val << (3 - i);
        }
    }
    gb_mem[0xff00] = joypad;
    return joypad;
}

typedef struct s_sgb_cmd
{
    uint8_t code;
    char    *info;
}              t_sgb_cmd;

t_sgb_cmd   sgb_commands[] = {
    {0x00, "PAL01     Set SGB Palette 0,1 Data"},
    {0x01, "PAL23     Set SGB Palette 2,3 Data"},
    {0x02, "PAL03     Set SGB Palette 0,3 Data"},
    {0x03, "PAL12     Set SGB Palette 1,2 Data"},
    {0x04, "ATTR_BLK  'Block' Area Designation Mode"},
    {0x05, "ATTR_LIN  'Line' Area Designation Mode"},
    {0x06, "ATTR_DIV  'Divide' Area Designation Mode"},
    {0x07, "ATTR_CHR  '1CHR' Area Designation Mode"},
    {0x08, "SOUND     Sound On/Off"},
    {0x09, "SOU_TRN   Transfer Sound PRG/DATA"},
    {0x0A, "PAL_SET   Set SGB Palette Indirect"},
    {0x0B, "PAL_TRN   Set System Color Palette Data"},
    {0x0C, "ATRC_EN   Enable/disable Attraction Mode"},
    {0x0D, "TEST_EN   Speed Function"},
    {0x0E, "ICON_EN   SGB Function"},
    {0x0F, "DATA_SND  SUPER NES WRAM Transfer 1"},
    {0x10, "DATA_TRN  SUPER NES WRAM Transfer 2"},
    {0x11, "MLT_REG   Controller 2 Request"},
    {0x12, "JUMP      Set SNES Program Counter"},
    {0x13, "CHR_TRN   Transfer Character Font Data"},
    {0x14, "PCT_TRN   Set Screen Data Color Data"},
    {0x15, "ATTR_TRN  Set Attribute from ATF"},
    {0x16, "ATTR_SET  Set Data to ATF"},
    {0x17, "MASK_EN   Game Boy Window Mask"},
    {0x18, "OBJ_TRN   Super NES OBJ Mode"},
    {0x19, "undefined 0x19 wtf"},
    {0x1a, "undefined 0x1a wtf"},
    {0x1b, "undefined 0x1b wtf"},
    {0x1c, "undefined 0x1c wtf"},
    {0x1d, "undefined 0x1d wtf"},
    {0x1e, "undefined 0x1e wtf"},
    {0x1f, "undefined 0x1f wtf"}
};

void        joypad_write(uint8_t data)
{
    static uint8_t  packet[256];
    static int      idx, i;
    uint8_t *gb_mem = state->gameboy_memory;

    data &= 0x30;
    gb_mem[0xff00] = (gb_mem[0xff00] & 15) | data;
    if (!IS_SGB)
        return ;
    data >>= 4;
    if (data == 3)              /* both high between pulses */
        return ;
    if (!data) {                /* both low: reset */
        printf("joypad reset ");
        for (idx = 0; idx < 256; idx++)
            packet[idx] = 0;
        idx = 0;
        return ;
    }
    packet[idx>>3] = (packet[idx>>3] & ~(1<<(idx&7))) | ((data&1) << (idx&7));
    idx++;
    idx &= 0x7ff;
    if (idx == 128) {
        for (i=0;i<16;i++) {
            printf("%02x ", packet[i]);
        }
        printf("%s\n", sgb_commands[packet[0]>>3].info);
    }
}
