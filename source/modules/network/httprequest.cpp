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
    return performRequest(CELL_GET);
}

FutureStringObject HttpRequest::performGetAsync()
{
    PromiseStringObject promise;
    FutureStringObject future = promise.get_future();
    std::thread t(&HttpRequest::performAsyncThread, this, std::move(promise), CELL_GET);
    t.detach();
    return future;
}

std::string HttpRequest::performPost()
{
    return HttpRequest::performRequest(CELL_POST);
}

FutureStringObject HttpRequest::performPostAsync()
{
    PromiseStringObject promise;
    FutureStringObject future = promise.get_future();
    std::thread t(&HttpRequest::performAsyncThread, this, std::move(promise), CELL_POST);
    t.detach();
    return future;
}

std::string HttpRequest::performPut()
{
    return HttpRequest::performRequest(CELL_PUT);
}

FutureStringObject HttpRequest::performPutAsync()
{
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
    } catch (const std::exception& ex) {
        if(DeveloperMode::IsEnable)
        {
            Log(std::string("HttpRequest::performAsyncThread failed: ") + ex.what(), LoggerType::Critical);
        }
        // Set the exception on the promise if an exception occurs
        promise.set_exception(std::make_exception_ptr(std::runtime_error(std::string("HttpRequest::performAsyncThread failed: ") + ex.what())));
    } catch (...) {
        // If an exception occurs, the exception object is moved into the promise object using set_exception() function  .
        promise.set_exception(std::current_exception());
    }
}

// Definition of the createMyClassObject function
std::unique_ptr<System::Engine> createEngineObject()
{
    // Allocate memory for a MyClass object using 'new'
    Engine* myClassPtr = new Engine;

    // Wrap the raw pointer in a unique_ptr and return it
    return std::unique_ptr<Engine>(myClassPtr);
}


CELL_NAMESPACE_END
