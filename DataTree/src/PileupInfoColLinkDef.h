// $Id: PileupInfoColLinkDef.h,v 1.1 2009/06/15 15:00:15 loizides Exp $

#ifndef MITANA_DATATREE_PILEUPINFOCOLLINKDEF_H
#define MITANA_DATATREE_PILEUPINFOCOLLINKDEF_H

#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/PileupInfoCol.h"
#endif

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::PileupInfo+;
#pragma link C++ class mithep::Collection<mithep::PileupInfo>+;
#pragma link C++ class mithep::Array<mithep::PileupInfo>+;
#pragma link C++ class mithep::ObjArray<mithep::PileupInfo>+;
#pragma link C++ class mithep::Ref<mithep::PileupInfo>+;
#pragma link C++ typedef mithep::PileupInfoCol;
#pragma link C++ typedef mithep::PileupInfoArr;
#pragma link C++ typedef mithep::PileupInfoOArr;
#endif
