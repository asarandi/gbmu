webrtc: copy gobuild remove
gobuild:
	go build -o gbmu

docker: copy dockerbuild remove
dockerbuild:
	docker build -t gbmu .

copy:
	@cp ../include/cpu.h .
	@cp ../include/endian.h .
	@cp ../include/gb.h .
	@cp ../include/hardware.h .
	@cp ../include/sound.h .
	@cp ../include/timer.h .
	@cp ../src/bus.c .
	@cp ../src/cartridge.c .
	@cp ../src/cpu.c .
	@cp ../src/endian.c .
	@cp ../src/init.c .
	@cp ../src/interrupts.c .
	@cp ../src/io.c .
	@cp ../src/joypad.c .
	@cp ../src/lcd.c .
	@cp ../src/savefile.c .
	@cp ../src/serial.c .
	@cp ../src/sound.c .
	@cp ../src/timer.c .

remove:
	@rm -f cpu.h
	@rm -f endian.h
	@rm -f gb.h
	@rm -f hardware.h
	@rm -f sound.h
	@rm -f timer.h
	@rm -f bus.c
	@rm -f cartridge.c
	@rm -f cpu.c
	@rm -f endian.c
	@rm -f init.c
	@rm -f interrupts.c
	@rm -f io.c
	@rm -f joypad.c
	@rm -f lcd.c
	@rm -f savefile.c
	@rm -f serial.c
	@rm -f sound.c
	@rm -f timer.c

.PHONY: copy remove
