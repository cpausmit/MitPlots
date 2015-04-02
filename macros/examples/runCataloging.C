// $Id: runCataloging.C,v 1.3 2008/07/28 23:13:43 paus Exp $

#if !defined(__CLING__) || defined(__ROOTCLING__)
#include <TROOT.h>
#include <TSystem.h>
#include "MitAna/DataUtil/interface/Debug.h"
#include "MitAna/Catalog/interface/Catalog.h"
#include "MitAna/Catalog/interface/Dataset.h"
#include "MitAna/TreeMod/interface/CatalogingMod.h"
#include "MitAna/TreeMod/interface/Analysis.h"
#endif

using namespace mithep;

const Int_t   gNFilesPerSet = 5;
const TString slash   = "/";

void catalogData(const char *dir, Int_t iFileSet = 0);
void catalogFile(const char *dir, const char *file, Int_t iFileSet = 0);
void reset();

Analysis      *gAna(0);
CatalogingMod *gMod(0);

//--------------------------------------------------------------------------------------------------
void runCataloging(const char *dataBaseDir = "/castor/cern.ch/user/p/paus",
		   const char *book        = "filler/006",
		   const char *dataset     = "s8-ttbar-mg-id9")
{
  // -----------------------------------------------------------------------------------------------
  // This script runs a full cataloging action on the given directory
  // -----------------------------------------------------------------------------------------------
  gDebugMask        = Debug::kNone;
  gDebugLevel       = 1;
  gErrorIgnoreLevel = kWarning;

  // create information per files
  TString fullDir = dataBaseDir +slash+ book +slash+ dataset;

  TString cmd     = TString("ls -1 ")+fullDir;
  if (fullDir.BeginsWith("/castor/"))
    cmd = TString("nsls ")+fullDir;

  Char_t dummy[4096];
  Int_t i = 0;
  FILE *f = gSystem->OpenPipe(cmd.Data(),"r");
  while (fscanf(f,"%s",dummy) != EOF) {
    TString fstr(dummy);
    if (!fstr.EndsWith(".root"))
      continue;
    if (gDebugLevel > 0)
      printf(" LINE %s\n",dummy);
    reset();
    catalogFile(fullDir.Data(),fstr, i++/gNFilesPerSet);
  }
  gSystem->ClosePipe(f);

  // create information per file set
  i = 0;
  Int_t iF = 0, iFLast = 0;
  reset();
  f = gSystem->OpenPipe(cmd.Data(),"r");
  while (fscanf(f,"%s",dummy) != EOF) {
    TString fstr(dummy);
    if (!fstr.EndsWith(".root"))
      continue;
    iF = i/gNFilesPerSet;
    if (gDebugLevel > 0)
      printf(" I: %2d  ISet: %2d  ",i,i/gNFilesPerSet);

    if (iF != iFLast) {
      if (gDebugLevel > 0)
	printf(" Make catalog, and reset afterwards");
      catalogData(fullDir.Data(),iF-1);
      reset();
      iFLast = iF;
    }

    if (gDebugLevel > 0)
      printf(" Add file: %2d\n",i);
    gAna->AddFile(fullDir+slash+TString(dummy));
    i++;
  }

  if (i>0) {
    if (gDebugLevel > 0)
      printf(" Make catalog, and reset for new tasks\n");
    catalogData(fullDir.Data(),iF);
    reset();
  }

  gSystem->ClosePipe(f);

  return;
}

//--------------------------------------------------------------------------------------------------
void catalogData(const char *dir, Int_t iFileSet)
{
  // set up the modules
  gMod->SetMetaDataString(dir);
  gMod->SetNFileSet      (iFileSet);

  // set up analysis
  gAna->SetSuperModule(gMod);

  // run the analysis after successful initialisation
  gAna->Run(kFALSE);  
}

//--------------------------------------------------------------------------------------------------
void catalogFile(const char *dir, const char *file, Int_t iFileSet)
{
  // set up the modules
  gMod->SetMetaDataString(file);
  gMod->SetNFileSet      (iFileSet);

  // set up analysis
  gAna->SetSuperModule(gMod);
  gAna->AddFile(TString(dir)+slash+TString(file));

  // run the analysis after successful initialisation
  gAna->Run(kFALSE);  
}

//--------------------------------------------------------------------------------------------------
void reset()
{
  // reset pointers
  if (gAna)
    delete gAna;
  gAna = new Analysis();
  gAna->SetUseHLT(0);
  if (gMod)
    delete gMod;
  gMod = new CatalogingMod();
}
