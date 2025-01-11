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

#ifndef CELL_ETH_ABSTRACT_HPP
#define CELL_ETH_ABSTRACT_HPP

//! Cell's Common.
#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's common was not found!"
#endif

struct NetworkAdapter;

CELL_NAMESPACE_BEGIN(Cell::Abstracts::Blochchain)

/**
 * @class AbstractEthereumClient
 * @brief A class to interact with an Ethereum or Ethereum-compatible node.
 *
 * This class provides methods to send RPC requests to an Ethereum node,
 * parse the responses, and process the results. It supports common Ethereum RPC methods
 * such as retrieving block data, transaction details, estimating gas, and more.
 */
class __cell_export AbstractEthereumClient {
public:
    CELL_DEFAULT_INTERFACE_OCTORS(AbstractEthereumClient)
    /**
     * @brief Constructs an AbstractEthereumClient instance.
     * @param nodeUrl The URL of the Ethereum node (e.g., Infura, local node).
     * @param networkAdapter A reference to the NetworkAdapter used for sending requests.
     */
    AbstractEthereumClient(const std::string& nodeUrl, NetworkAdapter& networkAdapter);

    /**
     * @brief General method to send RPC requests.
     * @param method The name of the RPC method to call (e.g., "eth_blockNumber").
     * @param params The parameters for the RPC method (as a JSON object).
     * @return The raw JSON response as a string, wrapped in std::optional.
     */
    __cell_no_discard Types::OptionalString executeCommand(const std::string& method, const Json::Value& params);

    /**
     * @brief Parses the response from the Ethereum node.
     * @param response The raw response from the Ethereum node.
     * @return The parsed JSON response, or an empty std::optional in case of failure.
     */
    __cell_no_discard Types::OptionalJsonVal parseResponse(const std::string& response);

    /**
     * @brief Processes the parsed JSON response and outputs relevant information.
     * @param jsonResponse The parsed JSON response from the node.
     */
    void processResult(const Json::Value& jsonResponse);

           // Ethereum RPC Methods

    /**
     * @brief Retrieves the latest block number.
     * @return The block number as a string in hexadecimal format, or an empty std::optional if an error occurs.
     */
    __cell_no_discard Types::OptionalString getBlockNumber();

    /**
     * @brief Retrieves block information by block number.
     * @param blockNumber The block number (hexadecimal).
     * @param fullTransactionData Flag to determine whether to fetch full transaction data.
     * @return The block data in JSON format, or an empty std::optional if an error occurs.
     */
    __cell_no_discard Types::OptionalJsonVal getBlockByNumber(const std::string& blockNumber, bool fullTransactionData);

    /**
     * @brief Retrieves block information by block hash.
     * @param blockHash The block hash (hexadecimal).
     * @param fullTransactionData Flag to determine whether to fetch full transaction data.
     * @return The block data in JSON format, or an empty std::optional if an error occurs.
     */
    __cell_no_discard Types::OptionalJsonVal getBlockByHash(const std::string& blockHash, bool fullTransactionData);

    /**
     * @brief Retrieves transaction information by transaction hash.
     * @param txHash The transaction hash.
     * @return The transaction data in JSON format, or an empty std::optional if an error occurs.
     */
    __cell_no_discard Types::OptionalJsonVal getTransactionByHash(const std::string& txHash);

    /**
     * @brief Estimates the gas required for a transaction.
     * @param from The sender address.
     * @param to The recipient address.
     * @param value The value to be sent (in hexadecimal).
     * @return The estimated gas (in hexadecimal), or an empty std::optional if an error occurs.
     */
    __cell_no_discard Types::OptionalString estimateGas(const std::string& from, const std::string& to, const std::string& value);

    /**
     * @brief Retrieves the current gas price.
     * @return The current gas price in hexadecimal format, or an empty std::optional if an error occurs.
     */
    __cell_no_discard Types::OptionalString getGasPrice();

    /**
     * @brief Sends a raw transaction.
     * @param rawTransaction The raw transaction data.
     * @return The transaction hash (if successful), or an empty std::optional if an error occurs.
     */
    __cell_no_discard Types::OptionalString sendTransaction(const std::string& rawTransaction);

    /**
     * @brief Retrieves logs based on filter parameters.
     * @param params The filter parameters for fetching logs.
     * @return The logs in JSON format, or an empty std::optional if an error occurs.
     */
    __cell_no_discard Types::OptionalJsonVal getLogs(const Json::Value& params);

    /**
     * @brief Retrieves the transaction receipt by transaction hash.
     * @param txHash The transaction hash.
     * @return The transaction receipt data in JSON format, or an empty std::optional if an error occurs.
     */
    __cell_no_discard Types::OptionalJsonVal getTransactionReceipt(const std::string& txHash);

           // Additional Methods

    /**
     * @brief Retrieves the transaction count (nonce) for an address.
     * @param address The address for which to fetch the transaction count.
     * @return The transaction count (nonce) as a string, or an empty std::optional if an error occurs.
     */
    __cell_no_discard Types::OptionalString getTransactionCount(const std::string& address);

    /**
     * @brief Retrieves the chain ID of the connected Ethereum network.
     * @return The chain ID as a string, or an empty std::optional if an error occurs.
     */
    __cell_no_discard Types::OptionalString getChainId();

    /**
     * @brief Retrieves the version of the connected Ethereum network.
     * @return The network version as a string, or an empty std::optional if an error occurs.
     */
    __cell_no_discard Types::OptionalString getNetworkVersion();

    /**
     * @brief Checks if the Ethereum node is syncing.
     * @return Syncing status in JSON format, or an empty std::optional if an error occurs.
     */
    __cell_no_discard Types::OptionalString getSyncingStatus();

private:
    std::string nodeUrl; ///< The URL of the Ethereum node.
    NetworkAdapter& networkAdapter; ///< Reference to the network adapter used for sending requests.
};

CELL_NAMESPACE_END

#endif  // CELL_ETH_ABSTRACT_HPP
