webrtc: copy gobuild clean
gobuild:
	go build -a -o gbmu

docker: copy dockerbuild clean
dockerbuild:
	docker build -t gbmu .

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
    ../src/lib/endian.c \
    ../include/endian.h \
    ../src/lib/filter.c \
    ../include/filter.h

copy:
	@cp $(SRC) .

clean:
	@rm -f $(notdir $(SRC))

.PHONY: copy clean
