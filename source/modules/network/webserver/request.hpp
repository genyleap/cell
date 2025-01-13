#ifndef CELL_WEBSERVER_REQUEST_HPP
#define CELL_WEBSERVER_REQUEST_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

#if __has_include("classes/cookies.hpp")
#   include "classes/cookies.hpp"
#else
#   error "Cell's "classes/cookies.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Network::WebServer)

/**
 * @brief Structure that represents the parts of a HTTP request
 */
struct RequestStructure final
{
    Types::Headers              headers       {}; //!< The headers of the request.
    Types::OptionalString       method        {}; //!< The HTTP method of the request.
    Types::OptionalString       uri           {}; //!< The URI of the request.
    Types::OptionalString       httpVersion   {}; //!< The HTTP version of the request.
    Types::OptionalString       body          {}; //!< The body of the request.
    Globals::Storage::Cookies   cookies       {}; //!< The cookies received in the request.
    std::unordered_map<std::string, std::string> pathParameters {}; //!< Dynamic path parameters (e.g., `/user/{id}`).
};

/**
 * @class Request
 * @brief Class representing an HTTP request.
 *
 * @note This class is marked with the "__cell_export" attribute, indicating
 *       it is part of the "cell" module for exporting purposes.
 */
class __cell_export Request {
public:
    /**
     * @brief Get the HTTP method of the request.
     * @return The optional HTTP method of the request.
     */
    Types::OptionalString method() const;

    /**
     * @brief Get the path of the request.
     * @return The optional path of the request.
     */
    Types::OptionalString path() const;

    /**
     * @brief Returns the HTTP version of the request
     *
     * @return The HTTP version of the request
     */
    const Types::OptionalString& httpVersion() const;

    /**
     * @brief Get the body of the request.
     * @return The optional body of the request.
     */
    Types::OptionalString body() const;

    /**
     * @brief Returns the headers of the request
     *
     * @return The headers of the request as an unordered map with string keys and values
     */
    const std::unordered_map<std::string, std::string> headers()  const;

    /**
     * @brief Set the HTTP method of the request.
     * @param method The HTTP method to set.
     */
    void setMethod(const std::string& method);

    /**
     * @brief Set the path of the request.
     * @param path The path to set.
     */
    void setPath(const std::string& path);

    /**
     * @brief Set a header in the request.
     * @param key The key of the header.
     * @param value The value of the header.
     */
    void setHeader(const std::string& key, const std::string& value);

    /**
     * @brief Set the body of the request.
     * @param body The body to set.
     */
    void setBody(const std::string& body);

    /**
     * @brief Set the session ID of the request.
     * @param sessionId The session ID to set.
     */
    void setSessionId(const std::string& sessionId);

    /**
     * @brief Get the cookies received in the request.
     * @return The cookies received in the request.
     */
    const Cell::Globals::Storage::Cookies& cookies() const;

    /**
     * @brief Get the uploaded files in the request.
     * @return The uploaded files as an unordered map.
     */
    std::unordered_map<std::string, std::string> getUploadedFiles() const;

    /**
     * @brief Set path parameters for the request.
     * @param params The path parameters to set.
     */
    void setPathParameters(const std::unordered_map<std::string, std::string>& params);

    /**
     * @brief Get the path parameters of the request.
     * @return The path parameters as an unordered map.
     */
    const std::unordered_map<std::string, std::string>& pathParameters() const;

private:
    RequestStructure m_requestStructure {};
    std::unordered_map<std::string, std::string> m_uploadedFiles;
};

CELL_NAMESPACE_END

#endif  // CELL_WEBSERVER_REQUEST_HPP
