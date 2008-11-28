// $Id: MitAnaPhysicsModLinkDef.h,v 1.4 2008/11/25 14:30:54 loizides Exp $

#ifndef MITANA_PHYSICSMOD_LINKDEF_H
#define MITANA_PHYSICSMOD_LINKDEF_H
#include "MitAna/DataTree/interface/Collections.h"
#include "MitAna/PhysicsMod/interface/FullExampleMod.h"
#include "MitAna/PhysicsMod/interface/HLTExampleMod.h"
#include "MitAna/PhysicsMod/interface/SimpleExampleMod.h"
#include "MitAna/PhysicsMod/interface/PlotKineMod.h"
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
#pragma link C++ class mithep::PlotKineMod<mithep::CompositeParticleCol>+;
#pragma link C++ class mithep::PlotKineMod<mithep::ConversionCol>+;
#pragma link C++ class mithep::PlotKineMod<mithep::ElectronCol>+;
#pragma link C++ class mithep::PlotKineMod<mithep::GenJetCol>+;
#pragma link C++ class mithep::PlotKineMod<mithep::JetCol>+;
#pragma link C++ class mithep::PlotKineMod<mithep::MCParticleCol>+;
#pragma link C++ class mithep::PlotKineMod<mithep::MetCol>+;
#pragma link C++ class mithep::PlotKineMod<mithep::MuonCol>+;
#pragma link C++ class mithep::PlotKineMod<mithep::PhotonCol>+;
//#pragma link C++ class mithep::PlotKineMod<mithep::TrackCol>+;
#pragma link C++ class mithep::PlotKineMod<mithep::TriggerObjectCol>+;
#endif
