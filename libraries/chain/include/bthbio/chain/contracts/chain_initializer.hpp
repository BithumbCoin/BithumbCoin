/**
 *  @file
 *  @copyright defined in BithumbCoin/LICENSE.txt
 */
#pragma once

#include <BithumbCoinio/chain/contracts/genesis_state.hpp>
#include <BithumbCoinio/chain/contracts/types.hpp>
#include <BithumbCoinio/chain/chain_controller.hpp>

namespace BithumbCoinio { namespace chain {  namespace contracts {

   class chain_initializer 
   {

      public:
         chain_initializer(const genesis_state_type& genesis) : genesis(genesis) {}

         time_point              get_chain_start_time();
         chain::chain_config     get_chain_start_configuration();
         producer_schedule_type  get_chain_start_producers();

         void register_types(chain::chain_controller& chain, chainbase::database& db);

         void prepare_database(chain::chain_controller& chain, chainbase::database& db);

         static abi_def BithumbCoin_contract_abi(const abi_def& BithumbCoinio_system_abi);

      private:
         genesis_state_type genesis;
   };

} } } // namespace BithumbCoinio::chain::contracts

