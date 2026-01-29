#include <cassert>
#include <cstdint>
#include <iostream>
#include <optional>
#include <regex>
#include <string>

struct URI
{
    std::string protocol;
    std::string domain;
    std::optional<int> port;
    std::optional<std::string> path;
    std::optional<std::string> query;
    std::optional<std::string> fragment;
};

std::optional<URI> parseURI(const std::string &uri)
{
    std::regex pattern(R"(^(\w+):\/\/([\w.-]+)(:(\d+))?([\w\/\.]+)?(\?([\w=&]*)(#?(\w+))?)?$)");
    std::smatch matches{};

    URI results{};
    if (std::regex_match(uri, matches, pattern))
    {
        std::cout << matches.size() << std::endl;
        for (size_t i = 0; i < matches.size(); i++)
        {
            std::cout << matches[i].str() << std::endl;
        }
        if (matches[1].matched && matches[2].matched)
        {
            results.protocol = matches[1].str();
            results.domain = matches[2].str();

            if (matches[4].matched)
            {
                results.port = std::stoi(matches[4]);
            }
            if (matches[5].matched)
            {
                results.path = matches[5];
            }
            if (matches[7].matched)
            {
                results.query = matches[7];
            }
            if (matches[9].matched)
            {
                results.fragment = matches[9];
            }
        }
    }

    return results;
}

int main()
{

    auto p1 = parseURI("https://packt.com");
    assert(p1);
    assert(p1->protocol == "https");
    assert(p1->domain == "packt.com");
    assert(!p1->port);
    assert(!p1->path);
    assert(!p1->query);
    assert(!p1->fragment);

    auto p2 = parseURI("https://bbc.com:80/en/index.html?lite=true#ui");
    assert(p2);
    assert(p2->protocol == "https");
    assert(p2->domain == "bbc.com");
    assert(p2->port == 80);
    assert(p2->path.value() == "/en/index.html");
    assert(p2->query.value() == "lite=true");
    assert(p2->fragment.value() == "ui");

    return 0;
}