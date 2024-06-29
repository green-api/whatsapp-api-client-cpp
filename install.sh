#!/usr/bin/env bash
git clone https://github.com/Microsoft/vcpkg.git
./vcpkg/bootstrap-vcpkg.sh
./vcpkg/vcpkg install curl
./vcpkg/vcpkg install nlohmann-json
# ./vcpkg install websocketpp
./vcpkg/vcpkg integrate install