// $Id: MitAnaTreeModLinkDef.h,v 1.1 2008/05/27 19:50:16 loizides Exp $

#ifndef TREEMOD_LINKDEF_H
#define TREEMOD_LINKDEF_H
#include "MitAna/TreeMod/interface/Analysis.h"
#include "MitAna/TreeMod/interface/ParticleExampleMod.h"
#include "MitAna/TreeMod/interface/FullExampleMod.h"
#endif

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::Analysis+;
#pragma link C++ class mithep::ParticleExampleMod+;
#pragma link C++ class mithep::FullExampleMod+;
#endif
