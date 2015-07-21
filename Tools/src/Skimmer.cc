#include "TFile.h"
#include "MitPlots/Tools/interface/Skimmer.h"

using namespace mithep;

ClassImp(mithep::Skimmer)

//--------------------------------------------------------------------------------------------------
Skimmer::Skimmer():
  fInputTree(0),
  fOutputFileName("skim.root")
{}

//--------------------------------------------------------------------------------------------------
Skimmer::~Skimmer() {}

//--------------------------------------------------------------------------------------------------
void
Skimmer::DoSkim(){

  fInputTree->SetBranchStatus("*",0);
  for(UInt_t i0 = 0; i0 < fKeepBranches.size(); i0++){
    fInputTree->SetBranchStatus(fKeepBranches[i0],1);
  }

  TFile *outFile = new TFile(fOutputFileName,"RECREATE");
  TTree *outTree = fInputTree->CloneTree();
  outTree->Write();
  outFile->Close();

}
