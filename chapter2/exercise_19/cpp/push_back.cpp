#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

template <class Container, class T>
concept PushBackable = requires(Container c, T value) {
    { c.push_back(value) };
};

template <class Container, class... T>
    requires(PushBackable<Container, T> && ...)
void push_back(Container &c, T... args)
{
    (c.push_back(args), ...);
}

int main()
{
    std::vector<int> vec;
    push_back(vec, 3, 2, 1);

    std::copy(std::begin(vec), std::end(vec), std::ostream_iterator<int>(std::cout, ","));
    return 0;
}