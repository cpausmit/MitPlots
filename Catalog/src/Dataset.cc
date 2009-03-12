// $Id: Dataset.cc,v 1.2 2008/07/08 05:50:57 loizides Exp $

#include "MitAna/Catalog/interface/Dataset.h"
#include <Riostream.h>

ClassImp(mithep::Dataset)

using namespace std;
using namespace mithep;

//--------------------------------------------------------------------------------------------------
Dataset::Dataset(const char *name) : 
  BaseMetaData(),
  fName       (name),
  fNFiles     (0)
{
  // Constructor
}

//--------------------------------------------------------------------------------------------------
void Dataset::AddFile(const char *filesetName, const FileMetaData *f)
{
  // Add a file to a fileset.

  TString name(filesetName);
  for (UInt_t i=0; i<fFilesetList.size(); i++) {
    if (filesetName == *fFilesetList[i].FilesetName()) {
      fNFiles++;
      Add(f);
      fFilesetList[i].AddFile(f);
      break;
    }
  }
}

//--------------------------------------------------------------------------------------------------
void Dataset::AddFileset(const FilesetMetaData *f)
{
  // Add a fileset.

  Add(f);
  fFilesetList.push_back(*f);
  fNFiles += f->NFiles();
}

//--------------------------------------------------------------------------------------------------
const FileMetaData *Dataset::File(UInt_t iFile) const
{
  // Get filename corresponding to given file number.

  if (iFile >= fNFiles)
    return 0;

  UInt_t localI = iFile;
  for (UInt_t i=0; i<fFilesetList.size(); i++) {    
    if (localI < fFilesetList[i].NFiles())
      return fFilesetList[i].File(localI);
    else
      localI -= fFilesetList[i].NFiles();
  }
  
  return 0;
}

//--------------------------------------------------------------------------------------------------
const char *Dataset::FileUrl(UInt_t iFile) const
{
  // Get url corresponding to given file number.

  TString slash("/");
  TString url("");
  if (iFile >= fNFiles)
    return url.Data();

  UInt_t localI = iFile;
  for (UInt_t i=0; i<fFilesetList.size(); i++) {    
    if (localI < fFilesetList[i].NFiles()) {
      url = *fFilesetList[i].Location() + slash + *fFilesetList[i].File(localI)->FileName();
      break;
    }
    else
      localI -= fFilesetList[i].NFiles();
  }
  
  return url.Data();
}

//--------------------------------------------------------------------------------------------------
void Dataset::Print() const
{
  // Print useful information.

  cout << endl << " Printing contents of dataset: " << fName << endl << " - Metadata: ";
  BaseMetaData::Print();
  for (UInt_t i=0; i<fFilesetList.size(); i++) {
    cout << endl;
    fFilesetList[i].Print();
  }
  cout << endl;
}
