// $Id: ElectronColLinkDef.h,v 1.1 2009/06/15 15:00:15 loizides Exp $

#ifndef MITANA_DATATREE_ELECTRONCOLLINKDEF_H
#define MITANA_DATATREE_ELECTRONCOLLINKDEF_H

#include "MitAna/DataCont/interface/Ref.h"
#include "MitAna/DataTree/interface/ElectronCol.h"
#endif

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma read                                              \
    sourceClass="mithep::Electron"                        \
    version="[-2]"                                        \
    source="dummysource"                                  \
    targetClass="mithep::Electron"                        \
    target="fCharge"                                      \
    code="{ fCharge = -99; }"                             \


#pragma link C++ class mithep::Electron+;
#pragma link C++ class mithep::Collection<mithep::Electron>+;
#pragma link C++ class mithep::Array<mithep::Electron>+;
#pragma link C++ class mithep::ObjArray<mithep::Electron>+;
#pragma link C++ class mithep::Ref<mithep::Electron>+;
#pragma link C++ typedef mithep::ElectronCol;
#pragma link C++ typedef mithep::ElectronArr;
#pragma link C++ typedef mithep::ElectronOArr;
#endif
