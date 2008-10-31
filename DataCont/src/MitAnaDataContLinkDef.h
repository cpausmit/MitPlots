// $Id: MitAnaDataContLinkDef.h,v 1.2 2008/10/14 05:28:21 loizides Exp $

#ifndef MITANA_DATACONT_LINKDEF_H
#define MITANA_DATACONT_LINKDEF_H

#include "MitAna/DataCont/interface/BaseCollection.h"
#include "MitAna/DataCont/interface/StackArray.h"
#include "MitAna/DataCont/interface/StackArrayBasic.h"
#include "MitAna/DataCont/interface/ProcIDRef.h"
#endif

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::BaseCollection+;
#pragma link C++ class mithep::ProcIDRef-;
#pragma link C++ class mithep::Collection<mithep::ProcIDRef>+;
#pragma link C++ class mithep::StackArrayBasic<UInt_t, 32>-;
#pragma link C++ class mithep::StackArray<mithep::ProcIDRef,32>-;
#pragma link C++ class mithep::StackArrayBasic<UInt_t, 128>-;
#pragma link C++ class mithep::StackArray<mithep::ProcIDRef,128>-;
#pragma link C++ class mithep::StackArrayBasic<UInt_t, 1024>-;
#pragma link C++ class mithep::StackArray<mithep::ProcIDRef,1024>-;
#endif
