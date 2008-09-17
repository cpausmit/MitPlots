// $Id: runObjectCleaner.C,v 1.1 2008/08/08 11:23:17 sixie Exp $

#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TBasket.h>
#include <TCanvas.h>
#include <TPie.h>

#include "MitAna/DataUtil/interface/Debug.h"
#include "MitAna/TreeMod/interface/Analysis.h"
#endif


extern "C" void R__zip (Int_t cxlevel, Int_t *nin, char *bufin, Int_t *lout, char *bufout, Int_t *nout);

//--------------------------------------------------------------------------------------------------
Long64_t RawBytes(TBranch* branch, UInt_t recursion=0) {

  //Long64_t rawCurrentBasketSize = 0;
 // if (recursion==0)
//    rawCurrentBasketSize = branch->GetTotalSize() - branch->GetTotBytes();
    
  //TBasket* currentBasket = branch->GetBasket(branch->GetReadBasket());
  //currentBasket->SetWriteMode();
  //rawCurrentBasketSize = currentBasket->WriteBuffer();

  //branch->WriteBasket(currentBasket);

  //branch->Print();
  


//branch->Print();
 // if (currentBasket->GetNevBuf())
    //rawCurrentBasketSize = currentBasket->GetBufferRef()->Length();
   // rawCurrentBasketSize = currentBasket->GetObjlen();
  //Long64_t altRawBasketSize = currentBasket->GetBufferRef()->Length();

  Long64_t totBytes = branch->GetTotBytes();
  //Long64_t totBytes = branch->GetTotBytes() + altRawBasketSize;
  TObjArray *subBranches = branch->GetListOfBranches();
  for (UInt_t i = 0; i<subBranches->GetEntries(); ++i) {
    TBranch *subBranch = (TBranch*)subBranches->At(i);
    totBytes += RawBytes(subBranch, recursion+1);
  }
  return totBytes;
}

Long64_t ZipBytes(TBranch* branch, Double_t ratio, UInt_t recursion=0) {

  Long64_t zipBytes = branch->GetZipBytes();


  
  TBasket* currentBasket = branch->GetBasket(branch->GetReadBasket());
  currentBasket->SetWriteMode();
  branch->WriteBasket(currentBasket);
  //Long64_t zipBasketSize = currentBasket->GetNbytes();
  
  //printf("Simple basket raw size = %i\n", rawCurrentBasketSize);
  //printf("objlen basket raw size = %i\n", altRawBasketSize);
  
 // Int_t basketSize = branch->GetBasketSize();
  
  //Long64_t basketZipEstimate = TMath::Min(((Double_t)rawCurrentBasketSize)/ratio, (Double_t)basketSize);
  //printf("basket zip estimate = %i\n",basketZipEstimate);

  Long64_t totBytes = branch->GetZipBytes();
  //Long64_t totBytes = branch->GetZipBytes() + altRawBasketSize;
  TObjArray *subBranches = branch->GetListOfBranches();
  for (UInt_t i = 0; i<subBranches->GetEntries(); ++i) {
    TBranch *subBranch = (TBranch*)subBranches->At(i);
    totBytes += ZipBytes(subBranch, ratio, recursion+1);
  }
  return totBytes;
}

Long64_t TotSize(TBranch* branch) {
  Long64_t totBytes = branch->GetTotalSize();
  TObjArray *subBranches = branch->GetListOfBranches();
  for (UInt_t i = 0; i<subBranches->GetEntries(); ++i) {
    TBranch *subBranch = (TBranch*)subBranches->At(i);
    //totBytes += TotSize(subBranch);
  }
  return totBytes;
}


void AppendPrefix(TBranch* branch, std::string prefix) {
  //branch->GetTree()->SetBranchStatus(branch->GetName(),1);
  //branch->ResetBit(kDoNotProcess);
  std::string name = prefix + branch->GetName();
  branch->SetName(name.c_str());
  TObjArray *subBranches = branch->GetListOfBranches();
  for (UInt_t i = 0; i<subBranches->GetEntries(); ++i) {
    TBranch *subBranch = (TBranch*)subBranches->At(i);
    AppendPrefix(subBranch, prefix);
  }
  
  return;

}

void treeSizeVal(const char *file = "/server/02a/bendavid/OAK/XX-MITDATASET-XX_000.root")
{
  using namespace mithep;
  gDebugMask  = Debug::kAnalysis;
  gDebugLevel = 1;

  TFile *infile = new TFile(file,"READ");
  //TFile *tmpfile = new TFile("/tmp/bendavid/tmpfile.root","RECREATE");

  TTree *events = (TTree*)infile->Get("Events");
  TTree *runs = (TTree*)infile->Get("Runs");
  TTree *fwMetaData = (TTree*)infile->Get("FWMetaData");

  //TPie fileRaw, fileZip;
  
  const char **treeLabels = new const char*[3];
  treeLabels[0] = "Events";
  treeLabels[1] = "Runs";
  treeLabels[2] = "FWMetaData";
  
  Double_t rawTreeSizes[] = { events->GetTotBytes(), runs->GetTotBytes(), fwMetaData->GetTotBytes() };
  Double_t zipTreeSizes[] = { events->GetZipBytes(), runs->GetZipBytes(), fwMetaData->GetZipBytes() };

  TPie *fileRaw = new TPie("fileRaw", "Top Level Tree Sizes - Raw", 3, rawTreeSizes);
  fileRaw->SetLabels(treeLabels);
  new TCanvas();
  fileRaw->Draw("3d");

  TPie *fileZip = new TPie("fileZip", "Top Level Tree Sizes - Compressed", 3, zipTreeSizes);
  fileZip->SetLabels(treeLabels);
  new TCanvas();
  fileZip->Draw("3d");
  
  Long64_t eventsRawSize = events->GetTotBytes();
  Long64_t eventsZipSize = events->GetZipBytes();

  Double_t eventsCompression = (Double_t)eventsRawSize/eventsZipSize;

  infile->Cp(file, "tmpFile.root");
  infile->Close();
  TFile *tmpfile = new TFile("tmpFile.root","UPDATE");

  events = (TTree*)tmpfile->Get("Events");  

  TObjArray *evtBranches = events->GetListOfBranches();
  UInt_t nBranches = evtBranches->GetEntries();
  UInt_t nEvents = events->GetEntries();

  Double_t *rawBranchSizes = new Double_t[nBranches];
  Double_t *zipBranchSizes = new Double_t[nBranches];
  const char **branchLabels = new const char*[nBranches];

  Double_t *rawDataBranchSizes = new Double_t[nBranches];
  Double_t *zipDataBranchSizes = new Double_t[nBranches];

  
  

  

  
  
  Long64_t rawTotal = 0;
  Long64_t zipTotal = 0;
  
  Long64_t zipDataTotal=0;
  
  for (UInt_t i=0; i<nBranches; ++i) {
  
    
    TBranch* branch = (TBranch*)evtBranches->At(i);
//     events->SetBranchStatus("*",0);
//     const char* branchName = branch->GetName();
//     std::string prefix = branchName;
//     prefix += "-SpaceVal-";
//     AppendPrefix(branch,prefix);
//     
//     std::string branchSearch = prefix + "*";
//     events->SetBranchStatus(branchSearch.c_str(),1);
    
    //TFile *tmpFile = new TFile("tmpFile.root","RECREATE");

    //branch->SetFile(tmpFile);

    //TBasket* basket = branch->GetBasket(branch->GetReadBasket());

    //basket->SetWriteMode();
   // basket->WriteBuffer();

    //basket->WriteFile(1, tmpFile);

  //  branch->Print();

//    tmpFile->Close();

    //TTree *eventSubset = events->CloneTree();
    //TTree *eventSubset = events;
    
    //tmpFile->Write();
    //tmpFile->Close();
   // eventSubset->Write();
   // eventSubset->Print();
    
    //Long64_t branchSizeRaw = eventSubset->GetTotBytes();
   // Long64_t branchSizeZip = eventSubset->GetTotBytes();
    

    
     //Long64_t branchSizeTotal = TotSize(branch);
    
     Long64_t branchSizeZip = ZipBytes(branch, eventsCompression);
     Long64_t branchSizeRaw = RawBytes(branch);

    rawTotal += branchSizeRaw;
    zipTotal += branchSizeZip;
    
    
     printf("%s BranchSizeRaw = %i\n",branch->GetName(),branchSizeRaw);
     printf("%s BranchSizeZip = %i\n",branch->GetName(),branchSizeZip);
//     //printf("%s BranchSizeZipSimple = %i\n",branch->GetName(),branchSizeZipSimple);
//     printf("%s BranchSizeTotal = %i\n",branch->GetName(),branchSizeTotal);
    rawBranchSizes[i] = (Double_t)branchSizeRaw/nEvents/1024.0;
    zipBranchSizes[i] = (Double_t)branchSizeZip/nEvents/1024.0;
    branchLabels[i] = branch->GetName();

    if (i!=1) {
     rawDataBranchSizes[i] = (Double_t)branchSizeRaw/nEvents/1024.0;
     zipDataBranchSizes[i] = (Double_t)branchSizeZip/nEvents/1024.0;
     zipDataTotal+=branchSizeZip;

    }
    
    
    //tmpFile->Close();

  }
  
  printf("Event Size Raw = %i\n" , eventsRawSize);
  printf("Total Raw Size = %i\n", rawTotal);
  
  printf("Event Size Zip = %i\n" , eventsZipSize);
  printf("Total Zip Size = %i\n", zipTotal);
  
  Double_t avgEvent = (Double_t)zipTotal/nEvents/1024.0;
  printf("Average Event Size = %f kBytes\n",avgEvent);
  
  Double_t avgDataEvent = (Double_t)zipDataTotal/nEvents/1024.0;
  printf("Average Event Size (data) = %f kBytes\n",avgDataEvent);


  TPie *branchRaw = new TPie("branchRaw", "Event Branch Sizes  - Raw", nBranches, rawBranchSizes);
  branchRaw->SetLabels(branchLabels);
  new TCanvas();
  branchRaw->Draw("3d");

  TPie *branchZip = new TPie("branchZip", "Event Branch Sizes  - Zip", nBranches, zipBranchSizes);
  branchZip->SetLabels(branchLabels);
  branchZip->SetLabelsOffset(0.1);
  branchZip->SetLabelFormat("#splitline{%val (%perc)}{%txt}");
  new TCanvas();
  branchZip->Draw("3dr");

  TPie *branchDataRaw = new TPie("branchDataRaw", "Event Branch Sizes  - Raw", nBranches, rawDataBranchSizes);
  branchDataRaw->SetLabels(branchLabels);
  
  new TCanvas();
  branchDataRaw->Draw("3d");

  TPie *branchDataZip = new TPie("branchDataZip", "Event Branch Sizes  - Zip", nBranches, zipDataBranchSizes);
  branchDataZip->SetLabels(branchLabels);
  branchDataZip->SetLabelsOffset(0.1);
  branchDataZip->SetLabelFormat("#splitline{%val (%perc)}{%txt}");

  new TCanvas();
  branchDataZip->Draw("3dr");

    //tmpfile->Close();

}
