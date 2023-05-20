/*!
 * Gen3 License
 *
 * @file        system.hpp
 * @brief       This file is part of the Cell engine.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     libCell
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 */

#ifndef CELL_SYSTEM_HPP
#define CELL_SYSTEM_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell)

struct NetworkInfo final
{
    Types::OptionalString name {};
    Types::OptionalString ip {};
};

class SystemInformation;
/*!
 * \brief The SystemInfo class
 */
class SystemInformation
{
public:
    SystemInformation();
    ~SystemInformation();

    /*!
     * \brief getHostUserName function gets local host username.
     * \returns string of host username.
     */
    static std::string getHostUserName();

    /*!
     * \brief getHostName function gets local host name.
     * \returns string of host name.
     */
    static std::string getHostName();

    /*!
     * \brief getOsName function will gets os name.
     * \returns string of os name.
     */
    static std::string getOsName();

    /*!
     * \brief macAddressAsByteArray
     */
    static std::string macAddressAsByteArray(unsigned char MACData[]);
    /*!
     * \brief getMacAddress function gets Mac Address.
     * \returns string of Mac address.
     */
    static std::string getMacAddress();

    /*!
     * \brief getIpAddress function gets Ip Version 4 Address.
     * \returns as string of ip address.
     */
    static std::string getIpV4Address();

    /*!
     * \brief getIpV6Address function gets Ip Version 6 Address.
     * \returns as string of ip address.
     */
    static std::string getIpV6Address();

    /*!
     * \brief getMachineUniqueId function gets machine unique id.
     * \returns string of uniqueId
     */
    static std::string getMachineUniqueId();

    /*!
     * \brief getSerialNumber function gets setial number
     * \returns as string.
     */
    static std::string getSerialNumber();

    /*!
     * \brief getStorageDiskModel function gets storage disk model.
     * \returns as string.
     */
    static std::string getStorageDiskModel();

    /*!
     * \brief getStorageDiskSerialNumber function gets storage disk model.
     * \returns as string.
     */
    static std::string getStorageDiskSerialNumber();

    /*!
     * \brief getGpuModel function gets gpu type.
     * \returns as string of gpu type.
     */
    static std::string getGpuModel();

private:
    std::list<std::string> m_macAddressList{};

};

CELL_NAMESPACE_END

#endif // CELL_SYSTEM_HPP
