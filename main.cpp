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
    else
    {
        std::cout << "Invalid input." << std::endl;
        return 1;
    }
}