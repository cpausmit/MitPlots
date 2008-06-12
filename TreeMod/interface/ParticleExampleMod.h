// $Id: ParticleExampleMod.h,v 1.5 2008/06/09 00:06:36 bendavid Exp $

#ifndef TREEMOD_PARTICLEXAMPLEMOD_H
#define TREEMOD_PARTICLEXAMPLEMOD_H

#include "MitAna/TreeMod/interface/BaseMod.h" 
#include "MitAna/DataTree/interface/Collections.h"

class TH1D;

//--------------------------------------------------------------------------------------------------
//
// ParticleExampleAnaMod
//
// This TAM module shows how to use TAM. It takes the GenParticle branch
// and produces a pt and eta distribution.
//
// More information about TAM in general can be found at
// http://www.cmsaf.mit.edu/twiki/bin/view/Software/TAM
//
// Authors: C.Loizides
//
//--------------------------------------------------------------------------------------------------

namespace mithep 
{
  class ParticleExampleMod : public BaseMod 
  {
    public:
      ParticleExampleMod(const char *name="ParticleExampleMod", 
                         const char *title="Particle example analysis module");
      ~ParticleExampleMod() {}

      const char              *GetPartName()              const { return fPartName; }
      void                     SetPartName(const char *n)       { fPartName=n; }

    protected:
      TString                  fPartName;   //branch name of GenParticle collection
      GenParticleCol          *fParticles;  //!point to generated particle branch
      TH1D                    *fPtHist;     //!pt histogram
      TH1D                    *fEtaHist;    //!eta histogram

      void                     Begin();
      void                     Process();
      void                     SlaveBegin();
      void                     SlaveTerminate();
      void                     Terminate();

      ClassDef(ParticleExampleMod,1) // TAM example analysis module
  };
}
#endif
