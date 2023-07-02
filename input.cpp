#include "input.h"
#include "primes.h"
#include "utilities.h"

int argInput(long long n, char m) {
    auto result = calcAndPrintDuration(n, m);
    std::vector<long long> primes = result.first;
    long long duration = result.second;
    long long durationWrite = outputToFile(primes, n);
    printTotalDuration(duration, durationWrite);
    std::cout << "Done. Check 'primes.txt' for " << primes.size() << " results."<< std::endl; // 输出提示信息
    return 0;
}

int usrInput() {
    long long n;
    char m;
    while (true) {
        std::cout << "Enter a positive integer: ";
        if (!(std::cin >> n) || n <= 1) {
            std::cout << "Invalid input." << std::endl;
            return 1;
        }
        std::cout << "Choose an algorithm: ";
        std::cout << "a stand for Trial Division" << std::endl;
        std::cout << "b stand for Sieve of Eratosthenes" << std::endl;
        std::cout << "c stand for Sieve of Euler" << std::endl;
        std::cout << "d stand for Sieve of Sundaram" << std::endl;
        std::cout << "e stand for Sieve of Atkin" << std::endl;
        std::cout << "f stand for Incremental Sieve" << std::endl;
        std::cout << "g stand for Wheel Sieve" << std::endl;
        if (!(std::cin >> m)) {
            std::cout << "Invalid input." << std::endl;
            return 1;
        } else argInput(n, m);
    }
}