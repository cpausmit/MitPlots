// $Id: MitAnaDataUtilLinkDef.h,v 1.2 2008/10/14 05:28:21 loizides Exp $

#ifndef MITANA_UTILS_LINKDEF_H
#define MITANA_UTILS_LINKDEF_H
#include "MitAna/Utils/interface/SimpleTable.h"
#endif

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::SimpleTable+;
#pragma link C++ class mithep::SimpleTable::MyParameter+;
#endif
