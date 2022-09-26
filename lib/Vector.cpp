/**
 * @file Vector.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Vector.hpp"

template<typename T>
std::ostream& operator<<(std::ostream& os, Vector<T> const& op) {
    os << op.to_string();
    return os;
}

template<typename T>
std::istream& operator>>(std::istream& is, Vector<T>& op) { // To be done



    return is;
}