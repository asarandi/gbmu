# syntax=docker/dockerfile:1

FROM golang:alpine
WORKDIR /build
COPY apu.c bridge.c bridge.go bridge.h bus.c cpu.c cpu.h endian.c endian.h filter.c filter.h gb.h go.mod go.sum hardware.h hash.c hash.h init.c io.c irq.c joypad.c lcd.c main.go mbc.c pipeline.c pipeline.h rtc.c savefile.c serial.c sound.h testing.c timer.c timer.h video_message.c ./
RUN apk add --no-cache build-base gstreamer-dev gst-plugins-base-dev
RUN go build -o gbmu

FROM alpine:latest
RUN apk add --no-cache gst-plugins-base gst-plugins-good gst-plugins-ugly
WORKDIR /app
COPY ./web ./web
COPY --from=0 /build/gbmu ./
CMD [ "./gbmu" ]
