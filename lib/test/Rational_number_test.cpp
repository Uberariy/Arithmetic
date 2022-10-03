/**
 * @file Rational_number_constructor_test.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-10-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../Rational_number.hpp"
#include "gtest/gtest.h"

class Rational_number_constructor_test:public testing::Test {};

TEST(Rational_number_constructor_test, constructor_null) {
    Rational_number rational(0);
    ASSERT_EQ(rational.get_numerator(), 0) << "Wrong numerator, got " << rational.get_numerator();
    ASSERT_EQ(rational.get_denominator(), 1) << "Wrong denominator, got " << rational.get_denominator();
    
    ASSERT_ANY_THROW(Rational_number(1, 0));
    ASSERT_ANY_THROW(Rational_number(0, 0));
}

TEST(Rational_number_constructor_test, constructor_int) {
    Rational_number rational(10);
    rational.set_denominator(2);
    ASSERT_EQ(rational.get_numerator(), 5) << "Wrong numerator, got " << rational.get_numerator();
    ASSERT_EQ(rational.get_denominator(), 1) << "Wrong denominator, got " << rational.get_denominator();

    rational = Rational_number(1, 10);
    rational.set_numerator(2);
    ASSERT_EQ(rational.get_numerator(), 1) << "Wrong numerator, got " << rational.get_numerator();
    ASSERT_EQ(rational.get_denominator(), 5) << "Wrong denominator, got " << rational.get_denominator();
}

TEST(Rational_number_constructor_test, constructor_long) {
    Rational_number rational(LONG_MAX);
    ASSERT_EQ(rational.get_numerator(), LONG_MAX) << "Wrong numerator, got " << rational.get_numerator();
    ASSERT_EQ(rational.get_denominator(), 1) << "Wrong denominator, got " << rational.get_denominator();

    rational = Rational_number(LONG_MAX, 3);
    ASSERT_EQ(rational.get_numerator(), LONG_MAX) << "Wrong numerator, got " << rational.get_numerator();
    ASSERT_EQ(rational.get_denominator(), 3) << "Wrong denominator, got " << rational.get_denominator();
}

TEST(Rational_number_constructor_test, constructor_llong) {
    Rational_number rational(LLONG_MAX);
    ASSERT_EQ(rational.get_numerator(), LLONG_MAX) << "Wrong numerator, got " << rational.get_numerator();
    ASSERT_EQ(rational.get_denominator(), 1) << "Wrong denominator, got " << rational.get_denominator();

    rational = Rational_number(LLONG_MAX, 3);
    ASSERT_EQ(rational.get_numerator(), LLONG_MAX) << "Wrong numerator, got " << rational.get_numerator();
    ASSERT_EQ(rational.get_denominator(), 3) << "Wrong denominator, got " << rational.get_denominator();
}

TEST(Rational_number_constructor_test, constructor_float) {
    Rational_number rational(0.1);
    ASSERT_EQ(rational.get_numerator(), 1) << "Wrong numerator, got " << rational.get_numerator();
    ASSERT_EQ(rational.get_denominator(), 10) << "Wrong denominator, got " << rational.get_denominator();

    rational = Rational_number(0.333);
    ASSERT_EQ(rational.get_numerator(), 333) << "Wrong numerator, got " << rational.get_numerator();
    ASSERT_EQ(rational.get_denominator(), 1000) << "Wrong denominator, got " << rational.get_denominator();
}

TEST(Rational_number_constructor_test, constructor_string) {
    Rational_number rational("0.1");
    ASSERT_EQ(rational.get_numerator(), 1) << "Wrong numerator, got " << rational.get_numerator();
    ASSERT_EQ(rational.get_denominator(), 10) << "Wrong denominator, got " << rational.get_denominator();

    rational = Rational_number("0.333");
    ASSERT_EQ(rational.get_numerator(), 333) << "Wrong numerator, got " << rational.get_numerator();
    ASSERT_EQ(rational.get_denominator(), 1000) << "Wrong denominator, got " << rational.get_denominator();

    rational = Rational_number("1", "10");
    ASSERT_EQ(rational.get_numerator(), 1) << "Wrong numerator, got " << rational.get_numerator();
    ASSERT_EQ(rational.get_denominator(), 10) << "Wrong denominator, got " << rational.get_denominator();

    rational = Rational_number("10", "30");
    ASSERT_EQ(rational.get_numerator(), 1) << "Wrong numerator, got " << rational.get_numerator();
    ASSERT_EQ(rational.get_denominator(), 3) << "Wrong denominator, got " << rational.get_denominator();

    rational = Rational_number("-10 /   30");
    ASSERT_EQ(rational.get_numerator(), -1) << "Wrong numerator, got " << rational.get_numerator();
    ASSERT_EQ(rational.get_denominator(), 3) << "Wrong denominator, got " << rational.get_denominator();

    rational = Rational_number("1 / 6");
    ASSERT_EQ(rational.get_numerator(), 1) << "Wrong numerator, got " << rational.get_numerator();
    ASSERT_EQ(rational.get_denominator(), 6) << "Wrong denominator, got " << rational.get_denominator();

    rational = Rational_number("-6");
    ASSERT_EQ(rational.get_numerator(), -6) << "Wrong numerator, got " << rational.get_numerator();
    ASSERT_EQ(rational.get_denominator(), 1) << "Wrong denominator, got " << rational.get_denominator();

    ASSERT_ANY_THROW(Rational_number("1 / -6"));
    ASSERT_ANY_THROW(Rational_number("---1 / 6"));
    ASSERT_ANY_THROW(Rational_number("0 / 0"));
    ASSERT_ANY_THROW(Rational_number("1 / 0"));
    ASSERT_ANY_THROW(Rational_number("."));
    ASSERT_ANY_THROW(Rational_number("/"));
}

class Rational_number_operator_test:public testing::Test {};

TEST(Rational_number_operator_test, operator_div_mult) {
    Rational_number rational1(0.1);
    Rational_number rational2(0);
    Rational_number rational3;

    ASSERT_ANY_THROW(rational1 / rational2);

    rational3 = rational1 * rational2;
    ASSERT_EQ(rational3.get_numerator(), 0) << "Wrong numerator, got " << rational3.get_numerator();
    ASSERT_EQ(rational3.get_denominator(), 1) << "Wrong denominator, got " << rational3.get_denominator();

    rational2 = Rational_number(1, 3);
    rational3 = rational1 / rational2;
    ASSERT_EQ(rational3.get_numerator(), 3) << "Wrong numerator, got " << rational3.get_numerator();
    ASSERT_EQ(rational3.get_denominator(), 10) << "Wrong denominator, got " << rational3.get_denominator();

    rational2 = Rational_number(1, 3);
    rational3 = rational1;
    rational3 *= rational2;
    ASSERT_EQ(rational3.get_numerator(), 1) << "Wrong numerator, got " << rational3.get_numerator();
    ASSERT_EQ(rational3.get_denominator(), 30) << "Wrong denominator, got " << rational3.get_denominator();

    rational3 /= rational2;
    ASSERT_EQ(rational3.get_numerator(), 1) << "Wrong numerator, got " << rational3.get_numerator();
    ASSERT_EQ(rational3.get_denominator(), 10) << "Wrong denominator, got " << rational3.get_denominator();
}

TEST(Rational_number_operator_test, operator_additive) {
    Rational_number rational1(0.1);
    Rational_number rational2(0);
    Rational_number rational3;

    rational3 = rational1 + rational2;
    ASSERT_EQ(rational3.get_numerator(), 1) << "Wrong numerator, got " << rational3.get_numerator();
    ASSERT_EQ(rational3.get_denominator(), 10) << "Wrong denominator, got " << rational3.get_denominator();

    rational3 = -rational1;
    ASSERT_EQ(rational3.get_numerator(), -1) << "Wrong numerator, got " << rational3.get_numerator();
    ASSERT_EQ(rational3.get_denominator(), 10) << "Wrong denominator, got " << rational3.get_denominator();

    rational3 = -(-rational3);
    ASSERT_EQ(rational3.get_numerator(), -1) << "Wrong numerator, got " << rational3.get_numerator();
    ASSERT_EQ(rational3.get_denominator(), 10) << "Wrong denominator, got " << rational3.get_denominator();

    rational3 = +rational3;
    ASSERT_EQ(rational3.get_numerator(), -1) << "Wrong numerator, got " << rational3.get_numerator();
    ASSERT_EQ(rational3.get_denominator(), 10) << "Wrong denominator, got " << rational3.get_denominator();

    rational2 = Rational_number(1, 3);
    rational3 = rational1;
    rational3 += rational2;
    ASSERT_EQ(rational3.get_numerator(), 13) << "Wrong numerator, got " << rational3.get_numerator();
    ASSERT_EQ(rational3.get_denominator(), 30) << "Wrong denominator, got " << rational3.get_denominator();

    rational3 = rational3 + rational2;
    ASSERT_EQ(rational3.get_numerator(), 23) << "Wrong numerator, got " << rational3.get_numerator();
    ASSERT_EQ(rational3.get_denominator(), 30) << "Wrong denominator, got " << rational3.get_denominator();

    rational3 = rational3 - rational2;
    ASSERT_EQ(rational3.get_numerator(), 13) << "Wrong numerator, got " << rational3.get_numerator();
    ASSERT_EQ(rational3.get_denominator(), 30) << "Wrong denominator, got " << rational3.get_denominator();

    rational3 -= rational2;
    ASSERT_EQ(rational3.get_numerator(), 1) << "Wrong numerator, got " << rational3.get_numerator();
    ASSERT_EQ(rational3.get_denominator(), 10) << "Wrong denominator, got " << rational3.get_denominator();

    rational3++;
    ASSERT_EQ(rational3.get_numerator(), 11) << "Wrong numerator, got " << rational3.get_numerator();
    ASSERT_EQ(rational3.get_denominator(), 10) << "Wrong denominator, got " << rational3.get_denominator();

    rational3--;
    ASSERT_EQ(rational3.get_numerator(), 1) << "Wrong numerator, got " << rational3.get_numerator();
    ASSERT_EQ(rational3.get_denominator(), 10) << "Wrong denominator, got " << rational3.get_denominator();
}

TEST(Rational_number_operator_test, operator_comparator) {
    Rational_number rational1(1, 6);
    Rational_number rational2(1, 3);
    Rational_number rational3(1, 2);

    ASSERT_TRUE(rational1 < rational2);
    ASSERT_TRUE(rational1 <= rational2);
    ASSERT_TRUE(rational1 != rational2);
    ASSERT_FALSE(rational1 > rational2);
    ASSERT_FALSE(rational1 >= rational2);
    ASSERT_FALSE(rational1 == rational2);

    ASSERT_FALSE(rational1 + rational2 < rational3);
    ASSERT_TRUE(rational1 + rational2 <= rational3);
    ASSERT_TRUE(rational1 + rational2 == rational3);
    ASSERT_FALSE(rational1 + rational2 > rational3);
    ASSERT_TRUE(rational1 + rational2 >= rational3);
    ASSERT_FALSE(rational1 + rational2 != rational3);
}