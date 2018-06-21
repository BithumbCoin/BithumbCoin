/**
 *  @file
 *  @copyright defined in BithumbCoin/LICENSE.txt
 */

#include <bthbio/chain/get_config.hpp>
#include <bthbio/chain/config.hpp>
#include <bthbio/chain/types.hpp>

namespace bthbio { namespace chain {

fc::variant_object get_config()
{
   fc::mutable_variant_object result;

//   result["block_interval_ms"] = config::block_interval_ms;
//   result["producer_count"] = config::producer_count;
   /// TODO: add extra config parms
   return result;
}

} } // bthbio::chain
