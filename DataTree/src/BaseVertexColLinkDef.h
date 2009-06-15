// $Id:$

#ifndef MITANA_DATATREE_BASEVERTEXCOLLINKDEF_H
#define MITANA_DATATREE_BASEVERTEXCOLLINKDEF_H

#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/BaseVertexCol.h"
#endif

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::BaseVertex+;
#pragma link C++ class mithep::Collection<mithep::BaseVertex>+;
#pragma link C++ class mithep::Array<mithep::BaseVertex>+;
#pragma link C++ class mithep::ObjArray<mithep::BaseVertex>+;
#pragma link C++ class mithep::Ref<mithep::BaseVertex>+;
#pragma link C++ typedef mithep::BaseVertexCol;
#pragma link C++ typedef mithep::BaseVertexArr;
#endif
