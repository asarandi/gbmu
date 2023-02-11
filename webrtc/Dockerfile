# syntax=docker/dockerfile:1

FROM golang:alpine
WORKDIR /build
COPY ./ ./
RUN apk add --no-cache build-base gstreamer-dev gst-plugins-base-dev && go build -o gbmu

FROM alpine:latest
RUN apk add --no-cache gst-plugins-base gst-plugins-good gst-plugins-ugly
WORKDIR /app
COPY --from=0 /build/web ./web
COPY --from=0 /build/gbmu ./
CMD [ "./gbmu" ]
