#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>
#include <string>

template <typename Container>
std::string join_strings(const Container& c, const char* const separator)
{
    std::ostringstream os;
    std::copy(std::begin(c), std::end(c)-1, std::ostream_iterator<std::string>(os, separator));
    os << *(std::end(c)-1);
    return os.str();
}

int main()
{
    std::cout << join_strings(std::vector<std::string>{"one", "two", "three"}, ":elo:");
    return 0;
}