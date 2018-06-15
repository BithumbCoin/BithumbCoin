/**
 *  @file
 *  @copyright defined in BithumbCoin/LICENSE.txt
 */

#include <bthbio/chain/contracts/genesis_state.hpp>

// these are required to serialize a genesis_state
#include <fc/smart_ref_impl.hpp>   // required for gcc in release mode

namespace bthbio { namespace chain { namespace contracts {


chain::chain_id_type genesis_state_type::compute_chain_id() const {
   return initial_chain_id;
}

} } } // namespace bthbio::chain::contracts
