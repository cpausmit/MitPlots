// $Id: MitAnaPhysicsModLinkDef.h,v 1.1 2008/10/06 15:40:14 sixie Exp $

#ifndef PHYSICSMOD_LINKDEF_H
#define PHYSICSMOD_LINKDEF_H
#include "MitAna/PhysicsMod/interface/HwwEvtSelMod.h"
#include "MitAna/PhysicsMod/interface/HwwEvtPreSelMod.h"
#include "MitAna/PhysicsMod/interface/ttEvtSelMod.h"
#include "MitAna/PhysicsMod/interface/FwdJetEvtSelMod.h"
#include "MitAna/PhysicsMod/interface/ZXEvtSelMod.h"
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
#pragma link C++ class mithep::ttEvtSelMod+;
#pragma link C++ class mithep::FwdJetEvtSelMod+;
#pragma link C++ class mithep::ZXEvtSelMod+;
#endif
