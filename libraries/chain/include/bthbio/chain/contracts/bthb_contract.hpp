/**
 *  @file
 *  @copyright defined in BithumbCoin/LICENSE.txt
 */
#pragma once

#include <bthbio/chain/apply_context.hpp>

#include <bthbio/chain/types.hpp>

namespace bthbio { namespace chain { namespace contracts {

   /**
    * @defgroup native_action_handlers Native Action Handlers
    */
   ///@{
   void apply_bthbio_newaccount(apply_context&);
   void apply_bthbio_updateauth(apply_context&);
   void apply_bthbio_deleteauth(apply_context&);
   void apply_bthbio_linkauth(apply_context&);
   void apply_bthbio_unlinkauth(apply_context&);

   void apply_bthbio_postrecovery(apply_context&);
   void apply_bthbio_passrecovery(apply_context&);
   void apply_bthbio_vetorecovery(apply_context&);

   void apply_bthbio_setcode(apply_context&);
   void apply_bthbio_setabi(apply_context&);

   void apply_bthbio_onerror(apply_context&);

   void apply_bthbio_canceldelay(apply_context&);
   ///@}  end action handlers

} } } /// namespace bthbio::contracts
