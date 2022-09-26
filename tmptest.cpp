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
#include "lib/Rational_number.cpp"
#include "lib/Vector.cpp"

int main() {
    // Rational_number a1(10);
    // Rational_number a2(10, 2);
    // Rational_number a3("15 ", " 2");
    // Rational_number a4(" +20 /    2");

    // short i1 = 10;
    // char i2 = 10;
    // int i3 = 10;
    // long long int i4 = 10;

    // Rational_number a5(i1), a6(i2), a7(i3), a8(i4), a9;

    // std::string b(a1);
    // std::cout << a5 << "\n" << a6 << "\n" << a7 << "\n" << a8 << "\n";

    // std::string s;
    // std::cin >> s;
    // a9 = s;
    // std::cout << a9 << "\n";
    // a9 = s.c_str();
    // std::cout << a9 << "\n";

    Rational_number a10 = 20l;
    a10 *= Rational_number(1, 4);
    a10 += SHRT_MAX * 2;
    a10++;

    Rational_number a12 = Rational_number(SHRT_MIN);
    a12.make_canonical();
    // std::cout << a10 << "\n" << short(a10) << "\n" << a12 << "\n" << (Rational_number(SHRT_MIN) < a10) << "\n";
    Rational_number a11(1, 4);
    std::cout << a11.round() << "\t" << a11.floor() << "\t" << (a11 + a11).round() << "\t" << (a11 + a11).floor() << "\n";

    Vector<int> v(5, 0.001, true, a10);
    std::cout << v;

    return 0;
}