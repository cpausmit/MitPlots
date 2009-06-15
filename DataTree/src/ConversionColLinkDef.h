// $Id:$

#ifndef MITANA_DATATREE_CONVERSIONCOLLINKDEF_H
#define MITANA_DATATREE_CONVERSIONCOLLINKDEF_H

#include "MitAna/DataCont/interface/RefArray.h"
#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/ConversionCol.h"
#endif

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::Conversion+;
#pragma link C++ class mithep::Collection<mithep::Conversion>+;
#pragma link C++ class mithep::Array<mithep::Conversion>+;
#pragma link C++ class mithep::ObjArray<mithep::Conversion>+;
#pragma link C++ class mithep::Ref<mithep::Conversion>+;
#pragma link C++ class mithep::RefArray<mithep::Conversion>+;
#pragma link C++ typedef mithep::ConversionCol;
#pragma link C++ typedef mithep::ConversionArr;
#pragma link C++ typedef mithep::ConversionOArr;
#endif
