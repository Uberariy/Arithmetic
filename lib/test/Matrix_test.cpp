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
}

TEST(Matrix_test, matrix_exception) {
    Matrix<Rational_number> A(5, 5, 0.001, true, Rational_number(1, 10));
    Matrix<Rational_number> B(5, 5, 0.001, true, 1);

    ASSERT_ANY_THROW(A(1000, 0));
    // ASSERT_EQ(rational.get_denominator(), 1) << "Wrong denominator, got " << rational.get_denominator();
    
    // ASSERT_ANY_THROW(Rational_number(1, 0));
    // ASSERT_ANY_THROW(Rational_number(0, 0));
}