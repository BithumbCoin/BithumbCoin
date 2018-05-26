/**
 *  @file
 *  @copyright defined in BithumbCoin/LICENSE.txt
 */

#include <BithumbCoinio/chain/get_config.hpp>
#include <BithumbCoinio/chain/config.hpp>
#include <BithumbCoinio/chain/types.hpp>

namespace BithumbCoinio { namespace chain {

fc::variant_object get_config()
{
   fc::mutable_variant_object result;

//   result["block_interval_ms"] = config::block_interval_ms;
//   result["producer_count"] = config::producer_count;
   /// TODO: add extra config parms
   return result;
}

} } // BithumbCoinio::chain
