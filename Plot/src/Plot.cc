//--------------------------------------------------------------------------------------------------
// Perform a plot task using a specified set of samples. Nice and clean.
//
// Authors: C.Paus                                                                        (Aug 2010)
//--------------------------------------------------------------------------------------------------
#include <TROOT.h>
#include <iostream>
#include "TH1.h"
#include "TFile.h"
#include "TSystem.h"
#include "TLatex.h"
#include "TPostScript.h"
#include "TStyle.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "MitPlots/Style/interface/MitStyle.h"
#include "MitPlots/Input/interface/TaskSamples.h"
#include "MitPlots/Plot/interface/PlotTask.h"
#include "MitPlots/Plot/interface/Plot.h"

using namespace std;
using namespace mithep;

//==================================================================================================
void plot(const char *name, const char *filename, const char* title, int logy,
	  double xmin, double xmax, double ymin, double ymax,
	  int nRebin, double lumi, TString draw, TString cut, int nbins,
	  const TH1D *putarget, bool stack)
{
  stack = kFALSE;

  // use logarithmic scale?
  TCanvas *canvas = new TCanvas;
  canvas->SetLogy(logy);

  // read all environment variables
  TString home     = getEnv("HOME");
  TString mitMyAna = getEnv("MIT_USER_DIR");
  TString hstDir   = getEnv("MIT_ANA_HIST");
  TString anaCfg   = getEnv("MIT_ANA_CFG");
  TString prdCfg   = getEnv("MIT_PROD_CFG");

  // define sample
  TaskSamples* samples = new TaskSamples(prdCfg.Data(),hstDir.Data());
  samples->SetNameTxt(anaCfg.Data());
  samples->ReadFile((mitMyAna + TString("/config")).Data());

  // plot what we want
  PlotTask   *plotTask = new PlotTask(samples,lumi);
  plotTask->SetPuTarget(putarget);
  // adjust ranges if needed
  if (xmin!=0)
    plotTask->SetHistXMinimum(xmin);
  if (xmax!=0)
    plotTask->SetHistXMaximum(xmax);
  if (ymin!=0)
    plotTask->SetHistMinimum(ymin);
  if (ymax>0)
    plotTask->SetHistMaximum(ymax);
  // rebinning
  plotTask->SetNRebin     (nRebin);

  plotTask->SetNBins(nbins);
  plotTask->SetDrawExp(draw,cut);

  // set the titles
  plotTask->SetAxisTitles(title,"Number of Events");

  if (stack)
    plotTask->PlotStack("",name);
  else
    plotTask->PlotContributions("",name);

  canvas->SaveAs((TString(filename)+TString(".png")).Data());

  return;
}

TString getEnv(const char* name)
{
  if (! gSystem->Getenv(name)) {
    printf(" Environment variable: %s  not defined. EXIT!\n",name);
    return TString("");
  } 
  return TString(gSystem->Getenv(name));  
}
