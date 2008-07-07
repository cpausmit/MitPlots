//--------------------------------------------------------------------------------------------------
// $Id: $
//
// Dataset
//
// This class implements a dataset. The dataset consists of a bunch of filesets which are each
// composed of several files. All files which of a given fileset reside in one storage area (in most
// cases directory).
//
// Authors: C.Paus
//--------------------------------------------------------------------------------------------------

#ifndef CATALOG_DATASET_H
#define CATALOG_DATASET_H

#include <TString.h>
#include "MitAna/Catalog/interface/FilesetMetaData.h"

namespace mithep 
{
  class Dataset : public BaseMetaData
  {
    public:
      Dataset() {}
      Dataset(const char *name);
      ~Dataset() {}

      const TString               *Name      ()  { return &fName; }

      void                         AddFileset(FilesetMetaData *fs);
      void                         AddFile   (const char *filesetName, FileMetaData *f);

      void                         Print     () const;

      const UInt_t                 NFiles    () const { return fNFiles; }
      const FileMetaData          *File      (UInt_t i) const;
      const char                  *FileUrl   (UInt_t i) const;

    private:
      TString                      fName;
      std::vector<FilesetMetaData> fFilesetList;        // list of filesets contained in the dataset

      UInt_t                       fNFiles;
  };
}
#endif
