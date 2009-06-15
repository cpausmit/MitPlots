// $Id:$

#ifndef MITANA_DATATREE_DAUGHTERDATACOLLINKDEF_H
#define MITANA_DATATREE_DAUGHTERDATACOLLINKDEF_H

#include "MitAna/DataCont/interface/RefArray.h"
#include "MitAna/DataTree/interface/DaughterDataCol.h"
#endif

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::DaughterData+;
#pragma link C++ class mithep::Collection<mithep::DaughterData>+;
#pragma link C++ class mithep::ObjArray<mithep::DaughterData>+;
#pragma link C++ class mithep::RefArray<mithep::DaughterData>+;
#pragma link C++ typedef mithep::DaughterDataCol;
#pragma link C++ typedef mithep::DaughterDataOArr;
#endif
