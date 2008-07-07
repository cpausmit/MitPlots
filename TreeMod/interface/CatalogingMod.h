//--------------------------------------------------------------------------------------------------
// $Id: $
//
// Cataloging Module
//
// This TAM module analyzes the given files and writes out all metafile information necessary to
// create a catalog. Ideally Meta information should be created per file but this module will
// provide the combined Meta Information for all data analyzed. To get them per file therefore the
// module should be run per file separately.
//
// Authors: C.Paus
//--------------------------------------------------------------------------------------------------

#ifndef TREEMOD_CATALOGINGMOD_H
#define TREEMOD_CATALOGINGMOD_H

#include <TString.h>
#include "MitAna/TreeMod/interface/BaseMod.h"
#include "MitAna/Catalog/interface/BaseMetaData.h"

namespace mithep
{
  class CatalogingMod : public BaseMod
  {
    public:
      CatalogingMod(const char *name  = "CatalogingMod",
                    const char *title = "");
      ~CatalogingMod() {}

      void                     SetMetaDataString(const char* s) { fMetaDataString = TString(s); }
      const char              *MetaDataString()                 { return fMetaDataString.Data(); }

      void                     SetNFileSet(Int_t i)             { fNFileSet = i; }
      Int_t                    NFileSet()                       { return fNFileSet; }

    protected:
      void                     SlaveBegin();
      void                     BeginRun();
      void                     Process();
      void                     SlaveTerminate();

    private:
      TString                  fMetaDataString;
      Int_t                    fNFileSet;
      UInt_t                   fLastLumiSec;         // last active lumi section

      BaseMetaData             fMetaData;

      ClassDef(CatalogingMod,1)                      // Cataloging Module
  };
}
#endif
