// $Id: Names.cc,v 1.37 2009/09/25 08:39:11 loizides Exp $

#include "MitAna/DataTree/interface/Names.h"

using namespace mithep;

//--------------------------------------------------------------------------------------------------

const char *Names::gkEvtTreeName            = "Events";
const char *Names::gkBarrelBasicClusterBrn  = "BarrelBasicClusters";
const char *Names::gkBarrelSuperClusterBrn  = "BarrelSuperClusters";
const char *Names::gkCaloJetBrn             = "ItrCone5Jets";
const char *Names::gkCaloMetBrn             = "CorMuonMet";
const char *Names::gkCaloTauBrn             = "CaloTaus";
const char *Names::gkCaloTowerBrn           = "CaloTowers";
const char *Names::gkElectronBrn            = "Electrons";
const char *Names::gkEndcapBasicClusterBrn  = "EndcapBasicClusters";
const char *Names::gkEndcapSuperClusterBrn  = "EndcapSuperClusters";
const char *Names::gkEvtHeaderBrn           = "EventHeader";
const char *Names::gkGenMetBrn              = "GenMet";
const char *Names::gkGsfTrackBrn            = "GsfTracks";
const char *Names::gkHltBitBrn              = "HLTBits";
const char *Names::gkHltObjBrn              = "HLTObjects";
const char *Names::gkIC5GenJetBrn           = "IC5GenJets";
const char *Names::gkMCEvtInfoBrn           = "MCEventInfo";
const char *Names::gkMCPartBrn              = "MCParticles";
const char *Names::gkMuonBrn                = "Muons";
const char *Names::gkMvfConversionBrn       = "MvfConversions";
const char *Names::gkL1TechBitsBrn          = "L1TechBits";
const char *Names::gkL1AlgoBitsBrn          = "L1AlgoBits";
const char *Names::gkPFCandidatesBrn        = "PFCandidates";
const char *Names::gkPFTauBrn               = "PFTaus";
const char *Names::gkPhotonBrn              = "Photons";
const char *Names::gkPixelHitBrn            = "PixelHits";
const char *Names::gkPVBeamSpotBrn          = "PrimaryVertexesBeamSpot";
const char *Names::gkSC5GenJetBrn           = "SC5GenJets";
const char *Names::gkSC5JetBrn              = "SisCone5Jets";
const char *Names::gkTrackBrn               = "Tracks";

const char *Names::gkRunTreeName            = "Runs";
const char *Names::gkRunInfoBrn             = "RunInfo";

const char *Names::gkLATreeName             = "FWMetaData";
const char *Names::gkLAHeaderBrn            = "LAHeader";

const char *Names::gkHltTreeName            = "HLT";
const char *Names::gkHltTableBrn            = "HLTTriggerTable";
const char *Names::gkHltLabelBrn            = "HLTLabels";

const char *Names::gkAllEvtTreeName         = "AllEvents";
const char *Names::gkAllEvtHeaderBrn        = "EventHeader";
const char *Names::gkSkimmedHeaders         = "SkimmedHeaders";

const char *Names::gkBranchTable            = "BranchTable";
