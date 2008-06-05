// $Id: Names.h,v 1.2 2008/06/03 09:51:21 loizides Exp $

#ifndef DATATREE_NAMES_H
#define DATATREE_NAMES_H
 
#include "MitAna/DataTree/interface/Types.h"

//--------------------------------------------------------------------------------------------------
//
// Names
//
// This class defines the standard names for branches,
// collections and what else we will standardize.
//
// Authors: C.Loizides
//
//--------------------------------------------------------------------------------------------------

namespace mithep 
{
  class Names 
  {
    public:
      static const char *gkMitTreeName;
      static const char *gkGenPartBrn;
      static const char *gkMuonBrn;
  };

} /*namespace mithep*/

#endif /*DATATREE_NAMES_H*/
