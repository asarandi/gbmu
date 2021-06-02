#ifndef CPU_H
# define CPU_H

#include <stdint.h>

enum CPU_STATE { RUNNING, HALTED, STOPPED };

struct cpu {
    uint8_t opcode;
    uint8_t r8[8];
    uint16_t pc;
    uint16_t sp;
    uint8_t hi, lo;
    int16_t i16;
    uint16_t u16;
    int step;
    int interrupt_dispatch;
    int instr_cycles;
    int state;
    int halt_bug;
    int ime;
    int ime_scheduled;
};

#define R16BC        ((gb->cpu.r8[0] << 8) | (gb->cpu.r8[1]))
#define R16DE        ((gb->cpu.r8[2] << 8) | (gb->cpu.r8[3]))
#define R16HL        ((gb->cpu.r8[4] << 8) | (gb->cpu.r8[5]))
#define R16AF        ((gb->cpu.r8[7] << 8) | (gb->cpu.r8[6] & 0b11110000))
#define R16PC        (gb->cpu.pc)
#define R16SP        (gb->cpu.sp)
#define A16          ((gb->cpu.hi << 8) | (gb->cpu.lo))
#define D16          A16

#define U3DST        ((gb->cpu.opcode >> 3) & 7)
#define U3SRC        (gb->cpu.opcode & 7)
#define U2IDX        ((gb->cpu.opcode >> 4) & 3)

#define IS_Z_FLAG    ((gb->cpu.r8[6] & 0b10000000) != 0)
#define IS_N_FLAG    ((gb->cpu.r8[6] & 0b01000000) != 0)
#define IS_H_FLAG    ((gb->cpu.r8[6] & 0b00100000) != 0)
#define IS_C_FLAG    ((gb->cpu.r8[6] & 0b00010000) != 0)

#define SET_Z_FLAG   (gb->cpu.r8[6] |= 0b10000000)
#define SET_N_FLAG   (gb->cpu.r8[6] |= 0b01000000)
#define SET_H_FLAG   (gb->cpu.r8[6] |= 0b00100000)
#define SET_C_FLAG   (gb->cpu.r8[6] |= 0b00010000)

#define CLEAR_Z_FLAG (gb->cpu.r8[6] &= ~0b10000000)
#define CLEAR_N_FLAG (gb->cpu.r8[6] &= ~0b01000000)
#define CLEAR_H_FLAG (gb->cpu.r8[6] &= ~0b00100000)
#define CLEAR_C_FLAG (gb->cpu.r8[6] &= ~0b00010000)

#define CC_NZ       (((gb->cpu.opcode & 0b00011000) == 0b00000000) && (!IS_Z_FLAG))
#define CC_Z        (((gb->cpu.opcode & 0b00011000) == 0b00001000) && (IS_Z_FLAG))
#define CC_NC       (((gb->cpu.opcode & 0b00011000) == 0b00010000) && (!IS_C_FLAG))
#define CC_C        (((gb->cpu.opcode & 0b00011000) == 0b00011000) && (IS_C_FLAG))
#define CONDITION   ((CC_NZ) || (CC_Z) || (CC_NC) || (CC_C))

# endif
