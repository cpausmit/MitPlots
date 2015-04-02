// $Id: JetColLinkDef.h,v 1.1 2009/06/15 15:00:15 loizides Exp $

#ifndef MITANA_DATATREE_JETCOLLINKDEF_H
#define MITANA_DATATREE_JETCOLLINKDEF_H

#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/JetCol.h"
#endif

#ifndef __CLING__
#   define _R__UNIQUEIDENTIFIER_ JetCol
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

#pragma link C++ class mithep::Jet+;
#pragma link C++ class mithep::Collection<mithep::Jet>+;
#pragma link C++ class mithep::Array<mithep::Jet>+;
#pragma link C++ class mithep::ObjArray<mithep::Jet>+;
#pragma link C++ class mithep::Ref<mithep::Jet>+;
#pragma link C++ typedef mithep::JetCol;
#pragma link C++ typedef mithep::JetArr;
#pragma link C++ typedef mithep::JetOArr;
#endif
