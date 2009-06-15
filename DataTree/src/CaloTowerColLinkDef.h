// $Id:$

#ifndef MITANA_DATATREE_CALOTOWERCOLLINKDEF_H
#define MITANA_DATATREE_CALOTOWERCOLLINKDEF_H

#include "MitAna/DataCont/interface/RefArray.h"
#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/CaloTowerCol.h"
#endif

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::CaloTower+;
#pragma link C++ class mithep::Collection<mithep::CaloTower>+;
#pragma link C++ class mithep::Array<mithep::CaloTower>+;
#pragma link C++ class mithep::ObjArray<mithep::CaloTower>+;
#pragma link C++ class mithep::Ref<mithep::CaloTower>+;
#pragma link C++ class mithep::RefArray<mithep::CaloTower>+;
#pragma link C++ typedef mithep::CaloTowerCol;
#pragma link C++ typedef mithep::CaloTowerArr;
#pragma link C++ typedef mithep::CaloTowerOArr;
#endif
