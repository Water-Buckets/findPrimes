#include "main.h"

void trialDivision(const long long &n, std::vector<long long> &primes) {
  if (n >= 2)
    primes.push_back(2);
  for (long long i = 3; i <= n; i += 2) {
    bool isPrime = true;
    for (long long p : primes) {
      if (p * p > i)
        break;
      if (i % p == 0) {
        isPrime = false;
        break;
      }
    }
    if (isPrime)
      primes.push_back(i);
  }
}

void eratosthenesSieve(const long long &n, std::vector<long long> &primes) {
  std::vector<bool> isPrime((n + 2) / 2, true);
  isPrime[0] = false;
  if (n >= 2)
    primes.push_back(2);
  for (long long i = 3; i <= n; i += 2) {
    if (isPrime[i / 2]) {
      primes.push_back(i);
      for (long long j = i * i; j <= n; j += 2 * i) {
        isPrime[j / 2] = false;
      }
    }
  }
}

void eulerSieve(const long long &n, std::vector<long long> &primes) {
  std::vector<bool> isPrime(n + 1, true);
  if (n >= 2)
    primes.push_back(2);
  for (long long i = 3; i <= n; i += 2) {
    if (isPrime[i]) {
      primes.push_back(i);
      if (i <= n / i) {
        for (long long j = i * i; j <= n; j += i * 2) {
          isPrime[j] = false;
        }
      }
    }
  }
}

void sundaramSieve(const long long &n, std::vector<long long> &primes) {
  const long long &nNew = n / 2;
  std::vector<bool> isPrime(nNew + 1, false);
  for (long long i = 1; i <= nNew; ++i)
    for (long long j = i; (i + j + 2 * i * j) <= nNew; ++j)
      isPrime[i + j + 2 * i * j] = true;
  if (n > 1)
    primes.push_back(2);
  for (long long i = 1; i <= nNew; ++i)
    if (!isPrime[i])
      primes.push_back(2 * i + 1);
}

void atkinSieve(const long long &n, std::vector<long long> &primes) {
  std::vector<bool> isPrime(n + 1, false);
  for (long long x = 1; x * x <= n; ++x) {
    for (long long y = 1; y * y <= n; ++y) {
      long long w = 4 * x * x + y * y;
      if (w <= n && (w % 12 == 1 || w % 12 == 5))
        isPrime[w].flip();
      w = 3 * x * x + y * y;
      if (w <= n && w % 12 == 7)
        isPrime[w].flip();
      if (x > y) {
        w = 3 * x * x - y * y;
        if (w <= n && w % 12 == 11)
          isPrime[w].flip();
      }
    }
  }
  for (long long a = 5; a * a <= n; ++a) {
    if (isPrime[a])
      for (long long b = a * a; b <= n; b += a * a)
        isPrime[b] = false;
  }
  if (2 <= n)
    primes.push_back(2);
  if (3 <= n)
    primes.push_back(3);
  for (long long a = 5; a <= n; a += 2)
    if (isPrime[a])
      primes.push_back(a);
}

void incrementalSieve(const long long &n, std::vector<long long> &primes) {
  std::vector<bool> isPrime(n + 1, true);
  if (n >= 2)
    primes.push_back(2);
  for (long long p = 3; p <= n; p += 2) {
    if (isPrime[p]) {
      primes.push_back(p);
      for (long long i = p * p; i <= n; i += p)
          isPrime[i] = false;
    }
  }
}

void wheelSieve(const long long &n, std::vector<long long> &primes) {
  if (n >= 2)
    primes.push_back(2);
  std::vector<bool> isPrime(n + 1, true);
  for (long long p = 3; p <= n; p += 2) {
    if (isPrime[p]) {
      primes.push_back(p);
      for (long long i = p * p; i <= n; i += p * 2)
          isPrime[i] = false;
    }
  }
}