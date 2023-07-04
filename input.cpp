#include "main.h"

void argInput(const long long &n, char &m) {
    std::vector<long long> primes;
    long long duration = calcAndPrintDuration(n, m, primes);
    long long durationWrite = outputToFile(primes, n);
    std::clog << "Total time elapsed: " << double(duration + durationWrite) / 1000000000 << " seconds." << std::endl;
    std::clog << "Done. Check 'primes.txt' for " << primes.size() << " results."<< std::endl; // 输出提示信息
}
 void usrInput() {
    long long n;
    char m;
    while (true) {
        std::cout << "Enter a positive integer: ";
        if (!(std::cin >> n) || n <= 1) throw std::invalid_argument("Invalid input.");

        std::cout << "a stand for Trial Division" << std::endl;
        std::cout << "b stand for Sieve of Eratosthenes" << std::endl;
        std::cout << "c stand for Sieve of Euler" << std::endl;
        std::cout << "d stand for Sieve of Sundaram" << std::endl;
        std::cout << "e stand for Sieve of Atkin" << std::endl;
        std::cout << "f stand for Incremental Sieve" << std::endl;
        std::cout << "g stand for Wheel Sieve" << std::endl;
        std::cout << "Choose an algorithm: ";
        if (!(std::cin >> m)) throw std::invalid_argument("Invalid input.");
        else argInput(n, m);
    }
}