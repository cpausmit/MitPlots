// $Id: L1TriggerMaskColLinkDef.h,v 1.1 2009/11/19 14:06:53 loizides Exp $

#ifndef MITANA_DATATREE_L1TRIGGERMASKCOLLINKDEF_H
#define MITANA_DATATREE_L1TRIGGERMASKCOLLINKDEF_H

#include "MitAna/DataTree/interface/L1TriggerMaskCol.h"
#endif

#ifndef __CLING__
#   define _R__UNIQUEIDENTIFIER_ L1TriggerMaskCol
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

#pragma link C++ class mithep::L1TriggerMask+;
#pragma link C++ class mithep::Collection<mithep::L1TriggerMask>+;
#pragma link C++ class mithep::Array<mithep::L1TriggerMask>+;
#pragma link C++ class mithep::ObjArray<mithep::L1TriggerMask>+;
#pragma link C++ typedef mithep::L1TriggerMaskCol;
#pragma link C++ typedef mithep::L1TriggerMaskArr;
#pragma link C++ typedef mithep::L1TriggerMaskOArr;
#endif
