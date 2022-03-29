CORE := \
	src/core/apu.c \
	src/core/bus.c \
	src/core/cpu.c \
	src/core/irq.c \
	src/core/joypad.c \
	src/core/lcd.c \
	src/core/mbc.c \
	src/core/rtc.c \
	src/core/serial.c \
	src/core/timer.c

LIB := \
	src/lib/endian.c \
	src/lib/filter.c \
	src/lib/hash.c \
	src/debug.c \
	src/init.c \
	src/io.c \
	src/savefile.c \
	src/testing.c

SDL2 := \
	src/shell/sdl2/main.c \
	src/shell/sdl2/audio.c \
	src/shell/sdl2/video.c \
	src/shell/sdl2/input.c \
	src/shell/sdl2/file.c

SRC := $(CORE) $(LIB) $(SDL2)
OBJ := $(SRC:.c=.o)

CFLAGS += -O2 -Wall -Werror -Wextra -I include/
CFLAGS += $(shell sdl2-config --cflags)
LDFLAGS += -O2 -lm $(shell sdl2-config --libs)

all: gbmu

gbmu: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) gbmu

re: fclean all

tidy: $(SRC) include/*.h
	clang-tidy $^ -checks=-clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling -- $(CFLAGS)

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
	$(SRC) include/*.h webrtc/*.c webrtc/*.h

tests: gbmu
	./tests/mealybug.sh > tests/mealybug.results.csv
	./tests/mooneye.sh acceptance > tests/acceptance.results.csv
	./tests/mooneye.sh emulator-only > tests/emulator-only.results.csv
	./tests/blargg1.sh > tests/blargg1.results.csv
	./tests/blargg2.sh > tests/blargg2.results.csv

tests-gambatte: gbmu
	./tests/gambatte.sh div > tests/gambatte-div.results.csv
	./tests/gambatte.sh tima > tests/gambatte-tima.results.csv
	./tests/gambatte.sh serial > tests/gambatte-serial.results.csv

.PHONY: tests
