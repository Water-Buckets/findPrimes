//
// Created by ASUS on 2023/7/7.
//

#ifndef FINDPRIMES_ARGINPUT_H
#define FINDPRIMES_ARGINPUT_H

#include "multiThread.h"
#include "segSieveMethods.h"
#include "sieveMethods.h"
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
    std::cout << "Using Incremental Sieve" << std::endl;
    return incrementalSieve;
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
  case 'f':
    return segIncrementalSieve;
  default:
    throw std::invalid_argument("Invalid argument.");
  }
}

void argInput(char *argv[]);

#endif // FINDPRIMES_ARGINPUT_H
