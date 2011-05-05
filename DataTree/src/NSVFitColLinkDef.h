// $Id: NSVFitColLinkDef.h,v 1.2 2011/03/11 04:03:00 bendavid Exp $

#ifndef MITANA_DATATREE_NSVFITCOLLINKDEF_H
#define MITANA_DATATREE_NSVFITCOLLINKDEF_H

#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/NSVFitCol.h"
#endif

#ifndef __CINT__
#   define _R__UNIQUEIDENTIFIER_ NSVFitCol
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

#pragma link C++ class mithep::NSVFit+;
#pragma link C++ class mithep::Collection<mithep::NSVFit>+;
#pragma link C++ class mithep::Array<mithep::NSVFit>+;
#pragma link C++ class mithep::ObjArray<mithep::NSVFit>+;
#pragma link C++ class mithep::Ref<mithep::NSVFit>+;
#pragma link C++ typedef mithep::NSVFitCol;
#pragma link C++ typedef mithep::NSVFitArr;
#pragma link C++ typedef mithep::NSVFitOArr;
#endif
