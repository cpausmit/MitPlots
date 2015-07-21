#ifndef MITPLOTS_TOOLS_LINKDEF_H
#define MITPLOTS_TOOLS_LINKDEF_H

#include "MitPlots/Tools/interface/Skimmer.h"
#endif

#ifdef __CLING__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::Skimmer+;
#endif
