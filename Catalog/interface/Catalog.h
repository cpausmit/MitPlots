//--------------------------------------------------------------------------------------------------
// $Id: Catalog.h,v 1.6 2010/10/01 02:20:26 paus Exp $
//
// Catalog
//
// This class implements a catalog. The catalog consists of books which in turn consist of
// datasets. Datasets are a set of data which represent a coherent set of events. The catalog knows
// about the location of all datasets and can therefore provide any combination of (book,dataset).
//
// For convenience datasets are subdivided into filesets which each contain a number of files.
// Filesets have to live in the same 'directory'. In principle a dataset could reside on various
// logical locations, but this likely never happens with the mass storage systems at hand. The main
// advantage of filesets is that they provide a natural unit to define separate processing tasks
// for job submission.
//
// Authors: C.Paus
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_CATALOG_CATALOG_H
#define MITANA_CATALOG_CATALOG_H

#include <TString.h>

namespace mithep 
{
  class Dataset;

  class Catalog
  {
    public:
      Catalog(const char *location);
      virtual ~Catalog() {}

      const TString           &Location()                            const { return fLocation; }
      Dataset                 *FindDataset(const char *book, const char *dataset,
					   const char *fileset = "", bool local = false) const;

    private:
      TString                  fLocation;    // location of catalog

    ClassDef(Catalog, 0) // Simple catalog for books consisting of datasets
  };
}
#endif
