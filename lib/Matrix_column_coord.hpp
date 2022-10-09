/**
 * @file Matrix_column_coord.hpp
 * @author Uberariy
 * @brief Matrix column coord header
 * @version 0.1
 * @date 2022-10-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef ARITHMETIC_MATRIX_COLUMN_COORD_
#define ARITHMETIC_MATRIX_COLUMN_COORD_

#include "Matrix_coords.hpp"

/**
 * @brief Class, that determines, that we are in column namespace
*/
class Matrix_column_coord {
public:

    Matrix_column_coord() : column_idx(0) {}

    Matrix_column_coord(unsigned long long idx_) : column_idx(idx_) {}

    unsigned long long get_column_idx() {
        return column_idx;
    }

    void set_column_idx(unsigned long long idx_) {
        column_idx = idx_;
    }

private:
    /**
     * @brief Index of a column
    */
    unsigned long long column_idx;
};

#endif