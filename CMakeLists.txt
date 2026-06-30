cmake_minimum_required(VERSION 3.20)

project(MaritimeOpsSim VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(MaritimeOpsSim
    cpp/src/main.cpp
    cpp/src/Vessel.cpp
)

target_include_directories(MaritimeOpsSim PRIVATE
    cpp/include
)

if (MSVC)
    target_compile_options(MaritimeOpsSim PRIVATE /W4)
else()
    target_compile_options(MaritimeOpsSim PRIVATE -Wall -Wextra -Wpedantic)
endif()