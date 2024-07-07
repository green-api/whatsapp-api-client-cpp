cmake_minimum_required(VERSION 3.5)
project(whatsapp-api-client-cpp VERSION 0.0.1)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")

add_library(whatsapp-api-client-cpp STATIC)

target_include_directories(whatsapp-api-client-cpp PRIVATE ${CMAKE_SOURCE_DIR}/include)
file(GLOB_RECURSE SOURCES "source/*.cpp")
target_sources(whatsapp-api-client-cpp PRIVATE ${SOURCES})

# Specifying paths to required library versions
# set(ZLIB_LIBRARY "${CMAKE_SOURCE_DIR}/vcpkg/installed/x64-windows/lib")
# set(ZLIB_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/vcpkg/installed/x64-windows/include")
# set(nlohmann_json_DIR "${CMAKE_SOURCE_DIR}/vcpkg/installed/x64-windows/share/nlohmann_json")
# set(CURL_LIBRARY "${CMAKE_SOURCE_DIR}/vcpkg/installed/x64-windows/lib")
# set(CURL_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/vcpkg/installed/x64-windows/include/curl")

find_package(ZLIB REQUIRED)
find_package(CURL REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

if(MSVC)
    target_link_libraries(whatsapp-api-client-cpp PRIVATE CURL::libcurl nlohmann_json::nlohmann_json ZLIB::ZLIB)
elseif(UNIX)
    target_link_libraries(whatsapp-api-client-cpp PRIVATE CURL::libcurl nlohmann_json::nlohmann_json pthread)
endif()
