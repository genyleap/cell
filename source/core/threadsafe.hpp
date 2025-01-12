/*!
 * @file        threadsafe.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     System core.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2025 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_THREADSAFE_HPP
#define CELL_THREADSAFE_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell)

/**
 * @class ThreadSafe
 * @brief A template class for thread-safe access to a shared resource.
 *
 * The `ThreadSafe` class simplifies thread-safe access to a resource by encapsulating
 * shared and exclusive locks. It provides methods to perform read (shared) and write (exclusive)
 * operations on the underlying data in a thread-safe manner.
 *
 * @tparam T The type of the resource to be protected.
 */
template <typename T>
class ThreadSafe {
public:
    /**
     * @brief Constructor to initialize the underlying resource.
     *
     * @param initialData The initial value of the resource. Defaults to the default-constructed value of T.
     */
    explicit ThreadSafe(T initialData = T{}) : data(std::move(initialData)) {}

    /**
     * @brief Access the resource with an exclusive (write) lock.
     *
     * This method ensures that only one thread can access the resource at a time
     * while holding the exclusive lock. The provided callable is executed with
     * write access to the resource.
     *
     * @tparam Callable A callable object (e.g., lambda, function, or functor) that operates on the resource.
     * @param func The callable to execute.
     * @return The result of the callable's execution.
     */
    template <typename Callable>
    auto write(Callable&& func) -> decltype(func(std::declval<T&>())) {
        std::unique_lock lock(mutex);
        return func(data);
    }

    /**
     * @brief Access the resource with a shared (read) lock.
     *
     * This method allows multiple threads to concurrently access the resource
     * for reading, ensuring thread-safety. The provided callable is executed
     * with read-only access to the resource.
     *
     * @tparam Callable A callable object (e.g., lambda, function, or functor) that operates on the resource.
     * @param func The callable to execute.
     * @return The result of the callable's execution.
     */
    template <typename Callable>
    auto read(Callable&& func) const -> decltype(func(std::declval<const T&>())) {
        std::shared_lock lock(mutex);
        return func(data);
    }

private:
    mutable std::shared_mutex mutex; ///< Mutex for managing shared and exclusive locks.
    T data; ///< The protected resource.
};


CELL_NAMESPACE_END

#endif // CELL_THREADSAFE_HPP
