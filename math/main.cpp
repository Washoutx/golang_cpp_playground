#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <set>
#include <vector>

constexpr uint64_t sumOfNumbersDivisibleBy3or5(uint32_t number)
{
    uint64_t sum{};
    for (uint32_t i = 3; i <= number; i++)
    {
        if (i % 3 == 0 || i % 5 == 0)
        {
            sum += i;
        }
    }
    return sum;
}

constexpr uint64_t gcd_greatestCommonDivisor(uint64_t a, uint64_t b)
{
    // GCD(a,b) = GCD(b, a%b)
    while (b != 0)
    {
        a %= b;
        std::swap(a, b);
    }

    return a;
}

constexpr uint64_t lcm_leastCommonMultiple(uint64_t a, uint64_t b)
{
    if (a == 0 || b == 0)
        return 0;

    // LCM(a,b) = a*b / GCD(a,b)
    // Use transformed formula to reduce the risk of integer overflow
    // LCM(a,b) = (a/GDC(a,b)) * b
    return (a / gcd_greatestCommonDivisor(a, b)) * b;
}

template <typename InputIt> constexpr uint64_t lcm_group(InputIt begin, InputIt end)
{
    return std::accumulate(begin, end, 1, lcm_leastCommonMultiple);
}

constexpr bool isPrime(uint64_t n)
{
    if (n <= 3)
        return n > 1;
    if (n % 2 == 0 || n % 3 == 0)
        return false;
    // algo 6k +- 1
    for (uint64_t i = 5; i * i < n; i += 6)
    {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}
constexpr uint64_t firstPrimeNumberBefore(uint64_t n)
{
    while (n != 0)
    {
        n--;
        if (isPrime(n))
            return n;
    }

    return n;
}

constexpr void printPrime6kNumbersUntil(uint64_t n)
{
    if (n < 11)
        std::cout << "no prime 6k\n";

    for (uint64_t i = 5; i <= n; i++)
    {
        if (isPrime(i) && isPrime(i + 6))
        {
            std::cout << "Prime6k{" << i << "," << i + 6 << "}" << std::endl;
        }
    }
    std::cout << std::endl;
}

uint64_t sumOfDivisors(uint64_t i)
{
    uint64_t sumOfDivisors{1};
    for (uint64_t j = 2; j <= std::sqrt(i); j++)
    {
        if (i % j == 0)
        {
            sumOfDivisors += (j == (i / j)) ? j : j + (i / j);
        }
    }
    return sumOfDivisors;
}

std::pair<uint64_t, uint64_t> makeOrderPair(uint64_t a, uint64_t b)
{
    if (a > b)
        return std::make_pair(b, a);
    return std::make_pair(a, b);
}

constexpr void calcAbundantNumbersUntil(uint64_t n)
{
    int counter = 1;
    for (uint64_t i = 10; i <= n; i++)
    {
        const auto sum = sumOfDivisors(i);
        if (sum > i)
        {
            std::cout << counter << " Abundant number(" << i << ") Abound=" << sum - i << std::endl;
            counter++;
        }
    }
}

void printAmicableUntil(uint64_t limit)
{
    std::set<std::pair<uint64_t, uint64_t>> friends;

    for (uint64_t i = 0; i < limit; i++)
    {
        const auto sum1 = sumOfDivisors(i);
        if (sum1 < limit)
        {
            const auto sum2 = sumOfDivisors(sum1);
            if (i == sum2 && i != sum1)
            {
                friends.insert(makeOrderPair(i, sum1));
            }
        }
    }

    std::cout << "Amount=" << friends.size() << std::endl;
    for (const auto i : friends)
    {
        std::cout << i.first << " and " << i.second << " are friends numbers" << std::endl;
    }
}

constexpr void checkIfArmstrongNum(uint64_t n)
{
    uint32_t digits{};
    uint64_t buffer = n;

    while (buffer > 0)
    {
        buffer /= 10;
        digits++;
    }

    buffer = n;
    uint64_t sum{};
    for (auto i = 0u; i < digits; i++)
    {
        uint64_t digit = buffer % 10;
        sum = std::pow(digit, digits);
        digit /= 10;
    }

    if (sum == n)
    {
        std::cout << n << " is Armstrong number\n";
    }
}

void printPrimeFactors(uint64_t n)
{
    std::vector<uint64_t> vec;
    while (n % 2 == 0)
    {
        vec.emplace_back(2);
        n /= 2;
    }

    for (int i = 3; i < std::sqrt(n); i += 2)
    {
        while (n % i == 0)
        {
            vec.emplace_back(i);
            n /= i;
        }
    }

    if (n > 2)
    {
        vec.emplace_back(n);
    }
    for (const auto &n : vec)
    {
        std::cout << n << std::endl;
    }
}

std::vector<bool> decToBin(uint64_t n)
{
    std::vector<bool> bin;

    if (n == 0)
    {
        return {0};
    }
    while (n > 0)
    {
        bin.emplace_back(n%2);
        n /= 2;
    }
    std::reverse(bin.begin(), bin.end());
    return bin;
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
    // printAmicableUntil(1000000);
    // printPrimeFactors(420);

    for (const auto &i : decToBin(504))
    {
        std::cout << i;
    }

    return 0;
}