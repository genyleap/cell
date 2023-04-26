/*!
 * @file        powersave.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Service interface for system.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_POWERSAVE_ABSTRACT_HPP
#define CELL_POWERSAVE_ABSTRACT_HPP

#include "common.hpp"

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief The PowerSaveStruct class
 */
struct PowerSavingStruct final
{
    Types::u8           batteryEnergy       {10};
    Types::OptionalBool backgroundUpdate    {false};
    Types::OptionalBool preloadMedia        {false};
    Types::OptionalBool interfaceEffect     {false};
    Types::OptionalBool emojiAnimation      {false};
    Types::OptionalBool stickerAnimation    {false};
    Types::OptionalBool autoplayGIFs        {false};
    Types::OptionalBool autoplayVideo       {false};
    Types::OptionalBool autoplayMusic       {false};
};

/*!
 * \brief The PowerSave enum [Resource-Intensive Process]
 */
__cell_enum_class SaveType : Types::u8
{
    BackgroundUpdate        =   0x1,  ///< This option enables background update faster.
    PreloadMedia            =   0x2,  ///< This option enables start loading media while in the service list for faster access.
    InterfaceEffect         =   0x3,  ///< This option enables various effects and animations that make application look amazing.
    EmojiAnimation          =   0x4,  ///< This option enables loop animated emoji in messages, reactions and status.
    StickerAnimation        =   0x5,  ///< This option enables loop animated stickers, play full-screen special effects.
    AutoplayGifs            =   0x6,  ///< This option enables autoplay and loop gifs inside services like chats and in the keyboard.
    AutoplayVideos          =   0x7,  ///< This option enables autoplay and loop video and video message in some services such as chat.
    AutoplayMusic           =   0x8   ///< This option enables autoplay and loop music and sound message in some services such as chat.
};

/*!
 * \brief The LicenseType enum
 */
__cell_enum_class Mode : Types::u8
{
    Automatic =   0x0, ///< Automatically disables all resource-intensive processes when battery is below {%}.
    On        =   0x1, ///< Always off, never reduce power usage and keep all animations even when battery is low.
    Off       =   0x2  ///< Always on, always disable all resource-intensive processes, regardless of the battery charge level.
};

class __cell_export AbstractPowerSave
{
public:
    CELL_DEFAULT_INTERFACE_OCTORS(AbstractPowerSave)

    /*!
     * \brief saveType will gets types of power option.
     * \returns SaveType's options.
     */
    __cell_virtual SaveType saveType() = __cell_zero;

    /*!
     * \brief registerSaveType will sets types for powersaving.
     * \param tp as SaveType.
     */
    __cell_virtual void registerSaveType(const SaveType& tp) = __cell_zero;

private:
    CELL_DISABLE_COPY(AbstractPowerSave)
};

CELL_NAMESPACE_END

#endif  // CELL_POWERSAVE_ABSTRACT_HPP
