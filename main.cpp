#include "main.h"

int main(int argc, char *argv[]) {
    if (argc == 3) {
        if (isNumeric(argv[1])) {
            long long n = std::stoll(argv[1]);
            char m = argv[2][0];
            if (n <= 1)
                throw std::invalid_argument("n must be greater than 1.");
            argInput(n, m);
        } else
            throw std::invalid_argument("Invalid input.");
    } else if (argc == 1) {
        usrInput();
        return 1;
    } else if (argc == 2) {
        if (argv[1][0] == '-' && argv[1][1] == 'h') {
            return printHelp();
        } else if (isNumeric(argv[1])) {
            long long n = std::stoll(argv[1]);
            halfInput(n);
        } else {
            switch (argv[1][0]) {
                case 'a':
                case 'b':
                case 'c':
                case 'd':
                case 'e':
                case 'f':
                case 'g':
                    halfInput(argv[1][0]);
                    break;
                default:
                    throw std::invalid_argument("Invalid input.");
            }
        }
    }
}