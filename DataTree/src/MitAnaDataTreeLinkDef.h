// $Id: MitAnaDataTreeLinkDef.h,v 1.67 2009/04/09 11:24:46 loizides Exp $

#ifndef MITANA_DATATREE_LINKDEF_H
#define MITANA_DATATREE_LINKDEF_H

#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/Collections.h"
#include "MitAna/DataTree/interface/Names.h"
#include "MitAna/DataTree/interface/ObjTypes.h"
#include "MitAna/DataTree/interface/Types.h"

#include "MitAna/DataTree/interface/DataBase.h"
#include "MitAna/DataTree/interface/BranchName.h"
#include "MitAna/DataTree/interface/BranchTable.h"
#include "MitAna/DataTree/interface/EventHeader.h"
#include "MitAna/DataTree/interface/LAHeader.h"
#include "MitAna/DataTree/interface/MCEventInfo.h"
#include "MitAna/DataTree/interface/RunInfo.h"
#include "MitAna/DataTree/interface/TriggerName.h"
#include "MitAna/DataTree/interface/TriggerMask.h"
#include "MitAna/DataTree/interface/TriggerTable.h"

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
#include "MitAna/DataTree/interface/GenericParticle.h"
#include "MitAna/DataTree/interface/Muon.h"
#include "MitAna/DataTree/interface/Electron.h"
#include "MitAna/DataTree/interface/Jet.h"
#include "MitAna/DataTree/interface/CaloJet.h"
#include "MitAna/DataTree/interface/GenJet.h"
#include "MitAna/DataTree/interface/Met.h"
#include "MitAna/DataTree/interface/CaloMet.h"
#include "MitAna/DataTree/interface/PFMet.h"
#include "MitAna/DataTree/interface/TriggerObject.h"
#include "MitAna/DataTree/interface/MCParticle.h"
#include "MitAna/DataTree/interface/CompositeParticle.h"
#include "MitAna/DataTree/interface/CompoundParticle.h"
#include "MitAna/DataTree/interface/DaughterData.h"
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
#endif

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::Names+;

#pragma link C++ class mithep::Collection<TObject>+;
#pragma link C++ class mithep::ObjArray<TObject>+;

#pragma link C++ class mithep::DataBase+;
#pragma link C++ class mithep::Collection<mithep::DataBase>+;
#pragma link C++ class mithep::Array<mithep::DataBase>+;
#pragma link C++ class mithep::ObjArray<mithep::DataBase>+;
#pragma link C++ typedef mithep::DataObjectCol;
#pragma link C++ typedef mithep::DataObjectArr;
#pragma link C++ typedef mithep::DataObjectOArr;
#pragma link C++ enum mithep::EObjType;

#pragma link C++ class mithep::EventHeader+;
#pragma link C++ class mithep::Collection<mithep::EventHeader>+;
#pragma link C++ class mithep::Array<mithep::EventHeader>+;
#pragma link C++ class mithep::ObjArray<mithep::EventHeader>+;
#pragma link C++ typedef mithep::EventHeaderCol;
#pragma link C++ typedef mithep::EventHeaderArr;
#pragma link C++ typedef mithep::EventHeaderOArr;

#pragma link C++ class mithep::BranchName+;
#pragma link C++ class mithep::BranchTable+;
#pragma link C++ class mithep::LAHeader+;
#pragma link C++ class mithep::MCEventInfo+;
#pragma link C++ class mithep::RunInfo+;
#pragma link C++ class mithep::TriggerName+;
#pragma link C++ class mithep::TriggerTable+;

#pragma link C++ class mithep::DataObject+;
#pragma link C++ class mithep::Collection<mithep::DataObject>+;
#pragma link C++ class mithep::Array<mithep::DataObject>+;
#pragma link C++ class mithep::ObjArray<mithep::DataObject>+;
#pragma link C++ class mithep::Ref<mithep::DataObject>+;
#pragma link C++ typedef mithep::DataObjectCol;
#pragma link C++ typedef mithep::DataObjectArr;
#pragma link C++ typedef mithep::DataObjectOArr;

#pragma link C++ class mithep::Ref<mithep::MCParticle>+;
#pragma link C++ class mithep::MCParticle+;
#pragma link C++ class mithep::Collection<mithep::MCParticle>+;
#pragma link C++ class mithep::Array<mithep::MCParticle>+;
#pragma link C++ class mithep::ObjArray<mithep::MCParticle>+;
#pragma link C++ typedef mithep::MCParticleCol;
#pragma link C++ typedef mithep::MCParticleArr;
#pragma link C++ typedef mithep::MCParticleOArr;
#pragma link C++ enum mithep::MCParticle::EPartType;

#pragma link C++ class mithep::BaseVertex+;
#pragma link C++ class mithep::Collection<mithep::BaseVertex>+;
#pragma link C++ class mithep::Array<mithep::BaseVertex>+;
#pragma link C++ class mithep::ObjArray<mithep::BaseVertex>+;
#pragma link C++ class mithep::Ref<mithep::BaseVertex>+;
#pragma link C++ typedef mithep::BaseVertexCol;
#pragma link C++ typedef mithep::BaseVertexArr;

#pragma link C++ class mithep::Vertex+;
#pragma link C++ class mithep::Collection<mithep::Vertex>+;
#pragma link C++ class mithep::Array<mithep::Vertex>+;
#pragma link C++ class mithep::ObjArray<mithep::Vertex>+;
#pragma link C++ class mithep::Ref<mithep::Vertex>+;
#pragma link C++ typedef mithep::VertexCol;
#pragma link C++ typedef mithep::VertexArr;

#pragma link C++ class mithep::BeamSpot+;
#pragma link C++ class mithep::Collection<mithep::BeamSpot>+;
#pragma link C++ class mithep::Array<mithep::BeamSpot>+;
#pragma link C++ class mithep::ObjArray<mithep::BeamSpot>+;
#pragma link C++ class mithep::Ref<mithep::BeamSpot>+;
#pragma link C++ typedef mithep::BeamSpotCol;
#pragma link C++ typedef mithep::BeamSpotArr;

#pragma link C++ class mithep::BasicCluster+;
#pragma link C++ class mithep::Collection<mithep::BasicCluster>+;
#pragma link C++ class mithep::Array<mithep::BasicCluster>+;
#pragma link C++ class mithep::ObjArray<mithep::BasicCluster>+;
#pragma link C++ class mithep::Ref<mithep::BasicCluster>+;
#pragma link C++ class mithep::RefArray<mithep::BasicCluster>+;
#pragma link C++ typedef mithep::BasicClusterCol;
#pragma link C++ typedef mithep::BasicClusterArr;
#pragma link C++ typedef mithep::BasicClusterOArr;

#pragma link C++ class mithep::SuperCluster+;
#pragma link C++ class mithep::Collection<mithep::SuperCluster>+;
#pragma link C++ class mithep::Array<mithep::SuperCluster>+;
#pragma link C++ class mithep::ObjArray<mithep::SuperCluster>+;
#pragma link C++ class mithep::Ref<mithep::SuperCluster>+;
#pragma link C++ typedef mithep::SuperClusterCol;
#pragma link C++ typedef mithep::SuperClusterArr;
#pragma link C++ typedef mithep::SuperClusterOArr;

#pragma link C++ class mithep::Track+;
#pragma link C++ class mithep::Collection<mithep::Track>+;
#pragma link C++ class mithep::Array<mithep::Track>+;
#pragma link C++ class mithep::ObjArray<mithep::Track>+;
#pragma link C++ class mithep::Ref<mithep::Track>+;
#pragma link C++ class mithep::RefArray<mithep::Track>+;
#pragma link C++ typedef mithep::TrackCol;
#pragma link C++ typedef mithep::TrackArr;
#pragma link C++ typedef mithep::TrackOArr;
#pragma link C++ enum mithep::Track::EHitLayer;

#pragma link C++ class mithep::CaloTower+;
#pragma link C++ class mithep::Collection<mithep::CaloTower>+;
#pragma link C++ class mithep::Array<mithep::CaloTower>+;
#pragma link C++ class mithep::ObjArray<mithep::CaloTower>+;
#pragma link C++ class mithep::Ref<mithep::CaloTower>+;
#pragma link C++ class mithep::RefArray<mithep::CaloTower>+;
#pragma link C++ typedef mithep::CaloTowerCol;
#pragma link C++ typedef mithep::CaloTowerArr;
#pragma link C++ typedef mithep::CaloTowerOArr;

#pragma link C++ class mithep::Particle+;
#pragma link C++ class mithep::Collection<mithep::Particle>+;
#pragma link C++ class mithep::RefArray<mithep::Particle>+;
#pragma link C++ class mithep::ObjArray<mithep::Particle>+;
#pragma link C++ class mithep::Ref<mithep::Particle>+;
#pragma link C++ typedef mithep::ParticleCol;
#pragma link C++ typedef mithep::ParticleOArr;

#pragma link C++ class mithep::ChargedParticle+;
#pragma link C++ class mithep::Collection<mithep::ChargedParticle>+;
#pragma link C++ class mithep::ObjArray<mithep::ChargedParticle>+;
#pragma link C++ class mithep::Ref<mithep::ChargedParticle>+;
#pragma link C++ typedef mithep::ChargedParticleCol;
#pragma link C++ typedef mithep::ChargedParticleArr;
#pragma link C++ typedef mithep::ChargedParticleOArr;

#pragma link C++ class mithep::GenericParticle+;
#pragma link C++ class mithep::Collection<mithep::GenericParticle>+;
#pragma link C++ class mithep::RefArray<mithep::GenericParticle>+;
#pragma link C++ class mithep::ObjArray<mithep::GenericParticle>+;
#pragma link C++ class mithep::Ref<mithep::GenericParticle>+;
#pragma link C++ typedef mithep::GenericParticleCol;
#pragma link C++ typedef mithep::GenericParticleOArr;

#pragma link C++ class mithep::Muon+;
#pragma link C++ enum mithep::Muon::EClassType;
#pragma link C++ class mithep::Collection<mithep::Muon>+;
#pragma link C++ class mithep::Array<mithep::Muon>+;
#pragma link C++ class mithep::ObjArray<mithep::Muon>+;
#pragma link C++ class mithep::Ref<mithep::Muon>+;
#pragma link C++ typedef mithep::MuonCol;
#pragma link C++ typedef mithep::MuonArr;
#pragma link C++ typedef mithep::MuonOArr;

#pragma link C++ class mithep::Electron+;
#pragma link C++ class mithep::Collection<mithep::Electron>+;
#pragma link C++ class mithep::Array<mithep::Electron>+;
#pragma link C++ class mithep::ObjArray<mithep::Electron>+;
#pragma link C++ class mithep::Ref<mithep::Electron>+;
#pragma link C++ typedef mithep::ElectronCol;
#pragma link C++ typedef mithep::ElectronArr;
#pragma link C++ typedef mithep::ElectronOArr;

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

#pragma link C++ class mithep::TriggerMask+;
#pragma link C++ class mithep::Collection<mithep::TriggerMask>+;
#pragma link C++ class mithep::Array<mithep::TriggerMask>+;
#pragma link C++ class mithep::ObjArray<mithep::TriggerMask>+;
#pragma link C++ typedef mithep::TriggerMaskCol;
#pragma link C++ typedef mithep::TriggerMaskArr;
#pragma link C++ typedef mithep::TriggerMaskOArr;

#pragma link C++ class mithep::CompositeParticle+;
#pragma link C++ class mithep::Collection<mithep::CompositeParticle>+;
#pragma link C++ class mithep::Array<mithep::CompositeParticle>+;
#pragma link C++ class mithep::ObjArray<mithep::CompositeParticle>+;
#pragma link C++ class mithep::Ref<mithep::CompositeParticle>+;
#pragma link C++ typedef mithep::CompositeParticleCol;
#pragma link C++ typedef mithep::CompositeParticleArr;
#pragma link C++ typedef mithep::CompositeParticleOArr;

#pragma link C++ class mithep::CompoundParticle+;

#pragma link C++ class mithep::DaughterData+;
#pragma link C++ class mithep::Collection<mithep::DaughterData>+;
#pragma link C++ class mithep::RefArray<mithep::DaughterData>+;

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
#pragma link C++ class mithep::Ref<mithep::Conversion>+;
#pragma link C++ class mithep::RefArray<mithep::Conversion>+;
#pragma link C++ typedef mithep::ConversionCol;
#pragma link C++ typedef mithep::ConversionArr;
#pragma link C++ typedef mithep::ConversionOArr;

#pragma link C++ class mithep::Photon+;
#pragma link C++ class mithep::Collection<mithep::Photon>+;
#pragma link C++ class mithep::Array<mithep::Photon>+;
#pragma link C++ class mithep::ObjArray<mithep::Photon>+;
#pragma link C++ class mithep::Ref<mithep::Photon>+;
#pragma link C++ typedef mithep::PhotonCol;
#pragma link C++ typedef mithep::PhotonArr;
#pragma link C++ typedef mithep::PhotonOArr;

#pragma link C++ class mithep::StableParticle+;
#pragma link C++ class mithep::Collection<mithep::StableParticle>+;
#pragma link C++ class mithep::Array<mithep::StableParticle>+;
#pragma link C++ class mithep::ObjArray<mithep::StableParticle>+;
#pragma link C++ class mithep::Ref<mithep::StableParticle>+;
#pragma link C++ typedef mithep::StableParticleCol;
#pragma link C++ typedef mithep::StableParticleArr;
#pragma link C++ typedef mithep::StableParticleOArr;

#pragma link C++ class mithep::Ref<mithep::PFCandidate>+;
#pragma link C++ class mithep::PFCandidate+;
#pragma link C++ class mithep::Collection<mithep::PFCandidate>+;
#pragma link C++ class mithep::Array<mithep::PFCandidate>+;
#pragma link C++ class mithep::ObjArray<mithep::PFCandidate>+;
#pragma link C++ class mithep::RefArray<mithep::PFCandidate>+;
#pragma link C++ typedef mithep::PFCandidateCol;
#pragma link C++ typedef mithep::PFCandidateArr;
#pragma link C++ typedef mithep::PFCandidateOArr;

#pragma link C++ class mithep::Jet+;
#pragma link C++ class mithep::Collection<mithep::Jet>+;
#pragma link C++ class mithep::Array<mithep::Jet>+;
#pragma link C++ class mithep::ObjArray<mithep::Jet>+;
#pragma link C++ class mithep::Ref<mithep::Jet>+;
#pragma link C++ typedef mithep::JetCol;
#pragma link C++ typedef mithep::JetArr;
#pragma link C++ typedef mithep::JetOArr;

#pragma link C++ class mithep::CaloJet+;
#pragma link C++ class mithep::Collection<mithep::CaloJet>+;
#pragma link C++ class mithep::Array<mithep::CaloJet>+;
#pragma link C++ class mithep::ObjArray<mithep::CaloJet>+;
#pragma link C++ class mithep::Ref<mithep::CaloJet>+;
#pragma link C++ typedef mithep::CaloJetCol;
#pragma link C++ typedef mithep::CaloJetArr;
#pragma link C++ typedef mithep::CaloJetOArr;

#pragma link C++ class mithep::PFJet+;
#pragma link C++ class mithep::Collection<mithep::PFJet>+;
#pragma link C++ class mithep::Array<mithep::PFJet>+;
#pragma link C++ class mithep::ObjArray<mithep::PFJet>+;
#pragma link C++ class mithep::Ref<mithep::PFJet>+;
#pragma link C++ typedef mithep::PFJetCol;
#pragma link C++ typedef mithep::PFJetArr;
#pragma link C++ typedef mithep::PFJetOArr;

#pragma link C++ class mithep::GenJet+;
#pragma link C++ class mithep::Collection<mithep::GenJet>+;
#pragma link C++ class mithep::Array<mithep::GenJet>+;
#pragma link C++ class mithep::ObjArray<mithep::GenJet>+;
#pragma link C++ class mithep::Ref<mithep::GenJet>+;
#pragma link C++ typedef mithep::GenJetCol;
#pragma link C++ typedef mithep::GenJetArr;
#pragma link C++ typedef mithep::GenJetOArr;

#pragma link C++ class mithep::Met+;
#pragma link C++ class mithep::Collection<mithep::Met>+;
#pragma link C++ class mithep::Array<mithep::Met>+;
#pragma link C++ class mithep::ObjArray<mithep::Met>+;
#pragma link C++ class mithep::Ref<mithep::Met>+;
#pragma link C++ typedef mithep::MetCol;
#pragma link C++ typedef mithep::MetArr;
#pragma link C++ typedef mithep::MetOArr;

#pragma link C++ class mithep::CaloMet+;
#pragma link C++ class mithep::Collection<mithep::CaloMet>+;
#pragma link C++ class mithep::Array<mithep::CaloMet>+;
#pragma link C++ class mithep::ObjArray<mithep::CaloMet>+;
#pragma link C++ class mithep::Ref<mithep::CaloMet>+;
#pragma link C++ typedef mithep::CaloMetCol;
#pragma link C++ typedef mithep::CaloMetArr;
#pragma link C++ typedef mithep::CaloMetOArr;

#pragma link C++ class mithep::PFMet+;
#pragma link C++ class mithep::Collection<mithep::PFMet>+;
#pragma link C++ class mithep::Array<mithep::PFMet>+;
#pragma link C++ class mithep::ObjArray<mithep::PFMet>+;
#pragma link C++ class mithep::Ref<mithep::PFMet>+;
#pragma link C++ typedef mithep::PFMetCol;
#pragma link C++ typedef mithep::PFMetArr;
#pragma link C++ typedef mithep::PFMetOArr;

#pragma link C++ class mithep::Tau+;
#pragma link C++ class mithep::Collection<mithep::Tau>+;
#pragma link C++ class mithep::Array<mithep::Tau>+;
#pragma link C++ class mithep::ObjArray<mithep::Tau>+;
#pragma link C++ class mithep::Ref<mithep::Tau>+;
#pragma link C++ typedef mithep::TauCol;
#pragma link C++ typedef mithep::TauArr;
#pragma link C++ typedef mithep::TauOArr;

#pragma link C++ class mithep::CaloTau+;
#pragma link C++ class mithep::Collection<mithep::CaloTau>+;
#pragma link C++ class mithep::Array<mithep::CaloTau>+;
#pragma link C++ class mithep::ObjArray<mithep::CaloTau>+;
#pragma link C++ class mithep::Ref<mithep::CaloTau>+;
#pragma link C++ typedef mithep::CaloTauCol;
#pragma link C++ typedef mithep::CaloTauArr;
#pragma link C++ typedef mithep::CaloTauOArr;

#pragma link C++ class mithep::PFTau+;
#pragma link C++ class mithep::Collection<mithep::PFTau>+;
#pragma link C++ class mithep::Array<mithep::PFTau>+;
#pragma link C++ class mithep::ObjArray<mithep::PFTau>+;
#pragma link C++ class mithep::Ref<mithep::PFTau>+;
#pragma link C++ typedef mithep::PFTauCol;
#pragma link C++ typedef mithep::PFTauArr;
#pragma link C++ typedef mithep::PFTauOArr;

#endif
