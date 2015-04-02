#if !defined(__CLING__) || defined(__ROOTCLING__)
#include <TROOT.h>
#include <TSystem.h>
#include <TFile.h>
#include <TTree.h>
#include <TKey.h>
#include <TH1D.h>
#endif

const TString slash      = "/";
const TString dCacheDoor = "dcap://t2srv0012.cmsaf.mit.edu/";
//const TString dCacheDoor = "dcap://t2srv0005.cmsaf.mit.edu/";
const TString hadoopDoor = "root://xrootd.cmsaf.mit.edu/";

void catalogFile(const char *dir, const char *file);
void reset();

//--------------------------------------------------------------------------------------------------
void runSimpleFileCataloger(const char *dir  = "/mnt/hadoop/cms/store/user/paus/fabstoec/Summer11Private/TTH_HToGG_M-120_TuneZ2_7TeV-pythia6/Summer11-PU32_8CM_START42_V13C-v4/GEN-SIM-RECO",
			    const char *file = "")
{
  // -----------------------------------------------------------------------------------------------
  // This script runs a full cataloging action on the given directory
  // -----------------------------------------------------------------------------------------------
  reset();
  catalogFile(dir,file);
  return;
}

//--------------------------------------------------------------------------------------------------
void catalogFile(const char *dir, const char *file)
{
  TString fileName = TString(dir) + slash +  + TString(file);
  //printf("Index: %d\n",fileName.Index("castor/cern.ch"));
  if (fileName.Index("castor/cern.ch") != -1)
    fileName = TString("castor:") + fileName;
  if (fileName.Index("pnfs/cmsaf.mit.edu") != -1) {
    fileName = dCacheDoor + fileName;
  }
  if (fileName.Index("mnt/hadoop/cms/store") != -1) {
    fileName.Remove(0,15);
    fileName = hadoopDoor + fileName;
  }
  
  printf("\n Opening: %s\n\n",fileName.Data());
  TFile* f       = TFile::Open(fileName.Data());

  TTree* tree = (TTree*) f->FindObjectAny("Delphes");
  if (tree) {
    printf("0000 %s %.0f %.0f\n",fileName.Data(),tree->GetEntries(),tree->GetEntries());
    return;
  }

  Bool_t done = kFALSE;
  tree    = (TTree*) f->FindObjectAny("Events");
  if (tree) {
    printf("XX-CATALOG-XX %s %.0f\n",fileName.Data(),tree->GetEntries());
    done = kTRUE;
  }

  TTree* allTree = (TTree*) f->FindObjectAny("AllEvents");
  if (tree && allTree) {
    printf("XX-CATALOG-XX %s %.0f %.0f\n",fileName.Data(),tree->GetEntries(),allTree->GetEntries());
    done = kTRUE;
  }
  
  if (!done) {
    TString hname="hDEvents";
    f->cd("AnaFwkMod");
    TH1D *h = (TH1D*) f->FindObjectAny(hname);
    if (h)
      printf("XX-CATALOG-XX %s %.0f %.0f\n",fileName.Data(),h->GetEntries(),h->GetEntries());
  }

}

//--------------------------------------------------------------------------------------------------
void reset()
{
}

//// file from F.
//void runSimpleFileCataloger(TString dir = "root://xroot.cmsaf.mit.edu/store/user/paus/fabstoec/Summer11Private//TTH_HToGG_M-120_TuneZ2_7TeV-pythia6/Summer11-PU32_8CM_START42_V13C-v4/GEN-SIM-RECO",
//		 TString fileName="SUM11-HGGPRIV-0540-4890-0018.root") {
// 
//  TString fullName = dir+TString("/") +fileName;
//  TFile*  file     = TFile::Open(fullName.Data());
//  TTree*  tree     = (TTree*) file->FindObjectAny("Events");
//  std::cout << tree->GetEntries() << std::endl;
//}
