/*!
 * @file        text.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Text convertor.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2023 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_TEXT_CONVERTOR_HPP
#define CELL_TEXT_CONVERTOR_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Convertors::Text)

/**
 * @brief The TextConverter class provides functions for converting text between different formats and performing text manipulation operations.
 */
class __cell_export TextConverter {
public:
    /**
     * @brief Converts ASCII codes to text.
     * @param ascii The ASCII codes to convert.
     * @return The converted text.
     */
    Types::OptionalString asciiToText(const std::string& ascii);

    /**
     * @brief Converts text to ASCII codes.
     * @param text The text to convert.
     * @return The converted ASCII codes.
     */
    Types::OptionalString textToAscii(const std::string& text);

    /**
     * @brief Converts hexadecimal representation to text.
     * @param hex The hexadecimal representation to convert.
     * @return The converted text.
     */
    Types::OptionalString hexadecimalToText(const std::string& hex);

    /**
     * @brief Converts text to hexadecimal representation.
     * @param text The text to convert.
     * @return The converted hexadecimal representation.
     */
    Types::OptionalString textToHexadecimal(const std::string& text);

    /**
     * @brief Converts text to binary representation.
     * @param text The text to convert.
     * @return The converted binary representation.
     */
    Types::OptionalString textToBinary(const std::string& text);

    /**
     * @brief Converts binary representation to text.
     * @param binary The binary representation to convert.
     * @return The converted text.
     */
    Types::OptionalString binaryToText(const std::string& binary);

    /**
     * @brief Converts octal representation to text.
     * @param octal The octal representation to convert.
     * @return The converted text.
     */
    Types::OptionalString octalToText(const std::string& octal);

    /**
     * @brief Converts text to octal representation.
     * @param text The text to convert.
     * @return The converted octal representation.
     */
    Types::OptionalString textToOctal(const std::string& text);

    /**
     * @brief Converts Morse code to text.
     * @param morseCode The Morse code to convert.
     * @return The converted text.
     */
    Types::OptionalString morseCodeToText(const std::string& morseCode);

    /**
     * @brief Converts text to Morse code.
     * @param text The text to convert.
     * @return The converted Morse code.
     */
    Types::OptionalString textToMorseCode(const std::string& text);

    /**
     * @brief Converts text to uppercase.
     * @param text The text to convert.
     * @return The converted uppercase text.
     */
    Types::OptionalString toUppercase(const std::string& text);

    /**
     * @brief Converts text to lowercase.
     * @param text The text to convert.
     * @return The converted lowercase text.
     */
    Types::OptionalString toLowercase(const std::string& text);

    /**
     * @brief Converts text to random case.
     * @param text The text to convert.
     * @return The converted text with random case.
     */
    Types::OptionalString toRandomcase(const std::string& text);

    /**
     * @brief Removes accents from text.
     * @param text The text to remove accents from.
     * @return The text with accents removed.
     */
    Types::OptionalWString removeAccents(const std::wstring& text);

    /**
     * @brief Capitalizes the first letter of each word in the text.
     * @param text The text to capitalize.
     * @return The capitalized text.
     */
    Types::OptionalString capitalizeWords(const std::string& text);

    /**
     * @brief Capitalizes the first letter of the first sentence in the text.
     * @param text The text to capitalize.
     * @return The capitalized text.
     */
    Types::OptionalString capitalizeSentence(const std::string& text);

    /**
     * @brief Reverses the order of characters in the text.
     * @param text The text to reverse.
     * @return The reversed text.
     */
    Types::OptionalString reverseText(const std::string& text);

    /**
     * @brief Reverses the order of words in the text.
     * @param text The text to reverse.
     * @return The text with reversed words.
     */
    Types::OptionalString reverseWords(const std::string& text);

    /**
     * @brief Converts text to HTML representation.
     * @param text The text to convert.
     * @return The HTML representation of the text.
     */
    Types::OptionalString textToHTML(const std::string& text);

    /**
     * @brief Converts HTML representation to plain text.
     * @param html The HTML representation to convert.
     * @return The converted plain text.
     */
    Types::OptionalString htmlToText(const std::string& html);

    /**
     * @brief Removes all whitespace characters from the text.
     * @param text The text to remove whitespace from.
     * @return The text with whitespace removed.
     */
    Types::OptionalString removeWhitespace(const std::string& text);

    /**
     * @brief Trims leading and trailing whitespace from the text.
     * @param text The text to trim whitespace from.
     * @return The text with leading and trailing whitespace trimmed.
     */
    Types::OptionalString trimWhitespace(const std::string& text);

    /**
     * @brief Removes special characters from the text.
     * @param text The text to remove special characters from.
     * @return The text with special characters removed.
     */
    Types::OptionalString removeSpecialCharacters(const std::string& text);

    /**
     * @brief Extracts digits from the text.
     * @param text The text to extract digits from.
     * @return The extracted digits from the text.
     */
    Types::OptionalString extractDigits(const std::string& text);
};

CELL_NAMESPACE_END

#endif  // CELL_TEXT_CONVERTOR_HPP
