//--------------------------------------------------------------------------------------------------
// $Id: FilesetMetaData.h,v 1.3 2008/09/10 03:33:25 loizides Exp $
//
// FilesetMetaData
//
// This class keeps meta data of a file. It inherits from the BaseMetaData and just adds on 
// top a name for the fileset and a list of files which are contained.
//
// Authors: C.Paus
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_CATALOG_FILESETMETADATA_H
#define MITANA_CATALOG_FILESETMETADATA_H

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

      void                         AddFile     (const FileMetaData *f);
      const FileMetaData          *File        (UInt_t i) const { return &fFileList[i];    }
      const TString               *FilesetName ()         const { return &fFilesetName;    }
      UInt_t                       NFiles      ()         const { return fFileList.size(); }
      const TString               *Location    ()         const { return &fLocation;       }
      void                         Print       () const;

    protected:
      TString                      fFilesetName;   //name of the fileset
      TString                      fLocation;      //location of the fileset
      std::vector<FileMetaData>    fFileList;      //list of files contained in the fileset

    ClassDef(FilesetMetaData, 1) // Class keeping meta data of a file
  };
}
#endif
