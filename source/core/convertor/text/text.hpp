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
     *
     * This function takes a string `ascii` representing ASCII codes and converts them into text.
     *
     * @param ascii The ASCII codes to convert, separated by spaces.
     * @return An optional string with the converted text if successful, or an empty optional if the conversion fails.
     */
    Types::OptionalString asciiToText(const std::string& ascii);

    /**
     * @brief Converts text to ASCII codes.
     *
     * This function takes a string `text` and converts it into ASCII codes, representing each character as its corresponding ASCII value.
     *
     * @param text The text to convert.
     * @return An optional string with the converted ASCII codes if successful, or an empty optional if the conversion fails.
     */
    Types::OptionalString textToAscii(const std::string& text);

    /**
     * @brief Converts hexadecimal representation to text.
     *
     * This function takes a string `hex` containing a hexadecimal representation and converts it into its corresponding text representation.
     * Each pair of hexadecimal digits is interpreted as a character and combined to form the resulting text.
     *
     * @param hex The hexadecimal representation to convert.
     * @return An optional string with the converted text if successful, or an empty optional if the conversion fails.
     */
    Types::OptionalString hexadecimalToText(const std::string& hex);

    /**
     * @brief Converts text to hexadecimal representation.
     *
     * This function takes a string `text` and converts it into its corresponding hexadecimal representation.
     * Each character in the text is converted to its hexadecimal value and combined to form the resulting string.
     *
     * @param text The text to convert.
     * @return An optional string with the converted hexadecimal representation if successful, or an empty optional if the conversion fails.
     */
    Types::OptionalString textToHexadecimal(const std::string& text);

    /**
     * @brief Converts text to binary representation.
     *
     * This function takes a string `text` and converts it into its corresponding binary representation.
     * Each character in the text is converted to its binary representation and combined to form the resulting string.
     *
     * @param text The text to convert.
     * @return An optional string with the converted binary representation if successful, or an empty optional if the conversion fails.
     */
    Types::OptionalString textToBinary(const std::string& text);

    /**
     * @brief Converts binary representation to text.
     *
     * This function takes a string `binary` containing binary representation and converts it into its corresponding text.
     * The binary string is divided into groups of 8 bits, each representing an ASCII character. The ASCII characters are
     * combined to form the resulting text.
     *
     * @param binary The binary representation to convert.
     * @return An optional string with the converted text if successful, or an empty optional if the conversion fails.
     */
    Types::OptionalString binaryToText(const std::string& binary);

    /**
     * @brief Converts octal representation to text.
     *
     * This function takes a string `octal` containing octal representation and converts it into its corresponding text.
     * Each group of three octal digits represents an ASCII character. The ASCII characters are combined to form the resulting text.
     *
     * @param octal The octal representation to convert.
     * @return An optional string with the converted text if successful, or an empty optional if the conversion fails.
     */
    Types::OptionalString octalToText(const std::string& octal);

    /**
     * @brief Converts text to octal representation.
     *
     * This function takes a string `text` and converts it into its corresponding octal representation.
     * Each character in the text is converted to its ASCII code and represented as a group of three octal digits.
     * The octal digits are combined to form the resulting octal representation.
     *
     * @param text The text to convert.
     * @return An optional string with the converted octal representation if successful, or an empty optional if the conversion fails.
     */
    Types::OptionalString textToOctal(const std::string& text);

    /**
     * @brief Converts Morse code to text.
     *
     * This function takes a string `morseCode` containing Morse code and converts it into its corresponding text representation.
     * The Morse code is decoded by mapping each sequence of dots and dashes to its corresponding alphanumeric character or special symbol.
     * The resulting text is returned as a string.
     *
     * @param morseCode The Morse code to convert.
     * @return An optional string with the converted text if successful, or an empty optional if the conversion fails.
     */
    Types::OptionalString morseCodeToText(const std::string& morseCode);

    /**
     * @brief Converts text to Morse code.
     *
     * This function takes a string `text` and converts it into its corresponding Morse code representation.
     * Each alphanumeric character and special symbol in the input text is encoded using a sequence of dots and dashes
     * based on the Morse code lookup table. The resulting Morse code is returned as a string.
     *
     * @param text The text to convert to Morse code.
     * @return An optional string with the converted Morse code if successful, or an empty optional if the conversion fails.
     */
    Types::OptionalString textToMorseCode(const std::string& text);

    /**
     * @brief Converts text to uppercase.
     *
     * This function takes a string `text` and converts all the characters in the string to uppercase.
     * The resulting uppercase text is returned as a string.
     *
     * @param text The text to convert to uppercase.
     * @return An optional string with the converted uppercase text if successful, or an empty optional if the conversion fails.
     */
    Types::OptionalString toUppercase(const std::string& text);

    /**
     * @brief Converts text to lowercase.
     *
     * This function takes a string `text` and converts all the characters in the string to lowercase.
     * The resulting lowercase text is returned as a string.
     *
     * @param text The text to convert to lowercase.
     * @return An optional string with the converted lowercase text if successful, or an empty optional if the conversion fails.
     */
    Types::OptionalString toLowercase(const std::string& text);

    /**
     * @brief Converts text to random case.
     *
     * This function takes a string `text` and randomly converts the characters in the string to uppercase or lowercase,
     * resulting in a text with random casing. The converted text is returned as a string.
     *
     * @param text The text to convert to random case.
     * @return An optional string with the converted text in random case if successful, or an empty optional if the conversion fails.
     */
    Types::OptionalString toRandomcase(const std::string& text);

    /**
     * @brief Removes accents from text.
     *
     * This function takes a wide string `text` as input and removes any accents or diacritical marks from the characters in the string.
     * It returns the modified text with accents removed as a wide string.
     *
     * @param text The wide string from which to remove accents.
     * @return An optional wide string with accents removed if successful, or an empty optional if the removal fails.
     */
    Types::OptionalWString removeAccents(const std::wstring& text);

    /**
     * @brief Capitalizes the first letter of each word in the text.
     *
     * This function takes a string `text` as input and capitalizes the first letter of each word in the text.
     * Words are delimited by whitespace characters. The function returns the modified text with capitalized words as a string.
     *
     * @param text The string in which to capitalize words.
     * @return An optional string with the first letter of each word capitalized if successful, or an empty optional if the operation fails.
     */
    Types::OptionalString capitalizeWords(const std::string& text);

    /**
     * @brief Capitalizes the first letter of the first sentence in the text.
     *
     * This function takes a string `text` as input and capitalizes the first letter of the first sentence in the text.
     * The sentence is determined by the presence of punctuation marks (e.g., '.', '!', '?') followed by whitespace.
     * The function returns the modified text with the first letter of the first sentence capitalized as a string.
     *
     * @param text The string in which to capitalize the first sentence.
     * @return An optional string with the first letter of the first sentence capitalized if successful, or an empty optional if the operation fails.
     */
    Types::OptionalString capitalizeSentence(const std::string& text);

    /**
     * @brief Reverses the order of characters in the text.
     *
     * This function takes a string `text` as input and reverses the order of characters in the text.
     * The reversed text is returned as a new string.
     *
     * @param text The string to reverse.
     * @return An optional string with the characters reversed if successful, or an empty optional if the operation fails.
     */
    Types::OptionalString reverseText(const std::string& text);

    /**
     * @brief Reverses the order of words in the text.
     *
     * This function takes a string `text` as input and reverses the order of words in the text.
     * The words are delimited by whitespace characters. The resulting text with reversed words is returned as a new string.
     *
     * @param text The string to reverse the words.
     * @return An optional string with the words reversed if successful, or an empty optional if the operation fails.
     */
    Types::OptionalString reverseWords(const std::string& text);

    /**
     * @brief Converts text to HTML representation.
     *
     * This function takes a string `text` as input and converts it to its HTML representation.
     * The special characters in the text are escaped, and appropriate HTML tags are added for formatting.
     * The resulting HTML representation of the text is returned as a new string.
     *
     * @param text The string to convert to HTML representation.
     * @return An optional string with the HTML representation of the text if successful, or an empty optional if the operation fails.
     */
    Types::OptionalString textToHTML(const std::string& text);

    /**
     * @brief Converts HTML representation to plain text.
     *
     * This function takes a string `html` as input, which represents HTML content, and converts it to plain text.
     * The HTML tags and special characters are removed, and the resulting plain text is returned as a new string.
     *
     * @param html The HTML representation to convert to plain text.
     * @return An optional string with the converted plain text if successful, or an empty optional if the operation fails.
     */
    Types::OptionalString htmlToText(const std::string& html);

    /**
     * @brief Removes all whitespace characters from the text.
     *
     * This function takes a string `text` as input and removes all whitespace characters, including spaces, tabs, and newlines.
     * The resulting text without any whitespace characters is returned as a new string.
     *
     * @param text The text to remove whitespace from.
     * @return An optional string with whitespace removed if successful, or an empty optional if the operation fails.
     */
    Types::OptionalString removeWhitespace(const std::string& text);

    /**
     * @brief Trims leading and trailing whitespace from the text.
     *
     * This function takes a string `text` as input and removes any leading and trailing whitespace characters, including spaces, tabs, and newlines.
     * The resulting text with leading and trailing whitespace trimmed is returned as a new string.
     *
     * @param text The text to trim whitespace from.
     * @return An optional string with leading and trailing whitespace trimmed if successful, or an empty optional if the operation fails.
     */
    Types::OptionalString trimWhitespace(const std::string& text);

    /**
     * @brief Removes special characters from the text.
     *
     * This function takes a string `text` as input and removes any special characters, such as punctuation marks, symbols, and non-alphanumeric characters.
     * The resulting text with special characters removed is returned as a new string.
     *
     * @param text The text to remove special characters from.
     * @return An optional string with special characters removed if successful, or an empty optional if the operation fails.
     */
    Types::OptionalString removeSpecialCharacters(const std::string& text);

    /**
     * @brief Extracts digits from the text.
     *
     * This function takes a string `text` as input and extracts all the digits present in the text.
     * The extracted digits are returned as a new string, preserving their original order.
     *
     * @param text The text to extract digits from.
     * @return An optional string containing the extracted digits if successful, or an empty optional if no digits are found.
     */
    Types::OptionalString extractDigits(const std::string& text);

    /**
     * @brief Removes HTML tags from the given text.
     *
     * This function takes a string containing HTML tags and removes them, returning the resulting string
     * without the HTML tags. The tags are identified using a regular expression pattern match.
     *
     * @param text The input text containing HTML tags.
     * @return An optional string with HTML tags stripped, or an empty optional if the input is empty.
     */
    Types::OptionalString stripHtmlTags(const std::string& text);
};

CELL_NAMESPACE_END

#endif  // CELL_TEXT_CONVERTOR_HPP
