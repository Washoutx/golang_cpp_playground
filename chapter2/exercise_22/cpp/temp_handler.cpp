#include <cstdint>
#include <iostream>
#include <ostream>

namespace Temperature
{

enum class Scale
{
    Celcius,
    Fahrenheit,
    Kelvin
};

template <Scale s> class Value
{
  public:
    constexpr Value(long double t) : _t(t) {};
    constexpr Value operator-() const { return Value(-_t); }
    constexpr explicit operator double() const { return _t; };

  private:
    double _t;

    friend std::ostream &operator<<(std::ostream &stream, const Value<s> &v)
    {
        if constexpr (s == Scale::Celcius)
        {
            stream << v._t << " Celcius";
        }
        else if constexpr (s == Scale::Kelvin)
        {
            stream << v._t << " Kelvin";
        }
        else if constexpr (s == Scale::Fahrenheit)
        {
            stream << v._t << " Fahrenheit";
        }
        return stream;
    }
};

template <Scale s> constexpr bool operator>(const Value<s> &t1, const Value<s> &t2)
{
    return t1 > t2;
}
template <Scale s> constexpr bool operator<(const Value<s> &t1, const Value<s> &t2)
{
    return t1 < t2;
}
template <Scale s> constexpr bool operator>=(const Value<s> &t1, const Value<s> &t2)
{
    return t1 >= t2;
}
template <Scale s> constexpr bool operator<=(const Value<s> &t1, const Value<s> &t2)
{
    return t1 <= t2;
}
template <Scale s> constexpr bool operator==(const Value<s> &t1, const Value<s> &t2)
{
    return t1 == t2;
}
template <Scale s> constexpr bool operator!=(const Value<s> &t1, const Value<s> &t2)
{
    return t1 != t2;
}

template <Scale From, Scale T> struct conversion
{
    static double convert(const double value) = delete;
};

// I am too lazy to implement all the conversion...
template <> struct conversion<Scale::Celcius, Scale::Fahrenheit>
{
    static double convert(const double value) { return value * 9.0 / 5.0 + 32.0; }
};

template <Scale To, Scale From> Value<To> cast_scale(const Value<From> &t)
{
    return Value<To>(conversion<From, To>::convert(static_cast<double>(t)));
}

constexpr Value<Scale::Celcius> operator"" _deg(long double t) { return Value<Scale::Celcius>(t); }
constexpr Value<Scale::Kelvin> operator"" _K(long double t) { return Value<Scale::Kelvin>(t); }
constexpr Value<Scale::Fahrenheit> operator"" _f(long double t)
{
    return Value<Scale::Fahrenheit>(t);
}
constexpr Value<Scale::Celcius> operator"" _deg(unsigned long long t)
{
    return Value<Scale::Celcius>(t);
}
constexpr Value<Scale::Kelvin> operator"" _K(unsigned long long t)
{
    return Value<Scale::Kelvin>(t);
}
constexpr Value<Scale::Fahrenheit> operator"" _f(unsigned long long t)
{
    return Value<Scale::Fahrenheit>(t);
}
} // namespace Temperature

int main()
{
    using namespace Temperature;
    auto t1 = -10_deg;
    auto t2 = -10_f;

    auto t3 = cast_scale<Scale::Fahrenheit>(t1);
    std::cout << t1 << std::endl;
    std::cout << t2 << std::endl;
    std::cout << t3 << std::endl;
    return 0;
}