#include <iostream>
#include <regex>

std::vector<std::string> extractAllLicensePlates(const std::string& str){
    std::vector<std::string> results{};

    std::regex pattern{"[A-Za-z]{3}-[A-Za-z]{2} \\d{3,4}"};

    const auto begin = std::sregex_iterator(str.begin(), str.end(), pattern);
    const auto end = std::sregex_iterator();

    for (auto it = begin; it != end; ++it) {
        std::cout << it->position() << " " << it->str() << std::endl;
        results.emplace_back(it->str());
    }
    return results;
}

int main()
{
    std::regex pattern{"^[A-Za-z]{3}-[A-Za-z]{2} \\d{3,4}$"};

    std::string s1 = "ABC-DE 123";
    std::string s2 = "XYZ-QW 1234";
    std::string s3 = "AB-DE 123";

    std::cout << std::regex_match(s1, pattern) << std::endl; // 1
    std::cout << std::regex_match(s2, pattern) << std::endl; // 1
    std::cout << std::regex_match(s3, pattern) << std::endl; // 0

    const auto str = s1+s2+s3;
    extractAllLicensePlates(str);
    return 0;
}