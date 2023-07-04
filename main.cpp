#include "main.h"

int main(int argc, char *argv[]) {
  if (argc == 3) {
    if (isNumeric(argv[1])) {
      long long n = std::stoll(argv[1]);
      char m = argv[2][0];
      if (n <= 1) throw std::invalid_argument("n must be greater than 1.");
      argInput(n, m);
    } else throw std::invalid_argument("Invalid input.");
  } else if (argc == 1){
    usrInput();
    return 1;
  }
  else if (argc == 2 &&
           (argv[1][0] == '-' && argv[1][1] == 'h')) {
    std::cout << "Usage: findprimes [n] [m]" << std::endl;
    std::cout << "Help findPrimes -help" << std::endl;
    std::cout << "(if you're using Windows than replace findprimes with "
                 "findprimes.exe)"
              << std::endl;
    std::cout << "n: a positive integer" << std::endl;
    std::cout << "m: a character in {a, b, c}" << std::endl;
    std::cout << "a: Trial Division" << std::endl;
    std::cout << "b: Sieve of Eratosthenes" << std::endl;
    std::cout << "c: Sieve of Euler" << std::endl;
    std::cout << "If no arguments are provided, the program will prompt the "
                 "user for input."
              << std::endl;
    std::cout << "If both n and m are provided, the program will use the "
                 "provided values."
              << std::endl;
    std::cout << "If the provided values are invalid, the program will exit "
                 "with an error."
              << std::endl;
    std::cout << "If the provided values are valid, the program will output "
                 "the results to 'primes.txt'."
              << std::endl;
    std::cout << "If the file already exists, the program will overwrite it."
              << std::endl;
    std::cout << "If the file does not exist, the program will create it."
              << std::endl;
    std::cout << "If the program is run with the -h flag, the program will "
                 "output this message."
              << std::endl;
    return 0;
  } else throw std::invalid_argument("Invalid input.");
}