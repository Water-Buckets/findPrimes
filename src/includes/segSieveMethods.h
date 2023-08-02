//
// Created by ASUS on 2023/7/11.
//

#ifndef FINDPRIMES_MULTITHREAD_SEGSIEVEMETHODS_H
#define FINDPRIMES_MULTITHREAD_SEGSIEVEMETHODS_H

#include <algorithm>
#include <vector>

void segTrialDivision(const long long &lL, const long long &uL,
                      std::vector<long long> &primes,
                      const std::vector<long long> &preSievedPrimes);

void segEratosthenesSieve(const long long &lL, const long long &uL,
                          std::vector<long long> &primes,
                          const std::vector<long long> &preSievedPrimes);

void segEulerSieve(const long long &lL, const long long &uL,
                   std::vector<long long> &primes,
                   const std::vector<long long> &preSievedPrimes);

void segSundaramSieve(const long long &lL, const long long &uL,
                      std::vector<long long> &primes,
                      const std::vector<long long> &preSievedPrimes);

void atkinSieve(const long long &lL, const long long &uL,
                std::vector<long long> &primes,
                const std::vector<long long>
                    &preSievedPrimes); // unused due to the complexity of the
                                       // Atkin Sieve algorithm

void segIncrementalSieve(const long long &lL, const long long &uL,
                         std::vector<long long> &primes,
                         const std::vector<long long> &preSievedPrimes);

void wheelSieve(const long long &lL, const long long &uL,
                std::vector<long long> &primes,
                const std::vector<long long>
                    &preSievedPrimes); // unused due to the complexity of the
                                       // Wheel Sieve algorithm

#endif // FINDPRIMES_MULTITHREAD_SEGSIEVEMETHODS_H
