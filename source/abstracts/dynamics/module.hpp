/*!
 * @file        module.hpp
 * @brief       This file is part of the Cell System.
 * @details     Module interface for system.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_MODULE_ABSTRACT_HPP
#define CELL_MODULE_ABSTRACT_HPP

//! Cell's Common.
#ifdef __has_include
# if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's common was not found!"
# endif
#endif


CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief The ModuleType enum
 */
__cell_enum_class ModuleType : Types::u8
{
    Index,      //!< For global user service.
    Admin,      //!< For administrator service.
    System,     //!< For system service.
    Service,    //!< For external or internal service.
    Default,    //!< For default global service.
    Custom      //!< For custom global service.
};

/*!
 * \brief The PermissionType enum
 */
__cell_enum_class PermissionType
{
    ReadOnly,
    EditableOnly,
    Restricted,
    FullAccess,
    ByService
};

/*!
 * \brief The ModuleInfo class
 */
struct ModuleInfo __cell_final
{
    Types::Optional<Types::u32>        codeName        {}; //!< A unique code for module.
    Types::OptionalString              name            {}; //!< A name for module.
    Types::OptionalString              description     {}; //!< A description for explanation module.
    Types::OptionalString              compiledDate    {}; //!< Compiled date for module.
    Types::Optional<SystemLicense>     license         {}; //!< License type for module.
    ModuleType                         moduleType      {}; //!< The type of module.
    Types::Optional<SemanticVersion>   version         {}; //!< Version of module.
    Types::OptionalString              author          {}; //!< Author of module.
    Types::OptionalString              url             {}; //!< Url of module.
};


/*!
 * \brief The AbstractBaseClass class
 */
class __cell_export AbstractModule
{
public:
    CELL_DEFAULT_INTERFACE_OCTORS(AbstractModule)

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

protected:
    ModuleInfo* m_moduleInfo;
    friend class AbstractModuleManager;
    void setCodeName(const Types::OptionalString& codename);
    void setName(const Types::OptionalString& name);
    void setDescription(const Types::OptionalString& desc);
    void setCompiledDate(const Types::OptionalString& compiledDate);
    void setLicense(const Types::Optional<SystemLicense>& licese);
    void setModuleType(const ModuleType moduleType);
    void setVersion(const Types::Optional<SemanticVersion>& version);
    void setAuthor(const Types::OptionalString& author);
    void setUrl(const Types::OptionalString& url);

private:
    CELL_DISABLE_COPY(AbstractModule)
};

CELL_NAMESPACE_END

#endif  // CELL_MODULE_ABSTRACT_HPP
