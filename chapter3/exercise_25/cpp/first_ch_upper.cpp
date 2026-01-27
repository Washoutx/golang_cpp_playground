#include <cassert>
#include <cctype>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

template <class CHAR_TYPE>
using tstring =
    std::basic_string<CHAR_TYPE, std::char_traits<CHAR_TYPE>, std::allocator<CHAR_TYPE>>;

template <class CHAR_TYPE>
using tstringstream =
    std::basic_stringstream<CHAR_TYPE, std::char_traits<CHAR_TYPE>, std::allocator<CHAR_TYPE>>;

template <class CHAR_TYPE> tstring<CHAR_TYPE> first_ch_upper(const tstring<CHAR_TYPE> &str)
{
    tstringstream<CHAR_TYPE> result;

    bool isNewWord{true};

    for (const auto &ch : str)
    {
        isNewWord = isNewWord || std::isspace(ch) || std::ispunct(ch);
        if (std::isalpha(ch))
        {
            if (isNewWord)
            {
                result << static_cast<CHAR_TYPE>(std::toupper(ch));
                isNewWord = false;
            }
            else
            {

                result << static_cast<CHAR_TYPE>(std::tolower(ch));
            }
        }
        else
        {
            result << ch;
        }
    }
    return result.str();
}

int main()
{
    using namespace std::string_literals;
    std::string text = "THIS IS an ExamplE, should wORk!";
    std::string expected = "This Is An Example, Should Work!";
    std::cout << expected << " " << first_ch_upper(text) << std::flush;
    assert(expected == first_ch_upper(text));

    assert(L"The C++ Challenger"s == first_ch_upper(L"the c++ challenger"s));

    assert(L"This Is An Example, Should Work!"s ==
           first_ch_upper(L"THIS IS an ExamplE, should wORk!"s));
    return 0;
}