// $Id: MitAnaValidationLinkDef.h,v 1.3 2008/10/14 05:27:00 loizides Exp $

#ifndef MITANA_VALIDATION_LINKDEF_H
#define MITANA_VALIDATION_LINKDEF_H
#include "MitAna/Validation/interface/GenRelValMod.h"
#include "MitAna/Validation/interface/MCParticlesValMod.h"
#include "MitAna/Validation/interface/TracksValMod.h"
#endif

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::GenRelValMod+;
#pragma link C++ class mithep::MCParticlesValMod+;
#pragma link C++ class mithep::TracksValMod+;
#endif
