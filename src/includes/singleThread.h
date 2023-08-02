//
// Created by ASUS on 2023/7/10.
//

#ifndef FINDPRIMES_MULTITHREAD_SINGLETHREAD_H
#define FINDPRIMES_MULTITHREAD_SINGLETHREAD_H

#include "utilities.h"
#include <fstream>
#include <vector>

// main part of the singleThread function
inline std::vector<long long> singleThreadSieve(
    const long long &n,
    void (*pSMethod)(const long long &n, std::vector<long long> &primes)) {

#ifndef NDEBUG
  std::cerr << __func__ << std::endl;
#endif

  // define primes vector to store primes
  std::vector<long long> primes;
  // call pSMethod based on the pointer
  (*pSMethod)(n, primes);

#ifndef NDEBUG
  std::cerr << __func__ << ": " << *primes.begin() << " " << *--primes.end()
            << std::endl;
#endif

  return primes;
}

// Writing to file in singleThread mode
inline int writeToFileST(std::vector<long long> primes,
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
  if (!outfile.is_open()) {
    throw std::runtime_error("Failed to open file.");
  }

  // write to file
  for (auto p : primes) {
    outfile << p << " ";
  }

  // close file
  outfile.close();
  return 0;
}

// main function of singleThread mode
void singleThread(const long long &n, const std::string &file,
                  void (*pSMethod)(const long long &n,
                                   std::vector<long long> &primes));

#endif // FINDPRIMES_MULTITHREAD_SINGLETHREAD_H
