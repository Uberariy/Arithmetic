/**
 * @file Matrix.cpp
 * @author Uberariy
 * @brief 
 * @version 0.1
 * @date 2022-10-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Matrix.hpp"
#include <iostream>

template<typename T>
std::ostream& operator<<(std::ostream& os, Matrix<T> const& op) {
    os << op.to_string();
    return os;
}

template<typename T>
std::istream& operator>>(std::istream& is, Matrix<T>& op) {
    std::string s;
    is >> s;
    while (s == "#") {
        while (is.peek() != '\n') {
            is >> s;
        }
        is >> s;
    }
    if (s != "matrix") {
        throw WrongFormatWhileParsingException("Insupported structure: '" + s + "'");
    }
    is >> s;
    if (s != "rational") {
        throw WrongFormatWhileParsingException("Insupported type: '" + s + "'");
    }
    unsigned long long x;
    unsigned long long y;
    is >> s;
    x = std::stoull(s.c_str());
    op.set_length_x(x);
    is >> s;
    x = std::stoull(s.c_str());
    op.set_length_y(x);
    T element;
    while (!is.fail() && (is >> s)) {
        while (s == "#") {
            while (is.peek() != '\n') {
                is >> s;
            }
            is >> s;
        }
        x = std::stoull(s.c_str());
        is >> y;
        std::getline(is, s, '>');
        element = Rational_number(s + '>');
        op(x, y) = element;
    }
    return is;
}

template<typename Tl, typename Tr>
bool operator==(const Matrix<Tl> &lop, const Matrix<Tr> &rop) {
    return !(lop != rop);
}

template<typename Tl, typename Tr>
bool operator!=(const Matrix<Tl> &lop, const Matrix<Tr> &rop) {
    if ((lop.length_x != rop.length_x) || (lop.length_y != rop.length_y))
        return true;
    Matrix<decltype(Tl() + Tr())> res(lop.length_x, lop.length_y);
    for (auto &[key, val] : lop.data) {
        if ((rop.data.find(key) != rop.data.end()) && (rop.data.find(key)->second == lop.data.find(key)->second)) {
            ;
        } else {
            return true;
        }
    }
    return false;
}

template<typename Tl, typename Tr>
auto operator+(Matrix<Tl> lop, const Tr& rop) {
    for (auto &[key, val] : lop.data) {
        val += rop;
    }
    lop.delete_null_elements();
    return lop;
}

template<typename Tl, typename Tr>
auto operator-(Matrix<Tl> lop, const Tr& rop) {
    for (auto &[key, val] : lop.data) {
        val -= rop;
    }
    lop.delete_null_elements();
    return lop;
}

template<typename Tl, typename Tr>
auto operator*(Matrix<Tl> lop, const Tr& rop) {
    for (auto &[key, val] : lop.data) {
        val *= rop;
    }
    lop.delete_null_elements();
    return lop;
}

template<typename Tl, typename Tr>
auto operator/(Matrix<Tl> lop, const Tr& rop) {
    for (auto &[key, val] : lop.data) {
        val /= rop;
    }
    lop.delete_null_elements();
    return lop;
}

template<typename Tl, typename Tr>
auto operator-(const Matrix<Tl> &lop, const Matrix<Tr> &rop) {
    Matrix<decltype(Tl() + Tr())> res(lop.length_x, lop.length_y);
    for (auto &[key, val]: lop.data) {
        res.data[key] = val;
    }
    for (auto &[key, val]: rop.data) {
        if (res.data.find(key) != res.data.end()) {
            res.data[key] += -val;
        } else {
            res.data[key] = -val;
        }
    }
    res.delete_null_elements();
    return res;
}
template<typename Tl, typename Tr>
auto operator+(const Matrix<Tl> &lop, const Matrix<Tr> &rop) {
    Matrix<decltype(Tl() + Tr())> res(lop.length_x, lop.length_y);
    for (auto &[key, val]: lop.data) {
        res.data[key] = val;
    }
    for (auto &[key, val]: rop.data) {
        if (res.data.find(key) != res.data.end()) {
            res.data[key] += val;
        } else {
            res.data[key] = val;
        }
    }
    res.delete_null_elements();
    return res;
}

// template<typename Tl, typename Tr>
// auto operator*(Matrix<Tl> lop, Matrix<Tr> rop) {
//     Matrix<decltype(Tl() + Tr())> res(lop.length_x, lop.length_y);

//     res.delete_null_elements();
//     return res;
// }