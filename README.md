# findPrimes_multiThread
This is a program designed to find all the prime numbers between 2 and a given number.

# Usage: 
findprimes [threads] [method] [n] [outputFile]

If threads equals 1 the program will run in singleThread mode.
Else if threads is over 1 the program will run in multiThread mode.
You can tell the program to use multiple threads by providing a number for threads.
If the number of threads is invalid, the program will exit with an error.

You can tell the program to use a specific method by providing a character for method.
For method you can choose between 'a' 'b' 'c' 'd' 'e' 'f' 'g'.

a stand for Trial Division.

b stand for Sieve of Eratosthenes.

c stand for Sieve of Euler.

d stand for Sieve of Sundaram.

e stand for Sieve of Atkin.

f stand for Incremental Sieve.

g stand for Wheel Sieve.

When using multiThread mode Sieve of Atkin and Wheel Sieve aren't supported.

n stand for the upper limit of the primes you want to find.

outputFile is the file that you want the primes to be output.

If no arguments are provided, the program will show this help.

# Build
Requires cmake.
````bash
git clone https://github.com/Water-Buckets/findPrimes_multiThread.git && cd findPrimes_multiThread
cmake -S . -B ./cmake-build && cmake --build ./cmake-build
````
