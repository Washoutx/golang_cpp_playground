
#include <format>
#include <initializer_list>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <vector>

template <class T, size_t ROWS, size_t COLUMNS> class Array2D
{
  private:
    using value_type = T;
    using iterator = value_type *;
    using const_iterator = value_type const *;

    std::vector<T> arr{};

  public:
    explicit Array2D() : arr(ROWS * COLUMNS) {};
    Array2D(std::initializer_list<T> initList) : arr(initList)
    {
        if (const auto initSize = (ROWS * COLUMNS), listSize = initList.size(); listSize > initSize)
        {
            const std::string err =
                std::format("Init list too big list size. {} > {}", listSize, initSize);
            throw std::runtime_error(err);
        }
    };
    T at(const size_t r, const size_t c) const
    {
        if (const auto idx = (r * COLUMNS) + c, size = arr.size(); idx >= size)
        {
            const std::string err = std::format("Out of bounds idx>=size {} >= {}", idx, size);
            throw std::runtime_error(err);
        }
        else
        {
            return arr[idx];
        }
    }

    iterator begin() { return arr.data(); }
    const_iterator cbegin() const { return arr.size(); }

    iterator end() { return arr.data() + arr.size(); }
    const_iterator cend() const { return arr.data() + arr.size(); }

    friend std::ostream &operator<<(std::ostream &s, Array2D &arr)
    {
        for (const auto &l : arr.arr)
        {
            s << l;
        }
        return s;
    }
};

int main()
{

    Array2D<int, 2, 3> arr = {1, 2, 3, 4, 5};
    std::cout << arr << std::endl;
    try
    {
        arr.at(100, 100);
    }
    catch (...)
    {
        // I try this logic just for fun
        std::exception_ptr eptr = std::current_exception();

        try
        {
            if (eptr)
                std::rethrow_exception(eptr);
        }
        catch (const std::exception &e)
        {
            std::cout << "Error: " << e.what() << '\n';
        }
        catch (...)
        {
            std::cout << "Zlapano niestandardowy wyjatek\n";
        }
    }

    for (const auto &obj : arr)
    {
        std::cout << obj;
    }

    return 0;
}
