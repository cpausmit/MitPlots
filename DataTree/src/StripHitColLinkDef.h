// $Id: PixelHitColLinkDef.h,v 1.1 2009/09/25 08:39:11 loizides Exp $

#ifndef MITANA_DATATREE_STRIPHITCOLLINKDEF_H
#define MITANA_DATATREE_STRIPHITCOLLINKDEF_H

#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/StripHitCol.h"
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
