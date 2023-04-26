/*!
 * @file        service.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Service interface for system.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_SERVICE_ABSTRACT_HPP
#define CELL_SERVICE_ABSTRACT_HPP

#ifdef __has_include
# if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
# endif
#endif

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/*!
 * \brief The ServiceType enum
 * \details Each part of the system can be provided according to the purpose of the service.
 */
__cell_enum_class ServiceType : Types::u8
{
    Self        =   0x1,  ///< This option enables the system to use the desired feature for system's internal purposes only.
    Api         =   0x2,  ///< This option enables the system to use the desired feature for output api purposes only.
    Multi       =   0x3,  ///< This option enables the system to use the desired feature for internal and external purposes only.
    Limited     =   0x4,  ///< This option enables the system to use the desired feature for limited purposes only.
    Customized  =   0x5   ///< This option enables the system to use the desired feature for customized purposes only.
};

/*!
 * \brief The LicenseType enum
 */
__cell_enum_class LicenseType : Types::u8
{
    Free            =   0x0,  ///< Making items as a service based on love <3! (Full Free).
    Commercial      =   0x1,  ///< Making items as a service based on commercial goals.
    Customized      =   0x2   ///< Making items as a service based on terms and conditions.
};

/*!
 * \brief The Status enum
 */
__cell_enum_class Status : Types::u8
{
    Disabled        =   0x0,  ///< Disabled.
    InDevelopment   =   0x2,  ///< In Development.
    Suspended       =   0x3,  ///< Hidden.
    Active          =   0x4   ///< Active.
};

/*!
 * \brief The ActivityType enum
 */
__cell_enum_class ActivityType : Types::u8
{
    DefaultAsNull           =   0x0,    ///< Activated by no limitation.
    BasedOnIp               =   0x1,    ///< Active based on IP Address.
    BasedOnMacAddress       =   0x2,    ///< Active based on Mac Address.
    BasedOnDNS              =   0x3,    ///< Active based on DNS Address [NS1, NS2, ...].
    BasedOnDomainAddress    =   0x4,    ///< Active based on Domain Address [domainname.com].
    BasedOnCustomProperty   =   0x5     ///< Active based on custom propery.
};

/*!
 * \brief The ActivityStruct class
 */
struct ActivityStruct __cell_final { Types::Optional<ActivityType> activityType; };

class __cell_export AbstractActivity
{
public:
    CELL_DEFAULT_INTERFACE_OCTORS(AbstractActivity)

    /*!
     * \brief activeType will gets activated mode for service.
     * \returns ActivityType's options.
     */
    __cell_virtual ActivityType activeType() = __cell_zero;

    /*!
     * \brief registerActiveType will sets active type for service.
     * \param act as ActivityType.
     */
    __cell_virtual void registerActiveType(const ActivityType& act) = __cell_zero;

private:
    CELL_DISABLE_COPY(AbstractActivity)
};

/*!
 * \brief The SettingData class
 */
struct ServiceData __cell_final
{
    Types::OptionalNumeric         uid        {};   ///< Unique identifier.
    Types::OptionalString          title      {};   ///< Title.
    Types::OptionalString          descr      {};   ///< Description.
    Types::Optional<ServiceType>   type       {};   ///< Type based on optional ServiceType.
    Types::Optional<Status>        status     {};   ///< Status of service.
};

/*!
 * \brief The ServiceInfo class
 */
struct ServiceInfo __cell_final
{
    SemanticVersion                 version    {};   ///< Version number.
    Types::Optional<LicenseType>    license    {};   ///< Type of license.
};

/*!
 * \brief The AbstractService class
 */
class __cell_export AbstractService : protected AbstractActivity
{
public:
    CELL_DEFAULT_INTERFACE_OCTORS(AbstractService)

    /*!
     * \brief The UID enum
     */
    enum UID : Types::u8 { Numeric, String, Complex };

    /*!
     * \brief uid is unique number for each service.
     * \returns random number.
     */
    __cell_constexpr_virtual Types::OptionalNumeric uid() __cell_const = __cell_zero;

    /*!
     * \brief title is subject of setting option.
     * \returns string.
     */
    __cell_virtual Types::OptionalString title() = __cell_zero;

    /*!
     * \brief descr is description of setting option.
     * \returns string.
     */
    __cell_virtual Types::OptionalString descr() = __cell_zero;

    /*!
     * \brief service will gets service type value.
     * \returns one of the service types.
     */
    __cell_virtual Types::Optional<ServiceType> service() = __cell_zero;

    /*!
     * \brief status will gets license type.
     * \returns one of the licenses.
     */
    __cell_virtual Types::Optional<LicenseType> license() = __cell_zero;

    /*!
     * \brief version will gets full version of service.
     * \returns based on SemanticVersion class.
     */
    __cell_virtual SemanticVersion version() = __cell_zero;

    /*!
     * \brief status will gets status value from service.
     * \returns one of the Status.
     */
    __cell_virtual Types::Optional<Status> status() = __cell_zero;

    /*!
     * \brief setUid generates unique id for service.
     * \param uid is a numerical type for inserting values into the function.
     */
    __cell_constexpr_virtual void setUid() __cell_const = __cell_zero;

    /*!
     * \brief SetTitle inserts data for the option's title.
     * \param title is a string type for inserting values into the function.
     */
    __cell_virtual void setTitle(const std::string& title) = __cell_zero;

    /*!
     * \brief setDescr inserts data for the option's description.
     * \param descr is a string type for inserting values into the function.
     */
    __cell_virtual void setDescr(const std::string& descr) = __cell_zero;

    /*!
     * \brief setService sets service type for service.
     * \param service is a ServiceType for setting into the function.
     */
    __cell_virtual void setService(const Types::Optional<ServiceType>& service) = __cell_zero;

    /*!
     * \brief setLicense sets license for the service.
     * \param license is a LicenseType for setting into the function.
     */
    __cell_virtual void setLicense(const Types::Optional<LicenseType>& license) = __cell_zero;

    /*!
     * \brief setStatus will change option's status.
     * \param status is a Status type for change the option status.
     */
    __cell_virtual void setStatus(const Types::Optional<Status> status) = __cell_zero;

    /*!
     * \brief setStatus will sets service's version.
     * \param version is a SemanticVersion type.
     */
    __cell_virtual void setVersion(const SemanticVersion& version) = __cell_zero;

private:
    CELL_DISABLE_COPY(AbstractService)
};

CELL_NAMESPACE_END

#endif  // CELL_SERVICE_ABSTRACT_HPP
