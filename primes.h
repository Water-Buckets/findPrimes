#ifndef FINDPRIMES_PRIMES_H
#define FINDPRIMES_PRIMES_H

#pragma once

#include "bits/stdc++.h"


std::vector<long long> trialDivision(long long n);
std::vector<long long> eratosthenesSieve(long long n);
std::vector<long long> eulerSieve(long long n);
std::vector<long long> sundaramSieve(long long n);
std::vector<long long> atkinSieve(long long n);
std::vector<long long> incrementalSieve(long long n);
std::vector<long long> wheelSieve(long long n);



#endif //FINDPRIMES_PRIMES_H