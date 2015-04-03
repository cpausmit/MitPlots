// $Id:$

#ifndef MITANA_DATATREE_METCOLLINKDEF_H
#define MITANA_DATATREE_METCOLLINKDEF_H

#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/MetCol.h"
#endif

#ifdef __CLING__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::Met+;
#pragma link C++ class mithep::Collection<mithep::Met>+;
#pragma link C++ class mithep::Array<mithep::Met>+;
#pragma link C++ class mithep::ObjArray<mithep::Met>+;
#pragma link C++ class mithep::Ref<mithep::Met>+;
#pragma link C++ typedef mithep::MetCol;
#pragma link C++ typedef mithep::MetArr;
#pragma link C++ typedef mithep::MetOArr;
#endif
