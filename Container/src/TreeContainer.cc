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
  fPrinting(false),
  tempFile(0),
  tempTree(0),
  fTreeName("events"),
  fTree(0),
  fOutputFileName("output.root"),
  fSkimmingTrees(false)
{

  // Constructor
  fFileList.resize(0);
  fKeepBranches.resize(0);

}

//--------------------------------------------------------------------
TreeContainer::~TreeContainer()
{
  delete fTree;

  for (UInt_t i0 = 0; i0 < fFileList.size(); i0++) {
    if (fFileList[i0]->IsOpen())
      fFileList[i0]->Close();

    delete fFileList[i0];
  }
}

//--------------------------------------------------------------------
void
TreeContainer::AddFile(TString fileName)
{
  tempFile = TFile::Open(fileName);
  if (fPrinting)
    std::cout << "File: " << tempFile << std::endl;

  if (tempFile != NULL)
    fFileList.push_back(tempFile);

}

//--------------------------------------------------------------------
void
TreeContainer::AddDirectory(TString directoryName,TString searchFor)
{
  TString tempName;
  TSystemDirectory *dir = new TSystemDirectory(directoryName,directoryName);
  TList *fileNameList = dir->GetListOfFiles();
  for (Int_t i0 = 0; i0 < fileNameList->GetEntries(); i0++) {
    TNamed *tempMember = (TNamed*) fileNameList->At(i0);
    TString tempName = TString(tempMember->GetName());
    if (tempName.Contains(searchFor)) {
      if (fPrinting)
        std::cout << "Opening " << tempName << std::endl;

      tempFile = TFile::Open(directoryName+"/"+tempName);
      if (tempFile != NULL)
        fFileList.push_back(tempFile);
    }
  }
  delete dir;
}

//--------------------------------------------------------------------
TTree*
TreeContainer::SkimTree(TTree *tree, Bool_t inFile)
{
  tree->SetBranchStatus("*",0);
  for (UInt_t i0 = 0; i0 < fKeepBranches.size(); i0++)
    tree->SetBranchStatus(fKeepBranches[i0],1);

  if (not inFile)
    gROOT->cd();

  TTree *outTree = tree->CloneTree();
  return outTree;
}

//--------------------------------------------------------------------
TTree*
TreeContainer::ReturnTree(TString Name, Bool_t inFile)
{
  if (Name != "")
    SetTreeName(Name);

  TList *treeList = new TList;
  for (UInt_t i0 = 0; i0 < fFileList.size(); i0++) {
    if (fTreeName.Contains("/"))
      tempTree = (TTree*) fFileList[i0]->Get(fTreeName);
    else
      tempTree = (TTree*) fFileList[i0]->FindObjectAny(fTreeName);

    if (fPrinting)
      std::cout << "Getting " << fTreeName << " from " << fFileList[i0]->GetName() << std::endl;

    if (fSkimmingTrees)
      tempTree = SkimTree(tempTree,false);
    treeList->Add(tempTree);
  }

  gROOT->cd();

  if (treeList->GetEntries() > 1)
    fTree = TTree::MergeTrees(treeList);
  else if (treeList->GetEntries() == 1)
    fTree = tempTree;
  else
    fTree = NULL;

  delete treeList;
  return fTree;
}

//--------------------------------------------------------------------
std::vector<TTree*>
TreeContainer::ReturnTreeList(TString Name)
{
  if (Name != "")
    SetTreeName(Name);

  fTreeList.resize(0);

  for (UInt_t i0 = 0; i0 < fFileList.size(); i0++) {
    if (fTreeName.Contains("/"))
      tempTree = (TTree*) fFileList[i0]->Get(fTreeName);
    else
      tempTree = (TTree*) fFileList[i0]->FindObjectAny(fTreeName);

    if(fPrinting)
      std::cout << "Getting " << fTreeName << " from " << fFileList[i0]->GetName() << std::endl;

    if(fSkimmingTrees)
      tempTree = SkimTree(tempTree,false);
    fTreeList.push_back(tempTree);
  }
  return fTreeList;
}

//--------------------------------------------------------------------
void
TreeContainer::MakeFile(TString fileName, TString treeName)
{
  if (fileName != "")
    SetOutputFileName(fileName);

  if (treeName != "")
    SetTreeName(treeName);

  TFile *outFile = new TFile(fOutputFileName,"RECREATE");
  TTree *outTree = ReturnTree(fTreeName,true);
  outFile->cd();
  outTree->Write();
  outFile->Close();
  delete outFile;
}
