FROM ubuntu:latest

WORKDIR /system-monitor

RUN apt update && apt install -y gcc libx11-dev cmake

COPY . .

RUN mkdir build && cd build && cmake .. -DCMAKE_BUILD_TYPE=Release && make

EXPOSE 8080

CMD "./build/system-monitor"