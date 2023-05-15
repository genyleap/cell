#ifdef __has_include
# if __has_include("core.hpp")
#   include "core.hpp"
#else
#   error "Cell's "core.hpp" was not found!"
# endif
#endif

#include "logger.hpp"
#include "config.hpp"
#include "database.hpp"
#include "console.hpp"
#include "terminal.hpp"
#include "translator/language.hpp"

CELL_USING_NAMESPACE Cell::eLogger;

CELL_USING_NAMESPACE Cell::Abstracts;

CELL_NAMESPACE_BEGIN(Cell::System)

Exception::Exception(const Reason& reason, const std::string& message)
{
    m_exceptionData = new ExceptionData();
    std::string eMessage{};
    switch (reason) {
    case Reason::Core:
        eMessage=":[Core]:";
        break;
    case Reason::Framework:
        eMessage=":[Framework]:";
        break;
    case Reason::IO:
        eMessage=":[IO]:";
        break;
    case Reason::User:
        eMessage=":[User]:";
        break;
    case Reason::System:
        eMessage=":[System]:";
        break;
    case Reason::Other:
        eMessage=":[Other]:";
        break;
    default:
        break;
    }
    m_exceptionData->message = message;
}

Exception::~Exception()
{
    __cell_safe_delete(m_exceptionData);
};

const char* Exception::what() const throw()
{
    return m_exceptionData->message.c_str();
}

void Termination::terminate(TerminateType terminateType)
{
    switch (terminateType) {
    case TerminateType::Unknown:
        Log("The system has been terminated for [Unknown] reason!", LoggerType::Info);
        std::exit(EXIT_FAILURE);
        ///ToDo for more handling...
        break;
    case TerminateType::UnexpectedError:
        Log("The system has been terminated for [UnexpectedError] reason!", LoggerType::Info);
        std::exit(EXIT_FAILURE);
        ///ToDo for more handling...
        break;
    case TerminateType::Violation:
        Log("The system has been terminated for [Violation] reason!", LoggerType::Info);
        std::exit(EXIT_FAILURE);
        ///ToDo for more handling...
        break;
    default:
        break;
    }
}

MachineInterface::MachineInterface()
{
}

MachineInterface::~MachineInterface()
{
}

void Machine::turnOn()
{
    //Todo... need to physical api!
}

void Machine::turnOff()
{
    system("shutdown /s /t 0");
}

void Machine::reboot()
{
    system("shutdown /r /t 0");
}


Engine::Engine()
{
    //!< New instances.
    Scope<Configuration> config(new Configuration(ConfigType::File));
    config->init(SectionType::SystemCore);
    if(autoStart) {
        if(start())
        {
            Log("Engine ha set for auto start mode!", LoggerType::Default);
        }
    }
}

CreateSingletonSelf(Engine)

    Engine::~Engine()
{
}

Machine::Machine()
{
    //! Fast Boot
    //! ToDo...
    {
        if(!m_bootParameter.fastBoot) { m_bootParameter.fastBoot = true; }
    }

    //! System Type
    //! ToDo...
    {
        if(!m_bootParameter.systemType) { m_bootParameter.systemType = SystemType::Default; }
    }

    //! Page Init Time
    //! ToDo...
    {
        if(!m_bootParameter.pageInitTime) { m_bootParameter.pageInitTime = 1316615272; }
    }

    //! Page Size
    //! ToDo...
    {
        if(!m_bootParameter.pageSize) { m_bootParameter.pageSize = __cell_zero; }
    }

    //! Page Speed
    //! ToDo...
    {
        if(!m_bootParameter.pageSpeed) { m_bootParameter.pageSpeed = __cell_zero; }
    }

    //! Init Time
    //! ToDo...
    {
        if(!m_bootParameter.initTime) { m_bootParameter.initTime = 1316615272; }
    }

    //! User Mode
    //! ToDo...
    {
        if(!m_bootParameter.userMode) { m_bootParameter.userMode = UserMode::Guest; }
    }

    //! System License
    //! ToDo...
    {
        if(!m_bootParameter.systemLicense) { m_bootParameter.systemLicense = SystemLicense::Free; }
    }

    //! System Status
    //! ToDo...
    {
        if(!m_bootParameter.systemStatus) { m_bootParameter.systemStatus = SystemStatus::Unknown; }
    }


    //! Sync Device
    //! ToDo...
    {
        if(!m_bootParameter.syncDevice) { m_bootParameter.syncDevice = SyncDevice::WebOnly; }
    }

    //! Storage Type
    //! ToDo...
    {
        if(!m_bootParameter.storageType) { m_bootParameter.storageType = StorageType::Empty; }
    }

    //! State Index
    //! ToDo...
    {
        if(!m_bootParameter.stateIndex) { m_bootParameter.stateIndex = 0x1; }
    }

    //! Save State
    //! ToDo...
    {
        if(!m_bootParameter.saveState) { m_bootParameter.saveState = "0x9ax0000000"; }
    }

    //! Host Type
    {
#ifdef PLATFORM_WINDOWS
        m_bootParameter.hostType = HostType::Windows;
#elif defined(PLATFORM_LINUX)
        m_bootParameter.hostType = HostType::Linux;
#elif defined(PLATFORM_MAC)
        m_bootParameter.hostType = HostType::macOS;
#else
        m_bootParameter.hostType = HostType::Unknown;
#endif
    }
}

Machine::Machine(const BootParameter& bootParameter)
{

}

Machine::~Machine()
{

}

bool Machine::getFastBoot()
{
    return m_bootParameter.fastBoot;
}

std::time_t Machine::getInitTime()
{
    return std::time_t();
}

Optional<std::string> Machine::getSaveState()
{
    if (m_bootParameter.saveState) {
        return m_bootParameter.saveState;
    } else {
        return std::nullopt;
    }
}

Optional<u32> Machine::getPageSize()
{
    if (m_bootParameter.pageSize) {
        return m_bootParameter.pageSize;
    } else {
        return std::nullopt;
    }
}

std::time_t Machine::getPageInitTime()
{
    //ToDo...
    return std::time_t();
}

Optional<u32> Machine::getPageSpeed()
{
    if (m_bootParameter.pageSpeed) {
        return m_bootParameter.pageSpeed;
    } else {
        return std::nullopt;
    }
}

Optional<s32> Machine::getStateIndex()
{
    if (m_bootParameter.stateIndex) {
        return m_bootParameter.stateIndex;
    } else {
        return std::nullopt;
    }
}

Optional<HostType> Machine::getHostType()
{
    if (m_bootParameter.hostType) {
        return m_bootParameter.hostType;
    } else {
        return std::nullopt;
    }
}

Optional<UserMode> Machine::getUserMode()
{
    if (m_bootParameter.userMode) {
        return m_bootParameter.userMode;
    } else {
        return std::nullopt;
    }
}

Optional<SyncDevice> Machine::getSyncMode()
{
    if (m_bootParameter.syncDevice) {
        return m_bootParameter.syncDevice;
    } else {
        return std::nullopt;
    }
}

Optional<SystemType> Machine::getSystemType()
{
    if (m_bootParameter.systemType) {
        return m_bootParameter.systemType;
    } else {
        return std::nullopt;
    }
}

Optional<SystemLicense> Machine::getSystemLicense()
{
    if (m_bootParameter.systemLicense) {
        return m_bootParameter.systemLicense;
    } else {
        return std::nullopt;
    }
}

Optional<SystemStatus> Machine::getSystemStatus()
{
    if (m_bootParameter.systemStatus) {
        return m_bootParameter.systemStatus;
    } else {
        return std::nullopt;
    }
}


Translation::Translator& Engine::translator()
{
    return m_translator;
}

OptionalBool Engine::isInitialized = false;

bool Engine::start()
{
    bool res { false };

    // Check if engine has initialized!
    //    if((isInitialized.has_value()) && isInitialized.value())
    //    {
    //        return false;
    //    }


    std::thread t([&]() {
        auto language = Cell::Multilangual::Language();
        Cell::Translation::LanguageFile langFiles { language.languageSupport() };
        m_translator.setFile(langFiles);
        m_translator.parse() ? res = true : false;
    });

    t.join();


    auto config = Configuration(ConfigType::File);
    config.init(SectionType::SystemCore);
    //! Database Connection
    //    Scope<Database::Connection>con(new Database::Connection());
    ApplicationData appData;
    {
        appData.path    = "";
        appData.module  = "starter";
    }
    //    auto lang = Multilangual::Language(appData.path.value());
    //    {
    //        Application::get(appData)->engine->setLanguage(lang.getLanguage());
    //        Application::get(appData)->translator->setFile(lang.languageSupport());
    //    }
    //    //!< Parsing
    //    if(Application::get(appData)->translator->parse()) {
    //        res = true;
    //        if(System::DeveloperMode::IsEnable)
    //            Log("Language data has been parsed!", LoggerType::Done); //!< Parsing Done!
    //    } else {
    //        res = false;
    //        if(System::DeveloperMode::IsEnable)
    //            Log("No parsing...!", LoggerType::Failed);  //!< Parsing Failed!
    //    }
    isInitialized = true;

    Log("Engine has initialized!", LoggerType::Success);

    return res;
}


bool Engine::stop()
{

}

bool Engine::restart()
{

}

Machine Engine::machine()
{
    return Machine();
}

bool Engine::isStarted()
{
    if(isInitialized.has_value() && isInitialized.value())
    {
        return true;
    }
    return false;
}

std::string Engine::copyright() __cell_noexcept
{
#if defined(CELL_COPYRIGHT)
    return CELL_COPYRIGHT;
#else
    // TODO... add output for html template.
    Termination t;
    t.terminate(TerminateType::Violation);
#endif
}

int command(const std::string& cmd)
{
#ifdef PLATFORM_WINDOWS
    PROCESS_INFORMATION pi;
    STARTUPINFO si = { sizeof(si) };
    if (!CreateProcess(NULL, (LPSTR)command, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
        return false;
    WaitForSingleObject(pi.hProcess, INFINITE);
    DWORD exitCode;
    if (!GetExitCodeProcess(pi.hProcess, &exitCode))
        return false;
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return exitCode == 0;
#else
    int result = std::system(cmd.c_str());
    return WIFEXITED(result) && WEXITSTATUS(result) == 0;
#endif
}

__cell_no_discard std::string execute(const char* cmd)
{
    constexpr size_t buffer_size = 4096;
    std::array<char, buffer_size> buffer;
    std::string result;
    std::FILE* pipe = popen(cmd, "r");
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    size_t n;
    while ((n = std::fread(buffer.data(), 1, buffer_size, pipe)) > 0)
    {
        result.append(buffer.data(), n);
    }
    pclose(pipe);
    return result;
}

std::string convertStream(std::stringstream const& data) __cell_noexcept
{
    //ToDo...
    return std::string();
}

std::string Engine::htmlEntityDecode(const std::string& content)
{
    const std::string subs[] = {
        "& #34;",
        "&quot;",
        "& #39;",
        "&apos;",
        "& #38;",
        "&amp;",
        "& #60;",
        "&lt;",
        "& #62;",
        "&gt;",
        "&34;",
        "&39;",
        "&38;",
        "&60;",
        "&62;"
    };

    const std::string reps[] = {
        "\"",
        "\"",
        "'",
        "'",
        "&",
        "&",
        "<",
        "<",
        ">",
        ">",
        "\"",
        "'",
        "&",
        "<",
        ">"
    };

    std::string process = content;
    size_t found;

    for (int j = __cell_zero; j < 15; j++) {
        do {
            found = process.find(subs[j]);
            if (found != std::string::npos)
                process.replace(found, subs[j].length(), reps[j]);
        } while (found != std::string::npos);
    }

    return process;
}

bool Engine::findSubString(const std::vector<std::string>& list, const std::string& search)
{
    for (const std::string& str : list) {
        if (str.find(search) != std::string::npos) {
            return true;
        }
    }
    return false;
}

void Engine::findAndReplaceContent(std::string& data, std::string toSearch, std::string replaceStr)
{
    //! Get the first occurrence
    size_t pos = data.find(toSearch);
    //! Repeat till end is reached
    while (pos != std::string::npos) {
        // Replace this occurrence of Sub String
        data.replace(pos, toSearch.size(), replaceStr);
        // Get the next occurrence from the current position
        pos = data.find(toSearch, pos + replaceStr.size());
    }
}

void Engine::findAndReplaceLink(std::string& data, std::string toSearch, std::string replaceUrl)
{
    //! Get the first occurrence
    size_t pos = data.find(toSearch);
    //! Repeat till end is reached
    while (pos != std::string::npos) {
        // Replace this occurrence of Sub String
        data.replace(pos, toSearch.size(), replaceUrl);
        // Get the next occurrence from the current position
        pos = data.find(toSearch, pos + replaceUrl.size());
    }
}

std::vector<std::string> Engine::filteredQueryFields(VectorString& fields)
{
    //    Scope<Configuration> config(new Configuration(ConfigType::File));
    //    if(config->currentRdbms() == Database::CELL_RDBMS::PostgreSQL)
    //        ///!Nothing...
    //        if(config->currentRdbms() == Database::CELL_RDBMS::MySQL)
    //        {
    //            std::for_each(fields.begin(), fields.end(), [](auto& s){ s.insert(__cell_zero, "`");});
    //            for(auto& s : fields)
    //            {
    //                s+="`";
    //            }
    //        }
    //    return fields;
    return std::vector<std::string>();
}

Types::OptionalString Engine::convertMemorySize(Types::ullong bytes)
{
    const char* units[] = {"B", "KB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB"};
    const int numUnits = sizeof(units) / sizeof(units[0]);
    int index = 0;
    double value = static_cast<double>(bytes);
    while (value >= 1024.0 && index < numUnits - 1) {
        value /= 1024.0;
        index++;
    }
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "%.2f %s", value, units[index]);
    return buffer;
}

std::string Engine::tablePrefix()
{
    //Table prefix
    //    std::string prefix = Configuration::GET["table_prefix"].asString();
    //    if(!prefix)) {
    //        if(System::DeveloperMode::IsEnable)
    //            Log("Table prefix not found!", LoggerType::Warning);
    //    }
    //    return prefix;
    return "tb";
}

std::string Engine::tableUnicode()
{
    //Table unicode
    //    std::string unicode = Configuration::GET["table_unicode"].asString();
    //    if(!unicode)) {
    //        if(System::DeveloperMode::IsEnable)
    //            Log("Table unicode not found!", LoggerType::Warning);
    //    }
    //    return unicode;
    return std::string();
}

std::string Engine::mixedTablePrefix(const std::string& p, const std::string& t)
{
    std::string res;
    res = FROM_CELL_STRING(p) + FROM_CELL_STRING(t);
    if(!res.empty()) {
        if(System::DeveloperMode::IsEnable)
            Log("Table prefix not found!", LoggerType::Warning);
    }
    return res;
}

std::string Engine::table(std::string_view tableName, TableType tableType)
{
    std::string res{};
    res = FROM_CELL_STRING(mixedTablePrefix(tablePrefix(), tableName.data()));
    if(!res.empty()) {
        if(System::DeveloperMode::IsEnable)
            Log("Table not found!", LoggerType::Warning);
    }
    return res;
}

VectorString Engine::tableFilter(const std::vector<std::string>& tables, TableType tableType)
{
    //    std::string valueStruct = Configuration::GET["table_value_struct"].asString();
    //    std::vector<std::string> res{};
    //    switch (tableType)
    //    {
    //    case TableType::MixedStruct:
    //        res=tables;
    //        break;
    //    case TableType::KeyStruct:
    //        res=tables;
    //        for(const auto& t : tables) {
    //            if(t.ends_with(valueStruct)) {
    //                res.erase(std::remove(res.begin(), res.end(), t), res.end());
    //            }
    //        }
    //        break;
    //    case TableType::ValueSturct:
    //        res=tables;
    //        for(const auto& t : tables) {
    //            if(!t.ends_with(valueStruct)) {
    //                res.erase(std::remove(res.begin(), res.end(), t), res.end());
    //            }
    //        }
    //        break;
    //    default:
    //        res=tables;
    //        break;
    //    }

    //    return res;
    return VectorString();
}

std::string Engine::fullReplacer(const std::string& content, const MapString& map)
{
    std::string rawContent = content;
    // Get the first occurrence
    size_t pos;
    for(const auto& r : map) {
        pos = rawContent.find(r.first);
        // Repeat till end is reached
        while( pos != std::string::npos)
        {
            // Replace this occurrence of Sub String
            rawContent.replace(pos, r.first.size(), r.second);
            // Get the next occurrence from the current position
            pos = rawContent.find(r.first, pos + r.first.size());
        }
    }
    return rawContent;
}

std::string Engine::trim(std::string_view str)
{
    // Find the position of the first non-whitespace character
    const auto first = str.find_first_not_of(" \t\n\r\f\v");
    // If the string is all whitespace, return an empty string
    if (first == std::string_view::npos) {
        return "";
    }
    // Find the position of the last non-whitespace character
    const auto last = str.find_last_not_of(" \t\n\r\f\v");
    // Construct and return the trimmed string
    return str.substr(first, last - first + 1).data();
}

bool Engine::caseInsensitiveCompare(const std::string& l, const std::string& r)
{
    return l.size() == r.size() && std::ranges::equal(l, r, [](char c1, char c2) {
               return std::tolower(c1) == std::tolower(c2);
           });
}

void Engine::setLanguage(const std::string& l)
{
    m_languageStr = l;
}

std::string Engine::getLanguage()
{
    return m_languageStr;
}

/**
 * This implementation iterates over each character in the input string str, and keeps alphanumeric and a few other accepted characters intact.
 * Any other characters are percent-encoded using the % symbol followed by the hexadecimal representation of their ASCII code.
 * The resulting percent-encoded string is returned.
 */
std::string Engine::urlEncode(const std::string& str)
{
    std::ostringstream escaped;
    escaped.fill('0');
    escaped << std::hex;
    for (char c : str) {
        // Keep alphanumeric and other safe characters as-is
        if (std::isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
        } else { // Any other characters are percent-encoded
            escaped << std::uppercase;
            escaped << '%' << std::setw(2) << static_cast<int>(static_cast<unsigned char>(c));
            escaped << std::nouppercase;
        }
    }
    return escaped.str();
}

std::string Engine::escapeJson(const std::string &input)
{
    std::string output;
    output.reserve(input.length());
    for (std::string::size_type i = 0; i < input.length(); ++i)
    {
        switch (input[i]) {
        case '"':
            output += "\\\"";
            break;
        case '/':
            output += "\\/";
            break;
        case '\b':
            output += "\\b";
            break;
        case '\f':
            output += "\\f";
            break;
        case '\n':
            output += "\\n";
            break;
        case '\r':
            output += "\\r";
            break;
        case '\t':
            output += "\\t";
            break;
        case '\\':
            output += "\\\\";
            break;
        default:
            output += input[i];
            break;
        }
    }
    return whiteSpaceReduce(output);
}

std::string Engine::unescapeJson(const std::string& input)
{
    State s = UNESCAPED;
    std::string output;
    output.reserve(input.length());

    for (std::string::size_type i = 0; i < input.length(); ++i)
    {
        switch(s)
        {
        case ESCAPED:
        {
            switch(input[i])
            {
            case '"':
                output += '\"';
                break;
            case '/':
                output += '/';
                break;
            case 'b':
                output += '\b';
                break;
            case 'f':
                output += '\f';
                break;
            case 'n':
                output += '\n';
                break;
            case 'r':
                output += '\r';
                break;
            case 't':
                output += '\t';
                break;
            case '\\':
                output += '\\';
                break;
            default:
                output += input[i];
                break;
            }

            s = UNESCAPED;
            break;
        }
        case UNESCAPED:
        {
            switch(input[i])
            {
            case '\\':
                s = ESCAPED;
                break;
            default:
                output += input[i];
                break;
            }
        }
        }
    }
    return output;
}


bool Engine::ping(const std::string& address)
{
    Ping p(address);
    auto future = p.ping();
    bool success = future.get();
    return success ? true : false;
}

std::map <std::string, std::string> Engine::langs()
{
    //    std::map<std::string, std::string> l = {};
    //    //!Getting language from configuration file
    //    for(auto &var : Configuration::GET["langs"]) {
    //        l.insert(Types::PairString(var["uri"].asString(),var["code"].asString()));
    //        this->langUri.push_back("/" + std::string(var["uri"].asString()));
    //        this->langUri.push_back("/" + std::string(var["uri"].asString()) + "/");
    //    }
    //    return l;
    return std::map <std::string, std::string>();
}

std::map <std::string, std::string> Engine::langsByPath(const std::string& path)
{
    //    std::map<std::string, std::string> l = {};
    //    //!Getting language from configuration file
    //    for(auto &var : Configuration::GET["langs"]) {
    //        l.insert(Types::PairString(var["uri"].asString(),var["code"].asString()));
    //        this->langUri.push_back("/" + std::string(var["uri"].asString()));
    //        this->langUri.push_back("/" + std::string(var["uri"].asString()) + "/");
    //        this->langUri.push_back("/" + std::string(var["uri"].asString()) + "/" + std::string(path.empty() ? "" : path));
    //        this->langUri.push_back("/" + std::string(var["uri"].asString()) + "/" + std::string(path.empty() ? "" : path + "/"));
    //    }
    //    return l;
    return std::map <std::string, std::string>();
}

std::string Engine::reducePath(const std::string& path)
{
    std::string pathEnd{};
    std::string cl = defaultLanguage();
    for (const auto& l: langsByPath(path))
    {
        if (path.ends_with("/"))
        {
            pathEnd = {
                "/" + l.first + "/"
            };
        } else {
            pathEnd = {
                "/" + l.first + ""
            };
        }
        if (path == pathEnd) {
            cl = l.second;
        }
    }
    return cl;
}

std::string Engine::removeDashes(const std::string& src) __cell_const_noexcept
{
    std::string command = src;
    command.erase(std::remove(command.begin(), command.end(), '/'), command.end());
    return command;
}

std::string Engine::defaultLanguage()
{
    //Default language
    //    std::string def = Configuration::GET["default_lang"].asString();
    //    return def;
    return std::string();
}

std::string Engine::join(const std::vector<std::string>& strings,  const SepratorType& sep, const SepratorStyle& sepStyle) __cell_noexcept
{
    std::string delim{__cell_null_str};
    switch (sep) {
    case SepratorType::Comma:
        delim=",";
        break;
    case SepratorType::Dash:
        delim="-";
        break;
    case SepratorType::Slash:
        delim="/";
        break;
    case SepratorType::BackSlash:
        delim="\\";
        break;
    case SepratorType::Dot:
        delim=".";
        break;
    case SepratorType::Equal:
        delim="=";
        break;
    case SepratorType::Quote:
        delim="'";
        break;
    case SepratorType::Apostrophe:
        delim="'";
        break;
    case SepratorType::Grave:
        delim="`";
        break;
    case SepratorType::DoubleQuote:
        delim="\"";
        break;
    case SepratorType::Colon:
        delim=":";
        break;
    case SepratorType::SemiColon:
        delim=";";
        break;
    case SepratorType::Brvbar:
        delim="¦";
            break;
    case SepratorType::Lt:
        delim="<";
        break;
    case SepratorType::Gt:
        delim=">";
        break;
    case SepratorType::Percent:
        delim="%";
        break;
    case SepratorType::And:
        delim="&";
        break;
    case SepratorType::Sharp:
        delim="#";
        break;
    case SepratorType::Dollar:
        delim="$";
        break;
    case SepratorType::Atsign:
        delim="@";
        break;
    case SepratorType::Sim:
        delim="~";
        break;
    case SepratorType::Question:
        delim="?";
        break;
    case SepratorType::Exclamation:
        delim="!";
        break;
    case SepratorType::Hat:
        delim="^";
        break;
    case SepratorType::LeftCurlyBracket:
        delim="[";
        break;
    case SepratorType::RightCurlyBracket:
        delim="]";
        break;
    case SepratorType::LeftSquareBracket:
        delim="{";
        break;
    case SepratorType::RightSquareBracket:
        delim="}";
        break;
    case SepratorType::LeftRoundBracket:
        delim="(";
        break;
    case SepratorType::RightRoundBracket:
        delim=")";
        break;
    default:
        delim=",";
        break;
    }

    switch (sepStyle) {
    case SepratorStyle::WithSpace:
        delim.append(" ");
        break;
    case SepratorStyle::Mixed:
        delim.append("");
        break;
    default:
        break;
    }

    const auto res = std::accumulate(
        strings.begin(), strings.end(),
        std::string(),[&delim, sepStyle](const std::string& x, const std::string& y)
        {
            return x.empty() ? y : x + delim + y;
        });

    return res;
}

void Engine::elementErase(std::string& input, const std::string& chars) __cell_noexcept
{
    // Create a view of chars_to_remove as a ranges::set_view
    auto chars_set = chars | std::views::transform([](char c) {
                         return std::ranges::single_view(c);}) | std::views::join| std::views::common;

    // Use std::erase_if with the chars_set to remove the specified characters from the string
    std::erase_if(input, [&chars_set](char c) {
        return std::ranges::find(chars_set, c) != end(chars_set);
    });
}

std::string Engine::whiteSpaceReduce(std::string_view input) __cell_noexcept
{
    // Lambda function to filter out whitespace
    auto is_space = [](char c)
    {
        return std::isspace(c);
    };

    // Create a range that filters out whitespace
    auto range = input | std::views::filter([is_space](char c) { return !is_space(c); });

    // Use the filtered range to create a new string without whitespace
    std::string output{};

    // Append the contents of "range" to "output"
    std::ranges::copy(range, std::back_inserter(output));

    // Return the new string
    return output;
}

std::string Engine::whiteSpaceLeading(std::string_view input) __cell_noexcept
{
    // Define a lambda function named not_space that takes a char and returns whether it is not a white space character.
    auto not_space = [] (char c) {
        return !std::isspace(c);
    };

    // Find the first character in the string that is not a white space character.
    auto begin = std::ranges::find_if(input, not_space);

    // Create a new string that begins with the first non-white space character
    std::string output {
        input.substr(std::distance(input.begin(), begin))
    };

    // Return the new string
    return output;
}

void Engine::setIsMultilanguage(const bool value)
{
    m_multilang = value;
}

bool Engine::isFilePath(const std::filesystem::path& input)
{
    std::filesystem::path path(input);
    return (std::filesystem::is_regular_file(path) || std::filesystem::is_directory(path));
}

// Function to calculate the time since the last request and sleep for the appropriate amount of time.
void Engine::delayIfNeeded(std::chrono::time_point<std::chrono::high_resolution_clock>& lastRequestTime, unsigned int rateLimit)
{
    // Calculate the time since the last request in seconds.
    unsigned int timeSinceLastRequest = std::chrono::duration_cast<std::chrono::duration<unsigned int>>
                                        (std::chrono::high_resolution_clock::now() - lastRequestTime).count();
    // If the time since the last request is less than the rate limit, sleep for the appropriate amount of time.
    if (timeSinceLastRequest < rateLimit) {
        std::this_thread::sleep_for(std::chrono::duration<unsigned int>(rateLimit - timeSinceLastRequest));
    }

    // Update the last request time to the current time.
    lastRequestTime = std::chrono::high_resolution_clock::now();
}

bool Engine::isMultilanguage() const noexcept
{
    bool ret = {false};
    (m_multilang) ? ret = true : false;
    return ret;
}

void Engine::setPath(const std::string &p)
{
    currentPath = p;
}

// Definition of the createEngineObject function
Scope<System::Engine> createEngineObject()
{
    // Allocate memory for a Engine object using 'new'
    Engine* cellEnginePtr = new Engine;
    // Wrap the raw pointer in a unique_ptr and return it
    return std::unique_ptr<Engine>(cellEnginePtr);
}

Types::Optional<Engine> safeEngine() __cell_noexcept
{
    return std::make_optional(Engine());
}

Application::Application(const ApplicationData& appData)
{
    //    __cell_safe_instance_rhs(language, Multilangual::Language, appData.path.value_or(__cell_unknown));
    //    __cell_safe_instance(translator, Translation::Translator);
    //    __cell_safe_instance(appDataPtr, ApplicationData);
    ///!Smart Scopes
    {
        __cell_smart_instance(engine, Engine);
        __cell_smart_instance(version, Version);
        __cell_smart_instance(systemInfo, SystemInfo);
    }
    ///!Inits
    {
        version->setVersion(appData.semanticVersion, appData.releaseType);
        appDataPtr->path = appData.path.value_or(__cell_unknown);
        {
            systemInfo->name = appData.systemInfo.name;
            systemInfo->codeName = appData.systemInfo.codeName;
            systemInfo->compiledDate = appData.systemInfo.compiledDate;
            systemInfo->license = appData.systemInfo.license;
            systemInfo->type = appData.systemInfo.type;
            systemInfo->version = appData.systemInfo.version;
        }
    }
}

Application::~Application()
{
    //    __cell_safe_delete(translator);
    //    __cell_safe_delete(appDataPtr);
    //    __cell_safe_delete(language);
}

Application* Application::appPtr;

ApplicationData* Application::appDataPtr;

Application* Application::get(const ApplicationData& appData)
{
    if (!appPtr)
    {
        __cell_safe_instance_rhs(appPtr, Application, appData);
        {
            appPtr->path() = appData.path.value_or(__cell_unknown);
            appDataPtr->path = appData.path.value_or(__cell_unknown);
            appDataPtr->semanticVersion = appData.semanticVersion;
            appDataPtr->releaseType = appData.releaseType;
        }
    }
    return appPtr;
}

void Application::start()
{
    if(System::DeveloperMode::IsEnable)
        Log("Engine started!", LoggerType::Info); //!< Engine Start...
    {
        Console::print << "Starting..." << newline;
        Console::print << "=================[Cell System Info]=================\n";
        Console::print << newline;
        Console::print << Terminal::NativeTerminal::Primary << " ⇨ ["
                       << __cell_space << systemInfo->name.value() << ""
                       << " - compiled date on : "
                       << systemInfo->compiledDate.value() + " ]" << newline;
        Console::print << Terminal::NativeTerminal::Primary << " ⇨ ["
                       << " code name : "
                       << systemInfo->codeName.value() + " ]"<< " ⇙" << newline;
                              Console::print << Terminal::NativeTerminal::Primary << " ⇨ ["
                       << " version : "
                       << version->getAsString() + " ]"
                       << " ⇙" << newline;
                              Console::print << Terminal::NativeTerminal::Primary << " ⇨ ["
                       << " license type : "
                       << this->license().value() + " ]"
                       << " ⇙" << newline;
                              Console::print << Terminal::NativeTerminal::Primary << " ⇨ ["
                       << " system type : "
                       << this->type().value() + " ]"
                       << " ⇙" << newline;
                              Console::print << newline;
        Console::print << Terminal::NativeTerminal::Default;
        Console::print << "=================[--------------]=================\n";
        Console::print << newline;
    }
}

OptionalString Application::path() __cell_const_noexcept
{
    if(appDataPtr->path == __cell_unknown) {
        if(DeveloperMode::IsEnable)
            Log("No valid uri![Application::path()]", LoggerType::Critical);
        Log("[Application::path() == 'unknown' as ApplicationData]", LoggerType::Critical);
    }
    return appDataPtr->path.value_or(__cell_unknown);
}

OptionalString Application::name() __cell_const_noexcept
{
    return appDataPtr->systemInfo.name.value_or(__cell_unknown);
}

OptionalString Application::codeName() __cell_const_noexcept
{
    return appDataPtr->systemInfo.codeName.value_or(__cell_unknown);
}

OptionalString Application::type() __cell_const_noexcept
{
    std::string res{};
    switch (systemInfo->type.value()) {
    case SystemType::Private:
        res = "Private";
        break;
    case SystemType::General:
        res = "General";
        break;
    case SystemType::Professional:
        res = "Professional";
        break;
    case SystemType::Premium:
        res = "Premium";
        break;
    case SystemType::Default:
        res = "Default";
        break;
    default:
        res = "Default";
        break;
    }
    return res;
}

OptionalString Application::license() __cell_const_noexcept
{
    std::string res{};
    switch (systemInfo->license.value()) {
    case SystemLicense::Commercial:
        res = "Commercial";
        break;
    case SystemLicense::Free:
        res = "Free";
        break;
    default:
        res = "Free";
        break;
    }
    return res;
}

OptionalString Application::model() __cell_const_noexcept
{
    return appDataPtr->systemInfo.codeName.value_or(__cell_unknown);
}

OptionalString Application::module() __cell_const_noexcept
{
    return appDataPtr->module.value_or(__cell_unknown);
}

OptionalString Application::templateErrorId() __cell_const_noexcept
{
    return appDataPtr->templateErrorId.value_or(__cell_unknown);
}

OptionalString Application::templateId() __cell_const_noexcept
{
    return appDataPtr->templateId.value_or(__cell_unknown);
}

CELL_NAMESPACE_END
