//
// Created by ASUS on 2023/7/7.
//
#include "includes/argInput.h"

void argInput(char *argv[]) {
  try {
#ifndef NDEBUG
    std::cerr << __func__ << std::endl;
#endif

    // check if input is valid
    if (!isNumeric(argv[1]) || !isNumeric(argv[3]) || argv[2][1])
      throw std::invalid_argument("Invalid input.");

    // define required variables
    int threads = std::stoi(argv[1]);
    char m = argv[2][0];
    long long n = std::stoll(argv[3]);
    std::string file = argv[4];

    // check if input is valid
    if (n <= 1)
      throw std::invalid_argument("n must be greater than 1.");

#ifndef NDEBUG
    std::cerr << __func__ << ": " << threads << " " << m << " " << n << " "
              << file << std::endl;
#endif

      void (*pPreSieveMethod)(const long long &n,
                              std::vector<long long> &primes);
      pPreSieveMethod = switchSMethods(m);

#ifndef NDEBUG
      std::cerr << "pPreSieveMethod: " << &pPreSieveMethod << std::endl;
#endif

      void (*pMMethod)(const long long &lL, const long long &uL,
                       std::vector<long long> &primes,
                       const std::vector<long long> &preSievedPrimes);
      pMMethod = switchMMethods(m);

#ifndef NDEBUG
      std::cerr << "pMMethod: " << &pMMethod << std::endl;
#endif

      multiThread(threads, n, file, pMMethod, pPreSieveMethod);
  } catch (std::invalid_argument &e) {
    std::cerr << e.what() << std::endl;
    std::exit(0);
  } catch (std::runtime_error &e) {
    std::cerr << e.what() << std::endl;
    std::cerr
        << "Please submit you issues here: "
           "https://github.com/Water-Buckets/findPrimes/issues"
        << std::endl;
    std::exit(0);
  }
}