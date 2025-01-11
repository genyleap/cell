/*!
 * Gen3 License
 *
 * @file        linkparser.hpp
 * @brief       This file is part of the Cell engine.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     libCell
 * @copyright   Copyright (c) 2025 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 */

#ifndef CELL_LINK_PARSER_HPP
#define CELL_LINK_PARSER_HPP
#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Web)

/**
 * @class LinkParser
 * @brief Class to parse web links and extract items from them.
 */
class __cell_export LinkParser
{
public:
    LinkParser();
    ~LinkParser();

    /**
     * @brief Parse the given URL and extract items from it.
     * @param url The URL to parse.
     */
    void parse(std::string& url);

    /**
     * @brief Get the extracted items from the parsed URL.
     * @return A vector of strings containing the extracted items.
     */
    Types::VectorString items();

    /**
     * @brief Beautify the given URI by replacing spaces and other characters.
     * @details Some links have symptoms that need to be corrected, this function can provide it.
     * for example [page_one+1] ~ should be page-page1.
     * @param uri The URI to beautify.
     * @return A beautified version of the URI.
     */
    std::string beautify(const std::string& uri);

    /**
     * @brief recorrectUrl function will fix the given URL.
     * @param url as url string.
     * @return fixed url with protocol only.
     */
    std::string recorrectUrl(std::string& url);

    /**
     * @brief decodeUrl function takes a URL in the percent-encoded format and returns the corresponding UTF-8 string.
     * @param url as percent-encoded format.
     * @return a url as UTF-8 string.
     */
    std::string decodeUrl(const std::string& url);

private:
    Types::VectorString m_item{}; /*!< A vector of strings to hold the extracted items from the URL */
};

CELL_NAMESPACE_END

#endif // CELL_LINK_PARSER_HPP
