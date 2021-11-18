# syntax=docker/dockerfile:1

FROM golang:alpine

WORKDIR /app

COPY ./ ./

RUN apk add --update build-base gcc gstreamer-dev gst-plugins-base-dev && go build -o gbmu

EXPOSE 8080

CMD [ "./gbmu" ]
