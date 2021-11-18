package main

// #include "cpu.h"
// #include "gb.h"
// #include "hardware.h"
// #include "sound.h"
// #include "timer.h"
// #include "pipeline.h"
// #include "bridge.h"
// #cgo pkg-config: gstreamer-1.0 gstreamer-plugins-base-1.0
// #cgo CFLAGS: -Ofast
// #cgo LDFLAGS: -pthread -Ofast -lgstapp-1.0 -lpthread
import "C"
import (
	"log"
	"time"
	"unsafe"
)

func emulator(done chan bool) {
	go C.run()
	// 1,000,000,000 nanoseconds / (65536 hz sound rate / 1024 sample frames)
	ticker := time.NewTicker(15625000 * time.Nanosecond)
	defer ticker.Stop()
loop:
	for {
		select {
		case <-ticker.C:
			C.timer_callback()
		case <-done:
			break loop
		}
	}
	C.finish()
}

//export BroadcastRTP
func BroadcastRTP(trackId C.int, data unsafe.Pointer, size C.int) {
	peersMux.RLock()
	packet := C.GoBytes(data, size)
	for id, peer := range peers {
		if !peer.broadcast {
			continue
		}
		if int(trackId) < len(peer.tracks) {
			_, err := peer.tracks[trackId].Write(packet)
			if err != nil {
				log.Println(id, err)
			}
		}
	}
	peersMux.RUnlock()
}

func SetInput(playerId int, input byte) {
	C.set_input(C.int(playerId), C.int(input))
}

func SetCartridge(playerId int, data []byte) {
	C.load_rom_from_bytes(C.int(playerId), C.CBytes(data), C.int(len(data)))
}

func SetSavefile(playerId int, data []byte) {
	C.load_ram_from_bytes(C.int(playerId), C.CBytes(data), C.int(len(data)))
}

func GetSavefile(playerId int) []byte {
	data := make([]byte, 131072)
	size := C.save_ram_to_bytes(C.int(playerId), unsafe.Pointer(&data[0]), C.int(len(data)))
	return data[:size]
}

func SetFrameBlending(playerId int, enabled bool) {
	C.set_frame_blending(C.int(playerId), C.bool(enabled))
}

func ReloadBoth() {
	C.reload_both()
}
