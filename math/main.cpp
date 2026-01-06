#include <cmath>
#include <iostream>
#include <cstdint>
#include <numeric>
#include <array>

constexpr uint64_t sumOfNumbersDivisibleBy3or5(uint32_t number)
{
    uint64_t sum{};
    for(uint32_t i = 3; i <= number; i++)
    {
        if(i % 3 == 0 || i % 5 == 0)
        {
            sum += i;
        }
    }
    return sum;
}

constexpr uint64_t gcd_greatestCommonDivisor(uint64_t a, uint64_t b)
{
    // GCD(a,b) = GCD(b, a%b)
    while(b != 0)
    {
        a %= b;
        std::swap(a, b);
    }

    return a;
}

constexpr uint64_t lcm_leastCommonMultiple(uint64_t a, uint64_t b)
{
    if(a == 0 || b == 0) return 0;

    // LCM(a,b) = a*b / GCD(a,b)
    // Use transformed formula to reduce the risk of integer overflow
    // LCM(a,b) = (a/GDC(a,b)) * b 
    return (a / gcd_greatestCommonDivisor(a, b)) * b;
}

template <typename InputIt>
constexpr uint64_t lcm_group(InputIt begin, InputIt end)
{
    return std::accumulate(begin, end, 1, lcm_leastCommonMultiple);
}

constexpr bool isPrime(uint64_t n)
{
    if(n <= 3) return n>1;
    if(n % 2 == 0 || n % 3 == 0) return false;
    // algo 6k +- 1
    for(uint64_t i = 5; i*i < n; i+=6)
    {
        if(n % i == 0 || n % (i+2) == 0) return false;
    }
    return true;
}
constexpr uint64_t firstPrimeNumberBefore(uint64_t n)
{
    while(n != 0)
    {
        n--; 
        if(isPrime(n)) return n;
    }

    return n;
}

void printPrime6kNumbersUntil(uint64_t n)
{
    if (n < 11) std::cout << "no prime 6k\n";

    for(uint64_t i = 5; i <= n; i++)
    {
        if(isPrime(i) && isPrime(i+6))
        {
            std::cout << "Prime6k{" << i << "," << i+6 << "}" << std::endl;
        }
    }
    std::cout << std::endl;
}

void calcAbundantNumbersUntil(uint64_t n)
{
    int counter = 1;
    for(uint64_t i = 10; i <= n; i++)
    {
        uint64_t sumOfDivisors{1};
        for(uint64_t j = 2; j <= std::sqrt(i); j++)
        {
            if(i % j == 0)
            {
                sumOfDivisors += (j == (i/j)) ? j : j + (i/j);
            }
        }
        if (sumOfDivisors > i)
        {
            std::cout << counter << " Abundant number(" << i << ") Abound=" << sumOfDivisors-i << std::endl;
            counter++;
        }
    }
}

int main()
{
    // std::cout << sumOfNumbersDivisibleBy3or5(15) << std::endl;
    // std::cout << gcd_greatestCommonDivisor(48, 12) << std::endl;
    // std::cout << lcm_leastCommonMultiple(48, 12) << std::endl;
    // std::array<int, 3> arr {48,5,12};
    // std::cout << lcm_group(arr.begin(), arr.end() ) << std::endl;
    // std::cout << firstPrimeNumberBefore(7) << std::endl;
    // firstPrimeNumberBefore(100);
    // printPrime6kNumbersUntil(100);
    // calcAbundantNumbersUntil(200);
    
    return 0;
}