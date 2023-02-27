#include <rational/rational.hpp>

#include <iostream>
#include <sstream>
#include <exception>

int gcd(int lhs, int rhs) {
    lhs = abs(lhs);
    rhs = abs(rhs);
    if (rhs == 0) {
        return lhs;
    }
    else {
        return gcd(rhs, lhs % rhs);
    }
}

int lcm(int lhs, int rhs) {
    return lhs / gcd(lhs, rhs) * rhs;
}

//Input and output
std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs) {
    return rhs.writeTo(ostrm);
}

std::ostream& Rational::writeTo(std::ostream& ostrm) const {
    ostrm << num_ << separator << denum_;
    return ostrm;
}

std::istream& operator>>(std::istream& istrm, Rational& rhs) {
    return rhs.readFrom(istrm);
}

std::istream& Rational::readFrom(std::istream& istrm) {
    int p(0);
    int q(1);
    char divide(0);
    istrm >> p;
    istrm >> divide;
    istrm >> q;
    if (istrm.good() || !istrm.fail() && istrm.eof()) {
        if (Rational::separator == divide) {
            istrm.clear();
            *this = Rational(p, q);
        }
        else {
            istrm.setstate(std::ios_base::failbit);
        }
    }
    return istrm;
}

// Algebra
Rational Rational::operator+(const Rational& rhs) const {
    return Rational(num_ * rhs.denum_ + rhs.num_ * denum_, denum_ * rhs.denum_);
}

Rational Rational::operator-(const Rational& rhs) {
    return Rational(num_ * rhs.denum_ - rhs.num_ * denum_, denum_ * rhs.denum_);
}

Rational Rational::operator*(const Rational& rhs) {
    return Rational(num_ * rhs.num_, denum_ * rhs.denum_);
}

Rational Rational::operator/(const Rational& rhs) {
    if (rhs.num_ == 0) throw std::exception();
    return Rational(num_ * rhs.denum_, denum_ * rhs.num_);
}

Rational& Rational::operator+=(const Rational& rhs)
{
    int _lcm = lcm(denum_, rhs.denum_);
    int left_multiplier = _lcm / denum_;
    int right_multiplier = _lcm / rhs.denum_;
    num_ = (num_ * left_multiplier + rhs.num_ * right_multiplier);
    denum_ = _lcm;
    this->reduce();
    return *this;
}

Rational& Rational::operator-=(const Rational& rhs)
{
    int _lcm = lcm(denum_, rhs.denum_);
    int left_multiplier = _lcm / denum_;
    int right_multiplier = _lcm / rhs.denum_;
    num_ = (num_ * left_multiplier - rhs.num_ * right_multiplier);
    denum_ = _lcm;
    this->reduce();
    return *this;
}

Rational& Rational::operator*=(const Rational& rhs)
{
    num_ *= rhs.num_;
    denum_ *= rhs.denum_;
    this->reduce();
    return *this;
}

Rational& Rational::operator/=(const Rational& rhs)
{
    if (rhs.num_ == 0) throw std::exception();
    num_ *= rhs.denum_;
    denum_ *= rhs.num_;
    this->reduce();
    return *this;
}

// Comparsion
bool Rational::operator==(const Rational& rhs) const {
    return (num_ == rhs.num_) && (denum_ == rhs.denum_);
}

bool Rational::operator!=(const Rational& rhs) const {
    return !operator==(rhs);
}

bool Rational::operator>(const Rational& rhs) const {
    return ((num_ * rhs.denum_ - rhs.num_ * denum_) > 0);
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    return rhs.operator>(lhs);
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
    return !lhs.operator>(rhs);
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
    return !rhs.operator>(lhs);
}

// Other
Rational::Rational(const int num)
    : Rational(num, 1)
{
}

Rational& Rational::reduce()
{
    int _gcd = gcd(num_, denum_);
    num_ /= _gcd;
    denum_ /= _gcd;
    return *this;
}

Rational::Rational(const int num, const int denum) {
    if (denum == 0) throw std::exception();
    int d = gcd(num, denum);
    denum_ = denum / d;
    num_ = num / d;
    if (denum_ < 0) {
        denum_ = -denum_;
        num_ = -num_;
    }
}