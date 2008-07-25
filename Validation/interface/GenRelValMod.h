//--------------------------------------------------------------------------------------------------
// $Id: GenRelValMod.h,v 1.1 2008/07/10 14:56:27 loizides Exp $
//
// GenRelValMod
//
// This is an analysis module which is used to validate the genparticles filled into the tree.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef VALIDATION_GENRELVAL_H
#define VALIDATION_GENRELVAL_H

#include <Riostream.h>
#include "MitAna/TreeMod/interface/BaseMod.h"
#include "MitAna/DataTree/interface/Collections.h"

namespace mithep
{
  class GenRelValMod : public BaseMod
  {
    public:
      GenRelValMod(const char *name  = "GenRelValMod",
                   const char *title = "Analysis Module for GenParticles validation");
      ~GenRelValMod() {}

      void             Process       ();
      void             SlaveBegin    ();
      void             SlaveTerminate();

    protected:
      TString          fMCPartName;   //name of particle collection
      MCParticleCol   *fParticles;    //!particle branch
      std::ofstream   *ofile;         //!output text file

      ClassDef(GenRelValMod,1) // GenParticle validation module
  };
}
#endif
