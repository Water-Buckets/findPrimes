#ifndef FINDPRIMES_UTILITIES_H
#define FINDPRIMES_UTILITIES_H

#pragma once
#include "bits/stdc++.h"

long long calcAndPrintDuration(const long long &n, char &m, std::vector<long long> &primes);
long long outputToFile(const std::vector<long long> &primes,const long long &n);
bool isNumeric(const std::string& str);
void calculatePrimes(const long long &n, char &m, std::vector<long long> &primes);


#endif //FINDPRIMES_UTILITIES_H