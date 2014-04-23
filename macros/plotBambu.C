//--------------------------------------------------------------------------------------------------
// Test plots created out of Bambu ntuples.
//
// Authors: L.Di Matteo                                                                   (Mar 2014)
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
void plotBambu()
{

  // open input bambu file
  //TFile* inputFile = new TFile("/mnt/hadoop/cms/store/user/paus/filefi/032/r12b-smu-j22-v1/00022801-5771-E211-913C-E0CB4E1A1194.root","READ");
  TFile* inputFile = new TFile("./bambu_000.root","READ");
  TTree* inputTree = (TTree*) inputFile->Get("Events");
  
  // test plotting of collections size
  TCanvas *canSize = new TCanvas();
  inputTree->Draw("Muons->GetEntries()");

  // test plotting of object quantities
  TCanvas *canPtMuon = new TCanvas();
  inputTree->Draw("Muons->At(0)->Pt()","Muons->GetEntries() > 1");

  // test cutting on object quantities
  TCanvas *canPtMuonTrack = new TCanvas();
  inputTree->Draw("Muons->At(0)->GlobalTrk()->Pt()","Muons->GetEntries() > 1 && Muons->At(0)->HasGlobalTrk()");

  return;
}
