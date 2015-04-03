// $Id: PublisherModLinkDef.h,v 1.2 2009/10/22 18:43:48 loizides Exp $

#ifndef MITANA_PHYSICSMOD_LINKDEF_H
#define MITANA_PHYSICSMOD_LINKDEF_H
#include "MitAna/PhysicsMod/interface/PublisherMod.h"
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
#include "MitAna/DataTree/interface/PFJet.h"
#include "MitAna/DataTree/interface/PFMet.h"
#include "MitAna/DataTree/interface/Photon.h"
#include "MitAna/DataTree/interface/Track.h"
#include "MitAna/DataTree/interface/SuperCluster.h"
#include "MitAna/DataTree/interface/TriggerObject.h"
#endif

#ifdef __CLING__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

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
#endif
