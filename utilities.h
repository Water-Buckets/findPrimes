//
// Created by ASUS on 2023/6/29.
//

#ifndef FINDPRIMES_UTILITIES_H
#define FINDPRIMES_UTILITIES_H

#pragma once
#include <bits/stdc++.h>

std::pair<std::vector<long long>, long long> calcAndPrintDuration(long long n,char m);
void printTotalDuration(long long duration, long long durationWrite);
long long outputToFile(const std::vector<long long>& primes, long long n);
bool isNumeric(const std::string& str);
std::vector<long long> calculatePrimes(long long n,char m);


#endif //FINDPRIMES_UTILITIES_H
