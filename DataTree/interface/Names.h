//--------------------------------------------------------------------------------------------------
// $Id: Names.h,v 1.20 2008/10/06 15:54:41 ceballos Exp $
//
// Names
//
// This class defines the standard names for branches,
// collections and what else we will standardize.
//
// Authors: C.Loizides, C.Paus
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_NAMES_H
#define MITANA_DATATREE_NAMES_H
 
#include "MitAna/DataTree/interface/Types.h"

namespace mithep 
{
  class Names 
  {
    public:
      static const char *gkEvtTreeName;
      static const char *gkEvtHeaderBrn;
      static const char *gkL1BitBrn;
      static const char *gkL1ObjBrn;
      static const char *gkHltBitBrn;
      static const char *gkHltObjBrn;
      static const char *gkMCEvtInfoBrn;
      static const char *gkTrackBrn;
      static const char *gkBarrelBasicClusterBrn;
      static const char *gkBarrelSuperClusterBrn;
      static const char *gkEndcapBasicClusterBrn;
      static const char *gkEndcapSuperClusterBrn;
      static const char *gkCaloTowerBrn;
      static const char *gkMuonBrn;
      static const char *gkElectronBrn;
      static const char *gkCaloJetBrn;
      static const char *gkSC5JetBrn;
      static const char *gkCaloMetBrn;
      static const char *gkMCPartBrn;
      static const char *gkPhotonBrn;

      static const char *gkRunTreeName;
      static const char *gkRunInfoBrn;

      static const char *gkLATreeName;
      static const char *gkLAHeaderBrn;

      static const char *gkHltTreeName;
      static const char *gkHltTableBrn;
      static const char *gkHltLabelBrn;

      static const char *gkL1TreeName;
      static const char *gkL1TableBrn;

      static const char *gkGoodElectronsName;
      static const char *gkGoodMuonsName;
      static const char *gkGoodPhotonsName;
      static const char *gkGoodTausName;
      static const char *gkGoodJetsName;
      static const char *gkCleanElectronsName;
      static const char *gkCleanMuonsName;
      static const char *gkCleanPhotonsName;
      static const char *gkCleanTausName;
      static const char *gkCleanJetsName;
      static const char *gkCleanFwdJetsName;
      static const char *gkCleanNoFwdJetsName;
      static const char *gkMCLeptonsName;
      static const char *gkMCAllLeptonsName;
      static const char *gkMCTausName;
      static const char *gkMCNeutrinosName;
      static const char *gkMCQuarksName;
      static const char *gkMCqqHsName;
      static const char *gkMCBosonsName;

  };
}
#endif
