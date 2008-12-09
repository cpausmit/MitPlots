//--------------------------------------------------------------------------------------------------
// $Id: PlotKineMod.h,v 1.2 2008/12/04 13:52:27 loizides Exp $
//
// GenericSelMod
// 
// This module allows trivial event selection based on counting the number of
// particles found in the given kinematic range.
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_PHYSICSMOD_GENERICSELMOD_H
#define MITANA_PHYSICSMOD_GENERICSELMOD_H

#include "MitAna/PhysicsMod/interface/PlotKineMod.h" 

namespace mithep 
{
  template<class T>
  class GenericSelMod : public PlotKineMod<T>
  {
    public:
      GenericSelMod(const char *name="GenericSelMod", 
                    const char *title="Generic selection module");
      ~GenericSelMod() {}

      UInt_t                   GetMinCounts()         const { return fMinCounts; }
      void                     SetMinCounts(UInt_t c)       { fMinCounts = c; }

    protected:
      void                     Process();

      UInt_t                   fMinCounts; //minimum number of particles required to accept event

      ClassDefT(GenericSelMod,1) // Plot kinematics module
  };
}

//--------------------------------------------------------------------------------------------------
template<class T>
mithep::GenericSelMod<T>::GenericSelMod(const char *name, const char *title) : 
  PlotKineMod<T>(name,title),
  fMinCounts(1)
{
  // Constructor.

  this->SetFillHist(0);
}

//--------------------------------------------------------------------------------------------------
template<class T>
void mithep::GenericSelMod<T>::Process()
{
  // Process entries of the tree: Just load the branch and fill the histograms.

  UInt_t counter = 0;

  if (!this->Load()) {
    this->SendError(TAModule::kAbortModule, "Process", "Could not load data!");
    return;
  }

  UInt_t ents=this->fCol->GetEntries();

  for(UInt_t i=0;i<ents;++i) {
     const T *p = this->fCol->At(i);
     Double_t pt = p->Pt();
     if (pt<this->fPtMin) 
       continue;
     if (pt>this->fPtMax)
       continue;
     Double_t eta = p->Eta();
     if (eta<this->fEtaMin)
       continue;
     if (eta>this->fEtaMax)
       continue;

     ++counter;

     if (!this->GetFillHist())
       continue;

     this->fPtHist->Fill(pt);
     this->fEtaHist->Fill(eta);
  }

  // skip event if not enough particles are found in kinematic region
  if (counter<GetMinCounts())
    this->SkipEvent();
}
#endif
