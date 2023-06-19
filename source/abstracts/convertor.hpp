/*!
 * @file        convertor.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Convertor interface for system.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2023 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_CONVERTOR_UNIT_ABSTRACT_HPP
#define CELL_CONVERTOR_UNIT_ABSTRACT_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Abstracts::Convertor)

/**
 * @brief Concept to check if the type is an enumeration.
 * @tparam Unit The type to check.
 */
template<typename Unit>
concept UnitConcept = std::is_enum_v<Unit>;

/**
 * @brief Abstract class for unit converters.
 * @tparam Unit The enumeration type representing the units.
 */
template<UnitConcept Unit>
class __cell_export UnitConverter {
public:
    /**
     * @brief Convert a value from one unit to another.
     * @param value The value to be converted.
     * @param fromUnit The unit to convert from.
     * @param toUnit The unit to convert to.
     * @return The converted value.
     */
    __cell_virtual double convert(double value, Unit fromUnit, Unit toUnit) = __cell_zero;

    /**
     * @brief Get the string representation of a unit.
     * @param unit The unit to get the string representation of.
     * @return The string representation of the unit.
     */
    __cell_virtual std::string toString(Unit unit) = __cell_zero;

    /**
     * @brief Virtual destructor for proper cleanup of derived classes.
     */
    __cell_virtual ~UnitConverter() = default;
};

CELL_NAMESPACE_END

#endif  // CELL_CONVERTOR_UNIT_ABSTRACT_HPP
