// $Id: MCParticle.cc,v 1.5 2009/02/18 15:38:55 loizides Exp $

#include "MitAna/DataTree/interface/MCParticle.h"

ClassImp(mithep::MCParticle)

using namespace mithep;

//--------------------------------------------------------------------------------------------------
const MCParticle *MCParticle::FindDaughter(Int_t pid, 
                                           Bool_t checkCharge, const MCParticle *start) const
{
  // Return daughter with given pid. If checkCharge is false then just the type of particle is 
  // checked (ie particle and anti-particle). If start is not null, start searching from 
  // this daughter.

  UInt_t i = 0;
  if (start) {
    for (; i<NDaughters(); ++i) {
      if (Daughter(i)==start) {
        ++i;
        break;
      }
    }
    return 0;
  }

  for (UInt_t j=i; j<NDaughters(); ++j) {
    if (Daughter(j)->Is(pid,checkCharge)) 
      return Daughter(j);
  }

  return 0;
}

//--------------------------------------------------------------------------------------------------
const MCParticle *MCParticle::FindMother(Int_t pid, Bool_t checkCharge) const
{
  // Return mother with given pid. If checkCharge is false then just the type of particle is 
  // checked (ie particle and anti-particle). 

  const MCParticle *mother = Mother();
  if (!mother) 
    return 0;
  
  if (checkCharge) {
    while (mother && mother->PdgId()!=pid)
      mother = mother->Mother();
    return mother;
  }

  Int_t apid = pid>0?pid:-pid;
  while (mother && mother->AbsPdgId()!=apid)
    mother = mother->Mother();

  return mother;
}

//--------------------------------------------------------------------------------------------------
void MCParticle::Print(Option_t *opt) const
{
  // Print particle kinematics. In case option "l" is given then also print info about daughters.

  printf("id=%5d st=%2d nd=%3d gen=%d sim=%d px=%.3f py=%.3f pz=%.3f e=%.3f\n", 
         PdgId(), Status(), NDaughters(), IsGenerated(), IsSimulated(), Px(), Py(), Pz(), E());

  if (opt && opt[0]=='l') {
    for (UInt_t i=0; i<NDaughters(); ++i) {
      printf("  %2d -> id=%5d st=%2d gen=%d sim=%d px=%.3f py=%.3f pz=%.3f e=%.3f\n", 
             i, Daughter(i)->PdgId(), Daughter(i)->Status(), 
             Daughter(i)->IsGenerated(), Daughter(i)->IsSimulated(),
             Daughter(i)->Px(), Daughter(i)->Py(), Daughter(i)->Pz(), Daughter(i)->E());
    }
  }
}
