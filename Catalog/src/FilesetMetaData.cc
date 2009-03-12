// $Id: FilesetMetaData.cc,v 1.2 2008/07/08 05:50:57 loizides Exp $

#include "MitAna/Catalog/interface/FilesetMetaData.h"
#include <Riostream.h>

ClassImp(mithep::FilesetMetaData)

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

//--------------------------------------------------------------------------------------------------
void FilesetMetaData::AddFile(const FileMetaData *f)
{
  // Add file to fileset.

  Add(f);
  fFileList.push_back(*f);
}

//--------------------------------------------------------------------------------------------------
void FilesetMetaData::Print() const
{
  // Print useful information.

  cout << "   Printing contents of fileset: " << fFilesetName.Data()
       << " - location: " << fLocation.Data() << endl
       << "   - Metadata: ";
  BaseMetaData::Print();

  for (UInt_t i=0; i<fFileList.size(); i++)
    fFileList[i].Print();
}
