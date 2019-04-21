#!/bin/bash
rm -f *.o a.out test
gcc \
	-g \
    -fsanitize=undefined \
    -Wno-format \
	mbc.c \
	mmu.c \
	interrupts.c \
	debug.c \
	lcd.c \
	jump_table.c \
	gui.c \
	cycles.c \
	timers.c \
	joypad.c \
    init.c \
	main.c \
	ops/*.c \
	-I. \
    -lSDL2 \
	-o test
