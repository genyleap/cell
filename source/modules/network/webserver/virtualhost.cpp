#if __has_include("virtualhost.hpp")
#   include "virtualhost.hpp"
#else
#   error "Cell's virtualhost was not found!"
#endif

CELL_USING_NAMESPACE Cell;

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Network::WebServer)

const std::string& VirtualHostConfig::getDocumentRoot() const
{
    return m_documentRoot;
}

void VirtualHostConfig::setDocumentRoot(const std::string& documentRoot)
{
    m_documentRoot = documentRoot;
}

const std::unordered_map<std::string, std::string>& VirtualHostConfig::getErrorPages() const
{
    return m_errorPages;
}

void VirtualHostConfig::setErrorPage(const std::string& errorPage, int errorCode)
{
    m_errorPages[std::to_string(errorCode)] = errorPage;
}

CELL_NAMESPACE_END
