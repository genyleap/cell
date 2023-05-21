#if __has_include("format.hpp")
#   include "format.hpp"
#else
#   error "Cell's "format.hpp" was not found!"
#endif

#if __has_include(<core>)
#   include <core>
#else
#   error "Cell's <core> was not found!"
#endif

CELL_USING_NAMESPACE Cell::System;
CELL_USING_NAMESPACE Cell::FileSystem;

CELL_NAMESPACE_BEGIN(Cell)

#ifdef USE_BOOST_FORMAT
std::string convertPlaceholders(const std::string& formatString)
{
    std::string convertedFormatString;
    std::size_t argIndex = 1;
    for (std::size_t i = 0; i < formatString.size(); ++i) {
        if (formatString[i] == '{' && i + 1 < formatString.size() && formatString[i + 1] == '}') {
            convertedFormatString += "%" + std::to_string(argIndex) + "%";
            ++argIndex;
            ++i;
        } else {
            convertedFormatString += formatString[i];
        }
    }
    return convertedFormatString;
}
#endif

CELL_NAMESPACE_END
