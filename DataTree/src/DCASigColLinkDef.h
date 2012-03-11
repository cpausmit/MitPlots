#ifndef MITANA_DATATREE_EMBEDWEIGHTCOLLINKDEF_H
#define MITANA_DATATREE_EMBEDWEIGHTCOLLINKDEF_H

#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/DCASigCol.h"
#endif

#ifndef __CINT__
#   define _R__UNIQUEIDENTIFIER_ DCASigCol
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

#pragma link C++ class mithep::DCASig+;
#pragma link C++ class mithep::Collection<mithep::DCASig>+;
#pragma link C++ class mithep::Array<mithep::DCASig>+;
#pragma link C++ class mithep::ObjArray<mithep::DCASig>+;
#pragma link C++ class mithep::Ref<mithep::DCASig>+;
#pragma link C++ typedef mithep::DCASigCol;
#pragma link C++ typedef mithep::DCASigArr;
#pragma link C++ typedef mithep::DCASigOArr;
#endif
