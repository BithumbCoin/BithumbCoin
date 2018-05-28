/**
 *  @file
 *  @copyright defined in BithumbCoin/LICENSE.txt
 */

#pragma once

#include "consumer_core.h"

#include <BithumbCoinio/chain/block_state.hpp>

namespace BithumbCoinio {

class block_storage : public consumer_core<chain::block_state_ptr>
{
public:
    void consume(const std::vector<chain::block_state_ptr>& blocks) override;
};

} // namespace
