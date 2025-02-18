/*!
 * @file        device.hpp
 * @brief       This file is part of the Cell System.
 * @details     Device interface for system.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2025 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_DEVICE_ABSTRACT_HPP
#define CELL_DEVICE_ABSTRACT_HPP

//! Cell's Common.
#if __has_include(<common>)
#   include <common>
#else
#   error "Cell's common was not found!"
#endif

//! Cell's Core (Core Only).
#if __has_include(<core>)
#   include <core>
#else
#   error "Cell's requirements was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

enum class DeviceState : Types::u8
{
    Online, Offline
};

struct DeviceInfo final
{
    //!Statics
    Types::OptionalNumeric id          {}; //!< Device ID.
    Types::OptionalString  title       {}; //!< Device Title.
    Types::OptionalString  description {}; //!< Device Description.
    Types::OptionalString  ipAddress   {}; //!< Device IP Address.
    Types::OptionalString  macAddress  {}; //!< Device Mac Address.
    //!Dynamics
//    Optional<Cell::System::DeviceType> type   {}; //!< Device Type (Desktop, Mobile and etc.).
    Types::Optional<DeviceState> state {}; //!< Device State.
};

/*!
 * \brief The AbstractDevice class
 */
class __cell_export AbstractDevice
{
public:
    CELL_DEFAULT_INTERFACE_OCTORS(AbstractDevice)

    /*!
     * \brief set function will registers new device.
     * \param device as array holds DeviceInfo.
     * \returns as boolean.
     */
    __cell_no_discard_virtual bool set(const std::vector<DeviceInfo>& device) __cell_const_noexcept = __cell_zero;

    /*!
     * \brief get function will reterives user-agent data from user's device only.
     * \param memberId as array is unique user id.
     * \returns DeviceInfo as data.
     */
    __cell_no_discard_virtual DeviceInfo get(const std::vector<Types::OptionalNumeric>& memberId) __cell_const_noexcept = __cell_zero;


private:
    DeviceInfo *deviceInfoPtr{};
    CELL_DISABLE_COPY(AbstractDevice)
};

CELL_NAMESPACE_END

#endif  // CELL_DEVICE_ABSTRACT_HPP
