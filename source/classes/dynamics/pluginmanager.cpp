#ifdef __has_include
# if __has_include("pluginmanager.hpp")
#   include "pluginmanager.hpp"
#else
#   error "Cell's "pluginmanager.hpp" was not found!"
# endif
#endif

#ifdef __has_include
# if __has_include("core/logger.hpp")
#   include "core/logger.hpp"
#else
#   error "Cell's "core/logger.hpp" was not found!"
# endif
#endif


#if defined(PLATFORM_WINDOWS)
#   include <windows.h>
#else
#   include <dlfcn.h>
#endif

CELL_USING_NAMESPACE Cell;
CELL_USING_NAMESPACE Cell::eLogger;

using PluginMap  =  std::map<std::string, Plugin*>;

using LibraryMap =  std::map<std::string, void*>;

class PluginManagerPimpl
{
public:
    PluginMap plugins;
    LibraryMap libs;
};

PluginManager::PluginManager()
{
    __cell_smart_instance(implementationPtr, PluginManagerPimpl);
}

PluginManager::~PluginManager()
{
}

CreateSingletonInstance(PluginManager);

Plugin* PluginManager::load(const std::string& name)
{
    Plugin* plugin = nullptr;
    PluginMap::iterator iter = implementationPtr->plugins.find(name);
    try {
        if (iter == implementationPtr->plugins.end())
        {
// Try to load the plugin library
#if defined(PLATFORM_WINDOWS)
            void *hModule;
            hModule = LoadLibraryW(name.c_str());
#elif defined(PLATFORM_MAC)
            void *hModule;
            hModule = dlopen(name.c_str(), RTLD_LAZY);
#elif defined(PLATFORM_LINUX)
            void *hModule;
            hModule = dlopen(name.c_str(), RTLD_LAZY);
#endif
            if (hModule != nullptr)
            {
#if defined(PLATFORM_WINDOWS)
                fnCreatePlugin CreatePlugin = (fnCreatePlugin)GetProcAddress(hModule, "CreatePlugin");
#elif defined(PLATFORM_MAC)
                fnCreatePlugin CreatePlugin = (fnCreatePlugin)dlsym(hModule, "CreatePlugin");
#elif defined(PLATFORM_LINUX)
                fnCreatePlugin CreatePlugin = (fnCreatePlugin)dlsym(hModule, "CreatePlugin");
#endif
                if (CreatePlugin != nullptr)
                {
                    // Invoke the function to get the plugin from the DLL.
                    plugin = CreatePlugin();
                    if (plugin != nullptr)
                    {
                        // plugin->setName("{?}"); //May we want to set name here!
                        // Add the plugin and library18 to the maps.
                        implementationPtr->plugins.insert(PluginMap::value_type(name, plugin));
                        implementationPtr->libs.insert(LibraryMap::value_type(name, hModule));
                    }
                    else
                    {
                        Log("Could not load plugin from " + FROM_CELL_STRING(name.c_str()) , LoggerType::Critical);
// Unload the library.
#if defined(PLATFORM_WINDOWS)
                        FreeLibrary(hModule);
#elif defined(PLATFORM_MAC)
                        dlclose(hModule);
#elif defined(PLATFORM_LINUX)
                        dlclose(hModule);
#endif
                    }
                }
                else
                {
                    Log("Could not find symbol \"CreatePlugin\" in " + FROM_CELL_STRING(name.c_str()) , LoggerType::Critical);
#if defined(PLATFORM_WINDOWS)
                    FreeLibrary(hModule);
#elif defined(PLATFORM_MAC)
                    dlclose(hModule);
#elif defined(PLATFORM_LINUX)
                    dlclose(hModule);
#endif
                }
            }
            else
            {
                Log("Could not load library: " + FROM_CELL_STRING(name.c_str()) , LoggerType::Critical);
                m_status = {false};
            }
        }
        else
        {
            Log("Library \"" + FROM_CELL_STRING(name.c_str()) + "\" already loaded." , LoggerType::Info);
            plugin = iter->second;
            m_status = {true};
        }
    } catch (...) {
    }
    return plugin;
}

void PluginManager::unload(Plugin *&plugin)
{
    if (plugin != nullptr)
    {
        LibraryMap::iterator iter = implementationPtr->libs.find(plugin->getName().value());
        if(iter != implementationPtr->libs.end())
        {
            // Remove the plugin from our plugin map.
            implementationPtr->plugins.erase(plugin->getName().value());
            void* hModule = iter->second;
#if defined(PLATFORM_WINDOWS)
            fnDestroyPlugin DestroyPlugin = (fnDestroyPlugin)GetProcAddress(hModule, "DestroyPlugin");
#elif defined(PLATFORM_MAC)
            fnDestroyPlugin DestroyPlugin = (fnDestroyPlugin)dlsym(hModule, "DestroyPlugin");
#elif defined(PLATFORM_LINUX)
            fnDestroyPlugin DestroyPlugin = (fnDestroyPlugin)dlsym(hModule, "DestroyPlugin");
#endif
            if (DestroyPlugin != nullptr)
            {
                DestroyPlugin();
            }
            else
            {
                Log("Unable to find symbol \"DestroyPlugin\" in library \"" + FROM_CELL_STRING(plugin->getName().value().c_str()) , LoggerType::Critical);
            }
// Unload the library and remove the library from the map.
#if defined(PLATFORM_WINDOWS)
            FreeLibrary(hModule);
#elif defined(PLATFORM_MAC)
            dlclose(hModule);
#elif defined(PLATFORM_LINUX)
            dlclose(hModule);
#endif
            implementationPtr->libs.erase(iter);
        }
        else
        {
            Log("Trying to unload a plugin that is already unloaded or has never been loaded.", LoggerType::Warning);
        }
        plugin = nullptr;
    }
}

bool PluginManager::isLoaded() const
{
    return m_status;
}
