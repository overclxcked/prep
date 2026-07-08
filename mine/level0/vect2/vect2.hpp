#pragma once
#include <iostream>

class vect2 {
    int a;
    int b;

    public:
        vect2();
        vect2(int a, int b);
        vect2(const vect2& other);
        ~vect2();

        int get_a() const ;
        int get_b() const ;
        
        const vect2& operator=(const vect2& other);
        int& operator[](int idx);
        const int& operator[](int idx) const;
        vect2& operator++();
        vect2& operator--();
        vect2 operator++(int);
        vect2 operator--(int);
        vect2& operator+=(const int& value);
        vect2& operator-=(const int& value);
        vect2& operator*=(const int& value);
        vect2& operator+=(const vect2& other);
        vect2& operator-=(const vect2& other);
        
        vect2 operator-() const;

        vect2 operator+(const vect2& other) const;
        vect2 operator-(const vect2& other) const;
        vect2 operator*(const int& value) const;

        vect2& operator+(const int& value);
        vect2& operator-(const int& value);
        vect2& operator*(const vect2& other);
        
        vect2& operator*=(const vect2& other);
        
        bool operator==(const vect2& other);
        bool operator!=(const vect2& other);
};

std::ostream& operator<<(std::ostream& ostr, const vect2& obj);
vect2 operator*(int value, const vect2& obj);