//--------------------------------------------------------------------------------------------------
// $Id: ObjTypes.h,v 1.13 2009/09/25 08:39:10 loizides Exp $
//
// ObjTypes
//
// Here we define an enum for each data class.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_OBJTYPES_H
#define MITANA_DATATREE_OBJTYPES_H
 
namespace mithep
{
  enum EObjType {
    kUnspecified = 0,
    kBaseVertex,
    kBasicCluster,
    kBeamSpot,
    kBranchName,
    kCaloJet,
    kCaloMet,
    kCaloTau,
    kCaloTower,
    kChargedParticle,
    kCompositeParticle,
    kCompoundParticle,
    kConversion,
    kDataBase,
    kDataObject,
    kDaughterData,
    kDecayData,
    kDecayParticle,
    kElectron,
    kEventHeader,
    kGenJet,
    kGenMet,
    kGenericParticle,
    kJet,
    kLAHeader,
    kMCEventInfo,
    kMCParticle,
    kMet,
    kMuon,
    kL1TriggerMask,
    kPair,
    kPFCandidate,
    kPFJet,
    kPFMet,
    kPFTau,
    kParticle,
    kPhoton,
    kPixelHit,
    kRunInfo,
    kStableData,
    kStableDaughter,
    kStableParticle,
    kSuperCluster,
    kTau,
    kTrack,
    kTriggerMask,
    kTriggerName,
    kTriggerObject,
    kTriggerObjectBase,
    kTriggerObjectRel,
    kVertex,
    kUnknown
  };
}
#endif
