// $Id: $

#include <iostream>
#include "MitAna/Catalog/interface/FileMetaData.h"

using namespace std;
using namespace mithep;

//--------------------------------------------------------------------------------------------------
FileMetaData::FileMetaData(const char *fileName, BaseMetaData *metaData) :
  BaseMetaData(metaData),
  fFileName   (fileName)
{
  // Constructor
}

void FileMetaData::Print() const
{
  cout << "     - File: " << fFileName.Data();
  BaseMetaData::Print();
}
