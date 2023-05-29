#if __has_include("text.hpp")
#   include "text.hpp"
#else
#   error "Cell's "currency.hpp" was not found!"
#endif

#if __has_include("core/core.hpp")
#   include "core/core.hpp"
#else
#   error "Cell's "core/core.hpp" was not found!"
#endif

CELL_USING_NAMESPACE Cell;
CELL_USING_NAMESPACE Cell::System;
CELL_USING_NAMESPACE Cell::Logger;
CELL_USING_NAMESPACE Cell::Types;
CELL_USING_NAMESPACE Cell::JSon;

CELL_NAMESPACE_BEGIN(Cell::Convertors::Text)

Types::OptionalString TextConverter::asciiToText(const std::string& ascii)
{
    std::stringstream ss;
    std::string result;
    std::istringstream iss(ascii);
    int value;

    while (iss >> value) {
        if (value >= 0 && value <= 127) {
            ss << static_cast<char>(value);
        } else {
            std::cerr << "Invalid ASCII code: " << value << std::endl;
            Log("Invalid ASCII code:" + TO_CELL_STRING(value), LoggerType::Critical);
            return Types::OptionalString();
        }
    }

    result = ss.str();
    return Types::OptionalString(result);
}

Types::OptionalString TextConverter::textToAscii(const std::string& text)
{
    std::stringstream ss;
    std::string result;
    for (char c : text) {
        int asciiCode = static_cast<int>(c);
        ss << asciiCode << " ";
    }
    result = ss.str();
    return Types::OptionalString(result);
}

Types::OptionalString TextConverter::hexadecimalToText(const std::string& hex)
{
    std::stringstream ss;
    std::string result;
    std::istringstream iss(hex);

    while (iss.good()) {
        std::string hexCode;
        iss >> hexCode;

        if (hexCode.length() != 2) {
            Log("Invalid hexadecimal code:" + FROM_CELL_STRING(hexCode), LoggerType::Critical);
            return Types::OptionalString();
        }

        try {
            int asciiCode = std::stoi(hexCode, nullptr, 16);
            ss << static_cast<char>(asciiCode);
        } catch (const Exception& e) {
            Log("Invalid hexadecimal code:" + FROM_CELL_STRING(hexCode), LoggerType::Critical);
            return Types::OptionalString();
        }
    }

    result = ss.str();
    return Types::OptionalString(result);
}

Types::OptionalString TextConverter::textToHexadecimal(const std::string& text)
{
    std::stringstream ss;
    std::string result;
    for (char c : text) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c) << " ";
    }
    result = ss.str();
    return Types::OptionalString(result);
}

Types::OptionalString TextConverter::textToBinary(const std::string& text)
{
    std::stringstream ss;
    std::string result;

    for (char c : text) {
        ss << std::bitset<8>(static_cast<unsigned int>(c)) << " ";
    }

    result = ss.str();
    return Types::OptionalString(result);
}

Types::OptionalString TextConverter::binaryToText(const std::string& binary)
{
    std::stringstream ss;
    std::string result;
    std::istringstream iss(binary);

    while (iss.good()) {
        std::string binaryCode;
        iss >> binaryCode;

        if (binaryCode.length() != 8) {
            Log("Invalid binary code:" + FROM_CELL_STRING(binaryCode), LoggerType::Critical);
            return Types::OptionalString();
        }

        try {
            char c = static_cast<char>(std::bitset<8>(binaryCode).to_ulong());
            ss << c;
        } catch (const std::exception& e) {
            Log("Invalid binary code:" + FROM_CELL_STRING(binaryCode), LoggerType::Critical);
            return Types::OptionalString();
        }
    }

    result = ss.str();
    return Types::OptionalString(result);
}

Types::OptionalString TextConverter::octalToText(const std::string& octal)
{
    std::stringstream ss;
    std::string result;
    std::istringstream iss(octal);

    while (iss.good()) {
        std::string octalCode;
        iss >> octalCode;

        try {
            int decimalCode = std::stoi(octalCode, nullptr, 8);
            ss << static_cast<char>(decimalCode);
        } catch (const std::exception& e) {
            // Invalid octal code
            return Types::OptionalString();
        }
    }

    result = ss.str();
    return Types::OptionalString(result);
}

Types::OptionalString TextConverter::textToOctal(const std::string& text)
{
    std::stringstream ss;
    std::string result;

    for (char c : text) {
        ss << std::oct << static_cast<int>(c) << " ";
    }

    result = ss.str();
    return Types::OptionalString(result);
}

Types::OptionalString TextConverter::morseCodeToText(const std::string& morseCode)
{
    std::stringstream ss;
    std::string result;
    std::istringstream iss(morseCode);

    // Define Morse code mapping
    std::unordered_map<std::string, char> morseCodeMap = {
        {".-", 'A'}, {"-...", 'B'}, {"-.-.", 'C'}, {"-..", 'D'}, {".", 'E'},
        {"..-.", 'F'}, {"--.", 'G'}, {"....", 'H'}, {"..", 'I'}, {".---", 'J'},
        {"-.-", 'K'}, {".-..", 'L'}, {"--", 'M'}, {"-.", 'N'}, {"---", 'O'},
        {".--.", 'P'}, {"--.-", 'Q'}, {".-.", 'R'}, {"...", 'S'}, {"-", 'T'},
        {"..-", 'U'}, {"...-", 'V'}, {".--", 'W'}, {"-..-", 'X'}, {"-.--", 'Y'},
        {"--..", 'Z'}, {".----", '1'}, {"..---", '2'}, {"...--", '3'}, {"....-", '4'},
        {".....", '5'}, {"-....", '6'}, {"--...", '7'}, {"---..", '8'}, {"----.", '9'},
        {"-----", '0'}
    };

    while (iss.good()) {
        std::string morseCodeLetter;
        iss >> morseCodeLetter;

        if (morseCodeLetter.empty()) {
            continue;
        }

        if (morseCodeMap.count(morseCodeLetter) > 0) {
            char letter = morseCodeMap[morseCodeLetter];
            ss << letter;
        } else {
            // Invalid Morse code letter
            return Types::OptionalString();
        }
    }

    result = ss.str();
    return Types::OptionalString(result);
}

Types::OptionalString TextConverter::textToMorseCode(const std::string& text)
{
    std::stringstream ss;
    std::string result;

    // Define Morse code mapping
    std::unordered_map<char, std::string> morseCodeMap = {
        {'A', ".-"}, {'B', "-..."}, {'C', "-.-."}, {'D', "-.."}, {'E', "."},
        {'F', "..-."}, {'G', "--."}, {'H', "...."}, {'I', ".."}, {'J', ".---"},
        {'K', "-.-"}, {'L', ".-.."}, {'M', "--"}, {'N', "-."}, {'O', "---"},
        {'P', ".--."}, {'Q', "--.-"}, {'R', ".-."}, {'S', "..."}, {'T', "-"},
        {'U', "..-"}, {'V', "...-"}, {'W', ".--"}, {'X', "-..-"}, {'Y', "-.--"},
        {'Z', "--.."}, {'1', ".----"}, {'2', "..---"}, {'3', "...--"}, {'4', "....-"},
        {'5', "....."}, {'6', "-...."}, {'7', "--..."}, {'8', "---.."}, {'9', "----."},
        {'0', "-----"}
    };

    for (char c : text) {
        if (morseCodeMap.count(c) > 0) {
            std::string morseCodeLetter = morseCodeMap[c];
            ss << morseCodeLetter << " ";
        } else {
            // Invalid character
            return Types::OptionalString();
        }
    }

    result = ss.str();
    return Types::OptionalString(result);
}

Types::OptionalString TextConverter::toUppercase(const std::string& text)
{
    std::string result = text;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return Types::OptionalString(result);
}

Types::OptionalString TextConverter::toLowercase(const std::string& text)
{
    std::string result = text;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return Types::OptionalString(result);
}

Types::OptionalString TextConverter::toRandomcase(const std::string& text)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    std::string result = text;
    for (char& c : result) {
        if (std::isalpha(c)) {
            if (dis(gen) == 0) {
                c = std::tolower(c);
            } else {
                c = std::toupper(c);
            }
        }
    }

    return Types::OptionalString(result);
}

Types::OptionalWString TextConverter::removeAccents(const std::wstring& text)
{
    std::unordered_map<wchar_t, std::wstring> accentMap =
    {
        {L'À', L"A"}, {L'Á', L"A"}, {L'Â', L"A"}, {L'Ã', L"A"}, {L'Ä', L"A"}, {L'Å', L"A"},
         {L'Æ', L"A"}, {L'Ç', L"C"}, {L'È', L"E"}, {L'É', L"E"}, {L'Ê', L"E"}, {L'Ë', L"E"},
          {L'Ì', L"I"}, {L'Í', L"I"}, {L'Î', L"I"}, {L'Ï', L"I"}, {L'Ð', L"D"}, {L'Ñ', L"N"},
           {L'Ò', L"O"}, {L'Ó', L"O"}, {L'Ô', L"O"}, {L'Õ', L"O"}, {L'Ö', L"O"}, {L'Ø', L"O"},
            {L'Ù', L"U"}, {L'Ú', L"U"}, {L'Û', L"U"}, {L'Ü', L"U"}, {L'Ý', L"Y"}, {L'Þ', L"TH"},
             {L'ß', L"ss"}, {L'à', L"a"}, {L'á', L"a"}, {L'â', L"a"}, {L'ã', L"a"}, {L'ä', L"a"},
              {L'å', L"a"}, {L'æ', L"a"}, {L'ç', L"c"}, {L'è', L"e"}, {L'é', L"e"}, {L'ê', L"e"},
               {L'ë', L"e"}, {L'ì', L"i"}, {L'í', L"i"}, {L'î', L"i"}, {L'ï', L"i"}, {L'ð', L"d"},
                {L'ñ', L"n"}, {L'ò', L"o"}, {L'ó', L"o"}, {L'ô', L"o"}, {L'õ', L"o"}, {L'ö', L"o"},
                 {L'ø', L"o"}, {L'ù', L"u"}, {L'ú', L"u"}, {L'û', L"u"}, {L'ü', L"u"}, {L'ý', L"y"},
                  {L'þ', L"th"}, {L'ÿ', L"y"}
    };

    std::wstring result = text;
    for (wchar_t& c : result) {
        if (accentMap.count(c) > 0) {
            c = accentMap[c][0];
        }
    }

    return Types::OptionalWString(result);
}
Types::OptionalString TextConverter::capitalizeWords(const std::string& text)
{
    std::stringstream ss(text);
    std::string word;
    std::string result;

    while (ss >> word) {
        if (!word.empty()) {
            // Capitalize the first letter of the word
            word[0] = std::toupper(word[0]);
            result += word + " ";
        }
    }

    // Remove the trailing whitespace
    if (!result.empty()) {
        result.pop_back();
    }

    return Types::OptionalString(result);
}

Types::OptionalString TextConverter::capitalizeSentence(const std::string& text)
{
    std::string result = text;

    // Capitalize the first letter of the first word
    if (!result.empty() && std::isalpha(result[0])) {
        result[0] = std::toupper(result[0]);
    }

    // Capitalize the first letter after a period (.) or exclamation mark (!)
    for (std::size_t i = 1; i < result.length(); ++i) {
        if (std::isalpha(result[i]) && (result[i - 1] == '.' || result[i - 1] == '!'))
        {
            result[i] = std::toupper(result[i]);
        }
    }

    return Types::OptionalString(result);
}

Types::OptionalString TextConverter::reverseText(const std::string& text)
{
    std::string result = text;
    std::reverse(result.begin(), result.end());
    return Types::OptionalString(result);
}

Types::OptionalString TextConverter::reverseWords(const std::string& text)
{
    std::istringstream iss(text);
    std::string word;
    std::string result;

    while (iss >> word) {
        std::reverse(word.begin(), word.end());
        result += word + " ";
    }

    if (!result.empty()) {
        result.pop_back(); // Remove the trailing space
    }

    return Types::OptionalString(result);
}

Types::OptionalString TextConverter::textToHTML(const std::string& text)
{
    std::ostringstream oss;

    for (const char& c : text) {
        switch (c) {
        case '<':
            oss << "&lt;";
            break;
        case '>':
            oss << "&gt;";
            break;
        case '&':
            oss << "&amp;";
            break;
        case '"':
            oss << "&quot;";
            break;
        case '\'':
            oss << "&apos;";
            break;
        default:
            oss << c;
            break;
        }
    }

    return Types::OptionalString(oss.str());
}

Types::OptionalString TextConverter::htmlToText(const std::string& html)
{
    std::istringstream iss(html);
    std::ostringstream oss;
    std::string encoded;

    while (std::getline(iss, encoded, '&')) {
        std::size_t semicolonPos = encoded.find(';');
        if (semicolonPos != std::string::npos) {
            std::string entity = encoded.substr(0, semicolonPos);
            if (entity[0] == '#') {
                std::string hexValue = entity.substr(1);
                if (!hexValue.empty()) {
                    unsigned long codepoint = std::stoul(hexValue, nullptr, 16);
                    oss << static_cast<char>(codepoint);
                }
            } else {
                if (entity == "lt")
                    oss << '<';
                else if (entity == "gt")
                    oss << '>';
                else if (entity == "amp")
                    oss << '&';
                else if (entity == "quot")
                    oss << '"';
                else if (entity == "apos")
                    oss << '\'';
            }

            if (semicolonPos + 1 < encoded.length())
                oss << encoded.substr(semicolonPos + 1);
        } else {
            oss << encoded;
        }
    }

    return Types::OptionalString(oss.str());
}

Types::OptionalString TextConverter::removeWhitespace(const std::string& text)
{
    std::string result;
    for (char c : text) {
        if (!std::isspace(c)) {
            result += c;
        }
    }
    return Types::OptionalString(result);
}

Types::OptionalString TextConverter::trimWhitespace(const std::string& text)
{
    std::string result = text;
    // Remove leading whitespace
    result.erase(result.begin(), std::find_if(result.begin(), result.end(), [](int ch)
                                              {
                                                  return !std::isspace(ch);
                                              }));

    // Remove trailing whitespace
    result.erase(std::find_if(result.rbegin(), result.rend(), [](int ch)
                              {
                                  return !std::isspace(ch);
                              }).base(), result.end());

    return Types::OptionalString(result);
}

Types::OptionalString TextConverter::removeSpecialCharacters(const std::string& text)
{
    std::string result;
    for (char c : text) {
        if (std::isalnum(c) || std::isspace(c)) {
            result += c;
        }
    }
    return Types::OptionalString(result);
}

Types::OptionalString TextConverter::extractDigits(const std::string& text)
{
    std::string result;
    for (char c : text) {
        if (std::isdigit(c)) {
            result += c;
        }
    }
    return Types::OptionalString(result);
}

Types::OptionalString TextConverter::stripHtmlTags(const std::string& text)
{
    // Define a regex pattern to match HTML tags
    std::regex tagRegex("<[^>]+>");

    // Use std::regex_replace to remove the HTML tags from the text
    std::string result = std::regex_replace(text, tagRegex, "");
    return Types::OptionalString(result);
}

CELL_NAMESPACE_END

