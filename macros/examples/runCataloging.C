// $Id: runCataloging.C,v 1.2 2008/07/08 05:52:09 loizides Exp $

#if !defined(__CINT__) || defined(__MAKECINT__)
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

void catalogData(const char *dir, int iFileSet = 0);
void catalogFile(const char *dir, const char *file, int iFileSet = 0);
void reset();

Analysis      *gAna(0);
CatalogingMod *gMod(0);

//--------------------------------------------------------------------------------------------------
void runCataloging(const char *catalogDir  = "/home/mitprod/catalog",
		   const char *dataBaseDir = "/server/03b/paus",
		   const char *book        = "filler/000",
		   const char *dataset     = "jpsi-csa08-10pb")
{
  // -----------------------------------------------------------------------------------------------
  // This script runs a full cataloging action on the given directory
  // -----------------------------------------------------------------------------------------------
  gDebugMask        = Debug::kNone;
<<<<<<< runCataloging.C
  gDebugLevel       = 0;
=======
  gDebugLevel       = 1;
>>>>>>> 1.2
  gErrorIgnoreLevel = kWarning;

<<<<<<< runCataloging.C
  // Create information per files
  TString fullDir = dataBaseDir +slash+ book +slash+ dataset;
=======
  // create information per files
  TString fullDir = baseDir +slash+ book +slash+ dataset;
>>>>>>> 1.2
  TString cmd     = TString("ls -1 ")+fullDir;
  char    file[1000];
  int i = 0;
  FILE* f = gSystem->OpenPipe(cmd.Data(),"r");
  while (fscanf(f,"%s",file) != EOF) {
    if (gDebugLevel > 0)
      printf(" LINE %s\n",file);
    reset();
    catalogFile(fullDir.Data(),file, i++/gNFilesPerSet);
  }
  gSystem->ClosePipe(f);

  // create information per file set
  i = 0;
  int iF = 0, iFLast = 0;
  reset();
  f = gSystem->OpenPipe(cmd.Data(),"r");
  while (fscanf(f,"%s",file) != EOF) {
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
    gAna->AddFile(fullDir+slash+TString(file));
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
void catalogData(const char *dir, int iFileSet)
{
  // set up the modules
  gMod->SetMetaDataString(dir);
  gMod->SetNFileSet      (iFileSet);

  // set up analysis
  gAna->SetSuperModule(gMod);

  // run the analysis after successful initialisation
  gAna->Run(false);  
}

//--------------------------------------------------------------------------------------------------
void catalogFile(const char *dir, const char *file, int iFileSet)
{
  // set up the modules
  gMod->SetMetaDataString(file);
  gMod->SetNFileSet      (iFileSet);

  // set up analysis
  gAna->SetSuperModule(gMod);
  gAna->AddFile(TString(dir)+slash+TString(file));

  // run the analysis after successful initialisation
  gAna->Run(false);  
}

//--------------------------------------------------------------------------------------------------
void reset()
{
  // reset pointers
  if (gAna)
    delete gAna;
  gAna = new Analysis();
  if (gMod)
    delete gMod;
  gMod = new CatalogingMod();
}
