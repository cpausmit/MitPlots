// $Id: MitAnaPhysicsModLinkDef.h,v 1.15 2009/06/15 15:00:16 loizides Exp $

#ifndef MITANA_PHYSICSMOD_PLOTKINELINKDEF_H
#define MITANA_PHYSICSMOD_PLOTKINELINKDEF_H
#include "MitAna/PhysicsMod/interface/PlotKineMod.h"
#include "MitAna/DataTree/interface/CaloJet.h"
#include "MitAna/DataTree/interface/CaloMet.h"
#include "MitAna/DataTree/interface/CaloTower.h"
#include "MitAna/DataTree/interface/CompositeParticle.h"
#include "MitAna/DataTree/interface/CompoundParticle.h"
#include "MitAna/DataTree/interface/Conversion.h"
#include "MitAna/DataTree/interface/Electron.h"
#include "MitAna/DataTree/interface/GenJet.h"
#include "MitAna/DataTree/interface/MCParticle.h"
#include "MitAna/DataTree/interface/Muon.h"
#include "MitAna/DataTree/interface/PFJet.h"
#include "MitAna/DataTree/interface/PFMet.h"
#include "MitAna/DataTree/interface/Photon.h"
#include "MitAna/DataTree/interface/Track.h"
#include "MitAna/DataTree/interface/TriggerObject.h"
#endif

#ifdef __CLING__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

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
#endif
