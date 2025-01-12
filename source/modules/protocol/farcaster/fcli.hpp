/*!
 * @file        fcli.hpp
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

#if __has_include("modules/network/http/network.hpp")
#   include "modules/network/http/network.hpp"
#else
#   error "Cell's "modules/network/http/network.hpp" was not found!"
#endif

#ifndef CELL_FCLI_HPP
#define CELL_FCLI_HPP

CELL_NAMESPACE_BEGIN(Cell::Modules::BuiltIn::Protocol::Farcaster)

/**
 * @class FCLI
 * @brief A command-line interface for interacting with APIs using the `Network` utility.
 *
 * Handles user input, constructs and sends API requests, and processes the responses.
 * Provides features like JSON pretty-printing and dynamic help messages.
 * Supports dynamic configuration of the hub address.
 */
class FCLI {
private:
    /**
     * @brief The base URL of the hub (default: "https://hub.pinata.cloud").
     */
    std::string baseUrl = "https://hub.pinata.cloud";

    /**
     * @brief A utility object for handling network requests.
     */
    Network::Network network;

    /**
     * @brief Pretty-prints a JSON string to the console.
     *
     * Parses a raw JSON string and outputs it in a human-readable format
     * with indentation.
     *
     * @param json The raw JSON string to pretty-print.
     */
    void prettyPrintJson(const std::string& json);

    /**
     * @brief Displays help information for available commands or a specific endpoint.
     *
     * Outputs general help if no endpoint is specified. If an endpoint is provided,
     * details and examples specific to that endpoint are shown.
     *
     * @param endpoint The optional endpoint for which help is requested (default: "").
     */
    void handleHelp(const std::string& endpoint = "");

    /**
     * @brief Executes an API command by sending a request to the specified endpoint.
     *
     * Constructs the full URL using the base endpoint and query parameters, sends
     * the request using the `Network` utility, and processes the response.
     *
     * @param endpoint The API endpoint to query (e.g., `/v1/info`).
     * @param params A map of query parameters to include in the request.
     * @param verbose If `true`, enables verbose output for debugging (default: false).
     */
    void executeCommand(const std::string& endpoint, const std::map<std::string, std::string>& params, bool verbose);

    /**
     * @brief Sets the base URL for the hub dynamically.
     *
     * Updates the `baseUrl` with a custom hub address provided by the user.
     *
     * @param hubUrl The custom hub URL to set.
     */
    void setHubUrl(const std::string& hubUrl);

public:
    /**
     * @brief Main entry point for the command-line interface.
     *
     * Parses command-line arguments, determines the requested action, and
     * executes the corresponding command or displays help.
     *
     * @param argc The number of command-line arguments.
     * @param argv An array of command-line argument strings.
     */
    void run(int argc, char* argv[]);
};

CELL_NAMESPACE_END

#endif // FCLI_HPP
