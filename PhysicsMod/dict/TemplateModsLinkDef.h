// $Id: MitAnaPhysicsModLinkDef.h,v 1.15 2009/06/15 15:00:16 loizides Exp $

#ifndef MITANA_PHYSICSMOD_FILTERMODLINKDEF_H
#define MITANA_PHYSICSMOD_FILTERMODLINKDEF_H
#include "MitAna/PhysicsMod/interface/FilterMod.h"
#include "MitAna/PhysicsMod/interface/MergerMod.h"
#include "MitAna/PhysicsMod/interface/PlotKineMod.h"
#include "MitAna/PhysicsMod/interface/PublisherMod.h"
#include "MitAna/PhysicsMod/interface/SkimMod.h"

#include "MitAna/DataTree/interface/BasicCluster.h"
#include "MitAna/DataTree/interface/CaloJet.h"
#include "MitAna/DataTree/interface/CaloMet.h"
#include "MitAna/DataTree/interface/CaloTower.h"
#include "MitAna/DataTree/interface/CompositeParticle.h"
#include "MitAna/DataTree/interface/CompoundParticle.h"
#include "MitAna/DataTree/interface/Conversion.h"
#include "MitAna/DataTree/interface/DataBase.h"
#include "MitAna/DataTree/interface/DataObject.h"
#include "MitAna/DataTree/interface/Electron.h"
#include "MitAna/DataTree/interface/GenJet.h"
#include "MitAna/DataTree/interface/GenericParticle.h"
#include "MitAna/DataTree/interface/JPTJet.h"
#include "MitAna/DataTree/interface/MCParticle.h"
#include "MitAna/DataTree/interface/Muon.h"
#include "MitAna/DataTree/interface/PFJet.h"
#include "MitAna/DataTree/interface/PFMet.h"
#include "MitAna/DataTree/interface/Particle.h"
#include "MitAna/DataTree/interface/Photon.h"
#include "MitAna/DataTree/interface/SuperCluster.h"
#include "MitAna/DataTree/interface/Tau.h"
#include "MitAna/DataTree/interface/Track.h"
#include "MitAna/DataTree/interface/TriggerObject.h"
#include "MitAna/DataTree/interface/Vertex.h"
#endif

#ifdef __CLING__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::FilterMod<mithep::CaloJet,mithep::Jet>+;
#pragma link C++ class mithep::FilterMod<mithep::CaloJet>+;
#pragma link C++ class mithep::FilterMod<mithep::CaloMet,mithep::Met>+;
#pragma link C++ class mithep::FilterMod<mithep::CaloMet>+;
#pragma link C++ class mithep::FilterMod<mithep::CaloTower>+;
#pragma link C++ class mithep::FilterMod<mithep::CompositeParticle>+;
#pragma link C++ class mithep::FilterMod<mithep::CompoundParticle>+;
#pragma link C++ class mithep::FilterMod<mithep::Conversion>+;
#pragma link C++ class mithep::FilterMod<mithep::Electron>+;
#pragma link C++ class mithep::FilterMod<mithep::GenJet>+;
#pragma link C++ class mithep::FilterMod<mithep::Jet>+;
#pragma link C++ class mithep::FilterMod<mithep::MCParticle>+;
#pragma link C++ class mithep::FilterMod<mithep::Met>+;
#pragma link C++ class mithep::FilterMod<mithep::Muon>+;
#pragma link C++ class mithep::FilterMod<mithep::PFJet>+;
#pragma link C++ class mithep::FilterMod<mithep::Photon>+;
#pragma link C++ class mithep::FilterMod<mithep::Track>+;
#pragma link C++ class mithep::FilterMod<mithep::TriggerObject>+;

#pragma link C++ class mithep::MergerMod<TObject>+;
#pragma link C++ class mithep::MergerMod<mithep::BasicCluster>+;
#pragma link C++ class mithep::MergerMod<mithep::DataBase>+;
#pragma link C++ class mithep::MergerMod<mithep::DataObject>+;
#pragma link C++ class mithep::MergerMod<mithep::GenericParticle>+;
#pragma link C++ class mithep::MergerMod<mithep::Particle>+;
#pragma link C++ class mithep::MergerMod<mithep::SuperCluster>+;

#pragma link C++ class mithep::PlotKineMod<mithep::CaloJet>+;
#pragma link C++ class mithep::PlotKineMod<mithep::CaloMet>+;
#pragma link C++ class mithep::PlotKineMod<mithep::CompositeParticle>+;
#pragma link C++ class mithep::PlotKineMod<mithep::CompoundParticle>+;
#pragma link C++ class mithep::PlotKineMod<mithep::Conversion>+;
#pragma link C++ class mithep::PlotKineMod<mithep::Electron>+;
#pragma link C++ class mithep::PlotKineMod<mithep::GenJet>+;
#pragma link C++ class mithep::PlotKineMod<mithep::Jet>+;
#pragma link C++ class mithep::PlotKineMod<mithep::MCParticle>+;
#pragma link C++ class mithep::PlotKineMod<mithep::Met>+;
#pragma link C++ class mithep::PlotKineMod<mithep::Muon>+;
#pragma link C++ class mithep::PlotKineMod<mithep::PFJet>+;
#pragma link C++ class mithep::PlotKineMod<mithep::Particle>+;
#pragma link C++ class mithep::PlotKineMod<mithep::Photon>+;
#pragma link C++ class mithep::PlotKineMod<mithep::Track>+;
#pragma link C++ class mithep::PlotKineMod<mithep::TriggerObject>+;

#pragma link C++ class mithep::PublisherMod<mithep::BasicCluster>+;
#pragma link C++ class mithep::PublisherMod<mithep::CaloJet,mithep::Jet>+;
#pragma link C++ class mithep::PublisherMod<mithep::CaloJet>+;
#pragma link C++ class mithep::PublisherMod<mithep::CaloMet,mithep::Met>+;
#pragma link C++ class mithep::PublisherMod<mithep::CaloMet>+;
#pragma link C++ class mithep::PublisherMod<mithep::CaloTower>+;
#pragma link C++ class mithep::PublisherMod<mithep::CompositeParticle>+;
#pragma link C++ class mithep::PublisherMod<mithep::CompoundParticle>+;
#pragma link C++ class mithep::PublisherMod<mithep::Conversion>+;
#pragma link C++ class mithep::PublisherMod<mithep::Electron>+;
#pragma link C++ class mithep::PublisherMod<mithep::Muon>+;
#pragma link C++ class mithep::PublisherMod<mithep::GenJet>+;
#pragma link C++ class mithep::PublisherMod<mithep::Jet>+;
#pragma link C++ class mithep::PublisherMod<mithep::MCParticle>+;
#pragma link C++ class mithep::PublisherMod<mithep::Met>+;
#pragma link C++ class mithep::PublisherMod<mithep::PFMet,mithep::Met>+;
#pragma link C++ class mithep::PublisherMod<mithep::PFMet>+;
#pragma link C++ class mithep::PublisherMod<mithep::PFJet,mithep::Jet>+;
#pragma link C++ class mithep::PublisherMod<mithep::PFJet>+;
#pragma link C++ class mithep::PublisherMod<mithep::Photon>+;
#pragma link C++ class mithep::PublisherMod<mithep::SuperCluster>+;
#pragma link C++ class mithep::PublisherMod<mithep::Track>+;
#pragma link C++ class mithep::PublisherMod<mithep::TriggerObject>+;
#pragma link C++ class mithep::PublisherMod<mithep::JPTJet, mithep::Jet>+;

#pragma link C++ class mithep::SkimMod<mithep::BasicCluster>+;
#pragma link C++ class mithep::SkimMod<mithep::CaloJet>+;
#pragma link C++ class mithep::SkimMod<mithep::CaloMet>+;
#pragma link C++ class mithep::SkimMod<mithep::CaloTower>+;
#pragma link C++ class mithep::SkimMod<mithep::CompositeParticle>+;
#pragma link C++ class mithep::SkimMod<mithep::Conversion>+;
#pragma link C++ class mithep::SkimMod<mithep::Electron>+;
#pragma link C++ class mithep::SkimMod<mithep::GenJet>+;
#pragma link C++ class mithep::SkimMod<mithep::Jet>+;
#pragma link C++ class mithep::SkimMod<mithep::MCParticle>+;
#pragma link C++ class mithep::SkimMod<mithep::Met>+;
#pragma link C++ class mithep::SkimMod<mithep::CaloMet>+;
#pragma link C++ class mithep::SkimMod<mithep::PFMet>+;
#pragma link C++ class mithep::SkimMod<mithep::Muon>+;
#pragma link C++ class mithep::SkimMod<mithep::PFCandidate>+;
#pragma link C++ class mithep::SkimMod<mithep::PFJet>+;
#pragma link C++ class mithep::SkimMod<mithep::Tau>+;
#pragma link C++ class mithep::SkimMod<mithep::PFTau>+;
#pragma link C++ class mithep::SkimMod<mithep::Photon>+;
#pragma link C++ class mithep::SkimMod<mithep::SuperCluster>+;
#pragma link C++ class mithep::SkimMod<mithep::Track>+;
#pragma link C++ class mithep::SkimMod<mithep::TriggerObject>+;
#pragma link C++ class mithep::SkimMod<mithep::Vertex>+;
#endif
