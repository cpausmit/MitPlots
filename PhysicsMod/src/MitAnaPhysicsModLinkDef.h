// $Id: MitAnaPhysicsModLinkDef.h,v 1.5 2008/11/28 20:27:23 loizides Exp $

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
#pragma link C++ class mithep::PlotKineMod<mithep::CompositeParticle>+;
#pragma link C++ class mithep::PlotKineMod<mithep::Conversion>+;
#pragma link C++ class mithep::PlotKineMod<mithep::Electron>+;
#pragma link C++ class mithep::PlotKineMod<mithep::GenJet>+;
#pragma link C++ class mithep::PlotKineMod<mithep::Jet>+;
#pragma link C++ class mithep::PlotKineMod<mithep::MCParticle>+;
#pragma link C++ class mithep::PlotKineMod<mithep::Met>+;
#pragma link C++ class mithep::PlotKineMod<mithep::Muon>+;
#pragma link C++ class mithep::PlotKineMod<mithep::Photon>+;
#pragma link C++ class mithep::PlotKineMod<mithep::Track>+;
#pragma link C++ class mithep::PlotKineMod<mithep::TriggerObject>+;
#endif
