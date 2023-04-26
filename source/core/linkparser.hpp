/*!
 * Gen3 License
 *
 * @file        linkparser.hpp
 * @brief       This file is part of the Cell engine.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     libCell
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 */

#ifndef CELL_LINK_PARSER_HPP
#define CELL_LINK_PARSER_HPP

#ifdef __has_include
# if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
# endif
#endif

CELL_NAMESPACE_BEGIN(Cell)

/*!
 * \brief The LinkParser class
 */
class LinkParser
{
public:
    LinkParser();
    ~LinkParser();
    /*!
     * \brief parse function will parse the simple url.
     * \param url is the url string.
     */
    void parse(std::string& url);

    /*!
     * \brief items will returns elements of link.
     * \return as array.
     */
    Types::VectorString items();

private:
    Types::VectorString m_item{};
};

CELL_NAMESPACE_END

#endif // CELL_LINK_PARSER_HPP
