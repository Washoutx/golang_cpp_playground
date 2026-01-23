
#include <algorithm>
#include <array>
#include <bit>
#include <charconv>
#include <codecvt>
#include <cstdint>
#include <ios>
#include <iostream>
#include <istream>
#include <ranges>
#include <string_view>
#include <sys/types.h>

class IP_V4
{
    using OCTET = std::uint8_t;
    using IP = std::array<OCTET, 4>;

  public:
    constexpr IP_V4() noexcept = default;
    explicit constexpr IP_V4(OCTET a, OCTET b, OCTET c, OCTET d) noexcept : ip{a, b, c, d} {};
    // explicit constexpr IP_V4(uint32_t a)
    //     : ip{
    //           static_cast<OCTET>(a >> 24 & 0xFF),
    //           static_cast<OCTET>(a >> 16 & 0xFF),
    //           static_cast<OCTET>(a >> 8 & 0xFF),
    //           static_cast<OCTET>(a & 0xFF),
    //       }
    // {}
    // Modern solution but tricky because std::array has size under the hood
    explicit constexpr IP_V4(std::uint32_t a) { ip = std::bit_cast<IP>(std::byteswap(a)); };
    // std::uint32_t to_uint32_t() const
    // {
    //     std::uint32_t ip_int = static_cast<uint32_t>(ip[0] << 24) |
    //                            static_cast<uint32_t>(ip[1] << 16) |
    //                            static_cast<uint32_t>(ip[2] << 8) | static_cast<uint32_t>(ip[3]);
    //     return ip_int;
    // }
    // Moden solution swap to little endian interpretation
    std::uint32_t to_uint32_t() const
    {
        std::uint32_t s = std::byteswap(std::bit_cast<std::uint32_t>(ip));
        std::cout << std::endl << s << std::endl;
        return s;
    }
    friend std::ostream &operator<<(std::ostream &s, const IP_V4 &ip)
    {
        s << static_cast<int>(ip.ip[0]) << '.' << static_cast<int>(ip.ip[1]) << '.'
          << static_cast<int>(ip.ip[2]) << '.' << static_cast<int>(ip.ip[3]);
        return s;
    }
    friend std::istream &operator>>(std::istream &s, IP_V4 &ip)
    {
        int octet1{}, octet2{}, octet3{}, octet4{};
        char d1{}, d2{}, d3{};
        s >> octet1 >> d1 >> octet2 >> d2 >> octet3 >> d3 >> octet4;

        if (d1 != '.' || d2 != '.' || d3 != '.' || octet1 < 0 || octet1 > 255 || octet2 < 0 ||
            octet2 > 255 || octet3 < 0 || octet3 > 255 || octet4 < 0 || octet4 > 255)
        {
            s.setstate(std::ios_base::failbit);
            return s;
        }

        ip = IP_V4(octet1, octet2, octet3, octet4);
        return s;
    }
    bool parseIP(std::string_view str)
    {
        auto octets = str | std::views::split('.');
        int octet_counter{};
        for (const auto &octet : octets)
        {
            if (octet_counter > 4)
            {
                return false;
            }
            std::string_view sv(octet.begin(), octet.end());
            int octet_dec{};
            auto [ptr, err] = std::from_chars(sv.data(), sv.data() + sv.size(), octet_dec);
            if (err != std::errc{} || ptr != (sv.data() + sv.size()) || octet_dec < 0 ||
                octet_dec > 255)
            {
                return false;
            }
            else
            {
                ip[octet_counter++] = static_cast<OCTET>(octet_dec);
            }
        }
        return true;
    }
    IP_V4 &operator++()
    {
        *this = IP_V4(1 + to_uint32_t());
        return *this;
    }
    IP_V4 &operator++(int)
    {
        *this = IP_V4(1 + to_uint32_t());
        return *this;
    }

    bool operator<=(const IP_V4 &rhs) const { return to_uint32_t() <= rhs.to_uint32_t(); }

  private:
    IP ip{};
};

int main()
{
    IP_V4 ip1{}, ip2{};
    std::cin >> ip1 >> ip2;
    std::cout << ip1 << " " << ip2;

    for (; ip1 <= ip2; ip1++)
    {
        std::cout << ip1 << std::endl;
    }

    // std::string str{};
    // std::cin >> str;
    // ip.parseIP(str);
    // std::cout << ip;
}