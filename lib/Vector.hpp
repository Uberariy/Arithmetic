/**
 * @file Vector.hpp
 * @author Uberariy
 * @brief Vector class header
 * @version 0.1
 * @date 2022-09-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef ARITHMETIC_VECTOR_
#define ARITHMETIC_VECTOR_

#include <map>
#include <set>
#include <fstream>
#include <sstream>

#include "Rational_number.hpp"

/**
 * @brief Vector class implementation
 * 
 * @tparam T 
 */
template<typename T>
class Vector {
public:
    /**
     * @brief Construct a new Vector object. If user wants, constructor can fill vector with a certain value
     * (This constructor answers constructor for zeros and ones task condition)
     * 
     * @param length_ 
     * @param epsilon_tresh_ 
     * @param fill_all 
     * @param start_value_all 
     */
    Vector(unsigned long long length_ = default_length,
           double epsilon_tresh_ = default_epsilon_tresh,
           bool fill_all = true,
           T start_value_all = 0):
           length(length_), epsilon_tresh(epsilon_tresh_) {
        if (fill_all) {
            unsigned long long key;
            for (key = 1; key < length_ + 1; key++) {
                data_map[key] = start_value_all;
            }
            delete_null_elements();
        }
    }

    /**
     * @brief Output a string repr of a vector
     * 
     * @tparam Ti 
     * @param os 
     * @param op 
     * @return std::ostream& 
     */
    template<typename Ti>
    friend std::ostream& operator<<(std::ostream& os, Vector<Ti> const& op);
    
    /**
     * @brief Parse vector from a file
     * 
     * @tparam Ti 
     * @param is 
     * @param op 
     * @return std::istream& 
     */
    template<typename Ti>
    friend std::istream& operator>>(std::istream& is, Vector<Ti>& op);

    /**
     * @brief Set the epsilon tresh object
     * 
     * @param op 
     */
    void set_epsilon_tresh(double& op) {
        epsilon_tresh = op;
    }

    /**
     * @brief Set the length object
     * 
     * @param op 
     */
    void set_length(unsigned long long& op) {
        length = op;
    }

    /**
     * @brief Get the epsilon tresh object
     * 
     * @return double 
     */
    double get_epsilon_tresh() {
        return epsilon_tresh;
    }

    /**
     * @brief Get the length object
     * 
     * @return unsigned long long 
     */
    unsigned long long get_length() {
        return length;
    }

    /**
     * @brief Convert vector to a string
     * 
     * @return std::string 
     */
    std::string to_string() const {
        std::stringstream ss;
        ss << "vector \t" << typeid(T).name() << " \t" << length << "\n";
        for (auto [key, val]: data_map) {
            ss << "\n" << key << "\t" << val;
        }
        ss << "\n";
        return ss.str();
    }

private:

    /**
     * @brief The treshhold, that limits miserability of matrix element
     * 
     */
    double epsilon_tresh;

    /**
     * @brief The treshhold, that limits miserability of matrix element
     * Default version
     */
    static constexpr double default_epsilon_tresh = 0.000001;

    /**
     * @brief Vector can contain less elements, than length, but it is constraint on max size
     * 
     */
    unsigned long long length;

    static constexpr unsigned long long default_length = 10;

    std::map<unsigned long long, T> data_map;

    Vector& delete_null_elements() {
        std::set<unsigned long long> null_keys;
        for (auto [key, val]: data_map) {
            if (((long double)val < epsilon_tresh) && 
                ((long double)val > -epsilon_tresh))
                null_keys.insert(key);
        } 
        for (const int &key : null_keys) {
            data_map.erase(key);
        }
        return *this;
    }

};

#endif