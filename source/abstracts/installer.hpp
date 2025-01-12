/*!
 * @file        installer.hpp
 * @brief       Installer manager interface for the Cell Engine.
 * @details     This file defines the Database interface, which provides methods for interacting with a database.
 * @author      Kambiz Asadzadeh
 * @since       07 Jun 2023
 * @version     1.0
 * @note        This is part of the Cell Engine, developed by Kambiz Asadzadeh.
 *
 * @license     This file is licensed under the terms of the Genyleap License. See the LICENSE.md file for more information.
 * @copyright   Copyright (c) 2025 The Genyleap | Kambiz Asadzadeh. All rights reserved.
 * @see         https://github.com/genyleap/cell
 */

#ifndef CELL_INSTALLER_ABSTRACT_HPP
#define CELL_INSTALLER_ABSTRACT_HPP

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Abstracts)

/**
 * @class Installer
 * @brief Abstract class representing an installer.
 */
class __cell_export AbstractInstaller {
public:
    CELL_DEFAULT_INTERFACE_OCTORS(AbstractInstaller)

    /**
     * @brief Initializes the installer.
     */
    __cell_virtual void Initialize() = 0;

    /**
     * @brief Creates a user account.
     * @return True if the account creation is successful, false otherwise.
     */
    __cell_virtual bool CreateAccount() = 0;

    /**
     * @brief Logs in to the installer.
     * @return True if the login is successful, false otherwise.
     */
    __cell_virtual bool Login() = 0;

    /**
     * @brief Displays a welcome message.
     */
    __cell_virtual void ShowWelcomeMessage() = 0;

    /**
     * @brief Displays the license agreement.
     */
    __cell_virtual void ShowLicenseAgreement() = 0;

    /**
     * @brief Accepts the license agreement.
     * @return True if the license agreement is accepted, false otherwise.
     */
    __cell_virtual bool AcceptLicenseAgreement() = 0;

    /**
     * @brief Displays the system requirements.
     */
    __cell_virtual void ShowSystemRequirements() = 0;

    /**
     * @brief Checks the system requirements.
     * @return True if the system meets the requirements, false otherwise.
     */
    __cell_virtual bool CheckSystemRequirements() = 0;

    /**
     * @brief Configures the repository or mirror.
     */
    __cell_virtual void ConfigureRepository() = 0;

    /**
     * @brief Connects to the repository or mirror.
     * @return True if the connection is successful, false otherwise.
     */
    __cell_virtual bool ConnectToRepository() = 0;

    /**
     * @brief Retrieves the list of available packages.
     * @return A vector of package names.
     */
    __cell_virtual std::vector<std::string> GetAvailablePackages() = 0;

    /**
     * @brief Downloads a package.
     * @param packageName The name of the package to download.
     */
    __cell_virtual void DownloadPackage(const std::string& packageName) = 0;

    /**
     * @brief Installs a package.
     * @param packageName The name of the package to install.
     */
    __cell_virtual void InstallPackage(const std::string& packageName) = 0;

    /**
     * @brief Uninstalls a package.
     * @param packageName The name of the package to uninstall.
     */
    __cell_virtual void UninstallPackage(const std::string& packageName) = 0;

    /**
     * @brief Updates a package.
     * @param packageName The name of the package to update.
     */
    __cell_virtual void UpdatePackage(const std::string& packageName) = 0;

    /**
     * @brief Performs cleanup operations.
     */
    __cell_virtual void Cleanup() = 0;

    /**
     * @brief Shows the installation progress.
     * @param progress The progress value (0.0 to 1.0).
     */
    __cell_virtual void ShowProgress(double progress) = 0;

    /**
     * @brief Checks whether a package is installed.
     * @param packageName The name of the package to check.
     * @return True if the package is installed, false otherwise.
     */
    virtual bool IsPackageInstalled(const std::string& packageName) = 0;

};


CELL_NAMESPACE_END

#endif  // CELL_INSTALLER_ABSTRACT_HPP
