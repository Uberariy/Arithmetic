/**
 * @file Rational_number.hpp
 * @author Uberariy
 * @brief Rational_number class header
 * @version 0.1
 * @date 2022-09-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef ARITHMETIC_RATIONAL_NUMBER_
#define ARITHMETIC_RATIONAL_NUMBER_

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <numeric>
#include <limits.h>

#include "except/exceptions.hpp"

/**
 * @brief Class, that implements rational numbers
 * 
 */
class Rational_number {
public:
    /**
     * @brief Default constructor
     * 
     */
    Rational_number();

    /**
     * @brief Construct a new Rational_number object
     * 
     * @param op Numerator (denominator gets 1)
     */
    Rational_number(long long int op);
    /**
     * @brief Construct a new Rational_number object
     * 
     * @param lop Numerator
     * @param rop Denominator object
     */
    Rational_number(long long int lop, unsigned long long int rop);

    /**
     * @brief Construct a new Rational_number object
     * 
     * @param op Numerator (denominator gets 1) 
     */
    Rational_number(const char* op);

    /**
     * @brief Construct a new Rational_number object
     * 
     * @param lop Numerator
     * @param rop Denominator object
     */
    Rational_number(const char* lop, const char* rop);

    /**
     * @brief Assignment operator
     * 
     * @param op 
     * @return Rational_number& 
     */
    Rational_number& operator=(const long long int& op);

    /**
     * @brief Assignment operator
     * 
     * @param op 
     * @return Rational_number& 
     */
    Rational_number& operator=(const char* op);

    /**
     * @brief Assignment operator
     * 
     * @param op 
     * @return Rational_number& 
     */
    Rational_number& operator=(std::string op);

    /**
     * @brief Unary plus operator
     * 
     * @return Rational_number 
     */
    Rational_number operator+() const;

    /**
     * @brief Unary minus operator
     * 
     * @return Rational_number 
     */
    Rational_number operator-() const;

    /**
     * @brief Plus & Assigment operator
     * 
     * @param rop 
     * @return Rational_number& 
     */
    Rational_number& operator+=(const Rational_number& rop);

    /**
     * @brief Minus & Assigment operator
     * 
     * @param rop 
     * @return Rational_number& 
     */
    Rational_number& operator-=(const Rational_number& rop);

    /**
     * @brief Multiply & Assigment operator
     * 
     * @param rop 
     * @return Rational_number& 
     */
    Rational_number& operator*=(const Rational_number& rop);

    /**
     * @brief Division & Assigment operator
     * 
     * @param rop 
     * @return Rational_number& 
     */
    Rational_number& operator/=(const Rational_number& rop);

    /**
     * @brief Plus operator
     * 
     * @param op 
     * @return Rational_number 
     */
    Rational_number operator+(const Rational_number& op);

    /**
     * @brief Minus operator
     * 
     * @param op 
     * @return Rational_number 
     */
    Rational_number operator-(const Rational_number& op);

    /**
     * @brief Multiplication operator
     * 
     * @param op 
     * @return Rational_number 
     */
    Rational_number operator*(const Rational_number& op);

    /**
     * @brief Division operator
     * 
     * @param op 
     * @return Rational_number 
     */
    Rational_number operator/(const Rational_number& op);

    /**
     * @brief Incrementation operator
     * 
     * @param op 
     * @return Rational_number& 
     */
    Rational_number& operator++(int op);

    /**
     * @brief Decrementation operator
     * 
     * @param op 
     * @return Rational_number& 
     */
    Rational_number& operator--(int op);

    /**
     * @brief Print Rational_number to std::ostream.
     *
     * @param os output stream
     * @param op Rational_number to print
     * @return std::ostream& 
     */
    friend std::ostream& operator<< (std::ostream& os, Rational_number const& op);

    /**
     * @brief Input Rational_number from std::istream.
     *
     * @param is input stream
     * @param op Rational_number to input
     * @return std::istream& 
     */
    friend std::istream& operator>> (std::istream& is, Rational_number& op);

    /**
     * @brief Comparator: Equality check
     * 
     * @param lop 
     * @param rop 
     * @return true 
     * @return false 
     */
    friend bool operator==(const Rational_number& lop, const Rational_number& rop);

    /**
     * @brief Comparator: Inequality check
     * 
     * @param lop 
     * @param rop 
     * @return true 
     * @return false 
     */
    friend bool operator!=(const Rational_number& lop, const Rational_number& rop);

    /**
     * @brief Yet another comparator
     * 
     * @param lop 
     * @param rop 
     * @return true 
     * @return false 
     */
    friend bool operator<(const Rational_number& lop, const Rational_number& rop);

    /**
     * @brief Yet another comparator
     * 
     * @param lop 
     * @param rop 
     * @return true 
     * @return false 
     */
    friend bool operator>(const Rational_number& lop, const Rational_number& rop);

    /**
     * @brief Yet another comparator
     * 
     * @param lop 
     * @param rop 
     * @return true 
     * @return false 
     */
    friend bool operator<=(const Rational_number& lop, const Rational_number& rop);

    /**
     * @brief Yet another comparator
     * 
     * @param lop 
     * @param rop 
     * @return true 
     * @return false 
     */
    friend bool operator>=(const Rational_number& lop, const Rational_number& rop);

    /**
     * @brief Cast rational number to a string
     * 
     * @return std::string 
     */
    operator std::string() const;

    /**
     * @brief Cast rational number to long long
     * 
     * @return long long 
     */
    operator long long() const;

    /**
     * @brief Cast rational number to long
     * 
     * @return long 
     */
    operator long() const;

    /**
     * @brief Cast rational number to int
     * 
     * @return int 
     */
    operator int() const;

    /**
     * @brief Cast rational number to short
     * 
     * @return short 
     */
    operator short() const;
    
    /**
     * @brief Cast rational number to bool. If numerator is equal to zero => bool is false, elsewise it is true.
     * 
     * @return true 
     * @return false 
     */
    operator bool() const;

    /**
     * @brief Cast rational number to a whole type, removing fractional part
     * 
     * @return Rational_number& 
     */
    Rational_number& floor();

    /**
     * @brief Round the rational number
     * 
     * @return Rational_number& 
     */
    Rational_number& round();

private:
    /**
     * @brief Rational number nominator
     * 
     */
    long long numerator;

    /**
     * @brief Rational number denominator
     * 
     */
    unsigned long long denominator;

    /**
     * @brief Set the numerator object
     * 
     * @param op 
     */
    void set_numerator(const long long int& op);

    /**
     * @brief Set the denominator object
     * 
     * @param op 
     */
    void set_denominator(const long long int& op);

    /**
     * @brief Get the numerator object
     * 
     * @return long long int 
     */
    long long int get_numerator();

    /**
     * @brief Get the denominator object
     * 
     * @return long long int 
     */
    long long int get_denominator();

    /**
     * @brief Cast to undivided type (etc.: int, long, long long, short)
     * 
     * @param type_name is written to an exception in case of a failure
     * @param min minimum amount of signed undivided type
     * @param max maximum amount of signed undivided type
     * @param UTOE throw UndividedTypeOverflowException
     * @param NUE throw NotUndividedException
     * @return long long int 
     */
    long long int cast_to_undivided(const std::string& type_name, const long long int& min, const long long int& max, bool throwUTOE=true, bool throwNUE=true) const;

public:
    /**
     * @brief Cast rational number to a canonical form
     * 
     * @return Rational_number& 
     */
    Rational_number& make_canonical();

};

#endif