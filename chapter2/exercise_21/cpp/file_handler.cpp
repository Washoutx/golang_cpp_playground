#include <iostream>
#include <memory>
#include <stdexcept>

class FileHandler
{
  private:
    struct FileCloser
    {
        void operator()(FILE *f)
        {
            if (f)
            {
                std::cout << "Close file\n";
                std::fclose(f);
            }
        }
    };

    std::unique_ptr<FILE, FileCloser> f;

  public:
    FileHandler(const std::string &filename, const std::string &mode)
        : f(std::fopen(filename.data(), mode.data()))
    {
        if (!f)
        {
            throw std::runtime_error("Fopen failed\n");
        }
    }

    std::string read(size_t size) const
    {
        std::string buffer(size, '\0');
        const size_t readSize = fread(buffer.data(), sizeof(uint8_t), buffer.size(), f.get());
        buffer.resize(readSize);
        return buffer;
    }
};

int main()
{
    auto fh = FileHandler("test.txt", "r");
    std::cout << fh.read(256) << std::endl;

    auto fh2 = std::move(fh);

    return 0;
}