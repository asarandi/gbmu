#!/bin/bash
rm -f *.o a.out test
gcc -O1 jump_table.c main.c -I. -o test
