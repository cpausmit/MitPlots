//--------------------------------------------------------------------------------------------------
// $Id: FileMetaData.h,v 1.3 2008/09/10 03:33:25 loizides Exp $
//
// FileMetaData
//
// This class keeps meta data of a file. It inherits from the BaseMetaData and just adds 
// on top the filename.
//
// Authors: C.Paus
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_CATALOG_FILEMETADATA_H
#define MITANA_CATALOG_FILEMETADATA_H

#include <TString.h>
#include "MitAna/Catalog/interface/BaseMetaData.h"

namespace mithep 
{
  class FileMetaData : public BaseMetaData
  {
    public:
      FileMetaData() {}
      FileMetaData(const char *fileName, const BaseMetaData *metaData);
      ~FileMetaData() {}

      const TString               *FileName() const { return &fFileName; }
      void                         Print   () const;

    protected:
      TString                      fFileName;  //name of the file (no path included)

    ClassDef(FileMetaData, 1) // Class for keeping meta data of a file
  };
}
#endif
