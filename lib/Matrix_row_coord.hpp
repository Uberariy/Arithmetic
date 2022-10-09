/**
 * @file Matrix_row_coord.hpp
 * @author Uberariy
 * @brief Matrix row coord header
 * @version 0.1
 * @date 2022-10-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef ARITHMETIC_MATRIX_ROW_COORD_
#define ARITHMETIC_MATRIX_ROW_COORD_

#include "Matrix_coords.hpp"

/**
 * @brief Class, that determines, that we are in row namespace
*/
class Matrix_row_coord {
public:

    Matrix_row_coord() : row_idx(0) {}

    Matrix_row_coord(unsigned long long idx_) : row_idx(idx_) {}

    unsigned long long get_row_idx() {
        return row_idx;
    }

    void set_row_idx(unsigned long long idx_) {
        row_idx = idx_;
    }

private:
    /**
     * @brief Index of a row
    */
    unsigned long long row_idx;
};

#endif