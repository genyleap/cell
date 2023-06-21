#if __has_include("eventloop.hpp")
#   include "eventloop.hpp"
#else
#   error "Cell's eventloop was not found!"
#endif

CELL_USING_NAMESPACE Cell::Types;
CELL_USING_NAMESPACE Cell::Utility;

CELL_NAMESPACE_BEGIN(Cell)

EventLoop::EventLoop(EventLoopType loopType) : isRunning(false), loopType(loopType)
{
}

void EventLoop::start()
{
    // Set the isRunning flag to true
    isRunning = true;

    // Start the worker thread by invoking the run() function
    workerThread = std::thread(&EventLoop::run, this);
}

void EventLoop::stop()
{
    {
        std::lock_guard<std::mutex> lock(mutex);

        // Set the isRunning flag to false to stop the event loop
        isRunning = false;
    }

    // Notify the worker thread that it should wake up and check the condition
    conditionVariable.notify_one();

    // Wait for the worker thread to finish its execution
    workerThread.join();
}

void EventLoop::addTask(Task task)
{
    {
        std::lock_guard<std::mutex> lock(mutex);

        // Add the task to the task queue
        taskQueue.push(std::move(task));
    }

    // Notify the worker thread that a new task is available
    conditionVariable.notify_one();
}

bool EventLoop::getIsRunning() const
{
    // Return the current value of the isRunning flag
    return isRunning;
}

void EventLoop::run()
{
    while (true) {
        Task task;
        {
            std::unique_lock<std::mutex> lock(mutex);
            // Wait until the task queue is not empty or the event loop is no longer running
            conditionVariable.wait(lock, [this]() { return !taskQueue.empty() || !isRunning; });

            // Check if the event loop is no longer running and the task queue is empty
            if (!isRunning && taskQueue.empty())
                return;

            // Retrieve the task from the front of the task queue
            task = std::move(taskQueue.front());
            taskQueue.pop();
        }

        // Execute the retrieved task
        task();
    }
}
#if defined(CELL_PLATFORM_MAC) || defined(CELL_PLATFORM_IOS)
// Perform event loop using kqueue (macOS, BSD)
void EventLoop::runKqueue() {
    int kq = kqueue();
    if (kq == -1) {
        Log("Failed to create kqueue", LoggerType::Critical);
        return;
    }
    while (isRunning) {
        struct kevent events[32];
        struct timespec timeout;
        timeout.tv_sec = 0;
        timeout.tv_nsec = 100000000; // 100ms
        int eventCount = kevent(kq, nullptr, 0, events, 32, &timeout);
        if (eventCount == -1) {
            Log("Failed to retrieve events from kqueue", LoggerType::Critical);
            break;
        }
        for (int i = 0; i < eventCount; ++i) {
            struct kevent& event = events[i];
            if (event.filter == EVFILT_READ) {
                // Handle read event
                int fd = event.ident; // File descriptor associated with the event
                // Process read operation on the file descriptor
                // ...
            } else if (event.filter == EVFILT_WRITE) {
                // Handle write event
                int fd = event.ident; // File descriptor associated with the event
                // Process write operation on the file descriptor
                // ...
            } else {
                // Handle other types of events if necessary
            }
        }
    }
    close(kq);
}

#endif
#ifdef CELL_PLATFORM_LINUX
// Perform event loop using epoll (Linux)
void EventLoop::runEpoll() {
    int epollFd = epoll_create1(0);
    if (epollFd == -1) {
        // Handle error when creating epoll file descriptor
        Log("Failed to create epoll file descriptor. Error: " + FROM_CELL_STRING(strerror(errno)), LoggerType::Critical);
        return;
    }
    while (isRunning) {
        struct epoll_event events[32];
        int eventCount = epoll_wait(epollFd, events, 32, 100); // 100ms timeout

        if (eventCount == -1) {
            // Handle error when waiting for events
            Log("Failed to wait for events using epoll. Error: " + FROM_CELL_STRING(strerror(errno)), LoggerType::Critical);
            break;
        }
        for (int i = 0; i < eventCount; ++i) {
            // Handle events
            struct epoll_event& event = events[i];
            int fd = event.data.fd;
            // Perform event handling for the file descriptor
            // ...
        }
    }
    close(epollFd);
}
#endif
#ifdef CELL_PLATFORM_WINDOWS
// Perform event loop using I/O Completion Ports (Windows)
void EventLoop::runIOCP() {
    HANDLE completionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
    if (completionPort == NULL) {
        // Handle error when creating I/O completion port
        Log("Failed to create I/O completion port. Error: " + FROM_CELL_STRING(GetLastError()), LoggerType::Critical);
        return;
    }

    while (isRunning) {
        DWORD bytesTransferred = 0;
        ULONG_PTR completionKey = 0;
        LPOVERLAPPED overlapped = nullptr;
        BOOL result = GetQueuedCompletionStatus(completionPort, &bytesTransferred, &completionKey, &overlapped, 100); // 100ms timeout

        if (result != FALSE) {
            // Handle I/O completion
            // ...
        }
        else {
            DWORD errorCode = GetLastError();
            if (errorCode != WAIT_TIMEOUT) {
                // Handle error when getting queued completion status
                Log(Failed to get queued completion status. Error: " + FROM_CELL_STRING(errorCode), LoggerType::Critical);
                break;
            }
        }
    }

    CloseHandle(completionPort);
}
#endif

CELL_NAMESPACE_END
