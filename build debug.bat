@echo off
if not exist build mkdir build
pushd build
cmake ..
popd
cmake --build build
pause