cmake_minimum_required(VERSION 3.25)
project(findPrimes)

set(CMAKE_CXX_STANDARD 17)

add_executable(findPrimes main.cpp primes.cpp primes.h utilities.cpp utilities.h input.h input.cpp)

