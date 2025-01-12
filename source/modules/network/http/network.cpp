#include "network.hpp"
#include "utilities/types.hpp"

CELL_USING_NAMESPACE Cell::Utility;
CELL_USING_NAMESPACE Cell::Types;

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Network)

size_t Network::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* outBuffer) {
    size_t totalSize = size * nmemb;
    outBuffer->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

Network::Network(int threadPoolSize)
    : requestTokens(0), rateLimitInterval(1000), stopThreadPool(false), maxRetries(0), retryDelay(1000), verifySSL(true) {
    for (int i = 0; i < threadPoolSize; ++i) {
        threadPool.emplace_back(&Network::processTaskQueue, this);
    }
}

Network::~Network() {
    stopThreadPool = true;
    queueCV.notify_all();
    for (auto& thread : threadPool) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

void Network::processTaskQueue() {
    while (!stopThreadPool) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            queueCV.wait(lock, [this]() { return !taskQueue.empty() || stopThreadPool; });
            if (stopThreadPool && taskQueue.empty()) {
                return;
            }
            task = std::move(taskQueue.front());
            taskQueue.pop();
        }
        task();
    }
}

void Network::waitForRateLimit() {
    std::unique_lock<std::mutex> lock(rateLimitMutex);
    if (requestTokens <= 0) {
        rateLimitCV.wait(lock, [this]() { return requestTokens > 0; });
    }
    requestTokens--;
}

bool Network::sendRequestInternal(const std::string& url, const std::string& data, const Headers& headers, HttpMethod method, std::string& response, bool verbose, long timeout) {

    Logger::formatted(LoggerType::Info, "Sending request to: {}", url);

    CURL* curl = curl_easy_init();
    if (!curl) {
        Logger::formatted(LoggerType::Failed, "Failed to initialize CURL!");
        return false;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    if (verbose) curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    if (timeout > 0) curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout);

    if (!proxyUrl.empty()) {
        curl_easy_setopt(curl, CURLOPT_PROXY, proxyUrl.c_str());
    }

    if (!caCertPath.empty()) {
        curl_easy_setopt(curl, CURLOPT_CAINFO, caCertPath.c_str());
    }
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, verifySSL ? 1L : 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, verifySSL ? 2L : 0L);

    struct curl_slist* curlHeaders = nullptr;
    for (const auto& [key, value] : headers) {
        curlHeaders = curl_slist_append(curlHeaders, (key + ": " + value).c_str());
    }
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curlHeaders);

    switch (method) {
    case HttpMethod::POST:
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        break;
    case HttpMethod::PUT:
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        break;
    case HttpMethod::DELETE:
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
        break;
    case HttpMethod::PATCH:
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PATCH");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        break;
    case HttpMethod::GET:
    default:
        break;
    }

    auto start = std::chrono::steady_clock::now();
    CURLcode res = curl_easy_perform(curl);
    auto end = std::chrono::steady_clock::now();
    auto responseTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    curl_slist_free_all(curlHeaders);
    curl_easy_cleanup(curl);

    RequestMetrics metrics;
    metrics.responseTime = responseTime;
    metrics.success = (res == CURLE_OK);
    metrics.errorMessage = (res != CURLE_OK) ? curl_easy_strerror(res) : "";

    {
        std::unique_lock<std::shared_mutex> lock(networkMutex);
        requestMetrics[url] = metrics;
    }

    if (res != CURLE_OK) {
        Logger::formatted(LoggerType::Failed, "CURL error: {}", curl_easy_strerror(res));
        return false;
    }
    Logger::formatted(LoggerType::Success, "Request to {} completed successfully in {} ms.", url, responseTime.count());
    return true;
}

bool Network::sendRequest(const std::string& url, std::string& response, bool verbose, long timeout) {
    Headers headers;
    return sendRequestInternal(url, "", headers, HttpMethod::GET, response, verbose, timeout);
}

bool Network::sendRequest(const std::string& url, const std::string& data, const Headers& headers, HttpMethod method, std::string& response, bool verbose, long timeout) {
    return sendRequestInternal(url, data, headers, method, response, verbose, timeout);
}

void Network::retryRequest(const std::string& url, const std::string& data, const Headers& headers, HttpMethod method, ResponseCallback callback, bool verbose, long timeout, int retryCount) {
    std::string response;
    bool success = sendRequestInternal(url, data, headers, method, response, verbose, timeout);

    if (!success && retryCount < maxRetries) {
        Logger::formatted(LoggerType::InProgress, "Retry attempt {} for {}", retryCount + 1, url);
        std::this_thread::sleep_for(retryDelay);
        retryRequest(url, data, headers, method, callback, verbose, timeout, retryCount + 1);
    } else {
        callback(response, success);
    }
}

void Network::sendRequestAsync(const std::string& url, const std::string& data, const Headers& headers, HttpMethod method, ResponseCallback callback, bool verbose, long timeout) {
        Logger::formatted(LoggerType::InProgress, "Queueing async request to: {}", url);
    auto task = [this, url, data, headers, method, callback, verbose, timeout]() {
        Logger::formatted(LoggerType::InProgress, "Processing async request to: {}", url);
        retryRequest(url, data, headers, method, callback, verbose, timeout, 0);
    };

    {
        std::unique_lock<std::mutex> lock(queueMutex);
        taskQueue.push(task);
    }
    queueCV.notify_one();
}

void Network::setRateLimit(int maxRequests, std::chrono::milliseconds interval) {
    std::unique_lock<std::mutex> lock(rateLimitMutex);
    requestTokens = maxRequests;
    rateLimitInterval = interval;

    std::thread([this, maxRequests]() {
        while (true) {
            std::this_thread::sleep_for(rateLimitInterval);
            std::unique_lock<std::mutex> lock(rateLimitMutex);
            requestTokens = maxRequests;
            rateLimitCV.notify_all();
        }
    }).detach();
}

void Network::setRetryPolicy(int maxRetries, std::chrono::milliseconds retryDelay) {
    this->maxRetries = maxRetries;
    this->retryDelay = retryDelay;
}

void Network::setProxy(const std::string& proxyUrl) {
    this->proxyUrl = proxyUrl;
}

void Network::setSSLCertificate(const std::string& caCertPath, bool verifySSL) {
    this->caCertPath = caCertPath;
    this->verifySSL = verifySSL;
}

void Network::cancelAllRequests() {
    std::unique_lock<std::mutex> lock(queueMutex);
    taskQueue = std::queue<std::function<void()>>();
}

std::string urlEncode(const std::string& value) {
    std::ostringstream escaped;
    escaped.fill('0');
    escaped << std::hex;

    for (char c : value) {
        // Keep alphanumeric and other accepted characters as-is
        if (std::isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
        } else {
            // Encode special characters
            escaped << '%' << std::setw(2) << int(static_cast<unsigned char>(c));
        }
    }

    return escaped.str();
}

std::string Network::buildQueryString(const std::map<std::string, std::string>& params) const {
    std::string queryString;

    for (const auto& [key, value] : params) {
        if (!queryString.empty()) {
            queryString += "&"; // Add '&' between key-value pairs
        }

        // URL-encode the key and value
        queryString += urlEncode(key) + "=" + urlEncode(value);
    }

    return queryString;
}

Network::RequestMetrics Network::getRequestMetrics(const std::string& url) const {
    std::shared_lock<std::shared_mutex> lock(networkMutex);
    auto it = requestMetrics.find(url);
    if (it != requestMetrics.end()) {
        return it->second;
    }
    return RequestMetrics{};
}

CELL_NAMESPACE_END
