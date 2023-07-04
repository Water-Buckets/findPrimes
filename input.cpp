#include "main.h"

void argInput(const long long &n, const char &m) {
    std::vector<long long> primes;
    long long duration = calcAndPrintDuration(n, m, primes);
    long long durationWrite = outputToFile(primes, n);
    std::cout << "Total time elapsed: " << double(duration + durationWrite) / 1000000000 << " seconds." << std::endl;
    std::cout << "Done. Check 'primes.txt' for " << primes.size() << " results." << std::endl;
}

void halfInput(long long &n) {
    char m;
    askForMethod();
    if (!(std::cin >> m)) throw std::invalid_argument("Invalid input.");
    argInput(n, m);
}

void halfInput(const char &m) {
    long long n;
    askForNumber(n);
    argInput(n, m);

}

void usrInput() {
    long long n;
    char m;
    while (true) {
        askForNumber(n);
        askForMethod();
        if (!(std::cin >> m)) throw std::invalid_argument("Invalid input.");
        else argInput(n, m);
    }
}