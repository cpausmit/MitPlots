// $Id: MitAnaPhysicsModLinkDef.h,v 1.19 2011/04/12 14:10:09 bendavid Exp $

#ifndef MITANA_PHYSICSMOD_LINKDEF_H
#define MITANA_PHYSICSMOD_LINKDEF_H
#include "MitAna/PhysicsMod/interface/FullExampleMod.h"
#include "MitAna/PhysicsMod/interface/HLTExampleMod.h"
#include "MitAna/PhysicsMod/interface/RunSelectionMod.h"
#include "MitAna/PhysicsMod/interface/RunLumiSelectionMod.h"
#include "MitAna/PhysicsMod/interface/SimpleExampleMod.h"
#include "MitAna/PhysicsMod/interface/TrackToPartMod.h"
#include "MitAna/PhysicsMod/interface/MCProcessSelectionMod.h"
#endif

#ifdef __CLING__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;
#pragma link C++ class mithep::FullExampleMod+;
#pragma link C++ class mithep::HLTExampleMod+;
#pragma link C++ class mithep::SimpleExampleMod+;
#pragma link C++ class mithep::TrackToPartMod+;
#pragma link C++ class mithep::RunSelectionMod+;
#pragma link C++ class mithep::RunLumiSelectionMod+;
#pragma link C++ class mithep::MCProcessSelectionMod+;
#endif
