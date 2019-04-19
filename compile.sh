#!/bin/bash
rm -f *.o a.out test
gcc -O1 -Wno-unused-result mbc.c mmu.c interrupts.c debug.c lcd.c jump_table.c gui.c cycles.c main.c ops/*.c -I. -lSDL2 -lpthread  -o test 
