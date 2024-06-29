#!/usr/bin/env bash
mkdir build
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build/