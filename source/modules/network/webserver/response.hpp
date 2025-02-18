#ifndef CELL_WEBSERVER_RESPONSE_HPP
#define CELL_WEBSERVER_RESPONSE_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Network::WebServer)

struct RESPONSE_CONSTANTS final
{
    __cell_static_const_constexpr std::string_view MAX_AGE      {"; Max-Age="};
    __cell_static_const_constexpr std::string_view PATH         {"; Path="};
    __cell_static_const_constexpr std::string_view SET_COOKIE   {"Set-Cookie"};
    __cell_static_const_constexpr std::string_view SESSION_ID   {"sessionId"};
    __cell_static_const_constexpr std::string_view SECURE       {"; Secure"};
    __cell_static_const_constexpr std::string_view HTTP_ONLY    {"; HttpOnly"};
    __cell_static_const_constexpr std::string_view SAME_SITE    {"; SameSite="};
};

/**
 * @brief Structure representing an HTTP response.
 *
 * This structure contains information about an HTTP response, including the status code, content,
 * and content type.
 */
struct ResponseStructure final
{
    int                     statusCode  {}; //!< The HTTP status code.
    Types::OptionalString   content     {}; //!< The response body content.
    Types::OptionalString   contentType {}; //!< The MIME type of the response body.
    Types::Headers          headers     {}; //!< The headers of the response.
};

/**
 * @brief Class representing an HTTP response.
 *
 * This class contains information about an HTTP response, including the status code, content,
 * and content type. It also provides accessor methods to retrieve this information.
 *
 * @note This class is marked with the "__cell_export" attribute, indicating
 *       it is part of the "cell" module for exporting purposes.
 */
class __cell_export Response {
public:
    /**
     * @brief Get the status code of the response.
     * @return The status code of the response.
     */
    int statusCode() const;

    /**
     * @brief Get the content type of the response.
     * @return The optional content type of the response.
     */
    Types::OptionalString contentType() const;

    /**
     * @brief Get the content of the response.
     * @return The optional content of the response.
     */
    Types::OptionalString content() const;

    /**
     * @brief Set the status code of the response.
     * @param status_code The status code to set.
     * @throws std::invalid_argument If the status code is not in the valid range (100-599).
     */
    void setStatusCode(int status_code);

    /**
     * @brief Set the content type of the response.
     * @param content_type The content type to set.
     * @throws std::invalid_argument If the content type is empty.
     */
    void setContentType(std::string_view contentType);

    /**
     * @brief Set the content of the response.
     * @param content The content to set.
     */
    void setContent(const std::string& content);

    /**
     * @brief Set a header in the response.
     * @param key The key of the header.
     * @param value The value of the header.
     */
    void setHeader(const std::string& key, const std::string& value);

    /**
     * @brief Remove a header from the response.
     * @param key The key of the header to remove.
     */
    void removeHeader(const std::string& key);

    /**
     * @brief Set a cookie in the response.
     * @param name The name of the cookie.
     * @param value The value of the cookie.
     * @param maxAge The maximum age of the cookie in seconds.
     * @param path The path for which the cookie is valid.
     * @param secure Whether the cookie should only be sent over HTTPS.
     * @param httpOnly Whether the cookie should be inaccessible to JavaScript.
     * @param sameSite The SameSite attribute of the cookie (e.g., "Strict", "Lax", "None").
     */
    void setCookie(const std::string& name, const std::string& value, int maxAge = -1, const std::string& path = "/",
                   bool secure = false, bool httpOnly = false, const std::string& sameSite = "");

    /**
     * @brief Set a session ID cookie in the response.
     * @param sessionId The session ID to set as a cookie value.
     * @param maxAge The maximum age of the cookie in seconds.
     * @param path The path for which the cookie is valid.
     * @param secure Whether the cookie should only be sent over HTTPS.
     * @param httpOnly Whether the cookie should be inaccessible to JavaScript.
     * @param sameSite The SameSite attribute of the cookie (e.g., "Strict", "Lax", "None").
     */
    void setSessionIdCookie(const std::string& sessionId, int maxAge = -1, const std::string& path = "/",
                            bool secure = false, bool httpOnly = false, const std::string& sameSite = "");

    /**
     * @brief Get the headers of the response.
     * @return The headers of the response as an unordered map.
     */
    const std::unordered_map<std::string, std::string>& headers() const;

private:
    ResponseStructure m_responseStructure;
};

CELL_NAMESPACE_END

#endif  // CELL_WEBSERVER_RESPONSE_HPP
