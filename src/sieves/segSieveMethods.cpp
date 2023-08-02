//
// Created by ASUS on 2023/7/11.
//

#include "../includes/segSieveMethods.h"

void segTrialDivision(const long long &lL, const long long &uL,
                      std::vector<long long> &primes,
                      const std::vector<long long> &preSievedPrimes) {
  for (long long i = std::max(2LL, lL); i <= uL; ++i) { // trial division
    bool isPrime = true; // isPrime is true if i is a prime
    for (const long long &p : preSievedPrimes) { // for each prime p
      if (p * p > i)
        break;           // if p is greater than sqrt(i), break the loop
      if (i % p == 0) {  // if p divides i
        isPrime = false; // i is not a prime
        break;
      }
    }
    if (isPrime)
      primes.push_back(i); // if i is a prime, push it into primes
  }
}

void segEratosthenesSieve(const long long &lL, const long long &uL,
                          std::vector<long long> &primes,
                          const std::vector<long long> &preSievedPrimes) {
  std::vector<bool> isPrime(uL - lL + 1,
                            true); // isPrime[i] is true if i + lL is a prime

  // for each prime p, for each multiple of p, mark it as not prime
  for (const long long &p : preSievedPrimes)
    for (long long i = std::max(p * p, (lL + p - 1) / p * p); i <= uL; i += p)
      isPrime[i - lL] = false;

  // for each prime i, if it is a prime, push it into primes
  for (long long i = (lL < 2) ? 2 - lL : 0; i <= uL - lL; ++i)
    if (isPrime[i])
      primes.push_back(i + lL);
}

void segEulerSieve(const long long &lL, const long long &uL,
                   std::vector<long long> &primes,
                   const std::vector<long long> &preSievedPrimes) {
  std::vector<bool> isPrime(uL - lL + 1,
                            true); // isPrime[i] is true if i + lL is a prime

  // for each prime p, for each multiple of p, mark it as not prime
  for (const long long &p : preSievedPrimes)
    for (long long i = std::max(p * p, (lL + p - 1) / p * p); i <= uL; i += p)
      isPrime[i - lL] = false;

  // for each prime i, if it is a prime, push it into primes and mark its
  // multiples as not prime
  for (long long i = (lL < 2) ? 2 - lL : 0; i <= uL - lL; ++i) {
    if (isPrime[i]) {
      primes.push_back(i + lL);
      for (long long j = (i + lL) * (i + lL); j <= uL; j += i + lL)
        isPrime[j - lL] = false;
    }
  }
}

void segSundaramSieve(const long long &lL, const long long &uL,
                      std::vector<long long> &primes,
                      const std::vector<long long> &preSievedPrimes) {
  const long long &nNew =
      (uL - 1) / 2; // nNew is the number of odd numbers in [1, uL]
  std::vector<bool> isPrime(nNew + 1,
                            true); // isPrime[i] is true if 2 * i + 1 is a prime

  // for each pair (i, j), if i + j + 2 * i * j <= nNew, mark i + j + 2 * i * j
  // as not prime
  for (long long i = 1; i <= nNew; ++i)
    for (long long j = i; (i + j + 2 * i * j) <= nNew; ++j)
      isPrime[i + j + 2 * i * j] = false;

  // for each prime i, push 2 * i + 1 into primes
  for (long long i = std::max(lL / 2, 1LL); i <= nNew; ++i)
    if (isPrime[i])
      primes.push_back(2 * i + 1);
}

void segIncrementalSieve(const long long &lL, const long long &uL,
                         std::vector<long long> &primes,
                         const std::vector<long long> &preSievedPrimes) {
  std::vector<bool> isPrime(uL - lL + 1,
                            true); // isPrime[i] is true if i + lL is a prime

  // for each prime p, for each multiple of p, mark it as not prime
  for (const long long &p : preSievedPrimes)
    for (long long i = std::max(p * p, (lL + p - 1) / p * p); i <= uL; i += p)
      isPrime[i - lL] = false;

  // for each prime i, if it is a prime, push it into primes and mark its
  // multiples as not prime
  for (long long i = (lL < 2) ? 2 - lL : 0; i <= uL - lL; ++i) {
    if (isPrime[i]) {
      primes.push_back(i + lL);
      for (long long j = (i + lL) * (i + lL); j <= uL; j += i + lL) {
        isPrime[j - lL] = false;
      }
    }
  }
}