// $Id: ParticleExampleMod.h,v 1.1 2008/05/27 19:50:16 loizides Exp $

#ifndef TREEMOD_PARTICLEXAMPLEMOD_H
#define TREEMOD_PARTICLEXAMPLEMOD_H

#include "MitAna/TAM/interface/TAModule.h" 
#include "MitAna/DataTree/interface/Collections.h"

class TH1D;

//--------------------------------------------------------------------------------------------------
//
// THIExampleAnaMod
//
// This TAM module shows how to use TAM:
//   See http://www.cmsaf.mit.edu/twiki/bin/view/Software/TAM
//
// Authors: C.Loizides
//
//--------------------------------------------------------------------------------------------------

namespace mithep 
{
  class ParticleExampleMod : public TAModule 
  {
    public:
      ParticleExampleMod(const char *name="ParticleExampleMod", 
                         const char *title="Particle example analysis module");
      ~ParticleExampleMod() {}

      void                     Begin();
      void                     Process();
      void                     SlaveBegin();
      void                     SlaveTerminate();
      void                     Terminate();

      const char              *GetPartName()              const { return fPartName; }
      void                     SetPartName(const char *n)       { fPartName=n; }

    protected:
      ParticleCol             *fParticles;  //!point to particle branch
      TString                  fPartName;   //name of particle collection
      TH1D                    *fPtHist;     //!pt histogram
      TH1D                    *fEtaHist;    //!eta histogram

      ClassDef(ParticleExampleMod,1) // TAM example analysis module
  };

} /*namespace mithep*/

#endif /*TREEMOD_PARTICLEXAMPLEMOD_H*/
