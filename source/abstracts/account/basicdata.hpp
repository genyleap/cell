/*!
 * @file        basicdata.hpp
 * @brief       This file is part of the Cell System.
 * @details     Basic Data interface for system.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2025 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_USER_BASIC_DATA_ABSTRACT_HPP
#define CELL_USER_BASIC_DATA_ABSTRACT_HPP

//! Cell's Common.
#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's common was not found!"
#endif

//! Cell's Abstraction (Interface).
#if __has_include(<abstracts/account>)
#   include <abstracts/account>
#else
#   error "The account abstraction of Cell was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Abstracts::Account)

class Device;
class Activities;
class Timezone;

struct ExtraKey __cell_final
{
    int            keyAsInt    {};
    std::string    keyAsString {};
};

//! Extra option by key and value.
using ExtraField = std::map<ExtraKey*, std::string>;

/*!
 * \brief The UserTypes enum
 */
__cell_enum_class UserTypes
{
    Guest           =   0x1,    //!< As a guest.
    Admin           =   0x2,    //!< As a administrator.
    Master          =   0x3,    //!< As a master/root.
    Moderator       =   0x4,    //!< As a moderator.
    Robot           =   0x5,    //!< As a robot.
    BySystemGroup   =   0x6,    //!< As a system group.
    ByCustomGroup   =   0x7     //!< As a customized group.
};

__cell_enum_class Gender : Types::u8 { Unknown, Male, Female };

__cell_enum_class Editors : Types::u8 { Default, CKEditor, TinyMCE, Other };

struct PhysicalAddress __cell_final
{
    Types::OptionalString country      {}; //!< Country.
    Types::OptionalString state        {}; //!< State.
    Types::OptionalString city         {}; //!< City.
    Types::OptionalString street       {}; //!< Street.
    Types::OptionalString alley        {}; //!< Alley.
    Types::OptionalString plaque       {}; //!< Plaque.
    //!Extra
    Types::Optional<ExtraField> extra  {}; //!< Extra.
};

struct SocialAddress __cell_final
{
    Types::OptionalString google       {}; //!< Google/Gmail.
    Types::OptionalString instagram    {}; //!< Instagram.
    Types::OptionalString twitter      {}; //!< Twitter.
    Types::OptionalString telegram     {}; //!< Telegram.
    Types::OptionalString linkedin     {}; //!< LinkedIn.
    Types::OptionalString facebook     {}; //!< Facebook.
    Types::OptionalString discord      {}; //!< Discord.
    Types::OptionalString whatsapp     {}; //!< WhatsApp.
    Types::OptionalString github       {}; //!< Github.
    //!Extra
    Types::Optional<ExtraField> extra  {}; //!< Extra.
};

struct PersonalLinks __cell_final
{
    Types::Optional<SocialAddress> social  {}; //!< Social Media.
    Types::OptionalString email            {}; //!< Email Address.
    Types::OptionalString web              {}; //!< Personal/Business Website.
    Types::Optional<ExtraField> extra      {}; //!< Extra.
};

struct DateTimesData
{
    Types::OptionalString created      {}; //!< Created time.
    Types::OptionalString lastvisit    {}; //!< Last visit time.
    Types::OptionalString updatedTime  {}; //!< Updated time.
};

struct BanData
{
    Types::OptionalBool   banned   {}; //!< Banned mode.
    Types::OptionalString explain  {}; //!< Ban explain.
    Types::OptionalString until    {}; //!< Ban until.
};

struct UserMedia __cell_final
{
//    Types::Optional<Avatar>  avatar  {}; //!< Avatar.
//    Types::Optional<Image>   image   {}; //!< Image.
//    Types::Optional<Cover>   cover   {}; //!< Cover.
//    Types::Optional<Story>   story   {}; //!< Story.
};

struct PhoneNumbers __cell_final
{
    Types::OptionalString mobile           {}; //!< Mobile Number.
    Types::OptionalString tel              {}; //!< Telephone Number.
    Types::Optional<ExtraField> extra      {}; //!< Extra.
};

struct NetworkAddress __cell_final
{
   Types::OptionalString   ipv4  {}; //!< IP Version 4 Address.
   Types::OptionalString   ipv6  {}; //!< IP Version 6 Address.
   Types::OptionalString   mac   {}; //!< Mac Address.
};

struct MetaStrings __cell_final
{
   Types::OptionalString   bio        {}; //!< Bio Data.
   Types::OptionalString   signature  {}; //!< Signature.
   Types::Optional<ExtraField> extra  {}; //!< Extra.
};

struct Referrals __cell_final
{
   Types::OptionalString   referral  {}; //!< Referral For.
   Types::OptionalString   invited   {}; //!< Invited From.
};

struct UserBasicData __cell_final
{
    //! Raw Numeric
   Types::OptionalNumeric             memberId     {}; //!< User ID.
    //! Raw String
   Types::OptionalString              username     {}; //!< Username.
   Types::OptionalString              firstname    {}; //!< Firstname.
   Types::OptionalString              lastname     {}; //!< Lastname.
   Types::OptionalString              password     {}; //!< Password.
   Types::OptionalString              signature    {}; //!< Signature.
   Types::OptionalString              birthday     {}; //!< Birthday.
   Types::OptionalString              language     {}; //!< Language.
    //! By Classes & Enums.
   Types::Optional<Gender>            gender       {}; //!< Gender.
   Types::Optional<GroupData>         groups       {}; //!< Group.
   Types::Optional<UserMedia>         media        {}; //!< User Media.
   Types::Optional<PhoneNumbers>      phone        {}; //!< Gender.
   Types::Optional<PersonalLinks>     links        {}; //!< Links.
   Types::Optional<SocialAddress>     social       {}; //!< Social Network.
   Types::Optional<PhysicalAddress>   address      {}; //!< Physical Address.
   Types::Optional<NetworkAddress>    networkAddr  {}; //!< Network Address.
   Types::Optional<Timezone*>         timezone     {}; //!< Timezone.
   Types::Optional<Device*>           devices      {}; //!< Devices.
   Types::Optional<Activities*>       activities   {}; //!< User Activities.
   Types::Optional<DateTimesData>     datetime     {}; //!< User Datetimes data.
   Types::Optional<BanData>           ban          {}; //!< Ban Data.
   Types::Optional<Referrals>         referrals    {}; //!< Referrals.
   Types::Optional<MetaStrings>       metastring   {}; //!< Meta String.
   Types::Optional<Editors>           editor       {}; //!< User Editor.
    //! Raw Boolean
   Types::OptionalBool                completed    {}; //!< Completed Mode.
   Types::OptionalBool                subscription {}; //!< Subscription Mode.
   Types::OptionalBool                status       {}; //!< User Status.
    //! Raw ExtraField
   Types::Optional<ExtraField>        extra        {}; //!< Extra Options.
};

CELL_NAMESPACE_END

#endif // CELL_USER_BASIC_DATA_ABSTRACT_HPP
