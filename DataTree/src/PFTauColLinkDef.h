// $Id:$

#ifndef MITANA_DATATREE_PFTAUCOLLINKDEF_H
#define MITANA_DATATREE_PFTAUCOLLINKDEF_H

#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/PFTauCol.h"
#endif

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::PFTau+;
#pragma link C++ class mithep::Collection<mithep::PFTau>+;
#pragma link C++ class mithep::Array<mithep::PFTau>+;
#pragma link C++ class mithep::ObjArray<mithep::PFTau>+;
#pragma link C++ class mithep::Ref<mithep::PFTau>+;
#pragma link C++ typedef mithep::PFTauCol;
#pragma link C++ typedef mithep::PFTauArr;
#pragma link C++ typedef mithep::PFTauOArr;
#endif
