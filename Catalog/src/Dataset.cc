// $Id: $

#include <iostream>
#include "MitAna/Catalog/interface/Dataset.h"

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

void Dataset::AddFileset(FilesetMetaData *f)
{
  Add(f);
  fFilesetList.push_back(*f);
  fNFiles += f->NFiles();
}

void Dataset::AddFile(const char *filesetName, FileMetaData *f)
{
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

const FileMetaData *Dataset::File(UInt_t iFile) const
{
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

const char *Dataset::FileUrl(UInt_t iFile) const
{
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

void Dataset::Print() const
{
  cout << endl << " Printing contents of dataset: " << fName << endl << " - Metadata: ";
  BaseMetaData::Print();
  for (UInt_t i=0; i<fFilesetList.size(); i++) {
    cout << endl;
    fFilesetList[i].Print();
  }
  cout << endl;

}
