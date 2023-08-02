#include "includes/main.h"

int main(int argc, char *argv[]) {
#ifndef NDEBUG
  std::cerr << __func__ << ": " << argc << std::endl;
  for (int i = 0; i != argc; ++i) {
    std::cerr << __func__ << ": " << argv[i] << std::endl;
  }
#endif
  switch (argc) {
  case 1:
    // Print help when no arguments are given
    printHelp();
    break;
  case 5:
    // When 4 arguments are given, start the program
    argInput(argv);
    break;
  default:
    throw std::invalid_argument("Invalid input.");
    // Throw an exception when the number of arguments is invalid
  }
}