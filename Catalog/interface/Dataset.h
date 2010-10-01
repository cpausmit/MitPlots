//--------------------------------------------------------------------------------------------------
// $Id: Dataset.h,v 1.3 2008/09/10 03:33:25 loizides Exp $
//
// Dataset
//
// This class implements a dataset. The dataset consists of a bunch of filesets which are each
// composed of several files. All files which of a given fileset reside in one storage area (in most
// cases directory).
//
// Authors: C.Paus
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_CATALOG_DATASET_H
#define MITANA_CATALOG_DATASET_H

#include <TString.h>
#include "MitAna/Catalog/interface/FilesetMetaData.h"

namespace mithep 
{
  class Dataset : public BaseMetaData
  {
    public:
      Dataset(TRootIOCtor *rio) {}
      Dataset(const char *name);
      ~Dataset() {}

      void                         AddFileset(const FilesetMetaData *fs);
      void                         AddFile   (const char *filesetName, const FileMetaData *f);
      const FileMetaData          *File      (UInt_t i) const;
      const char                  *FileUrl   (UInt_t i) const;
      const TString               *Name      ()         const { return &fName; }
      const UInt_t                 NFiles    ()         const { return fNFiles; }
      void                         Print     ()         const;

    private:
      TString                      fName;               //name of dataset
      std::vector<FilesetMetaData> fFilesetList;        //list of filesets contained in the dataset
      UInt_t                       fNFiles;             //number of files in dataset

      ClassDef(Dataset, 1) // Dataset consisting of filesets.
  };
}
#endif
