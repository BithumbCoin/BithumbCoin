/**
 *  @file
 *  @copyright defined in BithumbCoin/LICENSE.txt
 */
#pragma once
#include <fc/exception/exception.hpp>
#include <bthbio/chain/types.hpp>
#include <bthbio/chain/symbol.hpp>

/// BithumbCoin with 8 digits of precision
#define BTHB_SYMBOL_VALUE  (int64_t(4) | (uint64_t('E') << 8) | (uint64_t('O') << 16) | (uint64_t('S') << 24))
static const bthbio::chain::symbol BTHB_SYMBOL(BTHB_SYMBOL_VALUE);

/// Defined to be largest power of 10 that fits in 53 bits of precision
#define BTHB_MAX_SHARE_SUPPLY   int64_t(1'000'000'000'000'000ll)

namespace bthbio { namespace chain {

/**

asset includes amount and currency symbol

asset::from_string takes a string of the form "10.0000 CUR" and constructs an asset 
with amount = 10 and symbol(4,"CUR")

*/


struct asset
{
   explicit asset(share_type a = 0, symbol id = BTHB_SYMBOL)
      :amount(a), sym(id){}

   share_type amount;
   symbol     sym;

   double to_real()const { return static_cast<double>(amount) / precision(); }

   uint8_t     decimals()const;
   string      symbol_name()const;
   int64_t     precision()const;
   const symbol& get_symbol() const { return sym; }

   static asset from_string(const string& from);
   string       to_string()const;

   asset& operator += (const asset& o)
   {
      FC_ASSERT(get_symbol() == o.get_symbol());
      amount += o.amount;
      return *this;
   }

   asset& operator -= (const asset& o)
   {
      FC_ASSERT(get_symbol() == o.get_symbol());
      amount -= o.amount;
      return *this;
   }
   asset operator -()const { return asset(-amount, get_symbol()); }

   friend bool operator == (const asset& a, const asset& b)
   {
      return std::tie(a.get_symbol(), a.amount) == std::tie(b.get_symbol(), b.amount);
   }
   friend bool operator < (const asset& a, const asset& b)
   {
      FC_ASSERT(a.get_symbol() == b.get_symbol());
      return std::tie(a.amount,a.get_symbol()) < std::tie(b.amount,b.get_symbol());
   }
   friend bool operator <= (const asset& a, const asset& b) { return (a == b) || (a < b); }
   friend bool operator != (const asset& a, const asset& b) { return !(a == b); }
   friend bool operator > (const asset& a, const asset& b)  { return !(a <= b); }
   friend bool operator >= (const asset& a, const asset& b) { return !(a < b);  }

   friend asset operator - (const asset& a, const asset& b) {
      FC_ASSERT(a.get_symbol() == b.get_symbol());
      return asset(a.amount - b.amount, a.get_symbol());
   }

   friend asset operator + (const asset& a, const asset& b) {
      FC_ASSERT(a.get_symbol() == b.get_symbol());
      return asset(a.amount + b.amount, a.get_symbol());
   }

   friend std::ostream& operator << (std::ostream& out, const asset& a) { return out << a.to_string(); }

};

struct extended_asset  {
  extended_asset(){}
  extended_asset( asset a, name n ):quantity(a),contract(n){}
  asset quantity;
  name contract;
};

bool  operator <  (const asset& a, const asset& b);
bool  operator <= (const asset& a, const asset& b);

}} // namespace bthbio::chain

namespace fc {
inline void to_variant(const bthbio::chain::asset& var, fc::variant& vo) { vo = var.to_string(); }
inline void from_variant(const fc::variant& var, bthbio::chain::asset& vo) {
   vo = bthbio::chain::asset::from_string(var.get_string());
}
}

FC_REFLECT(bthbio::chain::asset, (amount)(sym))
FC_REFLECT(bthbio::chain::extended_asset, (quantity)(contract) )
