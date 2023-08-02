#include "../includes/sieveMethods.h"

void trialDivision(const long long &n, std::vector<long long> &primes) {
  if (n >= 2)
    primes.push_back(2);                  // 2 is the only even prime
  for (long long i = 3; i <= n; i += 2) { // trial division
    bool isPrime = true;                  // isPrime is true if i is a prime
    for (long long p : primes) {          // for each prime p
      if (p * p > i)
        break; // if p is greater than sqrt(i), break the loop
      if (i % p == 0) {
        isPrime = false; // if p divides i, i is not a prime
        break;
      }
    }
    if (isPrime)
      primes.push_back(i); // if i is a prime, add i to the list
  }
}

void eratosthenesSieve(const long long &n, std::vector<long long> &primes) {
  std::vector<bool> isPrime(
      (n + 2) / 2, false); // isPrime[i] is true if (2 * i + 1) is a prime
  isPrime[0] = true;       // 1 is not a prime
  if (n >= 2)
    primes.push_back(2);                  // 2 is the only even prime
  for (long long i = 3; i <= n; i += 2) { // check odd integers i
    if (!isPrime[i / 2]) {
      primes.push_back(i); // i is a prime

      // mark multiples of i as non-prime
      for (long long j = i * i; j <= n; j += 2 * i)
        isPrime[j / 2] = true; //
    }
  }
}

void eulerSieve(const long long &n, std::vector<long long> &primes) {
  std::vector<bool> isPrime(n + 1, false); // isPrime[i] is true if i is a prime
  if (n >= 2)
    primes.push_back(2);                  // 2 is the only even prime
  for (long long i = 3; i <= n; i += 2) { // check odd integers i
    if (!isPrime[i]) {
      primes.push_back(i); // i is a prime

      // mark multiples of i as non-prime
      if (i <= n / i)
        for (long long j = i * i; j <= n; j += i * 2)
          isPrime[j] = true;
    }
  }
}

void sundaramSieve(const long long &n, std::vector<long long> &primes) {
  const long long &nNew = n / 2; // nNew is the number of odd integers in [1, n]
  std::vector<bool> isPrime(nNew + 1,
                            false); // isPrime[i] is true if i is a prime

  // generate all the numbers of the form i + j + 2 * i * j
  for (long long i = 1; i <= nNew; ++i)
    for (long long j = i; (i + j + 2 * i * j) <= nNew; ++j)
      isPrime[i + j + 2 * i * j] = true;
  if (n > 1)
    primes.push_back(2); // 2 is the only even prime

  // generate primes
  for (long long i = 1; i <= nNew; ++i)
    if (!isPrime[i])
      primes.push_back(2 * i + 1);
}

void atkinSieve(const long long &n, std::vector<long long> &primes) {
  std::vector<bool> isPrime(n + 1, false); // isPrime[i] is true if i is a prime

  // put in candidate primes: integers which have an odd number of
  for (long long x = 1; x * x <= n; ++x) {
    // solutions to the equation: x^2 + y^2 = n
    for (long long y = 1; y * y <= n; ++y) {
      long long w = 4 * x * x + y * y; // first quadratic using m = 4
      // w is prime, mark multiples of its square as non-prime
      if (w <= n && (w % 12 == 1 || w % 12 == 5))
        isPrime[w].flip();
      w = 3 * x * x + y * y; // second quadratic using m = 3
      if (w <= n && w % 12 == 7)
        isPrime[w]
            .flip(); // w is prime, mark multiples of its square as non-prime

      // third quadratic using m = 3 (x > y)
      if (x > y) {
        w = 3 * x * x - y * y;
        if (w <= n && w % 12 == 11)
          isPrime[w]
              .flip(); // w is prime, mark multiples of its square as non-prime
      }
    }
  }

  // eliminate composites by sieving
  for (long long a = 5; a * a <= n; ++a)
    if (isPrime[a])
      // mark multiples of square as non-prime
      for (long long b = a * a; b <= n; b += a * a)
        isPrime[b] = false;
  if (2 <= n)
    primes.push_back(2); // 2 is the only even prime
  if (3 <= n)
    primes.push_back(3); // 3 is the only odd prime
  for (long long a = 5; a <= n; a += 2)
    if (isPrime[a])
      primes.push_back(a); // add primes
}

void incrementalSieve(const long long &n, std::vector<long long> &primes) {
  std::vector<bool> isPrime(n + 1, false); // isPrime[i] is true if i is a prime
  if (n >= 2)
    primes.push_back(2); // 2 is the only even prime
  for (long long p = 3; p <= n; p += 2) {
    if (!isPrime[p]) {
      primes.push_back(p); // p is a prime
      // mark multiples of p as non-prime
      for (long long i = p * p; i <= n; i += p)
        isPrime[i] = true;
    }
  }
}

void wheelSieve(const long long &n, std::vector<long long> &primes) {
  primes.push_back(2); // 2 is the only even prime
  primes.push_back(3); // 3 is the only prime divisible by 3
  primes.push_back(5); // 5 is the only prime divisible by 5

  // wheel factorization
  const int wheel_indices[8] = {1, 7, 11, 13, 17, 19, 23, 29};
  std::vector<bool> is_prime(n + 1,
                             true);  // is_prime[i] is true if i is a prime
  is_prime[0] = is_prime[1] = false; // 0 and 1 are not primes

  // put in candidate primes: integers which have an odd number of
  for (long long i = 0; i <= n; i += 30) {
    // solutions to the equation: x^2 + y^2 = n
    for (int wheel_indice : wheel_indices) {
      long long num = i + wheel_indice; // num is prime if it is not divisible
                                        // by any of the first 7 primes
      if (num > n)
        break; // num is out of range
      if (is_prime[num]) {
        primes.push_back(num); // num is a prime
        // mark multiples of num as non-prime
        for (long long p = num * num; p <= n; p += num)
          is_prime[p] = false;
      }
    }
  }
}
