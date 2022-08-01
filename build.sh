#!/bin/bash

if [[ ! -e /build ]]; then
    mkdir build/
    cd build/
    cmake ..
    make
    ./Sentinel
fi
