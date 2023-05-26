/*!
 * @file        meta-convertor.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Corrency meta convertor.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2023 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_CORRENCY_META_CONVERTOR_HPP
#define CELL_CORRENCY_META_CONVERTOR_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Convertors::Currencies)

/**
 * @brief Concept to check if a type is a floating-point type.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept FloatingPoint = std::floating_point<T>;

/**
 * @brief Enum class representing different multiplier values.
 */
enum class Multiplier :Types::uint
{
    Default = 100,
    USA = 100,
    Iran = 10,
    Custom = 0
};

/**
 * @brief A class that performs unit conversion operations.
 *
 * The UnitConverter class supports conversion between different units based on the specified multiplier value.
 * The type T must satisfy the FloatingPoint concept, and the Multiplier M must be one of the valid Multiplier enum values.
 * By default, the class uses the Default multiplier value.
 *
 * @tparam T The type of the base unit.
 * @tparam M The multiplier value for unit conversion (default: Multiplier::Default).
 */
template <FloatingPoint T, Multiplier M = Multiplier::Default>
class UnitConverter
{
private:
    unsigned int multiplier; //!< The multiplier value for unit conversion.

public:
    /**
     * @brief Constructs a UnitConverter object with a custom multiplier value.
     *
     * @param multiplierValue The custom multiplier value.
     */
    UnitConverter(unsigned int multiplierValue) : multiplier(multiplierValue) {}

    /**
     * @brief Converts a base unit value to a subunit value.
     *
     * @param baseUnit The value in the base unit.
     * @return The value converted to the subunit.
     */
    T baseToSub(T baseUnit) requires (sizeof(T) <= sizeof(double))
    {
        T subunit = baseUnit * static_cast<T>(getMultiplier());
        return subunit;
    }

    /**
     * @brief Converts a subunit value to a base unit value.
     *
     * @param subUnit The value in the subunit.
     * @return The value converted to the base unit.
     */
    T subToBase(T subUnit) requires (sizeof(T) <= sizeof(double))
    {
        T baseUnit = subUnit / static_cast<T>(getMultiplier());
        return baseUnit;
    }

    /**
     * @brief Retrieves the multiplier value used for unit conversion.
     *
     * @return The multiplier value.
     */
    unsigned int getMultiplier() const
    {
        if (M == Multiplier::Custom)
            return multiplier;
        else
            return static_cast<unsigned int>(M);
    }
};
CELL_NAMESPACE_END

#endif  // CELL_CORRENCY_META_CONVERTOR_HPP
