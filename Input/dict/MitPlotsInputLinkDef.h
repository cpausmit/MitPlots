// $Id: MitPlotsInputLinkDef.h,v 1.1.2.1 2010/10/03 04:08:48 paus Exp $

#ifndef MITPLOTS_INPUT_LINKDEF_H
#define MITPLOTS_INPUT_LINKDEF_H
#include "MitPlots/Input/interface/Sample.h"
#include "MitPlots/Input/interface/TaskSamples.h"
#endif

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::Sample+;
#pragma link C++ class std::vector<mithep::Sample>+;
#pragma link C++ class mithep::TaskSamples+;
#endif
