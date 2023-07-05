#ifndef FINDPRIMES_INPUT_H
#define FINDPRIMES_INPUT_H

#include "bits/stdc++.h"

void argInput(const long long &n, const char &m);

void usrInput();

void halfInput(const long long &n);

void halfInput(const char &m);

inline void askForMethod() {
    std::cout << "a stand for Trial Division" << std::endl;
    std::cout << "b stand for Sieve of Eratosthenes" << std::endl;
    std::cout << "c stand for Sieve of Euler" << std::endl;
    std::cout << "d stand for Sieve of Sundaram" << std::endl;
    std::cout << "e stand for Sieve of Atkin" << std::endl;
    std::cout << "f stand for Incremental Sieve" << std::endl;
    std::cout << "g stand for Wheel Sieve" << std::endl;
    std::cout << "Choose an algorithm: ";
}

inline void askForNumber(long long &n) {
    std::cout << "Enter a positive integer: ";
    if (!(std::cin >> n) || n <= 1) throw std::invalid_argument("Invalid input.");
}


#endif //FINDPRIMES_INPUT_H