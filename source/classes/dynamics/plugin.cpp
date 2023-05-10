#ifdef __has_include
# if __has_include("plugin.hpp")
#   include "plugin.hpp"
#else
#   error "Cell's plugin not found!"
# endif
#endif

Plugin::Plugin()
{
    __cell_safe_instance(m_pluginInfo, PluginInfo);
}

Plugin::~Plugin()
{
    __cell_safe_instance(m_pluginInfo, PluginInfo);
}
