// $Id: Catalog.cc,v 1.7 2010/10/01 02:20:26 paus Exp $

#include <TSystem.h>
#include "MitAna/Catalog/interface/Catalog.h"
#include "MitAna/DataUtil/interface/Debug.h"
#include "MitAna/Catalog/interface/Dataset.h"

ClassImp(mithep::Catalog)

using namespace mithep;

//--------------------------------------------------------------------------------------------------
Catalog::Catalog(const char *location) : 
  fLocation(location)
{
  // Constructor
}

//--------------------------------------------------------------------------------------------------
Dataset *Catalog::FindDataset(const char *book, const char *dataset, const char *fileset) const
{
  // Try to find the given dataset in the catalog and return it properly filled.
  // Note that the caller must delete the returned dataset.

  TString slash        = "/";
  TString fullDir      = fLocation +slash+ TString(book) +slash+ TString(dataset);
  TString cmdFilesets  = TString("cat ")+fullDir+slash+TString("Filesets | grep -v ^#");
  TString cmdFiles     = TString("cat ")+fullDir+slash+TString("Files    | grep -v ^#");

  if (!TString(fileset).IsNull()) {
    cmdFilesets += TString(" | grep ^") + TString(fileset);
    cmdFiles    += TString(" | grep ^") + TString(fileset);
  }

  char    file[1024], fset[1024], location[1024];
  UInt_t  nAllEvents=0, nEvents=0, nLumiSecs=0;
  UInt_t  nMaxRun=0, nMaxLumiSecMaxRun=0, nMinRun=0, nMinLumiSecMinRun=0;
  FILE   *fHandle=0;

  Dataset *ds = new Dataset(dataset);

  // Read the locations and parameters of the different filesets
  fHandle = gSystem->OpenPipe(cmdFilesets.Data(),"r");
  while (fscanf(fHandle,"%s %s %u %u %u %u %u %u",fset,location,
		&nAllEvents,&nEvents,//&nLumiSecs,
		&nMaxRun,&nMaxLumiSecMaxRun,&nMinRun,&nMinLumiSecMinRun)
	 != EOF) {
    MDB(kGeneral,1)
      printf(" --> %s %s %u %u %u %u %u %u\n",fset,location,
	     nAllEvents,nEvents,//nLumiSecs,
	     nMaxRun,nMaxLumiSecMaxRun,nMinRun,nMinLumiSecMinRun);
    FilesetMetaData *fs = new FilesetMetaData(fset,location);
    ds->AddFileset(fs);
    delete fs;
  }
  gSystem->ClosePipe(fHandle);

  // Read the parameters for each file
  fHandle = gSystem->OpenPipe(cmdFiles.Data(),"r");
  while (fscanf(fHandle,"%s %s %u %u %u %u %u %u",fset,file,
		&nAllEvents,&nEvents,//&nLumiSecs,
		&nMaxRun,&nMaxLumiSecMaxRun,&nMinRun,&nMinLumiSecMinRun)
	 != EOF) {
    MDB(kGeneral,1)
      printf(" --> %s %s %u %u %u %u %u %u\n",fset,file,
	     nAllEvents,nEvents,//nLumiSecs,
	     nMaxRun,nMaxLumiSecMaxRun,nMinRun,nMinLumiSecMinRun);
    BaseMetaData  b(nAllEvents,nEvents,nLumiSecs,
		    nMaxRun,nMaxLumiSecMaxRun,nMinRun,nMinLumiSecMinRun);
    FileMetaData *f = new FileMetaData(file,&b);
    ds->AddFile(fset,f);
    delete f;
  }
  gSystem->ClosePipe(fHandle);

  return ds;
}
