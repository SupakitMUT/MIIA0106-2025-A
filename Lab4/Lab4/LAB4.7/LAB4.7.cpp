// LAB4.7.cpp : Prime-checking function and interactive tester.
// Compiles with C++14.

#include <iostream>
#include <cmath>

bool isPrime(long long n)
{
    if (n <= 1) return false;        // 0, 1 and negatives are not prime
    if (n <= 3) return true;         // 2 and 3 are prime
    if (n % 2 == 0) return false;    // even numbers >2 are not prime

    long long limit = static_cast<long long>(std::sqrt(static_cast<long double>(n)));
    for (long long i = 3; i <= limit; i += 2)
    {
        if (n % i == 0) return false;
    }
    return true;
}

int main()
{
    std::cout << "Prime checker\n";
    std::cout << "Enter integers to test (press Ctrl+Z then Enter to exit on Windows):\n";

    long long value;
    while (std::cout << "Number: " && (std::cin >> value))
    {
        if (isPrime(value))
            std::cout << value << " is prime.\n";
        else
            std::cout << value << " is not prime.\n";
    }

    std::cout << "Exiting.\n";
    return 0;
}
