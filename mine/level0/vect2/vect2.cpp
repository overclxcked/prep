#include "vect2.hpp"

vect2::vect2(): a(0), b(0){}

vect2::vect2(int c, int d): a(c), b(d){}

const vect2& vect2::operator=(const vect2& other)
{
    if (this != &other)
    {
        this->a = other.a;
        this->b = other.b;
    }
    return *this;
}

vect2::vect2(const vect2& other) { operator=(other); }

vect2::~vect2(){}

int vect2::get_a() const { return a; };
int vect2::get_b() const { return b; };

int& vect2::operator[](int idx) { if (idx == 0) return a; return b; }

const int& vect2::operator[](int idx) const { if (idx == 0) return a; return b; }

vect2& vect2::operator++() { a++; b++; return *this; }

vect2& vect2::operator--() { a--; b--; return *this; }

vect2 vect2::operator++(int) { vect2 tmp(*this); a++; b++; return tmp; }

vect2 vect2::operator--(int) { vect2 tmp(*this); a--; b--; return tmp; }

vect2& vect2::operator+=(const int& value) { a += value; b += value; return *this; }

vect2& vect2::operator-=(const int& value) { a -= value; b -= value; return *this; }

vect2& vect2::operator*=(const int& value) { a *= value; b *= value; return *this; }

vect2& vect2::operator+=(const vect2& other) { a += other.a; b += other.b; return *this; }

vect2& vect2::operator-=(const vect2& other) { a -= other.a; b -= other.b; return *this; }

vect2& vect2::operator*=(const vect2& other) { a *= other.a; b *= other.b; return *this; }

vect2& vect2::operator+(const int& value) { a += value; b += value; return *this; }

vect2& vect2::operator-(const int& value) { a -= value; b -= value; return *this; }

vect2 vect2::operator*(const int& value) const { vect2 v(a * value, b * value); return v; }

vect2 vect2::operator+(const vect2& other) const { vect2 v(a + other.a, b + other.b); return v; }

vect2 vect2::operator-(const vect2& other) const { vect2 v(a - other.a, b - other.b); return v; }

vect2 vect2::operator-() const { vect2 v(-a, -b); return v; }

vect2& vect2::operator*(const vect2& other) { a *= other.a; b *= other.b; return *this; }

bool vect2::operator==(const vect2& other) { return (a == other.a && b == other.b); }

bool vect2::operator!=(const vect2& other) { return !(a == other.a && b == other.b); }

vect2 operator*(int value, const vect2& obj) { return vect2(); }
std::ostream& operator<<(std::ostream& ostr, const vect2& obj)
{
    return ostr << "{" << obj.get_a() << ", " << obj.get_b() << "}" << std::endl;
}