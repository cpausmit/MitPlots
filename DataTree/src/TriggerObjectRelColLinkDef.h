// $Id: TriggerObjectRelColLinkDef.h,v 1.1 2009/07/13 09:42:15 loizides Exp $

#ifndef MITANA_DATATREE_TRIGGEROBJECTRELCOLLINKDEF_H
#define MITANA_DATATREE_TRIGGEROBJECTRELCOLLINKDEF_H

#include "MitAna/DataTree/interface/TriggerObjectRelCol.h"
#endif

#ifndef __CINT__
#   define _R__UNIQUEIDENTIFIER_ TriggerObjectRelCol
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

#pragma link C++ class mithep::TriggerObjectRel+;
#pragma link C++ class mithep::Collection<mithep::TriggerObjectRel>+;
#pragma link C++ class mithep::Array<mithep::TriggerObjectRel>+;
#pragma link C++ typedef mithep::TriggerObjectRelCol;
#pragma link C++ typedef mithep::TriggerObjectRelArr;
#pragma link C++ typedef mithep::TriggerObjectRelOArr;
#endif
