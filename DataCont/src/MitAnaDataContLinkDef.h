// $Id: MitAnaDataContLinkDef.h,v 1.4 2009/02/26 17:05:19 bendavid Exp $

#ifndef MITANA_DATACONT_LINKDEF_H
#define MITANA_DATACONT_LINKDEF_H

#include "MitAna/DataCont/interface/BaseCollection.h"
#include "MitAna/DataCont/interface/FastArray.h"
#include "MitAna/DataCont/interface/FastArrayBasic.h"
#include "MitAna/DataCont/interface/ProcIDRef.h"
#include "MitAna/DataCont/interface/RefResolver.h"
#include "MitAna/DataCont/interface/StackArray.h"
#include "MitAna/DataCont/interface/StackArrayBasic.h"
#endif

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::BaseCollection+;
#pragma link C++ class mithep::RefResolver+;
#pragma link C++ class mithep::ProcIDRef-;
#pragma link C++ class mithep::Collection<mithep::ProcIDRef>+;
#pragma link C++ class mithep::FastArray<mithep::ProcIDRef>-;
#pragma link C++ class mithep::FastArrayBasic<UInt_t>-;
#endif
