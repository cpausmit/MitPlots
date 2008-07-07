//--------------------------------------------------------------------------------------------------
// $Id: $
//
// FileMetaData - class for keeping meta data of a file
//
// This class inherits from the BaseMetaData and just adds on top the filename.
//
// Authors: C.Paus
//--------------------------------------------------------------------------------------------------

#ifndef CATALOG_FILEMETADATA_H
#define CATALOG_FILEMETADATA_H

#include <TString.h>
#include "MitAna/Catalog/interface/BaseMetaData.h"

namespace mithep 
{
  class FileMetaData : public BaseMetaData
  {
    public:
      FileMetaData() {}
      FileMetaData(const char *fileName, BaseMetaData *metaData);
      ~FileMetaData() {}

      const TString               *FileName() const { return &fFileName; }

      void                         Print     () const;

    protected:
      TString                      fFileName;            // name of the file (no path included)
  };
}
#endif
