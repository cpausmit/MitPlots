// $Id:$

#ifndef MITANA_DATATREE_PFMETCOLLINKDEF_H
#define MITANA_DATATREE_PFMETCOLLINKDEF_H

#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/PFMetCol.h"
#endif

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::PFMet+;
#pragma link C++ class mithep::Collection<mithep::PFMet>+;
#pragma link C++ class mithep::Array<mithep::PFMet>+;
#pragma link C++ class mithep::ObjArray<mithep::PFMet>+;
#pragma link C++ class mithep::Ref<mithep::PFMet>+;
#pragma link C++ typedef mithep::PFMetCol;
#pragma link C++ typedef mithep::PFMetArr;
#pragma link C++ typedef mithep::PFMetOArr;
#endif
