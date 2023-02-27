#ifndef RATIONAL_RATIONAL_HPP_20230215
#define RATIONAL_RATIONAL_HPP_20230215
#include <iosfwd>

int gcd(int lhs, int rhs);
int lcm(int lhs, int rhs);

class Rational
{
public:
    Rational() = default;
    Rational(const int num);
    Rational(const Rational&) = default;
    Rational(const int num, const int denum);
    ~Rational() = default;
    Rational& reduce();
    Rational& operator+=(const Rational& rhs);
    Rational& operator*=(const Rational& rhs);
    Rational& operator-=(const Rational& rhs);
    Rational& operator/=(const Rational& rhs);
    Rational operator+(const Rational& rhs) const;
    Rational operator-(const Rational& rhs);
    Rational operator*(const Rational& rhs);
    Rational operator/(const Rational& rhs);

    bool operator==(const Rational& rhs) const;
    bool operator>(const Rational& rhs) const;
    bool operator!=(const Rational& rhs) const;

    std::ostream& writeTo(std::ostream& ostrm) const;
    std::istream& readFrom(std::istream& istrm);


private:
    int num_{ 0 };
    int denum_{ 1 };
    static const char separator{ '/' };
};

std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs);
std::istream& operator>>(std::istream& istrm, Rational& rhs);
bool operator<(const Rational& lhs, const Rational& rhs);
bool operator<=(const Rational& lhs, const Rational& rhs);
bool operator>=(const Rational& lhs, const Rational& rhs);
#endif