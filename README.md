# findPrimes
This is a program designed to find all the prime numbers between 2 and a given number.

# Usage: 
findprimes [threads] [method] [n] [outputFile]

You can tell the program to use multiple threads by providing a number for threads.
If the number of threads is invalid, the program will exit with an error.

You can tell the program to use a specific method by providing a character for method.
For methods you can choose between 'a' 'b' 'c' 'd' 'e' 'f'.

a stand for Trial Division.

b stand for Sieve of Eratosthenes.

c stand for Sieve of Euler.

d stand for Sieve of Sundaram.

e stand for Incremental Sieve.

When using multiThread mode Sieve of Atkin and Wheel Sieve aren't supported.

n stand for the upper limit of the primes you want to find.

outputFile is the file that you want the primes to be output.

If no arguments are provided, the program will show this help.

# Build
Requires cmake.
````bash
git clone https://github.com/Water-Buckets/findPrimes.git && cd findPrimes
cmake -S . -B ./cmake-build && cmake --build ./cmake-build
````

# Run
Example:
````bash
findPrimes 32 c 2147483648 primes.txt
````
