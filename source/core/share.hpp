/*!
 * @file        system.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Share structure for content sharing.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_SHARE_HPP
#define CELL_SHARE_HPP

#ifdef __has_include
# if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
# endif
#endif

CELL_NAMESPACE_BEGIN(Cell)

/*!
 * \brief The ShareMethod enum
 */
__cell_enum_class ShareMethod : Types::u8
{
    InSelf,
    SocialNetwork,
    ByEmail,
    BySms,
    ForApi,
    Custom
};

struct ShareData final
{
    ShareMethod method  {};
    Types::OptionalString link {};
};

/*!
 * \brief The AbstractTags class
 */
class __cell_export Share
{
public:
    CELL_DEFAULT_INTERFACE_OCTORS(Share)

    /*!
     * \brief registerToShare function will share post via share methods.
     * \param shareData is data for sharing.
     */
    void registerToShare(const ShareData& shareData) __cell_const_noexcept;

private:
    CELL_DISABLE_COPY(Share)
    ShareData* m_shareData;
};

CELL_NAMESPACE_END

#endif  // CELL_SHARE_HPP
