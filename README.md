# findPrimes

## Description

This is a program that calculates all the prime numbers between 2 and a given number. It supports three different algorithms for prime number computation: Trial Division, Sieve of Eratosthenes, and Sieve of Euler. The program includes error handling mechanisms to ensure correct user input, and it provides performance measures for each run.

## Usage

The program can be executed through the command line with the following command:

```
cmake .. && make && ./findPrimes
```

The user will be prompted to input a positive integer, `n`, which is the upper limit for prime number computation. They will also be asked to choose an algorithm for the computation, represented by the characters 'a' (Trial Division), 'b' (Sieve of Eratosthenes), or 'c' (Sieve of Euler).

## Output

The program outputs all prime numbers between 2 and `n` to a file named primes.txt. It also displays the total number of primes found and the time taken for computation and file writing.

## Warning

If `n` is too large, primes.txt may be too large to open in a text editor and take up a lot of space on your computer. 

## Dependencies

The program utilizes the <bits/stdc++.h> library which requires the compiler's support.

# TODO

1. **Performance Optimization**: Investigate potential optimizations for each prime calculation algorithm. This could include parallel computing techniques or using more efficient data structures.

2. **Error Handling**: Enhance error handling for exceptional scenarios, such as insufficient disk space for the output file or extremely large input numbers.

3. **Extend Functionality**: Consider extending the functionality of the program, such as allowing users to specify a range of numbers for prime calculation instead of starting from 2.

4. **Testing**: Write comprehensive tests to ensure that all aspects of the program work as expected, especially as optimizations and new features are added.
