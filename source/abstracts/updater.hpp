/*!
 * @file        updater.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Updater interface for system.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2025 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_UPDATER_ABSTRACT_HPP
#define CELL_UPDATER_ABSTRACT_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

#if __has_include("core/version.hpp")
#   include "core/version.hpp"
#else
#   error "Cell's "core/version.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

struct UpdaterData : public Version
{
    Types::Optional<Version>    latestBetaVersion   {}; //!< Latest beta version of software.
    Types::Optional<Version>    latestVersion       {}; //!< Latest version of software.
    Types::Optional<Version>    currentVersion      {}; //!< Current version of software.
    Types::OptionalBool         available           {false};    //!< Update is available!
    Types::OptionalBool         autoUpdate          {false};    //!< Update automatically.
};

/*!
 * \brief The AbstractUpdater class
 */
class __cell_export AbstractUpdater
{
public:
    CELL_DEFAULT_INTERFACE_OCTORS(AbstractUpdater)

    /**
     * @brief checkForUpdates
     */
    __cell_virtual void checkForUpdates() __cell_const_noexcept = __cell_zero;

    /**
     * @brief download
     */
    __cell_virtual void download() __cell_const_noexcept = __cell_zero;

    /**
     * @brief install
     */
    __cell_virtual void install() __cell_const_noexcept = __cell_zero;

    /**
     * @brief update
     */
    __cell_virtual void update() __cell_const_noexcept = __cell_zero;

    /**
     * @brief betaUpdate
     */
    __cell_virtual void betaUpdate() __cell_const_noexcept = __cell_zero;

    /**
     * @brief upgrade
     */
    __cell_virtual void upgrade() __cell_const_noexcept = __cell_zero;

    /**
     * @brief automaticallyUpdate
     * @return
     */
    __cell_no_discard __cell_virtual bool isAutomatically() __cell_const_noexcept = __cell_zero;

    /*!
     * \brief get function will gets output of access string.
     * \returns as final string.
     */
    __cell_no_discard __cell_virtual Types::OptionalString get() __cell_const_noexcept = __cell_zero;

private:
    CELL_DISABLE_COPY(AbstractUpdater)
};

CELL_NAMESPACE_END

#endif  // CELL_UPDATER_ABSTRACT_HPP
