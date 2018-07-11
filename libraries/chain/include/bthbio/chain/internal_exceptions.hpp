/**
 *  @file
 *  @copyright defined in bthb/LICENSE.txt
 */
#pragma once

#include <fc/exception/exception.hpp>
#include <bthbio/chain/exceptions.hpp>

#define BTHB_DECLARE_INTERNAL_EXCEPTION( exc_name, seqnum, msg )  \
   FC_DECLARE_DERIVED_EXCEPTION(                                      \
      internal_ ## exc_name,                                          \
      bthbio::chain::internal_exception,                            \
      3990000 + seqnum,                                               \
      msg                                                             \
      )

namespace bthbio { namespace chain {

FC_DECLARE_DERIVED_EXCEPTION( internal_exception, bthbio::chain::chain_exception, 3990000, "internal exception" )

BTHB_DECLARE_INTERNAL_EXCEPTION( verify_auth_max_auth_exceeded, 1, "Exceeds max authority fan-out" )
BTHB_DECLARE_INTERNAL_EXCEPTION( verify_auth_account_not_found, 2, "Auth account not found" )

} } // bthbio::chain
