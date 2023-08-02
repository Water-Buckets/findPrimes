//
// Created by ASUS on 2023/7/7.
//

#ifndef FINDPRIMES_MULTITHREAD_MAIN_H
#define FINDPRIMES_MULTITHREAD_MAIN_H

#include "argInput.h"
#include <iostream>

inline void printHelp() {

#ifndef NDEBUG
  std::cerr << __func__ << std::endl;
#endif

  std::cout << "Usage: findprimes [threads] [method] [n] [outputFile]"
            << std::endl;
  std::cout << "If threads equals 1 the program will run in singleThread mode."
            << std::endl;
  std::cout
      << "Else if threads is over 1 the program will run in multiThread mode."
      << std::endl;
  std::cout << "You can tell the program to use multiple threads by providing "
               "a number for threads."
            << std::endl;
  std::cout << "If the number of threads is invalid, the program will exit "
               "with an error."
            << std::endl;
  std::cout << "You can tell the program to use a specific method by providing "
               "a character for method."
            << std::endl;
  std::cout << "For method you can choose between 'a' 'b' 'c' 'd' 'e' 'f' 'g'."
            << std::endl;
  std::cout << "a stand for Trial Division" << std::endl;
  std::cout << "b stand for Sieve of Eratosthenes" << std::endl;
  std::cout << "c stand for Sieve of Euler" << std::endl;
  std::cout << "d stand for Sieve of Sundaram" << std::endl;
  std::cout << "e stand for Sieve of Atkin" << std::endl;
  std::cout << "f stand for Incremental Sieve" << std::endl;
  std::cout << "g stand for Wheel Sieve" << std::endl;
  std::cout << "When using multiThread mode Sieve of Atkin and Wheel Sieve "
               "aren't supported."
            << std::endl;
  std::cout << "n stand for the upper limit of the primes you want to find."
            << std::endl;
  std::cout << "outputFile is the file that you want the primes to be output."
            << std::endl;
  std::cout << "If no arguments are provided, the program will show this help."
            << std::endl;
}

#endif // FINDPRIMES_MULTITHREAD_MAIN_H
