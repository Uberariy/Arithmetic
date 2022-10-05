/**
 * @file Vector.hpp
 * @author Uberariy
 * @brief Vector class header
 * @version 0.1
 * @date 2022-10-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef ARITHMETIC_MATRIX_COORDS_
#define ARITHMETIC_MATRIX_COORDS_

#include <tuple>
#include <except/exceptions.hpp>

/**
 * @brief 
 */
class Matrix_coords {
    Matrix_coords(): r_bot_x(-1), r_bot_y(-1), l_top_x(-1), l_top_y(-1) {}

    explicit Matrix_coords(long long r_bot_x_, long long r_bot_y_): 
    r_bot_x(r_bot_x_), r_bot_y(r_bot_y_), l_top_x(r_bot_x_), l_top_y(r_bot_y_) {
        check_coords();
    }

    explicit Matrix_coords(long long r_bot_x_, long long r_bot_y_,
                           long long l_top_x_, long long l_top_y_): 
    r_bot_x(r_bot_x_), r_bot_y(r_bot_y_), l_top_x(l_top_x_), l_top_y(l_top_y_) {
        check_coords();
    }

    std::tuple<long long, long long> get_l_top() {
        return std::make_tuple(l_top_x, l_top_y);
    }

    std::tuple<long long, long long> get_r_bot() {
        return std::make_tuple(r_bot_x, r_bot_y);
    }

    void set_l_top(long long l_top_x_, long long l_top_y_) {
        l_top_x = l_top_x_;
        l_top_y = l_top_y_;
        check_coords();
    }

    void set_r_bot(long long r_bot_x_, long long r_bot_y_) {
        r_bot_x = r_bot_x_;
        r_bot_y = r_bot_y_;
        check_coords();
    }
private:
    long long r_bot_x;
    long long r_bot_y;
    long long l_top_x;
    long long l_top_y;

    /**
     * @brief Check if figure does not have negative area
     * 
     * @return Rational_number& 
     */
    Matrix_coords& check_coords() {
        if ((r_bot_x < -1) ||
            (r_bot_y < -1) ||
            (l_top_x < -1) ||
            (l_top_y < -1) ||
            ((r_bot_x < l_top_x) && (r_bot_x != -1)) || 
            ((r_bot_y < l_top_y) && (r_bot_y != -1))) {
            throw CoordinatesMustMakeFigurePositive();
        }
        return *this;
    }
};


#endif