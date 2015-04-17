// $Id: BaseVertexColLinkDef.h,v 1.1 2009/06/15 15:00:14 loizides Exp $

#ifndef MITANA_DATATREE_BASEVERTEXCOLLINKDEF_H
#define MITANA_DATATREE_BASEVERTEXCOLLINKDEF_H

#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/BaseVertexCol.h"
#endif

#ifndef __CLING__
#   define _R__UNIQUEIDENTIFIER_ BaseVertexCol
#   define _R__JOIN3_(F,X,Y) _NAME3_(F,X,Y)
#   undef _R__UNIQUE_
#   define _R__UNIQUE_(X) _R__JOIN3_( _R__UNIQUEIDENTIFIER_,X,__LINE__)
#endif

#ifdef __CLING__
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
