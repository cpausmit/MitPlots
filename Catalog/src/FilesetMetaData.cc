// $Id: $

#include <iostream>
#include "MitAna/Catalog/interface/FilesetMetaData.h"

using namespace std;
using namespace mithep;

//--------------------------------------------------------------------------------------------------
FilesetMetaData::FilesetMetaData(const char *filesetName, const char* location) :
  BaseMetaData(),
  fFilesetName(filesetName),
  fLocation   (location)
{
  // Constructor
}

void FilesetMetaData::AddFile(FileMetaData *f)
{
  Add(f);
  fFileList.push_back(*f);
}

void FilesetMetaData::Print() const
{
  cout << "   Printing contents of fileset: " << fFilesetName.Data()
       << " - location: " << fLocation.Data() << endl
       << "   - Metadata: ";
  BaseMetaData::Print();

  for (UInt_t i=0; i<fFileList.size(); i++)
    fFileList[i].Print();
}
