/*!
 * @file        utility.hpp
 * @brief       Utilities for the Cell Engine.
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


#ifndef CELL_UTILITY_OS_APPLICATION_HPP
#define CELL_UTILITY_OS_APPLICATION_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Utility)

/**
 * @brief The ApplicationRetriever class provides functionality to retrieve and manipulate installed applications.
 */
class __cell_export ApplicationRetriever {
public:
    /**
     * @brief Constructs an ApplicationRetriever object.
     */
    ApplicationRetriever();

    /**
     * @brief Destructs the ApplicationRetriever object.
     */
    ~ApplicationRetriever();

    /**
     * @brief Retrieves the names and versions of all installed applications.
     * @return A vector of pairs where each pair contains the application name and version.
     */
    std::vector<std::pair<std::string, std::string>> getInstalledApplications();

    /**
     * @brief Filters the provided list of application names based on the specified category.
     * @param appNames A vector of pairs where each pair contains the application name and version.
     * @param category The category to filter by.
     * @return A vector of pairs where each pair contains the filtered application name and version.
     */
    std::vector<std::pair<std::string, std::string>> filterByCategory(const std::vector<std::pair<std::string, std::string>>& appNames, const std::string& category);

    /**
     * @brief Sorts the provided list of application names in ascending or descending order.
     * @param appNames A vector of pairs where each pair contains the application name and version.
     * @param ascending Boolean value indicating whether to sort in ascending order (default: true).
     */
    void sortApplications(std::vector<std::pair<std::string, std::string>>& appNames, bool ascending = true);

private:
    /**
     * @brief Checks if an application belongs to the specified category.
     * @param appName The name of the application.
     * @param category The category to check against.
     * @return True if the application belongs to the category, false otherwise.
     */
    bool isAppInCategory(const std::string& appName, const std::string& category);

#ifdef CELL_PLATFORM_MAC
    /**
     * @brief Retrieves the names and versions of all installed applications on macOS.
     * @return A vector of pairs where each pair contains the application name and version.
     */
    std::vector<std::pair<std::string, std::string>> getInstalledApplicationsMac();
#elif defined(CELL_PLATFORM_ANDROID)
    /**
     * @brief Retrieves the names and versions of all installed applications on Android.
     * @return A vector of pairs where each pair contains the application name and version.
     */
    std::vector<std::pair<std::string, std::string>> getInstalledApplicationsAndroid();
#elif defined(CELL_PLATFORM_IOS)
    /**
     * @brief Retrieves the names and versions of all installed applications on iOS.
     * @return A vector of pairs where each pair contains the application name and version.
     */
    std::vector<std::pair<std::string, std::string>> getInstalledApplicationsiOS();
#elif defined(CELL_PLATFORM_LINUX)
    /**
     * @brief Retrieves the names and versions of all installed applications on Linux.
     * @return A vector of pairs where each pair contains the application name and version.
     */
    std::vector<std::pair<std::string, std::string>> getInstalledApplicationsLinux();
#endif
};

CELL_NAMESPACE_END

#endif // CELL_UTILITY_OS_APPLICATION_HPP
