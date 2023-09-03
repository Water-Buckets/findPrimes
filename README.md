# findPrimes

This is a program designed to find all the prime numbers between 2 and a given number.

# Usage:

findprimes [threads] [method] [n] [outputFile]

You can tell the program to use multiple threads by providing a number for threads.
If the number of threads is invalid, the program will exit with an error.

You can tell the program to use a specific method by providing a character for method.
For methods you can choose between '0' '1' '2' '3' '4'.

0 stand for Trial Division.

1 stand for Sieve of Eratosthenes.

2 stand for Sieve of Euler.

3 stand for Sieve of Sundaram.

4 stand for Incremental Sieve.

n stand for the upper limit of the primes you want to find.

outputFile is the file that you want the primes to be output.

# Build

Requires cmake.

````bash
git clone https://github.com/Water-Buckets/findPrimes.git && cd findPrimes
cmake -S . -B ./cmake-build && cmake --build ./cmake-build
````

# Run

Example:

````bash
findPrimes 32 1 2147483648 primes.txt
````
