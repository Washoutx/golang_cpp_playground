#include <cassert>
#include <utility>
#include <vector>

template <class Container, class T> bool contains(const Container &c, const T &elem)
{
    return c.end() != std::ranges::find(c, elem);
}

template <class Container, class... T> bool contains_any(const Container &c, const T &&...elems)
{
    return (... || contains(c, elems));
}

template <class Container, class... T> bool contains_all(const Container &c, const T &&...elems)
{
    return (... && contains(c, elems));
}

template <class Container, class... T> bool contains_none(const Container &c, const T &&...elems)
{
    return !contains_any(c, std::forward<const T>(elems)...);
}

int main()
{
    std::vector<int> vec{1, 2, 33, 4, 5};
    assert(contains_any(vec, 9, 9, 1));
    assert(contains_all(vec, 1, 2, 33, 4, 5));
    assert(contains_none(vec, 9, 9, 9, 9));

    return 0;
}