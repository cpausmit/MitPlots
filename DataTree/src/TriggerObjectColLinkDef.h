// $Id: TriggerObjectColLinkDef.h,v 1.1 2009/06/15 15:00:16 loizides Exp $

#ifndef MITANA_DATATREE_TRIGGEROBJECTCOLLINKDEF_H
#define MITANA_DATATREE_TRIGGEROBJECTCOLLINKDEF_H

#include "MitAna/DataTree/interface/TriggerObjectCol.h"
#endif

#ifdef __CINT__
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
