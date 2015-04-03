// $Id: StableDataColLinkDef.h,v 1.1 2009/06/15 15:00:15 loizides Exp $

#ifndef MITANA_DATATREE_STABLEDATACOLLINKDEF_H
#define MITANA_DATATREE_STABLEDATACOLLINKDEF_H

#include "MitAna/DataTree/interface/StableDataCol.h"
#endif

#ifndef __CLING__
#   define _R__UNIQUEIDENTIFIER_ StableDataCol
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

#pragma link C++ class mithep::StableData+;
#pragma link C++ class mithep::Collection<mithep::StableData>+;
#pragma link C++ class mithep::Array<mithep::StableData>+;
#pragma link C++ class mithep::ObjArray<mithep::StableData>+;
#pragma link C++ typedef mithep::StableDataCol;
#pragma link C++ typedef mithep::StableDataArr;
#pragma link C++ typedef mithep::StableDataOArr;
#endif
