//--------------------------------------------------------------------------------------------------
// $Id: CatalogingMod.h,v 1.3 2008/09/10 03:33:28 loizides Exp $
//
// CatalogingMod
//
// This TAM module analyzes the given files and writes out all metafile information necessary to
// create a catalog. Ideally Meta information should be created per file but this module will
// provide the combined Meta Information for all data analyzed. To get them per file therefore the
// module should be run per file separately.
//
// Authors: C.Paus
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_TREEMOD_CATALOGINGMOD_H
#define MITANA_TREEMOD_CATALOGINGMOD_H

#include <TString.h>
#include "MitAna/TreeMod/interface/BaseMod.h"
#include "MitAna/Catalog/interface/BaseMetaData.h"

namespace mithep
{
  class CatalogingMod : public BaseMod
  {
    public:
      CatalogingMod(const char *name  = "CatalogingMod",
                    const char *title = "Cataloging module producing a fileset catalog");
      ~CatalogingMod() {}

      Int_t                    NFileSet()       const                 { return fNFileSet; }
      const char              *MetaDataString()                 const { return fMetaDataString; }
      void                     SetNFileSet(Int_t i)                   { fNFileSet = i; }
      void                     SetMetaDataString(const char* s)       { fMetaDataString = s;    }

    protected:
      void                     SlaveBegin();
      void                     BeginRun();
      void                     Process();
      void                     SlaveTerminate();

    private:
      TString                  fMetaDataString;      //metadata description
      Int_t                    fNFileSet;            //number of fileset
      UInt_t                   fLastLumiSec;         //!last active lumi section
      BaseMetaData             fMetaData;            //!meta data info

      ClassDef(CatalogingMod, 1) // Cataloging module
  };
}
#endif
