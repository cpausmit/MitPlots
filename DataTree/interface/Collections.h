//--------------------------------------------------------------------------------------------------
// $Id: Collections.h,v 1.44 2009/03/20 09:37:17 loizides Exp $
//
// Collections
//
// This header file defines the standard types for the collections we want to use.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_COLLECTIONS_H
#define MITANA_DATATREE_COLLECTIONS_H
 
#include "MitAna/DataCont/interface/Collection.h"
#include "MitAna/DataCont/interface/Array.h"
#include "MitAna/DataCont/interface/ObjArray.h"
#include "MitAna/DataCont/interface/Vector.h"
#include "MitAna/DataTree/interface/Types.h"
#include "MitAna/DataTree/interface/DataObject.h"
#include "MitAna/DataTree/interface/EventHeader.h"
#include "MitAna/DataTree/interface/BaseVertex.h"
#include "MitAna/DataTree/interface/Vertex.h"
#include "MitAna/DataTree/interface/BeamSpot.h"
#include "MitAna/DataTree/interface/Track.h"
#include "MitAna/DataTree/interface/BasicCluster.h"
#include "MitAna/DataTree/interface/SuperCluster.h"
#include "MitAna/DataTree/interface/CaloTower.h"
#include "MitAna/DataTree/interface/GenericParticle.h"
#include "MitAna/DataTree/interface/Particle.h"
#include "MitAna/DataTree/interface/ChargedParticle.h"
#include "MitAna/DataTree/interface/Muon.h"
#include "MitAna/DataTree/interface/Electron.h"
#include "MitAna/DataTree/interface/Jet.h"
#include "MitAna/DataTree/interface/CaloJet.h"
#include "MitAna/DataTree/interface/PFJet.h"
#include "MitAna/DataTree/interface/GenJet.h"
#include "MitAna/DataTree/interface/Met.h"
#include "MitAna/DataTree/interface/CaloMet.h"
#include "MitAna/DataTree/interface/PFMet.h"
#include "MitAna/DataTree/interface/TriggerObject.h"
#include "MitAna/DataTree/interface/TriggerMask.h"
#include "MitAna/DataTree/interface/CompositeParticle.h"
#include "MitAna/DataTree/interface/MCParticle.h"
#include "MitAna/DataTree/interface/StableData.h"
#include "MitAna/DataTree/interface/DecayData.h"
#include "MitAna/DataTree/interface/DecayParticle.h"
#include "MitAna/DataTree/interface/Conversion.h"
#include "MitAna/DataTree/interface/Photon.h"
#include "MitAna/DataTree/interface/StableParticle.h"
#include "MitAna/DataTree/interface/PFCandidate.h"
#include "MitAna/DataTree/interface/Tau.h"
#include "MitAna/DataTree/interface/CaloTau.h"
#include "MitAna/DataTree/interface/PFTau.h"

namespace mithep 
{
  typedef Collection<TObject>           ObjectCol;
  typedef Collection<DataBase>          DataBaseCol;
  typedef Collection<DataObject>        DataObjectCol;
  typedef Collection<BaseVertex>        BaseVertexCol;
  typedef Collection<Vertex>            VertexCol;
  typedef Collection<BeamSpot>          BeamSpotCol;
  typedef Collection<EventHeader>       EventHeaderCol;
  typedef Collection<Track>             TrackCol;
  typedef Collection<BasicCluster>      BasicClusterCol;
  typedef Collection<SuperCluster>      SuperClusterCol;
  typedef Collection<CaloTower>         CaloTowerCol;
  typedef Collection<GenericParticle>   GenericParticleCol;
  typedef Collection<Particle>          ParticleCol;
  typedef Collection<ChargedParticle>   ChargedParticleCol;
  typedef Collection<Muon>              MuonCol;
  typedef Collection<Electron>          ElectronCol;
  typedef Collection<Jet>               JetCol;
  typedef Collection<CaloJet>           CaloJetCol;
  typedef Collection<PFJet>             PFJetCol;
  typedef Collection<GenJet>            GenJetCol;
  typedef Collection<Met>               MetCol;
  typedef Collection<CaloMet>           CaloMetCol;
  typedef Collection<PFMet>             PFMetCol;
  typedef Collection<TriggerObjectRel>  TriggerObjectRelCol;
  typedef Collection<TriggerObjectBase> TriggerObjectBaseCol;
  typedef Collection<TriggerObject>     TriggerObjectCol;
  typedef Collection<TriggerMask>       TriggerMaskCol;
  typedef Collection<CompositeParticle> CompositeParticleCol;
  typedef Collection<MCParticle>        MCParticleCol;
  typedef Collection<StableData>        StableDataCol;
  typedef Collection<DecayData>         DecayDataCol;
  typedef Collection<DecayParticle>     DecayParticleCol;
  typedef Collection<Conversion>        ConversionCol;
  typedef Collection<Photon>            PhotonCol;
  typedef Collection<StableParticle>    StableParticleCol;
  typedef Collection<PFCandidate>       PFCandidateCol;
  typedef Collection<Tau>               TauCol;
  typedef Collection<CaloTau>           CaloTauCol;
  typedef Collection<PFTau>             PFTauCol;

  typedef Array<DataBase>               DataBaseArr;
  typedef Array<DataObject>             DataObjectArr;
  typedef Array<BaseVertex>             BaseVertexArr;
  typedef Array<Vertex>                 VertexArr;
  typedef Array<BeamSpot>               BeamSpotArr;
  typedef Array<EventHeader>            EventHeaderArr;
  typedef Array<Track>                  TrackArr;
  typedef Array<BasicCluster>           BasicClusterArr;
  typedef Array<SuperCluster>           SuperClusterArr;
  typedef Array<CaloTower>              CaloTowerArr; 
  typedef Array<ChargedParticle>        ChargedParticleArr;
  typedef Array<Muon>                   MuonArr;
  typedef Array<Electron>               ElectronArr;
  typedef Array<Jet>                    JetArr;
  typedef Array<CaloJet>                CaloJetArr;
  typedef Array<PFJet>                  PFJetArr;
  typedef Array<GenJet>                 GenJetArr;
  typedef Array<Met>                    MetArr;
  typedef Array<CaloMet>                CaloMetArr;
  typedef Array<PFMet>                  PFMetArr;
  typedef Array<TriggerObjectRel>       TriggerObjectRelArr;
  typedef Array<TriggerObjectBase>      TriggerObjectBaseArr;
  typedef Array<TriggerObject>          TriggerObjectArr;
  typedef Array<TriggerMask>            TriggerMaskArr;
  typedef Array<MCParticle>             MCParticleArr;
  typedef Array<CompositeParticle>      CompositeParticleArr;
  typedef Array<StableData>             StableDataArr;
  typedef Array<DecayData>              DecayDataArr;
  typedef Array<DecayParticle>          DecayParticleArr;
  typedef Array<Conversion>             ConversionArr;
  typedef Array<Photon>                 PhotonArr;
  typedef Array<StableParticle>         StableParticleArr;
  typedef Array<PFCandidate>            PFCandidateArr;
  typedef Array<Tau>                    TauArr;
  typedef Array<CaloTau>                CaloTauArr;
  typedef Array<PFTau>                  PFTauArr;

  typedef ObjArray<TObject>             ObjectOArr;
  typedef ObjArray<DataBase>            DataBaseOArr;
  typedef ObjArray<DataObject>          DataObjectOArr;
  typedef ObjArray<BaseVertex>          BaseVertexOArr;
  typedef ObjArray<Vertex>              VertexOArr;
  typedef ObjArray<BeamSpot>            BeamSpotOArr;
  typedef ObjArray<EventHeader>         EventHeaderOArr;
  typedef ObjArray<Track>               TrackOArr;
  typedef ObjArray<BasicCluster>        BasicClusterOArr;
  typedef ObjArray<SuperCluster>        SuperClusterOArr;
  typedef ObjArray<CaloTower>           CaloTowerOArr; 
  typedef ObjArray<GenericParticle>     GenericParticleOArr;
  typedef ObjArray<Particle>            ParticleOArr;
  typedef ObjArray<ChargedParticle>     ChargedParticleOArr;
  typedef ObjArray<Muon>                MuonOArr;
  typedef ObjArray<Electron>            ElectronOArr;
  typedef ObjArray<Jet>                 JetOArr;
  typedef ObjArray<CaloJet>             CaloJetOArr;
  typedef ObjArray<PFJet>               PFJetOArr;
  typedef ObjArray<GenJet>              GenJetOArr;
  typedef ObjArray<Met>                 MetOArr;
  typedef ObjArray<CaloMet>             CaloMetOArr;
  typedef ObjArray<PFMet>               PFMetOArr;
  typedef ObjArray<TriggerObjectRel>    TriggerObjectRelOArr;
  typedef ObjArray<TriggerObjectBase>   TriggerObjectBaseOArr;
  typedef ObjArray<TriggerObject>       TriggerObjectOArr;
  typedef ObjArray<TriggerMask>         TriggerMaskOArr;
  typedef ObjArray<MCParticle>          MCParticleOArr;
  typedef ObjArray<CompositeParticle>   CompositeParticleOArr;
  typedef ObjArray<DecayParticle>       DecayParticleOArr;
  typedef ObjArray<Conversion>          ConversionOArr;
  typedef ObjArray<Photon>              PhotonOArr;
  typedef ObjArray<StableParticle>      StableParticleOArr;
  typedef ObjArray<PFCandidate>         PFCandidateOArr;
  typedef ObjArray<Tau>                 TauOArr;
  typedef ObjArray<CaloTau>             CaloTauOArr;
  typedef ObjArray<PFTau>               PFTauOArr;
}
#endif
