CFLAGS  += -g -pedantic -std=c89 -Wall -Werror -Wextra -I include
LDFLAGS += $(shell sdl2-config --libs)

src = $(wildcard src/*.c)

gbmu: $(src:.c=.o) 
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o gbmu

src/ops.o:
	$(CC) $(CFLAGS) -Wno-unused-variable -Wno-unused-parameter -c src/ops.c -o $@

src/debug.o:
	$(CC) $(CFLAGS) -Wno-unused-result -c src/debug.c -o $@

src/sound.o:
	$(CC) $(CFLAGS) $(shell sdl2-config --cflags) -c src/sound.c -o $@

src/gui.o:
	$(CC) $(CFLAGS) $(shell sdl2-config --cflags) -c src/gui.c -o $@

clean:
	rm -f $(src:.c=.o)

