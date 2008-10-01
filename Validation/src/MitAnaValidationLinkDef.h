// $Id: MitAnaValidationLinkDef.h,v 1.1 2008/07/10 14:56:27 loizides Exp $

#ifndef RELVALMODS_LINKDEF_H
#define RELVALMODS_LINKDEF_H
#include "MitAna/Validation/interface/GenRelValMod.h"
#include "MitAna/Validation/interface/JetValidationMod.h"
#endif

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::GenRelValMod+;
#pragma link C++ class mithep::JetValidationMod+;
#endif
