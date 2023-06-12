//! Cell's Media types.
#if __has_include("mediatypes.hpp")
#   include "mediatypes.hpp"
#else
#   error "Cell's mediatype was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Globals)

MediaTypes::MediaTypes()
{
    addMimeType("html", "text/html");
    addMimeType("jpg", "image/jpeg");
    addMimeType("pdf", "application/pdf");
    addMimeType("css", "text/css");
    addMimeType("js", "application/javascript");
    //! Add more mappings as needed
    //! ToDo dynamics..
}

template <std::convertible_to<std::string> Extension, std::convertible_to<std::string> MimeType>
void MediaTypes::addMimeType(const Extension& extension, const MimeType& mimeType)
{
    mimeTypes[extension] = mimeType;
}

template <std::convertible_to<std::string> Extension>
std::string MediaTypes::getMimeType(const Extension& extension) const
{
    auto it = mimeTypes.find(extension);
    if (it != mimeTypes.end()) {
        return it->second;
    }
    return "application/octet-stream";
}

// Explicit instantiation of the template member functions
template void MediaTypes::addMimeType(const std::string& extension, const std::string& mimeType);
template std::string MediaTypes::getMimeType(const std::string& extension) const;

CELL_NAMESPACE_END
