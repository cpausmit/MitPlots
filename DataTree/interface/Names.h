//--------------------------------------------------------------------------------------------------
// $Id: Names.h,v 1.13 2008/07/25 11:32:45 bendavid Exp $
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
      static const char *gkMCPartBrn;
      static const char *gkTrackBrn;
      static const char *gkBarrelBasicClusterBrn;
      static const char *gkBarrelSuperClusterBrn;
      static const char *gkEndcapBasicClusterBrn;
      static const char *gkEndcapSuperClusterBrn;
      static const char *gkMuonBrn;
      static const char *gkElectronBrn;
      static const char *gkCaloJetBrn;
      static const char *gkCaloMetBrn;
      static const char *gkSimPartBrn;
      static const char *gkPhotonBrn;

      static const char *gkRunTreeName;
      static const char *gkRunInfoBrn;

      static const char *gkLATreeName;
      static const char *gkLAHeaderBrn;
  };
}
#endif
