//
// Created by ASUS on 2023/6/28.
//

#ifndef FINDPRIMES_PRIMES_H
#define FINDPRIMES_PRIMES_H

#pragma once

#include <bits/stdc++.h>


std::vector<long long> trialDivision(long long n);
std::vector<long long> eratosthenesSieve(long long n);
std::vector<long long> eulerSieve(long long n);

int usrInput();
int argInput(long long n, char m);



#endif //FINDPRIMES_PRIMES_H
