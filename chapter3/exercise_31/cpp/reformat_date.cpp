#include <cassert>
#include <iostream>
#include <regex>

std::string reformat_date(const std::string &str)
{
    std::string results;
    auto pattern = std::regex{R"((\d{1,2})(\.|-|/)(\d{1,2})(\.|-|/)(\d{4}))"};

    return std::regex_replace(str, pattern, R"($5-$3-$1)");
}

int main()
{
    using namespace std::string_literals;

    assert(reformat_date("today is 01.12.2017!"s) == "today is 2017-12-01!"s);
    return 0;
}