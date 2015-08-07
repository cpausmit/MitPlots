// $Id: MitPlotsPlotLinkDef.h,v 1.1.2.1 2010/10/03 04:08:49 paus Exp $

#ifndef MITPLOTS_PLOT_LINKDEF_H
#define MITPLOTS_PLOT_LINKDEF_H
#include "MitPlots/Plot/interface/PlotTask.h"
#include "MitPlots/Plot/interface/PlotBase.h"
#include "MitPlots/Plot/interface/PlotHists.h"
#include "MitPlots/Plot/interface/PlotResolution.h"
#include "MitPlots/Plot/interface/PlotROC.h"
#endif

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace mithep;

#pragma link C++ class mithep::PlotTask+;
#pragma link C++ class mithep::PlotBase+;
#pragma link C++ class mithep::PlotHists+;
#pragma link C++ class mithep::PlotResolution+;
#pragma link C++ class mithep::PlotROC+;
#endif
