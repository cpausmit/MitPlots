// $Id: MitAnaDataContLinkDef.h,v 1.12 2010/06/29 15:51:53 bendavid Exp $

#ifndef MITANA_DATACONT_LINKDEF_H
#define MITANA_DATACONT_LINKDEF_H

#include "MitAna/DataCont/interface/BaseCollection.h"
#include "MitAna/DataCont/interface/BitMask.h"
#include "MitAna/DataCont/interface/CacheFlag.h"
#include "MitAna/DataCont/interface/FastArray.h"
#include "MitAna/DataCont/interface/FastArrayBasic.h"
#include "MitAna/DataCont/interface/ObjArray.h"
#include "MitAna/DataCont/interface/ProcIDRef.h"
#include "MitAna/DataCont/interface/RefResolver.h"
#include "MitAna/DataCont/interface/RunLumiRangeMap.h"
#include "MitAna/DataCont/interface/RunLumiSet.h"
#include "MitAna/DataCont/interface/Types.h"
#endif


// typedef UInt_t unsignedint;
// typedef UChar_t unsignedchar;
// typedef UShort_t unsignedshort;
// typedef ULong64_t unsignedlonglong;


#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::BaseCollection+;

#pragma link C++ class mithep::BitMaskT<UChar_t>+;
#pragma link C++ class mithep::BitMaskT<UShort_t>+;
#pragma link C++ class mithep::BitMaskT<UInt_t>+;
#pragma link C++ class mithep::BitMask<6>+;
#pragma link C++ class mithep::BitMaskT<ULong64_t>+;
#pragma link C++ class mithep::BitMask<16>+;
#pragma link C++ class mithep::BitMask<32>+;
#pragma link C++ typedef mithep::BitMask8;
#pragma link C++ typedef mithep::BitMask16;
#pragma link C++ typedef mithep::BitMask32;
#pragma link C++ typedef mithep::BitMask48;
#pragma link C++ typedef mithep::BitMask64;
#pragma link C++ typedef mithep::BitMask128;
#pragma link C++ typedef mithep::BitMask256; 

#pragma link C++ class mithep::CacheFlag-;
#pragma link C++ class mithep::RefResolver+;
#pragma link C++ class mithep::ProcIDRef-;

#pragma link C++ class mithep::Collection<mithep::ProcIDRef>+;
#pragma link C++ class mithep::FastArray<mithep::ProcIDRef>-;
#pragma link C++ class mithep::FastArrayBasic<Double_t>-;
#pragma link C++ class mithep::FastArrayBasic<Double32_t,kTRUE>-;
#pragma link C++ class mithep::FastArrayBasic<Int_t>-;
#pragma link C++ class mithep::FastArrayBasic<UInt_t>-;
#pragma link C++ class mithep::FastArrayBasic<Short_t>-;
#pragma link C++ class mithep::FastArrayBasic<UShort_t>-;
#pragma link C++ class mithep::FastArrayBasic<Char_t>-;
#pragma link C++ class mithep::FastArrayBasic<UChar_t>-;
#pragma link C++ typedef mithep::FArrDouble;
#pragma link C++ typedef mithep::FArrDouble32;
#pragma link C++ typedef mithep::FArrInt;
#pragma link C++ typedef mithep::FArrUInt;

#pragma link C++ class mithep::Collection<TObject>+;
#pragma link C++ class mithep::ObjArray<TObject>+;

#pragma link C++ class std::pair<UInt_t,UInt_t>+;
#pragma link C++ class std::set<std::pair<UInt_t,UInt_t> >+;

#pragma link C++ typedef mithep::RunLumiSet::RunLumiPairType;
#pragma link C++ typedef mithep::RunLumiSet::SetType;

#pragma link C++ class mithep::RunLumiRangeMap+;
#pragma link C++ class mithep::RunLumiSet+;

#endif
