CFLAGS  += -O2 -Wall -Werror -Wextra -I include
LDFLAGS += $(shell sdl2-config --libs)

src = $(wildcard src/*.c)

src/debug.o : CFLAGS += -Wno-unused-result
src/ops.o : CFLAGS += -Wno-unused-variable -Wno-unused-parameter
src/sound.o src/gui.o : CFLAGS += $(shell sdl2-config --cflags)

gbmu: $(src:.c=.o) 
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o gbmu

clean:
	rm -f $(src:.c=.o)

fclean: clean
	rm -f gbmu

re: fclean gbmu
