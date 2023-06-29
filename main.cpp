#include "utilities.h"
#include "input.h"
#include "primes.h"


int main(int argc, char* argv[])
{
    if (argc == 3)
    {
        if (isNumeric(argv[1]))
        {
            long long n = std::stoll(argv[1]);
            char m = argv[2][0];
            if (n <= 1 || !(m=='a'|| m == 'b' || m == 'c'))
            {
                std::cout << "Invalid input." << std::endl;
                return 1;
            }
            argInput(n,m);
        }
        else
        {
            std::cout << "Invalid input." << std::endl;
            return 1;
        }
    }
    else if (argc == 1)
    {
        usrInput();
    }
    else if (argc ==2 && (argv[1][0] == '-' && argv[1][1] == 'h' && argv[1][2] == 'e' && argv[1][3] == 'l' && argv[1][4] == 'p')){ //any simplified version of this line? I tried using strcmp but it didn't work
        std::cout << "Usage: findprimes [n] [m]" << std::endl;
        std::cout << "n: a positive integer" << std::endl;
        std::cout << "m: a character in {a, b, c}" << std::endl;
        std::cout << "a: Trial Division" << std::endl;
        std::cout << "b: Sieve of Eratosthenes" << std::endl;
        std::cout << "c: Sieve of Euler" << std::endl;
        std::cout << "If no arguments are provided, the program will prompt the user for input." << std::endl;
        std::cout << "If both n and m are provided, the program will use the provided values." << std::endl;
        std::cout << "If the provided values are invalid, the program will exit with an error." << std::endl;
        std::cout << "If the provided values are valid, the program will output the results to 'primes.txt'." << std::endl;
        std::cout << "If the file already exists, the program will overwrite it." << std::endl;
        std::cout << "If the file does not exist, the program will create it." << std::endl;
        std::cout << "If the program is run with the -help flag, the program will output this message." << std::endl;
        return 0;
    }
    else
    {
        std::cout << "Invalid input." << std::endl;
        return 1;
    }
}