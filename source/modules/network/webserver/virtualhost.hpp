/*!
 * @file        virtualhost.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Webserver virtualhost for system.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2025 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_VIRTUAL_HOST_CONFIG_HPP
#define CELL_VIRTUAL_HOST_CONFIG_HPP

#ifdef __has_include
# if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
# endif
#endif

#ifdef __has_include
# if __has_include("request.hpp")
#   include "request.hpp"
#else
#   error "Cell's "request.hpp" was not found!"
# endif
#endif

#ifdef __has_include
# if __has_include("response.hpp")
#   include "response.hpp"
#else
#   error "Cell's "response.hpp" was not found!"
# endif
#endif

#if __has_include("abstracts/modules/webserver/virtualhost.hpp")
#include "abstracts/modules/webserver/virtualhost.hpp"
#else
#error "Cell's abstracts/modules/webserver/virtualhost.hpp was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Network::WebServer)

class __cell_export VirtualHostConfig {
public:
    const std::string& getDocumentRoot() const;
    const std::unordered_map<std::string, std::string>& getErrorPages() const;
    void setDocumentRoot(const std::string& documentRoot);
    void setErrorPage(const std::string& errorPage, int errorCode = 0);
private:
    std::string m_documentRoot;
    std::unordered_map<std::string, std::string> m_errorPages;
};


CELL_NAMESPACE_END

#endif  // CELL_VIRTUAL_HOST_CONFIG_HPP
