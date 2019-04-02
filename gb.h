#ifndef GB_H
# define GB_H

#include <stdint.h>

typedef struct s_r16 {
    uint16_t    AF; 
    uint16_t    BC; 
    uint16_t    DE; 
    uint16_t    HL; 
    uint16_t    SP; 
    uint16_t    PC; 
} t_r16;            

typedef struct s_r8 {
    uint8_t     F;  
    uint8_t     A;  

    uint8_t     C;  
    uint8_t     B;  

    uint8_t     E;  
    uint8_t     D;  

    uint8_t     L;  
    uint8_t     H;  

    uint16_t    SP; 
    uint16_t    PC; 
} t_r8;             

#define clear_z_flag     (r8->F &= (~0x80))
#define clear_n_flag     (r8->F &= (~0x40))
#define clear_h_flag     (r8->F &= (~0x20))
#define clear_c_flag     (r8->F &= (~0x10))

#define set_z_flag       (r8->F |= 0x80)
#define set_n_flag       (r8->F |= 0x40)
#define set_h_flag       (r8->F |= 0x20)
#define set_c_flag       (r8->F |= 0x10)

#define is_z_flag        (r8->F & 0x80 ? 1:0)
#define is_n_flag        (r8->F & 0x40 ? 1:0)
#define is_h_flag        (r8->F & 0x20 ? 1:0)
#define is_c_flag        (r8->F & 0x10 ? 1:0)

#endif
