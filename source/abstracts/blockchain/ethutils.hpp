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

#ifndef CELL_ETH_UTILS_HPP
#define CELL_ETH_UTILS_HPP

//! Cell's Common.
#if __has_include("common.hpp")
#   include "common.hpp"
#else
#   error "Cell's common was not found!"
#endif

struct NetworkAdapter;

CELL_NAMESPACE_BEGIN(Cell::Abstracts::Blochchain)

/**
 * @namespace EthereumUtils
 * @brief Utility functions for Ethereum-related operations.
 */
std::optional<Json::Value> parseResponse(const std::string& response);

void processResult(const Json::Value& jsonResponse);

#endif // CELL_ETH_UTILS_HPP

CELL_NAMESPACE_END
