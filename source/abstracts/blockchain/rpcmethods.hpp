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

#ifndef CELL_ETH_RPC_METHOD_HPP
#define CELL_ETH_RPC_METHOD_HPP

//! Cell's Common.
#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's common was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell::Abstracts::Blochchain)

/**
 * @class EthereumRpcMethods
 * @brief Provides common Ethereum RPC method calls.
 */
class EthereumRpcMethods {
public:
    EthereumRpcMethods(EthereumClient& client);

    std::optional<std::string> getBlockNumber();
    std::optional<Json::Value> getBlockByNumber(const std::string& blockNumber, bool fullTransactionData);
    std::optional<Json::Value> getBlockByHash(const std::string& blockHash, bool fullTransactionData);
    std::optional<Json::Value> getTransactionByHash(const std::string& txHash);
    std::optional<std::string> estimateGas(const std::string& from, const std::string& to, const std::string& value);
    std::optional<std::string> getGasPrice();
    std::optional<std::string> sendTransaction(const std::string& rawTransaction);
    std::optional<Json::Value> getLogs(const Json::Value& params);
    std::optional<Json::Value> getTransactionReceipt(const std::string& txHash);
    std::optional<std::string> getTransactionCount(const std::string& address);
    std::optional<std::string> getChainId();
    std::optional<std::string> getNetworkVersion();
    std::optional<std::string> getSyncingStatus();

private:
    EthereumClient& client;
};
#endif // CELL_ETH_RPC_METHOD_HPP

CELL_NAMESPACE_END
