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

    /**
     * @brief Construct a new Matrix_column_coord object
     * 
     */
    Matrix_column_coord() : column_idx(0) {}

    /**
     * @brief Construct a new Matrix_column_coord object
     * 
     * @param idx_ 
     */
    Matrix_column_coord(unsigned long long idx_) : column_idx(idx_) {}

    /**
     * @brief Get the column idx object
     * 
     * @return unsigned long long 
     */
    unsigned long long get_column_idx() const {
        return column_idx;
    }

    /**
     * @brief Set the column idx object
     * 
     * @param idx_ 
     */
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