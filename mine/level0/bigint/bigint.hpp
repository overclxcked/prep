// bigint.hpp
#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <cerrno>
#include <climits>

class bigint {
private:
    std::string str;
    
public:
    // Orthodox Canonical Form
    bigint();
    bigint(unsigned int num);
    bigint(const bigint& other);
    bigint& operator=(const bigint& other);
    ~bigint() {}
    
    std::string getStr() const;
    
    // Addition
    bigint operator+(const bigint& other) const;
    bigint& operator+=(const bigint& other);
    
    // // Increment
    bigint& operator++();    // ++x
    bigint operator++(int);  // x++
    
    // // Digit shifts (with unsigned int)
    bigint operator<<(unsigned int n) const;
    bigint operator>>(unsigned int n) const;
    bigint& operator<<=(unsigned int n);
    bigint& operator>>=(unsigned int n);
    
    // // Digit shifts (with bigint)
    bigint operator<<(const bigint& other) const;
    bigint operator>>(const bigint& other) const;
    bigint& operator<<=(const bigint& other);
    bigint& operator>>=(const bigint& other);
    
    // // Comparisons
    bool operator==(const bigint& other) const;
    bool operator!=(const bigint& other) const;
    bool operator<(const bigint& other) const;
    bool operator>(const bigint& other) const;
    bool operator<=(const bigint& other) const;
    bool operator>=(const bigint& other) const;
};

std::ostream& operator<<(std::ostream& os, const bigint& obj);

#endif