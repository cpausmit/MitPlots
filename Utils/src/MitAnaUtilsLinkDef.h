// $Id: MitAnaUtilsLinkDef.h,v 1.2 2009/08/11 23:09:28 loizides Exp $

#ifndef MITANA_UTILS_LINKDEF_H
#define MITANA_UTILS_LINKDEF_H
#include "MitAna/Utils/interface/MyHtml.h"
#include "MitAna/Utils/interface/SimpleTable.h"
#endif

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class MyHtml+;
#pragma link C++ class MyHtml::MyModDef+;
#pragma link C++ class mithep::SimpleTable+;
#pragma link C++ class mithep::SimpleTable::MyParameter+;
#endif
