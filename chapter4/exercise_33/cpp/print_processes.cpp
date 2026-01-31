#include <algorithm>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ranges>

void printProcesses()
{
    for (auto &file : std::filesystem::directory_iterator("/proc"))
    {
        const std::string pid = file.path().filename().string();

        if (!std::ranges::all_of(pid, ::isdigit))
        {
            continue;
        }
        std::ifstream commFile(file.path() / "comm");
        std::string processName;

        if (commFile.is_open())
        {
            std::getline(commFile, processName);
            std::cout << "PID: " << pid << " | Name:" << processName << "\n";
        }
        commFile.close();
    }
}

int main()
{

    printProcesses();
    return 0;
}