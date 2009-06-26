// $Id: MitAnaPhysicsModLinkDef.h,v 1.15 2009/06/15 15:00:16 loizides Exp $

#ifndef MITANA_PHYSICSMOD_LINKDEF_H
#define MITANA_PHYSICSMOD_LINKDEF_H
#include "MitAna/PhysicsMod/interface/FullExampleMod.h"
#include "MitAna/PhysicsMod/interface/HLTExampleMod.h"
#include "MitAna/PhysicsMod/interface/SimpleExampleMod.h"
#include "MitAna/PhysicsMod/interface/TrackToPartMod.h"
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
#pragma link C++ class mithep::TrackToPartMod+;
#endif
