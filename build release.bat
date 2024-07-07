@echo off
if not exist build mkdir build
pushd build
cmake .. -DCMAKE_BUILD_TYPE=Release
popd
cmake --build build --config Release
pause