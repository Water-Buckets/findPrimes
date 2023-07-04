#ifndef FINDPRIMES_UTILITIES_H
#define FINDPRIMES_UTILITIES_H

#pragma once

#include "bits/stdc++.h"

long long calcAndPrintDuration(const long long &n, const char &m, std::vector<long long> &primes);

long long outputToFile(const std::vector<long long> &primes, const long long &n);

void calculatePrimes(const long long &n, const char &m, std::vector<long long> &primes);

#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-use-anyofallof"

inline bool isNumeric(const std::string &str) {
    for (char c: str) {
        if (!std::isdigit(c)) return false;
    }
    return true;
}

#pragma clang diagnostic pop


#endif // FINDPRIMES_UTILITIES_H