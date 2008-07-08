// $Id: FileMetaData.cc,v 1.1 2008/07/07 16:41:52 paus Exp $

#include "MitAna/Catalog/interface/FileMetaData.h"

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
