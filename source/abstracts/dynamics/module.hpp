/*!
 * @file        module.hpp
 * @brief       This file is part of the Cell Engine.
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

#include "common.hpp"
#include "moduleschema.hpp"

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

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

protected:
    ModuleInfo* m_moduleInfo;
    friend class AbstractModuleManager;
    void setCodeName(const Types::Optional<Types::u32>& codename);
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
