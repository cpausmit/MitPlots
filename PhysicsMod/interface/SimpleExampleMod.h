//--------------------------------------------------------------------------------------------------
// $Id: SimpleExampleMod.h,v 1.3 2008/12/04 13:52:27 loizides Exp $
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
      void                     Begin();
      void                     BeginRun();
      void                     EndRun();
      void                     Process();
      void                     SlaveBegin();
      void                     SlaveTerminate();
      void                     Terminate();

      TString                  fPartName;   //branch name of MCParticle collection
      const MCParticleCol     *fParticles;  //!pointer to generated particle branch
      TH1D                    *fPtHist;     //!pt histogram
      TH1D                    *fEtaHist;    //!eta histogram

      ClassDef(SimpleExampleMod, 1) // Simple example analysis module
  };
}
#endif
