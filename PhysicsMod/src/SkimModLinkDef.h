// $Id: $

#ifndef MITANA_PHYSICSMOD_SKIMMOD_LINKDEF_H
#define MITANA_PHYSICSMOD_SKIMMOD_LINKDEF_H
#include "MitAna/PhysicsMod/interface/SkimMod.h"
#include "MitAna/DataTree/interface/BasicCluster.h"
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
#include "MitAna/DataTree/interface/JPTJet.h"
#include "MitAna/DataTree/interface/PFCandidate.h"
#include "MitAna/DataTree/interface/PFJet.h"
#include "MitAna/DataTree/interface/PFMet.h"
#include "MitAna/DataTree/interface/Tau.h"
#include "MitAna/DataTree/interface/PFTau.h"
#include "MitAna/DataTree/interface/Photon.h"
#include "MitAna/DataTree/interface/Track.h"
#include "MitAna/DataTree/interface/SuperCluster.h"
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
