/*!
 * @file        cache.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Cache interface for system.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_CACHE_ABSTRACT_HPP
#define CELL_CACHE_ABSTRACT_HPP

#include "common.hpp"

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

struct CacheMembers __cell_final
{
    Types::OptionalString  storage   {}; ///< String path to the "eternal" storage files. About what "eternal cache" is, read below.
};

/*!
 * Caching class constructor.
 * \brief The AbstractCache class
 * @param string|null uniq prefix for external cache machine names.
 * @param string|null path path to store files for the internal cache machine (when there are no external ones).
 * @param string|null storage perpetual cache storage path. The eternal is distinguished by the fact that it is easy to rule and it
 * is not deleted along with the main one. As a rule, the generated data is stored in the eternal cache key => value when inaccessible generator.
 */
class __cell_export AbstractCache
{
public:
    CELL_DEFAULT_INTERFACE_OCTORS(AbstractCache)

    /*!
     * \brief Write data to cache.
     * \param string key Key (name of cache storage location).
     * \param mixed value stored data.
     * \param int ttl storage time in seconds.
     * \param bool eternal write as "eternal" cache.
     * \param int|null insur Cache hopelessly expired. Used to prevent the dog-pile effect. Default is twice ttl.
     * \returns boolean.
     */
    __cell_virtual Types::OptionalBool put(const std::string& key, const bool value, const Types::u32 ttl, const bool eternal, const int insur) = __cell_zero;

    /*!
     * \brief Get data from the cache.
     * \param string key cache storage location name.
     * \param bool eternal eternal cache flag.
     * \returns string.
     */
    __cell_virtual Types::OptionalString get(const std::string& key, const bool eternal) = __cell_zero;

    /*!
     * \brief Get data from the cache.
     * \param string key cache storage location name.
     * \param bool eternal flag to remove the cache from the "eternal" storage table.
     * \returns boolean.
     */
    __cell_virtual Types::OptionalBool deleteCache(const std::string& key, const bool eternal) = __cell_zero;

    /*!
     * \brief Mark the cache as obsolete so it can be regenerated. Unlike delete.
     * \param string key cache storage location name.
     * \returns boolean.
     */
    __cell_virtual Types::OptionalBool obsolete(const std::string& key, const bool eternal) = __cell_zero;

private:
    CELL_DISABLE_COPY(AbstractCache)
};

CELL_NAMESPACE_END

#endif  // CELL_CACHE_ABSTRACT_HPP
