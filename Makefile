CFLAGS  += -O1 -Wall -Werror -Wextra -I include
CFLAGS  += -Wno-unused-parameter -Wno-unused-variable -Wno-unused-result
LDFLAGS += -lSDL2

src = $(wildcard src/*.c)
src += $(wildcard src/ops/*.c)

gbmu: $(src:.c=.o) 
	$(CC) $(CFLAGS) $(src) $(LDFLAGS) -o gbmu

clean:
	rm -f $(src:.c=.o)

