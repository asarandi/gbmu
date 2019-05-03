#!/bin/bash
rm -rf snd
gcc sound.c `sdl2-config --cflags --libs` -o snd
