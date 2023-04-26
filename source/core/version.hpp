/*!
 * Gen3 License
 *
 * @file        version.hpp
 * @brief       This file is part of the Cell engine.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     libCell
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 */

#ifndef CELL_VERSION_HPP
#define CELL_VERSION_HPP

#ifdef __has_include
# if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
# endif
#endif

CELL_NAMESPACE_BEGIN(Cell)

/*!
 * \brief The Version class
 */
class __cell_export Version
{
public:
    CELL_DEFAULT_INTERFACE_OCTORS(Version)

    enum class ReleaseType : Types::u8
    {
        PreAlpha,               ///< Pre-alpha refers to all activities performed during the software project before formal testing.
        Alpha,                  ///< The alpha phase of the release life cycle is the first phase of software testing (alpha is the first letter of the Greek alphabet, used as the number 1).
        Beta,                   ///< Beta, named after the second letter of the Greek alphabet, is the software development phase following alpha.
        ReleaseCandidate,       ///< A release candidate (RC), also known as "going silver", is a beta version with potential to be a stable product, which is ready to release unless significant bugs emerge.
        StableRelease           ///< Also called production release, the stable release is the last release candidate (RC) which has passed all verifications / tests. The remaining bugs are considered as acceptable.
    };

    /*!
     * \brief setVersion will sets value to version.
     * \param version is parameter as SemanticVersion.
     */
    void setVersion(const SemanticVersion& version, const ReleaseType releaseType);

    /*!
     * \brief getVersion will gets version data.
     * \returns SemanticVersion.
     */
    SemanticVersion getVersion() __cell_noexcept;

    /*!
     * \brief getAsString will gets version data as string.
     * \returns string of version.
     */
    std::string getAsString() __cell_const __cell_noexcept;

private:
    SemanticVersion* m_SemanticVersion{};
    CELL_DISABLE_COPY(Version)
    CELL_DISABLE_MOVE(Version)
};

CELL_NAMESPACE_END

#endif  // CELL_VERSION_HPP
