// $Id:  $

#ifndef PHYSICSMOD_LINKDEF_H
#define PHYSICSMOD_LINKDEF_H
#include "MitAna/PhysicsMod/interface/HwwEvtSelMod.h"
#include "MitAna/PhysicsMod/interface/HwwEvtPreSelMod.h"
#endif
 
#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::HwwEvtSelMod+;
#pragma link C++ class mithep::HwwEvtPreSelMod+;
#endif
