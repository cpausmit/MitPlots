//--------------------------------------------------------------------------------------------------
// $Id: Names.h,v 1.8 2008/06/18 19:08:14 loizides Exp $
//
// Names
//
// This class defines the standard names for branches,
// collections and what else we will standardize.
//
// Authors: C.Loizides, C.Paus
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_NAMES_H
#define DATATREE_NAMES_H
 
#include "MitAna/DataTree/interface/Types.h"

namespace mithep 
{
  class Names 
  {
    public:
      static const char *gkEvtTreeName;
      static const char *gkEvtHeaderBrn;
      static const char *gkGenPartBrn;
      static const char *gkTrackBrn;
      static const char *gkMuonBrn;
      static const char *gkElectronBrn;
      static const char *gkGlobalMuonBrn;

      static const char *gkRunTreeName;
      static const char *gkRunInfoBrn;
  };
}
#endif
