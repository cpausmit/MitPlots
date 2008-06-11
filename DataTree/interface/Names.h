// $Id: Names.h,v 1.4 2008/06/05 16:03:35 bendavid Exp $

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
      static const char *gkTrackBrn;
      static const char *gkMuonBrn;
      static const char *gkElectronBrn;
  };
}
#endif
