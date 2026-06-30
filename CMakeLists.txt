cmake_minimum_required(VERSION 3.20)

project(MaritimeOpsSim VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
    nlohmann_json
    URL https://github.com/nlohmann/json/archive/refs/tags/v3.11.3.zip
)

FetchContent_MakeAvailable(nlohmann_json)

add_library(MaritimeOpsSimCore
    cpp/src/Mission.cpp
    cpp/src/ScenarioLoader.cpp
    cpp/src/SimulationEngine.cpp
    cpp/src/Vessel.cpp
)

target_include_directories(MaritimeOpsSimCore PUBLIC
    cpp/include
)

target_link_libraries(MaritimeOpsSimCore PUBLIC
    nlohmann_json::nlohmann_json
)

if (MSVC)
    target_compile_options(MaritimeOpsSimCore PRIVATE /W4)
else()
    target_compile_options(MaritimeOpsSimCore PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_executable(MaritimeOpsSim
    cpp/src/main.cpp
)

target_link_libraries(MaritimeOpsSim PRIVATE
    MaritimeOpsSimCore
)

enable_testing()

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(MaritimeOpsSimTests
    cpp/tests/VesselMovementTest.cpp
)

target_link_libraries(MaritimeOpsSimTests PRIVATE
    MaritimeOpsSimCore
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(MaritimeOpsSimTests)