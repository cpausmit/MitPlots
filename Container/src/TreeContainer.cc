#include <iostream>

#include "TROOT.h"
#include "TSystem.h"
#include "TList.h"
#include "TSystemDirectory.h"
#include "MitPlots/Container/interface/TreeContainer.h"

using namespace mithep;

ClassImp(mithep::TreeContainer)

//--------------------------------------------------------------------
TreeContainer::TreeContainer() :
  fPrinting(true),
  tempFile(0),
  tempTree(0),
  fTreeName("events"),
  fTree(0)
{

  // Constructor
  fFileList.resize(0);

}

//--------------------------------------------------------------------
TreeContainer::~TreeContainer()
{

  delete fTree;

  for(UInt_t i0 = 0; i0 < fFileList.size(); i0++){
    if(fFileList[i0]->IsOpen()) fFileList[i0]->Close();
  }

}

//--------------------------------------------------------------------
void
TreeContainer::AddFile(TString fileName){

  tempFile = TFile::Open(fileName);
  if(tempFile != NULL)
    fFileList.push_back(tempFile);

}

//--------------------------------------------------------------------
void
TreeContainer::AddDirectory(TString directoryName,TString searchFor){
  TString tempName;
  TSystemDirectory *dir = new TSystemDirectory(directoryName,directoryName);
  TList *fileNameList = dir->GetListOfFiles();
  for(Int_t i0 = 0; i0 < fileNameList->GetEntries(); i0++){
    TNamed *tempMember = (TNamed*) fileNameList->At(i0);
    TString tempName = TString(tempMember->GetName());
    if(tempName.Contains(searchFor)){
      if(fPrinting) std::cout << "Opening " << tempName << std::endl;
      tempFile = TFile::Open(directoryName+"/"+tempName);
      if(tempFile != NULL)
        fFileList.push_back(tempFile);
    }
  }
}

//--------------------------------------------------------------------
TTree*
TreeContainer::ReturnTree(TString Name){

  if(Name != "") SetTreeName(Name);
  TList *treeList = new TList;

  for(UInt_t i0 = 0; i0 < fFileList.size(); i0++){
    if(fTreeName.Contains("/")) tempTree = (TTree*) fFileList[i0]->Get(fTreeName);
    else tempTree = (TTree*) fFileList[i0]->FindObjectAny(fTreeName);
    if(fPrinting) std::cout << "Getting " << fTreeName << " from " << fFileList[i0]->GetName() << std::endl;
    treeList->Add(tempTree);
  }

  gROOT->cd();

  if(treeList->GetEntries() > 1) fTree = TTree::MergeTrees(treeList);
  else if(treeList->GetEntries() == 1) fTree = tempTree;
  else fTree = NULL;

  return fTree;

}

//--------------------------------------------------------------------
std::vector<TTree*>
TreeContainer::ReturnTreeList(TString Name){

  if(Name != "") SetTreeName(Name);
  fTreeList.resize(0);

  for(UInt_t i0 = 0; i0 < fFileList.size(); i0++){
    if(fTreeName.Contains("/")) tempTree = (TTree*) fFileList[i0]->Get(fTreeName);
    else tempTree = (TTree*) fFileList[i0]->FindObjectAny(fTreeName);
    if(fPrinting) std::cout << "Getting " << fTreeName << " from " << fFileList[i0]->GetName() << std::endl;
    fTreeList.push_back(tempTree);
  }

  return fTreeList;

}
