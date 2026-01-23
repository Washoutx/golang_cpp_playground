#include <functional>
#include <iostream>

template <class Comparator, class T> T minimum(Comparator comp, T a, T b)
{
    return comp(a, b) ? a : b;
}

template <class Comparator, class T1, class... T> T1 minimum(Comparator comp, T1 a, T... args)
{
    return minimum(comp, a, minimum(comp, args...));
}

int main()
{
    std::cout << minimum(std::less<>(), 3, 2, 1);
    return 0;
}