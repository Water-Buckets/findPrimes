cmake_minimum_required(VERSION 3.15)
project(findPrimes_multiThread)

set(CMAKE_CXX_STANDARD 17)

add_executable(findPrimes_multiThread src/main.cpp
        src/includes/main.h
        src/argInput.cpp
        src/includes/argInput.h
        src/includes/multiThread.h
        src/multiThread.cpp
        src/singleThread.cpp
        src/includes/singleThread.h
        src/includes/sieveMethods.h
        src/includes/segSieveMethods.h
        src/sieves/segSieveMethods.cpp
        src/sieves/sieveMethods.cpp
        src/includes/utilities.h
        src/utilities.cpp
)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions(-DNDEBUG)
endif ()

find_package(Threads REQUIRED)
target_link_libraries(findPrimes_multiThread Threads::Threads)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
