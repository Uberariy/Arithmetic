/**
 * @file Matrix_test.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-10-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../Matrix.cpp"
#include "../Rational_number.cpp"
#include "../Matrix_coords.hpp"
#include "gtest/gtest.h"
#include <iostream>

class Matrix_test:public testing::Test {};

TEST(Matrix_test, matrix_constructor_comparator) {
    Matrix<Rational_number> A(5, 5, 0.001, true, Rational_number(1, 10));
    Matrix<Rational_number> C(5, 5, 0.001, true, Rational_number(1, 10));
    Matrix<Rational_number> B(5, 5, 0.001, true, 1);

    ASSERT_TRUE(A == C);
    ASSERT_FALSE(A == B);
    ASSERT_TRUE(A != B);
    ASSERT_FALSE(A != C);
}

TEST(Matrix_test, matrix_operator) {
    Matrix<Rational_number> A(5, 5, 0.001, true, Rational_number(1, 10));
    Matrix<Rational_number> B(5, 5, 0.001, true, 1);

    ASSERT_EQ(A * 10, B);
    ASSERT_EQ(A * 9 + A, B);
    ASSERT_EQ(A, B / 10);
    ASSERT_EQ(A * 11 - A, B);
    ASSERT_EQ(A + Rational_number(9, 10), B);
    ASSERT_EQ(A + 1 - Rational_number(1, 10), B);

    Matrix<Rational_number> C(5, 5, 0.001, true, 0);
    A = A / 10000000;
    ASSERT_EQ(A, C);
    C(1, 1) = 5;
    ASSERT_EQ(A, C / 10000000);
    C(1, 1) = 5;
    A(1, 1) = 0.5;
    ASSERT_EQ(A * 10, C);

    A(2, 3) = 8;
    C(3, 2) = 8;
    ASSERT_EQ(A, ~C);

    ASSERT_ANY_THROW(A(1000, 0));
}

TEST(Matrix_test, matrix_slice) {
    Matrix<Rational_number> A(5, 5, 0.001, true, Rational_number(1, 10));

    Matrix_coords FullCoords(1, -1, -1, 3);
    Matrix_proxy SrezA = A[FullCoords];

    Matrix_column_coord ColCoord(3);
    Matrix_proxy SrezB = A[ColCoord];

    Matrix_row_coord RowCoord(2);
    Matrix_proxy SrezC = A[RowCoord];

    SrezA(4, 3) = Rational_number(1, 3);
    ASSERT_EQ(SrezB(4), Rational_number(1, 3));
    SrezC(3) = Rational_number(2, 3);
    ASSERT_EQ(SrezA(2, 3), Rational_number(2, 3));

    ASSERT_ANY_THROW(SrezA(3, 4));
    ASSERT_ANY_THROW(SrezB(6));
    ASSERT_ANY_THROW(SrezC(6));

    A = Matrix<Rational_number>(1, 1, 0.001, true, Rational_number(1, 10));

    ASSERT_ANY_THROW(SrezA(4, 3));
    ASSERT_ANY_THROW(SrezB(4));
    ASSERT_ANY_THROW(SrezC(3));
}

TEST(Matrix_test, matrix_parser) {
    Matrix<Rational_number> A("input_example/matrix1.txt", 0.001);

    ASSERT_EQ(A(1, 1), Rational_number(100));
    ASSERT_EQ(A(6000, 2), Rational_number(23, 5));
    ASSERT_EQ(A(7, 1), Rational_number(-5, 3));
    ASSERT_EQ(A(22, 1), Rational_number(44, 1));
}