/**
 *  @file
 *  @copyright defined in BithumbCoin/LICENSE.txt
 */
#pragma once
#include <vector>
#include <string>

namespace BithumbCoinio { namespace chain {

std::vector<uint8_t> wast_to_wasm( const std::string& wast );
std::string  wasm_to_wast( const std::vector<uint8_t>& wasm );
std::string  wasm_to_wast( const uint8_t* data, uint64_t size );

} } /// BithumbCoinio::chain
