#!/usr/bin/env bash
if [ ! -d "build" ]; then
  mkdir build
fi
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build/