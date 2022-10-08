/**
 * @file Matrix.hpp
 * @author Uberariy
 * @brief Matrix header
 * @version 0.1
 * @date 2022-10-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef ARITHMETIC_MATRIX_
#define ARITHMETIC_MATRIX_

#include <map>
#include <set>
#include <fstream>
#include <sstream>

#include "Matrix_coords.hpp"
#include "Rational_number.hpp"

/**
 * @brief 
 * 
 * @tparam TValue type of stored objects
 */
template<typename T>
class Matrix {
public:
    /**
     * @brief Construct a new Matrix object. Creates a diagonal-ones matrix
     * 1 0 0 0
     * 0 1 0 0
     * 0 0 1 0
     * 0 0 0 1
     * 
     */
    Matrix():
           length_x(default_length_x), 
           length_y(default_length_y), 
           epsilon_tresh(default_epsilon_tresh) {
        unsigned long long key_x;
        std::cout << std::min(default_length_x, default_length_y);
        for (key_x = 1; key_x < std::min(default_length_x, default_length_y) + 1; key_x++) {
            data[std::pair<unsigned long long, unsigned long long>(key_x, key_x)] = 1;
        }
        delete_null_elements();
    }

    /**
     * @brief Construct a new Matrix object. If user wants, constructor can fill vector with a certain value
     * (This constructor answers constructor for zeros and ones task condition!)
     * 
     * @param length_ 
     * @param epsilon_tresh_ 
     * @param fill_all 
     * @param start_value_all 
     */
    Matrix(unsigned long long length_x_,
           unsigned long long length_y_,
           double epsilon_tresh_ = default_epsilon_tresh,
           bool fill_all = false,
           T start_value_all = 0):
           length_x(length_x_), 
           length_y(length_y_), 
           epsilon_tresh(epsilon_tresh_) {
        if (fill_all) {
            unsigned long long key_x, key_y;
            for (key_x = 1; key_x < length_x_ + 1; key_x++) {
                for (key_y = 1; key_y < length_y_ + 1; key_y++) {
                    data[std::pair<unsigned long long, unsigned long long>(key_x, key_y)] = start_value_all;
                }
            }
            delete_null_elements();
        }
    }

    /**
     * Access operator.
     *
     * @param x Pos of required element on x axis.
     * @param y Pos of required element on y axis.
     * @return element of this Matrix on position pos.
     */
    T& operator()(const unsigned long long& x, const unsigned long long& y) {
        delete_null_elements();
        std::pair<unsigned long long, unsigned long long> pos(x, y);
        if ((x > length_x) || (y > length_y)) {
            throw IndexOutOfRangeException("Index is out of range");
        }
        // if (data.find(pos) == data.end()) {
        //     data[pos] = T(0);
        // }
        return data[pos];
    }

    template<typename Tl, typename Tr>
    friend bool operator==(const Matrix<Tl> &lop, const Matrix<Tr> &rop);

    template<typename Tl, typename Tr>
    friend bool operator!=(const Matrix<Tl> &lop, const Matrix<Tr> &rop);

    template<typename Tl, typename Tr>
    friend auto operator-(const Matrix<Tl> &lop, const Matrix<Tr> &rop);

    template<typename Tl, typename Tr>
    friend auto operator+(const Matrix<Tl> &lop, const Matrix<Tr> &rop);

    // template<typename Tl, typename Tr>
    // friend auto operator*(Matrix<Tl> lop, Matrix<Tr> rop);

    template<typename Tl, typename Tr>
    friend auto operator+(Matrix<Tl> lop, const Tr& rop);

    template<typename Tl, typename Tr>
    friend auto operator-(Matrix<Tl> lop, const Tr& rop);

    template<typename Tl, typename Tr>
    friend auto operator*(Matrix<Tl> lop, const Tr& rop);

    template<typename Tl, typename Tr>
    friend auto operator/(Matrix<Tl> lop, const Tr& rop);

    void set_epsilon_tresh(double& op) {
        epsilon_tresh = op;
    }

    void set_length_x(unsigned long long& op) {
        length_x = op;
    }

    void set_length_y(unsigned long long& op) {
        length_y = op;
    }

    double get_epsilon_tresh() {
        return epsilon_tresh;
    }

    unsigned long long get_length_x() {
        return length_x;
    }

    unsigned long long get_length_y() {
        return length_y;
    }

    std::string to_string() const {
        std::stringstream ss;
        ss << "matrix " << typeid(T).name() << " " << length_x << " " << length_y << "\n";
        for (auto [key, val]: data) {
            ss << "\n" << key.first << "\t" << key.second << "\t" << val;
        }
        ss << "\n";
        return ss.str();
    }

private:

    double epsilon_tresh;

    static constexpr double default_epsilon_tresh = 0.000001;

    unsigned long long length_x;

    static constexpr unsigned long long default_length_x = 5;

    unsigned long long length_y;

    static constexpr unsigned long long default_length_y = 5;

    std::map<std::pair<unsigned long long, unsigned long long>, T> data;

    Matrix& delete_null_elements() {
        std::set<std::pair<unsigned long long, unsigned long long>> null_keys;
        for (auto [key, val]: data) {
            if (((long double)val < epsilon_tresh) && 
                ((long double)val > -epsilon_tresh))
                null_keys.insert(key);
        } 
        for (const std::pair<unsigned long long, unsigned long long> &key : null_keys) {
            data.erase(key);
        }
        return *this;
    }

};

template <typename T>
std::ostream& operator<<(std::ostream& os, Matrix<T> const& op);

template <typename T>
std::istream& operator>>(std::istream& is, Matrix<T>& op);

#endif