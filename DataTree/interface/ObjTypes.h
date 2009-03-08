//--------------------------------------------------------------------------------------------------
// $Id: ObjTypes.h,v 1.1 2008/12/09 17:40:36 loizides Exp $
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
    kParticle,
    kPhoton,
    kRunInfo,
    kStableData,
    kStableDaughter,
    kStableParticle,
    kSuperCluster,
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
