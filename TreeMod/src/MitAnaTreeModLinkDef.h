// $Id: MitAnaTreeModLinkDef.h,v 1.9 2008/09/30 16:39:26 sixie Exp $

#ifndef TREEMOD_LINKDEF_H
#define TREEMOD_LINKDEF_H
#include "MitAna/TreeMod/interface/Analysis.h"
#include "MitAna/TreeMod/interface/Selector.h"
#include "MitAna/TreeMod/interface/TreeLoader.h"
#include "MitAna/TreeMod/interface/TreeBranchLoader.h"
#include "MitAna/TreeMod/interface/BaseMod.h"
#include "MitAna/TreeMod/interface/HLTFwkMod.h"
#include "MitAna/TreeMod/interface/HLTMod.h"
#include "MitAna/TreeMod/interface/ObjectCleaningMod.h"
#include "MitAna/TreeMod/interface/ElectronCleaningMod.h"
#include "MitAna/TreeMod/interface/JetCleaningMod.h"
#include "MitAna/TreeMod/interface/ElectronIDMod.h"
#include "MitAna/TreeMod/interface/MuonIDMod.h"
#include "MitAna/TreeMod/interface/JetIDMod.h"
#include "MitAna/TreeMod/interface/CatalogingMod.h"
#include "MitAna/TreeMod/interface/FullExampleMod.h"
#include "MitAna/TreeMod/interface/HLTExampleMod.h"
#include "MitAna/TreeMod/interface/SimpleExampleMod.h"
#include "MitAna/TreeMod/interface/GeneratorMod.h"
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
#pragma link C++ class mithep::HLTFwkMod+;
#pragma link C++ class mithep::HLTMod+;
#pragma link C++ class mithep::ObjectCleaningMod+;
#pragma link C++ class mithep::ElectronCleaningMod+;
#pragma link C++ class mithep::JetCleaningMod+;
#pragma link C++ class mithep::ElectronIDMod+;
#pragma link C++ class mithep::MuonIDMod+;
#pragma link C++ class mithep::JetIDMod+;
#pragma link C++ class mithep::CatalogingMod+;
#pragma link C++ class mithep::FullExampleMod+;
#pragma link C++ class mithep::SimpleExampleMod+;
#pragma link C++ class mithep::HLTExampleMod+;
#pragma link C++ class mithep::GeneratorMod+;
#endif
