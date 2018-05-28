/**
 *  @file
 *  @copyright defined in BithumbCoin/LICENSE.txt
 */

#pragma once

#include "consumer_core.h"

#include <memory>
#include <BithumbCoinio/chain/block_state.hpp>

#include "database.h"

namespace BithumbCoinio {

class irreversible_block_storage : public consumer_core<chain::block_state_ptr>
{
public:
    irreversible_block_storage(std::shared_ptr<database> db);

    void consume(const std::vector<chain::block_state_ptr>& blocks) override;

private:
    std::shared_ptr<database> m_db;
};

} // namespace

