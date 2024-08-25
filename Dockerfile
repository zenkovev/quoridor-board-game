FROM ubuntu:22.04 AS builder

RUN apt update
RUN apt -y install build-essential cmake
RUN apt -y install libgtkmm-3.0-dev
RUN apt -y install libcanberra-gtk-module libcanberra-gtk3-module

WORKDIR /builder
COPY . .
RUN mkdir build && cd build && cmake .. && make

FROM ubuntu:22.04

RUN apt update
RUN apt -y install libgtkmm-3.0-dev
RUN apt -y install libcanberra-gtk-module libcanberra-gtk3-module

WORKDIR /game
COPY --from=builder /builder/bin/Quoridor /game/
COPY --from=builder /builder/code/image/ /game/code/image/

ENTRYPOINT ./Quoridor
