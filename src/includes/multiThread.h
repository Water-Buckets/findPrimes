//
// Created by ASUS on 2023/7/7.
//

#ifndef FINDPRIMES_MULTITHREAD_MULTITHREAD_H
#define FINDPRIMES_MULTITHREAD_MULTITHREAD_H

#include "utilities.h"
#include <cmath>
#include <fstream>
#include <thread>
#include <vector>

// Pre sieving in multiThread mode
inline auto preSieve(const long long &n,
                     void (*pPreSieveMethod)(const long long &n,
                                             std::vector<long long> &primes)) {

#ifndef NDEBUG
  std::cerr << __func__ << std::endl;
#endif

  // calculate sqrt(n)
  long long sqrtN = std::sqrt(n);

  // define preSievedPrimes vector to store pre-sieved primes
  std::vector<long long> preSievedPrimes;

  // call preSieveMethod based on the pointer
  (*pPreSieveMethod)(sqrtN, preSievedPrimes);

#ifndef NDEBUG
  std::cerr << __func__ << ": " << sqrtN << std::endl;
  std::cerr << __func__ << ": " << *preSievedPrimes.begin() << " "
            << *--preSievedPrimes.end() << std::endl;
#endif

  return std::make_pair(sqrtN, preSievedPrimes);
}

// the main part of multiThread function
inline std::vector<std::vector<long long>> multiThreadSieve(
    const long long &n, const long long &sqrtN, const int &threads,
    std::vector<long long> preSievedPrimes,
    void (*pMMethod)(const long long &lL, const long long &uL,
                     std::vector<long long> &primes,
                     const std::vector<long long> &preSievedPrimes)) {

#ifndef NDEBUG
  std::cerr << __func__ << std::endl;
#endif

  // range per thread
  long long perThread = (n - sqrtN) / threads;

  // define threads vector to store threads
  std::vector<std::thread> vThread;

  // define primesVec vector to store primes
  std::vector<std::vector<long long>> primesMat(threads);

  // check if preSievedPrimes is empty
  if (preSievedPrimes.empty())
    throw std::runtime_error("Empty preSievedPrimes!");

#ifndef NDEBUG
  std::cerr << __func__ << ": " << perThread << std::endl;
#endif

  // start threads
  for (int i = 0; i < threads; ++i) {

    // calculate lower and upper limit
    long long lL = sqrtN + i * perThread + 1;
    long long uL = sqrtN + (i + 1) * perThread;

    // the upper limit of the last thread should be n
    if (i == threads - 1)
      uL = n;

#ifndef NDEBUG
    std::cerr << __func__ << ": " << i << ": " << lL << " " << uL << std::endl;
#endif

    // start thread and call pMultiMethod to sieve
    std::thread thr((*pMMethod), lL, uL, std::ref(primesMat[i]),
                    std::cref(preSievedPrimes));

    // add thread to vThread
    vThread.emplace_back(std::move(thr));
  }

  // join threads
  for (auto &thr : vThread)
    if (thr.joinable())
      thr.join();

#ifndef NDEBUG
  for (auto &vec : primesMat) {
    std::cerr << __func__ << ": ";
    std::cerr << *vec.begin() << " " << *--vec.end() << std::endl;
  }
#endif

  return primesMat;
}

// Writing to file in multiThread mode
inline long long
writeToFileMT(const std::vector<long long> &preSievedPrimes,
              const std::vector<std::vector<long long>> &primesVec,
              const std::string &file) {

#ifndef NDEBUG
  std::cerr << __func__ << std::endl;
#endif

  // open file
  std::ofstream outfile(file);

#ifndef NDEBUG
  std::cerr << __func__ << ": " << outfile.is_open() << std::endl;
#endif

  // check if file is open
  if (!outfile.is_open())
    throw std::runtime_error("Failed to open file.");

  // output preSievedPrimes
  for (long long i : preSievedPrimes)
    outfile << i << " ";

  // output primesVec
  long long totalSize = preSievedPrimes.size();
  for (auto &vec : primesVec) {
    for (long long i : vec)
      outfile << i << " ";
    totalSize += vec.size();
  }

  // close file
  outfile.close();
  return totalSize;
}

// main function of multiThread mode
void multiThread(
    const int &threads, const long long &n, const std::string &file,
    void (*pMMethod)(const long long &lL, const long long &uL,
                     std::vector<long long> &primes,
                     const std::vector<long long> &preSievedPrimes),
    void (*pPreSieveMethod)(const long long &n,
                            std::vector<long long> &primes));

#endif // FINDPRIMES_MULTITHREAD_MULTITHREAD_H
