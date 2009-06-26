// $Id: MitAnaPhysicsModLinkDef.h,v 1.15 2009/06/15 15:00:16 loizides Exp $

#ifndef MITANA_PHYSICSMOD_FILTERMODLINKDEF_H
#define MITANA_PHYSICSMOD_FILTERMODLINKDEF_H
#include "MitAna/PhysicsMod/interface/FilterMod.h"
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

#ifdef __CINT__
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
#endif
