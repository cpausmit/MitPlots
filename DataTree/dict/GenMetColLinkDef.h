// $Id: GenMetColLinkDef.h,v 1.1 2009/07/14 13:46:12 bendavid Exp $

#ifndef MITANA_DATATREE_GENMETCOLLINKDEF_H
#define MITANA_DATATREE_GENMETCOLLINKDEF_H

#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/GenMetCol.h"
#endif

#ifndef __CLING__
#   define _R__UNIQUEIDENTIFIER_ GenMetCol
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

#pragma link C++ class mithep::GenMet+;
#pragma link C++ class mithep::Collection<mithep::GenMet>+;
#pragma link C++ class mithep::Array<mithep::GenMet>+;
#pragma link C++ class mithep::ObjArray<mithep::GenMet>+;
#pragma link C++ class mithep::Ref<mithep::GenMet>+;
#pragma link C++ typedef mithep::GenMetCol;
#pragma link C++ typedef mithep::GenMetArr;
#pragma link C++ typedef mithep::GenMetOArr;
#endif
