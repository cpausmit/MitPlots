//--------------------------------------------------------------------------------------------------
// $Id: SimpleExampleMod.h,v 1.1 2008/11/25 14:30:53 loizides Exp $
//
// SimpleExampleAnaMod
//
// This TAM module shows how to use TAM. It takes the MCParticle branch
// and produces the pt and eta distribution of the contained particles.
//
// The module also declares all relevant member functions of a TAModule
// and has extensive comments for each of them, even if for this simple
// example they are not implemented.
//
// More information about TAM in general can be found at
// http://www.cmsaf.mit.edu/twiki/bin/view/Software/TAM
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_PHYSICSMOD_SIMPLEEXAMPLEMOD_H
#define MITANA_PHYSICSMOD_SIMPLEEXAMPLEMOD_H

#include "MitAna/TreeMod/interface/BaseMod.h" 
#include "MitAna/DataTree/interface/Collections.h"

class TH1D;

namespace mithep 
{
  class SimpleExampleMod : public BaseMod 
  {
    public:
      SimpleExampleMod(const char *name="SimpleExampleMod", 
                       const char *title="Simple example analysis module");
      ~SimpleExampleMod() {}

      const char              *GetPartName()              const { return fPartName; }
      void                     SetPartName(const char *n)       { fPartName=n; }

    protected:
      TString                  fPartName;   //branch name of MCParticle collection
      MCParticleCol           *fParticles;  //!pointer to generated particle branch
      TH1D                    *fPtHist;     //!pt histogram
      TH1D                    *fEtaHist;    //!eta histogram

      void                     Begin();
      void                     BeginRun();
      void                     EndRun();
      void                     Process();
      void                     SlaveBegin();
      void                     SlaveTerminate();
      void                     Terminate();

      ClassDef(SimpleExampleMod,1) // TAM simple example analysis module
  };
}
#endif
