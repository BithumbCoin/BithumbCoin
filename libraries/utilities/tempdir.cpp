/**
 *  @file
 *  @copyright defined in BithumbCoin/LICENSE.txt
 */

#include <BithumbCoinio/utilities/tempdir.hpp>

#include <cstdlib>

namespace BithumbCoinio { namespace utilities {

fc::path temp_directory_path()
{
   const char* BithumbCoin_tempdir = getenv("BithumbCoin_TEMPDIR");
   if( BithumbCoin_tempdir != nullptr )
      return fc::path( BithumbCoin_tempdir );
   return fc::temp_directory_path() / "BithumbCoin-tmp";
}

} } // BithumbCoinio::utilities
