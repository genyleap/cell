/*!
 * @file        eth.hpp
 * @brief       This file is part of the Cell Engine.
 * @details     Eth interface for Ethereum blochchain.
 * @author      <a href='https://github.com/thecompez'>Kambiz Asadzadeh</a>
 * @package     Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2025 The Genyleap. All rights reserved.
 * @link        https://genyleap.com/technology/cell
 *
 */

#ifndef CELL_ETH_CLIENT_HPP
#define CELL_ETH_CLIENT_HPP

//! Cell's Common.
#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's common was not found!"
#endif

struct NetworkAdapter;

CELL_NAMESPACE_BEGIN(Cell::Abstracts::Blochchain)

/**
 * @class EthereumClient
 * @brief Main class to manage interaction with Ethereum nodes.
 */
class PROJECT_EXPORT EthereumClient {
public:
    EthereumClient(const std::string& nodeUrl, NetworkAdapter& networkAdapter);

    /**
     * @brief Executes an Ethereum RPC command.
     * @param method The name of the method.
     * @param params The parameters as a JSON object.
     * @return The response as a string or nullopt on failure.
     */
    std::optional<std::string> executeCommand(const std::string& method, const Json::Value& params);

private:
    std::string nodeUrl;
    NetworkAdapter& networkAdapter;
};


#endif // CELL_ETH_CLIENT_HPP

CELL_NAMESPACE_END
