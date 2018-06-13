/**
 *  @file
 *  @copyright defined in BithumbCoin/LICENSE.txt
 */
#include <bthbio/chain/contracts/chain_initializer.hpp>
#include <bthbio/chain/contracts/bthbio_contract.hpp>
#include <bthbio/chain/contracts/types.hpp>

#include <bthbio/chain/producer_object.hpp>
#include <bthbio/chain/permission_object.hpp>

#include <fc/io/json.hpp>

#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/algorithm/copy.hpp>

namespace bthbio { namespace chain { namespace contracts {

time_point chain_initializer::get_chain_start_time() {
   return genesis.initial_timestamp;
}

chain_config chain_initializer::get_chain_start_configuration() {
   return genesis.initial_configuration;
}

producer_schedule_type  chain_initializer::get_chain_start_producers() {
   producer_schedule_type result;
   result.producers.push_back( {config::system_account_name, genesis.initial_key} );
   return result;
}

void chain_initializer::register_types(chain_controller& chain, chainbase::database& db) {

#define SET_APP_HANDLER( contract, scope, action, nspace ) \
   chain._set_apply_handler( #contract, #scope, #action, &BOOST_PP_CAT(contracts::apply_, BOOST_PP_CAT(contract, BOOST_PP_CAT(_,action) ) ) )
   SET_APP_HANDLER( bthbio, bthbio, newaccount, bthbio );
   SET_APP_HANDLER( bthbio, bthbio, setcode, bthbio );
   SET_APP_HANDLER( bthbio, bthbio, setabi, bthbio );
   SET_APP_HANDLER( bthbio, bthbio, updateauth, bthbio );
   SET_APP_HANDLER( bthbio, bthbio, deleteauth, bthbio );
   SET_APP_HANDLER( bthbio, bthbio, linkauth, bthbio );
   SET_APP_HANDLER( bthbio, bthbio, unlinkauth, bthbio );
   SET_APP_HANDLER( bthbio, bthbio, onerror, bthbio );
   SET_APP_HANDLER( bthbio, bthbio, postrecovery, bthbio );
   SET_APP_HANDLER( bthbio, bthbio, passrecovery, bthbio );
   SET_APP_HANDLER( bthbio, bthbio, vetorecovery, bthbio );
   SET_APP_HANDLER( bthbio, bthbio, canceldelay, bthbio );
}


abi_def chain_initializer::bthbio_contract_abi(const abi_def& bthbio_system_abi)
{
   abi_def bthbio_abi(bthbio_system_abi);
   bthbio_abi.types.push_back( type_def{"account_name","name"} );
   bthbio_abi.types.push_back( type_def{"table_name","name"} );
   bthbio_abi.types.push_back( type_def{"share_type","int64"} );
   bthbio_abi.types.push_back( type_def{"onerror","bytes"} );
   bthbio_abi.types.push_back( type_def{"context_free_type","bytes"} );
   bthbio_abi.types.push_back( type_def{"weight_type","uint16"} );
   bthbio_abi.types.push_back( type_def{"fields","field[]"} );
   bthbio_abi.types.push_back( type_def{"time_point_sec","time"} );

   // TODO add ricardian contracts
   bthbio_abi.actions.push_back( action_def{name("setcode"), "setcode",""} );
   bthbio_abi.actions.push_back( action_def{name("setabi"), "setabi",""} );
   bthbio_abi.actions.push_back( action_def{name("linkauth"), "linkauth",""} );
   bthbio_abi.actions.push_back( action_def{name("unlinkauth"), "unlinkauth",""} );
   bthbio_abi.actions.push_back( action_def{name("updateauth"), "updateauth",""} );
   bthbio_abi.actions.push_back( action_def{name("deleteauth"), "deleteauth",""} );
   bthbio_abi.actions.push_back( action_def{name("newaccount"), "newaccount",""} );
   bthbio_abi.actions.push_back( action_def{name("postrecovery"), "postrecovery",""} );
   bthbio_abi.actions.push_back( action_def{name("passrecovery"), "passrecovery",""} );
   bthbio_abi.actions.push_back( action_def{name("vetorecovery"), "vetorecovery",""} );
   bthbio_abi.actions.push_back( action_def{name("onerror"), "onerror",""} );
   bthbio_abi.actions.push_back( action_def{name("onblock"), "onblock",""} );
   bthbio_abi.actions.push_back( action_def{name("canceldelay"), "canceldelay",""} );

   // TODO add any ricardian_clauses
   //
   // ACTION PAYLOADS


   bthbio_abi.structs.emplace_back( struct_def {
      "setcode", "", {
         {"account", "account_name"},
         {"vmtype", "uint8"},
         {"vmversion", "uint8"},
         {"code", "bytes"}
      }
   });

   bthbio_abi.structs.emplace_back( struct_def {
      "setabi", "", {
         {"account", "account_name"},
         {"abi", "abi_def"}
      }
   });

   bthbio_abi.structs.emplace_back( struct_def {
      "updateauth", "", {
         {"account", "account_name"},
         {"permission", "permission_name"},
         {"parent", "permission_name"},
         {"data", "authority"},
         {"delay", "uint32"}
      }
   });

   bthbio_abi.structs.emplace_back( struct_def {
      "linkauth", "", {
         {"account", "account_name"},
         {"code", "account_name"},
         {"type", "action_name"},
         {"requirement", "permission_name"},
      }
   });

   bthbio_abi.structs.emplace_back( struct_def {
      "unlinkauth", "", {
         {"account", "account_name"},
         {"code", "account_name"},
         {"type", "action_name"},
      }
   });

   bthbio_abi.structs.emplace_back( struct_def {
      "deleteauth", "", {
         {"account", "account_name"},
         {"permission", "permission_name"},
      }
   });

   bthbio_abi.structs.emplace_back( struct_def {
      "newaccount", "", {
         {"creator", "account_name"},
         {"name", "account_name"},
         {"owner", "authority"},
         {"active", "authority"},
         {"recovery", "authority"},
      }
   });

   bthbio_abi.structs.emplace_back( struct_def {
      "postrecovery", "", {
         {"account", "account_name"},
         {"data", "authority"},
         {"memo", "string"},
      }
   });

   bthbio_abi.structs.emplace_back( struct_def {
      "passrecovery", "", {
         {"account", "account_name"},
      }
   });

   bthbio_abi.structs.emplace_back( struct_def {
      "vetorecovery", "", {
         {"account", "account_name"},
      }
   });

   bthbio_abi.structs.emplace_back( struct_def {
      "canceldelay", "", {
         {"canceling_auth", "permission_level"},
         {"trx_id", "transaction_id_type"},
      }
   });

   // DATABASE RECORDS

   bthbio_abi.structs.emplace_back( struct_def {
      "pending_recovery", "", {
         {"account",    "name"},
         {"request_id", "uint128"},
         {"update",     "updateauth"},
         {"memo",       "string"}
      }
   });

   bthbio_abi.tables.emplace_back( table_def {
      "recovery", "i64", {
         "account",
      }, {
         "name"
      },
      "pending_recovery"
   });

   // abi_def fields

   bthbio_abi.structs.emplace_back( struct_def {
      "field", "", {
         {"name", "field_name"},
         {"type", "type_name"}
      }
   });

   bthbio_abi.structs.emplace_back( struct_def {
      "struct_def", "", {
         {"name", "type_name"},
         {"base", "type_name"},
         {"fields", "fields"}
      }
   });

   bthbio_abi.structs.emplace_back( struct_def {
      "permission_level", "", {
         {"actor", "account_name"},
         {"permission", "permission_name"}
      }
   });

   bthbio_abi.structs.emplace_back( struct_def {
      "action", "", {
         {"account", "account_name"},
         {"name", "action_name"},
         {"authorization", "permission_level[]"},
         {"data", "bytes"}
      }
   });

   bthbio_abi.structs.emplace_back( struct_def {
      "permission_level_weight", "", {
         {"permission", "permission_level"},
         {"weight", "weight_type"}
      }
   });

   bthbio_abi.structs.emplace_back( struct_def {
      "transaction_header", "", {
         {"expiration", "time_point_sec"},
         {"region", "uint16"},
         {"ref_block_num", "uint16"},
         {"ref_block_prefix", "uint32"},
         {"max_net_usage_words", "varuint32"},
         {"max_kcpu_usage", "varuint32"},
         {"delay_sec", "varuint32"}
      }
   });

   bthbio_abi.structs.emplace_back( struct_def {
      "transaction", "transaction_header", {
         {"context_free_actions", "action[]"},
         {"actions", "action[]"}
      }
   });

   bthbio_abi.structs.emplace_back( struct_def {
      "signed_transaction", "transaction", {
         {"signatures", "signature[]"},
         {"context_free_data", "bytes[]"}
      }
   });

   bthbio_abi.structs.emplace_back( struct_def {
      "key_weight", "", {
         {"key", "public_key"},
         {"weight", "weight_type"}
      }
   });

   bthbio_abi.structs.emplace_back( struct_def {
      "authority", "", {
         {"threshold", "uint32"},
         {"keys", "key_weight[]"},
         {"accounts", "permission_level_weight[]"}
      }
   });
   bthbio_abi.structs.emplace_back( struct_def {
         "clause_pair", "", {
            {"id", "string"},
            {"body", "string"}
         }
   });
   bthbio_abi.structs.emplace_back( struct_def {
      "type_def", "", {
         {"new_type_name", "type_name"},
         {"type", "type_name"}
      }
   });

   bthbio_abi.structs.emplace_back( struct_def {
      "action_def", "", {
         {"name", "action_name"},
         {"type", "type_name"},
         {"ricardian_contract", "string"}
      }
   });

   bthbio_abi.structs.emplace_back( struct_def {
      "table_def", "", {
         {"name", "table_name"},
         {"index_type", "type_name"},
         {"key_names", "field_name[]"},
         {"key_types", "type_name[]"},
         {"type", "type_name"}
      }
   });

   bthbio_abi.structs.emplace_back( struct_def {
      "abi_def", "", {
         {"types", "type_def[]"},
         {"structs", "struct_def[]"},
         {"actions", "action_def[]"},
         {"tables", "table_def[]"},
         {"ricardian_clauses", "clause_pair[]"}
      }
   });

   bthbio_abi.structs.emplace_back( struct_def {
      "block_header", "", {
         {"previous", "checksum256"},
         {"timestamp", "uint32"},
         {"transaction_mroot", "checksum256"},
         {"action_mroot", "checksum256"},
         {"block_mroot", "checksum256"},
         {"producer", "account_name"},
         {"schedule_version", "uint32"},
         {"new_producers", "producer_schedule?"}
      }
   });

   bthbio_abi.structs.emplace_back( struct_def {
         "onblock", "", {
            {"header", "block_header"}
      }
   });

   return bthbio_abi;
}

void chain_initializer::prepare_database( chain_controller& chain,
                                                         chainbase::database& db) {
   /// Reserve id of 0 in permission_index by creating dummy permission_object as the very first object in the index:
   db.create<permission_object>([&](permission_object& p) {
   });

   /// Create the native contract accounts manually; sadly, we can't run their contracts to make them create themselves
   auto create_native_account = [this, &chain, &db](account_name name) {
      db.create<account_object>([this, &name](account_object& a) {
         a.name = name;
         a.creation_date = genesis.initial_timestamp;
         a.privileged = true;

         if( name == config::system_account_name ) {
            a.set_abi(bthbio_contract_abi(abi_def()));
         }
      });
      const auto& owner = db.create<permission_object>([&](permission_object& p) {
         p.owner = name;
         p.name = "owner";
         p.auth.threshold = 1;
         p.auth.keys.push_back( key_weight{ .key = genesis.initial_key, .weight = 1 } );
      });
      db.create<permission_object>([&](permission_object& p) {
         p.owner = name;
         p.parent = owner.id;
         p.name = "active";
         p.auth.threshold = 1;
         p.auth.keys.push_back( key_weight{ .key = genesis.initial_key, .weight = 1 } );
      });

      chain.get_mutable_resource_limits_manager().initialize_account(name);

      db.create<producer_object>( [&]( auto& pro ) {
         pro.owner = config::system_account_name;
         pro.signing_key = genesis.initial_key;
      });
   };
   create_native_account(config::system_account_name);

   // Create special accounts
   auto create_special_account = [this, &db](account_name name, const auto& owner, const auto& active) {
      db.create<account_object>([this, &name](account_object& a) {
         a.name = name;
         a.creation_date = genesis.initial_timestamp;
      });
      const auto& owner_permission = db.create<permission_object>([&owner, &name](permission_object& p) {
         p.name = config::owner_name;
         p.parent = 0;
         p.owner = name;
         p.auth = move(owner);
      });
      db.create<permission_object>([&active, &owner_permission](permission_object& p) {
         p.name = config::active_name;
         p.parent = owner_permission.id;
         p.owner = owner_permission.owner;
         p.auth = move(active);
      });
   };

   auto empty_authority = authority(0, {}, {});
   auto active_producers_authority = authority(0, {}, {});
   active_producers_authority.accounts.push_back({{config::system_account_name, config::active_name}, 1});

   create_special_account(config::nobody_account_name, empty_authority, empty_authority);
   create_special_account(config::producers_account_name, empty_authority, active_producers_authority);
}

} } } // namespace bthbio::chain::contracts
