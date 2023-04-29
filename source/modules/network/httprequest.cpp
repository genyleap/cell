#ifdef __has_include
# if __has_include("httprequest.hpp")
#   include "httprequest.hpp"
#else
#   error "Cell's "httprequest.hpp" was not found!"
# endif
#endif

#ifdef __has_include
# if __has_include("core/core.hpp")
#   include "core/core.hpp"
#else
#   error "Cell's "core/core.hpp" was not found!"
# endif
#endif

#ifdef __has_include
# if __has_include("core/logger.hpp")
#   include "core/logger.hpp"
#else
#   error "Cell's "core/logger.hpp" was not found!"
# endif
#endif

CELL_USING_NAMESPACE Cell::System;
CELL_USING_NAMESPACE Cell::eLogger;
CELL_USING_NAMESPACE Cell::Types;

CELL_NAMESPACE_BEGIN(Cell::Modules::Network)


HttpRequest::HttpRequest(const std::string& url)
{
    curl_global_init(CURL_GLOBAL_ALL);
    requestStruct.curlHandlePtr.reset(curl_easy_init());
    if (!requestStruct.curlHandlePtr) {
        if(DeveloperMode::IsEnable)
        {
            Log("Failed to initialize curl handle!", LoggerType::Critical);
        }
        throw RuntimeError("Failed to initialize curl handle!");
    }
    requestStruct.url = url;
}

HttpRequest::~HttpRequest()
{
    LockGuard lock(requestStruct.curlHandleMutex);
    if (requestStruct.curlHandlePtr) {
        curl_easy_cleanup(requestStruct.curlHandlePtr.get());
        requestStruct.curlHandlePtr.release();
    }
    curl_global_cleanup();
}

void HttpRequest::setAuthUsernamePassword(const std::string& username, const std::string& password)
{
    LockGuard lock(requestStruct.curlHandleMutex);
    requestStruct.authUsername = username;
    requestStruct.authPassword = password;
    curl_easy_setopt(requestStruct.curlHandlePtr.get(), CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
    curl_easy_setopt(requestStruct.curlHandlePtr.get(), CURLOPT_USERPWD, (requestStruct.authUsername + ":" + requestStruct.authPassword).c_str());

}

void HttpRequest::addHeader(const std::string& header)
{
    requestStruct.headers.push_back(header);
}

void HttpRequest::setData(const std::string& data) {
    requestStruct.data = data;
}

void HttpRequest::setTimeout(long timeout)
{
    requestStruct.timeout = timeout;
}

std::string HttpRequest::performGet()
{
    return performRequest(CELL_GET);
}

std::string HttpRequest::performPost()
{
    return HttpRequest::performRequest(CELL_POST);
}

std::string HttpRequest::performPut()
{
    return HttpRequest::performRequest(CELL_PUT);
}

std::string HttpRequest::performDelete()
{
    return HttpRequest::performRequest(CELL_DELETE);
}

Mutex& HttpRequest::getMutex()
{
    static Mutex m;
    return m;
}

size_t HttpRequest::writeCallback(char* ptr, size_t size, size_t nmemb, void* userdata)
{
    std::string* response = reinterpret_cast<std::string*>(userdata);
    size_t num_bytes = size * nmemb;
    response->append(ptr, num_bytes);
    return num_bytes;
}

int HttpRequest::authCallback(char* buffer, size_t size, size_t nitems, void* userdata)
{
    const std::string& username = static_cast<RequestStruct*>(userdata)->authUsername;
    const std::string& password = static_cast<RequestStruct*>(userdata)->authPassword;

    size_t length = username.length() + password.length() + 1; // +1 for the colon separator
    if (length > size * nitems) {
        return 0;
    }

    std::copy(username.begin(), username.end(), buffer);
    *(buffer + username.length()) = ':';
    std::copy(password.begin(), password.end(), buffer + username.length() + 1);

    return static_cast<int>(length);
}

void HttpRequest::performRequestWithGuard(const FunctionCurl& func)
{
    LockGuard lock(requestStruct.curlHandleMutex);
    func(requestStruct.curlHandlePtr.get());
}

std::string HttpRequest::performRequest(const std::string& method)
{
    LockGuard lock(requestStruct.curlHandleMutex);

    // Set the method
    curl_easy_setopt(requestStruct.curlHandlePtr.get(), CURLOPT_CUSTOMREQUEST, method.c_str());

    // Set the URL
    curl_easy_setopt(requestStruct.curlHandlePtr.get(), CURLOPT_URL, requestStruct.url.c_str());

    // Set the headers
    struct curl_slist* headerList = nullptr;
    for (const auto& header : requestStruct.headers) {
        headerList = curl_slist_append(headerList, header.c_str());
    }
    curl_easy_setopt(requestStruct.curlHandlePtr.get(), CURLOPT_HTTPHEADER, headerList);

    // Set the data
    curl_easy_setopt(requestStruct.curlHandlePtr.get(), CURLOPT_POSTFIELDS, requestStruct.data.c_str());
    curl_easy_setopt(requestStruct.curlHandlePtr.get(), CURLOPT_POSTFIELDSIZE, requestStruct.data.size());

    // Set the timeout
    curl_easy_setopt(requestStruct.curlHandlePtr.get(), CURLOPT_TIMEOUT, requestStruct.timeout);

    // Set the authentication callback
    if (!requestStruct.authUsername.empty() && !requestStruct.authPassword.empty()) {
        curl_easy_setopt(requestStruct.curlHandlePtr.get(), CURLOPT_USERPWD, (requestStruct.authUsername + ":" + requestStruct.authPassword).c_str());
        curl_easy_setopt(requestStruct.curlHandlePtr.get(), CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_easy_setopt(requestStruct.curlHandlePtr.get(), CURLOPT_XFERINFOFUNCTION, &HttpRequest::authCallback);
        curl_easy_setopt(requestStruct.curlHandlePtr.get(), CURLOPT_XFERINFODATA, &requestStruct);
    }

    // Set the write callback
    curl_easy_setopt(requestStruct.curlHandlePtr.get(), CURLOPT_WRITEFUNCTION, &HttpRequest::writeCallback);
    curl_easy_setopt(requestStruct.curlHandlePtr.get(), CURLOPT_WRITEDATA, &requestStruct.response);

    // Perform the request
    CURLcode resultCode = curl_easy_perform(requestStruct.curlHandlePtr.get());

    // Clean up the headers list
    curl_slist_free_all(headerList);

    // Check for errors
    if (resultCode != CURLE_OK) {
        if(DeveloperMode::IsEnable)
        {
            Log("Failed to perform " + method + " request: " + curl_easy_strerror(resultCode), LoggerType::Critical);
        }
        throw RuntimeError("Failed to perform " + method + " request: " + curl_easy_strerror(resultCode));
    }

    // Check the response code
    long responseCode = 0;
    curl_easy_getinfo(requestStruct.curlHandlePtr.get(), CURLINFO_RESPONSE_CODE, &responseCode);
    if (responseCode == 401) {
        if(DeveloperMode::IsEnable)
        {
            Log("Authentication failed!", LoggerType::Critical);
        }
        throw RuntimeError("Authentication failed");
    }

    // Return the response
    return requestStruct.response;
}

CELL_NAMESPACE_END
