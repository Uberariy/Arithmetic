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
#include <iostream>

#include "Matrix_proxy.hpp"
#include "Matrix_coords.hpp"
#include "Rational_number.hpp"

// template<typename T>
// class Matrix;

/**
 * @brief Matrix class capable of stroing dense matrices
 * 
 * @tparam T type of stored objects
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
     * @brief Construct a new Matrix object
     * 
     * @param in_file 
     * @param epsilon_tresh_ 
     */
    Matrix(const char* in_file,
           double epsilon_tresh_ = default_epsilon_tresh):
           epsilon_tresh(epsilon_tresh_) {
        std::fstream ss_f(in_file);
        ss_f >> *this;
    }

    /**
     * @brief Copy constructor
     *
     * @param rop instance to copy.
     */
    Matrix(Matrix& rop) : length_x(rop.length_x), length_y(rop.length_y), epsilon_tresh(rop.epsilon_tresh), data(rop.data) {}

    /**
     * Matrix destructor
     * It is necessary to mark matrix as deleted in all proxies that point to this matrix while deleting the matrix.
     */
    ~Matrix() {
        for (auto proxy: proxy_set) {
            proxy->deattach();
        }
    }

    /**
     * @brief Add a proxy and link it with this Matrix
     *
     * @param proxy
    */
    void add_proxy(Matrix_proxy<T>* proxy) {
        proxy_set.insert(proxy);
    }

    /**
     * @brief Unlink proxy object with this Matrix
     *
     * @param proxy
     */
    void remove_proxy(Matrix_proxy<T>* proxy) {
        proxy_set.erase(proxy);
    }

    /**
     * @brief Copy operator
     * 
     * @param rop 
     * @return Matrix& 
     */
    Matrix& operator=(const Matrix& rop) {
        Matrix res(rop.length_x, rop.length_y, rop.epsilon_tresh);
        for (auto &[key, val] : rop.data) {
            res.data[key] = rop.data.find(key)->second;
        }
        std::swap(length_x, res.length_x);
        std::swap(length_y, res.length_y);
        std::swap(epsilon_tresh, res.epsilon_tresh);
        std::swap(data, res.data);
        return *this;
    }

    // Matrix& operator=(Matrix&& rop) noexcept {
    //     length_x = std::move(rop.length_x);
    //     rop.length_x = (unsigned long long)(default_length_x);
    //     length_y = std::move(rop.length_y);
    //     rop.length_y = (unsigned long long)(default_length_y);
    //     epsilon_tresh = std::move(rop.epsilon_tresh);
    //     rop.epsilon_tresh = (unsigned long long)(default_epsilon_tresh);
    //     data = std::move(rop.data);
    //     rop.data = {};
    // }

    // Matrix& operator=(std::map<std::pair<unsigned long long, unsigned long long>, T>&& rop) noexcept {
    //     data = std::move(rop);
    //     rop = {};
    // }

    /**
     * @brief Transpose the matrix
     * 
     * @return Matrix 
     */
    Matrix operator~() {
        Matrix res(length_y, length_x);
        for(auto [key, value] : data) {
            std::pair<unsigned long long, unsigned long long> pos(key.second, key.first);
            res.data[pos] = value;
        }
        return res;
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
        // std::cout << "Matrix operator() x: " << x << ", y:" << y << "\n";
        if ((x > length_x) || (y > length_y)) {
            throw IndexOutOfRangeException("Index is out of range");
        }
        // if (data.find(pos) == data.end()) {
        //     data[pos] = T(0);
        // }
        return data[pos];
    }

    /**
     * Slice operator
     *
     * @param coords
     * @return 
     */
    Matrix_proxy<T> operator[](const Matrix_coords& coords) {
        auto [slice_r_bot_x, slice_r_bot_y] = coords.get_r_bot();
        if ((slice_r_bot_x > (long long)length_x) || (slice_r_bot_y > (long long)length_y)) {
            throw IndexOutOfRangeException("Matrix has got you!");
        }
        return Matrix_proxy<T>(this, coords);
    }

    /**
     * Slice operator
     *
     * @param coords
     * @return 
     */
    Matrix_proxy<T> operator[](const Matrix_row_coord& coords) {
        if (coords.get_row_idx() > length_y) {
            throw IndexOutOfRangeException("Matrix has got you!");
        }
        return Matrix_proxy<T>(this, coords);
    }

    /**
     * Slice operator
     *
     * @param coords
     * @return 
     */
    Matrix_proxy<T> operator[](const Matrix_column_coord& coords) {
        if (coords.get_column_idx() > length_x) {
            throw IndexOutOfRangeException("Matrix has got you!");
        }
        return Matrix_proxy<T>(this, coords);
    }

    /**
     * @brief Equality comparator
     * 
     * @tparam Tl 
     * @tparam Tr 
     * @param lop 
     * @param rop 
     * @return true 
     * @return false 
     */
    template<typename Tl, typename Tr>
    friend bool operator==(const Matrix<Tl> &lop, const Matrix<Tr> &rop);

    /**
     * @brief Inequality comparator
     * 
     * @tparam Tl 
     * @tparam Tr 
     * @param lop 
     * @param rop 
     * @return true 
     * @return false 
     */
    template<typename Tl, typename Tr>
    friend bool operator!=(const Matrix<Tl> &lop, const Matrix<Tr> &rop);

    /**
     * @brief Matrix Minus operator
     * 
     * @tparam Tl 
     * @tparam Tr 
     * @param lop 
     * @param rop 
     * @return auto 
     */
    template<typename Tl, typename Tr>
    friend auto operator-(const Matrix<Tl> &lop, const Matrix<Tr> &rop);

    /**
     * @brief Matrix plus operator
     * 
     * @tparam Tl 
     * @tparam Tr 
     * @param lop 
     * @param rop 
     * @return auto 
     */
    template<typename Tl, typename Tr>
    friend auto operator+(const Matrix<Tl> &lop, const Matrix<Tr> &rop);

    // template<typename Tl, typename Tr>
    // friend auto operator*(Matrix<Tl> lop, Matrix<Tr> rop);

    /**
     * @brief Plus operator
     * 
     * @tparam Tl 
     * @tparam Tr 
     * @param lop 
     * @param rop 
     * @return auto 
     */
    template<typename Tl, typename Tr>
    friend auto operator+(Matrix<Tl> lop, const Tr& rop);

    /**
     * @brief Minus operator
     * 
     * @tparam Tl 
     * @tparam Tr 
     * @param lop 
     * @param rop 
     * @return auto 
     */
    template<typename Tl, typename Tr>
    friend auto operator-(Matrix<Tl> lop, const Tr& rop);

    /**
     * @brief Multiplication operator
     * 
     * @tparam Tl 
     * @tparam Tr 
     * @param lop 
     * @param rop 
     * @return auto 
     */
    template<typename Tl, typename Tr>
    friend auto operator*(Matrix<Tl> lop, const Tr& rop);

    /**
     * @brief Division operator
     * 
     * @tparam Tl 
     * @tparam Tr 
     * @param lop 
     * @param rop 
     * @return auto 
     */
    template<typename Tl, typename Tr>
    friend auto operator/(Matrix<Tl> lop, const Tr& rop);

    /**
     * @brief Set the epsilon tresh object
     * 
     * @param op 
     */
    void set_epsilon_tresh(double& op) {
        epsilon_tresh = op;
    }

    /**
     * @brief Set the length x object
     * 
     * @param op 
     */
    void set_length_x(unsigned long long& op) {
        length_x = op;
    }

    /**
     * @brief Set the length y object
     * 
     * @param op 
     */
    void set_length_y(unsigned long long& op) {
        length_y = op;
    }

    /**
     * @brief Get the epsilon tresh object
     * 
     * @return double 
     */
    double get_epsilon_tresh() {
        return epsilon_tresh;
    }

    /**
     * @brief Get the length x object
     * 
     * @return unsigned long long 
     */
    unsigned long long get_length_x() {
        return length_x;
    }

    /**
     * @brief Get the length y object
     * 
     * @return unsigned long long 
     */
    unsigned long long get_length_y() {
        return length_y;
    }

    /**
     * @brief Convert matrix to string
     * 
     * @return std::string 
     */
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

    /**
     * @brief The treshhold, that limits miserability of matrix element
     * 
     */
    double epsilon_tresh;

    /**
     * @brief The treshhold, that limits miserability of matrix element
     * Default version
     */
    static constexpr double default_epsilon_tresh = 0.000001;

    /**
     * @brief Matrix length
     * 
     */
    unsigned long long length_x;

    /**
     * @brief Matrix length
     * Default version
     */
    static constexpr unsigned long long default_length_x = 5;

    /**
     * @brief Matrix width
     * 
     */
    unsigned long long length_y;

    /**
     * @brief Matrix width
     * Default version
     */
    static constexpr unsigned long long default_length_y = 5;

    /**
     * @brief Actual matrix data
     * 
     */
    std::map<std::pair<unsigned long long, unsigned long long>, T> data;

    /**
     * @brief Set of matrix proxies related with this matrix
     * 
     */
    std::set<Matrix_proxy<T>*> proxy_set;

    /**
     * Remove miserable enough elements.
    */
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

/**
 * @brief Output matrix to the out stream
 * 
 * @tparam T 
 * @param os 
 * @param op 
 * @return std::ostream& 
 */
template <typename T>
std::ostream& operator<<(std::ostream& os, Matrix<T> const& op);

/**
 * @brief Parse matrix from a file
 * 
 * @tparam T 
 * @param is 
 * @param op 
 * @return std::istream& 
 */
template <typename T>
std::istream& operator>>(std::istream& is, Matrix<T>& op);

template<typename Tl, typename Tr>
auto operator+(Matrix<Tl> lop, const Tr& rop);

template<typename Tl, typename Tr>
auto operator-(Matrix<Tl> lop, const Tr& rop);

template<typename Tl, typename Tr>
auto operator*(Matrix<Tl> lop, const Tr& rop);

#endif