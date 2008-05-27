// $Id: LinkDef.h 2272 2006-01-08 17:16:44Z loizides $

#ifndef TREEMOD_LINKDEF_H
#define TREEMOD_LINKDEF_H
#include "MitAna/TreeMod/interface/Analysis.h"
#include "MitAna/TreeMod/interface/ParticleExampleMod.h"
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
#endif
