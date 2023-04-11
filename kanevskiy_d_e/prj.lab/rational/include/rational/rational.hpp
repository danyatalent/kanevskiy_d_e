#ifndef RATIONAL_RATIONAL_HPP_20230215
#define RATIONAL_RATIONAL_HPP_20230215
#include <iosfwd>
#include <cstdint>

class Rational
{
public:
    Rational() = default;
    explicit Rational(const std::int32_t num);
    Rational(const Rational&) = default;
    Rational(const std::int32_t num, const std::int32_t denum) ;
    ~Rational() = default;
    Rational& reduce();
    Rational& operator+=(const Rational& rhs);
    Rational& operator*=(const Rational& rhs);
    Rational& operator-=(const Rational& rhs);
    Rational& operator/=(const Rational& rhs);


    Rational& operator+=(const std::int32_t& rhs);
    Rational& operator-=(const std::int32_t& rhs);
    Rational& operator*=(const std::int32_t& rhs);
    Rational& operator/=(const std::int32_t& rhs);

    Rational& operator++();
    Rational& operator--();
    /*Rational operator+(const Rational& rhs) const;
    Rational operator-(const Rational& rhs);
    Rational operator*(const Rational& rhs);
    Rational operator/(const Rational& rhs);*/
    Rational& operator-();

    bool operator==(const Rational& rhs) const;
    bool operator>(const Rational& rhs) const;
    bool operator!=(const Rational& rhs) const;

    std::ostream& writeTo(std::ostream& ostrm) const;
    std::istream& readFrom(std::stringstream& istrm);


private:
    std::int32_t num_{ 0 };
    std::int32_t denum_{ 1 };
    static const char separator{ '/' };
};

Rational operator+(const Rational& lhs, const Rational& rhs);
Rational operator-(const Rational& lhs, const Rational& rhs);
Rational operator*(const Rational& lhs, const Rational& rhs);
Rational operator/(const Rational& lhs, const Rational& rhs);

Rational operator+(const Rational& lhs, const std::int32_t rhs);
Rational operator-(const Rational& lhs, const std::int32_t rhs);
Rational operator*(const Rational& lhs, const std::int32_t rhs);
Rational operator/(const Rational& lhs, const std::int32_t rhs);

Rational operator+(const std::int32_t lhs, const Rational& rhs);
Rational operator-(const std::int32_t lhs, const Rational& rhs);
Rational operator*(const std::int32_t lhs, const Rational& rhs);
Rational operator/(const std::int32_t lhs, const Rational& rhs);

std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs);
std::istream& operator>>(std::stringstream& istrm, Rational& rhs);
bool operator<(const Rational& lhs, const Rational& rhs);
bool operator<=(const Rational& lhs, const Rational& rhs);
bool operator>=(const Rational& lhs, const Rational& rhs);
#endif