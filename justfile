set shell := ["powershell.exe", "-c"]

default: build run

build:
    cmake --build build

run:
    ./build/punggol.exe
