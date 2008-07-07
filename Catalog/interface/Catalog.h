//--------------------------------------------------------------------------------------------------
// $Id: $
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
      Catalog() {}
      Catalog(const char *location);
      ~Catalog() {}

      TString                  Location()  { return fLocation; }
      Dataset*                 FindDataset(const char *book, const char *dataset);

    private:
      TString                  fLocation;
  };
}
#endif
