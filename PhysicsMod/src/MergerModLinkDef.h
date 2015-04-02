// $Id: MergerModLinkDef.h,v 1.1 2009/06/17 08:42:29 loizides Exp $

#ifndef MITANA_PHYSICSMOD_MERGERMODLINKDEF_H
#define MITANA_PHYSICSMOD_MERGERMODLINKDEF_H
#include "MitAna/PhysicsMod/interface/MergerMod.h"
#include "MitAna/DataTree/interface/BasicCluster.h"
#include "MitAna/DataTree/interface/DataBase.h"
#include "MitAna/DataTree/interface/DataObject.h"
#include "MitAna/DataTree/interface/GenericParticle.h"
#include "MitAna/DataTree/interface/Particle.h"
#include "MitAna/DataTree/interface/SuperCluster.h"
#endif

#ifdef __CLING__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::MergerMod<TObject>+;
#pragma link C++ class mithep::MergerMod<mithep::BasicCluster>+;
#pragma link C++ class mithep::MergerMod<mithep::DataBase>+;
#pragma link C++ class mithep::MergerMod<mithep::DataObject>+;
#pragma link C++ class mithep::MergerMod<mithep::GenericParticle>+;
#pragma link C++ class mithep::MergerMod<mithep::Particle>+;
#pragma link C++ class mithep::MergerMod<mithep::SuperCluster>+;
#endif
