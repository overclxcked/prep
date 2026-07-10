#include "bigint.hpp"
#include <bits/stdc++.h>

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
    std::string result;
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
        result += temp_addition + '0';
    }
    if (rest)
        result += rest + '0';
    std::reverse(result.begin(), result.end());
    // std::cout << "rest: " << rest << std::endl;
    // std::cout << "result: " << result << std::endl;
    return bigint(*this);
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
    (*this)++;
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
    long unsigned_value = strtol(str, NULL, 10);
    if (errno == ERANGE || unsigned_value > UINT_MAX)
        throw std::runtime_error("Error");
    return unsigned_value;
}

bigint bigint::operator<<(const bigint& other) const
{
    bigint result(*this);
    for (bigint i(0); i < other; i++)
        result.str += '0';
    return result;
}

bigint bigint::operator>>(const bigint& other) const
{
    bigint result(*this);
    unsigned int unsigned_value = my_to_long(str.c_str());
    result.str = str.substr(0, str.length() - unsigned_value);
    return result;
}

bigint& bigint::operator<<=(const bigint& other)
{
    *this = *this << my_to_long(other.str.c_str());
    return *this;
}

bigint& bigint::operator>>=(const bigint& other)
{
    *this = *this >> my_to_long(other.str.c_str());
    return *this;
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
    if (str.length() < other.str.length() || (str.length() == other.str.length() && str[0] < other.str[0]))
        return true;
    return false;
}

bool bigint::operator>(const bigint& other) const
{
    if (other.str.length() < str.length() || (str.length() == other.str.length() && other.str[0] < str[0]))
        return true;
    return false;
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
}
