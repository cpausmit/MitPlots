//--------------------------------------------------------------------------------------------------
// $Id: MCParticlesMod.h,v 1.4 2008/12/10 17:25:17 loizides Exp $
//
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_VALIDATION_MCPARTICLESVALMOD_H
#define MITANA_VALIDATION_MCPARTICLESVALMOD_H

#include "MitAna/TreeMod/interface/BaseMod.h" 
#include "MitAna/DataTree/interface/Collections.h"

class TH1D;

namespace mithep 
{
  class MCParticlesValMod : public BaseMod 
  {
    public:
      MCParticlesValMod(const char *name="MCParticlesValMod", 
                        const char *title="MCParticles analysis module");
      ~MCParticlesValMod() {}

      const char              *GetPartName()              const { return fPartName; }
      void                     SetPartName(const char *n)       { fPartName=n;      }

    protected:
      void                     Process();
      void                     SlaveBegin();
      void                     SlaveTerminate();

      TString                  fPartName;   //branch name of MCParticle collection
      const MCParticleCol     *fParticles;  //!pointer to generated particle branch
      TH1D                    *fHs[100];    //!histograms

      ClassDef(MCParticlesValMod, 1) // MCParticles analysis module
  };
}
#endif
