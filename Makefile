CFLAGS  += -O2 -Wall -Werror -Wextra -I include/
SRC := \
    src/cycles.c \
    src/debug.c \
    src/init.c \
    src/interrupts.c \
    src/joypad.c \
    src/jump_table.c \
    src/lcd.c \
    src/main.c \
    src/mbc1.c \
    src/mbc2.c \
    src/mbc3.c \
    src/mbc5.c \
    src/mbc.c \
    src/mmu.c \
    src/ops.c \
    src/serial.c \
    src/sound.c \
    src/tcp_client.c \
    src/tcp_server.c \
    src/timers.c

SDL_SRC      := src/sdl.c
SFML_SRC     := src/sfml.c
TUI_SRC      := src/tui.c

BIN          := gbmu-sdl gbmu-sfml gbmu-tui
OBJ          := $(patsubst %.c,%.o,$(wildcard src/*.c))

src/debug.o: CFLAGS += -Wno-unused-result
src/ops.o:   CFLAGS += -Wno-unused-variable -Wno-unused-parameter

src/sdl.o:   CFLAGS += $(shell sdl2-config --cflags) -Wno-unused-result
gbmu-sdl:    LDFLAGS += $(shell sdl2-config --libs)

src/sfml.o:  CFLAGS += -Wno-deprecated-declarations
gbmu-sfml:   LDFLAGS += -lcsfml-audio -lcsfml-graphics -lcsfml-network -lcsfml-system -lcsfml-window

src/tui.o:   CFLAGS += -I miniaudio/
gbmu-tui:    LDFLAGS += -ldl -lpthread -lm -lcaca


all: $(BIN)

gbmu-sdl: $(SRC:.c=.o) $(SDL_SRC:.c=.o)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

gbmu-sfml: $(SRC:.c=.o) $(SFML_SRC:.c=.o)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

gbmu-tui: $(SRC:.c=.o) $(TUI_SRC:.c=.o)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(BIN)

re: fclean all

format:
	astyle -A14 -n src/*.c include/*.h
