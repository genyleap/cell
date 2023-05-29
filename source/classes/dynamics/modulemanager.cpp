#if __has_include("modulemanager.hpp")
#   include "modulemanager.hpp"
#else
#   error "Cell's "modulemanager.hpp" was not found!"
#endif

#if __has_include("core/logger.hpp")
#   include "core/logger.hpp"
#else
#   error "Cell's "core/logger.hpp" was not found!"
#endif


#if defined(PLATFORM_WINDOWS)
#   include <windows.h>
#else
#   include <dlfcn.h>
#endif

CELL_USING_NAMESPACE Cell;
CELL_USING_NAMESPACE Cell::Utility;

CELL_NAMESPACE_BEGIN(Cell::Dynamics)

using ModuleMap  =  std::map<std::string, Module*>;

using LibraryMap =  std::map<std::string, void*>;

class ModuleManagerPimpl
{
public:
    ModuleMap modules;
    LibraryMap libs;
};

ModuleManager::ModuleManager()
{
    __cell_smart_instance(implementationPtr, ModuleManagerPimpl);
}

ModuleManager::~ModuleManager()
{
}

CreateSingletonInstance(ModuleManager);

Module* ModuleManager::load(const std::string& name)
{
    Module* module = nullptr;
    ModuleMap::iterator iter = implementationPtr->modules.find(name);
    try {
        if (iter == implementationPtr->modules.end())
        {
// Try to load the module library
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
                fnCreateModule CreateModule = (fnCreateModule)GetProcAddress(hModule, "CreateModule");
#elif defined(PLATFORM_MAC)
                fnCreateModule CreateModule = (fnCreateModule)dlsym(hModule, "CreateModule");
#elif defined(PLATFORM_LINUX)
                fnCreateModule CreateModule = (fnCreateModule)dlsym(hModule, "CreateModule");
#endif
                if (CreateModule != nullptr)
                {
                    // Invoke the function to get the module from the DLL.
                    module = CreateModule();
                    if (module != nullptr)
                    {
                        // module->setName("{?}"); //May we want to set name here!
                        // Add the module and library18 to the maps.
                        implementationPtr->modules.insert(ModuleMap::value_type(name, module));
                        implementationPtr->libs.insert(LibraryMap::value_type(name, hModule));
                    }
                    else
                    {
                        Log("Could not load module from " + FROM_CELL_STRING(name.c_str()) , LoggerType::Critical);
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
                    Log("Could not find symbol \"CreateModule\" in " + FROM_CELL_STRING(name.c_str()) , LoggerType::Critical);
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
            module = iter->second;
            m_status = {true};
        }
    } catch (...) {
    }
    return module;
}

void ModuleManager::unload(Module *&module)
{
    if (module != nullptr)
    {
        LibraryMap::iterator iter = implementationPtr->libs.find(module->getName().value());
        if(iter != implementationPtr->libs.end())
        {
            // Remove the module from our module map.
            implementationPtr->modules.erase(module->getName().value());
            void* hModule = iter->second;
#if defined(PLATFORM_WINDOWS)
            fnDestroyModule DestroyModule = (fnDestroyModule)GetProcAddress(hModule, "DestroyModule");
#elif defined(PLATFORM_MAC)
            fnDestroyModule DestroyModule = (fnDestroyModule)dlsym(hModule, "DestroyModule");
#elif defined(PLATFORM_LINUX)
            fnDestroyModule DestroyModule = (fnDestroyModule)dlsym(hModule, "DestroyModule");
#endif
            if (DestroyModule != nullptr)
            {
                DestroyModule();
            }
            else
            {
                Log("Unable to find symbol \"DestroyModule\" in library \"" + FROM_CELL_STRING(module->getName().value().c_str()) , LoggerType::Critical);
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
            Log("Trying to unload a module that is already unloaded or has never been loaded.", LoggerType::Warning);
        }
        module = nullptr;
    }
}

bool ModuleManager::isLoaded() const
{
    return m_status;
}

CELL_NAMESPACE_END
