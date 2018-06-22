/**
 *  @file
 *  @copyright defined in BithumbCoin/LICENSE.txt
 */
#pragma once

#include <fc/exception/exception.hpp>
#include <BithumbCoinio/chain/exceptions.hpp>

#define BithumbCoin_DECLARE_INTERNAL_EXCEPTION( exc_name, seqnum, msg )  \
   FC_DECLARE_DERIVED_EXCEPTION(                                      \
      internal_ ## exc_name,                                          \
      BithumbCoinio::chain::internal_exception,                            \
      3990000 + seqnum,                                               \
      msg                                                             \
      )

namespace BithumbCoinio { namespace chain {

FC_DECLARE_DERIVED_EXCEPTION( internal_exception, BithumbCoinio::chain::chain_exception, 3990000, "internal exception" )

BithumbCoin_DECLARE_INTERNAL_EXCEPTION( verify_auth_max_auth_exceeded, 1, "Exceeds max authority fan-out" )
BithumbCoin_DECLARE_INTERNAL_EXCEPTION( verify_auth_account_not_found, 2, "Auth account not found" )

} } // BithumbCoinio::chain
