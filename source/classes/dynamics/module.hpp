/*!
 * @file        module.hpp
 * @brief       This file is part of the Cell System.
 * @details     Module for system.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       29 Apr 2023
 * @copyright   Copyright (c) 2025 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_MODULE_HPP
#define CELL_MODULE_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

#if __has_include("moduleschema.hpp")
#   include "moduleschema.hpp"
#else
#   error "Cell's "moduleschema.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Dynamics)

/**
 * @brief The Module class
 *
 * @note This class is marked with the "__cell_export" attribute, indicating
 *       it is part of the "cell" module for exporting purposes.
 */
class __cell_export Module
{
public:
    CELL_DEFAULT_INTERFACE_OCTORS_WITHOUT_IMPL(Module)

    /*!
     * \brief getCodeName function returns a unique code of module.
     * \returns a code as unique type.
     */
    __cell_no_discard_virtual Types::OptionalString getCodeName()  __cell_const_noexcept = __cell_zero;

    /*!
     * \brief getName function returns name of module.
     * \returns a name as string.
     */
    __cell_no_discard_virtual Types::OptionalString getName()  __cell_const_noexcept = __cell_zero;

    /*!
     * \brief getDescription function returns description of module.
     * \returns a description about module as string.
     */
    __cell_no_discard_virtual Types::OptionalString getDescription()  __cell_const_noexcept = __cell_zero;

    /*!
     * \brief getCompiledDate function returns date of module's compile date.
     * \returns a name as string.
     */
    __cell_no_discard_virtual Types::OptionalString getCompiledDate()  __cell_const_noexcept = __cell_zero;

    /*!
     * \brief getLicense function returns license of module.
     * \returns a license as SystemLicense.
     */
    __cell_no_discard_virtual Types::Optional<SystemLicense> getLicense()  __cell_const_noexcept = __cell_zero;

    /*!
     * \brief getModuleType function returns type of module.
     * \returns a type as ModuleType.
     */
    __cell_no_discard_virtual Types::Optional<ModuleType> getModuleType()  __cell_const_noexcept = __cell_zero;

    /*!
     * \brief getVersion function returns version of module.
     * \returns a version as SemanticVersion.
     */
    __cell_no_discard_virtual Types::Optional<SemanticVersion> getVersion()  __cell_const_noexcept = __cell_zero;

    /*!
     * \brief getAuthor function returns author of module.
     * \returns a name as string.
     */
    __cell_no_discard_virtual Types::OptionalString getAuthor()  __cell_const_noexcept = __cell_zero;

    /*!
     * \brief getUrl function returns url of module.
     * \returns a url as string.
     */
    __cell_no_discard_virtual Types::OptionalString getUrl()  __cell_const_noexcept = __cell_zero;

    /**
     * @brief getPermission function will returns module permission.
     * @return an optional type of permision.
     */
    __cell_no_discard_virtual Types::Optional<ModuleInfo::PermissionType> getPermission()  __cell_const_noexcept = __cell_zero;

    /**
     * @brief getState function will returns module status.
     * @return an optional state.
     */
    __cell_no_discard_virtual Types::Optional<ModuleState> getState()  __cell_const_noexcept = __cell_zero;

    /*!
     * \brief run is action function for modules.
     */
    __cell_virtual void run()  __cell_const_noexcept = __cell_zero;

    /*!
     * \brief runAsTemplate is action function for modules based on template.
     * \param val is a parameter as multi type support.
     */
    template <typename... Args>
    auto runAsTemplate(const auto& val)
    {
        return val;
    }

    /*!
     * \brief type function returns type of module.
     * \returns as ModuleType.
     */
    __cell_virtual ModuleType type() __cell_const_noexcept = __cell_zero;
};

struct MODULES_CONSTANTS final
{
    __cell_static_const_constexpr std::string_view MODULES_ROOT  { CONFIG::SYSTEM_MODULES_FOLDER };
};

/**
 * @brief Class for managing a container of module items.
 */
class ModuleContainer
{
public:
    /**
     * @brief Default constructor for ModuleContainer.
     */
    ModuleContainer() = default;

    /**
     * @brief Registers a module item to the container.
     *
     * @param name The name of the module to register.
     */
    void registerItem(const std::string& name)
    {
        auto bySuffix { name + CONFIG::MODULE_FILE_SUFFIX.data() };
        m_list.push_back(bySuffix);
    }

    /**
     * @brief Gets the list of registered plugin items.
     *
     * @return A vector of strings containing the registered module items.
     */
    std::vector<std::string> getList()
    {
        return m_list;
    }

private:
    std::vector<std::string> m_list; //!< The list of registered module items.
};


CELL_NAMESPACE_END

#endif // CELL_MODULE_HPP
