/**
 * @file exceptions.hpp
 * @author your name (you@domain.com)
 * @brief File, containing library exceptions
 * @version 0.1
 * @date 2022-09-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef ARITHMETIC_EXCEPT_
#define ARITHMETIC_EXCEPT_

#include <exception>
#include <string>

/**
 * @brief Exception thrown on division by zero.
 * 
 */
class DivisionByZeroException :std::exception {
private:
    const char* message;

public:
    DivisionByZeroException() : message("Division by zero is forbidden") {}
    explicit DivisionByZeroException(const char* msg) : message(msg) {}
    explicit DivisionByZeroException(const std::string& msg) : message(msg.c_str()) {}
    const char* what () {
        return message;
    }
};

/**
 * @brief Exception thrown on undivided type overflow.
 * 
 */
class UndividedTypeOverflowException :std::exception {
private:
    const char* message;

public:
    UndividedTypeOverflowException() : message("This operation causes aimed type overflow!") {}
    explicit UndividedTypeOverflowException(const char* msg) : message(msg) {}
    explicit UndividedTypeOverflowException(const std::string& msg) : message(msg.c_str()) {}
    const char* what () {
        return message;
    }
};

/**
 * @brief Exception thrown on undivided type overflow.
 * 
 */
class NotUndividedException :std::exception {
private:
    const char* message;

public:
    NotUndividedException() : message("This operation cannot be done, because used type is cannot be divided without a remainder.") {}
    explicit NotUndividedException(const char* msg) : message(msg) {}
    explicit NotUndividedException(const std::string& msg) : message(msg.c_str()) {}
    const char* what () {
        return message;
    }
};

/**
 * @brief Exception, that is thrown when we get wrong type format
 * 
 */
class WrongFormatException :std::exception {
private:
    const char* message;

public:
    WrongFormatException() : message("Got wrong format of some type.") {}
    explicit WrongFormatException(const char* msg) : message(msg) {}
    explicit WrongFormatException(const std::string& msg) : message(msg.c_str()) {}
    const char* what () {
        return message;
    }
};

/**
 * @brief Exception, that is thrown when we are trying to create wrong coordinates
 * 
 */
class CoordinatesMustMakeFigurePositive :std::exception {
private:
    const char* message;

public:
    CoordinatesMustMakeFigurePositive() : message("Left-up corner of coordinates must be lefter and upper than right-bottom corner.") {}
    explicit CoordinatesMustMakeFigurePositive(const char* msg) : message(msg) {}
    explicit CoordinatesMustMakeFigurePositive(const std::string& msg) : message(msg.c_str()) {}
    const char* what () {
        return message;
    }
};

/**
 * @brief Exception, that is thrown when we are trying to access inaccessable element in a matrix
 * 
 */
class IndexOutOfRangeException :std::exception {
private:
    const char* message;

public:
    IndexOutOfRangeException() : message("Index is out of range.") {}
    explicit IndexOutOfRangeException(const char* msg) : message(msg) {}
    explicit IndexOutOfRangeException(const std::string& msg) : message(msg.c_str()) {}
    const char* what () {
        return message;
    }
};

#endif