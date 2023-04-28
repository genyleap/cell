#ifdef __has_include
# if __has_include("regex.hpp")
#   include "regex.hpp"
#else
#   error "Cell's "regex.hpp" was not found!"
# endif
#endif

#if defined(_MSC_VER) && _MSC_VER >= 1900
#include <unordered_map>
#include <regex>
#elif defined (__MINGW32__) || defined (__MINGW64_STRINGIFY)
#include <unordered_map>
#include <regex>
#elif defined(__linux__) && !defined(__ANDROID__)
#include <tr1/unordered_map>
#include <tr1/regex>
#include <regex>
#elif defined(__APPLE__) && defined(__MACH__)
#include <regex>
#elif defined (__ANDROID__)
#include <regex>
#endif

CELL_NAMESPACE_BEGIN(Cell::Regexation)

Regex::Regex()
{
}

Regex::~Regex()
{
}

void Regex::reverse(char s[]) {
    int i, j;
    for (i = strlen(s) - 1, j = __cell_zero; j <= i; j++, i--) {
        int t = s[i];
        s[i] = s[j];
        s[j] = t;
    }
}

std::string Regex::vowelReplace(const std::string& input)
{
    // text to transform
    // std::string text = "This is a element and this a unique ID.";
    std::string text = input;
    // regular expression with two capture groups
    const std::regex pattern("(\\ba (a|e|i|u|o))+");
    // the pattern for the transformation, using the second
    // capture group
    std::string replace = "an $2";
    std::string newtext = regex_replace(text, pattern, replace);
    return newtext;
}

std::string Regex::strReplace(const std::string& input ,const std::string& find, const std::string& replace)
{
    // std::string s("Your ability is amazing!");
    std::string s(input);
    while (s.find(find) != std::string::npos)
        s.replace(s.find(find), 3, replace);
    return s;
}

std::string Regex::changeRoot(const std::string& item, const std::string& newroot)
{
    // regular expression
    const std::regex pattern("\\\\?((\\w|:)*)");
    // transformation pattern
    std::string replacer = newroot;
    // flag that indicates to transform only the first match
    std::regex_constants::match_flag_type fonly = std::regex_constants::format_first_only;
    // apply the transformation
    return regex_replace(item, pattern, replacer, fonly);
}

std::string Regex::repeatedWord(const std::string& input)
{
    std::regex reg1("([A-Za-z]+) \\1");  // Find double word.
    std::string replacement = "$1";      // Replace with one word.
    std::string target = input;
    std::string result = std::regex_replace(target, reg1, replacement);
    return result;
}

CELL_NAMESPACE_END

