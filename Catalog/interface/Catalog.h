//--------------------------------------------------------------------------------------------------
// $Id: Catalog.h,v 1.1 2008/07/07 16:41:51 paus Exp $
//
// Catalog
//
// This class implements a catalog. The catalog consists of books which in turn consists of
// datasets. Datasets are a set of data which represent a coherent set of events. The catalog knows
// about the location of all datasets and can therefore provide any combination of (book,dataset).
//
// Authors: C.Paus
//--------------------------------------------------------------------------------------------------

#ifndef CATALOG_CATALOG_H
#define CATALOG_CATALOG_H

#include <TString.h>

namespace mithep 
{
  class Dataset;

  class Catalog
  {
    public:
      Catalog(const char *location);
      virtual ~Catalog() {}

      const TString           &Location() const { return fLocation; }
      Dataset                 *FindDataset(const char *book, const char *dataset);

    private:
      TString                  fLocation;    //Location of catalog

    ClassDef(Catalog, 0) // Simple catalog for books consisting of datasets
  };
}
#endif
