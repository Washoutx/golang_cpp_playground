#include <array>
#include <charconv>
#include <ranges>
#include <cstdint>
#include <ios>
#include <iostream>
#include <istream>
#include <string_view>

class IP_V4
{
    using OCTET = std::uint8_t;
    using IP = std::array<OCTET, 4>;

  public:
    constexpr IP_V4() noexcept = default;
    explicit constexpr IP_V4(OCTET a, OCTET b, OCTET c, OCTET d) noexcept : ip{a, b, c, d} {};
    friend std::ostream &operator<<(std::ostream &s, IP_V4 &ip)
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

  private:
    IP ip{};
};

int main()
{
    IP_V4 ip;
    // std::cin >> ip;
    // std::cout << ip;

    std::string str{};
    std::cin >> str;
    ip.parseIP(str);
    std::cout << ip;
}