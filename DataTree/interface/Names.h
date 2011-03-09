//--------------------------------------------------------------------------------------------------
// $Id: Names.h,v 1.47 2011/02/17 13:44:28 bendavid Exp $
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
 
namespace mithep 
{
  class Names 
  {
    public:
      static const char *gkEvtTreeName;
      static const char *gkBarrelBasicClusterBrn;
      static const char *gkBarrelSuperClusterBrn;
      static const char *gkBeamSpotBrn;
      static const char *gkCaloJetBrn;
      static const char *gkCaloMetBrn;
      static const char *gkCaloTauBrn;
      static const char *gkCaloTowerBrn;
      static const char *gkElectronBrn;
      static const char *gkEndcapBasicClusterBrn;
      static const char *gkEndcapSuperClusterBrn;
      static const char *gkEvtHeaderBrn;
      static const char *gkEvtSelDataBrn;
      static const char *gkGenMetBrn;
      static const char *gkGsfTrackBrn;
      static const char *gkHltBitBrn;
      static const char *gkHltObjBrn;
      static const char *gkGenJetBrn;
      static const char *gkMCEvtInfoBrn;
      static const char *gkMCPartBrn;
      static const char *gkPileupInfoBrn;
      static const char *gkMuonBrn;
      static const char *gkMvfConversionBrn;
      static const char *gkL1TechBitsBrn;
      static const char *gkL1AlgoBitsBrn;
      static const char *gkPFCandidatesBrn;
      static const char *gkPFJetBrn;
      static const char *gkPFTauBrn;
      static const char *gkHPSTauBrn;
      static const char *gkPhotonBrn;
      static const char *gkPixelHitBrn;
      static const char *gkPVBrn;
      static const char *gkPVBeamSpotBrn;
      static const char *gkSC5GenJetBrn;
      static const char *gkSC5JetBrn;
      static const char *gkStripHitBrn;
      static const char *gkTrackBrn;
      static const char *gkTrackJetBrn;
      static const char *gkTrackingParticleBrn;

      static const char *gkRunTreeName;
      static const char *gkRunInfoBrn;

      static const char *gkLATreeName;
      static const char *gkLAHeaderBrn;

      static const char *gkHltTreeName;
      static const char *gkHltTableBrn;
      static const char *gkHltLabelBrn;
      static const char *gkHltMenuBrn;

      static const char *gkAllEvtTreeName;
      static const char *gkAllEvtHeaderBrn;
      static const char *gkSkimmedHeaders;

      static const char *gkBranchTable;
  };
}
#endif
