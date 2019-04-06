#!/bin/bash
rm -f *.o a.out test
gcc -g jump_table.c main.c ops/*.c -I. -o test
