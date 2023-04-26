/*!
 * Gen3 License
 *
 * @file        regex.hpp
 * @brief       This file is part of the Cell engine.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     libCell
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 */

#ifndef CELL_CELL_REGEX_HPP
#define CELL_CELL_REGEX_HPP

#ifdef __has_include
# if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
# endif
#endif


CELL_NAMESPACE_BEGIN(Cell::Regexation)

template <typename T>
concept Regexable = requires(T a) {
    { std::regex(a) };
};

namespace Helper::Regex
{
template <typename T> std::string to_string( const T& n )
{
    std::ostringstream stm ;
    stm << n ;
    return stm.str() ;
}
}
/*!
 * \brief The Regex class
 */
class __cell_export Regex {
public:
    Regex();
    ~Regex();

    /*!
     * @brief reverse
     * @param s
     */
    void reverse(char s[]);

    /*!
     * @brief isEmailValid
     * @param email
     * @return
     */
    template <typename T> requires Regexable<T>
        bool isEmailValid(const T& input) {
        const std::regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
        if(std::regex_match(input, pattern))
        {
            return CELL_VALID_EMAIL;
        }
        else
        {
            return CELL_INVALID_EMAIL;
        }
    }

    /*!
     * @brief vowelReplace
     * @param input
     * @return
     */
    std::string vowelReplace(const std::string& input);

    /*!
     * @brief strReplace
     * @param input
     * @param find
     * @param replace
     * @return
     */
    std::string strReplace(const std::string& input, const std::string& find, const std::string& replace);

    /*!
     * @brief changeRoot
     * @param item
     * @param newroot
     * @return
     */
    std::string changeRoot(const std::string& item, const std::string& newroot);

    /*!
     * @brief repeatedWord
     * @param input
     * @return
     */
    std::string repeatedWord(const std::string& input);

    /*!
     * @brief isUrlValid
     * @param url
     * @return
     */
    template <typename T> requires Regexable<T>
        bool isUrlValid(const T& input) {
        const std::regex pattern(".*\\..*");
        if(std::regex_match(input, pattern))
        {
            return CELL_VALID_URL;
        }
        else
        {
            return CELL_INVALID_URL;
        }
    }

    /*!
     * @brief isIpv4Valid
     * @param input
     * @return
     */
    template <typename T> requires Regexable<T>
        bool isIpv4Valid(const T& input) {
        const std::regex pattern
            ("^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)"
             "\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)"
             "\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)"
             "\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
        if(std::regex_match(input, pattern))
        {
            return CELL_VALID_IPV4;
        }
        else
        {
            return CELL_VALID_IPV4;
        }
    }

    /*!
     * @brief isIpv6Valid
     * @param input
     * @return
     */
    template <typename T> requires Regexable<T>
        bool isIpv6Valid(const T& input) {
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
        if(std::regex_match(input, pattern))
        {
            return CELL_VALID_IPV6;
        }
        else
        {
            return CELL_VALID_IPV6;
        }
    }

    /*===============================================
     * Matching Mac Addresses (Physical address)    #
     * ==============================================
     *
     * A MAC address is a unique identifier assigned to most network adapters or
     * network interface cards (NICs) by the manufacturer for identification,
     * IEEE 802 standards use 48 bites or 6 bytes to represent a MAC address. This
     * format gives 281,474,976,710,656 possible unique MAC addresses.*/

    template <typename T> requires Regexable<T>
        bool isMacValid(const T& input) {
        const std::regex pattern("^([0-9a-fA-F][0-9a-fA-F]:){5}([0-9a-fA-F][0-9a-fA-F])$");
        if(std::regex_match(input, pattern))
        {
            return CELL_VALID_MAC;
        }
        else
        {
            return CELL_INVALID_MAC;
        }
    }

    /* ==============================================
     # Domain validation                            #
     * ==============================================
     *
     * The domain name is a component of a uniform resource locator (URL) used to
     access web sites, for example:
     * URL: http://www.example.net/index.html
     * Top-level domain: net
     * Second-level domain: example
     * Host name: www
     * A domain name may point to multiple IP addresses to provide server
     redundancy for the services offered, a feature that is used to manage the
     traffic of large, popular web sites.
     * Web hosting services, on the other hand, run servers that are typically
     assigned only one or a few addresses while serving websites for many domains,
     a technique referred to as virtual web hosting. Such IP address overloading
     requires that each request identifies the domain name being referenced, for
     instance by using the HTTP request header field Host:, or Server Name
     Indication.
    */

    template <typename T> requires Regexable<T>
        bool isDomainValid(const T& input) {
        const std::regex pattern("^([a-zA-Z0-9]([a-zA-Z0-9\\-]{0,61}[a-zA-Z0-9])?\\.)+[a-zA-Z]{2,6}$");
        if(std::regex_match(input, pattern))
        {
            return CELL_VALID_DOMAIN;
        }
        else
        {
            return CELL_INVALID_DOMAIN;
        }
    }

    /* =============================================
     * Http validation
     * =============================================
     *
     * The Hypertext Transfer Protocol (HTTP) is an application protocol for
     * distributed, collaborative, hypermedia information systems. HTTP is the
     * foundation of data communication for the World Wide Web
     */

    template <typename T> requires Regexable<T>
        bool isHttpValid(const T& input) {
        const std::regex pattern("(http:\\/\\/).*");
        if(std::regex_match(input, pattern))
        {
            return CELL_INVALID_HTTP;
        }
        else
        {
            return CELL_INVALID_HTTP;
        }
    }

    /* =============================================
     * Https validation
     * =============================================
     *
     * HTTPS (also called HTTP over TLS, HTTP over SSL, and HTTP Secure) is a
     * protocol for secure communication over a computer network which is widely
     * used on the Internet. HTTPS consists of communication over Hypertext
     * Transfer Protocol (HTTP) within a connection encrypted by Transport Layer
     * Security or its predecessor, Secure Sockets Layer. The main motivation for
     * HTTPS is authentication of the visited website and protection of the
     * privacy and integrity of the exchanged data.
     */

    template <typename T> requires Regexable<T>
        bool isHttpsValid(const T& input) {
        const std::regex pattern("(https:\\/\\/).*");
        if(std::regex_match(input, pattern))
        {
            return CELL_INVALID_HTTPS;
        }
        else
        {
            return CELL_INVALID_HTTPS;
        }
    }

    /* =============================================
     * Ftp validation
     * =============================================
     *
     * The File Transfer Protocol (FTP) is a standard network protocol used to
     * transfer computer files between a client and server on a computer network.
     * FTP is built on a client-server model architecture and uses separate
     * control and data connections between the client and the server.
     */

    /*!
     * @brief isFtpValid
     * @param input
     * @return
     */    
    template <typename T> requires Regexable<T>
        bool isFtpValid(const T& input) {
        const std::regex pattern("(ftp:\\/\\/).*");
        if(std::regex_match(input, pattern))
        {
            return CELL_VALID_FTP;
        }
        else
        {
            return CELL_INVALID_FTP;
        }
    }

    /*!
     * @brief isPasswordValid
     * @param input
     * @param mode
     * @param length
     * @return
     */
    template <typename T> requires Regexable<T>
        bool isPasswordValid(const T& input, const T mode, const T& length) {
        // Safe Password that allow only with a number, a lowercase, a uppercase, and a special character
        // define a regular expression
        // Mode 0 = Simple regex contains (lowercase, upercase and numbers)
        // Mode 1 = Complex regex contains (lowercase, upercase and numbers)
        std::string regPattern;
        std::string lh = Helper::Regex::to_string(length);
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

    /*!
     * @brief isAlphanumericValid
     * @param input
     * @return
     */
    template <typename T> requires Regexable<T>
        bool isAlphanumericValid(const T& input) {
        const std::regex pattern("^(?=.*[a-zA-Z])(?=.*[0-9])[a-zA-Z0-9]+$");
        if(std::regex_match(input, pattern))
        {
            return CELL_VALID_ALPHANUMERIC;
        }
        else
        {
            return CELL_INVALID_ALPHANUMERIC;
        }
    }

    /*!
     * @brief isNumberValid
     * @param input
     * @return
     */
    template <typename T> requires Regexable<T>
        bool isNumberValid(const T& input) {
        const std::regex pattern("^[0-9]+$");
        if(std::regex_match(input, pattern))
        {
            return CELL_VALID_NUMERIC;
        }
        else
        {
            return CELL_INVALID_NUMERIC;
        }
    }

    /*!
     * @brief isVariableValid
     * @param input
     * @return
     */    
    template <typename T> requires Regexable<T>
        bool isVariableValid(const T& input) {
        const std::regex pattern("[a-zA-Z_\x7f-\xff][a-zA-Z0-9_\x7f-\xff]*");
        if(std::regex_match(input, pattern))
        {
            return CELL_VALID_VARIABLE;
        }
        else
        {
            return CELL_INVALID_VARIABLE;
        }
    }

    /*!
     * @brief isHttpImageurlValid
     * @param input
     * @return
     */    
    template <typename T> requires Regexable<T>
        bool isHttpImageUrlValid(const T& input) {
        const std::regex pattern("(?:(?:https?)+\\:\\/\\/+[a-zA-Z0-9\\/\\._-]{1,})+(?:(?:jpe?g|png|gif))");
        if(std::regex_match(input, pattern))
        {
            return CELL_VALID_ISBN;
        }
        else
        {
            return CELL_INVALID_ISBN;
        }
    }

    /*!
     * @brief isUsernameValid
     * @param input
     * @return
     */
    template <typename T> requires Regexable<T>
        bool isUsernameValid(const T& input) {
        const std::regex pattern("(?=^.{3,20}$)^[a-zA-Z][a-zA-Z0-9]*[._-]?[a-zA-Z0-9]+$");
        if(std::regex_match(input, pattern))
        {
            return CELL_VALID_USERNAME;
        }
        else
        {
            return CELL_INVALID_USERNAME;
        }
    }

    /* =============================================
     * ISBN (International Standard Book Number)
     * =============================================
     *
     * ISBN is the acronym for International Standard Book Number. This 10 or
     * 13-digit number identifies a specific book, an edition of a book, or a
     * book-like product (such as an audiobook). Since 1970 each published book
     * has a unique ISBN. In 2007, assigned ISBNs changed from 10 digits to 13.
     */
    template <typename T> requires Regexable<T>
        bool isIsbnValid(const T& input) {
        const std::regex pattern("^ISBN\\s(?=[-0-9xX ]{13}$)(?:[0-9]+[- ]){3}[0-9]*[xX0-9]$");
        if(std::regex_match(input, pattern))
        {
            return CELL_VALID_ISBN;
        }
        else
        {
            return CELL_INVALID_ISBN;
        }
    }

    /*!
     * @brief isIrMobileValid
     * @param input
     * @return
     */

    template <typename T> requires Regexable<T>
        bool isIrMobileValid(const T& input) {
        const std::regex pattern("(9|09|98\\d)\\d{9}");
        if(std::regex_match(input, pattern))
        {
            return CELL_VALID_MOBILE;
        }
        else
        {
            return CELL_INVALID_MOBILE;
        }
    }

    /* =============================================
     * Hex validation
     * =============================================
     *
     * In mathematics and computing, hexadecimal (also base 16, or hex) is a
     * positional numeral system with a radix, or base, of 16. It uses sixteen
     * distinct symbols, most often the symbols 0–9 to represent values zero to
     * nine, and A, B, C, D, E, F (or alternatively a, b, c, d, e, f) to represent
     * values ten to fifteen. Hexadecimal numerals are widely used by computer
     * system designers and programmers. Several different notations are used to
     * represent hexadecimal constants in computing languages; the prefix "0x" is
     * widespread due to its use in Unix and C (and related operating systems and
     * languages). Alternatively, some authors denote hexadecimal values using a
     * suffix or subscript. For example, one could write 0x2AF3 or 2AF316,
     * depending on the choice of notation.
     */

    template <typename T> requires Regexable<T>
        bool isHexValid(const T& input) {
        const std::regex pattern("^(0[xX])?[A-Fa-f0-9]+$");
        if(std::regex_match(input, pattern))
        {
            return CELL_VALID_HEX;
        }
        else
        {
            return CELL_INVALID_HEX;
        }
    }

    /* =============================================
     * HTML tag validation
     * =============================================
     *
     * Hypertext Markup Language, a standardized system for tagging text files to
     * achieve font, colour, graphic, and hyperlink effects on World Wide Web
     * pages.
     */

    template <typename T> requires Regexable<T>
        bool isHtmlValid(const T& input) {
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
        if(std::regex_match(input, pattern))
        {
            return CELL_VALID_HTML;
        }
        else
        {
            return CELL_INVALID_HTML;
        }
    }



    /* =============================================
     * Base64_encode — Encodes data with MIME base64
     * =============================================
     *
     * Base64 is a group of similar binary-to-text encoding schemes that represent
     * binary data in an ASCII string format by translating it into a radix-64
     * representation. The term Base64 originates from a specific MIME content
     * transfer encoding.
     */

    template <typename T> requires Regexable<T>
        bool isBase64Valid(const T& input) {
        const std::regex pattern("^([A-Za-z0-9+/]{4})*([A-Za-z0-9+/]{4}|[A-Za-z0-9+/]{3}=|[A-Za-z0-9+/]{2}==)$");
        if(std::regex_match(input, pattern))
        {
            return CELL_VALID_BASE64;
        }
        else
        {
            return CELL_INVALID_BASE64;
        }
    }

    /*!
     * \brief isPersianValid
     * \param input
     * \return
     */
    template <typename T> requires Regexable<T>
        bool isPersianValid(const T& input) {
        std::wregex pattern(L"[ چجحخهعغفقثصضکمنتالبیسشوپدذرزطظًًٌٍَُِّْ؛«»ةآأإيئؤ؟ءٔ‌ٰژطك‌]+");
        if(std::regex_match(input, pattern))
        {
            return CELL_VALID_PERSIAN;
        }
        else
        {
            return CELL_INVALID_PERSIAN;
        }
    }
};

CELL_NAMESPACE_END

#endif  // CELL_CELL_REGEX_HPP
