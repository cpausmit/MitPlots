//--------------------------------------------------------------------------------------------------
// $Id: $
//
// FilesetMetaData - class for keeping meta data of a file
//
// This class inherits from the BaseMetaData and just adds on top a name for the fileset and a list
// of files which are contained.
//
// Authors: C.Paus
//--------------------------------------------------------------------------------------------------

#ifndef CATALOG_FILESETMETADATA_H
#define CATALOG_FILESETMETADATA_H

#include <vector>
#include <TString.h>
#include "MitAna/Catalog/interface/BaseMetaData.h"
#include "MitAna/Catalog/interface/FileMetaData.h"

namespace mithep 
{
  class FilesetMetaData : public BaseMetaData
  {
    public:
      FilesetMetaData() {}
      FilesetMetaData(const char *filesetName, const char *location);
      ~FilesetMetaData() {}

      const TString               *FilesetName ()         const { return &fFilesetName; }
      const TString               *Location    ()         const { return &fLocation; }
      const FileMetaData          *File        (UInt_t i) const { return &fFileList[i]; }
      UInt_t                       NFiles      ()         const { return fFileList.size(); }

      void                         AddFile     (FileMetaData *f);

      void                         Print       () const;

    protected:
      TString                      fFilesetName;          // name of the fileset
      TString                      fLocation;             // location of the fileset
      std::vector<FileMetaData>    fFileList;             // list of files contained in the fileset
  };
}
#endif
