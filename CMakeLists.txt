cmake_minimum_required(VERSION 3.15)
project(findPrimes)

set(CMAKE_CXX_STANDARD 17)

add_executable(findPrimes
        src/main.cpp
        src/findPrimes/primesGen.cpp
        src/findPrimes/primesGen.h
)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions(-DNDEBUG)
endif ()

find_package(Threads REQUIRED)
target_link_libraries(findPrimes Threads::Threads)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
