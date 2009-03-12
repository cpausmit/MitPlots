// $Id: FileMetaData.cc,v 1.2 2008/07/08 05:50:57 loizides Exp $

#include "MitAna/Catalog/interface/FileMetaData.h"
#include <Riostream.h>

ClassImp(mithep::FileMetaData)

using namespace std;
using namespace mithep;

//--------------------------------------------------------------------------------------------------
FileMetaData::FileMetaData(const char *fileName, const BaseMetaData *metaData) :
  BaseMetaData(*metaData),
  fFileName   (fileName)
{
  // Constructor
}

//--------------------------------------------------------------------------------------------------
void FileMetaData::Print() const
{
  // Print useful information.

  cout << "     - File: " << fFileName.Data();
  BaseMetaData::Print();
}
