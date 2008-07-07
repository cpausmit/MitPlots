// $Id: Catalog.cc,v 1.1 2008/07/07 16:41:52 paus Exp $

#include <TROOT.h>
#include <TSystem.h>
#include "MitAna/DataUtil/interface/Debug.h"
#include "MitAna/Catalog/interface/Catalog.h"
#include "MitAna/Catalog/interface/Dataset.h"

using namespace mithep;

//--------------------------------------------------------------------------------------------------
Catalog::Catalog(const char *location) : 
  fLocation(location)
{
  // Constructor
}

//--------------------------------------------------------------------------------------------------
Dataset *Catalog::FindDataset(const char *book, const char *dataset)
{
  // Try to find the given dataset in the catalog and return it properly filled.

  TString slash        = "/";
  TString fullDir      = fLocation +slash+ TString(book) +slash+ TString(dataset);
  TString cmdFilesets  = TString("cat ")+fullDir+slash+TString("Filesets | grep -v ^#");
  TString cmdFiles     = TString("cat ")+fullDir+slash+TString("Files    | grep -v ^#");

  char    file[6], fset[60], location[100];
  UInt_t  nLumiSecs=0, nEvents=0;
  UInt_t  nMaxRun=0, nMaxLumiSecMaxRun=0, nMinRun=0, nMinLumiSecMinRun=0;
  FILE   *f;

  Dataset *ds = new Dataset(dataset);

  // Read the locations and parameters of the different filesets
  f = gSystem->OpenPipe(cmdFilesets.Data(),"r");
  while (fscanf(f,"%s %s %d %d %d %d %d %d",fset,location,
		&nLumiSecs,&nEvents,&nMaxRun,&nMaxLumiSecMaxRun,&nMinRun,&nMinLumiSecMinRun)
	 != EOF) {
    MDB(kGeneral,1)
      printf(" --> %s %s %d %d %d %d %d %d\n",fset,location,
	     nLumiSecs,nEvents,nMaxRun,nMaxLumiSecMaxRun,nMinRun,nMinLumiSecMinRun);
    FilesetMetaData *fs = new FilesetMetaData(fset,location);
    ds->AddFileset(fs);
  }
  gSystem->ClosePipe(f);

  // Read the parameters for each file
  f = gSystem->OpenPipe(cmdFiles.Data(),"r");
  while (fscanf(f,"%s %s %d %d %d %d %d %d",fset,file,
		&nLumiSecs,&nEvents,&nMaxRun,&nMaxLumiSecMaxRun,&nMinRun,&nMinLumiSecMinRun)
	 != EOF) {
    MDB(kGeneral,1)
      printf(" --> %s %s %d %d %d %d %d %d\n",fset,file,
	     nLumiSecs,nEvents,nMaxRun,nMaxLumiSecMaxRun,nMinRun,nMinLumiSecMinRun);
    BaseMetaData  b(nLumiSecs,nEvents,nMaxRun,nMaxLumiSecMaxRun,nMinRun,nMinLumiSecMinRun);
    FileMetaData *f = new FileMetaData(file,&b);
    ds->AddFile(fset,f);
  }
  gSystem->ClosePipe(f);

  return ds;
}
