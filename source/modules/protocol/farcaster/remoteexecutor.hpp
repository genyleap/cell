/*!
 * @file        remoteexecutor.hpp
 * @brief       Farcaster command-line tool  for the Cell Engine.
 * @details     FCLI is a powerful, extensible, and thread-safe command-line interface (CLI) tool for interacting with APIs, particularly those following the Farcaster hub protocol.
 * @author      Kambiz Asadzadeh
 * @since       01 Jan 2025
 * @version     1.0
 * @note        This is part of the Cell Engine, developed by Kambiz Asadzadeh.
 *
 * @license     This file is licensed under the terms of the Genyleap License. See the LICENSE.md file for more information.
 * @copyright   Copyright (c) 2025 The Genyleap | Kambiz Asadzadeh. All rights reserved.
 * @see         https://github.com/genyleap/cell
 */

#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's "common.hpp" was not found!"
#endif


#ifndef REMOTE_EXECUTOR_HPP
#define REMOTE_EXECUTOR_HPP

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Protocol::Farcaster)

#include <string>
#include <stdexcept>

/**
 * @class RemoteExecutor
 * @brief Provides functionality to execute commands remotely via SSH or API.
 *
 * This class offers static methods for executing shell commands on remote servers
 * using SSH and interacting with APIs to execute commands remotely.
 */
class RemoteExecutor {
public:
    /**
     * @brief Executes a command on a remote server via SSH.
     *
     * This method establishes an SSH connection to the specified host using the given
     * user credentials and private key. It then executes the provided command remotely
     * and captures the output.
     *
     * @param host The hostname or IP address of the remote server.
     * @param user The username for the SSH connection.
     * @param command The shell command to execute on the remote server.
     * @param keyPath The path to the private key file for SSH authentication.
     * @return The output of the command executed on the remote server.
     * @throws std::runtime_error If the SSH command execution fails.
     */
    static std::string executeSSH(const std::string& host, const std::string& user,
                                  const std::string& command, const std::string& keyPath);

    /**
     * @brief Executes a command via an API.
     *
     * This method sends a POST request to the specified API URL with the provided command
     * as a parameter. Authentication is performed using a bearer token.
     *
     * @param url The API endpoint URL.
     * @param command The command or data to send to the API for execution.
     * @param token The bearer token for API authentication.
     * @return The response from the API.
     * @throws std::runtime_error If the API request fails.
     */
    static std::string executeAPI(const std::string& url, const std::string& command,
                                  const std::string& token);
};

CELL_NAMESPACE_END

#endif // REMOTE_EXECUTOR_HPP
