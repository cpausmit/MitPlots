// $Id: MitAnaDataContLinkDef.h,v 1.6 2009/03/02 14:56:42 loizides Exp $

#ifndef MITANA_DATACONT_LINKDEF_H
#define MITANA_DATACONT_LINKDEF_H

#include "MitAna/DataCont/interface/BaseCollection.h"
#include "MitAna/DataCont/interface/FastArray.h"
#include "MitAna/DataCont/interface/FastArrayBasic.h"
#include "MitAna/DataCont/interface/ProcIDRef.h"
#include "MitAna/DataCont/interface/RefResolver.h"
#include "MitAna/DataCont/interface/Types.h"
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

#pragma link C++ class mithep::FastArrayBasic<Double_t>-;
#pragma link C++ class mithep::FastArrayBasic<Double32_t,kTRUE>-;
#pragma link C++ class mithep::FastArrayBasic<Int_t>-;
#pragma link C++ class mithep::FastArrayBasic<UInt_t>-;

#pragma link C++ typedef mithep::FArrDouble;
#pragma link C++ typedef mithep::FArrDouble32;
#pragma link C++ typedef mithep::FArrInt;
#pragma link C++ typedef mithep::FArrUInt;
#endif
