// $Id:$

#ifndef MITANA_DATATREE_DECAYDATACOLLINKDEF_H
#define MITANA_DATATREE_DECAYDATACOLLINKDEF_H

#include "MitAna/DataTree/interface/DecayDataCol.h"
#endif

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::DecayData+;
#pragma link C++ class mithep::Collection<mithep::DecayData>+;
#pragma link C++ class mithep::Array<mithep::DecayData>+;
#pragma link C++ typedef mithep::DecayDataCol;
#pragma link C++ typedef mithep::DecayDataArr;
#endif
