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
    uint8_t     A;  
    uint8_t     F;  
    uint8_t     B;  
    uint8_t     C;  
    uint8_t     D;  
    uint8_t     E;  
    uint8_t     H;  
    uint8_t     L;  
    uint16_t    SP; 
    uint16_t    PC; 
} t_r8;             

#define set_z      (r8->F |= 0x80)
#define set_n      (r8->F |= 0x40)
#define set_h      (r8->F |= 0x20)
#define set_c      (r8->F |= 0x10)

#define clear_z    (r8->F &= (~0x80))
#define clear_n    (r8->F &= (~0x40))
#define clear_h    (r8->F &= (~0x20))
#define clear_c    (r8->F &= (~0x10))

#endif
