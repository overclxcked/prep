#include "bigint.hpp"

bigint::bigint(): str("0")
{

}

bigint::bigint(unsigned int num)
{
    // std::cout << "unum: " << num << std::endl;
    std::ostringstream ostr;
    ostr << num;
    str = ostr.str();
}

bigint::bigint(const bigint& other): str(other.str) {}

bigint& bigint::operator=(const bigint& other)
{
    if (this != &other)
    {
        str = other.str;
    }
    return *this;
}

std::string bigint::getStr() const
{
    return str;
}

bigint bigint::operator+(const bigint& other) const
{
    // std::cout << "str: " << str << std::endl;
    std::string a(str.rbegin(), str.rend());
    std::string b(other.str.rbegin(), other.str.rend());
    // std::cout << a << b << std::endl;

    if (b.length() > a.length())
        std::swap(a, b);
    
    int rest = 0;
    bigint result;
    for (int i = 0; i < a.length(); i++)
    {
        int digit1;
        int digit2;
        digit1 = a[i] - '0';
        if (i >= b.length())
            digit2 = 0;
        else
            digit2 = b[i] - '0';
        
        // std::cout << "digit1: " << digit1 << std::endl;
        // std::cout << "digit2: " << digit2 << std::endl;
        int temp_addition = rest + digit1 + digit2;
        // std::cout << "temp_addition before: " << temp_addition << std::endl;
        if (temp_addition > 9)
        {
            rest = temp_addition / 10;
            // std::cout << "rest is: " << rest << std::endl;
            temp_addition = temp_addition % 10;
            // std::cout << "temp_addition after: " << temp_addition << std::endl;
        }
        else rest = 0;
        // std::cout << "entering: " << (char) (temp_addition + '0') << std::endl;
        result.str += temp_addition + '0';
    }
    if (rest)
        result.str += rest + '0';
    std::reverse(result.str.begin(), result.str.end());
    // std::cout << "rest: " << rest << std::endl;
    // std::cout << "result: " << result << std::endl;
    return result;
}

bigint& bigint::operator+=(const bigint& other)
{
    str = (*this + other).str;
    return *this;
}

bigint& bigint::operator++()
{
    *this += bigint(1);
    return *this;
}

bigint bigint::operator++(int)
{
    bigint temp(*this);
    (*this) += 1;
    return temp;
}

bigint bigint::operator<<(unsigned int n) const
{
    bigint result(*this);
    for (int i = 0; i < n; i++)
        result.str += '0';
    return result;
}

bigint bigint::operator>>(unsigned int n) const
{
    bigint result(*this);
    if (n > str.length())
        result.str = "0";
    else
        result.str = str.substr(0, str.length() - n);
    return result;
}

bigint& bigint::operator<<=(unsigned int n)
{
    *this = *this << n;
    return *this;
}

bigint& bigint::operator>>=(unsigned int n)
{
    *this = *this >> n;
    return *this;
}

unsigned int my_to_long(const char *str)
{
    errno = 0;
    long unsigned_value = strtol(str, NULL, 10);
    if (errno == ERANGE || unsigned_value > UINT_MAX)
        throw std::runtime_error("Error");
    return unsigned_value;
}

bigint bigint::operator<<(const bigint& other) const
{
    unsigned int n = my_to_long(other.str.c_str());
    return *this << n;
}

bigint bigint::operator>>(const bigint& other) const
{
    unsigned int n = my_to_long(other.str.c_str());
    return *this >> n;
}

bigint& bigint::operator<<=(const bigint& other)
{
    return *this <<= my_to_long(other.str.c_str());
}

bigint& bigint::operator>>=(const bigint& other)
{
    return *this >>= my_to_long(other.str.c_str());
}

bool bigint::operator==(const bigint& other) const
{
    return str == other.str;
}

bool bigint::operator!=(const bigint& other) const
{
    return str != other.str;
}

bool bigint::operator<(const bigint& other) const
{
    if (str.length() != other.str.length())
        return str.length() < other.str.length();
    return str < other.str;
}

bool bigint::operator>(const bigint& other) const
{
    if (str.length() != other.str.length())
        return str.length() > other.str.length();
    return str > other.str;
}

bool bigint::operator<=(const bigint& other) const
{
    return *this < other || *this == other;
}

bool bigint::operator>=(const bigint& other) const
{
    return *this > other || *this == other;
}

std::ostream& operator<<(std::ostream& os, const bigint& obj)
{
    os << obj.getStr();
    return os;
}
