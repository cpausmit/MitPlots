// $Id: LinkDef.h 2272 2006-01-08 17:16:44Z loizides $

#ifndef DATAUTIL_LINKDEF_H
#define DATAUTIL_LINKDEF_H
#include "MitAna/DataUtil/interface/Debug.h"
#include "MitAna/DataUtil/interface/TreeWriter.h"
#endif

#ifdef __CINT__
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
#endif
