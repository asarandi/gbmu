CFLAGS += -O2 -Wall -Werror -Wextra -I include/
SRC := \
    src/crc.c \
    src/cycles.c \
    src/debug.c \
    src/init.c \
    src/interrupts.c \
    src/joypad.c \
    src/jump_table.c \
    src/lcd.c \
    src/main.c \
    src/cartridge.c \
    src/mmu.c \
    src/ops.c \
    src/sdl.c \
    src/serial.c \
    src/sound.c \
    src/testing.c \
    src/timers.c

src/debug.o: CFLAGS  += -Wno-unused-function -Wno-unused-result
src/ops.o:   CFLAGS  += -Wno-unused-variable -Wno-unused-parameter
src/sdl.o:   CFLAGS  += $(shell sdl2-config --cflags) -Wno-unused-result
gbmu:        LDFLAGS += $(shell sdl2-config --libs)

all: gbmu

gbmu: $(SRC:.c=.o) src/crc.o
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	$(RM) $(SRC:.c=.o)

fclean: clean
	$(RM) gbmu

re: fclean all

format:
	astyle -A14 \
	--mode=c \
	--break-one-line-headers \
	--break-blocks \
	--align-pointer=name \
	--convert-tabs \
	--pad-header \
	--unpad-paren \
	--add-braces \
	--max-code-length=80 \
	--break-after-logical \
	--delete-empty-lines \
	--indent-continuation=1 \
	--lineend=linux \
	--suffix=none \
	src/*.c include/*.h

tests: gbmu
	./tests/mooneye.sh acceptance > tests/acceptance.results.csv
	./tests/mooneye.sh emulator-only > tests/emulator-only.results.csv
	./tests/blargg1.sh > tests/blargg1.results.csv
	./tests/blargg2.sh > tests/blargg2.results.csv

.PHONY: tests
