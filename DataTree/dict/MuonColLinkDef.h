#ifndef MITANA_DATATREE_MUONCOLLINKDEF_H
#define MITANA_DATATREE_MUONCOLLINKDEF_H

#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/MuonCol.h"
#endif

#ifndef __CLING__
#   define _R__UNIQUEIDENTIFIER_ MuonCol
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

#pragma link C++ class mithep::Muon+;
#pragma link C++ enum mithep::Muon::EClassType;
#pragma link C++ class mithep::Collection<mithep::Muon>+;
#pragma link C++ class mithep::Array<mithep::Muon>+;
#pragma link C++ class mithep::ObjArray<mithep::Muon>+;
#pragma link C++ class mithep::Ref<mithep::Muon>+;
#pragma link C++ typedef mithep::MuonCol;
#pragma link C++ typedef mithep::MuonArr;
#pragma link C++ typedef mithep::MuonOArr;
#endif
