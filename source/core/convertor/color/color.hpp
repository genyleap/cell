/*!
 * @file        color.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Color convertor.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2023 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_COLOR_CONVERTOR_HPP
#define CELL_COLOR_CONVERTOR_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Convertors::Color)

/**
 * @brief The ColorConverter class provides color conversion utilities.
 */
class __cell_export ColorConverter {
public:
    /**
     * @brief Converts RGB values to HEX format.
     *
     * @param red   The red component value (0-255).
     * @param green The green component value (0-255).
     * @param blue  The blue component value (0-255).
     * @return The HEX color string representation.
     */
    std::string rgbToHex(int red, int green, int blue);

    /**
     * @brief Converts HEX color string to RGB values.
     *
     * @param hex   The HEX color string (e.g., "#FF0000").
     * @param red   The reference to store the red component value.
     * @param green The reference to store the green component value.
     * @param blue  The reference to store the blue component value.
     */
    void hexToRgb(const std::string& hex, int& red, int& green, int& blue);

    /**
     * @brief Converts RGB values to CMYK format.
     *
     * @param red     The red component value (0-255).
     * @param green   The green component value (0-255).
     * @param blue    The blue component value (0-255).
     * @param cyan    The reference to store the cyan component value (0.0-1.0).
     * @param magenta The reference to store the magenta component value (0.0-1.0).
     * @param yellow  The reference to store the yellow component value (0.0-1.0).
     * @param black   The reference to store the black component value (0.0-1.0).
     */
    void rgbToCmyk(int red, int green, int blue, double& cyan, double& magenta, double& yellow, double& black);

    /**
     * @brief Converts CMYK values to RGB format.
     *
     * @param cyan    The cyan component value (0.0-1.0).
     * @param magenta The magenta component value (0.0-1.0).
     * @param yellow  The yellow component value (0.0-1.0).
     * @param black   The black component value (0.0-1.0).
     * @param red     The reference to store the red component value.
     * @param green   The reference to store the green component value.
     * @param blue    The reference to store the blue component value.
     */
    void cmykToRgb(double cyan, double magenta, double yellow, double black, int& red, int& green, int& blue);

    /**
     * @brief Converts RGB values to HSL format.
     *
     * @param red         The red component value (0-255).
     * @param green       The green component value (0-255).
     * @param blue        The blue component value (0-255).
     * @param hue         The reference to store the hue component value (0.0-1.0).
     * @param saturation  The reference to store the saturation component value (0.0-1.0).
     * @param lightness   The reference to store the lightness component value (0.0-1.0).
     */
    void rgbToHsl(int red, int green, int blue, double& hue, double& saturation, double& lightness);

    /**
     * @brief Converts HSL values to RGB format.
     *
     * @param hue         The hue component value (0.0-1.0).
     * @param saturation  The saturation component value (0.0-1.0).
     * @param lightness   The lightness component value (0.0-1.0).
     * @param red         The reference to store the red component value.
     * @param green       The reference to store the green component value.
     * @param blue        The reference to store the blue component value.
     */
    void hslToRgb(double hue, double saturation, double lightness, int& red, int& green, int& blue);
};

CELL_NAMESPACE_END

#endif  // CELL_COLOR_CONVERTOR_HPP
