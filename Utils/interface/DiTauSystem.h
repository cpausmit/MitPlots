//--------------------------------------------------------------------------------------------------
// $Id: DiTauSystem.h,v 1.1 2008/09/30 19:24:22 ceballos Exp $
//
// to calculate the mass to the di-tau system, I 
// assume that the tau is boosted and that the 
// neutrinos have the same flight direction as the
// tau. 
//
// Authors: ceballos
//--------------------------------------------------------------------------------------------------

#ifndef UTIL_DITAUSYSTEM_H
#define UTIL_DITAUSYSTEM_H

#include "MitAna/TreeMod/interface/BaseMod.h" 
#include "MitAna/DataTree/interface/Collections.h"

namespace mithep
{
  class DiTauSystem {
    public:

  DiTauSystem(ChargedParticle *t1, ChargedParticle *t2, Met *met);
  ~DiTauSystem() {};

  double        RecoMass()       {return fRecoMass;}
  double        VisMass()        {return fVisMass;}
  double        XTau1()          {return fXTau[0];}
  double        XTau2()          {return fXTau[1];}
  double        TransverseMass() {return fMT;}
  double        TransverseEll()  {return fETll;}
  double        TransverseEnn()  {return fETnn;}
  
 private:
  void          init();
  
  ChargedParticle *fT1;
  ChargedParticle *fT2;
  Met             *fMet;
  
  // derived data members
  double        fXTau[2];
  double        fRecoMass;
  double        fVisMass;
  double        fMT;
  double        fETll;
  double        fETnn;
};
}
#endif
