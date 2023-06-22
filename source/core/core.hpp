/*!
 * @file        core.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     System core.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_CELL_CORE_HPP
#define CELL_CELL_CORE_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

#if __has_include("core-meta.hpp")
#   include "core-meta.hpp"
#else
#   error "Cell's "core-meta.hpp" was not found!"
#endif

#if __has_include("version.hpp")
#   include "version.hpp"
#else
#   error "Cell's "version.hpp" was not found!"
#endif

#if __has_include("translator/language.hpp")
#   include "translator/language.hpp"
#else
#   error "Cell's "translator/language.hpp" was not found!"
#endif

#if __has_include("translator/translator.hpp")
#   include "translator/translator.hpp"
#else
#   error "Cell's "translator/translator.hpp" was not found!"
#endif

#if __has_include("logger.hpp")
#   include "logger.hpp"
#else
#   error "Cell's "logger.hpp" was not found!"
#endif

#if __has_include("core/console.hpp")
#   include "core/console.hpp"
#else
#   error "Cell's "core/console.hpp" was not found!"
#endif

#if __has_include("format.hpp")
#   include "format.hpp"
#else
#   error "Cell's "format.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::System)

/*!
 * @brief The DeveloperMode is for enable or disable system debuging information.
 */
struct DeveloperMode {
#if defined(BUILD_DEBUG_MODE) || defined(ENABLE_DEVELOPER_MODE)
    inline static bool IsEnable = true;
#else
    inline static bool IsEnable = false;
#endif
};

template <typename T>
/*!
 * @brief IsSet — Determine if a variable is declared and is different than null
 * @return true if var exists and has any value other than null. false otherwise.
 */
__cell_no_discard_message("Checks if the variable has no value.")
    static auto IsSet(T t) __cell_noexcept_expr(true)
{
    if (const auto it = t; it != T {})
        // on success
        return true;
    else
        // on false...
        return false;
}

/*!
 * @brief check if these two are equal
 */
template <typename T1, typename T2>
__cell_no_discard constexpr bool equals(T1 const& first, T2 const& second) __cell_noexcept
{
    return first == second;
}

/*!
 * \brief Replaces the value of obj with new_value and returns the old value of obj. like (std::exchange)
 * \param oldValue
 * \param newValue
 * \returns as replaced value.
 */
template <typename T, typename U = T>
__cell_constexpr T exchange(T& t, U&& newValue)
{
    T old = std::move(t);
    t = std::forward<U>(newValue);
    return old;
}

/**
 * @brief Reduces the usage of std::optional by returning the value if it exists, or a default value if it is empty.
 *
 * @tparam T The type of the optional value.
 * @param optionalValue The optional value to be reduced.
 * @param defaultValue The default value to be returned if the optional value is empty. Defaults to a default-constructed value of type T.
 * @return The value of the optional if it exists, or the default value.
 */
template <typename T>
T reduceOptionalValue(const std::optional<T>& optionalValue, const T& defaultValue = T())
{
    return optionalValue ? *optionalValue : defaultValue;
}

/**
 * @brief Retrieves the value of a std::optional, throwing an exception if the value is not set.
 *
 * @tparam T The type of the optional value.
 * @param opt The optional value to be retrieved.
 * @return The value of the optional if it exists.
 * @throws std::runtime_error if the optional value is not set.
 */
template<typename T>
T retrieveOptionalValue(const std::optional<T>& opt)
{
    if (opt.has_value()) {
        return opt.value();
    } else {
        throw std::runtime_error("Optional value is not set.");
    }
}

template<typename ... Args>
inline std::string stringFormat(const std::string& format, Args ... args)
{
    Types::s8 size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
    if (size <= 0)
    {
        throw std::runtime_error("Error during formatting.");
    }
    std::unique_ptr<char[]> buf(new char[size]);
    snprintf(buf.get(), size, format.c_str(), args ...);
    return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

/*!
 * @brief Invokes the command processor to execute a command.
 * @param cmd holds the commands for function.
 * @return data from terminal.
 */
__cell_no_discard int command(const std::string& cm);

/**
 * @brief This function executes a command specified as a string, captures the output of the command and returns it as a string.
 * @param cmd as a command.
 * @return as string of result.
 */
__cell_no_discard std::string execute(const char* cmd);

/*!
 * @brief Maybe we need to convert stringstream to standard string.
 * @param data as stringstream content.
 * @return as std::string output.
 */
__cell_no_discard std::string convertStream(std::stringstream const& data) __cell_noexcept;

/*!
 * @brief regen url by length fro, the first
 */
template <typename T1, typename T2>
__cell_no_discard std::string_view regenUrl(T1 const& url, T2 const len) __cell_noexcept
{
    if(!url.empty)
        return url.substr(len);
}

/**
 * @brief This is an enumeration (enum) that defines different types of text encoding.
 * Each element of the enum represents a specific encoding type, and can be used to identify or select the encoding when working with text data.
 * The enum contains a range of common text encodings, including UTF-8, UTF-16LE, UTF-16BE, UTF-32LE, UTF-32BE, various ISO-8859 encodings, Windows code pages, Chinese and Japanese encodings, and others.
 * Using an enum to represent text encodings can make code more readable and maintainable, as it provides a clear and concise way to refer to different encodings, and can help prevent errors due to typos or incorrect string literals.
 */
enum class Encoding {
    UTF8,
    UTF16LE,
    UTF16BE,
    UTF32LE,
    UTF32BE,
    ISO8859_1,
    ISO8859_2,
    ISO8859_3,
    ISO8859_4,
    ISO8859_5,
    ISO8859_6,
    ISO8859_7,
    ISO8859_8,
    ISO8859_9,
    ISO8859_10,
    WINDOWS1250,
    WINDOWS1251,
    WINDOWS1252,
    WINDOWS1253,
    WINDOWS1254,
    WINDOWS1255,
    WINDOWS1256,
    WINDOWS1257,
    WINDOWS1258,
    GB2312,
    GBK,
    GB18030,
    BIG5,
    EUCJP,
    SHIFTJIS,
    JOHAB,
    EUCKR,
    KOI8R,
    KOI8U,
    MACCYRILLIC,
    MACROMAN,
    UCS2,
    UNKNOWN
};

using EncodingList = std::map<Encoding, std::string>;

const EncodingList encodingList {
    { Encoding::UTF8, "UTF-8" },
    { Encoding::UTF16LE, "UTF-16LE" },
    { Encoding::UTF16BE, "UTF-16BE" },
    { Encoding::UTF32LE, "UTF-32LE" },
    { Encoding::UTF32BE, "UTF-32BE" },
    { Encoding::ISO8859_1, "ISO-8859-1" },
    { Encoding::ISO8859_2, "ISO-8859-2" },
    { Encoding::ISO8859_3, "ISO-8859-3" },
    { Encoding::ISO8859_4, "ISO-8859-4" },
    { Encoding::ISO8859_5, "ISO-8859-5" },
    { Encoding::ISO8859_6, "ISO-8859-6" },
    { Encoding::ISO8859_7, "ISO-8859-7" },
    { Encoding::ISO8859_8, "ISO-8859-8" },
    { Encoding::ISO8859_9, "ISO-8859-9" },
    { Encoding::ISO8859_10, "ISO-8859-10" },
    { Encoding::WINDOWS1250, "Windows-1250" },
    { Encoding::WINDOWS1251, "Windows-1251" },
    { Encoding::WINDOWS1252, "Windows-1252" },
    { Encoding::WINDOWS1253, "Windows-1253" },
    { Encoding::WINDOWS1254, "Windows-1254" },
    { Encoding::WINDOWS1255, "Windows-1255" },
    { Encoding::WINDOWS1256, "Windows-1256" },
    { Encoding::WINDOWS1257, "Windows-1257" },
    { Encoding::WINDOWS1258, "Windows-1258" },
    { Encoding::GB2312, "GB2312" },
    { Encoding::GBK, "GBK" },
    { Encoding::GB18030, "GB18030" },
    { Encoding::BIG5, "Big5" },
    { Encoding::EUCJP, "EUC-JP" },
    { Encoding::SHIFTJIS, "Shift_JIS" },
    { Encoding::JOHAB, "Johab" },
    { Encoding::EUCKR, "EUC-KR" },
    { Encoding::KOI8R, "KOI8-R" },
    { Encoding::KOI8U, "KOI8-U" },
    { Encoding::MACCYRILLIC, "macCyrillic" },
    { Encoding::MACROMAN, "macRoman" },
    { Encoding::UCS2, "UCS-2" },
    { Encoding::UNKNOWN, "Unknown" }
};



/*!
 * @brief The StorageType enum
 */
enum class StorageType :Types::u8
{
    Empty           =   0x0,
    File            =   0x1,
    MemoryCard      =   0x2,
    Hdd             =   0x3,
    Ssd             =   0x4,
    Cache           =   0x5,
    Database        =   0x6,
    Network         =   0x7
};

enum class UserMode :Types::u8
{
    Guest           =   0x0,
    User            =   0x1,
    Master          =   0x2,
    Customized      =   0x3
};

enum class SyncDevice :Types::u8
{
    Unknown         =   0x0,
    WebOnly         =   0x1,
    Mobile          =   0x2,
    Desktop         =   0x3,
    CrossPlatform   =   0x4
};

enum class HostType :Types::u8
{
    Unknown     =   0x0,
    Windows     =   0x1,
    macOS       =   0x2,
    Linux       =   0x3
};

enum class Service :Types::u8
{
    Local       =   0x0,
    Installed   =   0x1,
    Closed      =   0x2,
    Running     =   0x3
};

enum class IconType :Types::u8
{
    Png,
    Svg,
    FontIcon
};

enum class MediaType :Types::u8
{
    Image,
    Video,
    Canvas
};

enum class ApiModel :Types::u8
{
    Unknown,
    Json,
    Xml,
    GraphQl
};

enum class TerminateType :Types::u8
{
    Unknown,
    Violation,
    UnexpectedError
};

enum class TableType :Types::u8
{
    MixedStruct, //!<Key and Value table
    KeyStruct,   //!<Only key table
    ValueSturct  //!<Only value table [with suffix "l"]
};

struct Termination
{
    /*!
     * @brief It is sometimes necessary to force the system in runtime.
     * @param terminateType is based on reasons for action.
     */
    void terminate(TerminateType terminateType);
};

/*!
 * @brief The ExceptionMode enum
 */
enum class ExceptionMode : Types::u8 {
    Default,        //!< Default exception mode
    StlException,   //!< STL exception mode
    CellException   //!< Cell exception mode
};

/*!
 * @brief The ExceptionData struct
 */
struct ExceptionData {
    std::string message {}; //!< Default message
    std::string file {};    //!< File name associated with the exception
    uint line {};           //!< Line number in the file where the exception occurred
    std::string func {};    //!< Function name where the exception occurred
    std::string info {};    //!< Additional information about the exception
};

/*!
 * @brief The Exception class
 */
class __cell_export Exception : public std::exception {
public:
    /*!
     * @brief The Reason enum
     */
    enum Reason : Types::u8 {
        Core,       //!< Core reason for the exception
        Database,   //!< Database reason for the exception
        Framework,  //!< Framework-related reason for the exception
        IO,         //!< Input/Output-related reason for the exception
        User,       //!< User-defined reason for the exception
        System,     //!< System-related reason for the exception
        Other       //!< Other reason for the exception
    };

    /*!
     * @brief Constructor for the Exception class.
     * @param reason The reason for the exception (Reason enum value).
     * @param message The exception message.
     */
    Exception(const Reason& reason, const std::string& message);

    /*!
     * @brief Destructor for the Exception class
     */
    virtual ~Exception();

    /*!
     * @brief Get the exception message.
     * @return A C-style string representing the exception message.
     */
    virtual const char* what() const throw();

    /*!
     * @brief Get the associated std::runtime_error object.
     *
     * This function returns a reference to the const std::runtime_error object associated with the exception.
     * It allows access to additional information or operations provided by the std::runtime_error class.
     *
     * @return A reference to the const std::runtime_error object.
     */
    virtual const std::runtime_error& getRuntimeError() const;

private:
    ExceptionData* m_exceptionData;     //!< Pointer to the exception data
    std::runtime_error  m_runtimeError; //!< Runtime/exception
    std::string m_message;
};

struct Ping {
    Ping(const std::string& address) : m_address(address) {}
    std::future<bool> ping() const {
        return std::async(std::launch::async, [this]() {
            std::lock_guard<std::mutex> lock(m_mutex);
            // Build the ping command
            std::string command = "ping -c 4 " + m_address;
            // Execute the ping command
            int result = std::system(command.c_str());
            // Check the result of the ping command
            if (result == 0) {
                std::cout << "Ping succeeded." << std::endl;
                return true;
            } else {
                std::cout << "Ping failed." << std::endl;
                return false;
            }
        });
    }
private:
    std::string m_address;
    mutable std::mutex m_mutex;
};

struct __cell_export BootParameter final
{
    bool                            fastBoot       {};      //!< This property is set to true when the system is booted with the highest possible state.
    std::time_t                     initTime       {};      //!< The time spent on execution.
    Types::Optional<std::string>    saveState      {};      //!< The system save state applied during a save operation after execution or completion of the operation..
    Types::Optional<Types::u32>     pageSize       {};      //!< The size of the requested page.
    std::time_t                     pageInitTime   {};      //!< The loading time of the requested page.
    Types::Optional<Types::u32>     pageSpeed      {};      //!< The loading speed of the requested page.
    Types::Optional<Types::s32>     stateIndex     {};      //!< The state of index for any page.
    Types::Optional<HostType>       hostType       {};      //!< This attribute specifies the type of site hosting. for example: Linux
    Types::Optional<StorageType>    storageType    {};      //!< This attribute specifies the type of storage to use.
    Types::Optional<UserMode>       userMode       {};      //!< This attribute specifies the type of user who uses the system.
    Types::Optional<SyncDevice>     syncDevice     {};      //!< This attribute specifies the type of devices that are incellted with the system.
    Types::Optional<SystemType>     systemType     {};      //!< This attribute determines the type of system consumption.
    Types::Optional<SystemLicense>  systemLicense  {};      //!< The type of license to use the system.
    Types::Optional<SystemStatus>   systemStatus   {};      //!< This attribute specifies the state the system is in.
};

class __cell_export MachineInterface
{
public:
    MachineInterface();
    MachineInterface(const BootParameter& bootParameter);
    virtual ~MachineInterface();

    /*!
     * @brief initialize starter!
     */
    virtual void turnOn() = __cell_zero;

    /**
     * @brief turnOff
     */
    virtual void turnOff() = __cell_zero;

    /**
     * @brief reboot
     */
    virtual void reboot() = __cell_zero;

    /*!
     * @brief Getting current fast boot status.
     * @return true if system has been booted as fast as possible.
     */
    virtual bool getFastBoot()  = __cell_zero;

    /*!
     * @brief Getting current system init time duration.
     * @return returns as time.
     */
    virtual std::time_t getInitTime() = __cell_zero;

    /*!
     * @brief Getting current system state.
     * @return returns string of system state, for example version and etc.
     */
    virtual Types::Optional<std::string>  getSaveState() = __cell_zero;

    /*!
     * @brief Getting current loaded page size.
     * @return returns as unsigned int 32 for page size.
     */
    virtual Types::Optional<Types::u32> getPageSize() = __cell_zero;

    /*!
     * @brief Getting current system current page init time duration.
     * @return returns as time.
     */
    virtual std::time_t getPageInitTime() = __cell_zero;

    /*!
     * @brief Getting current page speed load.
     * @return returns as counter of page speed.
     */
    virtual Types::Optional<Types::u32> getPageSpeed() = __cell_zero;

    /*!
     * @brief Getting current system state index.
     * @return returns as signed integer for state index.
     */
    virtual Types::Optional<Types::s32> getStateIndex() = __cell_zero;

    /*!
     * @brief Getting current installed host type.
     * @return returns as HostType enum.
     */
    virtual Types::Optional<HostType> getHostType() = __cell_zero;

    /*!
     * @brief Getting current system user mode.
     * @return returns as UserMode enum.
     */
    virtual Types::Optional<UserMode> getUserMode() = __cell_zero;

    /*!
     * @brief Getting current system sync mode.
     * @return returns as SyncDevice enum.
     */
    virtual Types::Optional<SyncDevice> getSyncMode() = __cell_zero;

    /*!
     * @brief Getting current system type.
     * @return returns as SystemType enum.
     */
    virtual Types::Optional<SystemType> getSystemType() = __cell_zero;

    /*!
     * @brief Getting current system license.
     * @return returns as SystemLicense enum.
     */
    virtual Types::Optional<SystemLicense> getSystemLicense() = __cell_zero;

    /*!
     * @brief Getting current state of the system.
     * @return returns as SystemStatus enum.
     */
    virtual Types::Optional<SystemStatus> getSystemStatus() = __cell_zero;
};

/**
 * @brief The Machine class
 */
struct Machine : public MachineInterface
{
    Machine();
    Machine(const BootParameter& bootParameter);
    ~Machine();
    /*!
     * @brief Getting current fast boot status.
     * @return true if system has been booted as fast as possible.
     */
    bool getFastBoot() override;

    /*!
     * @brief Getting current system init time duration.
     * @return returns as time.
     */
    std::time_t getInitTime() override;

    /*!
     * @brief Getting current system state.
     * @return returns string of system state, for example version and etc.
     */
    Types::Optional<std::string>  getSaveState() override;

    /*!
     * @brief Getting current loaded page size.
     * @return returns as unsigned int 32 for page size.
     */
    Types::Optional<Types::u32> getPageSize() override;

    /*!
     * @brief Getting current system current page init time duration.
     * @return returns as time.
     */
    std::time_t getPageInitTime() override;

    /*!
     * @brief Getting current page speed load.
     * @return returns as counter of page speed.
     */
    Types::Optional<Types::u32> getPageSpeed() override;

    /*!
     * @brief Getting current system state index.
     * @return returns as signed integer for state index.
     */
    Types::Optional<Types::s32> getStateIndex() override;

    /*!
     * @brief Getting current installed host type.
     * @return returns as HostType enum.
     */
    Types::Optional<HostType> getHostType() override;

    /*!
     * @brief Getting current system user mode.
     * @return returns as UserMode enum.
     */
    Types::Optional<UserMode> getUserMode() override;

    /*!
     * @brief Getting current system sync mode.
     * @return returns as SyncDevice enum.
     */
    Types::Optional<SyncDevice> getSyncMode() override;

    /*!
     * @brief Getting current system type.
     * @return returns as SystemType enum.
     */
    Types::Optional<SystemType> getSystemType() override;

    /*!
     * @brief Getting current system license.
     * @return returns as SystemLicense enum.
     */
    Types::Optional<SystemLicense> getSystemLicense() override;

    /*!
     * @brief Getting current state of the system.
     * @return returns as SystemStatus enum.
     */
    Types::Optional<SystemStatus> getSystemStatus() override;

    void turnOn() override;

    void turnOff() override;

    void reboot() override;

private:
    BootParameter m_bootParameter;
};

/**
 * @brief The Engine class
 */
class __cell_export Engine final
{
private:
    //! Disable engine for new instance.
    //! We need to one instance only.
    CELL_DISABLE_COPY(Engine)
    CELL_DISABLE_MOVE(Engine)
    Engine();

public:
    ~Engine();
    static Engine* instance;
    static void destroyInstance();
    static Engine& self();

    /**
     * @brief get function will return MetaEngine class as optional method.
     * @return as static optional class.
     */
    inline static Types::Optional<Meta::MetaEngine>& meta()
    {
        static Types::Optional<Meta::MetaEngine> metaEngine = std::make_optional<Meta::MetaEngine>();
        return metaEngine;
    }

    /*!
     * @brief initialize starter!
     * @return true if the engine starts successfully.
     */
    __cell_no_discard_message("Pay attention! Note that the engine can only be started once.")
    bool start();

    /**
     * @brief stop the engine.
     * @return true if engine status.
     */
    bool stop();

    /**
     * @brief restart the engine.
     * @return true if engine status.
     */
    bool restart();

    /**
     * @brief machine is instance from hardware system.
     * @return as Machine source.
     */
    Machine machine();

    /**
     * @brief isStarted
     * @return
     */
    bool isStarted();

    /*!
     * System copyrights.
     * @brief Please do not delete or modify them, unless, of course, you have a little respect for the developers.
     * @return output as static copyright by system.
     */
    __cell_no_discard static std::string copyright() __cell_noexcept;

    /*!
     * @brief Convert HTML entities to their corresponding characters.
     * @param The input string.
     * @return output as string.
     */
    inline static std::string htmlEntityDecode(const std::string& content);

    /*!
     * @brief String find is used to find the first occurrence of sub-string in the specified string being called upon.
     * @param list contains of strings.
     * @param search is for searching as key.
     * @return true if the desired content is found and replaced.
     */
    inline bool findSubString(const std::vector<std::string>& list, const std::string& search);

    /*!
     * @brief Replace all occurrences of a sub string with new string of data.
     * @param data is a full content.
     * @param toSearch is target.
     * @param replaceStr is string for replace with toSearch.
     */
    inline void findAndReplaceContent(std::string& data, std::string toSearch, std::string replaceStr);

    /*!
     * @brief Replace all links of a sub string with new link.
     * @param data is a full content.
     * @param toSearch is target.
     * @param replaceUrl is string for replace with toSearch.
     */
    inline void findAndReplaceLink(std::string& data, std::string toSearch, std::string replaceUrl);

    /*!
     * @brief There are some differences in the fields of queries for some drivers that we can filter them with this function.
     * @param fields is list of the fields.
     * @return as filtered list of fields.
     */
    std::vector<std::string> filteredQueryFields(Types::VectorString& fields);

    /**
     * @brief The State enum
     */
    enum State { ESCAPED, UNESCAPED };

    /*!
     * @brief The SepratorType enum
     */
    enum class SepratorType :Types::u8
    {
        Comma,
        Dash,
        Slash,
        BackSlash,
        Dot,
        Equal,
        UnderLine,
        Quote,
        DoubleQuote,
        Apostrophe,
        Grave,
        Colon,
        SemiColon,
        Brvbar,
        Lt,
        Gt,
        Percent,
        And,
        Hat,
        Dollar,
        Question,
        Sim,
        Atsign,
        Sharp,
        Exclamation,
        LeftRoundBracket,
        RightRoundBracket,
        LeftSquareBracket,
        RightSquareBracket,
        LeftCurlyBracket,
        RightCurlyBracket
    };

    /**
     * @brief convertMemorySize converts values between different units of measurement.
     * @param bytes
     * @return
     */
    inline Types::OptionalString convertMemorySize(Types::ullong bytes);

    /*!
     * @brief The SepratorStyle enum
     */
    enum class SepratorStyle :Types::u8 { WithSpace, Mixed };

    /*!
     * @brief join function will implode a vector of strings into a comma-separated.
     * @param strings are list of strings.
     * @param sep is character of seprator.
     * @param sepStyle is style of seprator.
     * @return as string of result.
     */
    __cell_no_discard inline std::string join(const Types::VectorString& strings, const SepratorType& sep, const SepratorStyle& sepStyle) __cell_noexcept;

    /*!
     * \brief elementErase function removes certain characters from a string.
     * \param content is the main input of string.
     * \param chars containing the characters to remove.
     */
    inline void elementErase(std::string& input, const std::string& chars) __cell_noexcept;

    /*!
     * \brief whiteSpaceLeading function will reduce multiple whitespaces to a single white space.
     * \param input as string_view.
     * \return final content output after reducing single white space.
     */
    __cell_no_discard inline std::string whiteSpaceReduce(std::string_view input) __cell_noexcept;

    /*!
     * \brief whiteSpaceLeading function will removes leading whitespace from content.
     * \param input as string.
     * \return final content output after leading white spaces.
     */
    __cell_no_discard inline std::string whiteSpaceLeading(std::string_view input) __cell_noexcept;

    /*!
     * @brief  It may help to distinguish between tables and views depending on what your naming convention is.
     * @return string name of prefix.
     */
    inline static std::string tablePrefix();

    /**
     * Table unicode base.
     * @brief   It may help to distinguish between tables and views depending on what your naming convention is.
     * @return  string unicode of unicode.
     */
    inline static std::string tableUnicode();

    /**
     * @brief   It may help to mixing table prefixes for more details.
     * @return  string final table name after mixed.
     */
    inline static std::string mixedTablePrefix(const std::string& p, const std::string& t);

    /**
     * @brief   It may help to mixing table prefixes for more details.
     * @return  string final table name after mixed.
     */
    inline static std::string table(std::string_view tableName, TableType tableType);

    /**
     * @brief It may help to filter tables.
     * @return as tables.
     */
    inline Types::VectorString tableFilter(const Types::VectorString& tables, TableType tableType);

    /*!
     * @brief Sometimes we need to remove dashes from the uri or content based data.
     * @param src is a content source.
     * @return string of final output.
     */
    __cell_no_discard inline std::string removeDashes(const std::string& src) __cell_const_noexcept;

    /*!
     * @brief We need to get current language based on your selected translator value on page.
     * @return string for name of language that is used.
     */
    inline static std::string defaultLanguage();

    /*!
     * @brief Before displaying the contents of the pages, we need to replace some characters.
     * @param content as raw content.
     * @param map as data for replacing.
     * @return content as string.
     */
    std::string inline fullReplacer(const std::string& content, const Types::MapString& map);

    /**
     * @brief The trim function takes a string s as input, removes any leading and trailing whitespace characters from it, and returns the resulting string.
     * @param s as input value.
     * @return a trimmed version of output.
     */
    static std::string trim(std::string_view str);

    /**
     * @brief A function of the engine that performs a case-insensitive comparison of two strings.
     * It takes two std::string parameters and returns a bool indicating whether the strings are equal when compared in a case-insensitive manner.
     * @param variable one.
     * @param variable two.
     * @return as boolean.
     */
    static bool caseInsensitiveCompare(const std::string& l, const std::string& r);

    /*!
     * @brief setLanguage function sets language from user.
     * @param l as language string.
     */
    void setLanguage(const std::string& l);

    /*!
     * @brief getLanguage function will returns language name as string.
     * @return string.
     */
    inline std::string getLanguage();

    /**
     * @brief encodes a string so that it can be safely used as a part of a URL by converting certain characters to their hexadecimal representation.
     * @details URL encoding is the process of encoding special characters and reserved characters in a URL or web address to make sure that it conforms to the uniform resource identifier (URI) specification.
     * URL encoding is used to replace special characters in a URL with their corresponding escape sequences, which consist of a percent sign followed by two hexadecimal digits.
     * For example, the space character ( ) would be encoded as "%20". This is necessary because some special characters have special meanings in a URL and must be encoded to avoid ambiguity or misinterpretation by web servers or browsers.
     *
     * @param str as a input data.
     * @return as encoded string.
     */
    std::string urlEncode(const std::string& str);

    /**
     * @brief escapeJson escapes certain characters in a string so that it can be safely used as a JSON string value.
     * For example, it will replace double quotes with \".
     * @param input as string parameter.
     * @return as string.
     */
    std::string escapeJson(const std::string& input);

    /**
     * @brief unescapeJson does the opposite of escapeJson and will unescape certain characters in a JSON string value.
     * For example, it will replace \" with a double quote.
     * @param input as string parameter.
     * @return as string.
     */
    std::string unescapeJson(const std::string& input);

    /**
     * @brief ping function will pings address.
     * @param address as string.
     * @return status of ping result.
     */
    bool ping(const std::string& address);

    /*!
     * @brief A URI is an identifier of a specific resource. Like a page, or book, or a document.
     * @return uri.
     */
    std::vector <std::string> langUri;

    /*!
     * @brief array Languages available on the system
     * @return map of languages.
     */
    std::map <std::string, std::string> langs();

    /*!
     * @brief array getting language by path
     * @return map of languages based on their path.
     */
    std::map <std::string, std::string> langsByPath(const std::string& path);

    /*!
     * @brief Path reducing function.
     * @return string of reduced path.
     */
    inline std::string reducePath(const std::string& path);

    /*!
     * @brief Services name.
     * @return string services name.
     */
    std::vector <std::string> services;

    /*!
     * @brief Recommended container for module settings.
     * @return array of modules.
     */
    std::vector <std::string> module;

    /*!
     * \brief setIsMultilanguage function will sets bool value into the member.
     */
    void setIsMultilanguage(const bool value);

    /*!
     * \brief isMultilanguage function will returns true if the page url is based on multi-language method such as [en-us, fa-ir].
     * \return bool [true if it's true.]
     */
    __cell_no_discard inline bool isMultilanguage() __cell_const_noexcept;

    /**
     * @brief isFilePath function uses the C++ filesystem library to check if the given parameter is a file or directory path.
     * @param input
     * @return true if it is a path. Otherwise, it returns false, indicating that the parameter is just a string or content.
     */
    __cell_no_discard bool isFilePath(const std::filesystem::path& input);

    /**
     * @brief A function to calculate the time since the last request and sleep for the appropriate amount of time based on the rate limit.
     * @param lastRequestTime as last time for check [Initialize the last request time to the current time].
     * @param rateLimit for delay limitation.
     */
    void delayIfNeeded(std::chrono::time_point<std::chrono::high_resolution_clock>& lastRequestTime, unsigned int rateLimit);

    /**
     * @brief extractValue
     * @param line
     * @return
     */
    inline std::string extractValue(const std::string& line, const std::string& section = ":");

    /*!
     * \brief Lanuage translator engine.
     */

    Translation::Translator& translator();

    bool m_multilang {};

    std::string m_languageStr {__cell_null_str};

    void setPath(const std::string& p);

    mutable std::string currentPath{};

    static Types::OptionalBool isInitialized;

protected:
    Translation::Translator m_translator;
};

/**
 * @brief The EngineController class manages an instance of the Engine class.
 */
class EngineController {
private:
    std::shared_ptr<Engine> enginePtr; //!< Pointer to the Engine instance.
public:
    /**
     * @brief Constructs an EngineController object.
     */
    EngineController();
    /**
     * @brief Retrieves a reference to the Engine instance.
     * @return Reference to the Engine instance.
     */
    Engine& getEngine() const;
};


Scope<Multilangual::Language> createLanguageObject();

Scope<Meta::MetaEngine> createMetaObject();

Types::Optional<Meta::MetaEngine> safeMetaObject() __cell_noexcept;

__cell_no_discard_message("Pay attention! This version of the formatter is safe and has a return value!")
    Types::Optional<Format> safeFormat() __cell_noexcept;

/**
 * @brief Lambda function to safely translate a given language, section, and key.
 *
 * @param language The language code.
 * @param section The translation section.
 * @param key The translation key.
 * @return The translated default value.
 */
inline static const auto& safeTranslate = [](const std::string& language,
                                      const std::string& section,
                                      const std::string& key) {
    return Engine::self().translator().translate(language, section, key).defaultValue();
};

CELL_NAMESPACE_END

#endif // CELL_CORE_HPP
