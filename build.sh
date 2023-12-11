#!/bin/bash


CLEAN=${1:-'none'}

if [ "${CLEAN}" = "clean" ]; then
    if [ -d "build" ]; then
        rm -r build
    fi
fi

mkdir build
cd build

cmake ..

cmake --build . --target all