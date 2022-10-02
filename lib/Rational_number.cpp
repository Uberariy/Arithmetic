/**
 * @file Rational_number.cpp
 * @author Uberariy
 * @brief Rational_number class methods implementation
 * @version 0.1
 * @date 2022-09-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "Rational_number.hpp"

Rational_number::Rational_number():numerator(1), denominator(1) {}

Rational_number::Rational_number(long long int op):numerator(op), denominator(1) {}

Rational_number::Rational_number(long long int lop, unsigned long long int rop) {
    if (rop == 0) {
        throw DivisionByZeroException("Denominator cannot equal to zero.");
    }
    numerator = lop;
    denominator = rop;
}

Rational_number::Rational_number(const char* op) {
    std::string s = std::string(op);
    auto pos = s.find("/"); 
    if (std::string::npos == pos) {
        pos = s.find(".");
        if (std::string::npos == pos) {
            numerator = std::stoll(s);
            denominator = 1;
        } else {
            long double fl = std::atof(op);
            denominator = 1;
            while (fl - (long long int)fl >= 1e-10) {
                fl *= 10;
                denominator *= 10;
            }
            numerator = fl;
        }
    } else {
        if (s.substr(0, pos).empty()) {
            throw std::runtime_error("Invalid rational number format: '" + s + "'");
        }
        auto lopa = std::stoll(s.substr(0, pos));
        s.erase(0, pos + 1);
        if (s.empty()) {
            throw std::runtime_error("Invalid rational number format: '" + std::string(op) + "'");
        }
        auto ropa = std::stoll(s);
        if (ropa == 0) {
            throw DivisionByZeroException("Denominator cannot equal to zero.");
        } else if (ropa < 0) {
            throw std::runtime_error("Invalid rational number format: '" + std::string(op) + "'");
        }
        numerator = lopa;
        denominator = ropa;
    }
    make_canonical();
}

Rational_number::Rational_number(const char* lop, const char* rop) {
    if (std::string(lop).empty() or std::string(rop).empty()) {
        throw std::runtime_error("Invalid rational number format: '" + std::string(rop) + "' / '" + std::string(lop) + "'");
    }
    auto lopa = std::stoll(lop);
    auto ropa = std::stoll(rop);
    if (ropa == 0) {
        throw DivisionByZeroException("Denominator cannot equal to zero.");
    } else if (ropa < 0) {
        throw std::runtime_error("Invalid rational number format: '" + std::string(rop) + "' / '" + std::string(lop) + "'");
    }
    numerator = lopa;
    denominator = ropa;
}

Rational_number& Rational_number::operator=(const long long int& op) {
    Rational_number rat(op);
    *this = rat;
    return *this;
}

Rational_number& Rational_number::operator=(const char* op) {
    Rational_number rat(op);
    *this = rat;
    return *this;
}

Rational_number& Rational_number::operator=(std::string op) {
    Rational_number rat(op.c_str());
    *this = rat;
    return *this;
}

Rational_number Rational_number::operator+() const {
    return *this;
}

Rational_number Rational_number::operator-() const {
    return {-numerator, denominator};
}

Rational_number& Rational_number::operator+=(const Rational_number &op) {
    this->numerator *= op.denominator;
    this->numerator += op.numerator * this->denominator;
    this->denominator *= op.denominator;
    make_canonical();
    return *this;
}

Rational_number& Rational_number::operator-=(const Rational_number &op) {
    *this += -op;
    return *this;
}

Rational_number& Rational_number::operator*=(const Rational_number &op) {
    this->numerator *= op.numerator;
    this->denominator *= op.denominator;
    if (this->denominator == 0) {
        throw DivisionByZeroException("Denominator cannot equal to zero.");
    }
    make_canonical();
    return *this;
}

Rational_number& Rational_number::operator/=(const Rational_number &op) {
    this->numerator *= op.denominator;
    this->denominator *= op.numerator;
    if (this->denominator == 0) {
        throw DivisionByZeroException("Denominator cannot equal to zero.");
    }
    make_canonical();
    return *this;
}

Rational_number operator+(Rational_number lop, const Rational_number& rop) {
    return lop += rop;
}

Rational_number operator-(Rational_number lop, const Rational_number& rop) {
    return lop -= rop;
}

Rational_number operator*(Rational_number lop, const Rational_number& rop) {
    return lop *= rop;
}

Rational_number operator/(Rational_number lop, const Rational_number& rop) {
    return lop /= rop;
}

Rational_number& Rational_number::operator++(int op) {
    return *this += 1;
}

Rational_number& Rational_number::operator--(int op) {
    return *this -= 1;
}

std::ostream& operator<< (std::ostream& os, Rational_number const& op) {
    os << (std::to_string(op.numerator) + "/" + std::to_string(op.denominator));
    return os;
}

std::istream& operator>> (std::istream& is, Rational_number& op) {
    std::string s;
    is >> s;
    op = s;
    return is;
}

bool operator==(const Rational_number& lop, const Rational_number& rop) {
    Rational_number clop = lop;
    clop.make_canonical();
    Rational_number crop = rop;
    crop.make_canonical();
    return (long long int)clop.denominator * crop.numerator == clop.numerator * (long long int)crop.denominator;
}

bool operator!=(const Rational_number& lop, const Rational_number& rop) {
    return !(lop == rop);
}

bool operator<(const Rational_number& lop, const Rational_number& rop) {
    Rational_number clop = lop;
    clop.make_canonical();
    Rational_number crop = rop;
    crop.make_canonical();
    // std::cout << clop << "\t" << crop << "\t" << clop.denominator * crop.numerator << "\t" << clop.numerator * (long long int)crop.denominator << "\n";
    return (long long int)clop.denominator * crop.numerator > clop.numerator * (long long int)crop.denominator;
}

bool operator>(const Rational_number& lop, const Rational_number& rop) {
    return !(lop < rop);
}

bool operator<=(const Rational_number& lop, const Rational_number& rop) {
    return (lop < rop) || (lop == rop);
}

bool operator>=(const Rational_number& lop, const Rational_number& rop) {
    return (lop > rop) || (lop == rop);
}

Rational_number::operator std::string() const {
    long double fl = numerator / denominator;
    return std::to_string(fl);
}

Rational_number::operator long double() const {
    long double fl = (long double)numerator / (long double)denominator;
    return fl;
}

Rational_number::operator long long() const {
    return cast_to_undivided("long long", LLONG_MIN, LLONG_MAX);
}

Rational_number::operator long() const {
    return cast_to_undivided("long", LONG_MIN, LONG_MAX);
}

Rational_number::operator int() const {
    return cast_to_undivided("int", INT_MIN, INT_MAX);
}

Rational_number::operator short() const {
    return cast_to_undivided("short", SHRT_MIN, SHRT_MAX);
}
    
Rational_number::operator bool() const {
    return (numerator != 0);
}

void Rational_number::set_numerator(const long long int& op) {
    this->numerator = op;
}

void Rational_number::set_denominator(const long long int& op) {
    if (op == 0) {
        throw DivisionByZeroException("Denominator cannot equal to zero.");
    } else if (op < 0) {
        throw std::runtime_error("Invalid denominator format: '" + std::to_string(op) + "'");
    }
    this->denominator = op;
}

long long int Rational_number::get_numerator() {
    return numerator;
}

long long int Rational_number::get_denominator() {
    return denominator;
}

long long int Rational_number::cast_to_undivided(const std::string& type_name, const long long int& min, const long long int& max, bool throwUTOE, bool throwNUE) const {
    Rational_number tmp(numerator, denominator);
    if (throwUTOE && !((tmp < Rational_number(max)) && (tmp > Rational_number(min)))) {
        throw UndividedTypeOverflowException("This operation causes '" + type_name + "' type overflow!");
    } else if (throwNUE && (numerator % denominator)) {
        throw NotUndividedException();
    }
    return numerator / denominator;
}

Rational_number& Rational_number::floor() {
    numerator /= denominator;
    denominator = 1;
    return *this;
}

Rational_number& Rational_number::round() {
    int sign = (numerator >= 0) ? 1 : -1;
    numerator *= sign;
    long long occur = numerator / denominator;
    long long frac = numerator % denominator;
    numerator = sign * (occur + (int)(frac >= denominator / 2));
    denominator = 1;
    return *this;
}

Rational_number& Rational_number::make_canonical() {
    if (numerator == 0) {
        denominator = 1;
    } else {
        long long int gcd = std::gcd(numerator, denominator);
        if (!(numerator % denominator)) {
            numerator = numerator / gcd;
            denominator = denominator / gcd;
        }
    }
    return *this;
}
