webrtc: copy gobuild clean
gobuild:
	go build -a -o gbmu -ldflags "-X main.gitCommit=$(shell git rev-parse --short HEAD)"


docker: copy build clean
build:
	docker build --build-arg="GIT_COMMIT=$(shell git rev-parse --short HEAD)" -t asarandi/gbmu:latest .

push:
	docker push asarandi/gbmu:latest

pull:
	docker pull asarandi/gbmu:latest

run:
	docker run -it --rm --network=host asarandi/gbmu:latest


SRC := \
    ../src/core/apu.c \
    ../src/core/bus.c \
    ../src/core/cpu.c \
    ../src/core/irq.c \
    ../src/core/joypad.c \
    ../src/core/lcd.c \
    ../src/core/mbc.c \
    ../src/core/rtc.c \
    ../src/core/serial.c \
    ../src/core/timer.c \
    ../include/cpu.h \
    ../include/gb.h \
    ../include/hardware.h \
    ../include/sound.h \
    ../include/timer.h \
    ../src/savefile.c \
    ../src/init.c \
    ../src/io.c \
    ../src/testing.c \
    ../src/lib/hash.c \
    ../include/hash.h \
    ../src/lib/endian.c \
    ../include/endian.h \
    ../src/lib/filter.c \
    ../include/filter.h

copy:
	@cp $(SRC) .

clean:
	@rm -f $(notdir $(SRC))

.PHONY: copy clean
