/*!
 * @file        dictionary.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Translator core.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_DICTIONARY_HPP
#define CELL_DICTIONARY_HPP

#ifdef __has_include
# if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
# endif
#endif

CELL_NAMESPACE_BEGIN(Cell::Translation)

using DicType       = Types::MultiMap<std::string, Types::Map<std::string, std::string>>;
using Alphabet      = Types::VectorString;
using DicTypePair   = Types::PairString;
using DictonaryType = Types::MultiMap<std::string, DicTypePair>;

/*!
 * \brief The LanguageType enum
 */
enum class LanguageType : Types::u8
{
    AUTO            =  0x0, //In this case, the system checks the language status automatically.
    SINGLE          =  0x1, //In this casem the system will sets all system interface based on single activated language.
    MULTILANGUAGE   =  0x2  //In this casem the system will sets all system interface based on multi-language for only activated language.
};

/*!
 * \brief The LanguageTemplate class
 */
class LanguageTemplate {
public:
    LanguageTemplate();
    LanguageTemplate(const std::string& word_key,
                     const std::string& module,
                     const std::string& default_value,
                     const std::string& custom_value);

    ~LanguageTemplate();

    /*!
     * \brief wordKey function will gets key as string.
     * \returns string.
     */
    __cell_no_discard std::string wordKey () __cell_const_noexcept;

    /*!
     * \brief module function will gets module name as string.
     * \returns string.
     */
    __cell_no_discard std::string module () __cell_const_noexcept;

    /*!
     * \brief defaultValue function will gets default value if there is no any value in custom value.
     * \returns string.
     */
    __cell_no_discard std::string defaultValue () __cell_const_noexcept;

    /*!
     * \brief customValue function will gets custom value.
     * \returns string.
     */
    __cell_no_discard std::string customValue () __cell_const_noexcept;

private:
    std::string m_wordKey       {};
    std::string m_module        {};
    std::string m_defaultValue  {};
    std::string m_customValue   {};
};

CELL_NAMESPACE_END

#endif // CELL_DICTIONARY_HPP
