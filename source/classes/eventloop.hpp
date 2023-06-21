/*!
 * @file        eventloop.hpp
 * @brief       Event loop manager for the Cell Engine.
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

#ifndef CELL_EVENT_LOOP_HPP
#define CELL_EVENT_LOOP_HPP

//! Cell's Core (Basic Requirements).
#if __has_include(<requirements>)
#   include <requirements>
#else
#   error "Cell's requirements was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell)

/**
 * @brief Enumeration defining different types of event loops.
 */
enum class EventLoopType
{
    SELECT, //!< Uses the select() system call for event loop.
    POLL,   //!< Uses the poll() system call for event loop.
    EPOLL,  //!< Uses the epoll() system call for event loop.
    KQUEUE  //!< Uses the kqueue() system call for event loop.
};

/**
 * @class EventLoop
 * @brief A class representing an event loop.
 */
class __cell_export EventLoop {
public:
    using Task = std::function<void()>;

    /**
     * @brief Constructs an EventLoop object with the specified loop type.
     * @param loopType The type of event loop to use.
     */
    explicit EventLoop(EventLoopType loopType);

    /**
     * @brief Starts the event loop.
     */
    void start();

    /**
     * @brief Stops the event loop.
     */
    void stop();

    /**
     * @brief Adds a task to the event loop's task queue.
     * @param task The task to be added.
     */
    void addTask(Task task);

    /**
     * @brief Retrieves the running status of the event loop.
     * @return True if the event loop is running, false otherwise.
     */
    bool getIsRunning() const;

private:
    bool isRunning;                             //!< Flag indicating if the event loop is running.
    std::thread workerThread;                   //!< The worker thread that executes the event loop.
    std::queue<Task> taskQueue;                 //!< Queue of tasks to be processed by the event loop.
    std::mutex mutex;                           //!< Mutex for synchronizing access to the task queue.
    std::condition_variable conditionVariable;  //!< Condition variable for task synchronization.
    EventLoopType loopType;                     //!< The type of event loop being used.

    /**
     * @brief Runs the event loop.
     */
    void run();

#if defined(CELL_PLATFORM_MAC) || defined(CELL_PLATFORM_IOS)
    /**
     * @brief Performs the event loop using kqueue (macOS, BSD).
     */
    void runKqueue();
#endif

#ifdef CELL_PLATFORM_LINUX
    /**
     * @brief Performs the event loop using epoll (Linux).
     */
    void runEpoll();
#endif

#ifdef CELL_PLATFORM_WINDOWS
    /**
     * @brief Performs the event loop using I/O Completion Ports (Windows).
     */
    void runIOCP();
#endif
};


CELL_NAMESPACE_END

#endif  // CELL_EVENT_LOOP_HPP

