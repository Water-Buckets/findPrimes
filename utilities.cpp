#include "main.h"


long long calcAndPrintDuration(const long long &n, const char &m, std::vector<long long> &primes) {
    auto start = std::chrono::steady_clock::now();
    calculatePrimes(n, m, primes);
    auto end = std::chrono::steady_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    long long duration = diff.count();
    std::clog << "Found " << primes.size() << " primes in " << double(duration) / 1000000000 << " seconds."
              << std::endl;
    return duration;
}


void calculatePrimes(const long long &n, const char &m, std::vector<long long> &primes) {
    switch (m) {
        case 'a':
            std::clog << "Using Trial Division" << std::endl;
            trialDivision(n, primes);
            break;
        case 'b':
            std::clog << "Using Sieve of Eratosthenes" << std::endl;
            eratosthenesSieve(n, primes);
            break;
        case 'c':
            std::clog << "Using Sieve of Euler" << std::endl;
            eulerSieve(n, primes);
            break;
        case 'd':
            std::clog << "Using Sieve of Sundaram" << std::endl;
            sundaramSieve(n, primes);
            break;
        case 'e':
            std::clog << "Using Sieve of Atkin" << std::endl;
            atkinSieve(n, primes);
            break;
        case 'f':
            std::clog << "Using Incremental Sieve" << std::endl;
            incrementalSieve(n, primes);
            break;
        case 'g':
            std::clog << "Using Wheel Sieve" << std::endl;
            wheelSieve(n, primes);
            break;
        default:
            throw std::invalid_argument("Invalid input.");
    }
}

long long outputToFile(const std::vector<long long> &primes, const long long &n) {

    auto startWrite = std::chrono::steady_clock::now();
    std::ofstream outfile("primes.txt");
    if (!outfile.is_open()) throw std::runtime_error("Failed to open file.");

    outfile << "Primes less than or equal to " << n << ": ";
    for (auto p: primes) {
        outfile << p << " ";
    }
    outfile.close();
    auto endWrite = std::chrono::steady_clock::now();
    auto diffWrite = std::chrono::duration_cast<std::chrono::nanoseconds>(endWrite - startWrite);
    long long durationWrite = diffWrite.count();
    std::clog << "Time elapsed writing to file: " << double(durationWrite) / 1000000000 << " seconds." << std::endl;
    return durationWrite;
}