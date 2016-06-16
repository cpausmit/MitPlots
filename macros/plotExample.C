//--------------------------------------------------------------------------------------------------
// Basic plots for FastSim versus Fullsim comparison.
//
// Authors: C.Paus                                                                       (June 2016)
//--------------------------------------------------------------------------------------------------
#include <TSystem.h>
#include "MitPlots/Style/interface/MitStyle.h"
#include "MitPlots/Plot/interface/PlotTask.h"

using namespace std;
using namespace mithep;

// our plot task                                                 // make it global to keep it around
PlotTask *plotTask;

//==================================================================================================
void plotExample(double lumi = 100.0)
{
  // Create the basic comparsion plot fullSim versus fastSim

  // set the folder containing the input ntuples properly
  // here you can change the plot sources, these are the defaults
  gSystem->Setenv("MIT_PROD_CFG","example");
  gSystem->Setenv("MIT_ANA_HIST","/home/paus/tmp");

  // setup graphics stuff before starting
  MitStyle::Init();

  // set plot config properly
  gSystem->Setenv("MIT_ANA_CFG","example");

  // softdrop mass
  plotTask = new PlotTask(0,lumi);
  plotTask->SetHistRanges(0.0,400.,0.,0.);
  plotTask->SetAxisTitles("Softdrop Mass [GeV]","Number of Events");
  plotTask->SetPngFileName("softdropMass.png");
  plotTask->Plot(Stacked,"SoftDropMassN_1","raw","no-cuts","");

  printf("\n  WARNING -- root window might not show the complete plot. Check png file first.\n\n");

  return;
}
