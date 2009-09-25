// $Id: PixelHitColLinkDef.h,v 1.1 2009/06/15 15:00:16 loizides Exp $

#ifndef MITANA_DATATREE_PIXELHITCOLLINKDEF_H
#define MITANA_DATATREE_PIXELHITCOLLINKDEF_H

#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/PixelHitCol.h"
#endif

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::PixelHit+;
#pragma link C++ class mithep::Collection<mithep::PixelHit>+;
#pragma link C++ class mithep::Array<mithep::PixelHit>+;
#pragma link C++ class mithep::ObjArray<mithep::PixelHit>+;
#pragma link C++ class mithep::Ref<mithep::PixelHit>+;
#pragma link C++ typedef mithep::PixelHitCol;
#pragma link C++ typedef mithep::PixelHitArr;
#endif
