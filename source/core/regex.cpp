﻿#ifdef __has_include
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

void Regex::reverse(char s[]) {
    int i, j;
    for (i = strlen(s) - 1, j = 0; j <= i; j++, i--) {
        int t = s[i];
        s[i] = s[j];
        s[j] = t;
    }
}

bool Regex::isEmailValid(const std::string& email)
{
    // define a regular expression
    const std::regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    // try to match the string with the regular expression
    return regex_match(email, pattern);
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
    /*Example usage...
      UNIX: std::string item1 = "\\dir\\dir2\\dir3";
      WINDOWS: std::string item2 = "c:\\folder\\";

     //UNIX: std::cout << item1 << " -> " << change_root(item1, "\\dir1") << std::endl;
     //WINDOWS: std::cout << item2 << " -> " << change_root(item2, "d:")  << std::endl;
     */
}

std::string Regex::repeatedWord(const std::string& input)
{
    std::regex reg1("([A-Za-z]+) \\1");  // Find double word.
    std::string replacement = "$1";      // Replace with one word.
    std::string target = input;
    std::string result = std::regex_replace(target, reg1, replacement);
    return result;
}

bool Regex::isUrlValid (const std::string& url)
{
    std::regex url_s(".*\\..*");
    std::string url_test = url;
    bool CELL_VALID;
    if(regex_match(url_test, url_s)) {
        //std::cout << "It's a url!" << std::endl;
        CELL_VALID = true;
    } else {
        //std::cout << "Oh snap! It's not a url!" << std::endl;
        CELL_VALID = false;
    }
    if (CELL_VALID == true) { return true; } else {return false;}
}

bool Regex::isIpv4Valid(const std::string& input)
{
    // define a regular expression
    const std::regex pattern
        ("^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)"
         "\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)"
         "\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)"
         "\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
    if(regex_match(input,pattern))
    {
        return CELL_VALID_IPV4; //return CELL_VALID flag (0x1) = 1
    }
    else
    {
        return CELL_VALID_IPV4;//return CELL_INVALID flag (0x0) = 0
    }
}

bool Regex::isIpv6Valid(const std::string& input)
{
    // define a regular expression
    const std::regex pattern
        ("(([0-9a-fA-F]{1,4}:){7,7}[0-9a-fA-F]{1,4}"
         "|([0-9a-fA-F]{1,4}:){1,7}:|([0-9a-fA-F]{1,4}:){1,6}:[0-9a-fA-F]{1,4}"
         "|([0-9a-fA-F]{1,4}:){1,5}(:[0-9a-fA-F]{1,4}){1,2}"
         "|([0-9a-fA-F]{1,4}:){1,4}(:[0-9a-fA-F]{1,4}){1,3}"
         "|([0-9a-fA-F]{1,4}:){1,3}(:[0-9a-fA-F]{1,4}){1,4}"
         "|([0-9a-fA-F]{1,4}:){1,2}(:[0-9a-fA-F]{1,4}){1,5}"
         "|[0-9a-fA-F]{1,4}:((:[0-9a-fA-F]{1,4}){1,6})"
         "|:((:[0-9a-fA-F]{1,4}){1,7}|:)|fe80:(:[0-9a-fA-F]{0,4}){0,4}%[0-9a-zA-Z]{1,}"
         "|::(ffff(:0{1,4}){0,1}:){0,1}((25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])\\.){3,3}(25[0-5]"
         "|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])|([0-9a-fA-F]{1,4}:){1,4}:((25[0-5]|(2[0-4]"
         "|1{0,1}[0-9]){0,1}[0-9])\\.){3,3}(25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9]))");

    if(regex_match(input,pattern)) {
        return CELL_VALID_IPV6; //return CELL_VALID flag (0x1) = 1
    }
    else
    {
        return CELL_VALID_IPV6;//return CELL_INVALID flag (0x0) = 0
    }
}

bool Regex::isMacValid(const std::string& input)
{
    // define a regular expression
    const std::regex pattern("^([0-9a-fA-F][0-9a-fA-F]:){5}([0-9a-fA-F][0-9a-fA-F])$");
    if(std::regex_match(input,pattern))
    {
        return CELL_VALID_MAC; //return CELL_VALID flag (0x1) = 1
    }
    else
    {
        return CELL_INVALID_MAC;//return CELL_INVALID flag (0x0) = 0
    }
}

bool Regex::isDomainValid(const std::string& input)
{
    // define a regular expression
    const std::regex pattern("^([a-zA-Z0-9]([a-zA-Z0-9\\-]{0,61}[a-zA-Z0-9])?\\.)+[a-zA-Z]{2,6}$");
    if(std::regex_match(input,pattern))
    {
        return CELL_VALID_DOMAIN; //return CELL_VALID flag (0x1) = 1
    }
    else
    {
        return CELL_INVALID_DOMAIN;//return CELL_INVALID flag (0x0) = 0
    }
}

bool Regex::isHttpValid(const std::string& input)
{
    // define a regular expression
    const std::regex pattern("(http:\\/\\/).*");
    if(std::regex_match(input,pattern))
    {
        return CELL_VALID_HTTP; //return CELL_VALID flag (0x1) = 1
    }
    else
    {
        return CELL_INVALID_HTTP;//return CELL_INVALID flag (0x0) = 0
    }
}

bool Regex::isHttpsValid(const std::string& input)
{
    // define a regular expression
    const std::regex pattern("(https:\\/\\/).*");
    if(std::regex_match(input,pattern))
    {
        return CELL_VALID_HTTPS; //return CELL_VALID flag (0x1) = 1
    }
    else
    {
        return CELL_INVALID_HTTPS;//return CELL_INVALID flag (0x0) = 0
    }
}

bool Regex::isFtpValid(const std::string& input)
{
    // define a regular expression
    const std::regex pattern("(ftp:\\/\\/).*");
    if(std::regex_match(input,pattern))
    {
        return CELL_VALID_FTP; //return CELL_VALID flag (0x1) = 1
    }
    else
    {
        return CELL_INVALID_FTP;//return CELL_INVALID flag (0x0) = 0
    }
}

bool Regex::isPasswordValid(const std::string& input, const int &mode, const int &length)
{
    // Safe Password that allow only with a number, a lowercase, a uppercase, and a special character
    // define a regular expression
    // Mode 0 = Simple regex contains (lowercase, upercase and numbers)
    // Mode 1 = Complex regex contains (lowercase, upercase and numbers)
    std::string regPattern;
    std::string lh = regpatch::to_string(length);
    if(mode == CELL_PASSWORD_MODE_1) {
        regPattern = "^(?=.*?[A-Z])(?=.*?[a-z])(?=.*?[0-9])(?=.*?[#?!@$%^&*-]).{" + lh + ",}$";
    } else if(mode == CELL_PASSWORD_MODE_0) {
        regPattern = "^(?=.*?[A-Z])(?=.*?[a-z])(?=.*?[0-9]).{" + lh + ",}$";
    }
    const std::regex pattern (regPattern);
    if(std::regex_match(input,pattern)) {
        return CELL_VALID_PASSWORD; //return CELL_VALID flag (0x1) = 1
    }
    else
    {
        return CELL_INVALID_PASSWORD;//return CELL_INVALID flag (0x0) = 0
    }
}

bool Regex::isAlphanumericValid(const std::string& input)
{
    // define a regular expression
    const std::regex pattern("^(?=.*[a-zA-Z])(?=.*[0-9])[a-zA-Z0-9]+$");
    if(std::regex_match(input,pattern)) {
        return CELL_VALID_ALPHANUMERIC; //return CELL_VALID flag (0x1) = 1
    }
    else
    {
        return CELL_INVALID_ALPHANUMERIC;//return CELL_INVALID flag (0x0) = 0
    }
}

bool Regex::isVariableValid(const std::string& input)
{
    // define a regular expression
    const std::regex pattern("[a-zA-Z_\x7f-\xff][a-zA-Z0-9_\x7f-\xff]*");
    if(std::regex_match(input,pattern)) {
        return CELL_VALID_VARIABLE; //return CELL_VALID flag (0x1) = 1
    }
    else
    {
        return CELL_INVALID_VARIABLE;//return CELL_INVALID flag (0x0) = 0
    }
}

bool Regex::isNumberValid(const std::string& input)
{
    // Valid variable name
    // define a regular expression
    const std::regex pattern("^[0-9]+$");
    if(std::regex_match(input,pattern)) {
        return CELL_VALID_NUMERIC; //return CELL_VALID flag (0x1) = 1
    }
    else
    {
        return CELL_INVALID_NUMERIC;//return CELL_INVALID flag (0x0) = 0
    }
}

bool Regex::isHttpImageurlValid(const std::string& input)
{
    // define a regular expression
    const std::regex pattern("(?:(?:https?)+\\:\\/\\/+[a-zA-Z0-9\\/\\._-]{1,})+(?:(?:jpe?g|png|gif))");
    if(std::regex_match(input,pattern)) {
        return CELL_VALID_URL; //return CELL_VALID flag (0x1) = 1
    }
    else
    {
        return CELL_INVALID_URL;//return CELL_INVALID flag (0x0) = 0
    }
}

bool Regex::isUsernameValid(const std::string& input)
{
    // define a regular expression
    // field username 3-20 chars
    const std::regex pattern ("(?=^.{3,20}$)^[a-zA-Z][a-zA-Z0-9]*[._-]?[a-zA-Z0-9]+$");
    if(std::regex_match(input,pattern))
    {
        return CELL_VALID_USERNAME; //return CELL_VALID flag (0x1) = 1
    }
    else
    {
        return CELL_INVALID_USERNAME;//return CELL_INVALID flag (0x0) = 0
    }
}

bool Regex::isIrMobileValid(const std::string& input)
{
    // This regular expression chack matching Persian mobile numbers it is checking MCI,MTN Irancell and Talya operators
    // Format support: 989140000000 | 9140000000 | 989350000000
    // ("[\\+98|0]?([0-9]|-|[()]){0,2}9[1|2|3|4]([ ]|-|[()]){0,2}(?:[0-9]([ ]|-|[()]){0,2}){8}");
    const std::regex pattern ("([9]|-|[(1)]){0,9}9[1|2|3|4]([ ]|-|[()]){0,2}(?:[0-9]([ ]|-|[()]){0,2}){8}");
    if(std::regex_match(input,pattern))
    {
        return CELL_VALID_MOBILE; //return CELL_VALID flag (0x1) = 1
    }
    else
    {
        return CELL_INVALID_MOBILE;//return CELL_INVALID flag (0x0) = 0
    }
}

bool Regex::isHexValid(const std::string& input)
{
    // define a regular expression
    const std::regex pattern("^(0[xX])?[A-Fa-f0-9]+$");
    if(std::regex_match(input,pattern))
    {
        return CELL_VALID_HEX; //return CELL_VALID flag (0x1) = 1
    }
    else
    {
        return CELL_INVALID_HEX;//return CELL_INVALID flag (0x0) = 0
    }
}

bool Regex::isHtmlValid(const std::string& input)
{
    // define a regular expression
    const std::regex pattern(
        "(<\\s*html[^>]*>(.*?)<\\s*/\\s*html>)"           //html
        "|(<\\s*h1[^>]*>(.*?)<\\s*/\\s*h1>)"              //h1
        "|(<\\s*h2[^>]*>(.*?)<\\s*/\\s*h2>)"              //h2
        "|(<\\s*h3[^>]*>(.*?)<\\s*/\\s*h3>)"              //h3
        "|(<\\s*h4[^>]*>(.*?)<\\s*/\\s*h4>)"              //h4
        "|(<\\s*h5[^>]*>(.*?)<\\s*/\\s*h5>)"              //h5
        "|(<\\s*h6[^>]*>(.*?)<\\s*/\\s*h6>)"              //h6
        "|(<\\s*a[^>]*>(.*?)<\\s*/\\s*a>)"                //Defines a hyperlink
        "|(<\\s*abbr[^>]*>(.*?)<\\s*/\\s*abbr>)"          //Defines an abbreviation or an acronym
        "|(<\\s*acronym[^>]*>(.*?)<\\s*/\\s*acronym>)"    //Not supported in HTML5. Use <abbr> instead.(Defines an acronym).
        "|(<\\s*address[^>]*>(.*?)<\\s*/\\s*address>)"    //Defines contact information for the author/owner of a document
        "|(<\\s*applet[^>]*>(.*?)<\\s*/\\s*applet>)"      //Not supported in HTML5. Use <embed> or <object> instead.(Defines an embedded applet).
        "|(<\\s*address[^>]*>(.*?)<\\s*/\\s*address>)"    //Defines an area inside an image-map
        "|(<\\s*area[^>]*>(.*?)<\\s*/\\s*area>)"          //Defines contact information for the author/owner of a document
        "|(<\\s*article[^>]*>(.*?)<\\s*/\\s*article>)"    //Defines an article
        "|(<\\s*aside[^>]*>(.*?)<\\s*/\\s*aside>)"        //Defines content aside from the page content
        "|(<\\s*audio[^>]*>(.*?)<\\s*/\\s*audio>)"        //Defines sound content
        "|(<\\s*b[^>]*>(.*?)<\\s*/\\s*b>)"                //Defines bold text
        "|(<\\s*base[^>]*>(.*?)<\\s*/\\s*base>)"          //Specifies the base URL/target for all relative URLs in a document
        "|(<\\s*basefont[^>]*>(.*?)<\\s*/\\s*basefont>)"  //Not supported in HTML5. Use CSS instead. Specifies a default color, size, and font for all text in a document.
        "|(<\\s*bdi[^>]*>(.*?)<\\s*/\\s*bdi>)"            //Isolates a part of text that might be formatted in a different direction from other text outside it
        "|(<\\s*bdo[^>]*>(.*?)<\\s*/\\s*bdo>)"            //Overrides the current text direction
        "|(<\\s*big[^>]*>(.*?)<\\s*/\\s*big>)"            //Not supported in HTML5. Use CSS instead.(Defines big text).
        "|(<\\s*blockquote[^>]*>(.*?)<\\s*/\\s*blockquote>)" //Defines a section that is quoted from another source
        "|(<\\s*body[^>]*>(.*?)<\\s*/\\s*body>)"          //Defines the document's body
        "|(<\\s*br[^>]*>(.*?)<\\s*/\\s*br>)"              //Defines a single line break
        "|(<\\s*button[^>]*>(.*?)<\\s*/\\s*button>)"      //Defines a clickable button
        "|(<\\s*canvas[^>]*>(.*?)<\\s*/\\s*canvas>)"      //Used to draw graphics, on the fly, via scripting (usually JavaScript)
        "|(<\\s*caption[^>]*>(.*?)<\\s*/\\s*caption>)"    //Defines a table caption
        "|(<\\s*center[^>]*>(.*?)<\\s*/\\s*center>)"      //Not supported in HTML5. Use CSS instead.
        "|(<\\s*cite[^>]*>(.*?)<\\s*/\\s*cite>)"          //Defines a table caption
        "|(<\\s*caption[^>]*>(.*?)<\\s*/\\s*caption>)"    //Defines the title of a work
        "|(<\\s*code[^>]*>(.*?)<\\s*/\\s*code>)"          //Defines a piece of computer code
        "|(<\\s*col[^>]*>(.*?)<\\s*/\\s*col>)"            //Specifies column properties for each column within a <colgroup> element
        "|(<\\s*hr[^>]*>(.*?)<\\s*/\\s*hr>)"              //Defines a thematic change in the content
        "|(<\\s*title[^>]*>(.*?)<\\s*/\\s*title>)"        //Defines a title for the document
        "|(<\\s*link[^>]*>(.*?)<\\s*/\\s*link >)"         //Defines the relationship between a document and an external resource (most used to link to style sheets)
        "|(<\\s*div[^>]*>(.*?)<\\s*/\\s*div>)"            //div
        "|(<\\s*span[^>]*>(.*?)<\\s*/\\s*span>)"          //span
        "|(<\\s*main[^>]*>(.*?)<\\s*/\\s*main>)"          //Specifies the main content of a document
        "|(<\\s*ul[^>]*>(.*?)<\\s*/\\s*ul>)"              //Defines an unordered list
        "|(<\\s*li[^>]*>(.*?)<\\s*/\\s*li>)"              //Defines a list item
        "|(<\\s*section[^>]*>(.*?)<\\s*/\\s*section>)"    //Defines a section in a document
        "|(<\\s*meta[^>]*>(.*?)<\\s*/\\s*meta>)"          //Defines metadata about an HTML document
        "|(<\\s*label[^>]*>(.*?)<\\s*/\\s*label>)"        //Defines a label for an <input> element
        "|(<\\s*form[^>]*>(.*?)<\\s*/\\s*form>)"          //form
        "|(<\\s*svg[^>]*>(.*?)<\\s*/\\s*svg>)"            //svg
        "|(<\\s*tr[^>]*>(.*?)<\\s*/\\s*tr>)"              //Defines a row in a table
        "|(<\\s*td[^>]*>(.*?)<\\s*/\\s*td>)"              //td
        "|(<\\s*img[^>]*>(.*?)<\\s*/\\s*img>)"            //img
        //Add more...
        );
    if(regex_match(input,pattern))
    {
        return CELL_VALID_HTML; //return CELL_VALID flag (0x1) = 1
    }
    else
    {
        return CELL_INVALID_HTML;//return CELL_INVALID flag (0x0) = 0
    }
}

bool Regex::isBase64Valid(const std::string& input)
{
    // define a regular expression
    const std::regex pattern("^([A-Za-z0-9+/]{4})*([A-Za-z0-9+/]{4}|[A-Za-z0-9+/]{3}=|[A-Za-z0-9+/]{2}==)$");
    if(std::regex_match(input,pattern))
    {
        return CELL_VALID_BASE64; //return CELL_VALID flag (0x1) = 1
    }
    else
    {
        return CELL_INVALID_BASE64;//return CELL_INVALID flag (0x0) = 0
    }
}

bool Regex::isIsbnValid(const std::string& input)
{
    // define a regular expression
    const std::regex pattern("^ISBN\\s(?=[-0-9xX ]{13}$)(?:[0-9]+[- ]){3}[0-9]*[xX0-9]$");
    if(std::regex_match(input,pattern))
    {
        return CELL_VALID_ISBN; //return CELL_VALID flag (0x1) = 1
    }
    else
    {
        return CELL_INVALID_ISBN;//return CELL_INVALID flag (0x0) = 0
    }
}

bool Regex::isPersianValid(const std::wstring& input)
{
    std::wregex pattern(L"[ چجحخهعغفقثصضکمنتالبیسشوپدذرزطظًًٌٍَُِّْ؛«»ةآأإيئؤ؟ءٔ‌ٰژطك‌]+");
    if(std::regex_match(input,pattern)) {
        return CELL_VALID_PERSIAN; //return CELL_VALID flag (0x1) = 1
    }
    else
    {
        return CELL_INVALID_PERSIAN;//return CELL_INVALID flag (0x0) = 0
    }
}

CELL_NAMESPACE_END

