set shell := ["powershell.exe", "-c"]

default: build run

build:
    cmake --build build --parallel

run:
    ./build/punggol.exe

clean:
    Remove-Item build -Recurse -Force
