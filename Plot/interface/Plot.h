//--------------------------------------------------------------------------------------------------
// Plot
//
// This is the header for the plot macro
//
// Authors: C.Paus
//--------------------------------------------------------------------------------------------------
#ifndef MITPLOTS_PLOT_H
#define MITPLOTS_PLOT_H

#include <TString.h>

void plot(const char *name, const char *filename, const char* title,
	  int logy,
	  double xmin, double xmax,
	  double ymin, double ymax,
	  int nRebin, double lumi,
	  TString variable="", TString cuts="", int nbins=100,
	  const TH1D *puTarget=0, bool stack = kTRUE);

TString getEnv(const char* name);

#endif
