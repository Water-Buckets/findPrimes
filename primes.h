#ifndef FINDPRIMES_PRIMES_H
#define FINDPRIMES_PRIMES_H

#pragma once

#include "bits/stdc++.h"


void trialDivision(const long long &n, std::vector<long long> &primes);

void eratosthenesSieve(const long long &n, std::vector<long long> &primes);

void eulerSieve(const long long &n, std::vector<long long> &primes);

void sundaramSieve(const long long &n, std::vector<long long> &primes);

void atkinSieve(const long long &n, std::vector<long long> &primes);

void incrementalSieve(const long long &n, std::vector<long long> &primes);

void wheelSieve(const long long &n, std::vector<long long> &primes);


#endif //FINDPRIMES_PRIMES_H