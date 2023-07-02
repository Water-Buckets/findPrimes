#include "primes.h"

std::vector<long long> trialDivision(long long n) {
    std::vector<long long> primes;
    if (n >= 2) primes.push_back(2);
    for (long long i = 3; i <= n; i += 2) {
        bool isPrime = true;
        long long sqrt_i = std::ceil(std::sqrt(i));
        for (long long p: primes) {
            if (p > sqrt_i) break;
            if (i % p == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) primes.push_back(i);
    }
    return primes;
}

std::vector<long long> eratosthenesSieve(long long n) {
    std::vector<bool> isPrime(n + 1, true);
    std::vector<long long> primes;
    isPrime[0] = isPrime[1] = false;
    for (long long i = 2; i <= n; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
            if (i * i <= n) {
                for (long long j = i * i; j <= n; j += i) {
                    isPrime[j] = false;
                }
            }
        }
    }
    return primes;
}

std::vector<long long> eulerSieve(long long n) {
    std::vector<long long> primes;
    if (n >= 2) primes.push_back(2);
    std::vector<bool> isPrime((n + 1) / 2, true);
    for (long long i = 3; i <= n; i += 2) {
        if (isPrime[i / 2]) {
            primes.push_back(i);
            for (long long j = i; j * i <= n; j += 2) {
                isPrime[i * j / 2] = false;
            }
        }
    }
    return primes;
}

std::vector<long long> sundaramSieve(long long n) {
    long long nNew = (n - 2) / 2;
    std::vector<bool> marked(nNew + 1, false);
    std::vector<long long> primes;
    for (long long i = 1; i <= nNew; i++)
        for (long long j = i; (i + j + 2 * i * j) <= nNew; j++)
            marked[i + j + 2 * i * j] = true;
    if (n > 2) primes.push_back(2);
    for (long long i = 1; i <= nNew; i++)
        if (!marked[i]) primes.push_back(2 * i + 1);
    return primes;
}

std::vector<long long> atkinSieve(long long n) {
    std::vector<bool> sieve(n + 1, false);
    std::vector<long long> primes;
    for (long long x = 1; x * x <= n; x++) {
        for (long long y = 1; y * y <= n; y++) {
            long long w = 4*x*x + y*y;
            if (w <= n && (w % 12 == 1 || w % 12 == 5)) sieve[w] = !sieve[w];
            w = 3*x*x + y*y;
            if (w <= n && w % 12 == 7) sieve[w] = !sieve[w];
            w = 3*x*x - y*y;
            if (x > y && w <= n && w % 12 == 11) sieve[w] = !sieve[w];
        }
    }
    for (long long r = 5; r * r <= n; r++) {
        if (sieve[r]) {
            for (long long i = r * r; i <= n; i += r * r)
                sieve[i] = false;
        }
    }
    if (n > 2) primes.push_back(2);
    if (n > 3) primes.push_back(3);
    for (long long a = 5; a <= n; a+=2)
        if (sieve[a]) primes.push_back(a);
    return primes;
}

std::vector<long long> incrementalSieve(long long n) {
    std::vector<long long> primes;
    std::vector<bool> sieve(n + 1, true);
    for (long long p = 2; p <= n; p++) {
        if (sieve[p]) {
            primes.push_back(p);
            for (long long i = p * p; i <= n; i += p)
                sieve[i] = false;
        }
    }
    return primes;
}

std::vector<long long> wheelSieve(long long n) {
    std::vector<long long> primes;
    std::vector<bool> sieve(n + 1, true);
    for (long long p = 2; p <= n; p++) {
        if (sieve[p]) {
            primes.push_back(p);
            for (long long i = p * p; i <= n; i += p * 2)
                sieve[i] = false;
        }
    }
    return primes;
}