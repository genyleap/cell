/*!
 * @file        html.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Html interface for templates structure.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2025 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_HTML_HPP
#define CELL_HTML_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

CELL_USING_NAMESPACE Cell::Types;

CELL_NAMESPACE_BEGIN(Cell::System)

template <typename T>
concept Stringable = requires(T t) {
    { std::to_string(t) } -> std::convertible_to<std::string>;
};

/**
 * @brief The Html class
 */
class __cell_export Html {
public:
    Html();
    ~Html();

    /**
     * @brief getTags will reterives each tag of content.
     * @param content as a path or content view.
     * @return list of tags.
     */
    std::vector<std::string> getTags(const std::string_view content);

private:
    std::vector<std::string> m_tags{};

};

CELL_NAMESPACE_END

#endif // CELL_HTML_HPP
