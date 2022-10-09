/**
 * @file Matrix_proxy.hpp
 * @author Uberariy
 * @brief Matrix proxy header
 * @version 0.1
 * @date 2022-10-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef ARITHMETIC_MATRIX_PROXY_
#define ARITHMETIC_MATRIX_PROXY_

#include "Matrix_column_coord.hpp"
#include "Matrix_row_coord.hpp"
#include "Matrix_coords.hpp"

enum class Matrix_proxy_type {
    ROW,
    COLUMN,
    FULL,
};

/**
 * @brief Matrix class capable of stroing dense matrices
 * 
 * @tparam TValue type of stored objects
 */
template<typename T>
class Matrix_proxy {
public:

    Matrix_proxy(Matrix<T>* matrixptr_, Matrix_row_coord coords) : 
        matrixptr(matrixptr_), proxy_type(Matrix_proxy_type::ROW),
        slice_coords(1, coords.get_row_idx(), matrixptr_->get_length_x(), coords.get_row_idx()) {
        matrixptr->add_proxy(this);
    }

    Matrix_proxy(Matrix<T>* matrixptr_, Matrix_column_coord coords) : 
        matrixptr(matrixptr_), proxy_type(Matrix_proxy_type::COLUMN),
        slice_coords(coords.get_column_idx(), 1, coords.get_column_idx(), matrixptr_->get_length_y()) {
        matrixptr->add_proxy(this);
    }

    Matrix_proxy(Matrix<T>* matrixptr_, Matrix_coords coords) : 
        matrixptr(matrixptr_), proxy_type(Matrix_proxy_type::FULL) {
        matrixptr->add_proxy(this);
        auto [slice_l_top_x, slice_l_top_y] = coords.get_l_top();
        auto [slice_r_bot_x, slice_r_bot_y] = coords.get_r_bot();
        if (slice_l_top_x == -1) {
            slice_l_top_x = 1;
        }
        if (slice_l_top_y == -1) {
            slice_l_top_y = 1;
        }
        if (slice_r_bot_x == -1) {
            slice_r_bot_x = matrixptr->get_length_x();
        }
        if (slice_r_bot_y == -1) {
            slice_r_bot_y = matrixptr->get_length_y();
        }
        slice_coords 
    }

    ~Matrix_proxy() {
        if (matrixptr != nullptr) {
            matrixptr->remove_proxy(this);
        }
    }
    
    /**
     * @brief Matrix is destroyed => Unlink it
     */
    void deattach() {
        matrixptr = nullptr;
    }

    /**
     * @brief Get element of the slice
     * 
     * @param x_
     * @param y_
     */
    T& operator()(const long long x_, const long long y_) {
        auto [slice_l_top_x, slice_l_top_y] = slice_coords.get_l_top();
        auto [slice_r_bot_x, slice_r_bot_y] = slice_coords.get_r_bot();
        if ((slice_l_top_x + x_ < slice_r_bot_x) || (slice_l_top_y + y_ < slice_r_bot_y)) {
            throw IndexOutOfRangeException('Index is out of slice!');
        }
        return operator()(slice_l_top_x + x_, slice_l_top_y + y_);
    }

    /**
     * @brief Get element of the slice in a one-dimension case
     * 
     * @param idx_
     */
    T& operator()(const long long idx_) {
        auto [slice_l_top_x, slice_l_top_y] = slice_coords.get_l_top();
        auto [slice_r_bot_x, slice_r_bot_y] = slice_coords.get_r_bot();
        if (proxy_type == Matrix_proxy_type::FULL) {
            throw IndexOutOfRangeException('Cannot access a rectangle slice this way!');
        } else if (proxy_type == Matrix_proxy_type::COLUMN) {
            if (slice_l_top_y + idx < slice_r_bot_y) {
                throw IndexOutOfRangeException('Index is out of slice (column case)!');
            }
            return operator()(slice_l_top_x, slice_l_top_y + idx_);
        } else if (proxy_type == Matrix_proxy_type::ROW) {
            if (slice_l_top_x + idx < slice_r_bot_x) {
                throw IndexOutOfRangeException('Index is out of slice (row case)!');
            }
            return operator()(slice_l_top_x + idx_, slice_l_top_y);
        }
    }



private:
    /**
     * @brief Matrix pointer
     */
    Matrix<T>* matrixptr;

    /**
     * @brief slice borders; Here we already change -1 border to lower or upper matrix elem
    */
    Matrix_coords slice_coords;

    /**
     * @brief whether we treat matrix as a vector or retreat
    */
    Matrix_proxy_type proxy_type;

};


#endif