//
// Created by ASUS on 2023/7/7.
//
#include "includes/multiThread.h"

void multiThread(
    const int &threads, const long long &n, const std::string &file,
    void (*pMMethod)(const long long &lL, const long long &uL,
                     std::vector<long long> &primes,
                     const std::vector<long long> &preSievedPrimes),
    void (*pPreSieveMethod)(const long long &n,
                            std::vector<long long> &primes)) {

#ifndef NDEBUG
  std::cerr << __func__ << std::endl;
#endif

  // check if the input is valid
  if (pMMethod == nullptr || pPreSieveMethod == nullptr)
    throw std::runtime_error("Null pointer exception.");

  auto preSieveResults =
      timer(preSieve, "Time elapsed pre-sieving: ", n, pPreSieveMethod);

  long long sqrtN = preSieveResults.first.first;
  auto preSievedPrimes = preSieveResults.first.second;
  auto durationPre = preSieveResults.second;

  auto sieveResults = timer(multiThreadSieve, "Time elapsed sieving: ", n,
                            sqrtN, threads, preSievedPrimes, pMMethod);

  auto primesMat = sieveResults.first;
  auto duration = sieveResults.second;
  auto writeResults =
      timer(writeToFileMT, "Time elapsed writing to file: ", preSievedPrimes,
            primesMat, file);
  auto totalSize = writeResults.first;
  auto durationWrite = writeResults.second;

  // output total time elapsed
  std::cout << "Total time elapsed: "
            << double(durationPre + duration + durationWrite) / 1000000000
            << " seconds." << std::endl;

  // output file and result size
  std::cout << "Done. Check " << file << " for " << totalSize << " results."
            << std::endl;
}