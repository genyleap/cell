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

void HttpRequest::setContentType(Headers c){

    switch (c) {
    case Headers::X_Urlencoded:
        headerType = ContentTypeHeader::APPLICATION_X_WWW_FROM_URLENCODED;
        break;
    case Headers::JSon:
        headerType = ContentTypeHeader::APPLICATION_JSON;
        break;
    case Headers::XHtml:
        headerType = ContentTypeHeader::APPLICATION_XHTML;
        break;
    case Headers::Xml:
        headerType = ContentTypeHeader::APPLICATION_XML;
        break;
    case Headers::Html:
        headerType = ContentTypeHeader::TEXT_HTML;
        break;
    case Headers::MultiPart:
        headerType = ContentTypeHeader::MULTIPART_FROM_DATA;
        break;
    }

}

HttpRequest::HttpRequest()
{
}

HttpRequest::HttpRequest(const std::string& url)
{
    /**
     * RAII (Resource Acquisition Is Initialization) technique to acquire a new resource and automatically manage it using the std::unique_ptr smart pointer.
     * The std::unique_ptr class automatically destroys the previously owned object, if any, and takes ownership of the newly created System::Engine object when the new object is acquired.
     * When the std::unique_ptr object goes out of scope, it automatically destroys the owned object. This way, the resource is automatically managed without the need for explicit memory allocation and deallocation or the use of explicit destructors.
     */

    std::unique_ptr<System::Engine> engineSmartPtr = createEngineObject();
    if(engineSmartPtr->initialize())
    {
        //ToDo..!
    }

    // Initialize cURL
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
    curl_easy_setopt(requestStruct.curlHandlePtr.get(), CURLOPT_USERPWD, (requestStruct.authUsername.value() + ":" + requestStruct.authPassword.value()).c_str());

}

void HttpRequest::addHeader(const std::string& header)
{
    requestStruct.headers.push_back(header);
}

void HttpRequest::setData(const std::string& data)
{
    requestStruct.data = data;
}

void HttpRequest::setQuery(const HttpQueryString& params)
{
    std::unique_ptr<System::Engine> engineSmartPtr = createEngineObject();
    std::string queryStr;
    bool firstParam = true;
    for (const auto& [param, value] : requestStruct.queries = std::move(params))
    {
        if (firstParam) {
            queryStr += "?";
            firstParam = false;
        }
        else {
            queryStr += "&";
        }
        queryStr += engineSmartPtr->urlEncode(param) + "=" + engineSmartPtr->urlEncode(value);
    }
    if(!requestStruct.url.has_value())
    {
        requestStruct.url.value() += queryStr;
    }
}

void HttpRequest::setTimeout(long timeout)
{
    requestStruct.timeout = timeout;
}

std::string HttpRequest::performGet()
{
    std::unique_ptr<System::Engine> engineSmartPtr = createEngineObject();

    // Enforce a rate limit on the HTTP requests being made.
    (isEnableRateLimit()) ? engineSmartPtr->delayIfNeeded(requestStruct.lastRequestTime, rateLimit()) : DO_NOTHING;

    return performRequest(CELL_GET);
}

FutureStringObject HttpRequest::performGetAsync()
{
    std::unique_ptr<System::Engine> engineSmartPtr = createEngineObject();

    // Enforce a rate limit on the HTTP requests being made.
    (isEnableRateLimit()) ? engineSmartPtr->delayIfNeeded(requestStruct.lastRequestTime, rateLimit()) : DO_NOTHING;

    PromiseStringObject promise;
    FutureStringObject future = promise.get_future();
    std::thread t(&HttpRequest::performAsyncThread, this, std::move(promise), CELL_GET);
    t.detach();
    return future;
}

std::string HttpRequest::performPost()
{
    std::unique_ptr<System::Engine> engineSmartPtr = createEngineObject();

    // Enforce a rate limit on the HTTP requests being made.
    (isEnableRateLimit()) ? engineSmartPtr->delayIfNeeded(requestStruct.lastRequestTime, rateLimit()) : DO_NOTHING;

    return HttpRequest::performRequest(CELL_POST);
}

FutureStringObject HttpRequest::performPostAsync()
{
    std::unique_ptr<System::Engine> engineSmartPtr = createEngineObject();

    // Enforce a rate limit on the HTTP requests being made.
    (isEnableRateLimit()) ? engineSmartPtr->delayIfNeeded(requestStruct.lastRequestTime, rateLimit()) : DO_NOTHING;

    PromiseStringObject promise;
    FutureStringObject future = promise.get_future();
    std::thread t(&HttpRequest::performAsyncThread, this, std::move(promise), CELL_POST);
    t.detach();
    return future;
}

std::string HttpRequest::performPut()
{
    std::unique_ptr<System::Engine> engineSmartPtr = createEngineObject();

    // Enforce a rate limit on the HTTP requests being made.
    (isEnableRateLimit()) ? engineSmartPtr->delayIfNeeded(requestStruct.lastRequestTime, rateLimit()) : DO_NOTHING;

    return HttpRequest::performRequest(CELL_PUT);
}

FutureStringObject HttpRequest::performPutAsync()
{
    std::unique_ptr<System::Engine> engineSmartPtr = createEngineObject();

    // Enforce a rate limit on the HTTP requests being made.
    (isEnableRateLimit()) ? engineSmartPtr->delayIfNeeded(requestStruct.lastRequestTime, rateLimit()) : DO_NOTHING;

    PromiseStringObject promise;
    FutureStringObject future = promise.get_future();
    std::thread t(&HttpRequest::performAsyncThread, this, std::move(promise), CELL_PUT);
    t.detach();
    return future;
}

std::string HttpRequest::performDelete()
{
    return HttpRequest::performRequest(CELL_DELETE);
}

FutureStringObject HttpRequest::performDeleteAsync()
{
    std::unique_ptr<System::Engine> engineSmartPtr = createEngineObject();

    // Enforce a rate limit on the HTTP requests being made.
    (isEnableRateLimit()) ? engineSmartPtr->delayIfNeeded(requestStruct.lastRequestTime, rateLimit()) : DO_NOTHING;

    PromiseStringObject promise;
    FutureStringObject future = promise.get_future();
    std::thread t(&HttpRequest::performAsyncThread, this, std::move(promise), CELL_DELETE);
    t.detach();
    return future;
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
    const std::string& username = static_cast<RequestStruct*>(userdata)->authUsername.value();
    const std::string& password = static_cast<RequestStruct*>(userdata)->authPassword.value();

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
    std::unique_ptr<System::Engine> engineSmartPtr = createEngineObject();

    LockGuard lock(requestStruct.curlHandleMutex);

    // Set the method
    curl_easy_setopt(requestStruct.curlHandlePtr.get(), CURLOPT_CUSTOMREQUEST, method.c_str());

    // Set the URL
    curl_easy_setopt(requestStruct.curlHandlePtr.get(), CURLOPT_URL, requestStruct.url.value().c_str());


    // Set the headers
    struct curl_slist* headerList = nullptr;
    for (const auto& header : requestStruct.headers) {
        headerList = curl_slist_append(headerList, header.c_str());
    }

    curl_easy_setopt(requestStruct.curlHandlePtr.get(), CURLOPT_HTTPHEADER, headerList);

    // Set the data
    curl_easy_setopt(requestStruct.curlHandlePtr.get(), CURLOPT_POSTFIELDS, requestStruct.data->c_str());
    curl_easy_setopt(requestStruct.curlHandlePtr.get(), CURLOPT_POSTFIELDSIZE, requestStruct.data->size());

    // Set the timeout
    curl_easy_setopt(requestStruct.curlHandlePtr.get(), CURLOPT_TIMEOUT, requestStruct.timeout);

    // Set the authentication callback
    if (!requestStruct.authUsername.value().empty() && !requestStruct.authPassword.value().empty()) {
        curl_easy_setopt(requestStruct.curlHandlePtr.get(), CURLOPT_USERPWD, (requestStruct.authUsername.value() + ":" + requestStruct.authPassword.value()).c_str());
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
    long responseCode = __cell_zero;
    curl_easy_getinfo(requestStruct.curlHandlePtr.get(), CURLINFO_RESPONSE_CODE, &responseCode);

    switch (responseCode) {
    case ReturnCode::Ret400:
        if(DeveloperMode::IsEnable)
        {
            Log("Bad request!", LoggerType::Critical);
        }
        throw RuntimeError(CodeMessage::Ret400.data());
        break;
    case ReturnCode::Ret401:
        if(DeveloperMode::IsEnable)
        {
            Log("Authentication failed!", LoggerType::Critical);
        }
        throw RuntimeError(CodeMessage::Ret400.data());
        break;
    case ReturnCode::Ret408:
        if(DeveloperMode::IsEnable)
        {
            Log("Timeout failed!", LoggerType::Critical);
        }
        throw RuntimeError(CodeMessage::Ret400.data());
        break;
    case ReturnCode::Ret200:
        if(DeveloperMode::IsEnable)
        {
            Log("The request was received, understood, and accepted!", LoggerType::Info);
        }
        break;
    default:
        break;
    }
    if (responseCode == ReturnCode::Ret401)
    {
        if(DeveloperMode::IsEnable)
        {
            Log("Authentication failed!", LoggerType::Critical);
        }
        throw RuntimeError("Authentication failed");
    }
    if (responseCode == ReturnCode::Ret200)
    {
        if(DeveloperMode::IsEnable)
        {
            Log("Success!", LoggerType::Success);
        }
    }

    // Return the response
    return requestStruct.response.value();
}

void HttpRequest::performAsyncThread(PromiseStringObject&& promise, const std::string& method)
{
    // Wrap the promise in a try-catch block to handle any exceptions that may occur during execution.
    try {
        // Perform the HTTP request using the method.
        std::string result = performRequest(method);
        // The result is moved into the promise object using set_value() function.
        promise.set_value(std::move(result));
    } catch (const std::exception& e) {
        if(DeveloperMode::IsEnable)
        {
            Log(std::string("HttpRequest::performAsyncThread failed: ") + e.what(), LoggerType::Critical);
        }
        // Set the exception on the promise if an exception occurs
        promise.set_exception(std::make_exception_ptr(std::runtime_error(std::string("HttpRequest::performAsyncThread failed: ") + e.what())));
    } catch (...) {
        // If an exception occurs, the exception object is moved into the promise object using set_exception() function  .
        promise.set_exception(std::current_exception());
    }
}

/**
 * @details This code helps to ensure that requests are not made too frequently,
 * which can help avoid hitting rate limits or overwhelming a server with too many requests.
 */
void HttpRequest::setRateLimit(const unsigned int requestsPerSecond)
{
    HttpRequest::m_rateLimit  = requestsPerSecond;
}

unsigned int HttpRequest::m_rateLimit = __cell_zero;

unsigned int HttpRequest::rateLimit()
{
    return m_rateLimit;
}

bool HttpRequest::isEnableRateLimit()
{
    if(m_rateLimit > __cell_zero)
    {
        return true;
    }
    return true;
}


CELL_NAMESPACE_END
