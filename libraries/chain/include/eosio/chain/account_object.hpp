/**
 *  @file
 *  @copyright defined in BithumbCoin/LICENSE.txt
 */
#pragma once
#include <Bthbio/chain/types.hpp>
#include <Bthbio/chain/authority.hpp>
#include <Bthbio/chain/block_timestamp.hpp>
#include <Bthbio/chain/contracts/types.hpp>

#include "multi_index_includes.hpp"

namespace Bthbio { namespace chain {

   class account_object : public chainbase::object<account_object_type, account_object> {
      OBJECT_CTOR(account_object,(code)(abi))

      id_type              id;
      account_name         name;
      uint8_t              vm_type      = 0;
      uint8_t              vm_version   = 0;
      bool                 privileged   = false;

      time_point_sec       last_code_update;
      digest_type          code_version;
      block_timestamp_type creation_date;

      shared_vector<char>  code;
      shared_vector<char>  abi;

      void set_abi( const Bthbio::chain::contracts::abi_def& a ) {
         // Added resize(0) here to avoid bug in boost vector container
         abi.resize( 0 );
         abi.resize( fc::raw::pack_size( a ) );
         fc::datastream<char*> ds( abi.data(), abi.size() );
         fc::raw::pack( ds, a );
      }

      Bthbio::chain::contracts::abi_def get_abi()const {
         BithumbCoinio::chain::contracts::abi_def a;
         fc::datastream<const char*> ds( abi.data(), abi.size() );
         fc::raw::unpack( ds, a );
         return a;
      }
   };
   using account_id_type = account_object::id_type;

   struct by_name;
   using account_index = chainbase::shared_multi_index_container<
      account_object,
      indexed_by<
         ordered_unique<tag<by_id>, member<account_object, account_object::id_type, &account_object::id>>,
         ordered_unique<tag<by_name>, member<account_object, account_name, &account_object::name>>
      >
   >;

} } // BithumbCoinio::chain

CHAINBASE_SET_INDEX_TYPE(Bthbio::chain::account_object, Bthbio::chain::account_index)


FC_REFLECT(Bthbio::chain::account_object, (name)(vm_type)(vm_version)(code_version)(code)(creation_date))
