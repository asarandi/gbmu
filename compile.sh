#!/bin/bash
rm -f *.o a.out test
gcc -O1 main.c ops/*.c -I. -o test
