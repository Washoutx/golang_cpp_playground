#include <array>
#include <cassert>
#include <cstdint>
#include <iomanip>
#include <ios>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <sys/types.h>
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

std::vector<uint8_t> str_to_hex(const std::string &str)
{
    auto ch_conv = [](char c) -> int
    {
        if (c >= '0' && c <= '9')
            return c - '0';
        else if (c >= 'a' && c <= 'f')
            return c - 'a' + 10;
        else if (c >= 'A' && c <= 'F')
            return c - 'A' + 10;
        return 0;
    };

    std::vector<uint8_t> v{};
    v.reserve(str.size() / 2);
    for (size_t i = 0; i < str.size(); i += 2)
    {
        uint8_t hi = str[i];
        uint8_t lo = str[i + 1];

        uint8_t result = (ch_conv(hi) << 4 | ch_conv(lo));
        v.push_back(result);
    }

    return v;
}

int main()
{
    std::vector<uint8_t> v{0xBA, 0xAD, 0xF0, 0x0D};
    std::array<uint8_t, 6> a{{1, 2, 3, 4, 5, 6}};

    uint8_t buf[5] = {0x11, 0x22, 0x33, 0x44, 0x55};
    assert(to_hex_str(v, true) == "BAADF00D");
    assert(to_hex_str(a, true) == "010203040506");
    assert(to_hex_str(buf, true) == "1122334455");

    assert(to_hex_str(v) == "baadf00d");
    assert(to_hex_str(a) == "010203040506");
    assert(to_hex_str(buf) == "1122334455");

    for (const auto &obj : str_to_hex("DEADBEEF"))
    {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(obj) << " ";
    }
    return 0;
}
