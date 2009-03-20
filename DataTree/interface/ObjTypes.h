//--------------------------------------------------------------------------------------------------
// $Id: ObjTypes.h,v 1.6 2009/03/19 23:09:36 bendavid Exp $
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
    kConversion,
    kDataBase,
    kDataObject,
    kDaughterData,
    kDecayData,
    kDecayParticle,
    kElectron,
    kEventHeader,
    kGenJet,
    kJet,
    kLAHeader,
    kMCEventInfo,
    kMCParticle,
    kMet,
    kMuon,
    kPFCandidate,
    kPFJet,
    kPFMet,
    kPFTau,
    kParticle,
    kPhoton,
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
    kTriggerObjectRef,
    kVertex,
    kUnknown
  };
}
#endif
