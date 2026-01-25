#include <array>
#include <cassert>
#include <iomanip>
#include <ios>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

template <typename Iter> std::string to_hex_str(Iter begin, Iter end, bool isUpperCase = false)
{
    std::ostringstream os;
    if (isUpperCase)
    {
        os.setf(std::ios_base::uppercase);
    }

    for (auto it = begin; it < end; ++it)
    {
        os << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(*it);
    }

    return os.str();
}

template <typename C> std::string to_hex_str(const C &container, bool isUpperCase = false)
{
    return to_hex_str(std::cbegin(container), std::cend(container), isUpperCase);
}

int main()
{
    std::vector<unsigned char> v{0xBA, 0xAD, 0xF0, 0x0D};
    std::array<unsigned char, 6> a{{1, 2, 3, 4, 5, 6}};

    unsigned char buf[5] = {0x11, 0x22, 0x33, 0x44, 0x55};
    assert(to_hex_str(v, true) == "BAADF00D");
    assert(to_hex_str(a, true) == "010203040506");
    assert(to_hex_str(buf, true) == "1122334455");

    assert(to_hex_str(v) == "baadf00d");
    assert(to_hex_str(a) == "010203040506");
    assert(to_hex_str(buf) == "1122334455");
    return 0;
}
