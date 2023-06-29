#include "primes.h"

std::vector<long long> trialDivision(long long n)
{
    std::vector <long long> primes; // 用来存储素数的结果集

    if (n >= 2) {
        primes.push_back(2); // 2 是素数，特别处理
    }

    for (long long i = 3; i <= n; i += 2) // 从3开始，只循环奇数
    {
        bool isPrime = true;
        for (long long j = 2; j * j <= i; j++) // 试除法判断i是否为素数
        {
            if (i % j == 0)
            {
                isPrime = false;
                break;
            }
        }

        if (isPrime) // 如果i是素数，将它加入结果集中
        {
            primes.push_back(i);
        }
    }

    return primes; // 返回结果集
}



std::vector<long long> eratosthenesSieve(long long n)
{
    std::vector<bool> isPrime(n + 1, true); // 创建一个大小为n+1的bool数组，初始化为true

    for (long long i = 2; i <= n * n; i++) // 从2循环到sqrt(n)
    {
        if (isPrime[i]) // 如果i是素数
        {
            for (long long j = i * i; j <= n; j += i) // 将i的倍数标记为false
            {
                isPrime[j] = false;
            }
        }
    }

    std::vector<long long> primes;          // 用来存储素数的结果集
    for (long long i = 2; i <= n; i++) // 将所有值为true的下标加入结果集中
    {
        if (isPrime[i])
        {
            primes.push_back(i);
        }
    }

    return primes; // 返回结果集
}

std::vector<long long> eulerSieve(long long n)
{
    std::vector<bool> isPrime(n + 1, true); // 创建一个大小为n+1的bool数组，初始化为true
    std::vector<long long> primes;          // 用来存储素数的结果集

    for (long long i = 2; i * i <= n; i++) // 从2循环到n
    {
        if (isPrime[i]) // 如果i是素数，将它加入结果集中 Q：这里是如何判断素数的？ A：如果i是素数，那么i的倍数一定不是素数，所以将i的倍数标记为false
        {
            primes.push_back(i);
        }

        for (int j = 0; j < primes.size() && i * primes[j] <= n; j++) // 遍历素数集合，将i*primes[j]标记为false
        {
            isPrime[i * primes[j]] = false;

            if (i % primes[j] == 0) // 如果i能够整除primes[j]，说明i*primes[j]已经被标记过了，退出循环
            {
                break;
            }
        }
    }
    return primes; // 返回结果集
}