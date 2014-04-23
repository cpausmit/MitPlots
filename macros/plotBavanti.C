//--------------------------------------------------------------------------------------------------
// Test plots created out of Bavanti ntuples.
//
// Authors: C.Paus                                                                        (Apr 2014)
//--------------------------------------------------------------------------------------------------
#include <TSystem.h>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include "MitPlots/Style/interface/MitStyle.h"
#include "MitPlots/Plot/interface/PlotTask.h"

using namespace std;
using namespace mithep;

//==================================================================================================
void plotBavanti()
{

  // open input bambu file
  TFile* inputFile = new TFile("./bavanti_000.root","READ");
  TTree* inputTree = (TTree*) inputFile->Get("Events");
  
  // test plotting of collections size
  new TCanvas();
  inputTree->Draw("SkmMuons->GetEntries()");

  // test plotting of object quantities
  new TCanvas();
  inputTree->Draw("SkmMuons->At(0)->Pt()","SkmMuons->GetEntries() > 1");

  // test cutting on object quantities
  new TCanvas();
  inputTree->Draw("SkmMuons->At(0)->GlobalTrk()->Pt()","SkmMuons->GetEntries() > 1 && SkmMuons->At(0)->HasGlobalTrk()");

  return;
}
