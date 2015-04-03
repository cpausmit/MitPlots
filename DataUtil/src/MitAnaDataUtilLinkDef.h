// $Id: MitAnaDataUtilLinkDef.h,v 1.1 2008/05/27 19:36:05 loizides Exp $

#ifndef MITANA_DATAUTIL_LINKDEF_H
#define MITANA_DATAUTIL_LINKDEF_H
#include "MitAna/DataUtil/interface/Debug.h"
#include "MitAna/DataUtil/interface/TreeWriter.h"
#include "MitAna/DataUtil/interface/Cacher.h"
#endif

#ifdef __CLING__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::Debug;
#pragma link C++ enum  mithep::Debug::EDebugMask;
#pragma link C++ global gDebugMask;
#pragma link C++ global gDebugLevel;
#pragma link C++ class mithep::TreeWriter+;
#pragma link C++ class mithep::Cacher+;
#endif
