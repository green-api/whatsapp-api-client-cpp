cmake_minimum_required(VERSION 3.8.0)
project(whatsapp-api-client-cpp VERSION 0.0.1)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")

add_library(whatsapp-api-client-cpp STATIC)

target_include_directories(whatsapp-api-client-cpp PRIVATE ${CMAKE_SOURCE_DIR}/include)
file(GLOB SOURCES "source/*.cpp")
target_sources(whatsapp-api-client-cpp PRIVATE ${SOURCES})

find_package(CURL REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

if(MSVC)
    target_link_libraries(whatsapp-api-client-cpp PRIVATE CURL::libcurl nlohmann_json::nlohmann_json)
    # target_compile_definitions(whatsapp-api-client-cpp PRIVATE WIN32_LEAN_AND_MEAN)
elseif(UNIX)
    target_link_libraries(whatsapp-api-client-cpp PRIVATE CURL::libcurl nlohmann_json::nlohmann_json pthread)
endif()
