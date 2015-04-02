// $Id:$

#ifndef MITANA_DATATREE_VERTEXCOLLINKDEF_H
#define MITANA_DATATREE_VERTEXCOLLINKDEF_H

#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/VertexCol.h"
#endif

#ifdef __CLING__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::Vertex+;
#pragma link C++ class mithep::Collection<mithep::Vertex>+;
#pragma link C++ class mithep::Array<mithep::Vertex>+;
#pragma link C++ class mithep::ObjArray<mithep::Vertex>+;
#pragma link C++ class mithep::Ref<mithep::Vertex>+;
#pragma link C++ typedef mithep::VertexCol;
#pragma link C++ typedef mithep::VertexArr;
#endif
