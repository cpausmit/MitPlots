//--------------------------------------------------------------------------------------------------
// $Id: Collections.h,v 1.34 2009/02/18 15:38:54 loizides Exp $
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
#include "MitAna/DataCont/interface/RefArray.h"
#include "MitAna/DataCont/interface/StackArray.h"
#include "MitAna/DataCont/interface/Vector.h"
#include "MitAna/DataTree/interface/Types.h"
#include "MitAna/DataTree/interface/DataObject.h"
#include "MitAna/DataTree/interface/Track.h"
#include "MitAna/DataTree/interface/BasicCluster.h"
#include "MitAna/DataTree/interface/SuperCluster.h"
#include "MitAna/DataTree/interface/CaloTower.h"
#include "MitAna/DataTree/interface/Particle.h"
#include "MitAna/DataTree/interface/ChargedParticle.h"
#include "MitAna/DataTree/interface/Muon.h"
#include "MitAna/DataTree/interface/Electron.h"
#include "MitAna/DataTree/interface/Jet.h"
#include "MitAna/DataTree/interface/GenJet.h"
#include "MitAna/DataTree/interface/Met.h"
#include "MitAna/DataTree/interface/TriggerObject.h"
#include "MitAna/DataTree/interface/CompositeParticle.h"
#include "MitAna/DataTree/interface/MCParticle.h"
#include "MitAna/DataTree/interface/StableData.h"
#include "MitAna/DataTree/interface/DecayData.h"
#include "MitAna/DataTree/interface/DecayParticle.h"
#include "MitAna/DataTree/interface/Conversion.h"
#include "MitAna/DataTree/interface/Photon.h"
#include "MitAna/DataTree/interface/StableParticle.h"
#include "MitAna/DataTree/interface/BaseVertex.h"
#include "MitAna/DataTree/interface/Vertex.h"
#include "MitAna/DataTree/interface/BeamSpot.h"

namespace mithep 
{
  typedef Collection<TObject>           ObjectCol;
  typedef Collection<DataBase>          DataBaseCol;

  typedef Collection<BitMask<1> >       BitMask8Col;
  typedef Collection<BitMask<2> >       BitMask16Col;
  typedef Collection<BitMask<4> >       BitMask32Col;
  typedef Collection<BitMask<6> >       BitMask48Col;
  typedef Collection<BitMask<8> >       BitMask64Col;
  typedef Collection<BitMask<16> >      BitMask128Col;
  typedef Collection<BitMask<32> >      BitMask256Col;

  typedef Vector<BitMask<1> >           BitMask8Vec;
  typedef Vector<BitMask<2> >           BitMask16Vec;
  typedef Vector<BitMask<4> >           BitMask32Vec;
  typedef Vector<BitMask<6> >           BitMask48Vec;
  typedef Vector<BitMask<8> >           BitMask64Vec;
  typedef Vector<BitMask<16> >          BitMask128Vec;
  typedef Vector<BitMask<32> >          BitMask256Vec;

  typedef Collection<DataObject>        DataObjectCol;
  typedef Collection<Track>             TrackCol;
  typedef Collection<BasicCluster>      BasicClusterCol;
  typedef Collection<SuperCluster>      SuperClusterCol;
  typedef Collection<CaloTower>         CaloTowerCol;
  typedef Collection<Particle>          ParticleCol;
  typedef Collection<ChargedParticle>   ChargedParticleCol;
  typedef Collection<Muon>              MuonCol;
  typedef Collection<Electron>          ElectronCol;
  typedef Collection<Jet>               JetCol;
  typedef Collection<GenJet>            GenJetCol;
  typedef Collection<Met>               MetCol;
  typedef Collection<TriggerObjectRel>  TriggerObjectRelCol;
  typedef Collection<TriggerObjectBase> TriggerObjectBaseCol;
  typedef Collection<TriggerObject>     TriggerObjectCol;
  typedef Collection<CompositeParticle> CompositeParticleCol;
  typedef Collection<MCParticle>        MCParticleCol;
  typedef Collection<StableData>        StableDataCol;
  typedef Collection<DecayData>         DecayDataCol;
  typedef Collection<DecayParticle>     DecayParticleCol;
  typedef Collection<Conversion>        ConversionCol;
  typedef Collection<Photon>            PhotonCol;
  typedef Collection<StableParticle>    StableParticleCol;
  typedef Collection<BaseVertex>        BaseVertexCol;
  typedef Collection<Vertex>            VertexCol;
  typedef Collection<BeamSpot>          BeamSpotCol;

  typedef Array<DataBase>               DataBaseArr;
  typedef Array<DataObject>             DataObjectArr;
  typedef Array<Track>                  TrackArr;
  typedef Array<BasicCluster>           BasicClusterArr;
  typedef Array<SuperCluster>           SuperClusterArr;
  typedef Array<CaloTower>              CaloTowerArr; 
  typedef Array<ChargedParticle>        ChargedParticleArr;
  typedef Array<Muon>                   MuonArr;
  typedef Array<Electron>               ElectronArr;
  typedef Array<Jet>                    JetArr;
  typedef Array<GenJet>                 GenJetArr;
  typedef Array<Met>                    MetArr;
  typedef Array<TriggerObjectRel>       TriggerObjectRelArr;
  typedef Array<TriggerObjectBase>      TriggerObjectBaseArr;
  typedef Array<TriggerObject>          TriggerObjectArr;
  typedef Array<MCParticle>             MCParticleArr;
  typedef Array<CompositeParticle>      CompositeParticleArr;
  typedef Array<StableData>             StableDataArr;
  typedef Array<DecayData>              DecayDataArr;
  typedef Array<DecayParticle>          DecayParticleArr;
  typedef Array<Conversion>             ConversionArr;
  typedef Array<Photon>                 PhotonArr;
  typedef Array<StableParticle>         StableParticleArr;
  typedef Array<BaseVertex>             BaseVertexArr;
  typedef Array<Vertex>                 VertexArr;
  typedef Array<BeamSpot>               BeamSpotArr;

  typedef ObjArray<TObject>             ObjectOArr;
  typedef ObjArray<DataBase>            DataBaseOArr;
  typedef ObjArray<DataObject>          DataObjectOArr;
  typedef ObjArray<Track>               TrackOArr;
  typedef ObjArray<BasicCluster>        BasicClusterOArr;
  typedef ObjArray<SuperCluster>        SuperClusterOArr;
  typedef ObjArray<CaloTower>           CaloTowerOArr; 
  typedef ObjArray<Particle>            ParticleOArr;
  typedef ObjArray<ChargedParticle>     ChargedParticleOArr;
  typedef ObjArray<Muon>                MuonOArr;
  typedef ObjArray<Electron>            ElectronOArr;
  typedef ObjArray<Jet>                 JetOArr;
  typedef ObjArray<GenJet>              GenJetOArr;
  typedef ObjArray<Met>                 MetOArr;
  typedef ObjArray<TriggerObjectRel>    TriggerObjectRelOArr;
  typedef ObjArray<TriggerObjectBase>   TriggerObjectBaseOArr;
  typedef ObjArray<TriggerObject>       TriggerObjectOArr;
  typedef ObjArray<MCParticle>          MCParticleOArr;
  typedef ObjArray<CompositeParticle>   CompositeParticleOArr;
  typedef ObjArray<DecayParticle>       DecayParticleOArr;
  typedef ObjArray<Conversion>          ConversionOArr;
  typedef ObjArray<Photon>              PhotonOArr;
  typedef ObjArray<StableParticle>      StableParticleOArr;
  typedef ObjArray<BaseVertex>          BaseVertexOArr;
  typedef ObjArray<Vertex>              VertexOArr;
  typedef ObjArray<BeamSpot>            BeamSpotOArr;


  typedef Collection<std::string>     StringCol;
  typedef Vector<std::string> StringVec;

}
#endif
