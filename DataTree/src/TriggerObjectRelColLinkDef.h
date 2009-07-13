// $Id: TriggerObjectColLinkDef.h,v 1.1 2009/06/15 15:00:16 loizides Exp $

#ifndef MITANA_DATATREE_TRIGGEROBJECTRELCOLLINKDEF_H
#define MITANA_DATATREE_TRIGGEROBJECTRELCOLLINKDEF_H

#include "MitAna/DataTree/interface/TriggerObjectRelCol.h"
#endif

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::TriggerObjectRel+;
#pragma link C++ class mithep::Collection<mithep::TriggerObjectRel>+;
#pragma link C++ class mithep::Array<mithep::TriggerObjectRel>+;
#pragma link C++ typedef mithep::TriggerObjectRelCol;
#pragma link C++ typedef mithep::TriggerObjectRelArr;
#pragma link C++ typedef mithep::TriggerObjectRelOArr;
#endif
