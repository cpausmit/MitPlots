// $Id:$

#ifndef MITANA_DATATREE_GENJETCOLLINKDEF_H
#define MITANA_DATATREE_GENJETCOLLINKDEF_H

#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/GenJetCol.h"
#endif

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::GenJet+;
#pragma link C++ class mithep::Collection<mithep::GenJet>+;
#pragma link C++ class mithep::Array<mithep::GenJet>+;
#pragma link C++ class mithep::ObjArray<mithep::GenJet>+;
#pragma link C++ class mithep::Ref<mithep::GenJet>+;
#pragma link C++ typedef mithep::GenJetCol;
#pragma link C++ typedef mithep::GenJetArr;
#pragma link C++ typedef mithep::GenJetOArr;
#endif
