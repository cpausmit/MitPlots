// $Id: MitAnaPhysicsModLinkDef.h,v 1.12 2009/05/18 06:30:39 loizides Exp $

#ifndef MITANA_PHYSICSMOD_LINKDEF_H
#define MITANA_PHYSICSMOD_LINKDEF_H
#include "MitAna/DataTree/interface/Collections.h"
#include "MitAna/PhysicsMod/interface/FilterMod.h"
#include "MitAna/PhysicsMod/interface/FullExampleMod.h"
#include "MitAna/PhysicsMod/interface/HLTExampleMod.h"
#include "MitAna/PhysicsMod/interface/PlotKineMod.h"
#include "MitAna/PhysicsMod/interface/PublisherMod.h"
#include "MitAna/PhysicsMod/interface/SimpleExampleMod.h"
#endif

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::FullExampleMod+;
#pragma link C++ class mithep::HLTExampleMod+;
#pragma link C++ class mithep::SimpleExampleMod+;

#pragma link C++ class mithep::FilterMod<mithep::CaloJet,mithep::Jet>+;
#pragma link C++ class mithep::FilterMod<mithep::CaloJet>+;
#pragma link C++ class mithep::FilterMod<mithep::CaloMet,mithep::Met>+;
#pragma link C++ class mithep::FilterMod<mithep::CaloMet>+;
#pragma link C++ class mithep::FilterMod<mithep::CaloTower>+;
#pragma link C++ class mithep::FilterMod<mithep::CompositeParticle>+;
#pragma link C++ class mithep::FilterMod<mithep::Conversion>+;
#pragma link C++ class mithep::FilterMod<mithep::Electron>+;
#pragma link C++ class mithep::FilterMod<mithep::GenJet>+;
#pragma link C++ class mithep::FilterMod<mithep::Jet>+;
#pragma link C++ class mithep::FilterMod<mithep::MCParticle>+;
#pragma link C++ class mithep::FilterMod<mithep::Met>+;
#pragma link C++ class mithep::FilterMod<mithep::Muon>+;
#pragma link C++ class mithep::FilterMod<mithep::Photon>+;
#pragma link C++ class mithep::FilterMod<mithep::Track>+;
#pragma link C++ class mithep::FilterMod<mithep::TriggerObject>+;

#pragma link C++ class mithep::PlotKineMod<mithep::CaloJet>+;
#pragma link C++ class mithep::PlotKineMod<mithep::CaloMet>+;
#pragma link C++ class mithep::PlotKineMod<mithep::CompositeParticle>+;
#pragma link C++ class mithep::PlotKineMod<mithep::Conversion>+;
#pragma link C++ class mithep::PlotKineMod<mithep::Electron>+;
#pragma link C++ class mithep::PlotKineMod<mithep::GenJet>+;
#pragma link C++ class mithep::PlotKineMod<mithep::Jet>+;
#pragma link C++ class mithep::PlotKineMod<mithep::MCParticle>+;
#pragma link C++ class mithep::PlotKineMod<mithep::Met>+;
#pragma link C++ class mithep::PlotKineMod<mithep::Muon>+;
#pragma link C++ class mithep::PlotKineMod<mithep::Particle>+;
#pragma link C++ class mithep::PlotKineMod<mithep::Photon>+;
#pragma link C++ class mithep::PlotKineMod<mithep::Track>+;
#pragma link C++ class mithep::PlotKineMod<mithep::TriggerObject>+;

#pragma link C++ class mithep::PublisherMod<mithep::CaloJet,mithep::Jet>+;
#pragma link C++ class mithep::PublisherMod<mithep::CaloJet>+;
#pragma link C++ class mithep::PublisherMod<mithep::PFJet,mithep::Jet>+;
#pragma link C++ class mithep::PublisherMod<mithep::PFJet>+;
#pragma link C++ class mithep::PublisherMod<mithep::CaloMet,mithep::Met>+;
#pragma link C++ class mithep::PublisherMod<mithep::CaloMet>+;
#pragma link C++ class mithep::PublisherMod<mithep::CaloTower>+;
#pragma link C++ class mithep::PublisherMod<mithep::CompositeParticle>+;
#pragma link C++ class mithep::PublisherMod<mithep::Conversion>+;
#pragma link C++ class mithep::PublisherMod<mithep::Electron>+;
#pragma link C++ class mithep::PublisherMod<mithep::GenJet>+;
#pragma link C++ class mithep::PublisherMod<mithep::Jet>+;
#pragma link C++ class mithep::PublisherMod<mithep::MCParticle>+;
#pragma link C++ class mithep::PublisherMod<mithep::Met>+;
#pragma link C++ class mithep::PublisherMod<mithep::Muon>+;
#pragma link C++ class mithep::PublisherMod<mithep::Photon>+;
#pragma link C++ class mithep::PublisherMod<mithep::Track>+;
#pragma link C++ class mithep::PublisherMod<mithep::TriggerObject>+;
#endif
