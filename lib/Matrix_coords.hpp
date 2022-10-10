/**
 * @file Matrix_coords.hpp
 * @author Uberariy
 * @brief Header containing matrix coordinates
 * @version 0.1
 * @date 2022-10-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef ARITHMETIC_MATRIX_COORDS_
#define ARITHMETIC_MATRIX_COORDS_

#include <tuple>

#include "except/exceptions.hpp"

/**
 * @brief Matrix coordinates class
 */
class Matrix_coords {
public:

    /**
     * @brief Construct a new Matrix_coords object - default constructor
     * If all of the coordinates equal -1, then we wan to take the whole matrix child
     */
    Matrix_coords(): r_bot_x(-1), r_bot_y(-1), l_top_x(-1), l_top_y(-1) {}

    /**
     * @brief Construct a new Matrix_coords object, both coordinates are equal, meaning
     * we want to get [1, 1] matrix
     * 
     * @param r_bot_x_ 
     * @param r_bot_y_ 
     */
    explicit Matrix_coords(long long r_bot_x_, long long r_bot_y_): 
    r_bot_x(r_bot_x_), r_bot_y(r_bot_y_), l_top_x(r_bot_x_), l_top_y(r_bot_y_) {
        check_coords();
    }

    /**
     * @brief Construct a new Matrix_coords object
     * 
     * @param r_bot_x_ 
     * @param r_bot_y_ 
     * @param l_top_x_ 
     * @param l_top_y_ 
     */
    explicit Matrix_coords(long long l_top_x_, long long l_top_y_,
                           long long r_bot_x_, long long r_bot_y_): 
    r_bot_x(r_bot_x_), r_bot_y(r_bot_y_), l_top_x(l_top_x_), l_top_y(l_top_y_) {
        check_coords();
    }

    /**
     * @brief Get the l top object
     * 
     * @return std::tuple<long long, long long> 
     */
    std::tuple<long long, long long> get_l_top() const {
        return std::make_tuple(l_top_x, l_top_y);
    }

    /**
     * @brief Get the r bot object
     * 
     * @return std::tuple<long long, long long> 
     */
    std::tuple<long long, long long> get_r_bot() const {
        return std::make_tuple(r_bot_x, r_bot_y);
    }

    /**
     * @brief Set the l top object
     * 
     * @param l_top_x_ 
     * @param l_top_y_ 
     */
    void set_l_top(long long l_top_x_, long long l_top_y_) {
        l_top_x = l_top_x_;
        l_top_y = l_top_y_;
        check_coords();
    }

    /**
     * @brief Set the r bot object
     * 
     * @param r_bot_x_ 
     * @param r_bot_y_ 
     */
    void set_r_bot(long long r_bot_x_, long long r_bot_y_) {
        r_bot_x = r_bot_x_;
        r_bot_y = r_bot_y_;
        check_coords();
    }

    /**
     * @brief Check if figure does not have negative area
     * 
     * @return Rational_number& 
     */
    Matrix_coords& check_coords() {
        if ((r_bot_x < -1) || (r_bot_x == 0) ||
            (r_bot_y < -1) || (r_bot_y == 0) ||
            (l_top_x < -1) || (l_top_x == 0) ||
            (l_top_y < -1) || (l_top_y == 0) ||
            ((r_bot_x < l_top_x) && (r_bot_x != -1)) || 
            ((r_bot_y < l_top_y) && (r_bot_y != -1))) {
            throw CoordinatesMustMakeFigurePositive("Coordinates don't match: " + std::to_string(l_top_x) + ", " + std::to_string(l_top_y) + ", " + std::to_string(r_bot_x) + ", " + std::to_string(r_bot_y) + "; ");
        }
        return *this;
    }
private:
    /**
     * @brief Right bottom corner x axis coordinate
     * 
     */
    long long r_bot_x;

    /**
     * @brief Right bottom corner y axis coordinate
     * 
     */
    long long r_bot_y;

    /**
     * @brief Left top corner x axis coordinate
     * 
     */
    long long l_top_x;

    /**
     * @brief Left top corner y axis coordinate
     * 
     */
    long long l_top_y;
};


#endif