#if __has_include("cookies.hpp")
#   include "cookies.hpp"
#else
#   error "Cell's cookies was not found!"
#endif

#if __has_include("core/core.hpp")
#   include "core/core.hpp"
#else
#   error "Cell's core was not found!"
#endif

CELL_USING_NAMESPACE Cell;
CELL_USING_NAMESPACE Cell::Types;
CELL_USING_NAMESPACE Cell::System;

CELL_NAMESPACE_BEGIN(Cell::Globals::Storage)

OptionalString Cookies::getCookie(const std::string& name) const
{
    auto it = m_cookies.find(name);
    if (it != m_cookies.end()) {
        return it->second;
    }
    return __cell_null_optional;
}

OptionalString Cookies::getSessionIdCookie() const
{
    EngineController engineController;
    auto& engine = engineController.getEngine();
    return getCookie(engine.meta()->returnView(COOKIES_CONSTANTS::SESSION_ID));
}

void Cookies::addCookie(const std::string& name, const std::string& value)
{
    m_cookies[name] = value;
}


CELL_NAMESPACE_END
