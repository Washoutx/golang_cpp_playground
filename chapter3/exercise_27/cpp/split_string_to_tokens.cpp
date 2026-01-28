#include <cassert>
#include <cctype>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

template <class CHAR_TYPE>
using tstring =
    std::basic_string<CHAR_TYPE, std::char_traits<CHAR_TYPE>, std::allocator<CHAR_TYPE>>;

template <class CHAR_TYPE>
using tstringstream =
    std::basic_stringstream<CHAR_TYPE, std::char_traits<CHAR_TYPE>, std::allocator<CHAR_TYPE>>;

template <class CHAR_TYPE>
std::vector<tstring<CHAR_TYPE>> split_string_to_tokens(const tstring<CHAR_TYPE> &str,
                                                       const CHAR_TYPE delim)
{
    tstringstream<CHAR_TYPE> result{str};
    tstring<CHAR_TYPE> token;
    std::vector<tstring<CHAR_TYPE>> tokens;

    while (std::getline(result, token, delim))
    {
        if (!token.empty())
        {
            tokens.push_back(token);
        }
    }

    return tokens;
}

template <class CHAR_TYPE>
std::vector<tstring<CHAR_TYPE>> split_string_to_tokens(const tstring<CHAR_TYPE> &str,
                                                       const tstring<CHAR_TYPE> &delim)
{
    tstringstream<CHAR_TYPE> result{str};
    tstring<CHAR_TYPE> token;
    std::vector<tstring<CHAR_TYPE>> tokens;

    size_t pos{}, prev_pos{};
    while ((pos = str.find_first_of(delim, prev_pos)) != std::string::npos)
    {
        // Fix situation when two delimiters are next to each other
        if (pos == prev_pos)
        {
            prev_pos++;
            continue;
        }
        if (pos > prev_pos)
        {
            tokens.push_back(str.substr(prev_pos, pos - prev_pos));
            prev_pos = pos + 1;
        }
    }

    if (prev_pos < str.length())
    {
        tokens.push_back(str.substr(prev_pos, std::string::npos));
    }
    return tokens;
}

int main()
{

    const auto tokens1 = split_string_to_tokens(std::string("const tstring<CHAR_TYPE> &str"), ' ');
    for (auto token : tokens1)
    {
        std::cout << token << std::endl;
    }

    const auto tokens2 =
        split_string_to_tokens(std::string("one:two::three!four     check"), std::string(":!. "));
    for (auto token : tokens2)
    {
        std::cout << token << std::endl;
    }
    return 0;
}