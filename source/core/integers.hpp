/*!
 * @file        integers.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Integers class.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2023 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_INTEGERS_HPP
#define CELL_INTEGERS_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Types)

/**
 * The BigNumber, BigNumber64, and BigNumber128 classes in your program are designed to work with large numbers with customizable precision.
 * These classes represent arbitrary-precision integers and provide mathematical operations such as addition, subtraction, and multiplication on these numbers.
 * The BigNumber class is used for working with large numbers with custom precision and uses the long long int data type to store the numbers.
 * The BigNumber64 class represents 64-bit precision large numbers and uses the Types::u64 data type to store the numbers.
 * The BigNumber128 class is used to represent large numbers with 128-bit precision and uses the Types::u128 data type for storing the numbers.
 * Each class provides similar mathematical operations, including addition, subtraction, multiplication, and comparison of numbers.
 * They can also convert the numbers to string representation and allow modifying the values of the numbers using appropriate operators.
 **/

/**
 * @class BigNumber
 * @brief A class for handling arbitrary precision numbers.
 */
class __cell_export BigNumber
{
public:
    /**
     * @brief Default constructor for BigNumber.
     */
    BigNumber();

    /**
     * @brief Constructor for BigNumber that takes a string representation of a number.
     * @param number The string representation of the number.
     */
    BigNumber(const std::string& number);

    /**
     * @brief Constructor for BigNumber that takes a long long int.
     * @param number The long long int value.
     */
    BigNumber(Types::llong number);

    /**
     * @brief Converts the BigNumber to a string representation.
     * @return The string representation of the BigNumber.
     */
    __cell_no_discard Types::OptionalString toString() const;

    /**
     * @brief Adds two BigNumber objects.
     * @param other The other BigNumber to add.
     * @return The sum of the two BigNumber objects.
     */
    BigNumber operator+(const BigNumber& other) const;

    /**
     * @brief Subtracts two BigNumber objects.
     * @param other The other BigNumber to subtract.
     * @return The difference of the two BigNumber objects.
     */
    BigNumber operator-(const BigNumber& other) const;

    /**
     * @brief Multiplies two BigNumber objects.
     * @param other The other BigNumber to multiply.
     * @return The product of the two BigNumber objects.
     */
    BigNumber operator*(const BigNumber& other) const;

    /**
     * @brief Checks if the BigNumber is equal to another BigNumber.
     * @param other The other BigNumber to compare.
     * @return True if the BigNumber objects are equal, false otherwise.
     */
    bool operator==(const BigNumber& other) const;

    /**
     * @brief Checks if the BigNumber is not equal to another BigNumber.
     * @param other The other BigNumber to compare.
     * @return True if the BigNumber objects are not equal, false otherwise.
     */
    bool operator!=(const BigNumber& other) const;

    /**
     * @brief Checks if the BigNumber is less than another BigNumber.
     * @param other The other BigNumber to compare.
     * @return True if the BigNumber is less than the other BigNumber, false otherwise.
     */
    bool operator<(const BigNumber& other) const;

    /**
     * @brief Checks if the BigNumber is less than or equal to another BigNumber.
     * @param other The other BigNumber to compare.
     * @return True if the BigNumber is less than or equal to the other BigNumber, false otherwise.
     */
    bool operator<=(const BigNumber& other) const;

    /**
     * @brief Checks if the BigNumber is greater than another BigNumber.
     * @param other The other BigNumber to compare.
     * @return True if the BigNumber is greater than the other BigNumber, false otherwise.
     */
    bool operator>(const BigNumber& other) const;

    /**
     * @brief Checks if the BigNumber is greater than or equal to another BigNumber.
     * @param other The other BigNumber to compare.
     * @return True if the BigNumber is greater than or equal to the other BigNumber, false otherwise.
     */
    bool operator>=(const BigNumber& other) const;

    /**
     * @brief Negates the BigNumber.
     * @return The negated BigNumber.
     */
    BigNumber operator-() const;

    /**
     * @brief Adds another BigNumber to the current BigNumber.
     * @param other The other BigNumber to add.
     * @return The reference to the modified current BigNumber.
     */
    BigNumber& operator+=(const BigNumber& other);

    /**
     * @brief Subtracts another BigNumber from the current BigNumber.
     * @param other The other BigNumber to subtract.
     * @return The reference to the modified current BigNumber.
     */
    BigNumber& operator-=(const BigNumber& other);

    /**
     * @brief Multiplies the current BigNumber with another BigNumber.
     * @param other The other BigNumber to multiply.
     * @return The reference to the modified current BigNumber.
     */
    BigNumber& operator*=(const BigNumber& other);

private:
    Types::Vector<long long int> digits; /**< The digits of the BigNumber. */
};

/**
 * @class BigNumber64
 * @brief A class for handling 64-bit arbitrary precision numbers.
 */
class __cell_export BigNumber64
{
public:
    /**
     * @brief Default constructor for BigNumber64.
     */
    BigNumber64();

    /**
     * @brief Constructor for BigNumber64 that takes a string representation of a number.
     * @param number The string representation of the number.
     */
    BigNumber64(const std::string& number);

    /**
     * @brief Constructor for BigNumber64 that takes a 64-bit unsigned integer.
     * @param number The 64-bit unsigned integer value.
     */
    BigNumber64(Types::u64 number);

    /**
     * @brief Converts the BigNumber64 to a string representation.
     * @return The string representation of the BigNumber64.
     */
    __cell_no_discard Types::OptionalString toString() const;

    /**
     * @brief Adds two BigNumber64 objects.
     * @param other The other BigNumber64 to add.
     * @return The sum of the two BigNumber64 objects.
     */
    BigNumber64 operator+(const BigNumber64& other) const;

    /**
     * @brief Subtracts two BigNumber64 objects.
     * @param other The other BigNumber64 to subtract.
     * @return The difference of the two BigNumber64 objects.
     */
    BigNumber64 operator-(const BigNumber64& other) const;

    /**
     * @brief Multiplies two BigNumber64 objects.
     * @param other The other BigNumber64 to multiply.
     * @return The product of the two BigNumber64 objects.
     */
    BigNumber64 operator*(const BigNumber64& other) const;

    /**
     * @brief Checks if the BigNumber64 is equal to another BigNumber64.
     * @param other The other BigNumber64 to compare.
     * @return True if the BigNumber64 objects are equal, false otherwise.
     */
    bool operator==(const BigNumber64& other) const;

    /**
     * @brief Checks if the BigNumber64 is not equal to another BigNumber64.
     * @param other The other BigNumber64 to compare.
     * @return True if the BigNumber64 objects are not equal, false otherwise.
     */
    bool operator!=(const BigNumber64& other) const;

    /**
     * @brief Checks if the BigNumber64 is less than another BigNumber64.
     * @param other The other BigNumber64 to compare.
     * @return True if the BigNumber64 is less than the other BigNumber64, false otherwise.
     */
    bool operator<(const BigNumber64& other) const;

    /**
     * @brief Checks if the BigNumber64 is less than or equal to another BigNumber64.
     * @param other The other BigNumber64 to compare.
     * @return True if the BigNumber64 is less than or equal to the other BigNumber64, false otherwise.
     */
    bool operator<=(const BigNumber64& other) const;

    /**
     * @brief Checks if the BigNumber64 is greater than another BigNumber64.
     * @param other The other BigNumber64 to compare.
     * @return True if the BigNumber64 is greater than the other BigNumber64, false otherwise.
     */
    bool operator>(const BigNumber64& other) const;

    /**
     * @brief Checks if the BigNumber64 is greater than or equal to another BigNumber64.
     * @param other The other BigNumber64 to compare.
     * @return True if the BigNumber64 is greater than or equal to the other BigNumber64, false otherwise.
     */
    bool operator>=(const BigNumber64& other) const;

    /**
     * @brief Negates the BigNumber64.
     * @return The negated BigNumber64.
     */
    BigNumber64 operator-() const;

    /**
     * @brief Adds another BigNumber64 to the current BigNumber64.
     * @param other The other BigNumber64 to add.
     * @return The reference to the modified current BigNumber64.
     */
    BigNumber64& operator+=(const BigNumber64& other);

    /**
     * @brief Subtracts another BigNumber64 from the current BigNumber64.
     * @param other The other BigNumber64 to subtract.
     * @return The reference to the modified current BigNumber64.
     */
    BigNumber64& operator-=(const BigNumber64& other);

    /**
     * @brief Multiplies the current BigNumber64 with another BigNumber64.
     * @param other The other BigNumber64 to multiply.
     * @return The reference to the modified current BigNumber64.
     */
    BigNumber64& operator*=(const BigNumber64& other);

private:
    Types::Vector<Types::u64> digits; /**< The digits of the BigNumber64. */

    /**
     * @brief Removes leading zeros from the BigNumber64.
     */
    void removeLeadingZeros();
};

/**
 * @class BigNumber128
 * @brief A class for handling 128-bit arbitrary precision numbers.
 */
class __cell_export BigNumber128
{
public:
    /**
     * @brief Default constructor for BigNumber128.
     */
    BigNumber128();

    /**
     * @brief Constructor for BigNumber128 that takes a string representation of a number.
     * @param number The string representation of the number.
     */
    BigNumber128(const std::string& number);

    /**
     * @brief Constructor for BigNumber128 that takes a 128-bit unsigned integer.
     * @param number The 128-bit unsigned integer value.
     */
    BigNumber128(Types::u128 number);

    /**
     * @brief Converts the BigNumber128 to a string representation.
     * @return The string representation of the BigNumber128.
     */
    __cell_no_discard Types::OptionalString toString() const;

    /**
     * @brief Adds two BigNumber128 objects.
     * @param other The other BigNumber128 to add.
     * @return The sum of the two BigNumber128 objects.
     */
    BigNumber128 operator+(const BigNumber128& other) const;

    /**
     * @brief Subtracts two BigNumber128 objects.
     * @param other The other BigNumber128 to subtract.
     * @return The difference of the two BigNumber128 objects.
     */
    BigNumber128 operator-(const BigNumber128& other) const;

    /**
     * @brief Multiplies two BigNumber128 objects.
     * @param other The other BigNumber128 to multiply.
     * @return The product of the two BigNumber128 objects.
     */
    BigNumber128 operator*(const BigNumber128& other) const;

    /**
     * @brief Checks if the BigNumber128 is equal to another BigNumber128.
     * @param other The other BigNumber128 to compare.
     * @return True if the BigNumber128 objects are equal, false otherwise.
     */
    bool operator==(const BigNumber128& other) const;

    /**
     * @brief Checks if the BigNumber128 is not equal to another BigNumber128.
     * @param other The other BigNumber128 to compare.
     * @return True if the BigNumber128 objects are not equal, false otherwise.
     */
    bool operator!=(const BigNumber128& other) const;

    /**
     * @brief Checks if the BigNumber128 is less than another BigNumber128.
     * @param other The other BigNumber128 to compare.
     * @return True if the BigNumber128 is less than the other BigNumber128, false otherwise.
     */
    bool operator<(const BigNumber128& other) const;

    /**
     * @brief Checks if the BigNumber128 is less than or equal to another BigNumber128.
     * @param other The other BigNumber128 to compare.
     * @return True if the BigNumber128 is less than or equal to the other BigNumber128, false otherwise.
     */
    bool operator<=(const BigNumber128& other) const;

    /**
     * @brief Checks if the BigNumber128 is greater than another BigNumber128.
     * @param other The other BigNumber128 to compare.
     * @return True if the BigNumber128 is greater than the other BigNumber128, false otherwise.
     */
    bool operator>(const BigNumber128& other) const;

    /**
     * @brief Checks if the BigNumber128 is greater than or equal to another BigNumber128.
     * @param other The other BigNumber128 to compare.
     * @return True if the BigNumber128 is greater than or equal to the other BigNumber128, false otherwise.
     */
    bool operator>=(const BigNumber128& other) const;

    /**
     * @brief Negates the BigNumber128.
     * @return The negated BigNumber128.
     */
    BigNumber128 operator-() const;

    /**
     * @brief Adds another BigNumber128 to the current BigNumber128.
     * @param other The other BigNumber128 to add.
     * @return The reference to the modified current BigNumber128.
     */
    BigNumber128& operator+=(const BigNumber128& other);

    /**
     * @brief Subtracts another BigNumber128 from the current BigNumber128.
     * @param other The other BigNumber128 to subtract.
     * @return The reference to the modified current BigNumber128.
     */
    BigNumber128& operator-=(const BigNumber128& other);

    /**
     * @brief Multiplies the current BigNumber128 with another BigNumber128.
     * @param other The other BigNumber128 to multiply.
     * @return The reference to the modified current BigNumber128.
     */
    BigNumber128& operator*=(const BigNumber128& other);

private:
    Types::Vector<Types::u128> digits; /**< The digits of the BigNumber128. */

    /**
     * @brief Removes leading zeros from the BigNumber128.
     */
    void removeLeadingZeros();
};

CELL_NAMESPACE_END

#endif  // CELL_INTEGERS_HPP
