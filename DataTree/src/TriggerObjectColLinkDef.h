// $Id: TriggerObjectColLinkDef.h,v 1.2 2009/07/13 09:42:15 loizides Exp $

#ifndef MITANA_DATATREE_TRIGGEROBJECTCOLLINKDEF_H
#define MITANA_DATATREE_TRIGGEROBJECTCOLLINKDEF_H

#include "MitAna/DataTree/interface/TriggerObjectCol.h"
#endif

#ifndef __CLING__
#   define _R__UNIQUEIDENTIFIER_ TriggerObjectCol
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

#pragma link C++ class mithep::TriggerObject+;
#pragma link C++ class mithep::Collection<mithep::TriggerObject>+;
#pragma link C++ class mithep::Array<mithep::TriggerObject>+;
#pragma link C++ class mithep::ObjArray<mithep::TriggerObject>+;
#pragma link C++ typedef mithep::TriggerObjectCol;
#pragma link C++ typedef mithep::TriggerObjectArr;
#pragma link C++ typedef mithep::TriggerObjectOArr;
#pragma link C++ enum mithep::TriggerObject::ETriggerObject;
#endif
