//! Cell's Media types.
#if __has_include("mediatypes.hpp")
#   include "mediatypes.hpp"
#else
#   error "Cell's mediatype was not found!"
#endif

#if __has_include("core/core.hpp")
#   include "core/core.hpp"
#else
#   error "Cell's core was not found!"
#endif

CELL_USING_NAMESPACE Cell;
CELL_USING_NAMESPACE Cell::System;
CELL_USING_NAMESPACE Cell::Types;
CELL_USING_NAMESPACE Cell::Utility;

CELL_NAMESPACE_BEGIN(Cell::Globals)

MediaTypes::MediaTypes()
{
    EngineController engineController;
    auto& engine = engineController.getEngine();

    addMimeType("html",     engine.meta()->returnView(ContentTypes::HTML));
    addMimeType("jpg",      engine.meta()->returnView(ContentTypes::JPEG));
    addMimeType("pdf",      engine.meta()->returnView(ContentTypes::PDF));
    addMimeType("css",      engine.meta()->returnView(ContentTypes::CSS));
    addMimeType("js",       engine.meta()->returnView(ContentTypes::JavaScript));
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
    EngineController engineController;
    auto& engine = engineController.getEngine();
    auto it = mimeTypes.find(extension);
    if (it != mimeTypes.end()) {
        return it->second;
    }
    return engine.meta()->returnView(ContentTypes::OctetStream);
}

// Explicit instantiation of the template member functions
template void MediaTypes::addMimeType(const std::string& extension, const std::string& mimeType);
template std::string MediaTypes::getMimeType(const std::string& extension) const;

CELL_NAMESPACE_END
