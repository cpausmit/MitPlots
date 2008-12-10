// $Id: MitAnaDataTreeLinkDef.h,v 1.47 2008/12/09 17:47:11 loizides Exp $

#ifndef MITANA_DATATREE_LINKDEF_H
#define MITANA_DATATREE_LINKDEF_H

#include <string>
#include <vector>

#include "MitAna/DataTree/interface/Types.h"
#include "MitAna/DataTree/interface/ObjTypes.h"
#include "MitAna/DataTree/interface/Names.h"
#include "MitAna/DataTree/interface/Collections.h"

#include "MitAna/DataTree/interface/DataBase.h"
#include "MitAna/DataTree/interface/BitMask.h"
#include "MitAna/DataTree/interface/EventHeader.h"
#include "MitAna/DataTree/interface/LAHeader.h"
#include "MitAna/DataTree/interface/TriggerName.h"
#include "MitAna/DataTree/interface/RunInfo.h"
#include "MitAna/DataTree/interface/MCEventInfo.h"

#include "MitAna/DataTree/interface/DataObject.h"
#include "MitAna/DataTree/interface/BaseVertex.h"
#include "MitAna/DataTree/interface/Vertex.h"
#include "MitAna/DataTree/interface/BeamSpot.h"
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
#include "MitAna/DataTree/interface/MCParticle.h"
#include "MitAna/DataTree/interface/CompositeParticle.h"
#include "MitAna/DataTree/interface/DaughterData.h"
#include "MitAna/DataTree/interface/StableData.h"
#include "MitAna/DataTree/interface/DecayData.h"
#include "MitAna/DataTree/interface/DecayParticle.h"
#include "MitAna/DataTree/interface/Conversion.h"
#include "MitAna/DataTree/interface/Photon.h"
#include "MitAna/DataTree/interface/StableParticle.h"
#include "MitAna/DataTree/interface/StableDaughter.h"
#endif

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::Names+;

#pragma link C++ class mithep::Collection<TRef>+;
#pragma link C++ class mithep::Collection<std::string>+; //todo  remove for Mit_008
#pragma link C++ typedef mithep::StringCol;              //todo  remove for Mit_008
#pragma link C++ class mithep::Vector<std::string>+;     //todo  remove for Mit_008
#pragma link C++ typedef mithep::StringVec;              //todo  remove for Mit_008

#pragma link C++ class mithep::DataBase+;
#pragma link C++ enum mithep::EObjType;

#pragma link C++ class mithep::BitMask<1>+;
#pragma link C++ class mithep::BitMask<2>+;
#pragma link C++ class mithep::BitMask<4>+;
#pragma link C++ class mithep::BitMask<6>+;
#pragma link C++ class mithep::BitMask<8>+;
#pragma link C++ class mithep::BitMask<16>+;
#pragma link C++ class mithep::BitMask<32>+;
#pragma link C++ typedef mithep::BitMask8;
#pragma link C++ typedef mithep::BitMask16;
#pragma link C++ typedef mithep::BitMask32;
#pragma link C++ typedef mithep::BitMask48;
#pragma link C++ typedef mithep::BitMask64;
#pragma link C++ typedef mithep::BitMask128;
#pragma link C++ typedef mithep::BitMask256;
#pragma link C++ class mithep::Collection<mithep::BitMask<1> >+;
#pragma link C++ class mithep::Vector<mithep::BitMask<1> >+;
#pragma link C++ typedef mithep::BitMask8Col;
#pragma link C++ typedef mithep::BitMask8Vec;
#pragma link C++ class mithep::Collection<mithep::BitMask<2> >+;
#pragma link C++ class mithep::Vector<mithep::BitMask<2> >+;
#pragma link C++ typedef mithep::BitMask16Col;
#pragma link C++ typedef mithep::BitMask16Vec;
#pragma link C++ class mithep::Collection<mithep::BitMask<4> >+;
#pragma link C++ class mithep::Vector<mithep::BitMask<4> >+;
#pragma link C++ typedef mithep::BitMask32Col;
#pragma link C++ typedef mithep::BitMask32Vec;
#pragma link C++ class mithep::Collection<mithep::BitMask<6> >+;
#pragma link C++ class mithep::Vector<mithep::BitMask<6> >+;
#pragma link C++ typedef mithep::BitMask48Col;
#pragma link C++ typedef mithep::BitMask48Vec;
#pragma link C++ class mithep::Collection<mithep::BitMask<8> >+;
#pragma link C++ class mithep::Vector<mithep::BitMask<8> >+;
#pragma link C++ typedef mithep::BitMask64Col;
#pragma link C++ typedef mithep::BitMask64Vec;
#pragma link C++ class mithep::Collection<mithep::BitMask<16> >+;
#pragma link C++ class mithep::Vector<mithep::BitMask<16> >+;
#pragma link C++ typedef mithep::BitMask128Col;
#pragma link C++ typedef mithep::BitMask128Vec;
#pragma link C++ class mithep::Collection<mithep::BitMask<32> >+;
#pragma link C++ class mithep::Vector<mithep::BitMask<32> >+;
#pragma link C++ typedef mithep::BitMask256Col;
#pragma link C++ typedef mithep::BitMask256Vec;

#pragma link C++ class mithep::EventHeader+;
#pragma link C++ class mithep::LAHeader+;
#pragma link C++ class mithep::TriggerName+;
#pragma link C++ class mithep::RunInfo+;
#pragma link C++ class mithep::MCEventInfo+;

#pragma link C++ class mithep::DataObject+;
#pragma link C++ class mithep::Collection<mithep::DataObject>+;
#pragma link C++ class mithep::Array<mithep::DataObject>+;
#pragma link C++ class mithep::ObjArray<mithep::DataObject>+;
#pragma link C++ typedef mithep::DataObjectCol;
#pragma link C++ typedef mithep::DataObjectArr;
#pragma link C++ typedef mithep::DataObjectOArr;

#pragma link C++ class mithep::BaseVertex+;
#pragma link C++ class mithep::Collection<mithep::BaseVertex>+;
#pragma link C++ class mithep::Array<mithep::BaseVertex>+;
#pragma link C++ class mithep::ObjArray<mithep::BaseVertex>+;
#pragma link C++ typedef mithep::BaseVertexCol;
#pragma link C++ typedef mithep::BaseVertexArr;

#pragma link C++ class mithep::Vertex+;
#pragma link C++ class mithep::Collection<mithep::Vertex>+;
#pragma link C++ class mithep::Array<mithep::Vertex>+;
#pragma link C++ class mithep::ObjArray<mithep::Vertex>+;
#pragma link C++ typedef mithep::VertexCol;
#pragma link C++ typedef mithep::VertexArr;

#pragma link C++ class mithep::BeamSpot+;
#pragma link C++ class mithep::Collection<mithep::BeamSpot>+;
#pragma link C++ class mithep::Array<mithep::BeamSpot>+;
#pragma link C++ class mithep::ObjArray<mithep::BeamSpot>+;
#pragma link C++ typedef mithep::BeamSpotCol;
#pragma link C++ typedef mithep::BeamSpotArr;

#pragma link C++ class mithep::Collection<mithep::BitMask256>+;
#pragma link C++ class mithep::Vector<mithep::BitMask256>+;

#pragma link C++ class mithep::Track+;
#pragma link C++ class mithep::Collection<mithep::Track>+;
#pragma link C++ class mithep::Array<mithep::Track>+;
#pragma link C++ class mithep::ObjArray<mithep::Track>+;
#pragma link C++ typedef mithep::TrackCol;
#pragma link C++ typedef mithep::TrackArr;
#pragma link C++ typedef mithep::TrackOArr;
#pragma link C++ enum mithep::Track::EHitLayer;

#pragma link C++ class mithep::BasicCluster+;
#pragma link C++ class mithep::Collection<mithep::BasicCluster>+;
#pragma link C++ class mithep::Array<mithep::BasicCluster>+;
#pragma link C++ class mithep::ObjArray<mithep::BasicCluster>+;
#pragma link C++ class mithep::RefArray<mithep::BasicCluster,1024>+;
#pragma link C++ typedef mithep::BasicClusterCol;
#pragma link C++ typedef mithep::BasicClusterArr;
#pragma link C++ typedef mithep::BasicClusterOArr;

#pragma link C++ class mithep::SuperCluster+;
#pragma link C++ class mithep::Collection<mithep::SuperCluster>+;
#pragma link C++ class mithep::Array<mithep::SuperCluster>+;
#pragma link C++ class mithep::ObjArray<mithep::SuperCluster>+;
#pragma link C++ typedef mithep::SuperClusterCol;
#pragma link C++ typedef mithep::SuperClusterArr;
#pragma link C++ typedef mithep::SuperClusterOArr;

#pragma link C++ class mithep::CaloTower+;
#pragma link C++ class mithep::Collection<mithep::CaloTower>+;
#pragma link C++ class mithep::Array<mithep::CaloTower>+;
#pragma link C++ class mithep::ObjArray<mithep::CaloTower>+;
#pragma link C++ class mithep::RefArray<mithep::CaloTower,1024>+;
#pragma link C++ typedef mithep::CaloTowerCol;
#pragma link C++ typedef mithep::CaloTowerArr;
#pragma link C++ typedef mithep::CaloTowerOArr;

#pragma link C++ class mithep::Particle+;
#pragma link C++ class mithep::Collection<mithep::Particle>+;
#pragma link C++ class mithep::RefArray<mithep::Particle,1024>+;
#pragma link C++ class mithep::ObjArray<mithep::Particle>+;
#pragma link C++ typedef mithep::ParticleCol;
#pragma link C++ typedef mithep::ParticleOArr;

#pragma link C++ class mithep::ChargedParticle+;
#pragma link C++ class mithep::Collection<mithep::ChargedParticle>+;
#pragma link C++ class mithep::ObjArray<mithep::ChargedParticle>+;
#pragma link C++ typedef mithep::ChargedParticleCol;
#pragma link C++ typedef mithep::ChargedParticleArr;
#pragma link C++ typedef mithep::ChargedParticleOArr;

#pragma link C++ class mithep::Muon+;
#pragma link C++ enum mithep::Muon::EClassType;
#pragma link C++ class mithep::Collection<mithep::Muon>+;
#pragma link C++ class mithep::Array<mithep::Muon>+;
#pragma link C++ class mithep::ObjArray<mithep::Muon>+;
#pragma link C++ typedef mithep::MuonCol;
#pragma link C++ typedef mithep::MuonArr;
#pragma link C++ typedef mithep::MuonOArr;

#pragma link C++ class mithep::Electron+;
#pragma link C++ class mithep::Collection<mithep::Electron>+;
#pragma link C++ class mithep::Array<mithep::Electron>+;
#pragma link C++ class mithep::ObjArray<mithep::Electron>+;
#pragma link C++ typedef mithep::ElectronCol;
#pragma link C++ typedef mithep::ElectronArr;
#pragma link C++ typedef mithep::ElectronOArr;

#pragma link C++ class mithep::Jet+;
#pragma link C++ class mithep::Collection<mithep::Jet>+;
#pragma link C++ class mithep::Array<mithep::Jet>+;
#pragma link C++ class mithep::ObjArray<mithep::Jet>+;
#pragma link C++ typedef mithep::JetCol;
#pragma link C++ typedef mithep::JetArr;
#pragma link C++ typedef mithep::JetOArr;

#pragma link C++ class mithep::GenJet+;
#pragma link C++ class mithep::Collection<mithep::GenJet>+;
#pragma link C++ class mithep::Array<mithep::GenJet>+;
#pragma link C++ class mithep::ObjArray<mithep::GenJet>+;
#pragma link C++ typedef mithep::GenJetCol;
#pragma link C++ typedef mithep::GenJetArr;
#pragma link C++ typedef mithep::GenJetOArr;

#pragma link C++ class mithep::Met+;
#pragma link C++ class mithep::Collection<mithep::Met>+;
#pragma link C++ class mithep::Array<mithep::Met>+;
#pragma link C++ class mithep::ObjArray<mithep::Met>+;
#pragma link C++ typedef mithep::MetCol;
#pragma link C++ typedef mithep::MetArr;
#pragma link C++ typedef mithep::MetOArr;

#pragma link C++ class mithep::TriggerObjectRel+;
#pragma link C++ class mithep::Collection<mithep::TriggerObjectRel>+;
#pragma link C++ class mithep::Array<mithep::TriggerObjectRel>+;
#pragma link C++ typedef mithep::TriggerObjectRelCol;
#pragma link C++ typedef mithep::TriggerObjectRelArr;
#pragma link C++ typedef mithep::TriggerObjectRelOArr;

#pragma link C++ class mithep::TriggerObjectBase+;
#pragma link C++ class mithep::Collection<mithep::TriggerObjectBase>+;
#pragma link C++ class mithep::Array<mithep::TriggerObjectBase>+;
#pragma link C++ typedef mithep::TriggerObjectBaseCol;
#pragma link C++ typedef mithep::TriggerObjectBaseArr;
#pragma link C++ typedef mithep::TriggerObjectBaseOArr;

#pragma link C++ class mithep::TriggerObject+;
#pragma link C++ class mithep::Collection<mithep::TriggerObject>+;
#pragma link C++ class mithep::Array<mithep::TriggerObject>+;
#pragma link C++ class mithep::ObjArray<mithep::TriggerObject>+;
#pragma link C++ typedef mithep::TriggerObjectCol;
#pragma link C++ typedef mithep::TriggerObjectArr;
#pragma link C++ typedef mithep::TriggerObjectOArr;
#pragma link C++ enum mithep::TriggerObject::ETriggerObject;

#pragma link C++ class mithep::CompositeParticle+;
#pragma link C++ class mithep::Collection<mithep::CompositeParticle>+;
#pragma link C++ class mithep::Array<mithep::CompositeParticle>+;
#pragma link C++ class mithep::ObjArray<mithep::CompositeParticle>+;
#pragma link C++ typedef mithep::CompositeParticleCol;
#pragma link C++ typedef mithep::CompositeParticleArr;
#pragma link C++ typedef mithep::CompositeParticleOArr;

#pragma link C++ class mithep::MCParticle+;
#pragma link C++ class mithep::Collection<mithep::MCParticle>+;
#pragma link C++ class mithep::Array<mithep::MCParticle>+;
#pragma link C++ class mithep::ObjArray<mithep::MCParticle>+;
#pragma link C++ typedef mithep::MCParticleCol;
#pragma link C++ typedef mithep::MCParticleArr;
#pragma link C++ typedef mithep::MCParticleOArr;
#pragma link C++ enum mithep::MCParticle::EPartType;

#pragma link C++ class mithep::DaughterData+;
#pragma link C++ class mithep::Collection<mithep::DaughterData>+;
#pragma link C++ class mithep::RefArray<mithep::DaughterData,32>+;

#pragma link C++ class mithep::StableData+;
#pragma link C++ class mithep::Collection<mithep::StableData>+;
#pragma link C++ class mithep::Array<mithep::StableData>+;
#pragma link C++ typedef mithep::StableDataCol;
#pragma link C++ typedef mithep::StableDataArr;

#pragma link C++ class mithep::DecayData+;
#pragma link C++ class mithep::Collection<mithep::DecayData>+;
#pragma link C++ class mithep::Array<mithep::DecayData>+;
#pragma link C++ typedef mithep::DecayDataCol;
#pragma link C++ typedef mithep::DecayDataArr;

#pragma link C++ class mithep::DecayParticle+;
#pragma link C++ class mithep::Collection<mithep::DecayParticle>+;
#pragma link C++ class mithep::Array<mithep::DecayParticle>+;
#pragma link C++ class mithep::ObjArray<mithep::DecayParticle>+;
#pragma link C++ typedef mithep::DecayParticleCol;
#pragma link C++ typedef mithep::DecayParticleArr;
#pragma link C++ typedef mithep::DecayParticleOArr;

#pragma link C++ class mithep::Conversion+;
#pragma link C++ class mithep::Collection<mithep::Conversion>+;
#pragma link C++ class mithep::Array<mithep::Conversion>+;
#pragma link C++ class mithep::ObjArray<mithep::Conversion>+;
#pragma link C++ class mithep::RefArray<mithep::Conversion,128>+;
#pragma link C++ typedef mithep::ConversionCol;
#pragma link C++ typedef mithep::ConversionArr;
#pragma link C++ typedef mithep::ConversionOArr;

#pragma link C++ class mithep::Photon+;
#pragma link C++ class mithep::Collection<mithep::Photon>+;
#pragma link C++ class mithep::Array<mithep::Photon>+;
#pragma link C++ class mithep::ObjArray<mithep::Photon>+;
#pragma link C++ typedef mithep::PhotonCol;
#pragma link C++ typedef mithep::PhotonArr;
#pragma link C++ typedef mithep::PhotonOArr;

#pragma link C++ class mithep::StableParticle+;
#pragma link C++ class mithep::Collection<mithep::StableParticle>+;
#pragma link C++ class mithep::Array<mithep::StableParticle>+;
#pragma link C++ class mithep::ObjArray<mithep::StableParticle>+;
#pragma link C++ typedef mithep::StableParticleCol;
#pragma link C++ typedef mithep::StableParticleArr;
#pragma link C++ typedef mithep::StableParticleOArr;

#pragma link C++ class mithep::StableDaughter+;
#pragma link C++ class mithep::Collection<mithep::StableDaughter>+;
#pragma link C++ class mithep::Array<mithep::StableDaughter>+;
#pragma link C++ class mithep::ObjArray<mithep::StableDaughter>+;
#pragma link C++ typedef mithep::StableDaughterCol;
#pragma link C++ typedef mithep::StableDaughterArr;
#pragma link C++ typedef mithep::StableDaughterOArr;

#endif
