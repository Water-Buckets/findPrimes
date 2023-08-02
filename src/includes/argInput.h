//
// Created by ASUS on 2023/7/7.
//

#ifndef FINDPRIMES_MULTITHREAD_ARGINPUT_H
#define FINDPRIMES_MULTITHREAD_ARGINPUT_H

#include "multiThread.h"
#include "segSieveMethods.h"
#include "sieveMethods.h"
#include "singleThread.h"
#include <cctype>
#include <iostream>

inline bool isNumeric(const std::string &str) {

#ifndef NDEBUG
  std::cerr << __func__ << std::endl;
#endif

  for (char c : str)
    if (!std::isdigit(c))
      return false;
  return true;
}

inline auto switchSMethods(const char &m)
    -> void (*)(const long long &n, std::vector<long long> &primes) {

#ifndef NDEBUG
  std::cerr << __func__ << std::endl;
#endif

  switch (m) {
  case 'a':
    std::cout << "Using Trial Division" << std::endl;
    return trialDivision;
  case 'b':
    std::cout << "Using Sieve of Eratosthenes" << std::endl;
    return eratosthenesSieve;
  case 'c':
    std::cout << "Using Sieve of Euler" << std::endl;
    return eulerSieve;
  case 'd':
    std::cout << "Using Sieve of Sundaram" << std::endl;
    return sundaramSieve;
  case 'e':
    std::cout << "Using Sieve of Atkin" << std::endl;
    return atkinSieve;
  case 'f':
    std::cout << "Using Incremental Sieve" << std::endl;
    return incrementalSieve;
  case 'g':
    std::cout << "Using Wheel Sieve" << std::endl;
    return wheelSieve;
  default:
    throw std::invalid_argument("Invalid argument.");
  }
}

inline auto switchMMethods(const char &m)
    -> void (*)(const long long &lL, const long long &uL,
                std::vector<long long> &primes,
                const std::vector<long long> &preSievedPrimes) {

#ifndef NDEBUG
  std::cerr << __func__ << std::endl;
#endif

  switch (m) {
  case 'a':
    return segTrialDivision;
  case 'b':
    return segEratosthenesSieve;
  case 'c':
    return segEulerSieve;
  case 'd':
    return segSundaramSieve;
  case 'e':
    throw std::runtime_error("What?!");
  case 'f':
    return segIncrementalSieve;
  case 'g':
    throw std::runtime_error("What?!");
  default:
    throw std::invalid_argument("Invalid argument.");
  }
}

void argInput(char *argv[]);

#endif // FINDPRIMES_MULTITHREAD_ARGINPUT_H
