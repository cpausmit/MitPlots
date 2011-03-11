// $Id: StripHitColLinkDef.h,v 1.1 2009/11/25 00:14:52 loizides Exp $

#ifndef MITANA_DATATREE_STRIPHITCOLLINKDEF_H
#define MITANA_DATATREE_STRIPHITCOLLINKDEF_H

#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/StripHitCol.h"
#endif

#ifndef __CINT__
#   define _R__UNIQUEIDENTIFIER_ StripHitCol
#   define _R__JOIN3_(F,X,Y) _NAME3_(F,X,Y)
#   undef _R__UNIQUE_
#   define _R__UNIQUE_(X) _R__JOIN3_( _R__UNIQUEIDENTIFIER_,X,__LINE__)
#endif

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::StripHit+;
#pragma link C++ class mithep::Collection<mithep::StripHit>+;
#pragma link C++ class mithep::Array<mithep::StripHit>+;
#pragma link C++ class mithep::ObjArray<mithep::StripHit>+;
#pragma link C++ class mithep::Ref<mithep::StripHit>+;
#pragma link C++ typedef mithep::StripHitCol;
#pragma link C++ typedef mithep::StripHitArr;
#endif
