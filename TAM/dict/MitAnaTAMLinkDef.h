//
// $Id: MitAnaTAMLinkDef.h,v 1.1 2008/05/27 19:13:21 loizides Exp $
//
//

#ifndef __MitAnaTreeModLinkDef__
#define __MitAnaTreeModLinkDef__

#include "MitAna/TAM/interface/TAMBranchInfo.h"
#include "MitAna/TAM/interface/TAModule.h"
#include "MitAna/TAM/interface/TAMObjBranchLoader.h"
#include "MitAna/TAM/interface/TAMObjLoader.h"
#include "MitAna/TAM/interface/TAMOutput.h"
#include "MitAna/TAM/interface/TAMSelector.h"
#include "MitAna/TAM/interface/TAMTreeBranchLoader.h"
#include "MitAna/TAM/interface/TAMTreeLoader.h"
#include "MitAna/TAM/interface/TAMVirtualBranchLoader.h"
#include "MitAna/TAM/interface/TAMVirtualLoader.h"

#endif

#ifdef __CLING__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ nestedclasses;

#pragma link C++ class TAMBranchInfo+;
#pragma link C++ class TAModule+;
#pragma link C++ enum  TAModule::EModResult;
#pragma link C++ class TAMOutput+;
#pragma link C++ class TAMOutput::TAMModInspector-;
#pragma link C++ class TAMOutput::TAMModInspector::TAMModMember+;
#pragma link C++ class TAMSelector+;
#pragma link C++ class TAMTreeLoader+;
#pragma link C++ class TAMTreeBranchLoader+;
#pragma link C++ class TAMVirtualLoader+;
#pragma link C++ class TAMVirtualBranchLoader+;
#pragma link C++ class TAMObjLoader+;
#pragma link C++ class TAMObjBranchLoader+;

#endif
