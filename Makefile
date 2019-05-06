CFLAGS  += -O1 -Wall -Werror -Wextra -I include
CFLAGS  += -Wno-format -Wno-unused-parameter -Wno-unused-variable -Wno-unused-result
CFLAGS  += $(shell sdl2-config --cflags)
LDFLAGS += $(shell sdl2-config --static-libs)

src = $(wildcard src/*.c)
src += $(wildcard src/ops/*.c)

gbmu: $(src:.c=.o) 
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o gbmu

clean:
	rm -f $(src:.c=.o)

