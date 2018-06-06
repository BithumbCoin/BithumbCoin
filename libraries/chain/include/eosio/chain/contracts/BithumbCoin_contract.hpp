/**
 *  @file
 *  @copyright defined in BithumbCoin/LICENSE.txt
 */
#pragma once

#include <Bthbio/chain/apply_context.hpp>

#include <Bthbio/chain/types.hpp>

namespace Bthbio { namespace chain { namespace contracts {

   /**
    * @defgroup native_action_handlers Native Action Handlers
    */
   ///@{
   void apply_BithumbCoinio_newaccount(apply_context&);
   void apply_BithumbCoinio_updateauth(apply_context&);
   void apply_BithumbCoinio_deleteauth(apply_context&);
   void apply_BithumbCoinio_linkauth(apply_context&);
   void apply_BithumbCoinio_unlinkauth(apply_context&);

   void apply_BithumbCoinio_postrecovery(apply_context&);
   void apply_BithumbCoinio_passrecovery(apply_context&);
   void apply_BithumbCoinio_vetorecovery(apply_context&);

   void apply_BithumbCoinio_setcode(apply_context&);
   void apply_BithumbCoinio_setabi(apply_context&);

   void apply_BithumbCoinio_onerror(apply_context&);

   void apply_BithumbCoinio_canceldelay(apply_context&);
   ///@}  end action handlers

} } } /// namespace BithumbCoinio::contracts
