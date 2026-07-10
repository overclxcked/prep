#include "bigint.hpp"
#include <bits/stdc++.h>

bigint::bigint(): str("0")
{

}

bigint::bigint(unsigned int num)
{
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
        
        std::cout << "digit1: " << digit1 << std::endl;
        std::cout << "digit2: " << digit2 << std::endl;
        int temp_addition = rest + digit1 + digit2;
        if (temp_addition > 9)
        {
            rest += temp_addition / 10;
            std::cout << rest << std::endl;
            temp_addition = temp_addition % 10;
            std::cout << temp_addition << std::endl;
        }
        std::cout << "entering: " << (char) (temp_addition + '0') << std::endl;
        result += temp_addition + '0';
    }
    std::reverse(result.begin(), result.end());
    std::cout << "result: " << result << std::endl;
    return bigint(*this);
}

// bigint& bigint::operator+=(const bigint& other)
// {

// }
