/*!
 * @file        mediatype.hpp
 * @brief       Media type manager for the Cell Engine.
 * @details     This file defines the Database interface, which provides methods for interacting with a database.
 * @author      Kambiz Asadzadeh
 * @since       07 Jun 2023
 * @version     1.0
 * @note        This is part of the Cell Engine, developed by Kambiz Asadzadeh.
 *
 * @license     This file is licensed under the terms of the Genyleap License. See the LICENSE.md file for more information.
 * @copyright   Copyright (c) 2023 The Genyleap | Kambiz Asadzadeh. All rights reserved.
 * @see         https://github.com/genyleap/cell
 */


#ifndef CELL_MEDIATYPES_HPP
#define CELL_MEDIATYPES_HPP

#ifdef __has_include
# if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
# endif
#endif

CELL_NAMESPACE_BEGIN(Cell::Globals)

/**
 * @brief An extended list of commonly used content types formatted for C++ usage:
 */
struct ContentTypes final
{
    // Text content types
    __cell_static_const_constexpr std::string_view PlainText        {"text/plain"};
    __cell_static_const_constexpr std::string_view HTML             {"text/html"};
    __cell_static_const_constexpr std::string_view CSS              {"text/css"};

    // Application content types
    __cell_static_const_constexpr std::string_view JSON             {"application/json"};
    __cell_static_const_constexpr std::string_view XML              {"application/xml"};
    __cell_static_const_constexpr std::string_view PDF              {"application/pdf"};
    __cell_static_const_constexpr std::string_view ZIP              {"application/zip"};

    // Image content types
    __cell_static_const_constexpr std::string_view JPEG             {"image/jpeg"};
    __cell_static_const_constexpr std::string_view PNG              {"image/png"};
    __cell_static_const_constexpr std::string_view GIF              {"image/gif"};

    // Audio content types
    __cell_static_const_constexpr std::string_view MP3              {"audio/mpeg"};
    __cell_static_const_constexpr std::string_view WAV              {"audio/wav"};

    // Video content types
    __cell_static_const_constexpr std::string_view MP4              {"video/mp4"};
    __cell_static_const_constexpr std::string_view MPEG             {"video/mpeg"};

    // Other content types
    __cell_static_const_constexpr std::string_view OctetStream      {"application/octet-stream"};
    __cell_static_const_constexpr std::string_view JavaScript       {"application/javascript"};
    __cell_static_const_constexpr std::string_view FormUrlEncoded   {"application/x-www-form-urlencoded"};
    __cell_static_const_constexpr std::string_view FormData         {"multipart/form-data"};
};

/**
 * @class MediaTypes
 * @brief Class for handling media types and mime type mappings.
 */
class __cell_export MediaTypes {
public:
    /**
     * @brief Default constructor for the MediaTypes class.
     */
    MediaTypes();

    /**
     * @brief Adds a new mime type mapping to the collection.
     * @tparam Extension Type convertible to std::string representing the file extension.
     * @tparam MimeType Type convertible to std::string representing the mime type.
     * @param extension The file extension.
     * @param mimeType The mime type to associate with the extension.
     */
    template <std::convertible_to<std::string> Extension, std::convertible_to<std::string> MimeType>
    void addMimeType(const Extension& extension, const MimeType& mimeType);

    /**
     * @brief Retrieves the mime type associated with the given file extension.
     * @tparam Extension Type convertible to std::string representing the file extension.
     * @param extension The file extension.
     * @return std::optional<std::string> The mime type associated with the extension, or std::nullopt if not found.
     */
    template <std::convertible_to<std::string> Extension>
    std::string getMimeType(const Extension& extension) const;

private:
    Types::MimeTypes mimeTypes; //!< Internal container for mime type mappings.

};

CELL_NAMESPACE_END

#endif  // CELL_MEDIATYPE_HPP
