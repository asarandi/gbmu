#!/bin/bash
rm -f *.o a.out test
gcc -g jump_table.c gui.c cycles.c main.c ops/*.c -I. -lSDL2 -lpthread  -o test 
