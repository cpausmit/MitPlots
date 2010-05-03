// $Id: Catalog.cc,v 1.5 2009/01/20 09:13:57 loizides Exp $

#include "MitAna/Catalog/interface/Catalog.h"
#include <TSystem.h>
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
  UInt_t  nLumiSecs=0, nEvents=0;
  UInt_t  nMaxRun=0, nMaxLumiSecMaxRun=0, nMinRun=0, nMinLumiSecMinRun=0;
  FILE   *f=0;

  Dataset *ds = new Dataset(dataset);

  // Read the locations and parameters of the different filesets
  f = gSystem->OpenPipe(cmdFilesets.Data(),"r");
  while (fscanf(f,"%s %s %u %u %u %u %u %u",fset,location,
		&nLumiSecs,&nEvents,&nMaxRun,&nMaxLumiSecMaxRun,&nMinRun,&nMinLumiSecMinRun)
	 != EOF) {
    MDB(kGeneral,1)
      printf(" --> %s %s %u %u %u %u %u %u\n",fset,location,
	     nLumiSecs,nEvents,nMaxRun,nMaxLumiSecMaxRun,nMinRun,nMinLumiSecMinRun);
    FilesetMetaData *fs = new FilesetMetaData(fset,location);
    ds->AddFileset(fs);
    delete fs;
  }
  gSystem->ClosePipe(f);

  // Read the parameters for each file
  f = gSystem->OpenPipe(cmdFiles.Data(),"r");
  while (fscanf(f,"%s %s %u %u %u %u %u %u",fset,file,
		&nLumiSecs,&nEvents,&nMaxRun,&nMaxLumiSecMaxRun,&nMinRun,&nMinLumiSecMinRun)
	 != EOF) {
    MDB(kGeneral,1)
      printf(" --> %s %s %u %u %u %u %u %u\n",fset,file,
	     nLumiSecs,nEvents,nMaxRun,nMaxLumiSecMaxRun,nMinRun,nMinLumiSecMinRun);
    BaseMetaData  b(nLumiSecs,nEvents,nMaxRun,nMaxLumiSecMaxRun,nMinRun,nMinLumiSecMinRun);
    FileMetaData *f = new FileMetaData(file,&b);
    ds->AddFile(fset,f);
    delete f;
  }
  gSystem->ClosePipe(f);

  return ds;
}
