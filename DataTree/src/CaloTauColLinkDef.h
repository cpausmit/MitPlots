// $Id: CaloTauColLinkDef.h,v 1.1 2009/06/15 15:00:14 loizides Exp $

#ifndef MITANA_DATATREE_CALOTAUCOLLINKDEF_H
#define MITANA_DATATREE_CALOTAUCOLLINKDEF_H

#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/CaloTauCol.h"
#endif

#ifndef __CINT__
#   define _R__UNIQUEIDENTIFIER_ CaloTauCol
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

#pragma link C++ class mithep::CaloTau+;
#pragma link C++ class mithep::Collection<mithep::CaloTau>+;
#pragma link C++ class mithep::Array<mithep::CaloTau>+;
#pragma link C++ class mithep::ObjArray<mithep::CaloTau>+;
#pragma link C++ class mithep::Ref<mithep::CaloTau>+;
#pragma link C++ typedef mithep::CaloTauCol;
#pragma link C++ typedef mithep::CaloTauArr;
#pragma link C++ typedef mithep::CaloTauOArr;
#endif
