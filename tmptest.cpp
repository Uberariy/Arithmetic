/**
 * @file tmptest.cpp
 * @author Ubeariy (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <vector>
#include "lib/Rational_number.cpp"
#include "lib/Vector.cpp"
#include "lib/Matrix.cpp"

int main() {
    // Rational_number a1(1, 10);
    // Rational_number a2(1, 10);

    // std::cout << a1 << "\n" << (long double)(a1) << "\n";

    // Rational_number rational1(1, 6);
    // Rational_number rational2(1, 3);

    // Vector<Rational_number> v(5, 0.001, true, Rational_number(10, 30));
    // auto b = rational2 + rational1 > Rational_number(1, 2);
    // std::cout << b;

    // Matrix<Rational_number> A(5, 5, 0.001, true, 10);
    // std::cout << A;

    Matrix<Rational_number> A;
    A(2, 3) = 4;
    A = A * 2 / 3;
    std::cout << A;



    return 0;
}