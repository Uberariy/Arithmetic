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

TEST(Matrix_test, matrix_constructor) {
    // Matrix<Rational_number> A(5, 5, 0.001, true, 10);
    Matrix<Rational_number> B;

    B = B * 2;

    // ASSERT_EQ(rational.get_numerator(), 0) << "Wrong numerator, got " << rational.get_numerator();
    // ASSERT_EQ(rational.get_denominator(), 1) << "Wrong denominator, got " << rational.get_denominator();
    
    // ASSERT_ANY_THROW(Rational_number(1, 0));
    // ASSERT_ANY_THROW(Rational_number(0, 0));
}