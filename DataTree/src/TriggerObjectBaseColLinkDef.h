// $Id: TriggerObjectColLinkDef.h,v 1.1 2009/06/15 15:00:16 loizides Exp $

#ifndef MITANA_DATATREE_TRIGGEROBJECTBASECOLLINKDEF_H
#define MITANA_DATATREE_TRIGGEROBJECTBASECOLLINKDEF_H

#include "MitAna/DataTree/interface/TriggerObjectBaseCol.h"
#endif

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::TriggerObjectBase+;
#pragma link C++ class mithep::Collection<mithep::TriggerObjectBase>+;
#pragma link C++ class mithep::Array<mithep::TriggerObjectBase>+;
#pragma link C++ typedef mithep::TriggerObjectBaseCol;
#pragma link C++ typedef mithep::TriggerObjectBaseArr;
#pragma link C++ typedef mithep::TriggerObjectBaseOArr;
#endif
