/*!
 * @file        repository.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Repository manager.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       28 Apr 2023
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_REPOSITORY_HPP
#define CELL_REPOSITORY_HPP

#ifdef __has_include
# if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
# endif
#endif

CELL_NAMESPACE_BEGIN(Cell::Maintenance)

using SpeedCache = std::unordered_map<std::string, double>;

struct RepositoryData final
{
    Types::OptionalString           repoUrl {}; //!< Repository Url.
    Types::VectorString             mirrors {}; //!< List of mirrors.
    SpeedCache                      mirrorSpeedCache;   //!< Store all the data associated with a particular repository.
};

/**
 * Repository class for managing mirrors of a software repository.
 */
class __cell_export Repository {
public:
    /**
     * Constructor for Repository.
     * repo_url: The URL of the main repository.
     */
    Repository(const std::string& repo_url);

    /**
     * Destructor for Repository.
     */
    ~Repository();

    /**
     * @brief Measures the speed of the mirror, such as pinging the mirror and measuring
     * the response time, or downloading a small file from the mirror and measuring the download time.
     * @param mirrorUrl: The URL of the mirror to add.
     * @return The speed in microseconds per byte.
     */
    double measureSpeed(const std::string& mirrorUrl);
    /**
     * @brief Add a mirror to the list of mirrors for the repository.
     * @param mirrorUrl: The URL of the mirror to add.
     */
    void addMirror(const std::string& mirrorUrl);

    /**
     * @brief Remove a mirror from the list of mirrors for the repository.
     * @param mirrorUrl: The URL of the mirror to remove.
     */
    void removeMirror(const std::string& mirrorUrl);

    /**
     * @brief Get the URL of the fastest mirror for the repository.
     * @return Returns an empty string if no mirrors are available.
     */
    std::string getFastestMirror();

    /**
     * @brief Get the speed of a mirror in Mbps.
     * @param mirrorUrl: The URL of the mirror to test.
     * @return Returns -1 if the speed could not be determined.
     */
    double getMirrorSpeed(const std::string& mirrorUrl);

private:
    RepositoryData repositoryData {}; //!< Repository data, including URL and mirrors.
};

CELL_NAMESPACE_END


#endif // CELL_REPOSITORY_HPP
