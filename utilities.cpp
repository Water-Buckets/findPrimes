#include "utilities.h"
#include "primes.h"



std::pair<std::vector<long long>, long long> calcAndPrintDuration(long long n,char m){
        auto start = std::chrono::steady_clock::now();
        auto primes = calculatePrimes(n,m);
        auto end = std::chrono::steady_clock::now();
        auto diff = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        long long duration = diff.count();
        std::cout << "Found " << primes.size() << " primes in " << double(duration) / 1000000000 << " seconds." << std::endl;
        return std::make_pair(primes, duration);
}


std::vector<long long> calculatePrimes(long long n,char m){
    if (m == 'a'){
        std::cout << "Using Trial Division" << std::endl;
        return trialDivision(n);
    }
    else if (m == 'b'){
        std::cout << "Using Sieve of Eratosthenes" << std::endl;
        return eratosthenesSieve(n);
    }
    else if (m == 'c'){
        std::cout << "Using Sieve of Euler" << std::endl;
        return eulerSieve(n);
    }
    else {
        std::cout << "Invalid input." << std::endl;
        std::exit(1);
    }
}




void printTotalDuration(long long duration, long long durationWrite){
    std::cout << "Total time elapsed: " << double(duration + durationWrite) / 1000000000 << " seconds." << std::endl;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-use-anyofallof"
bool isNumeric(const std::string& str){
    for (char c : str){
        if (!std::isdigit(c))
        return false;
    }
    return true;
}
#pragma clang diagnostic pop


long long outputToFile(const std::vector<long long>& primes, long long n){

    auto startWrite = std::chrono::steady_clock::now();
    std::ofstream outfile("primes.txt");
    if (!outfile.is_open()){
        std::cout << "Failed to open file." << std::endl;
        return 1;
    }

    outfile << "Primes less than or equal to " << n << ": ";
    for (auto p : primes){
        outfile << p << " ";
    }
    outfile.close();
    auto endWrite = std::chrono::steady_clock::now();
    auto diffWrite = std::chrono::duration_cast<std::chrono::nanoseconds>(endWrite - startWrite);
    long long durationWrite = diffWrite.count();
    std::cout << "Time elapsed writing to file: " << double(durationWrite) / 1000000000 << " seconds." << std::endl;
    return durationWrite;
}