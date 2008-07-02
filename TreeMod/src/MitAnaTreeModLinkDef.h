// $Id: MitAnaTreeModLinkDef.h,v 1.4 2008/06/23 10:54:03 loizides Exp $

#ifndef TREEMOD_LINKDEF_H
#define TREEMOD_LINKDEF_H
#include "MitAna/TreeMod/interface/Analysis.h"
#include "MitAna/TreeMod/interface/Selector.h"
#include "MitAna/TreeMod/interface/TreeLoader.h"
#include "MitAna/TreeMod/interface/TreeBranchLoader.h"
#include "MitAna/TreeMod/interface/BaseMod.h"
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
#pragma link C++ class mithep::Selector+;
#pragma link C++ class mithep::TreeLoader+;
#pragma link C++ class mithep::TreeBranchLoader+;
#pragma link C++ class mithep::BaseMod+;
#pragma link C++ class mithep::ParticleExampleMod+;
#pragma link C++ class mithep::FullExampleMod+;
#endif
