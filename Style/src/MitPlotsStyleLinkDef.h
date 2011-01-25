// $Id: MitPlotsStyleLinkDef.h,v 1.1.2.1 2010/10/03 04:08:50 paus Exp $

#ifndef MITPLOTS_STYLE_LINKDEF_H
#define MITPLOTS_STYLE_LINKDEF_H
#include "MitPlots/Style/interface/MitStyle.h"
#include "MitPlots/Style/interface/HistStyle.h"
#include "MitPlots/Style/interface/HistStyles.h"
#endif

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::MitStyle+;
#pragma link C++ class mithep::HistStyle+;
#pragma link C++ class std::vector<mithep::HistStyle>+;
#pragma link C++ class mithep::HistStyles+;
#endif
